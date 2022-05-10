//// Wizard.cpp /////////////////////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "Wizard.h" 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/////////////////////////////////////
BEGIN_EVENT_TABLE(WizardDlg, wxDialog)

	//Audio Driver Pane
	EVT_GBUTTON(208, WizardDlg::OnNext1)

	//Audio Devices Pane
	EVT_GBUTTON(212, WizardDlg::OnNext2)

	// New Track Pane
	EVT_GBUTTON(213, WizardDlg::OnNext3)
	EVT_GBUTTON(214, WizardDlg::OnFinnished)

	//Learn Pane
	EVT_GBUTTON(215, WizardDlg::OnNext4)

END_EVENT_TABLE() 

/////////////////////////////////////////////////////////////////////////////////////////////////////////
WizardDlg::WizardDlg(wxWindow* parent, TrackProc &ref) 
		  :wxDialog(parent, -1, wxT("Drum Setup Wizard"), wxDefaultPosition, wxSize(400, 300), wxCAPTION)
{
	CentreOnScreen(wxBOTH);
	trackProc = &ref;
	MakePanes();
	AudioDriverPane->Show();
	ShowModal();
}

///////////////////////
WizardDlg::~WizardDlg()
{

}

///////////////////////////
void WizardDlg::MakePanes()
{
	/////////// Audio Driver Pane ///////////////
	AudioDriverPane = new wxPanel(this, wxID_ANY, wxPoint(0,0), wxSize(400, 500), wxNO_BORDER  , wxT(""));
    AudioDriverPane->SetBackgroundColour(wxColour(100,100,100));
	AudioDriverPane->Hide();
	image1 = new GImage(AudioDriverPane, wxID_ANY, wxPoint(10, 10), audiodriver_xpm);
	next1 = new GButton(AudioDriverPane, 208, wxPoint(320, 240), next_xpm);
	mme = new wxRadioButton(AudioDriverPane, 209, wxT("Windows MME"), wxPoint(250, 50), wxDefaultSize,  
                               0, wxDefaultValidator, wxT("Windows MME"));
	mme->Disable();
	wds = new wxRadioButton(AudioDriverPane, 210, wxT("Windows Direct Sound"), wxPoint(250, 75), wxDefaultSize,  
                               0, wxDefaultValidator, wxT("Windows Direct Sound"));
	wds->Disable();
	asio = new wxRadioButton(AudioDriverPane, 211, wxT("Asio (recommended)"), wxPoint(250, 100), wxDefaultSize,  
                               0, wxDefaultValidator, wxT("Asio (recommended)"));
	asio->Disable();

	wxArrayString AudioAPIs = trackProc->audio->GetInDeviceAPIs();
	for(unsigned int i=0; i<AudioAPIs.GetCount(); ++i){
		if(AudioAPIs.Item(i) == wxT("MME")){ mme->Enable(); mme->SetValue(true); }
		if(AudioAPIs.Item(i) == wxT("Windows DirectSound")){ wds->Enable(); wds->SetValue(true);}
		if(AudioAPIs.Item(i) == wxT("ASIO")){ asio->Enable(); asio->SetValue(true);}
	}
	///////////////////////////////////////////////


	//////////// Audio Devices Pane ///////////////
	AudioDevicesPane = new wxPanel(this, wxID_ANY, wxPoint(0,0), wxSize(400, 500), wxNO_BORDER  , wxT(""));
    AudioDevicesPane->SetBackgroundColour(wxColour(100,100,100));
	AudioDevicesPane->Hide();
	image2 = new GImage(AudioDevicesPane, wxID_ANY, wxPoint(10, 10), audiodevices_xpm);
	next2 = new GButton(AudioDevicesPane, 212, wxPoint(320, 240), next_xpm);
	
	audioIn = new wxListBox(AudioDevicesPane, -1, wxPoint(210,20), wxSize(150,120), NULL, NULL, wxLB_MULTIPLE, wxDefaultValidator);
	audioIn->SetBackgroundColour( wxColor(40,40,40));
	audioIn->SetForegroundColour( wxColor(200,200,200)); 

	///////////// New Track //////////////////
	NewTrackPane = new wxPanel(this, wxID_ANY, wxPoint(0,0), wxSize(400, 500), wxNO_BORDER  , wxT(""));
	NewTrackPane->SetBackgroundColour(wxColour(100,100,100));
	NewTrackPane->Hide();
	image3 = new GImage(NewTrackPane, wxID_ANY, wxPoint(10, 10), create_xpm);
	next3 = new GButton(NewTrackPane, 213, wxPoint(220, 50), newdrum_xpm);
	finnished = new GButton(NewTrackPane, 214, wxPoint(210, 240), finnished_xpm);

	//////////// LEARN //////////////////////
	LearnPane = new wxPanel(this, wxID_ANY, wxPoint(0,0), wxSize(400, 500), wxNO_BORDER  , wxT(""));
	LearnPane->SetBackgroundColour(wxColour(100,100,100));
	LearnPane->Hide();
    image4 = new GImage(LearnPane, wxID_ANY, wxPoint(10, 10), drumstick_xpm);
	next4 = new GButton(LearnPane, 215, wxPoint(320, 240), next_xpm);

	
}

////////////////////////////////////////////
void WizardDlg::OnNext1(GButtonEvent &event)
{
	event; //reference
	/// Audio Driver Pane ///////////////
	if(mme->GetValue()){trackProc->audio->SetInAPI(wxT("MME"));}
	if(wds->GetValue()){trackProc->audio->SetInAPI(wxT("Windows DirectSound"));}
	if(asio->GetValue()){trackProc->audio->SetInAPI(wxT("ASIO"));}
	AudioDriverPane->Hide();

	/// Audio Devices Pane ///////////////
	audioIn->Clear();
	audioIn->InsertItems( trackProc->audio->GetInDevices( trackProc->audio->selectedInAPI ), 0);
	AudioDevicesPane->Show();
}

////////////////////////////////////////////
void WizardDlg::OnNext2(GButtonEvent &event)
{
	event; //reference 
	/// Audio Devices Pane ///////////////
	wxArrayInt selections;
	if(audioIn->GetSelections(selections) == 0){
		wxMessageBox(wxT("Please select an audio device"));
	}
	else{
		trackProc->audio->StopCallback(); //must Stop Callbacks before changing audio devices
		trackProc->audio->KillStreams();
		
		wxArrayString strings;

		for(unsigned int i=0; i<selections.GetCount(); ++i){
			strings.Add( audioIn->GetString( (int)selections.Item(i) ), 1);
		}
		trackProc->audio->SetInDevices(strings);	//Set the selected Devices

		trackProc->audio->StartCallback(); //Start callbacks after devices are selected

		AudioDevicesPane->Hide();
		NewTrackPane->Show();
	}
}

////////////////////////////////////////////
void WizardDlg::OnNext3(GButtonEvent &event)
{
	event; //reference
	trackProc->AddTrigger();
	NewTrackPane->Hide();
	LearnPane->Show();
	
	//int temp = Process::Learn();
	//in1->SetValue(wxString::Format( "%d", temp ));
}

////////////////////////////////////////////
void WizardDlg::OnNext4(GButtonEvent &event)
{
	event; //reference
	Close();
}

////////////////////////////////////////////////
void WizardDlg::OnFinnished(GButtonEvent &event)
{
	event; //reference
	Close();
}
