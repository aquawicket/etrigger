//// MainPanel.cpp //////////////////////////////////////////////////////
//
//
/////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "MainPanel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////
BEGIN_EVENT_TABLE(MainPanel, wxPanel)
#ifndef VST
	EVT_MAXIMIZE     (MainPanel::OnMaximize)
	EVT_MOUSE_EVENTS (MainPanel::OnMouse)
	EVT_SIZE         (MainPanel::OnSize)
	EVT_CLOSE        (MainPanel::OnClose) 
	EVT_IDLE         (MainPanel::OnIdle)
	#ifdef WIN32  //The custom Scrollbar is not ready for Mac yet
	EVT_GSCROLLBAR   (110, MainPanel::OnGScrollBar)
	#endif //WIN32
#endif //VST
END_EVENT_TABLE() 


////////////////////////////// eTrigger Stand-Alone /////////////////////////////////////////////
#ifndef VST
///////////////////////////////////////////////////////////////////////////////////////////////
MainPanel::MainPanel(MainFrame* parent, wxString ver, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
		  :wxPanel(parent, id, pos, size, style, name)
{ 
	InitVariables();

	par = parent;
	version = ver;
	security = new Security(this);
	
	topSizer = new wxBoxSizer(wxVERTICAL);

	menuPanel = new MenuPanel(this, wxID_ANY, wxPoint(0,0), wxDefaultSize, wxBORDER_NONE, wxT("manuPanel"));
	topSizer->Add(menuPanel, 0, wxEXPAND, 0);

	//All of the tracks sit on this panel
	trackPanel = new TrackPanel(this, wxID_ANY, wxPoint(0,0), wxDefaultSize, wxBORDER_NONE, wxT("trackPanel"));
	topSizer->Add(trackPanel, 1, wxEXPAND, 0);

	scrollbar = new GScrollBar(this, trackPanel, 110, 2);

	topSizer->Add(scrollbar, 0, wxEXPAND, 0);
	topSizer->SetItemMinSize(scrollbar, par->frameSize.x, 15);

	SetSizer( topSizer ); 

	//Create all of the processes
	trackProc = new TrackProc(trackPanel); //Create a TrackProc database. 
	saveData = new TrackProc(trackPanel); //create a place to store "check for save" data
	StoreSaveData(); //then lets store it.

	midi = new Midi(trackProc); //Create a Midi Interface
	audio = new Audio(trackProc); //Create an Audio Interface
	soundController = new SoundController(this);
	etmFile = new EtmFile(soundController);
	samples = new Samples(soundController);
	joystick = new Joystick(this);
	statusDialog = new StatusDialog(this);
	midiMonitor = new MidiMonitor(this);
	details = new Details(this);
	sequencePlayer = new SequencePlayer();

	process = new Process(this);
	trackProc->LinkMidi(midi); //Let the TrackProc database know where the midi interface is.
	trackProc->LinkAudio(audio); //Let the TrackProc database know where the audio interface is.
	Process::LinkStatus(statusDialog); //Let the Process:: know where the StatusDialog is.
	Process::LinkMidiMonitor(midiMonitor);
	Process::LinkSequencePlayer(sequencePlayer);
	Process::LinkTrk(trackProc); //Let Process:: know where the TrackProc database is. 
	Process::LinkMenu(menuPanel);
	
	fileDirectory = wxT(".\\Kits");// is this the best place to default this variable?

	LoadMainSettings(); //Load ETR.dat

	security->DoTimeCheck();
	security->SetLastRunTime(); //Set Last Run Time Marker to Now.
	security->ImplantFirstAndLastRunTime(); //And implant the dates
	SaveMainSettings(); //LastRunTime has been updated and we want to save it now.

	trackProc->SetPreLoad(trackProc->preLoad); //preLoad all windows into memory?

	Process::active = true; //Turn the Process engine on last.

	//ToolTips
	idleMarker = 0;
	SetExtraStyle(wxWS_EX_PROCESS_IDLE);

	client = new Client(this); //client->Show();
	//netTimer = new NetTimer(*client);

	//Let's check if an update file exists
	if(::wxFileExists(wxT("eTrigger-Update.zip"))){

		//FIXME, we must also check to see that the size of the file is in range.
		// but give a megabyte or 2 to spare so we have room to flex.
		// We do this because the download may not have completed, and file is bad.
		 
		wxMessageDialog temp(this, 
			wxT("The newest version of eTrigger is ready to install. Install it now?"),
			wxT("Install Update?"), wxYES_NO | wxSTAY_ON_TOP, wxDefaultPosition);
			if(temp.ShowModal() == wxID_YES){
				client->InstallUpdate();
			}
	}

	//Tray Icon
	trayIcon = new TrayIcon(this);

	gTimer = new GTimer();
	gTimer->LinkTrackProc(trackProc);
	gTimer->LinkSequencePlayer(sequencePlayer);
	gTimer->LinkNetwork(client);
}
#endif //!VST




////////////////////////// eTrigger VST ////////////////////////////
#ifdef VST
//////////////////////////////////////////////////////////////////
MainPanel::MainPanel( wxVstEditor* editor ) : wxVstPanel( editor )
{
	InitVariables();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MainPanel::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
	version = wxString(wxT("0.521"));
    wxVstPanel::Create( parent, id, pos, size, style );
	par = (EtriggerEditor*)parent;
	
	security = new Security(this);
	
	topSizer = new wxBoxSizer(wxVERTICAL);
	
	//We must make the menu this way for VST
	menuPanel = new MenuPanel(this, wxID_ANY, wxPoint(0,0), wxSize(800,25), wxBORDER_NONE, wxT("manuPanel"));
	topSizer->Add(menuPanel, 0, wxEXPAND, 0);
	topSizer->SetItemMinSize(menuPanel, GetSize().x, 25);
	
	//All of the tracks sit on this panel
	trackPanel = new TrackPanel(this, wxID_ANY, wxPoint(0,0), wxSize(800, 600), wxBORDER_NONE, wxT("trackPanel"));
	topSizer->Add(trackPanel, 1, wxEXPAND, 0);
	
	//The custome Scrollbar is not ready for MAC yet
#ifdef WIN32
	scrollbar = new GScrollBar(this, trackPanel, 110, 2);
	topSizer->Add(scrollbar, 0, wxEXPAND, 0);
	topSizer->SetItemMinSize(scrollbar, GetSize().x, 15);
#endif //WIN32
	
	SetSizer( topSizer ); 
	
	GetSizer()->Fit(this);
    GetSizer()->SetSizeHints(this);
	
	//Create all of the processes
	trackProc = new TrackProc(trackPanel); //Create a TrackProc database. 
	saveData = new TrackProc(trackPanel); //create a place to store "check for save" data
	StoreSaveData(); //then lets store it.
	
	midi = new Midi(trackProc); //Create a Midi Interface
	audio = new Audio(trackProc); //Create an Audio Interface
	//soundController = new SoundController();
	etmFile = new EtmFile(soundController);
	samples = new Samples(soundController);
	joystick = new Joystick(this);
	statusDialog = new StatusDialog(this);
	midiMonitor = new MidiMonitor(this);
	details = new Details(this);
	
	Process *proc = new Process(this);
	trackProc->LinkMidi(midi); //Let the TrackProc database know where the midi interface is.
	trackProc->LinkAudio(audio); //Let the TrackProc database know where the audio interface is.
	Process::LinkStatus(statusDialog); //Let the Process:: know where the StatusDialog is.
	Process::LinkMidiMonitor(midiMonitor);
	Process::LinkTrk(trackProc); //Let Process:: know where the TrackProc database is. 
	
	fileDirectory = wxT(".\\Kits");// is this the best place to default this variable?
	
	LoadMainSettings(); //Load ETR.dat
	security->DoTimeCheck();
	security->SetLastRunTime(); //Set Last Run Time Marker to Now.
	security->ImplantFirstAndLastRunTime(); //And implant the dates
	SaveMainSettings(); //LastRunTime has been updated and we want to save it now.
	
	trackProc->SetPreLoad(trackProc->preLoad); //preLoad all windows into memory?
	
	Process::active = true; //Turn the Process engine on last.
	
	//ToolTips
	idleMarker = 0;
	SetExtraStyle(wxWS_EX_PROCESS_IDLE);
	
	client = new Client(this); //client->Show();
	//netTimer = new NetTimer(*client);
	
	//Let's check if an update file exists
	if(::wxFileExists(wxT("eTrigger-Update.zip"))){
		
		//FIXME, we must also check to see that the size of the file is in range.
		// but give a megabyte or 2 to spare so we have room to flex.
		// We do this because the download may not have completed, and file is bad.
		
		wxMessageDialog temp(this, 
							 wxT("The newest version of eTrigger is ready to install. Install it now?"),
							 wxT("Install Update?"), wxYES_NO | wxSTAY_ON_TOP, wxDefaultPosition);
		if(temp.ShowModal() == wxID_YES){
			client->InstallUpdate();
		}
	}
	
	//Tray Icon
	trayIcon = new TrayIcon(this);
	
    return TRUE;
}

/////////////////////////////////////////////////////////
void MainPanel::setParameter (long index, float value)
{
	/*
	 switch (index)
	 {
	 case kDelay:
	 delayFader->SetValue( round(value * 100) );
	 delayDisplay->SetLabel( wxString::Format( wxT("%.2f"), value ) );
	 break;
	 }
	 */
}

/////////////////////////////////////////////
float MainPanel::getParameter (long index)
{
	/*
	 switch (index)
	 {
	 case kDelay:
	 return (float)delayFader->GetValue() / 100;
	 break;
	 }
	 */
	
	return 0;
}
#endif //VST



///////////////////////
MainPanel::~MainPanel() 
{ 
//#ifndef VST
	
	SaveMainSettings();
	
	delete gTimer;
	delete security;
	delete trackProc;
	delete saveData;
	delete midi;
	delete audio;
	delete soundController;
	delete joystick;
	delete trackPanel;
	//delete netTimer;
	delete details;
	delete trayIcon;
	delete samples;
	delete etmFile;
	delete statusDialog;
	delete midiMonitor;
	delete audioDialog;
	delete midiDialog;
	delete joystickDialog;
	delete aboutDialog;
	delete optionsDialog;
	delete notesDialog;
	delete debugDialog;
	delete etmPlayerDialog;
	delete etmEditorDialog2;
	delete process;
	delete sequencePlayer;

//#endif //!VST
}

///////////////////////////////
void MainPanel::InitVariables()
{
	par = NULL;
	topSizer = NULL;
	menuPanel = NULL;
    trackPanel = NULL;
	scrollbar = NULL;
	debugDialog = NULL;
	audioDialog = NULL;
	midiDialog = NULL;	
	joystickDialog = NULL;
	statusDialog = NULL;
	midiMonitor = NULL;
	closeDLG = NULL;
	optionsDialog = NULL;
	aboutDialog = NULL;
	client = NULL;
	netTimer = NULL;
	notesDialog = NULL;
	details = NULL;
	pianoDialog = NULL;
	sequencerDialog = NULL;
	sequencePlayer = NULL;
	etmFile = NULL;
	etmPlayerDialog = NULL;
	etmEditorDialog2 = NULL;
	wizardDlg = NULL;
	sampleDialog = NULL;
	trackProc = NULL;
	midi = NULL;
	audio = NULL;
	soundController = NULL;
	samples = NULL;
	joystick = NULL;
	security = NULL;
	fileDirectory = wxT("");
	fileName = wxT("");
	saveData = NULL;
	version = wxT("");
	splashScreen = NULL;
	idleMarker = NULL;
	toolTips = NULL;
	versionNotes = NULL;
	initPath = wxT("");
	initFilename = wxT("");
	trayIcon = NULL;
	process = NULL;
}

//////////////////////////////////////////
void MainPanel::OnIdle(wxIdleEvent &event)
{
	// FIXME -  there has to be a better way to do this.

	//Tooltips
	if(toolTips){
		wxToolTip::Enable(true);
		wxToolTip::SetDelay(500);
	}
	else{
		wxToolTip::Enable(false); 
	}

	if(idleMarker > 500){
		SetExtraStyle(0); //Stop processing Idle
//#ifdef WIN32
	security->IsTrialPeriodUp();	
//#endif //WIN32
	}

	++idleMarker;
}

////////////////////////////////////////////////
void MainPanel::OnMenuNew(wxCommandEvent &event)
{
	//Bring up a save dialog if needed
	if(CheckForSave()){
		wxMessageDialog *temp = new wxMessageDialog(this, wxT("Save Changes Before Exiting ?"), wxT("Edrum Monitor"), wxYES_NO | wxCANCEL | wxSTAY_ON_TOP, wxDefaultPosition);
		int response = temp->ShowModal();
		if(response == wxID_YES){ if(!SaveVarsToFile(FALSE)){return;} }
		if(response == wxID_CANCEL){ return; }
		delete temp;
	}

	//Delete all current tracks
	trackProc->DeleteAllTracks();

	trackProc->focused = 0;
	fileDirectory = wxT(".\\Kits");

	StoreSaveData();
}

/////////////////////////////////////////////////
void MainPanel::OnMenuOpen(wxCommandEvent &event)
{	
	//Bring up a save dialog if needed
	if(CheckForSave()){
		wxMessageDialog *temp = new wxMessageDialog(this, wxT("Save Changes Before Exiting ?"), wxT("Edrum Monitor"), wxYES_NO | wxCANCEL | wxSTAY_ON_TOP, wxDefaultPosition);
		int response = temp->ShowModal();
		if(response == wxID_YES){ if(!SaveVarsToFile(FALSE)){return;} }
		if(response == wxID_CANCEL){ return; }
	}

	GetVarsFromFile(wxT(""), wxT(""));
}

/////////////////////////////////////////////////
void MainPanel::OnMenuSave(wxCommandEvent &event)
{
	SaveVarsToFile(0);
}

///////////////////////////////////////////////////
void MainPanel::OnMenuSaveAs(wxCommandEvent &event)
{
	SaveVarsToFile(1);
}

/////////////////////////////////////////////////
void MainPanel::OnMenuExit(wxCommandEvent &event)
{
    Close(); //FIXME - this does not trigger OnClose event in VST

	//#ifdef VST
	//OnClose( wxCloseEvent(wxEVT_NULL) );
	//#endif //VST
}

///////////////////////////////////////////////////////
void MainPanel::OnMenuWindowMode(wxCommandEvent &event)
{
#ifndef VST
	if(par->IsFullScreen()){
		par->ShowFullScreen(false, wxFULLSCREEN_ALL);
	}
#endif //VST
}

///////////////////////////////////////////////////////
void MainPanel::OnMenuFullScreen(wxCommandEvent &event)
{
#ifndef VST
	if(!par->IsFullScreen()){
	   par->ShowFullScreen(true, wxFULLSCREEN_NOBORDER|wxFULLSCREEN_NOCAPTION);
	}
#endif //VST
}

///////////////////////////////////////////////////////
void MainPanel::OnMenuAddTrigger(wxCommandEvent &event)
{	
	trackProc->AddTrigger();
}

//////////////////////////////////////////////////////
void MainPanel::OnMenuAddMidiCC(wxCommandEvent &event)
{	
	trackProc->AddMidiCC();
}

////////////////////////////////////////////////////////
void MainPanel::OnMenuDeleteTrack(wxCommandEvent &event)
{
	trackProc->DeleteTrack(trackProc->focused, true);
}

////////////////////////////////////////////////////////
void MainPanel::OnMenuSetupWizard(wxCommandEvent &event)
{	
	if(wizardDlg == NULL){
		wizardDlg = new WizardDlg(this, *trackProc);
		wizardDlg->Show();
		wizardDlg->SetFocus();
	}
	else{
		wizardDlg->Show();
		wizardDlg->SetFocus();
	}
}

/////////////////////////////////////////////////////////
void MainPanel::OnMenuAudioDevices(wxCommandEvent &event)
{
	if(audioDialog == NULL){
		audioDialog = new AudioDialog(audio);
		audioDialog->Show();
		audioDialog->SetFocus();
	}
	else{
		audioDialog->Show();
		audioDialog->SetFocus();
	}
}

////////////////////////////////////////////////////////
void MainPanel::OnMenuMidiDevices(wxCommandEvent &event)
{
	if(midiDialog == NULL){
		midiDialog = new MidiDialog(midi);
		midiDialog->Show();
		midiDialog->SetFocus();
	}
	else{
		midiDialog->Show();
		midiDialog->SetFocus();
	}
}

////////////////////////////////////////////////////////
void MainPanel::OnMenuGameDevices(wxCommandEvent &event)
{
	if(joystickDialog == NULL){
		joystickDialog = new JoystickDialog(joystick);
		joystickDialog->Show();
		joystickDialog->SetFocus();
	}
	else{
		joystickDialog->Show();
		joystickDialog->SetFocus();
	}
}

////////////////////////////////////////////////////
void MainPanel::OnMenuOptions(wxCommandEvent &event)
{
	if(optionsDialog == NULL){
		optionsDialog = new OptionsDialog(this, *trackProc);
		optionsDialog->Show();
		optionsDialog->SetFocus();
	}
	else{
		optionsDialog->Show();
		optionsDialog->SetFocus();
	}
}

///////////////////////////////////////////////////
void MainPanel::OnMenuStatus(wxCommandEvent &event)
{
	statusDialog->Show();
}

////////////////////////////////////////////////////////
void MainPanel::OnMenuMidiMonitor(wxCommandEvent &event)
{
	midiMonitor->Show();
}

//////////////////////////////////////////////////
void MainPanel::OnMenuPiano(wxCommandEvent &event)
{
	if(pianoDialog == NULL){
		pianoDialog = new PianoDialog(this);
		pianoDialog->Show();
		pianoDialog->SetFocus();
	}
	else{
		pianoDialog->Show();
		pianoDialog->transWindow->Show();
		pianoDialog->SetFocus();
	}
}

//////////////////////////////////////////////////////
void MainPanel::OnMenuSequencer(wxCommandEvent &event)
{
	if(sequencerDialog == NULL){
		sequencerDialog = new SequencerDialog(this);
		sequencerDialog->Show();
		sequencerDialog->SetFocus();
	}
	else{
		sequencerDialog->Show();
		sequencerDialog->SetFocus();
	}
}

////////////////////////////////////////////////////
void MainPanel::OnMenuSamples(wxCommandEvent &event)
{
	/*
	if(sampleDialog == NULL){
		sampleDialog = new SampleDialog(this);
		sampleDialog->Show();
		sampleDialog->SetFocus();
	}
	else{
		sampleDialog->Show();
		sampleDialog->SetFocus();
	}
	*/
}

///////////////////////////////////////////////////
void MainPanel::OnMenuPlayer(wxCommandEvent &event)
{
	if(etmPlayerDialog == NULL){
		etmPlayerDialog = new EtmPlayerDialog(this);
		etmPlayerDialog->Show();
		etmPlayerDialog->SetFocus();
	}
	else{
		etmPlayerDialog->Show();
		etmPlayerDialog->SetFocus();
	}
}
//////////////////////////////////////////////////
void MainPanel::OnMenuDebug(wxCommandEvent &event)
{
	if(debugDialog == NULL){
		debugDialog = new DebugDialog(this);
		debugDialog->Show();
		debugDialog->SetFocus();
	}
	else{
		debugDialog->Show();
		debugDialog->SetFocus();
	}
}

///////////////////////////////////////////////////
void MainPanel::OnMenuManual(wxCommandEvent &event)
{
	wxStandardPaths stdPath; 
    wxString fileLocation = stdPath.GetExecutablePath(); 
#ifdef MAC
	wxString temp = wxT("file://");
	temp += fileLocation;
	temp.Replace(wxT("eTrigger.app/Contents/MacOS/eTrigger"), wxT(""), true);
	temp += wxT("Manual/manual.html");
	fileLocation = temp;
#endif //MAC
#ifdef WIN32
	fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\Manual\\manual.html");
#endif //WIN32
	wxLaunchDefaultBrowser(fileLocation, wxBROWSER_NEW_WINDOW);
}

//////////////////////////////////////////////////
void MainPanel::OnMenuAbout(wxCommandEvent &event)
{
	if(aboutDialog == NULL){
		aboutDialog = new AboutDialog(this);
		aboutDialog->Show();
		aboutDialog->SetFocus();
	}
	else{
		aboutDialog->Show();
		aboutDialog->SetFocus();
	}
}

////////////////////////////////////////////
void MainPanel::OnClose(wxCloseEvent &event)
{
	//Bring up a save dialog if needed
	if(CheckForSave()){
		wxMessageDialog temp(this, wxT("Save Changes Before Exiting ?"), wxT("eTrigger"), wxYES_NO | wxCANCEL | wxSTAY_ON_TOP, wxDefaultPosition);
		int response = temp.ShowModal();
		if(response == wxID_YES){ if(!SaveVarsToFile(FALSE)){return;}}
		if(response == wxID_CANCEL){return;}
	}
 
	closeDLG = new wxDialog(this, -1, wxT(""), wxDefaultPosition, wxSize(125,60), 0, wxT(""));
	closeDLG->CenterOnParent(wxBOTH);
	closeDLG->Show();
	wxStaticText *text = new wxStaticText(closeDLG, -1, wxT("Closing Devices . . ."), wxPoint(10, 20), wxDefaultSize, 0, wxT(""));
	
	par->Hide();
//#ifdef VST
	//par->close();
//#endif //VST
	
#ifndef VST
	par->Hide();
	par->Destroy(); //END OF PROGRAM
#endif //VST
}

////////////////////////////
void MainPanel::OnMinimize()
{
#ifndef VST
	par->Iconize(true);
#endif //VST
}

//////////////////////////////////////////////////
void MainPanel::OnMaximize(wxMaximizeEvent& event)
{
	//The custome Scrollbar is not ready for MAC yet
#ifdef WIN32
	scrollbar->ResetScroll();
	trackPanel->position = scrollbar->scrollwinposition;
#endif //WIN32

	event.Skip(true); 
}

///////////////////////////////////////////////////////////
void MainPanel::OnMenuMinimizeToTray(wxCommandEvent &event)
{
#ifndef VST
	par->Hide();
#endif //VST
}

/////////////////////////////////
void MainPanel::RestoreFromTray()
{
#ifndef VST
	par->Show();
#endif //VST
}

//////////////////////////////////
void MainPanel::SaveMainSettings() //FIXME - VST isn't saving correctly
{
	//If the file does not exist, it will create it. 
	wxFile* save = new wxFile(wxT("ETR.dat"), wxFile::write);
	if(save->IsOpened()){

		/// HEADER ////////////////////////////////////////////////
		WriteString((wxString(wxT("ETR ")) += version), *save);

		/// Splash Screen ///////////////////////////////
		save->Write(&splashScreen, sizeof(splashScreen));

		/// Security ////////////////////////////////////////////////////////
		save->Write(&security->firstRunTime, sizeof(security->firstRunTime));
		save->Write(&security->lastRunTime, sizeof(security->lastRunTime));

		/// FRAME SIZE AND POSITION //////////////////////////////
		
		//if(par->IsMaximized()){maximized = true;}else{maximized = false;}
#ifndef VST
		save->Write(&par->maximized, sizeof(par->maximized));
		save->Write(&par->frameSize, sizeof(par->frameSize));
		save->Write(&par->framePosition, sizeof(par->framePosition));
#endif //VST

#ifdef VST
		bool maximized = false;
		wxSize frameSize = GetSize();
		wxPoint framePosition = GetPosition();
		save->Write(&maximized, sizeof(maximized));
		save->Write(&frameSize, sizeof(frameSize));
		save->Write(&framePosition, sizeof(framePosition));
#endif //VST
		///////////////////////////////////////////////////////////


		/// Status Dialog Size and Position ///////////////////////
		save->Write(&statusDialog->size, sizeof(statusDialog->size));
		save->Write(&statusDialog->position, sizeof(statusDialog->position));
		save->Write(&statusDialog->shown, sizeof(statusDialog->shown));
		///////////////////////////////////////////////////////////


		/// Tooltips //////////////////////////////////////////////
		save->Write(&toolTips, sizeof(toolTips));


		/// AUDIO API & DEVICES //////////////////////////////////
		save->Write(&audio->inSampleRate, sizeof(audio->inSampleRate));
		save->Write(&audio->outSampleRate, sizeof(audio->outSampleRate));
		save->Write(&audio->framesPerBuffer, sizeof(audio->framesPerBuffer));
		
		//API
		WriteString(audio->selectedInAPI, *save);
		WriteString(audio->selectedOutAPI, *save);

		//Devices
		int devices = audio->selectedIn.size();
		save->Write(&devices, sizeof(devices));
		for(int i=0; i<devices; ++i){
			WriteString(audio->selectedIn.Item(i), *save);
		}
		devices = audio->selectedOut.size();
		save->Write(&devices, sizeof(devices));
		for(int i=0; i<devices; ++i){
			WriteString(audio->selectedOut.Item(i), *save);
		}

		/// MIDI DEVICES /////////////////////////////////////////
		int devices2 = midi->selectedIn.size();
		save->Write(&devices2, sizeof(devices2));
		for(int i=0; i<devices2; ++i){
			WriteString(midi->selectedIn.Item(i), *save);
		}
		devices2 = midi->selectedOut.size();
		save->Write(&devices2, sizeof(devices2));
		for(int i=0; i<devices2; ++i){
			WriteString(midi->selectedOut.Item(i), *save);
		}

		/// GAME DEVICES ////////////////////////////////////////
		//Devices
		int devices3 = joystick->selected.size();
		save->Write(&devices3, sizeof(devices3));
		for(int i=0; i<devices3; ++i){
			WriteString(joystick->selected.Item(i), *save);
		}

		///// PreLoad Setting ///////////
		save->Write(&trackProc->preLoad, sizeof(trackProc->preLoad));

		///// Track File /////////////////////////////////////
		WriteString(initPath, *save);
		WriteString(initFilename, *save);

		///// Enable Meters /////////////////
		save->Write(&trackProc->enableMeters, sizeof(trackProc->enableMeters));

		///// Mouse Wheel Sensitivity /////////////
		save->Write(&trackProc->mouseSensitivity, sizeof(trackProc->mouseSensitivity));

		///// Midi Bleed /////////////////
		save->Write(&trackProc->midiBleed, sizeof(trackProc->midiBleed));

		///// Midi Input Channels ////////////////
		save->Write(&trackProc->midiChannel, sizeof(trackProc->midiChannel));

		///// Version Notes /////////////////////////////
		save->Write(&versionNotes, sizeof(versionNotes));

		///// Log Status Dialog //////////////////////////
		save->Write(&statusDialog->logToFile, sizeof(statusDialog->logToFile));

		///// Retrigger //////////////////////////////////
		save->Write(&trackProc->retriggerSafty, sizeof(trackProc->retriggerSafty));
		save->Write(&trackProc->retriggerThreshold, sizeof(trackProc->retriggerThreshold));
		save->Write(&trackProc->flamAdjustment, sizeof(trackProc->flamAdjustment));
		save->Write(&trackProc->rollAdjustment, sizeof(trackProc->rollAdjustment));

		///// Joystick Settings ///////////////////////////////
		save->Write(&joystick->pollSpeed, sizeof(joystick->pollSpeed));
		int temp = joystick->GetMaxX();
		save->Write(&temp, sizeof(temp));
		temp = joystick->GetMaxY();
		save->Write(&temp, sizeof(temp));
		temp = joystick->GetMaxZ();
		save->Write(&temp, sizeof(temp));
		temp = joystick->GetMaxR();
		save->Write(&temp, sizeof(temp));
		temp = joystick->GetMaxU();
		save->Write(&temp, sizeof(temp));
		temp = joystick->GetMaxV();
		save->Write(&temp, sizeof(temp));

		for(int i=0; i<3; ++i){
			WriteString(samples->sampleDir, *save);
		}

		///// Footer /////////////
		WriteString((wxString(wxT("ETR ")) += version), *save);

		save->Close();
		delete save;
	}
}

//////////////////////////////////
void MainPanel::LoadMainSettings()
{
	//Does the file exists?
	if(wxFile::Exists(wxT("ETR.dat"))){
		wxFile *file = new wxFile(wxT("ETR.dat"), wxFile::read);
		if(file->IsOpened()){

			//If the file has data, let's load the settings
			if(!file->Eof()){

				/// HEADER ////////////////////////////////////////////////
				wxString header = ReadString(*file);
				wxString fileVersion = header.Mid(4, 1000/*wxSTRING_MAXLEN*/);

				if(FileIsValid(header)){//Here we need to make sure the file is valid

					/// Splash Screen /////////////////////////////
					file->Read(&splashScreen, sizeof(splashScreen));

					/// Security ////////////////////////////////////////////////////////
					file->Read(&security->firstRunTime, sizeof(security->firstRunTime));
					file->Read(&security->lastRunTime, sizeof(security->lastRunTime));
					
					//This one spot where we reset the 30 day trial.
					if(fileVersion == wxT("0.428b")){
						   security->firstRunTime = security->currentTime;
						   security->lastRunTime = security->currentTime;
					}
					
					/// FRAME SIZE AND POSITION //////////////////////////////
#ifndef VST
					file->Read(&par->maximized, sizeof(par->maximized));
					file->Read(&par->frameSize, sizeof(par->frameSize));
					file->Read(&par->framePosition, sizeof(par->framePosition));
#endif //VST

#ifdef VST
					bool maximized;
					wxSize frameSize;
					wxPoint framePosition;
					file->Read(&maximized, sizeof(maximized));
					file->Read(&frameSize, sizeof(frameSize));
					file->Read(&framePosition, sizeof(framePosition));
#endif //VST

					/// Status Dialog Size and Position
					file->Read(&statusDialog->size, sizeof(statusDialog->size));
					file->Read(&statusDialog->position, sizeof(statusDialog->position));
					file->Read(&statusDialog->shown, sizeof(statusDialog->shown));
					
					/// ToolTips ////////////////////////////////////////////
					file->Read(&toolTips, sizeof(toolTips));

					/// AUDIO API & DEVICES //////////////////////////////////
					audio->StopCallback(); //must Stop Callbacks before changing audio devices
					audio->KillStreams();
					file->Read(&audio->inSampleRate, sizeof(audio->inSampleRate));
					file->Read(&audio->outSampleRate, sizeof(audio->outSampleRate));
					int framesPerBuffer = 0;
					file->Read(&framesPerBuffer, sizeof(audio->framesPerBuffer));
					audio->SetAudioBuffer(framesPerBuffer);

					//API
					wxString api = ReadString(*file);
					audio->SetInAPI(api);
					api = ReadString(*file);
					audio->SetOutAPI(api);

					//DEVICES
					int devices = 0;
					wxArrayString temp;
					file->Read(&devices, sizeof(devices));
					for(int i=0; i<devices; ++i){
						temp.Add(ReadString(*file), 1);
					}
					audio->SetInDevices(temp);

					temp.Clear();
					file->Read(&devices, sizeof(devices));
					for(int i=0; i<devices; ++i){
						temp.Add(ReadString(*file), 1);
					}
					audio->SetOutDevices(temp);

					audio->StartCallback(); //Start callbacks after devices are selected

					///// MIDI DEVICES /////////////////////////////////////
					midi->StopCallback();
					wxArrayString temp2;
					int devices2 = 0;
					file->Read(&devices2, sizeof(devices2));
					for(int i=0; i<devices2; ++i){
						temp2.Add(ReadString(*file), 1);
					}
					midi->SetInDevices(temp2);

					wxArrayString temp3;
					file->Read(&devices2, sizeof(devices2));
					for(int i=0; i<devices2; ++i){
						temp3.Add(ReadString(*file), 1);
					}
					midi->SetOutDevices(temp3);

					midi->StartCallback();


					///// GAME DEVICES /////////////////////////////////////
					wxArrayString temp4;
					int devices3 = 0;
					file->Read(&devices3, sizeof(devices3));
					for(int i=0; i<devices3; ++i){
						temp4.Add(ReadString(*file), 1);
					}
					joystick->SetDevices(temp4);

					///// PreLoad Setting
					file->Read(&trackProc->preLoad, sizeof(trackProc->preLoad));

					///// Track File /////////////////////////////////////
					initPath = ReadString(*file);
					initFilename = ReadString(*file);

					if(initPath != wxT("") && initFilename != wxT("")){
						GetVarsFromFile(initPath, initFilename);
					}

					///// Enable Meters ///////////////////////////////
					file->Read(&trackProc->enableMeters, sizeof(trackProc->enableMeters));
					//we should try stoping and or starting the Meter timer here

					///// Mouse Wheel Sensitivity /////////////
					file->Read(&trackProc->mouseSensitivity, sizeof(trackProc->mouseSensitivity));

					///// Midi Bleed //////////////
					file->Read(&trackProc->midiBleed, sizeof(trackProc->midiBleed));
				
					///// Midi Input Channels //////////////
					file->Read(&trackProc->midiChannel, sizeof(trackProc->midiChannel));

					///// Version Notes ///////////////////
					file->Read(&versionNotes, sizeof(versionNotes));
					if(fileVersion != version){				
						versionNotes = 1;
					}

					///// Log Status Dialog ///////////////////////
					file->Read(&statusDialog->logToFile, sizeof(statusDialog->logToFile));

					///// Retrigger  ////////////////////////////////////////////////////////
					file->Read(&trackProc->retriggerSafty, sizeof(trackProc->retriggerSafty));
					file->Read(&trackProc->retriggerThreshold, sizeof(trackProc->retriggerThreshold));

					file->Read(&trackProc->flamAdjustment, sizeof(trackProc->flamAdjustment));
					file->Read(&trackProc->rollAdjustment, sizeof(trackProc->rollAdjustment));
					
					///// Joystick Settings ///////////////////////////////////
					file->Read(&joystick->pollSpeed, sizeof(joystick->pollSpeed));
					int temp5 = 0;
					file->Read(&temp5, sizeof(temp5));
					joystick->SetMaxX(temp5);
					file->Read(&temp5, sizeof(temp5));
					joystick->SetMaxY(temp5);
					file->Read(&temp5, sizeof(temp5));
					joystick->SetMaxZ(temp5);
					file->Read(&temp5, sizeof(temp5));
					joystick->SetMaxR(temp5);
					file->Read(&temp5, sizeof(temp5));
					joystick->SetMaxU(temp5);
					file->Read(&temp5, sizeof(temp5));
					joystick->SetMaxV(temp5);

					if(fileVersion > wxT("0.430b")){
						for(int i=0; i<3; ++i){
							samples->sampleDir = ReadString(*file);
						}
					}

					/// Footer ////////////////////////////////////////////////
					wxString footer = ReadString(*file);

					if(header != footer){
						wxMessageBox(wxT("The main Data file is of incorrect size"),wxT(""), wxSTAY_ON_TOP);
					}
				}//is the file valid?

				//If the file is not valid, load default settings.	
				else{
					wxMessageBox(wxT("The main Data file is out of date.. Re-creating data file."), wxT(""), wxSTAY_ON_TOP);
					splashScreen = true;
					toolTips = true;
#ifndef VST
					par->maximized = false;
					par->frameSize = wxSize(800, 580);
#endif //VST
					Centre(wxBOTH);
#ifndef MAC
#ifndef VST
					par->framePosition = GetScreenPosition();
#endif //VST
					statusDialog->position = statusDialog->GetScreenPosition();
#endif
#ifdef MAC
					par->framePosition = GetPosition();
					statusDialog->position = statusDialog->GetPosition();
#endif
					statusDialog->size = statusDialog->GetSize();
					statusDialog->shown = statusDialog->IsShown();
					initPath = wxT("");
					initFilename = wxT("");
					trackProc->enableMeters = true;
					trackProc->preLoad = false;
					trackProc->mouseSensitivity = 10;
					trackProc->midiBleed = false;
					for(int i=0; i<17; ++i){trackProc->midiChannel[i] = true;}	
					versionNotes = true;
					statusDialog->logToFile = false;
					joystick->pollSpeed = 10;
					trackProc->retriggerSafty = 5;
					trackProc->retriggerThreshold = 150;
					trackProc->flamAdjustment = 5;
					trackProc->rollAdjustment = 15;
				}
			}

			//If the file is empty, load default settings
			else{
				wxMessageBox(wxT("The main Data file is blank.. Re-creating data file."),wxT(""), wxSTAY_ON_TOP);

				splashScreen = true;
				toolTips = true;
#ifndef VST
				par->maximized = false;
				par->frameSize = wxSize(800, 580);
#endif //VST
				Centre(wxBOTH);
#ifndef MAC
#ifndef VST
				par->framePosition = GetScreenPosition();
#endif //VST
				statusDialog->position = statusDialog->GetScreenPosition();
#endif

#ifdef MAC
				par->framePosition = GetPosition();
				statusDialog->position = statusDialog->GetPosition();
#endif
				
				statusDialog->size = statusDialog->GetSize();
				statusDialog->shown = statusDialog->IsShown();
				initPath = wxT("");
				initFilename = wxT("");
				trackProc->enableMeters = true;
				trackProc->preLoad = false;
				trackProc->mouseSensitivity = 10;
				trackProc->midiBleed = false;
				for(int i=0; i<17; ++i){trackProc->midiChannel[i] = true;}	
				versionNotes = true;
				statusDialog->logToFile = false;
				joystick->pollSpeed = 10;
				trackProc->retriggerSafty = 5;
				trackProc->retriggerThreshold = 150;
				trackProc->flamAdjustment = 5;
				trackProc->rollAdjustment = 15;
			}
			file->Close();
		}
		
		delete file;
	}

	//If the file does not exits, load default settings.
	else{
		splashScreen = true;
		toolTips = true;
#ifndef VST
		par->maximized = false;
		par->frameSize = wxSize(800, 580);
#endif //VST
		Centre(wxBOTH);
#ifndef MAC
#ifndef VST
		par->framePosition = GetScreenPosition();
#endif //VST
		statusDialog->position = statusDialog->GetScreenPosition();
#endif
	
#ifdef MAC
		par->framePosition = GetPosition();
		statusDialog->position = statusDialog->GetPosition();
#endif
		
		statusDialog->size = statusDialog->GetSize();
		statusDialog->shown = statusDialog->IsShown();
		initPath = wxT("");
		initFilename = wxT("");
		trackProc->enableMeters = true;
		trackProc->preLoad = false;
		trackProc->mouseSensitivity = 10;
		trackProc->midiBleed = false;
		for(int i=0; i<17; ++i){trackProc->midiChannel[i] = true;}	
		versionNotes = true;
		statusDialog->logToFile = false;
		joystick->pollSpeed = 10;
		trackProc->retriggerSafty = 5;
		trackProc->retriggerThreshold = 150;
		trackProc->flamAdjustment = 5;
		trackProc->rollAdjustment = 15;
	}

	//Set the Size and Position with the variables we have now. 
	//FRAME
#ifndef VST
	if(par->maximized){
		par->Move(par->framePosition);
		par->Maximize(true);
	}
	else{
		par->SetSize(par->frameSize);
		par->Move(par->framePosition);
	}
#endif //VST

	//StatusDialog
	if(statusDialog->shown){statusDialog->Show();}
	statusDialog->Move(statusDialog->position);
	statusDialog->SetSize(statusDialog->size);
	statusDialog->logToFileBox->SetValue(statusDialog->logToFile);

	//Tooltips
	if(toolTips){
		wxToolTip::Enable(true);
	    wxToolTip::SetDelay(500);
	}
	else{
		wxToolTip::Enable(false); //No effect :P
	}

	//VersionNotes
	if(versionNotes){
		if(notesDialog == NULL){
			notesDialog = new NotesDialog(this);
			notesDialog->Show();
			notesDialog->SetFocus();
		}
		else{
			notesDialog->Show();
			notesDialog->SetFocus();
		}
	}
}

///////////////////////////////////////////
bool MainPanel::SaveVarsToFile(bool saveAs)
{
	int response;

	wxStandardPaths stdPath; 
    wxString fileLocation = stdPath.GetExecutablePath(); 
#ifdef MAC
	fileLocation.Replace(wxT("/eTrigger.app/Contents/MacOS/eTrigger"), wxT(""), true);
	fileLocation += wxT("/Kits");
#endif //MAC
#ifdef WIN32
    fileLocation = wxFileName(fileLocation).GetPath() + wxT("/Kits");
#endif //WIN32

	if(fileDirectory == wxT(".\\Kits") || saveAs){
		wxFileDialog *fileDlg = new wxFileDialog(this, wxString(wxT("Save Tracks")), fileLocation, wxString(wxT("")), 
		                                    wxString(wxT("eTrigger Data (*.etd)|*.etd")), wxFD_SAVE | wxFD_OVERWRITE_PROMPT, wxDefaultPosition);

		response = fileDlg->ShowModal();
		if(response == wxID_OK){
			fileDirectory = fileDlg->GetDirectory();
			fileName = fileDlg->GetFilename();
		}

		delete fileDlg;
	}
	else{response = wxID_OK;}

	if(response == wxID_OK){
	
		//Set the Frame Title
		wxString title = wxString(wxT("eTrigger ")) += version;
		title += wxString(wxT("  -  "));
#ifdef WIN32
		//title += fileName.Remove(fileName.Length() - 4 ,fileName.Length()) ;
#endif WIN32
		//par->SetTitle(title);
		if(!fileName.Contains(wxT(".etd"))){
		   fileName += wxT(".etd");
		}

		wxString temp = fileDirectory;
#ifdef WIN32
		temp += wxString(wxT("\\"));
#endif //WIN32
#ifdef MAC
		temp += wxString(wxT("/"));
#endif //MAC
		temp += fileName;

		wxFile*	file = new wxFile(temp, wxFile::write);
		if(file->IsOpened()){

			/// HEADER ////////////////////////////////////////////////
			WriteString((wxString(wxT("ETR ")) += version), *file);

			/// TRACK INFO ////////////////////////////////////////////
			file->Write(&trackProc->tracks, sizeof(trackProc->tracks));

			for(int i=1; i < trackProc->tracks+1; ++i){
				file->Write(&trackProc->n[i].midiType, sizeof(trackProc->n[i].midiType));
				file->Write(&trackProc->n[i].drumType, sizeof(trackProc->n[i].drumType));
				for(int z=0; z<3; ++z){
					WriteString(trackProc->n[i].deviceName[z], *file);
					WriteString(trackProc->n[i].inputDetails[z], *file);
				}
	
				WriteString(trackProc->n[i].name, *file);
				WriteString(trackProc->n[i].image, *file);
				file->Write(&trackProc->n[i].inputCode, sizeof(trackProc->n[i].inputCode));
				file->Write(&trackProc->n[i].zones, sizeof(trackProc->n[i].zones));
				file->Write(&trackProc->n[i].preVolume, sizeof(trackProc->n[i].preVolume));
				file->Write(&trackProc->n[i].preGain, sizeof(trackProc->n[i].preGain));
				file->Write(&trackProc->n[i].masterGain, sizeof(trackProc->n[i].masterGain));
				file->Write(&trackProc->n[i].audioThreshold, sizeof(trackProc->n[i].audioThreshold));
				file->Write(&trackProc->n[i].retrigger, sizeof(trackProc->n[i].retrigger));
				file->Write(&trackProc->n[i].crosstalk, sizeof(trackProc->n[i].crosstalk));
				file->Write(&trackProc->n[i].highCompressor, sizeof(trackProc->n[i].highCompressor));
				file->Write(&trackProc->n[i].lowCompressor, sizeof(trackProc->n[i].lowCompressor));
				file->Write(&trackProc->n[i].lowPercent, sizeof(trackProc->n[i].lowPercent));
				file->Write(&trackProc->n[i].highPercent, sizeof(trackProc->n[i].highPercent));
				file->Write(&trackProc->n[i].highLimiter, sizeof(trackProc->n[i].highLimiter));
				file->Write(&trackProc->n[i].lowLimiter, sizeof(trackProc->n[i].lowLimiter));
				file->Write(&trackProc->n[i].ccReverse, sizeof(trackProc->n[i].ccReverse));
				file->Write(&trackProc->n[i].noteOff, sizeof(trackProc->n[i].noteOff));
				file->Write(&trackProc->n[i].masterVolume, sizeof(trackProc->n[i].masterVolume));
				file->Write(&trackProc->n[i].outputChannel, sizeof(trackProc->n[i].outputChannel));
				file->Write(&trackProc->n[i].outputNote, sizeof(trackProc->n[i].outputNote));
				file->Write(&trackProc->n[i].antiMachineGunTime, sizeof(trackProc->n[i].antiMachineGunTime));
				file->Write(&trackProc->n[i].basicOutput, sizeof(trackProc->n[i].basicOutput));
				file->Write(&trackProc->n[i].alternateOutput, sizeof(trackProc->n[i].alternateOutput));
				file->Write(&trackProc->n[i].midiCCControlledOutput, sizeof(trackProc->n[i].midiCCControlledOutput));
				file->Write(&trackProc->n[i].midiCCControlledInputNote, sizeof(trackProc->n[i].midiCCControlledInputNote));
				file->Write(&trackProc->n[i].midiCCControlledCheckBox, sizeof(trackProc->n[i].midiCCControlledCheckBox));
				file->Write(&trackProc->n[i].midiCCControlledNotes, sizeof(trackProc->n[i].midiCCControlledNotes));
				file->Write(&trackProc->n[i].midiCCControlledSliders, sizeof(trackProc->n[i].midiCCControlledSliders));
				file->Write(&trackProc->n[i].velocityControlledOutput, sizeof(trackProc->n[i].velocityControlledOutput));
				file->Write(&trackProc->n[i].velocityControlledCheckBox, sizeof(trackProc->n[i].velocityControlledCheckBox));
				file->Write(&trackProc->n[i].velocityControlledNotes, sizeof(trackProc->n[i].velocityControlledNotes));
				file->Write(&trackProc->n[i].velocityControlledSliders, sizeof(trackProc->n[i].velocityControlledSliders));
				file->Write(&trackProc->n[i].zoneControlledOutput, sizeof(trackProc->n[i].zoneControlledOutput));
				file->Write(&trackProc->n[i].zoneControlledCheckBox, sizeof(trackProc->n[i].zoneControlledCheckBox));
				file->Write(&trackProc->n[i].zoneControlledNotes, sizeof(trackProc->n[i].zoneControlledNotes));
				file->Write(&trackProc->n[i].zoneControlledSliders, sizeof(trackProc->n[i].zoneControlledSliders));
				file->Write(&trackProc->n[i].sequenceOutput, sizeof(trackProc->n[i].sequenceOutput));
				for(int z=0; z<3; ++z){
					WriteString(trackProc->n[i].sequenceFile[z], *file);
				}
				file->Write(&trackProc->n[i].sequenceOverlap, sizeof(trackProc->n[i].sequenceOverlap));
				file->Write(&trackProc->n[i].mouseOutput, sizeof(trackProc->n[i].mouseOutput));
				file->Write(&trackProc->n[i].mouseX, sizeof(trackProc->n[i].mouseX));
				file->Write(&trackProc->n[i].mouseY, sizeof(trackProc->n[i].mouseY));
				file->Write(&trackProc->n[i].alternateCheckBox, sizeof(trackProc->n[i].alternateCheckBox));
				file->Write(&trackProc->n[i].alternateNotes, sizeof(trackProc->n[i].alternateNotes));
				file->Write(&trackProc->n[i].alternateReset, sizeof(trackProc->n[i].alternateReset));
				file->Write(&trackProc->n[i].dynamics, sizeof(trackProc->n[i].dynamics));
				file->Write(&trackProc->n[i].pedalDownEvent, sizeof(trackProc->n[i].pedalDownEvent));
				file->Write(&trackProc->n[i].pedalDownThreshold, sizeof(trackProc->n[i].pedalDownThreshold));
				file->Write(&trackProc->n[i].pedalVolume, sizeof(trackProc->n[i].pedalVolume));
				file->Write(&trackProc->n[i].pedalNote, sizeof(trackProc->n[i].pedalNote));
				file->Write(&trackProc->n[i].pedalSpeedIntensity, sizeof(trackProc->n[i].pedalSpeedIntensity));
				file->Write(&trackProc->n[i].multiZoneWaitTime, sizeof(trackProc->n[i].multiZoneWaitTime));
				file->Write(&trackProc->n[i].priority, sizeof(trackProc->n[i].priority));
				file->Write(&trackProc->n[i].gravity, sizeof(trackProc->n[i].gravity));
				file->Write(&trackProc->n[i].velocityBalance, sizeof(trackProc->n[i].velocityBalance));
				file->Write(&trackProc->n[i].hasRim, sizeof(trackProc->n[i].hasRim));
				file->Write(&trackProc->n[i].enableCC, sizeof(trackProc->n[i].enableCC));
				file->Write(&trackProc->n[i].ccOutputChannel, sizeof(trackProc->n[i].ccOutputChannel));
				file->Write(&trackProc->n[i].ccOutputNote, sizeof(trackProc->n[i].ccOutputNote));
				file->Write(&trackProc->n[i].ccOutputLowCompressor, sizeof(trackProc->n[i].ccOutputLowCompressor));
				file->Write(&trackProc->n[i].ccOutputHighCompressor, sizeof(trackProc->n[i].ccOutputHighCompressor));
				file->Write(&trackProc->n[i].midiCCControlledVelocity, sizeof(trackProc->n[i].midiCCControlledVelocity));
				file->Write(&trackProc->n[i].midiCCControlledVelocityNote, sizeof(trackProc->n[i].midiCCControlledVelocityNote));
				
				int vectorSize = trackProc->n[i].pointsZone1.size();
				file->Write(&vectorSize, sizeof(vectorSize));
				for(int z=0; z<vectorSize; ++z){
					file->Write(&trackProc->n[i].pointsZone1[z], sizeof(trackProc->n[i].pointsZone1[z]));
				}

				vectorSize = trackProc->n[i].pointsZone2.size();
				file->Write(&vectorSize, sizeof(vectorSize));
				for(int z=0; z<vectorSize; ++z){
					file->Write(&trackProc->n[i].pointsZone2[z], sizeof(trackProc->n[i].pointsZone2[z]));
				}

				vectorSize = trackProc->n[i].pointsZone3.size();
				file->Write(&vectorSize, sizeof(vectorSize));
				for(int z=0; z<vectorSize; ++z){
					file->Write(&trackProc->n[i].pointsZone3[z], sizeof(trackProc->n[i].pointsZone3[z]));
				}

				for(int z=0; z<3; ++z){
					WriteString(trackProc->n[i].sampleFolder[z], *file);
				}
			}
			//////////////////////////////////////////////////////////////

			///// Footer /////////////
			WriteString((wxString(wxT("ETR ")) += version), *file);

			file->Close();
			delete file;
		}
		StoreSaveData();
		return true;
	}
	else {return false;} //we either canceled or were unsuccessful
}

/////////////////////////////////////////////////////////////////
void MainPanel::GetVarsFromFile(wxString path, wxString filename)
{
	int response;

	wxStandardPaths stdPath; 
    wxString fileLocation = stdPath.GetExecutablePath(); 
#ifdef MAC
	fileLocation.Replace(wxT("/eTrigger.app/Contents/MacOS/eTrigger"), wxT(""), true);
	fileLocation += wxT("/Kits");
#endif //MAC
#ifdef WIN32
    fileLocation = wxFileName(fileLocation).GetPath() + wxT("/Kits");
#endif //WIN32

	if(path == wxT("") && filename == wxT("")){
		wxFileDialog *fileDlg = new wxFileDialog(this, wxString(wxT("Load Tracks")), fileLocation, wxString(wxT("")), 
		                                    wxString(wxT("eTrigger Data (*.etd)|*.etd")), wxFD_OPEN | wxFD_FILE_MUST_EXIST, wxDefaultPosition);
		response = fileDlg->ShowModal();

		if(response == wxID_OK){
			fileDirectory = fileDlg->GetDirectory();
			fileName = fileDlg->GetFilename();
		}

		delete fileDlg;
	}
	else{
		fileDirectory = path;
		fileName = filename;
		response = wxID_OK;
	}

	if(response == wxID_OK){
	
		//Set the Frame Title
		wxString title = wxString(wxT("eTrigger ")) += version;
		title += wxString(wxT("  -  "));
#ifdef WIN32
		title += fileName.Remove(fileName.Length() - 4 ,fileName.Length()) ;
		//par->SetTitle(title);
		fileName += wxT(".etd");
#endif //WIN32

		//Delete all current tracks before loading
		trackProc->DeleteAllTracks();
		

		trackProc->focused = 0;
		
		wxString temp = fileDirectory;
#ifdef WIN32
		temp += wxString(wxT("\\"));
#endif //WIN32
#ifdef MAC
		temp += wxString(wxT("/"));
#endif //MAC
		temp += fileName;

		wxFile* file = new wxFile(temp, wxFile::read);
		if(file->IsOpened()){

			/// HEADER ////////////////////////////////////////////////
			wxString header = ReadString(*file);
			wxString fileVersion = header.Mid(4, 1000/*wxSTRING_MAXLEN*/);

			if(FileIsValid(header)){//Here we need to make sure the file is valid
					
				wxDialog *loadDLG = new wxDialog(this, -1, wxT("Loading Tracks . . ."), wxDefaultPosition, wxSize(125,25), wxCAPTION, wxT(""));
				loadDLG->CenterOnParent(wxBOTH);
				loadDLG->Show();

				/// TRACK INFO ////////////////////////////////////////////
				int tracks;
				//int type;
				file->Read(&tracks, sizeof(trackProc->tracks));
			
				for(int i=1; i < tracks+1; ++i){
					file->Read(&trackProc->n[i].midiType, sizeof(trackProc->n[i].midiType));

					if(trackProc->n[i].midiType == 1){ //Create Trigger Track	
						trackProc->AddTrigger();
					}
					if(trackProc->n[i].midiType == 2){ //Create Midi CC Track
						trackProc->AddMidiCC();
					}
					
					if(fileVersion > wxT("0.432")){
						file->Read(&trackProc->n[i].drumType, sizeof(trackProc->n[i].drumType));
					}
					
					for(int z=0; z<3; ++z){
						trackProc->n[i].deviceName[z] = ReadString(*file);
						trackProc->n[i].inputDetails[z] = ReadString(*file);
					}
	
					trackProc->n[i].name = ReadString(*file);
					trackProc->n[i].image = ReadString(*file);
					file->Read(&trackProc->n[i].inputCode, sizeof(trackProc->n[i].inputCode));
					file->Read(&trackProc->n[i].zones, sizeof(trackProc->n[i].zones));
					file->Read(&trackProc->n[i].preVolume, sizeof(trackProc->n[i].preVolume));
					file->Read(&trackProc->n[i].preGain, sizeof(trackProc->n[i].preGain));
					file->Read(&trackProc->n[i].masterGain, sizeof(trackProc->n[i].masterGain));
					file->Read(&trackProc->n[i].audioThreshold, sizeof(trackProc->n[i].audioThreshold));
					file->Read(&trackProc->n[i].retrigger, sizeof(trackProc->n[i].retrigger));
					if(fileVersion > wxT("0.520")){
						file->Read(&trackProc->n[i].crosstalk, sizeof(trackProc->n[i].crosstalk));
					}
					file->Read(&trackProc->n[i].highCompressor, sizeof(trackProc->n[i].highCompressor));
					file->Read(&trackProc->n[i].lowCompressor, sizeof(trackProc->n[i].lowCompressor));
					file->Read(&trackProc->n[i].highPercent, sizeof(trackProc->n[i].highPercent));
					file->Read(&trackProc->n[i].lowPercent, sizeof(trackProc->n[i].lowPercent));
					file->Read(&trackProc->n[i].highLimiter, sizeof(trackProc->n[i].highLimiter));
					file->Read(&trackProc->n[i].lowLimiter, sizeof(trackProc->n[i].lowLimiter));
					file->Read(&trackProc->n[i].ccReverse, sizeof(trackProc->n[i].ccReverse));
					
					file->Read(&trackProc->n[i].noteOff, sizeof(trackProc->n[i].noteOff));
					if(fileVersion < wxT("0.431")){
						for(int z=0; z<3; ++z){trackProc->n[i].noteOff[z] = true;}
					}
					file->Read(&trackProc->n[i].masterVolume, sizeof(trackProc->n[i].masterVolume));
					file->Read(&trackProc->n[i].outputChannel, sizeof(trackProc->n[i].outputChannel));
					file->Read(&trackProc->n[i].outputNote, sizeof(trackProc->n[i].outputNote));
					file->Read(&trackProc->n[i].antiMachineGunTime, sizeof(trackProc->n[i].antiMachineGunTime));
					file->Read(&trackProc->n[i].basicOutput, sizeof(trackProc->n[i].basicOutput));
					file->Read(&trackProc->n[i].alternateOutput, sizeof(trackProc->n[i].alternateOutput));
					file->Read(&trackProc->n[i].midiCCControlledOutput, sizeof(trackProc->n[i].midiCCControlledOutput));
					file->Read(&trackProc->n[i].midiCCControlledInputNote, sizeof(trackProc->n[i].midiCCControlledInputNote));
					file->Read(&trackProc->n[i].midiCCControlledCheckBox, sizeof(trackProc->n[i].midiCCControlledCheckBox));
					file->Read(&trackProc->n[i].midiCCControlledNotes, sizeof(trackProc->n[i].midiCCControlledNotes));
					file->Read(&trackProc->n[i].midiCCControlledSliders, sizeof(trackProc->n[i].midiCCControlledSliders));
					file->Read(&trackProc->n[i].velocityControlledOutput, sizeof(trackProc->n[i].velocityControlledOutput));
					file->Read(&trackProc->n[i].velocityControlledCheckBox, sizeof(trackProc->n[i].velocityControlledCheckBox));
					file->Read(&trackProc->n[i].velocityControlledNotes, sizeof(trackProc->n[i].velocityControlledNotes));
					file->Read(&trackProc->n[i].velocityControlledSliders, sizeof(trackProc->n[i].velocityControlledSliders));
					
					if(fileVersion > wxT("0.427b")){
					    file->Read(&trackProc->n[i].zoneControlledOutput, sizeof(trackProc->n[i].zoneControlledOutput));
					    file->Read(&trackProc->n[i].zoneControlledCheckBox, sizeof(trackProc->n[i].zoneControlledCheckBox));
					    file->Read(&trackProc->n[i].zoneControlledNotes, sizeof(trackProc->n[i].zoneControlledNotes));
					    file->Read(&trackProc->n[i].zoneControlledSliders, sizeof(trackProc->n[i].zoneControlledSliders));
					}

					if(fileVersion > wxT("0.435")){
						file->Read(&trackProc->n[i].sequenceOutput, sizeof(trackProc->n[i].sequenceOutput));
						for(int z=0; z<3; ++z){
							trackProc->n[i].sequenceFile[z] = ReadString(*file);
						}
					}
					if(fileVersion > wxT("0.509")){
						file->Read(&trackProc->n[i].sequenceOverlap, sizeof(trackProc->n[i].sequenceOverlap));
					}
					if(fileVersion > wxT("0.644")){
						file->Read(&trackProc->n[i].mouseOutput, sizeof(trackProc->n[i].mouseOutput));
						file->Read(&trackProc->n[i].mouseX, sizeof(trackProc->n[i].mouseX));
						file->Read(&trackProc->n[i].mouseY, sizeof(trackProc->n[i].mouseY));
					}
					file->Read(&trackProc->n[i].alternateCheckBox, sizeof(trackProc->n[i].alternateCheckBox));
					file->Read(&trackProc->n[i].alternateNotes, sizeof(trackProc->n[i].alternateNotes));
					file->Read(&trackProc->n[i].alternateReset, sizeof(trackProc->n[i].alternateReset));
					file->Read(&trackProc->n[i].dynamics, sizeof(trackProc->n[i].dynamics));
					file->Read(&trackProc->n[i].pedalDownEvent, sizeof(trackProc->n[i].pedalDownEvent));
					file->Read(&trackProc->n[i].pedalDownThreshold, sizeof(trackProc->n[i].pedalDownThreshold));
					file->Read(&trackProc->n[i].pedalVolume, sizeof(trackProc->n[i].pedalVolume));
					file->Read(&trackProc->n[i].pedalNote, sizeof(trackProc->n[i].pedalNote));
					file->Read(&trackProc->n[i].pedalSpeedIntensity, sizeof(trackProc->n[i].pedalSpeedIntensity));
					file->Read(&trackProc->n[i].multiZoneWaitTime, sizeof(trackProc->n[i].multiZoneWaitTime));
					file->Read(&trackProc->n[i].priority, sizeof(trackProc->n[i].priority));
					file->Read(&trackProc->n[i].gravity, sizeof(trackProc->n[i].gravity));

					if(fileVersion > wxT("0.430b")){
						file->Read(&trackProc->n[i].velocityBalance, sizeof(trackProc->n[i].velocityBalance));
					}
					
					file->Read(&trackProc->n[i].hasRim, sizeof(trackProc->n[i].hasRim));
					file->Read(&trackProc->n[i].enableCC, sizeof(trackProc->n[i].enableCC));
					file->Read(&trackProc->n[i].ccOutputChannel, sizeof(trackProc->n[i].ccOutputChannel));
					file->Read(&trackProc->n[i].ccOutputNote, sizeof(trackProc->n[i].ccOutputNote));
					
					if(fileVersion > wxT("0.429b")){
						file->Read(&trackProc->n[i].ccOutputLowCompressor, sizeof(trackProc->n[i].ccOutputLowCompressor));
						file->Read(&trackProc->n[i].ccOutputHighCompressor, sizeof(trackProc->n[i].ccOutputHighCompressor));
					}
					
					file->Read(&trackProc->n[i].midiCCControlledVelocity, sizeof(trackProc->n[i].midiCCControlledVelocity));
					file->Read(&trackProc->n[i].midiCCControlledVelocityNote, sizeof(trackProc->n[i].midiCCControlledVelocityNote));

					int vectorSize;
					file->Read(&vectorSize, sizeof(vectorSize));	
					for(int z=0; z<vectorSize; ++z){
						wxPoint temp;
						file->Read(&temp, sizeof(temp));
						trackProc->n[i].pointsZone1.push_back(temp);
					}
					
					file->Read(&vectorSize, sizeof(vectorSize));	
					for(int z=0; z<vectorSize; ++z){
						wxPoint temp;
						file->Read(&temp, sizeof(temp));
						trackProc->n[i].pointsZone2.push_back(temp);
					}

					file->Read(&vectorSize, sizeof(vectorSize));	
					for(int z=0; z<vectorSize; ++z){
						wxPoint temp;
						file->Read(&temp, sizeof(temp));
						trackProc->n[i].pointsZone3.push_back(temp);
					}

					if(fileVersion > wxT("0.431b")){  
						for(int z=0; z<3; ++z){
							trackProc->n[i].sampleFolder[z] = ReadString(*file);
						}
					}

					if(trackProc->n[i].trigger != NULL){
						trackProc->n[i].trigger->UpdateDialog();
					}
					if(trackProc->n[i].midicc != NULL){
						trackProc->n[i].midicc->UpdateDialog();
					}
				}

				delete loadDLG;
				///////////////////////////////////////////////////////////

				/// Footer ////////////////////////////////////////////////
				wxString footer = ReadString(*file);
				if(header != footer){
					wxMessageBox(wxT("The Data file is of incorrect size"),wxT(""), wxSTAY_ON_TOP);
				}

				file->Close();	
				delete file;
			}//endif(file is valid)

			else{
				wxMessageBox(wxT("This file is either not supported or corrupt"),wxT(""), wxSTAY_ON_TOP);

				//Reset Frame Title
				wxString title = wxString(wxT("eTrigger ")) += version;
				//par->SetTitle(title);

				//Reset path and filename
				fileDirectory = wxT(".\\Kits");
				fileName = wxT("");

				file->Close();	
				delete file;
			}
		}
		StoreSaveData();
	}

	//if we got here, we either canceled or we were unsuccessful
}

/////////////////////////////////////////
bool MainPanel::FileIsValid(wxString ver)
{
	// we just decide the oldest allowed file here. 
	if((ver <= (wxString(wxT("ETR ")) += version)) && (ver >= wxT("ETR 0.427b"))){return true;}

	/*  The old way.
	if(ver == (wxString(wxT("ETR ")) += version)){return true;}
	if(ver == wxT("ETR 0.427b")){return true;}
	if(ver == wxT("ETR 0.428b")){return true;}
	if(ver == wxT("ETR 0.429b")){return true;}
	if(ver == wxT("ETR 0.430b")){return true;}
	if(ver == wxT("ETR 0.431b")){return true;}
	if(ver == wxT("ETR 0.431")){return true;}
	if(ver == wxT("ETR 0.432")){return true;}
	if(ver == wxT("ETR 0.433")){return true;}
	if(ver == wxT("ETR 0.434")){return true;}
	if(ver == wxT("ETR 0.435")){return true;}
	if(ver == wxT("ETR 0.436")){return true;}
	if(ver == wxT("ETR 0.437")){return true;}
	if(ver == wxT("ETR 0.438")){return true;}
	if(ver == wxT("ETR 0.461")){return true;}
	*/

	return false;
}

////////////////////////////////////////////
void MainPanel::OnMouse(wxMouseEvent &event)
{
	if(event.GetWheelRotation() != 0)
	{
		//don't pass the event on
	}
	event.Skip();
}

///////////////////////////////
void MainPanel::StoreSaveData()
{		
	for(int i=0; i<100; ++i){
		saveData->n[i].midiType               = trackProc->n[i].midiType;
		saveData->n[i].drumType               = trackProc->n[i].drumType;
		saveData->n[i].pos                    = trackProc->n[i].pos;
		saveData->n[i].name                   = trackProc->n[i].name;
		saveData->n[i].image                  = trackProc->n[i].image;
		saveData->n[i].trackNum               = trackProc->n[i].trackNum;
		saveData->n[i].zones                  = trackProc->n[i].zones;
		saveData->n[i].masterGain             = trackProc->n[i].masterGain;
		saveData->n[i].masterVolume           = trackProc->n[i].masterVolume;
		saveData->n[i].ccReverse              = trackProc->n[i].ccReverse;
		saveData->n[i].pedalDownEvent         = trackProc->n[i].pedalDownEvent;
		saveData->n[i].pedalDownThreshold     = trackProc->n[i].pedalDownThreshold;
		saveData->n[i].pedalVolume            = trackProc->n[i].pedalVolume; 
		saveData->n[i].pedalNote              = trackProc->n[i].pedalNote; 
		saveData->n[i].pedalSpeedIntensity    = trackProc->n[i].pedalSpeedIntensity;
		saveData->n[i].pointsZone1            = trackProc->n[i].pointsZone1;
		saveData->n[i].pointsZone2            = trackProc->n[i].pointsZone2;
		saveData->n[i].pointsZone3            = trackProc->n[i].pointsZone3;
		saveData->n[i].multiZoneWaitTime      = trackProc->n[i].multiZoneWaitTime;
		saveData->n[i].velocityBalance        = trackProc->n[i].velocityBalance;
		saveData->n[i].hasRim                 = trackProc->n[i].hasRim;
		saveData->n[i].enableCC               = trackProc->n[i].enableCC;
		saveData->n[i].ccOutputChannel        = trackProc->n[i].ccOutputChannel;
		saveData->n[i].ccOutputNote           = trackProc->n[i].ccOutputNote;
		saveData->n[i].ccOutputHighCompressor = trackProc->n[i].ccOutputHighCompressor;
		saveData->n[i].ccOutputLowCompressor  = trackProc->n[i].ccOutputLowCompressor;

		for(int z=0; z<3; ++z){
			saveData->n[i].deviceName[z]                   = trackProc->n[i].deviceName[z];
			saveData->n[i].inputDetails[z]                 = trackProc->n[i].inputDetails[z];
			saveData->n[i].inputCode[z]                    = trackProc->n[i].inputCode[z];
			saveData->n[i].audioThreshold[z]               = trackProc->n[i].audioThreshold[z];
			saveData->n[i].preVolume[z]                    = trackProc->n[i].preVolume[z];
			saveData->n[i].preGain[z]                      = trackProc->n[i].preGain[z];
			saveData->n[i].retrigger[z]                    = trackProc->n[i].retrigger[z];
			saveData->n[i].crosstalk[z]                    = trackProc->n[i].crosstalk[z];
			saveData->n[i].outputChannel[z]                = trackProc->n[i].outputChannel[z];
			saveData->n[i].outputNote[z]                   = trackProc->n[i].outputNote[z];
			saveData->n[i].highCompressor[z]               = trackProc->n[i].highCompressor[z];
			saveData->n[i].lowCompressor[z]                = trackProc->n[i].lowCompressor[z];
			saveData->n[i].highLimiter[z]                  = trackProc->n[i].highLimiter[z];
			saveData->n[i].lowLimiter[z]                   = trackProc->n[i].lowLimiter[z];
			saveData->n[i].highPercent[z]                  = trackProc->n[i].highPercent[z];
			saveData->n[i].lowPercent[z]                   = trackProc->n[i].lowPercent[z];	
			saveData->n[i].noteOff[z]                      = trackProc->n[i].noteOff[z];
			saveData->n[i].antiMachineGunTime[z]           = trackProc->n[i].antiMachineGunTime[z];
			saveData->n[i].basicOutput[z]                  = trackProc->n[i].basicOutput[z];
			saveData->n[i].alternateOutput[z]              = trackProc->n[i].alternateOutput[z];
			saveData->n[i].midiCCControlledOutput[z]       = trackProc->n[i].midiCCControlledOutput[z];
			saveData->n[i].midiCCControlledInputNote[z]    = trackProc->n[i].midiCCControlledInputNote[z];
			saveData->n[i].velocityControlledOutput[z]     = trackProc->n[i].velocityControlledOutput[z];
			saveData->n[i].zoneControlledOutput            = trackProc->n[i].zoneControlledOutput;
			saveData->n[i].sequenceOutput[z]               = trackProc->n[i].sequenceOutput[z];
			saveData->n[i].mouseOutput[z]                  = trackProc->n[i].mouseOutput[z];
			saveData->n[i].mouseX[z]                       = trackProc->n[i].mouseX[z];
			saveData->n[i].mouseY[z]                       = trackProc->n[i].mouseY[z];
			saveData->n[i].sequenceFile[z]                 = trackProc->n[i].sequenceFile[z];
			saveData->n[i].sequenceOverlap[z]              = trackProc->n[i].sequenceOverlap[z];
			saveData->n[i].alternateReset[z]               = trackProc->n[i].alternateReset[z];
			saveData->n[i].priority[z]                     = trackProc->n[i].priority[z];
			saveData->n[i].gravity[z]                      = trackProc->n[i].gravity[z];
			saveData->n[i].midiCCControlledVelocity[z]     = trackProc->n[i].midiCCControlledVelocity[z];
			saveData->n[i].midiCCControlledVelocityNote[z] = trackProc->n[i].midiCCControlledVelocityNote[z];
			saveData->n[i].sampleFolder[z]                 = trackProc->n[i].sampleFolder[z];
				
			for(int n=0; n<100; ++n){
				saveData->n[i].alternateCheckBox[z][n]          = trackProc->n[i].alternateCheckBox[z][n];
				saveData->n[i].alternateNotes[z][n]             = trackProc->n[i].alternateNotes[z][n];
				saveData->n[i].midiCCControlledCheckBox[z][n]   = trackProc->n[i].midiCCControlledCheckBox[z][n];
				saveData->n[i].midiCCControlledNotes[z][n]      = trackProc->n[i].midiCCControlledNotes[z][n];
				saveData->n[i].midiCCControlledSliders[z][n]    = trackProc->n[i].midiCCControlledSliders[z][n];
				saveData->n[i].velocityControlledCheckBox[z][n] = trackProc->n[i].velocityControlledCheckBox[z][n];
				saveData->n[i].velocityControlledNotes[z][n]    = trackProc->n[i].velocityControlledNotes[z][n];
				saveData->n[i].velocityControlledSliders[z][n]  = trackProc->n[i].velocityControlledSliders[z][n];
				saveData->n[i].zoneControlledCheckBox[n]        = trackProc->n[i].zoneControlledCheckBox[n];
				saveData->n[i].zoneControlledNotes[n]           = trackProc->n[i].zoneControlledNotes[n];
				saveData->n[i].zoneControlledSliders[n]         = trackProc->n[i].zoneControlledSliders[n];
			}

			for(int p=0; p<127; ++p){
				saveData->n[i].dynamics[z][p]  = trackProc->n[i].dynamics[z][p];
			}
		}
	}					
}

//////////////////////////////
bool MainPanel::CheckForSave()
{
	for(int i=0; i<100; ++i){
		if(saveData->n[i].midiType               != trackProc->n[i].midiType){return true;}
		if(saveData->n[i].drumType               != trackProc->n[i].drumType){return true;}
		if(saveData->n[i].pos                    != trackProc->n[i].pos){return true;}
		if(saveData->n[i].name                   != trackProc->n[i].name){return true;}
		if(saveData->n[i].image                  != trackProc->n[i].image){return true;}
		if(saveData->n[i].trackNum               != trackProc->n[i].trackNum){return true;}
		if(saveData->n[i].zones                  != trackProc->n[i].zones){return true;}
		if(saveData->n[i].masterGain             != trackProc->n[i].masterGain){return true;}
		if(saveData->n[i].masterVolume           != trackProc->n[i].masterVolume){return true;}
		if(saveData->n[i].ccReverse              != trackProc->n[i].ccReverse){return true;}
		if(saveData->n[i].pedalDownEvent         != trackProc->n[i].pedalDownEvent){return true;}
		if(saveData->n[i].pedalDownThreshold     != trackProc->n[i].pedalDownThreshold){return true;}
		if(saveData->n[i].pedalVolume            != trackProc->n[i].pedalVolume){return true;}
		if(saveData->n[i].pedalNote              != trackProc->n[i].pedalNote){return true;} 
		if(saveData->n[i].pedalSpeedIntensity    != trackProc->n[i].pedalSpeedIntensity){return true;}
		if(saveData->n[i].pointsZone1            != trackProc->n[i].pointsZone1){return true;}
		if(saveData->n[i].pointsZone2            != trackProc->n[i].pointsZone2){return true;}
		if(saveData->n[i].pointsZone3            != trackProc->n[i].pointsZone3){return true;}
		if(saveData->n[i].multiZoneWaitTime      != trackProc->n[i].multiZoneWaitTime){return true;}
		if(saveData->n[i].velocityBalance        != trackProc->n[i].velocityBalance){return true;}
		if(saveData->n[i].hasRim                 != trackProc->n[i].hasRim){return true;}
		if(saveData->n[i].enableCC               != trackProc->n[i].enableCC){return true;}
		if(saveData->n[i].ccOutputChannel        != trackProc->n[i].ccOutputChannel){return true;}
		if(saveData->n[i].ccOutputNote           != trackProc->n[i].ccOutputNote){return true;}
		if(saveData->n[i].ccOutputHighCompressor != trackProc->n[i].ccOutputHighCompressor){return true;}
		if(saveData->n[i].ccOutputLowCompressor  != trackProc->n[i].ccOutputLowCompressor){return true;}

		for(int z=0; z<3; ++z){
			if(saveData->n[i].deviceName[z]					  != trackProc->n[i].deviceName[z]){return true;}
			if(saveData->n[i].inputDetails[z]				  != trackProc->n[i].inputDetails[z]){return true;}
			if(saveData->n[i].inputCode[z]					  != trackProc->n[i].inputCode[z]){return true;}
			if(saveData->n[i].audioThreshold[z]				  != trackProc->n[i].audioThreshold[z]){return true;}
			if(saveData->n[i].preVolume[z]					  != trackProc->n[i].preVolume[z]){return true;}
			if(saveData->n[i].preGain[z]					  != trackProc->n[i].preGain[z]){return true;}
			if(saveData->n[i].retrigger[z]					  != trackProc->n[i].retrigger[z]){return true;}
			if(saveData->n[i].crosstalk[z]					  != trackProc->n[i].crosstalk[z]){return true;}
			if(saveData->n[i].outputChannel[z]				  != trackProc->n[i].outputChannel[z]){return true;}
			if(saveData->n[i].outputNote[z]					  != trackProc->n[i].outputNote[z]){return true;}
			if(saveData->n[i].highCompressor[z]				  != trackProc->n[i].highCompressor[z]){return true;}
			if(saveData->n[i].lowCompressor[z]				  != trackProc->n[i].lowCompressor[z]){return true;}
			if(saveData->n[i].highLimiter[z]				  != trackProc->n[i].highLimiter[z]){return true;}
			if(saveData->n[i].lowLimiter[z]					  != trackProc->n[i].lowLimiter[z]){return true;}	
			if(saveData->n[i].highPercent[z]				  != trackProc->n[i].highPercent[z]){return true;}
			if(saveData->n[i].lowPercent[z]					  != trackProc->n[i].lowPercent[z]){return true;}
			if(saveData->n[i].noteOff[z]					  != trackProc->n[i].noteOff[z]){return true;}
			if(saveData->n[i].antiMachineGunTime[z]			  != trackProc->n[i].antiMachineGunTime[z]){return true;}
			if(saveData->n[i].basicOutput[z]			      != trackProc->n[i].basicOutput[z]){return true;}
			if(saveData->n[i].alternateOutput[z]			  != trackProc->n[i].alternateOutput[z]){return true;}
			if(saveData->n[i].midiCCControlledOutput[z]		  != trackProc->n[i].midiCCControlledOutput[z]){return true;}
			if(saveData->n[i].midiCCControlledInputNote[z]    != trackProc->n[i].midiCCControlledInputNote[z]){return true;}
			if(saveData->n[i].velocityControlledOutput[z]	  != trackProc->n[i].velocityControlledOutput[z]){return true;}
			if(saveData->n[i].zoneControlledOutput	          != trackProc->n[i].zoneControlledOutput){return true;}
			if(saveData->n[i].sequenceOutput[z]  	          != trackProc->n[i].sequenceOutput[z]){return true;}
			if(saveData->n[i].sequenceFile[z]  	              != trackProc->n[i].sequenceFile[z]){return true;}
			if(saveData->n[i].sequenceOverlap[z]  	          != trackProc->n[i].sequenceOverlap[z]){return true;}
			if(saveData->n[i].mouseOutput[z]  	              != trackProc->n[i].mouseOutput[z]){return true;}
			if(saveData->n[i].mouseX[z]  	                  != trackProc->n[i].mouseX[z]){return true;}
			if(saveData->n[i].mouseY[z]  	                  != trackProc->n[i].mouseY[z]){return true;}
			if(saveData->n[i].alternateReset[z]				  != trackProc->n[i].alternateReset[z]){return true;}
			if(saveData->n[i].priority[z]                     != trackProc->n[i].priority[z]){return true;}
			if(saveData->n[i].gravity[z]                      != trackProc->n[i].gravity[z]){return true;}
			if(saveData->n[i].midiCCControlledVelocity[z]     != trackProc->n[i].midiCCControlledVelocity[z]){return true;}
			if(saveData->n[i].midiCCControlledVelocityNote[z] != trackProc->n[i].midiCCControlledVelocityNote[z]){return true;}
			if(saveData->n[i].sampleFolder[z]                 != trackProc->n[i].sampleFolder[z]){return true;}

			for(int n=0; n<100; ++n){
				if(saveData->n[i].alternateCheckBox[z][n]          != trackProc->n[i].alternateCheckBox[z][n]){return true;}
				if(saveData->n[i].alternateNotes[z][n]             != trackProc->n[i].alternateNotes[z][n]){return true;}
				if(saveData->n[i].midiCCControlledCheckBox[z][n]   != trackProc->n[i].midiCCControlledCheckBox[z][n]){return true;}
				if(saveData->n[i].midiCCControlledNotes[z][n]      != trackProc->n[i].midiCCControlledNotes[z][n]){return true;}
				if(saveData->n[i].midiCCControlledSliders[z][n]    != trackProc->n[i].midiCCControlledSliders[z][n]){return true;}
				if(saveData->n[i].velocityControlledCheckBox[z][n] != trackProc->n[i].velocityControlledCheckBox[z][n]){return true;}
				if(saveData->n[i].velocityControlledNotes[z][n]    != trackProc->n[i].velocityControlledNotes[z][n]){return true;}
				if(saveData->n[i].velocityControlledSliders[z][n]  != trackProc->n[i].velocityControlledSliders[z][n]){return true;}
				if(saveData->n[i].zoneControlledCheckBox[n]        != trackProc->n[i].zoneControlledCheckBox[n]){return true;}
				if(saveData->n[i].zoneControlledNotes[n]           != trackProc->n[i].zoneControlledNotes[n]){return true;}
				if(saveData->n[i].zoneControlledSliders[n]         != trackProc->n[i].zoneControlledSliders[n]){return true;}
			}

			for(int p=0; p<127; ++p){
				if(saveData->n[i].dynamics[z][p] != trackProc->n[i].dynamics[z][p]){return true;}
			}
		}
	}
	return false;
}

//The custome Scrollbar is not ready for MAC yet
//////////////////////////////////////////
void MainPanel::OnSize(wxSizeEvent &event)
{
	#ifdef WIN32
	UpdateScroll(); //FIXME - this seems to be the only place this function works.
	#endif
	#ifndef VST
	par->frameSize = par->GetSize();
	#endif //VST
	event.Skip();
}

//////////////////////////////////////////////////
#ifndef MAC
//The custom Scrollbar is not ready for MAC yet
void MainPanel::OnGScrollBar(GScrollBarEvent &event) 
{ 
	//unsigned position = event.GetValue();
	//you can peek at the position value of the scrollbar here
	//But the GScrollBar class will scroll the window on it's own.

	//wxWindow::ScrollWindow does not change the windows position variables..  
	//i.e. trackPanel->GetPosition() will always return (0,0).
	//So we have to store the position when a scroll event happens.

	trackPanel->position = scrollbar->scrollwinposition;
	
	event.Skip(true);	
}
#endif //!MAC

//////////////////////////////
void MainPanel::UpdateScroll()
{
	if(trackProc != NULL){
		scrollbar->UpdateScrollBar(par->GetClientSize().x, (trackProc->tracks * 82));	
		trackPanel->position = scrollbar->scrollwinposition;
	}	
}

