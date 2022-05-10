//// Tracks.cpp /////////////////////////////////////////////////////////////////////////
//
// This is the class that hold all of the information about the tracks.
// Track type, number of zones, position, midi note, volume, etc.
//
// Tracks hold their own coordinates. 
// However, if the window is scrolled, we have to Add/Remove the tracks relative to the parent window position.
// Since the wxWindow::ScrollWindow function does not update the windows position variables, we store it in the class and use that.
// Example: wxPoint(n[tracks].pos.x + trackPanel->position, n[tracks].pos.y)  //create at track coords but relative to the parent position variable.
//
//////////////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "Tracks.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////
BEGIN_EVENT_TABLE(TrackPanel, wxPanel)
	EVT_PAINT(TrackPanel::OnPaint) 
	EVT_MOUSE_EVENTS(TrackPanel::OnMouse)
	EVT_MENU(100, TrackPanel::OnMenuAddTrigger)
	EVT_MENU(101, TrackPanel::OnMenuAddMidiCC)
	EVT_MENU(102, TrackPanel::OnMenuDeleteTrack)
END_EVENT_TABLE() 

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TrackPanel::TrackPanel(MainPanel* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
             :wxPanel(parent, id, pos, size, style, name)
{
	InitVariables();

	mainPanel = parent;
	logo = new wxImage(logo_xpm);
	trackMenu = new wxMenu;
	trackMenu->Append(100, wxT("Add Trigger") );
	trackMenu->Append(101, wxT("Add Midi CC") );
	trackMenu->InsertSeparator(2);
	trackMenu->Append(102, wxT("Delete Selected Track") );
	trackMenu->Enable(102, false);  //start it off disabled

	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	SetBackgroundColour(wxColour(99,99,99));
}

/////////////////////////
TrackPanel::~TrackPanel()
{
	delete trackMenu;
	delete logo;
}

////////////////////////////////
void TrackPanel::InitVariables()
{
	mainPanel = NULL;
	trackMenu = NULL;
	position = NULL;
	logo = NULL;
}

//////////////////////////////////////////////
void TrackPanel::OnMouse(wxMouseEvent &event)
{
	if(event.LeftDown()){
		mainPanel->SetFocus();
	}
	if(event.RightUp()){
		PopupMenu(trackMenu, wxDefaultPosition);
	}
	if(event.GetWheelRotation() != 0)
	{
		//don't pass the event to parent
	}
}

//////////////////////////////////////////////
void TrackPanel::OnPaint(wxPaintEvent& event)
{ 
#ifndef MAC
	SetDoubleBuffered(false);
#endif //!MAC
	wxBufferedPaintDC dc(this); 
	dc.SetBackground(wxColour(99, 99, 99)); 
	dc.Clear(); 
	dc.DrawBitmap(*logo, 20, 20, false); 
}




//////////////////////
TrackData::TrackData()
{
	InitVariables();
}

///////////////////////////////
void TrackData::InitVariables()
{
	midiType = NULL;
	drumType = 0;
	pos = wxPoint(0,0);
	trigger = NULL;
	midicc = NULL;
	name = wxT("");
	image = wxT("");
	trackNum = NULL;
	zones = 1;
	for(register int z=0; z<3; ++z){deviceName[z] = wxT("no device selected");}
	for(register int z=0; z<3; ++z){inputDetails[z] = wxT("");}
	for(register int z=0; z<3; ++z){inputCode[z] = NULL;}
	for(register int z=0; z<3; ++z){audioThreshold[z] = NULL;}
	multiZoneWaitTime = 10;
	for(register int z=0; z<3; ++z){preVolume[z] = NULL;}
	for(register int z=0; z<3; ++z){preGain[z] = 500;}
	for(register int z=0; z<3; ++z){retrigger[z] = NULL;}
	for(register int z=0; z<3; ++z){crosstalk[z] = NULL;}
	for(register int z=0; z<3; ++z){highCompressor[z] = 127;}
	for(register int z=0; z<3; ++z){highPercent[z] = 100;}
	for(register int z=0; z<3; ++z){lowCompressor[z] = 0;}
	for(register int z=0; z<3; ++z){lowPercent[z] = 100;}
	for(register int z=0; z<3; ++z){highLimiter[z] = 127;}
	for(register int z=0; z<3; ++z){lowLimiter[z] = 0;}
	for(register int z=0; z<3; ++z){lastHitTime[z] = NULL;}
	for(register int z=0; z<3; ++z){lastOutputVelocity[z] = NULL;}
	for(register int z=0; z<3; ++z){lastRetriggerVelocity[z] = NULL;}
	bool ccReverse = false;
	for(register int z=0; z<3; ++z){noteOff[z] = true;}
	for(register int z=0; z<3; ++z){lastWasNoteOff[z] = NULL;}
	pointsZone1.clear();
	pointsZone2.clear();
	pointsZone3.clear();
	for(register int z=0; z<3; ++z){
		for(register int d=0; d<127; ++d){dynamics[z][d] = NULL;}
	}
	for(register int z=0; z<3; ++z){
		for(register int d=0; d<127; ++d){antiMachineGun[z][d] = NULL;}
	}
	for(register int z=0; z<3; ++z){antiMachineGunTime[z] = NULL;}
	for(register int z=0; z<3; ++z){midiCCControlledVelocity[z] = NULL;}
	for(register int z=0; z<3; ++z){midiCCControlledVelocityNote[z] = NULL;}
	for(register int z=0; z<3; ++z){basicOutput[z] = NULL;}		
	for(register int z=0; z<3; ++z){alternateOutput[z] = NULL;}
	for(register int z=0; z<3; ++z){alternateRandom[z] = NULL;}
	for(register int z=0; z<3; ++z){
		for(register int d=0; d<100; ++d){alternateCheckBox[z][d] = NULL;}
	}
	for(register int z=0; z<3; ++z){
		for(register int d=0; d<100; ++d){alternateNotes[z][d] = NULL;}
	}
	for(register int z=0; z<3; ++z){alternateReset[z] = 1000;}
	for(register int z=0; z<3; ++z){alternateMarker[z] = NULL;}
	for(register int z=0; z<3; ++z){alternateOffMarker[z] = NULL;}
	for(register int z=0; z<3; ++z){lastAlternateHitTime[z] = NULL;}
	for(register int z=0; z<3; ++z){alternateLastOn[z] = NULL;}
	for(register int z=0; z<3; ++z){midiCCControlledOutput[z] = NULL;}
	for(register int z=0; z<3; ++z){midiCCControlledInputNote[z] = NULL;}
	for(register int z=0; z<3; ++z){
		for(register int d=0; d<100; ++d){midiCCControlledCheckBox[z][d] = NULL;}
	}
	for(register int z=0; z<3; ++z){
		for(register int d=0; d<100; ++d){midiCCControlledNotes[z][d] = NULL;}
	}
	for(register int z=0; z<3; ++z){		
		for(register int d=0; d<100; ++d){midiCCControlledSliders[z][d] = NULL;}
	}
	for(register int z=0; z<3; ++z){midiCCControlledLastOn[z] = NULL;}
	for(register int z=0; z<3; ++z){velocityControlledOutput[z] = NULL;}
	for(register int z=0; z<3; ++z){
		for(register int d=0; d<100; ++d){velocityControlledCheckBox[z][d] = NULL;}
	}
	for(register int z=0; z<3; ++z){
		for(register int d=0; d<100; ++d){velocityControlledNotes[z][d] = NULL;}
	}
	for(register int z=0; z<3; ++z){
		for(register int d=0; d<100; ++d){velocityControlledSliders[z][d] = NULL;}
	}
	for(register int z=0; z<3; ++z){velocityControlledLastOn[z] = NULL;}
	zoneControlledOutput = NULL;
	for(register int z=0; z<100; ++z){zoneControlledCheckBox[z] = NULL;}
	for(register int z=0; z<100; ++z){zoneControlledNotes[z] = NULL;}
	for(register int z=0; z<100; ++z){zoneControlledSliders[z] = NULL;}
	zoneControlledLastOn = NULL;
	for(register int z=0; z<3; ++z){sequenceOutput[z] = NULL;}
	for(register int z=0; z<3; ++z){sequenceFile[z] = wxT("");}
	for(register int z=0; z<3; ++z){sequenceOverlap[z] = NULL;}
	pedalDownEvent = NULL;
	pedalDownThreshold = NULL;
	storedHighVelocity = NULL;
	highTime = NULL;
	pedalVolume = 127;
	pedalNote = 1;
	pedalSpeedIntensity = 100;
	pedalDownFlag = NULL;
	masterGain = 100;
	masterVolume = 127;
	for(register int z=0; z<3; ++z){outputChannel[z] = 10;} 
	for(register int z=0; z<3; ++z){outputNote[z] = NULL;}
	for(register int z=0; z<3; ++z){outputVelocity[z] = NULL;} 
	for(register int z=0; z<3; ++z){storedVelocity[z] = NULL;} 
	waitForPiezo = NULL; 
	firstPiezoHitTime = NULL;
	for(register int z=0; z<3; ++z){priority[z] = NULL;}
	for(register int z=0; z<3; ++z){gravity[z] = NULL;}
	velocityBalance = NULL;
	for(register int z=0; z<127; ++z){
		for(register int d=0; d<1000; ++d){velToPosAvg[z][d] = NULL;}
	}
	for(register int z=0; z<127; ++z){
		for(register int d=0; d<1000; ++d){posToVelAvg[z][d] = NULL;}
	}
	hasRim = true;
	enableCC = NULL; 
	ccOutputChannel = 10;
	ccOutputNote = 1;
	ccOutputHighCompressor = 127;
	ccOutputLowCompressor = 0;
	for(register int z=0; z<3; ++z){sampleFolder[z] = wxT("");}
}





/////////////////////////////////////////
TrackProc::TrackProc(TrackPanel *parent)
{
	InitVariables();

	trackPanel = parent; //hold a pointer to the parent that we can use
	trackMenu = new wxMenu; //Create the Menu system for right clicking on tracks
	trackMenu->Append( 103, wxT("Add Trigger") );
	trackMenu->Append( 104, wxT("Add MidiCC") );
	trackMenu->InsertSeparator(2);
	trackMenu->Append( 102, wxT("Delete Track") );
}

///////////////////////
TrackProc::~TrackProc()
{
	if(trackMenu != NULL){delete trackMenu;}
}

///////////////////////////////
void TrackProc::InitVariables()
{
	tracks = NULL;
	focused = NULL;
	enableMeters = NULL;
	preLoad = NULL;
	mouseSensitivity = NULL;
	midiBleed = NULL;
	for(int i=0; i<17; ++i){midiChannel[i] = NULL;}	
	retriggerSafty = NULL;
	retriggerThreshold = NULL;
	flamAdjustment = NULL;
	rollAdjustment = NULL;
	audio = NULL;
	midi = NULL;
	trackMenu = NULL;
	trackPanel = NULL;
}

////////////////////////////
void TrackProc::AddTrigger()
{
	//Add a trigger track to the window
	if(tracks < 100){
		tracks++;
	
		if(tracks <= 1){ n[tracks].pos = wxPoint(0, 0);	}
		else{ n[tracks].pos = wxPoint(n[tracks-1].pos.x + 82, 0); }
	
		//assign default values and create track
		n[tracks].name = wxT("Trigger");

		wxStandardPaths stdPath;
		wxString fileLocation = stdPath.GetExecutablePath();
#ifdef MAC
		fileLocation.Replace(wxT("/eTrigger.app/Contents/MacOS/eTrigger"), wxT(""), true);
		fileLocation += wxT("/Images/Snare.bmp");
#endif //MAC

#ifdef WIN32
		fileLocation = wxFileName(fileLocation).GetPath() + wxT("/Images/Snare.bmp"); 
#endif //WIN32

		n[tracks].image = fileLocation;

		for(register int z=0; z<3; ++z){n[tracks].outputNote[z] = 35 + tracks;}

		for(register int z=0; z<3; ++z){n[tracks].basicOutput[z] = true;}

		for(register int i=0; i<3; ++i){for(register int z=0; z<2; ++z){n[tracks].alternateCheckBox[i][z] = 1;}}
		for(register int i=0; i<3; ++i){for(register int z=0; z<2; ++z){n[tracks].midiCCControlledCheckBox[i][z] = 1;}}
		for(register int i=0; i<3; ++i){for(register int z=0; z<2; ++z){n[tracks].velocityControlledCheckBox[i][z] = 1;}}
		for(register int i=0; i<3; ++i){n[tracks].midiCCControlledSliders[i][0] = 63;}
		for(register int i=0; i<3; ++i){n[tracks].velocityControlledSliders[i][0] = 63;}
		for(register int i=0; i<3; ++i){for(register int z=0; z<127; ++z){n[tracks].dynamics[i][z] = z+1;}}
		for(register int z=0; z<2; ++z){n[tracks].zoneControlledCheckBox[z] = 1;}
		n[tracks].zoneControlledSliders[0] = 63;
		n[tracks].pointsZone1.push_back( wxPoint(0, 200) );
		n[tracks].pointsZone1.push_back( wxPoint(250, 0) );
		n[tracks].pointsZone2.push_back( wxPoint(0, 200) );
		n[tracks].pointsZone2.push_back( wxPoint(250, 0) );
		n[tracks].pointsZone3.push_back( wxPoint(0, 200) );
		n[tracks].pointsZone3.push_back( wxPoint(250, 0) );
			
		n[tracks].midiType = 1;
		n[tracks].trackNum = tracks;
		n[tracks].trigger = new Trigger(trackPanel, this, wxPoint(n[tracks].pos.x + trackPanel->position, n[tracks].pos.y), tracks);
	}

	else{
		wxMessageBox(wxT("You have reached the maximum allowed tracks.  100"));
	}

	GMeterEvent event(wxEVT_COMMAND_GMETER, trackPanel->GetId()); //ID of where we come from?
	event.SetValue(100);
	wxPostEvent(n[tracks].trigger->meter->GetEventHandler(), event); //event handle of the gui object
		

	trackPanel->mainPanel->Refresh();
	trackPanel->mainPanel->UpdateScroll();
}

///////////////////////////
void TrackProc::AddMidiCC()
{
	//Add a Midi CC Track to the window
	if(tracks < 100){
		tracks++;
	
		if(tracks <= 1){ n[tracks].pos = wxPoint(0, 0);	}
		else{ n[tracks].pos = wxPoint(n[tracks-1].pos.x + 82, 0); }

		n[tracks].name = wxT("MidiCC");

		wxStandardPaths stdPath;
		wxString fileLocation = stdPath.GetExecutablePath();
#ifdef MAC
		fileLocation.Replace(wxT("/eTrigger.app/Contents/MacOS/eTrigger"), wxT(""), true);
		fileLocation += wxT("/Images/HiHat.bmp");
#endif //MAC
		
#ifdef WIN32
		fileLocation = wxFileName(fileLocation).GetPath() + wxT("/Images/HiHat.bmp"); 
#endif //WIN32
		
		n[tracks].image = fileLocation;

		n[tracks].midiType = 2;
		n[tracks].trackNum = tracks;
		n[tracks].midicc = new MidiCC(trackPanel, this, wxPoint(n[tracks].pos.x + trackPanel->position, n[tracks].pos.y), tracks);
		trackPanel->mainPanel->UpdateScroll();
	}

	else{
		wxMessageBox(wxT("You have reached the maximum allowed tracks.  100"));
	}

	GMeterEvent event(wxEVT_COMMAND_GMETER, trackPanel->GetId()); //ID of where we come from?
	event.SetValue(1);
	wxPostEvent(n[tracks].midicc->meter->GetEventHandler(), event); //event handle of the gui object
}


////////////////////////////////////////////////
void TrackProc::DeleteTrack(int i, bool confirm)
{	
	if(confirm){
		wxMessageDialog msgdlg(NULL, wxT("Are you sure you want to delete this track ?"), wxT("Delete?"), wxYES_NO | wxSTAY_ON_TOP, wxDefaultPosition);
		int response = msgdlg.ShowModal();
		if(response == wxID_NO){return;}
	}

	//Delete the track by it's number and move the rest of the tracks to line them back up
	int temp = i;
	if(i>0 && i<tracks+1){

		if(n[i].trigger != NULL){ n[i].trigger->Destroy();  n[i].trigger = NULL;}
		if(n[i].midicc != NULL){ n[i].midicc->Destroy(); n[i].midicc = NULL; }

		for(; i<tracks; ++i){
			n[i] = n[i+1];			
			n[i].pos.x = n[i].pos.x - 82;
			if(n[i].trigger != NULL){ n[i].trackNum--; n[i].trigger->SetTrackNum(n[i].trigger->trackNum - 1);
									  n[i].trigger->Move(wxPoint(n[i].pos.x + trackPanel->position, n[i].pos.y), 0);		
				if(n[i].trigger->focused){focused = n[i].trigger->trackNum;} //update focus marker
			}
			if(n[i].midicc != NULL){ n[i].trackNum--; n[i].midicc->SetTrackNum(n[i].midicc->trackNum - 1);
									 n[i].midicc->Move(wxPoint(n[i].pos.x + trackPanel->position, n[i].pos.y), 0);
				if(n[i].midicc->focused){focused = n[i].midicc->trackNum;} //update focus marker
			} 
		}

		n[tracks].InitVariables(); //Reset all the variables for this track		
		--tracks;
		trackPanel->mainPanel->UpdateScroll();
	}

	else{
		wxMessageBox(wxT("Error: attempting to delete a track that does not exist"));
	}
} 

/////////////////////////////////
void TrackProc::DeleteAllTracks()
{
	while(tracks > 0){
		DeleteTrack(tracks, false);
	}
}

//////////////////////////////////////////
void TrackProc::MoveTrack(int num, int to)
{
	//FIXME: we get alot of crashes here.

	//only the tracks between num and to are effected
	//this will require a temporary place to store the track being moved while the others are shifted over.
	
	//error protection
	/*
	if(to < 0){return;}
	if(num < 0){return;}

	if(num < to){ to--; }

	TrackData temp;
	temp = n[num];
	temp.pos.x = n[to].pos.x;
	if(temp.trigger != NULL){ temp.trackNum = n[to].trackNum; temp.trigger->SetTrackNum(0);}
	if(temp.midicc != NULL){ temp.trackNum = n[to].trackNum; temp.midicc->SetTrackNum(0);}

	//put num in temp, shift num through to left one. Put temp in to.
	if(num < to){
		for(int i=num; i<to; ++i){
			n[i] = n[i+1];
			n[i].pos.x = n[i].pos.x - 82;
			if(n[i].trigger != NULL){ 
				n[i].trackNum--; 
                n[i].trigger->SetTrackNum(n[i].trigger->TrackNum - 1);
			    n[i].trigger->Move(wxPoint(n[i].pos.x + trackPanel->position, n[i].pos.y), 0);	
				if(n[i].trigger->focused){focused = n[i].trigger->TrackNum;} //update focus marker
			}
			if(n[i].midicc != NULL){ 
				n[i].trackNum--; 
				n[i].midicc->SetTrackNum(n[i].midicc->TrackNum - 1);
			    n[i].midicc->Move(wxPoint(n[i].pos.x + trackPanel->position, n[i].pos.y), 0);  //FIXME - we get lots of crashes here.
				if(n[i].midicc->focused){focused = n[i].midicc->TrackNum;} //update focus marker
			} 
		}
	}

	//put num in temp, shift num through to right one. Put temp in to.
	if(num > to){
		for(int i=num; i>to; i--){
			n[i] = n[i-1];
			n[i].pos.x = n[i].pos.x + 82;
			if(n[i].trigger != NULL){ 
				n[i].trackNum++; 
				n[i].trigger->SetTrackNum(n[i].trigger->TrackNum + 1); 
				n[i].trigger->Move(wxPoint(n[i].pos.x + trackPanel->position, n[i].pos.y), 0);	
				if(n[i].trigger->focused){focused = n[i].trigger->TrackNum;} //update focus marker
			}
			if(n[i].midicc != NULL){ 
				n[i].trackNum++; 
				n[i].midicc->SetTrackNum(n[i].midicc->TrackNum + 1); 
			    n[i].midicc->Move(wxPoint(n[i].pos.x + trackPanel->position, n[i].pos.y), 0);
				if(n[i].midicc->focused){focused = n[i].midicc->TrackNum;} //update focus marker
			} 
		}
	}
	
	if(temp.trigger != NULL){ temp.trigger->SetTrackNum(n[to].trackNum);}
	if(temp.midicc != NULL){ temp.midicc->SetTrackNum(n[to].trackNum);}
	n[to] = temp;
	
	if(n[to].trigger != NULL){
		n[to].trigger->Move(wxPoint(n[to].pos.x + trackPanel->position, n[to].pos.y), 0);
		n[to].trigger->Refresh();
	}
	if(n[to].midicc != NULL){
		n[to].midicc->Move(wxPoint(n[to].pos.x + trackPanel->position, n[to].pos.y), 0);
		n[to].midicc->Refresh();
	}

	trackPanel->Refresh();
	*/
}

////////////////////////////////////////////////
int TrackProc::DetectLanding(int track, int pos)
{
	//Here we detect where to land a track that is being moved
	//We Take the x position of the transparent track and create a marker window to show where ti will land.
    //If there is only one track, don't draw a marker
	
	int dropSpot;
	if(tracks <= 1){return 0;}

	if(pos < n[1].pos.x){
        //draw first spot marker here.
		dropSpot = 1;
	}

	for(int i=1; i<tracks+1; ++i){
		if(pos > n[i].pos.x){
			dropSpot = i+1;
		}
	}

	//Here we move the track windows.

	return dropSpot;
}

///////////////////////////////////
void TrackProc::SetPreLoad(bool pl)
{
	if(pl == true){
		wxDialog *preLoadDlg = new wxDialog(NULL, -1, wxT("Pre-Loading Windows . . ."), wxDefaultPosition, wxSize(150,25), wxCAPTION, wxT(""));
		preLoadDlg->CenterOnParent(wxBOTH);
		preLoadDlg->Show();

		//if(trackPanel->mainPanel->audioDev == NULL) { trackPanel->mainPanel->audioDev = new AudioDev(*trackPanel->mainPanel->audio); }
		//if(trackPanel->mainPanel->midiDev == NULL) { trackPanel->mainPanel->midiDev = new MidiDev(*trackPanel->mainPanel->midi);}
		//if(trackPanel->mainPanel->joyDev == NULL) { trackPanel->mainPanel->joyDev = new JoyDev(*trackPanel->mainPanel->joystick); }
		//if(trackPanel->mainPanel->aboutDialog == NULL) { trackPanel->mainPanel->aboutDialog = new AboutDialog(trackPanel->mainPanel, *trackPanel->mainPanel->trackProc);}
		if(trackPanel->mainPanel->optionsDialog == NULL) { trackPanel->mainPanel->optionsDialog = new OptionsDialog(trackPanel->mainPanel, *trackPanel->mainPanel->trackProc);}
		if(trackPanel->mainPanel->pianoDialog == NULL) { trackPanel->mainPanel->pianoDialog = new PianoDialog(trackPanel->mainPanel); trackPanel->mainPanel->pianoDialog->transWindow->Hide();}

		for(int i=1; i<tracks+1; ++i){
			if(n[i].trigger != NULL){
				if(!trackPanel->FindWindowByName(wxString::Format(wxT("Track %d Settings"), i))){
					n[i].trigger->triggerDialog = new TriggerDialog(n[i].trigger); 
				}
			}
			if(n[i].midicc != NULL){
				if(!trackPanel->FindWindowByName(wxString::Format(wxT("Track %d Settings"), i))){
					n[i].midicc->midiCCDialog = new MidiCCDialog(n[i].midicc); 
				}
			}
		}

		delete preLoadDlg;
	}

	preLoad = pl;
}

///////////////////////////////////////
void TrackProc::LinkMidi(Midi *ref)
{
	//Allows us to link a Midi pointer to this class
	//This is currently only use to give the GUI access to the Midi Interface while learning..
	//We can probobly drop this for saftey and let Process:: decide when a track is learning. 
	//Mabey something like Process::Learn(track) or something
	midi = ref;
}

/////////////////////////////////////
void TrackProc::LinkAudio(Audio *ref)
{
	audio = ref;
}

void TrackPanel::OnMenuAddTrigger(wxCommandEvent &event){mainPanel->OnMenuAddTrigger(event);}
void TrackPanel::OnMenuAddMidiCC(wxCommandEvent &event){mainPanel->OnMenuAddMidiCC(event);}
void TrackPanel::OnMenuDeleteTrack(wxCommandEvent &event){mainPanel->OnMenuDeleteTrack(event);}
