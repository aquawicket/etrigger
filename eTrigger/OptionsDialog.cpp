//// OptionsDialog.cpp ///////////////////////////////////////////////////////////
//
//  
//
/////////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "OptionsDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////
BEGIN_EVENT_TABLE(OptionsDialog, wxDialog)
	
	// Main Window
	EVT_GBUTTON(206, OptionsDialog::OnGui)
	EVT_GBUTTON(207, OptionsDialog::OnEngine)
	EVT_GBUTTON(228, OptionsDialog::OnJoystick)
	EVT_GBUTTON(203, OptionsDialog::OnOk)
	EVT_GBUTTON(204, OptionsDialog::OnCancel) 

	// GUI Panel
	EVT_CHECKBOX(208, OptionsDialog::OnSplashScreen)
	EVT_CHECKBOX(210, OptionsDialog::OnEnableMeters)
	EVT_CHECKBOX(211, OptionsDialog::OnPreLoad)
	EVT_CHECKBOX(216, OptionsDialog::OnToolTips)
	EVT_TEXT(214, OptionsDialog::OnFileText)
	EVT_GBUTTON(209, OptionsDialog::OnFileSelect)

	// Engine Panel
	EVT_TEXT(205, OptionsDialog::OnOnsetType)
	EVT_TEXT(212, OptionsDialog::OnAudioBuffer)
	EVT_CHECKBOX(215, OptionsDialog::OnMidiBleed)
	EVT_CHECKBOX(217, OptionsDialog::OnMidiChannels)
	EVT_GNUMBERBOX(213, OptionsDialog::OnMouseSensitivity)
	EVT_GNUMBERBOX(220, OptionsDialog::OnRetriggerSafty)
	EVT_GNUMBERBOX(221, OptionsDialog::OnRetriggerThreshold)
	EVT_GNUMBERBOX(300, OptionsDialog::OnFlamAdjustment)
	EVT_GNUMBERBOX(301, OptionsDialog::OnRollAdjustment)

	EVT_TEXT(401, OptionsDialog::OnFolderText)
	EVT_GBUTTON(400, OptionsDialog::OnFolderSelect)

	// Joystick Panel
	EVT_GNUMBERBOX(218, OptionsDialog::OnJoystickPolling)
	EVT_GNUMBERBOX(233, OptionsDialog::OnJoyMinX)
	EVT_GNUMBERBOX(234, OptionsDialog::OnJoyMinY)
	EVT_GNUMBERBOX(235, OptionsDialog::OnJoyMinZ)
	EVT_GNUMBERBOX(236, OptionsDialog::OnJoyMinR)
	EVT_GNUMBERBOX(237, OptionsDialog::OnJoyMinU)
	EVT_GNUMBERBOX(238, OptionsDialog::OnJoyMinV)
	EVT_GNUMBERBOX(222, OptionsDialog::OnJoyMaxX)
	EVT_GNUMBERBOX(223, OptionsDialog::OnJoyMaxY)
	EVT_GNUMBERBOX(224, OptionsDialog::OnJoyMaxZ)
	EVT_GNUMBERBOX(225, OptionsDialog::OnJoyMaxR)
	EVT_GNUMBERBOX(226, OptionsDialog::OnJoyMaxU)
	EVT_GNUMBERBOX(227, OptionsDialog::OnJoyMaxV)
	EVT_GBUTTON(229, OptionsDialog::OnJoyMaxDetect)
	EVT_GBUTTON(230, OptionsDialog::OnJoyMaxReset)
	EVT_GBUTTON(231, OptionsDialog::OnJoyMaxOk)
	EVT_GBUTTON(232, OptionsDialog::OnJoyMaxCancel)

	EVT_LEFT_DOWN (OptionsDialog::OnMouse)
	EVT_CLOSE(   OptionsDialog::OnClose)
END_EVENT_TABLE() 

///////////////////////////////////////////////////////////////
OptionsDialog::OptionsDialog(MainPanel *parent, TrackProc &ref) 
        : trackProc(&ref), wxDialog(NULL, -1, wxT("Options"), wxDefaultPosition, wxSize(430, 510), wxDEFAULT_DIALOG_STYLE)
{
	CentreOnScreen(wxBOTH);

	mainPanel = parent;

#ifdef WIN32
	SetBackgroundColour(wxColour(30,30,30));
#endif //WIN32
#ifdef MAC
	wxPanel *background = new wxPanel(this, -1, wxPoint(0,0), this->GetSize(), 0, wxT(""));
	background->SetBackgroundColour(wxColour(30,30,30));
#endif //MAC
		
	//corners and edges
	topLeftCornerSide = new GImage(this, -1, wxPoint(120,40), TopLeftCornerSide_xpm);
	topLeftCornerTop = new GImage(this, -1, wxPoint(125,39), TopLeftCornerTop_xpm);
	topEdge1 = new GImage(this, -1, wxPoint(155,39), TopEdge_xpm);
	topEdge2 = new GImage(this, -1, wxPoint(229,39), TopEdge_xpm);
	topEdge3 = new GImage(this, -1, wxPoint(303,39), TopEdge_xpm);
	//leftEdge3 = new GImage(this, -1, wxPoint(120,140), LeftEdge_xpm);
	leftEdge4 = new GImage(this, -1, wxPoint(120,173), LeftEdge_xpm);
	leftEdge5 = new GImage(this, -1, wxPoint(120,206), LeftEdge_xpm);
	leftEdge6 = new GImage(this, -1, wxPoint(120,239), LeftEdge_xpm);
	leftEdge7 = new GImage(this, -1, wxPoint(120,272), LeftEdge_xpm);
	leftEdge8 = new GImage(this, -1, wxPoint(120,305), LeftEdge_xpm);
	leftEdge9 = new GImage(this, -1, wxPoint(120,338), LeftEdge_xpm);
	leftEdge10 = new GImage(this, -1, wxPoint(120,371), LeftEdge_xpm);

	//buttons
	guiButton = new GButton(this, 206, wxPoint(10,74), Gui_xpm , Gui_Hover_xpm);
	guiSelected = new GButton(this, -1, wxPoint(10,74), Gui_Selected_xpm);
	engineButton = new GButton(this, 207, wxPoint(10,107), Engine_xpm , Engine_Hover_xpm);
    engineSelected = new GButton(this, -1, wxPoint(10,107), Engine_Selected_xpm);
	joystickButton = new GButton(this, 228, wxPoint(10,140), joystickTab_xpm , joystickTab_hover_xpm);
    joystickSelected = new GButton(this, -1, wxPoint(10,140), joystickTab_selected_xpm);
	ok = new GButton(this, 203, wxPoint(264,445), ok2_xpm, ok2_hover_xpm, ok2_click_xpm); 
	cancel = new GButton(this, 204, wxPoint(335,445), cancel2_xpm, cancel2_hover_xpm, cancel2_click_xpm);

	///////////////////// Panels ////////////////

	//// GUI Panel
	guiPanel = new wxPanel(this, -1, wxPoint(125, 45), wxSize(290,388), 0, wxT(""));
	guiPanel->SetBackgroundColour(wxColour(99,99,99));
	#ifdef WIN32
	guiPanel->Connect(-1, wxEVT_LEFT_DOWN, wxMouseEventHandler(OptionsDialog::OnMouse), NULL, this);
	#endif
	splashScreenBox = new wxCheckBox(guiPanel, 208, wxT("Splash Screen"), wxPoint(20,20), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	toolTipsBox = new wxCheckBox(guiPanel, 216, wxT("Enable Tool Tips"), wxPoint(20,40), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	enableMetersBox = new wxCheckBox(guiPanel, 210, wxT("Enable Meters"), wxPoint(20,60), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	preLoadBox = new wxCheckBox(guiPanel, 211, wxT("Live Mode (Preload Windows On Startup)"), wxPoint(20,80), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	wxStaticText *startupFile = new wxStaticText(guiPanel, -1, wxT("Startup File"), wxPoint(20, 100), wxDefaultSize,  0, wxT(""));
	filePath = new wxTextCtrl(guiPanel, 214, wxT(""), wxPoint(20, 120), wxSize(200,16), wxNO_BORDER, wxDefaultValidator, wxT(""));
	filePath->SetBackgroundColour(wxColour(30,30,30));
	filePath->SetForegroundColour(wxColour(200,200,200));
	fileSelector = new GButton(guiPanel, 209, wxPoint(230,110), folder_xpm, folder_hover_xpm, folder_click_xpm); 
	wxStaticText *mouseSenseText =  new wxStaticText(guiPanel, -1, wxT("Mouse Wheel Sensitivity"), wxPoint(60, 145), wxDefaultSize,  0, wxT(""));
	mouseSenseBox = new GNumberBox(guiPanel, 213, wxT(""), wxPoint(20,145), wxSize(30,15));
	mouseSenseBox->SetMinMax(1,127);
	mouseSenseBox->SetDefault(5);
	


	//// Engine Panel
	enginePanel = new wxPanel(this, -1, wxPoint(125, 45), wxSize(282,388), 0, wxT(""));
	enginePanel->SetBackgroundColour(wxColour(99,99,99));
	#ifdef WIN32
	enginePanel->Connect(-1, wxEVT_LEFT_DOWN, wxMouseEventHandler(OptionsDialog::OnMouse), NULL, this);
	#endif
#ifdef AUBIO
	wxStaticText *onsetType = new wxStaticText(enginePanel, -1, wxT("Detection Method"), wxPoint(10, 20), wxSize(60, 30), 0, wxT(""));
	Types.Add(wxT("energy based"));
	Types.Add(wxT("spectral diff"));
	Types.Add(wxT("high frequency content"));
	Types.Add(wxT("complex domain"));
	Types.Add(wxT("phase fast"));
	Types.Add(wxT("Kullback Liebler"));
	Types.Add(wxT("modified Kullback Liebler"));	
	Type = new wxComboBox(enginePanel, 205, wxT(""), wxPoint(80,20), wxSize(150,30), Types, 0, wxDefaultValidator, wxT(""));
#endif //AUBIO
	wxStaticText *audioBufferText = new wxStaticText(enginePanel, -1, wxT("Audio Buffer"), wxPoint(10, 50), wxSize(60, 30), 0, wxT(""));
	buffers.Add(wxT("128"));
	buffers.Add(wxT("160"));
	buffers.Add(wxT("192"));
	buffers.Add(wxT("224"));
	buffers.Add(wxT("256"));
	buffers.Add(wxT("288"));
	buffers.Add(wxT("320"));
	buffers.Add(wxT("352"));
	buffers.Add(wxT("384"));
	buffers.Add(wxT("416"));
	buffers.Add(wxT("448"));
	buffers.Add(wxT("480"));
	buffers.Add(wxT("512"));
	buffers.Add(wxT("768"));
	buffers.Add(wxT("1024"));
	buffers.Add(wxT("1536"));
	buffers.Add(wxT("2048"));
	buffers.Add(wxT("4096"));
	audioBufferBox = new wxComboBox(enginePanel, 212, wxT(""), wxPoint(80,48), wxSize(125,30), buffers, 0, wxDefaultValidator, wxT(""));
	midiBleedBox = new wxCheckBox(enginePanel, 215, wxT("Midi Thru"), wxPoint(10,80), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	wxStaticText *midiListenChannelText = new wxStaticText(enginePanel, -1, wxT("Midi Input Channels"), wxPoint(10, 110), wxDefaultSize, 0, wxT(""));
	wxStaticText *midiChannelLabelText = new wxStaticText(enginePanel, -1, wxT(" 1   2   3   4   5   6   7   8   9  10 11 12 13 14 15 16"), wxPoint(10, 125), wxDefaultSize, 0, wxT(""));
   	midiChannel1Box = new wxCheckBox(enginePanel, 217, wxT(""), wxPoint(10,140), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	midiChannel2Box = new wxCheckBox(enginePanel, 217, wxT(""), wxPoint(25,140), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	midiChannel3Box = new wxCheckBox(enginePanel, 217, wxT(""), wxPoint(40,140), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	midiChannel4Box = new wxCheckBox(enginePanel, 217, wxT(""), wxPoint(55,140), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	midiChannel5Box = new wxCheckBox(enginePanel, 217, wxT(""), wxPoint(70,140), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	midiChannel6Box = new wxCheckBox(enginePanel, 217, wxT(""), wxPoint(85,140), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	midiChannel7Box = new wxCheckBox(enginePanel, 217, wxT(""), wxPoint(100,140), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	midiChannel8Box = new wxCheckBox(enginePanel, 217, wxT(""), wxPoint(115,140), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	midiChannel9Box = new wxCheckBox(enginePanel, 217, wxT(""), wxPoint(130,140), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	midiChannel10Box = new wxCheckBox(enginePanel, 217, wxT(""), wxPoint(145,140), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	midiChannel11Box = new wxCheckBox(enginePanel, 217, wxT(""), wxPoint(160,140), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	midiChannel12Box = new wxCheckBox(enginePanel, 217, wxT(""), wxPoint(175,140), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	midiChannel13Box = new wxCheckBox(enginePanel, 217, wxT(""), wxPoint(190,140), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	midiChannel14Box = new wxCheckBox(enginePanel, 217, wxT(""), wxPoint(205,140), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	midiChannel15Box = new wxCheckBox(enginePanel, 217, wxT(""), wxPoint(220,140), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	midiChannel16Box = new wxCheckBox(enginePanel, 217, wxT(""), wxPoint(235,140), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	retriggerSaftyBox = new GNumberBox(enginePanel, 220, wxT(""), wxPoint(10,180), wxSize(30,15));
	retriggerSaftyBox->SetMinMax(1,20);
	retriggerSaftyBox->SetDefault(5);
	wxStaticText *retriggerSafetyText = new wxStaticText(enginePanel, -1, wxT("Retrigger Safety"), wxPoint(50, 180), wxDefaultSize, 0, wxT(""));
	retriggerThresholdBox = new GNumberBox(enginePanel, 221, wxT(""), wxPoint(10,200), wxSize(30,15));
	retriggerThresholdBox->SetMinMax(1,250);
	retriggerThresholdBox->SetDefault(150);
	wxStaticText *retriggerThresholdText = new wxStaticText(enginePanel, -1, wxT("Retrigger Learn Threshold"), wxPoint(50, 200), wxDefaultSize, 0, wxT(""));
	flamAdjustmentBox = new GNumberBox(enginePanel, 300, wxT(""), wxPoint(10,220), wxSize(30,15));
	flamAdjustmentBox->SetMinMax(0,127);
	flamAdjustmentBox->SetDefault(5);
	wxStaticText *flamAdjustmentText = new wxStaticText(enginePanel, -1, wxT("Flam Adjustment"), wxPoint(50, 220), wxDefaultSize, 0, wxT(""));
	rollAdjustmentBox = new GNumberBox(enginePanel, 301, wxT(""), wxPoint(10,240), wxSize(30,15));
	rollAdjustmentBox->SetMinMax(0,127);
	rollAdjustmentBox->SetDefault(15);
	wxStaticText *rollAdjustmentText = new wxStaticText(enginePanel, -1, wxT("Roll Adjustment"), wxPoint(50, 240), wxDefaultSize, 0, wxT(""));
	
	wxStaticText *samplesFolder = new wxStaticText(enginePanel, -1, wxT("Samples Folder"), wxPoint(20, 270), wxDefaultSize,  0, wxT(""));
	folderPath = new wxTextCtrl(enginePanel, 401, wxT(""), wxPoint(20, 290), wxSize(200,16), wxNO_BORDER, wxDefaultValidator, wxT(""));
	folderPath->SetBackgroundColour(wxColour(30,30,30));
	folderPath->SetForegroundColour(wxColour(200,200,200));
	folderSelector = new GButton(enginePanel, 400, wxPoint(230,280), folder_xpm, folder_hover_xpm, folder_click_xpm);

	//// Joystick Panel
	joystickPanel = new wxPanel(this, -1, wxPoint(125, 45), wxSize(282,388), 0, wxT(""));
	joystickPanel->SetBackgroundColour(wxColour(99,99,99));

	wxStaticText *joyPollingText = new wxStaticText(joystickPanel, -1, wxT("JoyStick Polling Speed"), wxPoint(50, 20), wxDefaultSize, 0, wxT(""));
	joyPolling = new GNumberBox(joystickPanel, 218, wxT(""), wxPoint(10,20), wxSize(30,15));
	joyPolling->SetMinMax(1,10);
	joyPolling->SetDefault(10);
	
	joyMinXBox = new GNumberBox(joystickPanel, 233, wxT(""), wxPoint(10,40), wxSize(40,15));
	joyMinXBox->SetMinMax(0,65000);
	wxStaticText *joyMinXText = new wxStaticText(joystickPanel, -1, wxT("Min X Axes"), wxPoint(55, 40), wxDefaultSize, 0, wxT(""));
	joyMinYBox = new GNumberBox(joystickPanel, 234, wxT(""), wxPoint(10,60), wxSize(40,15));
	joyMinYBox->SetMinMax(0,65000);
	wxStaticText *joyMinYText = new wxStaticText(joystickPanel, -1, wxT("Min Y Axes"), wxPoint(55, 60), wxDefaultSize, 0, wxT(""));
	joyMinZBox = new GNumberBox(joystickPanel, 235, wxT(""), wxPoint(10,80), wxSize(40,15));
	joyMinZBox->SetMinMax(0,65000);
	wxStaticText *joyMinZText = new wxStaticText(joystickPanel, -1, wxT("Min Z Axes"), wxPoint(55, 80), wxDefaultSize, 0, wxT(""));
	joyMinRBox = new GNumberBox(joystickPanel, 236, wxT(""), wxPoint(10,100), wxSize(40,15));
	joyMinRBox->SetMinMax(0,65000);
	wxStaticText *joyMinRText = new wxStaticText(joystickPanel, -1, wxT("Min R Axes"), wxPoint(55, 100), wxDefaultSize, 0, wxT(""));
	joyMinUBox = new GNumberBox(joystickPanel, 237, wxT(""), wxPoint(10,120), wxSize(40,15));
	joyMinUBox->SetMinMax(0,65000);
	wxStaticText *joyMinUText = new wxStaticText(joystickPanel, -1, wxT("Min U Axes"), wxPoint(55, 120), wxDefaultSize, 0, wxT(""));
	joyMinVBox = new GNumberBox(joystickPanel, 238, wxT(""), wxPoint(10,140), wxSize(40,15));
	joyMinVBox->SetMinMax(0,65000);
	wxStaticText *joyMinVText = new wxStaticText(joystickPanel, -1, wxT("Min V Axes"), wxPoint(55, 140), wxDefaultSize, 0, wxT(""));

	joyMaxXBox = new GNumberBox(joystickPanel, 222, wxT(""), wxPoint(150,40), wxSize(40,15));
	joyMaxXBox->SetMinMax(0,65000);
	wxStaticText *joyMaxXText = new wxStaticText(joystickPanel, -1, wxT("Max X Axes"), wxPoint(195, 40), wxDefaultSize, 0, wxT(""));
	joyMaxYBox = new GNumberBox(joystickPanel, 223, wxT(""), wxPoint(150,60), wxSize(40,15));
	joyMaxYBox->SetMinMax(0,65000);
	wxStaticText *joyMaxYText = new wxStaticText(joystickPanel, -1, wxT("Max Y Axes"), wxPoint(195, 60), wxDefaultSize, 0, wxT(""));
	joyMaxZBox = new GNumberBox(joystickPanel, 224, wxT(""), wxPoint(150,80), wxSize(40,15));
	joyMaxZBox->SetMinMax(0,65000);
	wxStaticText *joyMaxZText = new wxStaticText(joystickPanel, -1, wxT("Max Z Axes"), wxPoint(195, 80), wxDefaultSize, 0, wxT(""));
	joyMaxRBox = new GNumberBox(joystickPanel, 225, wxT(""), wxPoint(150,100), wxSize(40,15));
	joyMaxRBox->SetMinMax(0,65000);
	wxStaticText *joyMaxRText = new wxStaticText(joystickPanel, -1, wxT("Max R Axes"), wxPoint(195, 100), wxDefaultSize, 0, wxT(""));
	joyMaxUBox = new GNumberBox(joystickPanel, 226, wxT(""), wxPoint(150,120), wxSize(40,15));
	joyMaxUBox->SetMinMax(0,65000);
	wxStaticText *joyMaxUText = new wxStaticText(joystickPanel, -1, wxT("Max U Axes"), wxPoint(195, 120), wxDefaultSize, 0, wxT(""));
	joyMaxVBox = new GNumberBox(joystickPanel, 227, wxT(""), wxPoint(150,140), wxSize(40,15));
	joyMaxVBox->SetMinMax(0,65000);
	wxStaticText *joyMaxVText = new wxStaticText(joystickPanel, -1, wxT("Max V Axes"), wxPoint(195, 140), wxDefaultSize, 0, wxT(""));
	
	joyMaxDetect = new GButton(joystickPanel, 229, wxPoint(100,200), detect_xpm, detect_hover_xpm, detect_click_xpm);
	joyMaxReset = new GButton(joystickPanel, 230, wxPoint(25,350), reset_xpm, reset_hover_xpm, reset_click_xpm);
	joyMaxOk = new GButton(joystickPanel, 231, wxPoint(100,350),  ok3_xpm, ok3_hover_xpm, ok3_click_xpm);
	joyMaxCancel = new GButton(joystickPanel, 232, wxPoint(175,350), cancel3_xpm, cancel3_hover_xpm, cancel3_click_xpm);
	joyMaxReset->Hide();
	joyMaxOk->Hide();
	joyMaxCancel->Hide();

	VarsToTemp();
	VarsToDlg();
	UpdateSelection(wxT("gui")); //make default panel1
}

///////////////////////////////
OptionsDialog::~OptionsDialog()
{

}

////////////////////////////////
void OptionsDialog::VarsToTemp()
{
	//Store the data temporarily in case we hit cancel and want to revert back.
	splashScreen = mainPanel->splashScreen;
	enableMeters = trackProc->enableMeters;
	preLoad = trackProc->preLoad;
	initPath = mainPanel->initPath;
	initFilename = mainPanel->initFilename;

	initFolderPath = mainPanel->samples->sampleDir;

	mouseSensitivity = trackProc->mouseSensitivity;
	
#ifdef AUBIO
	if(trackProc->audio->type_onset == aubio_onset_energy){onsetType = wxT("energy based"); }
	if(trackProc->audio->type_onset == aubio_onset_specdiff){onsetType = wxT("spectral diff");}
	if(trackProc->audio->type_onset == aubio_onset_hfc){onsetType = wxT("high frequency content");}
	if(trackProc->audio->type_onset == aubio_onset_complex){onsetType = wxT("complex domain");}
	if(trackProc->audio->type_onset == aubio_onset_phase){onsetType = wxT("phase fast");}
	if(trackProc->audio->type_onset == aubio_onset_kl){onsetType = wxT("Kullback Liebler");}
	if(trackProc->audio->type_onset == aubio_onset_mkl){onsetType = wxT("modified Kullback Liebler");}
#endif

	audioBuffer = trackProc->audio->framesPerBuffer;
	midiBleed = trackProc->midiBleed;
	toolTips = mainPanel->toolTips;
	for(int i = 0; i<16; ++i){
		midiChannel[i] = trackProc->midiChannel[i];
	}

	retriggerSafty = trackProc->retriggerSafty;
	retriggerThreshold = trackProc->retriggerThreshold;
	flamAdjustment = trackProc->flamAdjustment;
	rollAdjustment = trackProc->rollAdjustment;

	pollSpeed = mainPanel->joystick->pollSpeed;

	joyMinX = mainPanel->joystick->GetMinX();
	joyMinY = mainPanel->joystick->GetMinY();
	joyMinZ = mainPanel->joystick->GetMinZ();
	joyMinR = mainPanel->joystick->GetMinR();
	joyMinU = mainPanel->joystick->GetMinU();
	joyMinV = mainPanel->joystick->GetMinV();

	joyMaxX = mainPanel->joystick->GetMaxX();
	joyMaxY = mainPanel->joystick->GetMaxY();
	joyMaxZ = mainPanel->joystick->GetMaxZ();
	joyMaxR = mainPanel->joystick->GetMaxR();
	joyMaxU = mainPanel->joystick->GetMaxU();
	joyMaxV = mainPanel->joystick->GetMaxV();
}

///////////////////////////////
void OptionsDialog::VarsToDlg()
{
	//place the track Database data onto the dialog
	splashScreenBox->SetValue(mainPanel->splashScreen);
	enableMetersBox->SetValue(trackProc->enableMeters);
	preLoadBox->SetValue(trackProc->preLoad);
	wxString temp;
	temp = mainPanel->initPath;
	temp += mainPanel->initFilename;
	filePath->SetValue(temp);

	folderPath->SetValue(mainPanel->samples->sampleDir);
	
	mouseSenseBox->SetValue(wxString::Format(wxT("%d"), trackProc->mouseSensitivity));

#ifdef AUBIO
	if(trackProc->audio->type_onset == aubio_onset_energy){Type->SetValue(wxT("energy based")); }
	if(trackProc->audio->type_onset == aubio_onset_specdiff){Type->SetValue(wxT("spectral diff"));}
	if(trackProc->audio->type_onset == aubio_onset_hfc){Type->SetValue(wxT("high frequency content"));}
	if(trackProc->audio->type_onset == aubio_onset_complex){Type->SetValue(wxT("complex domain"));}
	if(trackProc->audio->type_onset == aubio_onset_phase){Type->SetValue(wxT("phase fast"));}
	if(trackProc->audio->type_onset == aubio_onset_kl){Type->SetValue(wxT("Kullback Liebler"));}
	if(trackProc->audio->type_onset == aubio_onset_mkl){Type->SetValue(wxT("modified Kullback Liebler"));}
#endif

	audioBufferBox->SetValue(wxString::Format(wxT("%d"),trackProc->audio->framesPerBuffer));
	midiBleedBox->SetValue(trackProc->midiBleed);
	toolTipsBox->SetValue(mainPanel->toolTips);

	midiChannel1Box->SetValue(trackProc->midiChannel[1]);
	midiChannel2Box->SetValue(trackProc->midiChannel[2]);
	midiChannel3Box->SetValue(trackProc->midiChannel[3]);
	midiChannel4Box->SetValue(trackProc->midiChannel[4]);
	midiChannel5Box->SetValue(trackProc->midiChannel[5]);
	midiChannel6Box->SetValue(trackProc->midiChannel[6]);
	midiChannel7Box->SetValue(trackProc->midiChannel[7]);
	midiChannel8Box->SetValue(trackProc->midiChannel[8]);
	midiChannel9Box->SetValue(trackProc->midiChannel[9]);
	midiChannel10Box->SetValue(trackProc->midiChannel[10]);
	midiChannel11Box->SetValue(trackProc->midiChannel[11]);
	midiChannel12Box->SetValue(trackProc->midiChannel[12]);
	midiChannel13Box->SetValue(trackProc->midiChannel[13]);
	midiChannel14Box->SetValue(trackProc->midiChannel[14]);
	midiChannel15Box->SetValue(trackProc->midiChannel[15]);
	midiChannel16Box->SetValue(trackProc->midiChannel[16]);

	retriggerSaftyBox->SetValue(wxString::Format(wxT("%d"), trackProc->retriggerSafty));
	retriggerThresholdBox->SetValue(wxString::Format(wxT("%d"), trackProc->retriggerThreshold));
	flamAdjustmentBox->SetValue(wxString::Format(wxT("%d"), trackProc->flamAdjustment));
	rollAdjustmentBox->SetValue(wxString::Format(wxT("%d"), trackProc->rollAdjustment));

	joyPolling->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->pollSpeed));

	joyMinXBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->GetMinX()));
	joyMinYBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->GetMinY()));
	joyMinZBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->GetMinZ()));
	joyMinRBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->GetMinR()));
	joyMinUBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->GetMinU()));
	joyMinVBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->GetMinV()));	

	joyMaxXBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->GetMaxX()));
	joyMaxYBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->GetMaxY()));
	joyMaxZBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->GetMaxZ()));
	joyMaxRBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->GetMaxR()));
	joyMaxUBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->GetMaxU()));
	joyMaxVBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->GetMaxV()));	
}

////////////////////////////////
void OptionsDialog::TempToVars()
{
	//Transfer the temporary back if we hit cancel
	mainPanel->splashScreen = splashScreen;
	trackProc->enableMeters = enableMeters;
	//we should try stoping and or starting the Meter timer here

	trackProc->SetPreLoad(preLoad);
	mainPanel->initPath = initPath;
	mainPanel->initFilename = initFilename;

	mainPanel->samples->sampleDir = initFolderPath;

	trackProc->mouseSensitivity = mouseSensitivity;
	wxArrayString temp = trackProc->audio->selectedIn; //store the current devices
	trackProc->audio->StopCallback();
	trackProc->audio->KillStreams(); //gotta reload the devices for aubio changes to take effect

#ifdef AUBIO
	if(onsetType == wxT("energy based")){ trackProc->audio->type_onset = aubio_onset_energy; }
	if(onsetType == wxT("spectral diff")){ trackProc->audio->type_onset = aubio_onset_specdiff; }
	if(onsetType == wxT("high frequency content")){ trackProc->audio->type_onset = aubio_onset_hfc; }
	if(onsetType == wxT("complex domain")){ trackProc->audio->type_onset = aubio_onset_complex; }
	if(onsetType == wxT("phase fast")){ trackProc->audio->type_onset = aubio_onset_phase; }
	if(onsetType == wxT("Kullback Liebler")){ trackProc->audio->type_onset = aubio_onset_kl; }
	if(onsetType == wxT("modified Kullback Liebler")){ trackProc->audio->type_onset = aubio_onset_mkl; }
#endif

	trackProc->audio->SetInDevices(temp); //reload the devices
	trackProc->audio->StartCallback();
	trackProc->audio->SetAudioBuffer(audioBuffer);
	trackProc->midiBleed = midiBleed;
	mainPanel->toolTips = toolTips;
	for(int i = 0; i<16; ++i){
		trackProc->midiChannel[i] = midiChannel[i];
	}
	trackProc->retriggerSafty = retriggerSafty;
	trackProc->retriggerThreshold = retriggerThreshold;
	trackProc->flamAdjustment = flamAdjustment;
	trackProc->rollAdjustment = rollAdjustment;

	mainPanel->joystick->pollSpeed = pollSpeed;
	
	mainPanel->joystick->SetMinX(joyMinX);
	mainPanel->joystick->SetMinY(joyMinY);
	mainPanel->joystick->SetMinZ(joyMinZ);
	mainPanel->joystick->SetMinR(joyMinR);
	mainPanel->joystick->SetMinU(joyMinU);
	mainPanel->joystick->SetMinV(joyMinV);

	mainPanel->joystick->SetMaxX(joyMaxX);
	mainPanel->joystick->SetMaxY(joyMaxY);
	mainPanel->joystick->SetMaxZ(joyMaxZ);
	mainPanel->joystick->SetMaxR(joyMaxR);
	mainPanel->joystick->SetMaxU(joyMaxU);
	mainPanel->joystick->SetMaxV(joyMaxV);
} 

///////////////////////////////
void OptionsDialog::TempToDlg()
{
	//place the track Database data onto the dialog
	splashScreenBox->SetValue(splashScreen);
	enableMetersBox->SetValue(enableMeters);
	preLoadBox->SetValue(preLoad);
	wxString temp;
	temp = initPath;
	temp += initFilename;
	filePath->SetValue(temp);

	folderPath->SetValue(initFolderPath);

	mouseSenseBox->SetValue(wxString::Format(wxT("%d"), mouseSensitivity));

#ifdef AUBIO
	if(onsetType == aubio_onset_energy){Type->SetValue(wxT("energy based")); }
	if(onsetType == aubio_onset_specdiff){Type->SetValue(wxT("spectral diff"));}
	if(onsetType == aubio_onset_hfc){Type->SetValue(wxT("high frequency content"));}
	if(onsetType == aubio_onset_complex){Type->SetValue(wxT("complex domain"));}
	if(onsetType == aubio_onset_phase){Type->SetValue(wxT("phase fast"));}
	if(onsetType == aubio_onset_kl){Type->SetValue(wxT("Kullback Liebler"));}
	if(onsetType == aubio_onset_mkl){Type->SetValue(wxT("modified Kullback Liebler"));}
#endif

	audioBufferBox->SetValue(wxString::Format(wxT("%d"),audioBuffer));
	midiBleedBox->SetValue(midiBleed);
	toolTipsBox->SetValue(toolTips);

	midiChannel1Box->SetValue(midiChannel[1]);
	midiChannel2Box->SetValue(midiChannel[2]);
	midiChannel3Box->SetValue(midiChannel[3]);
	midiChannel4Box->SetValue(midiChannel[4]);
	midiChannel5Box->SetValue(midiChannel[5]);
	midiChannel6Box->SetValue(midiChannel[6]);
	midiChannel7Box->SetValue(midiChannel[7]);
	midiChannel8Box->SetValue(midiChannel[8]);
	midiChannel9Box->SetValue(midiChannel[9]);
	midiChannel10Box->SetValue(midiChannel[10]);
	midiChannel11Box->SetValue(midiChannel[11]);
	midiChannel12Box->SetValue(midiChannel[12]);
	midiChannel13Box->SetValue(midiChannel[13]);
	midiChannel14Box->SetValue(midiChannel[14]);
	midiChannel15Box->SetValue(midiChannel[15]);
	midiChannel16Box->SetValue(midiChannel[16]);

	retriggerSaftyBox->SetValue(wxString::Format(wxT("%d"), retriggerSafty));
	retriggerThresholdBox->SetValue(wxString::Format(wxT("%d"), retriggerThreshold));
	flamAdjustmentBox->SetValue(wxString::Format(wxT("%d"), flamAdjustment));
	rollAdjustmentBox->SetValue(wxString::Format(wxT("%d"), rollAdjustment));

	joyPolling->SetValue(wxString::Format(wxT("%d"), pollSpeed));
	
	joyMinXBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->GetMinX()));
	joyMinYBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->GetMinY()));
	joyMinZBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->GetMinZ()));
	joyMinRBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->GetMinR()));
	joyMinUBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->GetMinU()));
	joyMinVBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->GetMinV()));

	joyMaxXBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->GetMaxX()));
	joyMaxYBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->GetMaxY()));
	joyMaxZBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->GetMaxZ()));
	joyMaxRBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->GetMaxR()));
	joyMaxUBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->GetMaxU()));
	joyMaxVBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->GetMaxV()));
}

/////////////////////////////////////////////
void OptionsDialog::OnOk(GButtonEvent &event)
{
	joyMaxDetect->Show();
	joyMaxReset->Hide();
	joyMaxOk->Hide();
	joyMaxCancel->Hide();
	mainPanel->joystick->detectMaxAxes = false;

	VarsToTemp(); 
	Hide();
}

/////////////////////////////////////////////////
void OptionsDialog::OnCancel(GButtonEvent &event)
{
	Close();
}

////////////////////////////////////////////////
void OptionsDialog::OnClose(wxCloseEvent &event)
{
	joyMaxDetect->Show();
	joyMaxReset->Hide();
	joyMaxOk->Hide();
	joyMaxCancel->Hide();
	mainPanel->joystick->detectMaxAxes = false;

	TempToVars();
	VarsToDlg();
	mainPanel->joystick->Reload();

	Hide();
}

//////////////////////////////////////////////
void OptionsDialog::OnGui(GButtonEvent &event)
{
	UpdateSelection(wxT("gui"));
}

/////////////////////////////////////////////////
void OptionsDialog::OnEngine(GButtonEvent &event)
{
	UpdateSelection(wxT("engine"));
}

///////////////////////////////////////////////////
void OptionsDialog::OnJoystick(GButtonEvent &event)
{
	UpdateSelection(wxT("joystick"));
}

////////////////////////////////////////////////////
void OptionsDialog::UpdateSelection(wxString string)
{
	if(string == wxT("gui")){
		guiSelected->Show();
		guiPanel->Show();
		engineButton->Show();
		joystickButton->Show();
		guiButton->Hide();
		engineSelected->Hide();
		enginePanel->Hide();
		joystickSelected->Hide();
		joystickPanel->Hide();
	}

	if(string == wxT("engine")){
		guiButton->Show();
		engineSelected->Show();
		enginePanel->Show();
		joystickButton->Show();
		guiSelected->Hide();
		guiPanel->Hide();
		engineButton->Hide();	
		joystickSelected->Hide();
		joystickPanel->Hide();
	}

	if(string == wxT("joystick")){
		guiButton->Show();
		engineButton->Show();
		joystickSelected->Show();
		joystickPanel->Show();
		guiSelected->Hide();
		guiPanel->Hide();
		engineSelected->Hide();
		enginePanel->Hide();
		joystickButton->Hide(); 	
	}
}

/////////////////////////////////////////////////////////
void OptionsDialog::OnSplashScreen(wxCommandEvent &event)
{
	mainPanel->splashScreen = splashScreenBox->GetValue();	
}

/////////////////////////////////////////////////////////
void OptionsDialog::OnEnableMeters(wxCommandEvent &event)
{
	trackProc->enableMeters = enableMetersBox->GetValue();	
	//we should try stoping and or starting the Meter timer here
}

////////////////////////////////////////////////////
void OptionsDialog::OnPreLoad(wxCommandEvent &event)
{
	trackProc->SetPreLoad(preLoadBox->GetValue());	
}

//////////////////////////////////////////////////////
void OptionsDialog::OnOnsetType(wxCommandEvent &event)
{
	wxArrayString temp = trackProc->audio->selectedIn; //store the current devices
	trackProc->audio->StopCallback();
	trackProc->audio->KillStreams(); //gotta reload the devices for aubio changes to take effect

	//Put Set AudioBuffer Size here
	//Put Set SampleRate here

#ifdef AUBIO
	if(Type->GetValue() == wxT("energy based")){
		trackProc->audio->type_onset = aubio_onset_energy;
	}
	if(Type->GetValue() == wxT("spectral diff")){
		trackProc->audio->type_onset = aubio_onset_specdiff;
	}
	if(Type->GetValue() == wxT("high frequency content")){
		trackProc->audio->type_onset = aubio_onset_hfc;
	}
	if(Type->GetValue() == wxT("complex domain")){
		trackProc->audio->type_onset = aubio_onset_complex;
	}
	if(Type->GetValue() == wxT("phase fast")){
		trackProc->audio->type_onset = aubio_onset_phase;
	}
	if(Type->GetValue() == wxT("Kullback Liebler")){
		trackProc->audio->type_onset = aubio_onset_kl;
	}
	if(Type->GetValue() == wxT("modified Kullback Liebler")){
		trackProc->audio->type_onset = aubio_onset_mkl;
	}
#endif

	trackProc->audio->SetInDevices(temp); //reload the devices
	trackProc->audio->StartCallback();
}

////////////////////////////////////////////////////////
void OptionsDialog::OnAudioBuffer(wxCommandEvent &event)
{
	int temp = ConvToInt( audioBufferBox->GetValue() );
	trackProc->audio->SetAudioBuffer(temp);
}

/////////////////////////////////////////////////////
void OptionsDialog::OnFileText(wxCommandEvent &event)
{
	//here we must decifer the File Path and File name from one string
	if(filePath->GetValue() != wxT("")){
		wxString temp = filePath->GetValue();
		//wxString temp2 = filePath->GetValue();
		mainPanel->initPath = temp.BeforeLast('\\') += wxT("\\");
		mainPanel->initFilename = temp.AfterLast('\\');
	}
	else{
		mainPanel->initPath = wxT("");
		mainPanel->initFilename = wxT("");
	}
}

/////////////////////////////////////////////////////
void OptionsDialog::OnFileSelect(GButtonEvent &event)
{
	wxStandardPaths stdPath; 
    wxString fileLocation = stdPath.GetExecutablePath(); 
    fileLocation = wxFileName(fileLocation).GetPath() + wxT("/Kits");

	wxFileDialog fileDlg(this, wxString(wxT("Load Track On Startup")), fileLocation, wxString(wxT("")), 
		                                    wxString(wxT("eTrigger Data (*.etd)|*.etd")), wxFD_OPEN | wxFD_FILE_MUST_EXIST, wxDefaultPosition);

	if(fileDlg.ShowModal() == wxID_OK){
		wxString temp;
		temp = fileDlg.GetDirectory();
		temp += wxT("\\");
		temp += fileDlg.GetFilename();
		filePath->SetValue(temp);
		return;
	}
	else{
		filePath->SetValue(wxT(""));
	}
	//if we get here, there was an error, or we canceled
}

//////////////////////////////////////////////////////////////
void OptionsDialog::OnMouseSensitivity(GNumberBoxEvent &event)
{
	trackProc->mouseSensitivity = ConvToInt( mouseSenseBox->GetValue() );
}

/////////////////////////////////////////////////////////////
void OptionsDialog::OnJoystickPolling(GNumberBoxEvent &event)
{
	mainPanel->joystick->pollSpeed = ConvToInt( joyPolling->GetValue() );
	mainPanel->joystick->Reload();
}

/////////////////////////////////////////////////////
void OptionsDialog::OnJoyMinX(GNumberBoxEvent &event)
{
	int temp;
	joyMinXBox->GetValue().ToLong((long *) &temp);
	mainPanel->joystick->SetMinX(temp);
}

/////////////////////////////////////////////////////
void OptionsDialog::OnJoyMinY(GNumberBoxEvent &event)
{
	int temp;
	joyMinYBox->GetValue().ToLong((long *) &temp);
	mainPanel->joystick->SetMinY(temp);
}

/////////////////////////////////////////////////////
void OptionsDialog::OnJoyMinZ(GNumberBoxEvent &event)
{
	int temp;
	joyMinZBox->GetValue().ToLong((long *) &temp);
	mainPanel->joystick->SetMinZ(temp);
}

/////////////////////////////////////////////////////
void OptionsDialog::OnJoyMinR(GNumberBoxEvent &event)
{
	int temp;
	joyMinRBox->GetValue().ToLong((long *) &temp);
	mainPanel->joystick->SetMinR(temp);
}

/////////////////////////////////////////////////////
void OptionsDialog::OnJoyMinU(GNumberBoxEvent &event)
{
	int temp;
	joyMinUBox->GetValue().ToLong((long *) &temp);
	mainPanel->joystick->SetMinU(temp);
}

/////////////////////////////////////////////////////
void OptionsDialog::OnJoyMinV(GNumberBoxEvent &event)
{
	int temp;
	joyMinVBox->GetValue().ToLong((long *) &temp);
	mainPanel->joystick->SetMinV(temp);
}

/////////////////////////////////////////////////////
void OptionsDialog::OnJoyMaxX(GNumberBoxEvent &event)
{
	int temp;
	joyMaxXBox->GetValue().ToLong((long *) &temp);
	mainPanel->joystick->SetMaxX(temp);
}

/////////////////////////////////////////////////////
void OptionsDialog::OnJoyMaxY(GNumberBoxEvent &event)
{
	int temp;
	joyMaxYBox->GetValue().ToLong((long *) &temp);
	mainPanel->joystick->SetMaxY(temp);
}

/////////////////////////////////////////////////////
void OptionsDialog::OnJoyMaxZ(GNumberBoxEvent &event)
{
	int temp;
	joyMaxZBox->GetValue().ToLong((long *) &temp);
	mainPanel->joystick->SetMaxZ(temp);
}

/////////////////////////////////////////////////////
void OptionsDialog::OnJoyMaxR(GNumberBoxEvent &event)
{
	int temp;
	joyMaxRBox->GetValue().ToLong((long *) &temp);
	mainPanel->joystick->SetMaxR(temp);
}

/////////////////////////////////////////////////////
void OptionsDialog::OnJoyMaxU(GNumberBoxEvent &event)
{
	int temp;
	joyMaxUBox->GetValue().ToLong((long *) &temp);
	mainPanel->joystick->SetMaxU(temp);
}

/////////////////////////////////////////////////////
void OptionsDialog::OnJoyMaxV(GNumberBoxEvent &event)
{
	int temp;
	joyMaxVBox->GetValue().ToLong((long *) &temp);
	mainPanel->joystick->SetMaxV(temp);
}

///////////////////////////////////////////////////////
void OptionsDialog::OnJoyMaxDetect(GButtonEvent &event)
{
	joyMaxDetect->Hide();
	joyMaxReset->Show();
	joyMaxOk->Show();
	joyMaxCancel->Show();

	mainPanel->joystick->DetectMaxAxes();

	mainPanel->joystick->SetMinX(0);
	joyMinXBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->detectMinX));
	mainPanel->joystick->SetMinY(0);
	joyMinYBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->detectMinY));
	mainPanel->joystick->SetMinZ(0);
	joyMinZBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->detectMinZ));
	mainPanel->joystick->SetMinR(0);
	joyMinRBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->detectMinR));
	mainPanel->joystick->SetMinU(0);
	joyMinUBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->detectMinU));
	mainPanel->joystick->SetMinV(0);
	joyMinVBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->detectMinV));

	mainPanel->joystick->SetMaxX(65000);
	joyMaxXBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->detectMaxX));
	mainPanel->joystick->SetMaxY(65000);
	joyMaxYBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->detectMaxY));
	mainPanel->joystick->SetMaxZ(65000);
	joyMaxZBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->detectMaxZ));
	mainPanel->joystick->SetMaxR(65000);
	joyMaxRBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->detectMaxR));
	mainPanel->joystick->SetMaxU(65000);
	joyMaxUBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->detectMaxU));
	mainPanel->joystick->SetMaxV(65000);
	joyMaxVBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->detectMaxV));
}

//////////////////////////////////////////////////////
void OptionsDialog::OnJoyMaxReset(GButtonEvent &event)
{
	mainPanel->joystick->ResetMaxAxes();

	joyMinXBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->detectMinX));
	joyMinYBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->detectMinY));
	joyMinZBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->detectMinZ));
	joyMinRBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->detectMinR));
	joyMinUBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->detectMinU));
	joyMinVBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->detectMinV));

	joyMaxXBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->detectMaxX));
	joyMaxYBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->detectMaxY));
	joyMaxZBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->detectMaxZ));
	joyMaxRBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->detectMaxR));
	joyMaxUBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->detectMaxU));
	joyMaxVBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->detectMaxV));
}

///////////////////////////////////////////////////
void OptionsDialog::OnJoyMaxOk(GButtonEvent &event)
{
	joyMaxDetect->Show();
	joyMaxReset->Hide();
	joyMaxOk->Hide();
	joyMaxCancel->Hide();

	int temp;
	joyMinXBox->GetValue().ToLong((long *) &temp);
	mainPanel->joystick->SetMinX(temp);
	joyMinX = temp;
	joyMinYBox->GetValue().ToLong((long *) &temp);
	mainPanel->joystick->SetMinY(temp);
	joyMinY = temp;
	joyMinZBox->GetValue().ToLong((long *) &temp);
	mainPanel->joystick->SetMinZ(temp);
	joyMinZ = temp;
	joyMinRBox->GetValue().ToLong((long *) &temp);
	mainPanel->joystick->SetMinR(temp);
	joyMinR = temp;
	joyMinUBox->GetValue().ToLong((long *) &temp);
	mainPanel->joystick->SetMinU(temp);
	joyMinU = temp;
	joyMinVBox->GetValue().ToLong((long *) &temp);
	mainPanel->joystick->SetMinV(temp);
	joyMinV = temp;

	//int temp;
	joyMaxXBox->GetValue().ToLong((long *) &temp);
	mainPanel->joystick->SetMaxX(temp);
	joyMaxX = temp;
	joyMaxYBox->GetValue().ToLong((long *) &temp);
	mainPanel->joystick->SetMaxY(temp);
	joyMaxY = temp;
	joyMaxZBox->GetValue().ToLong((long *) &temp);
	mainPanel->joystick->SetMaxZ(temp);
	joyMaxZ = temp;
	joyMaxRBox->GetValue().ToLong((long *) &temp);
	mainPanel->joystick->SetMaxR(temp);
	joyMaxR = temp;
	joyMaxUBox->GetValue().ToLong((long *) &temp);
	mainPanel->joystick->SetMaxU(temp);
	joyMaxU = temp;
	joyMaxVBox->GetValue().ToLong((long *) &temp);
	mainPanel->joystick->SetMaxV(temp);
	joyMaxV = temp;

	mainPanel->joystick->detectMaxAxes = false;
}

///////////////////////////////////////////////////////
void OptionsDialog::OnJoyMaxCancel(GButtonEvent &event)
{
	joyMaxDetect->Show();
	joyMaxReset->Hide();
	joyMaxOk->Hide();
	joyMaxCancel->Hide();

	mainPanel->joystick->detectMaxAxes = false;

	mainPanel->joystick->SetMinX(joyMinX);
	mainPanel->joystick->SetMinY(joyMinY);
	mainPanel->joystick->SetMinZ(joyMinZ);
	mainPanel->joystick->SetMinR(joyMinR);
	mainPanel->joystick->SetMinU(joyMinU);
	mainPanel->joystick->SetMinV(joyMinV);
	
	joyMinXBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->GetMinX()));
	joyMinYBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->GetMinY()));
	joyMinZBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->GetMinZ()));
	joyMinRBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->GetMinR()));
	joyMinUBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->GetMinU()));
	joyMinVBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->GetMinV()));

	mainPanel->joystick->SetMaxX(joyMaxX);
	mainPanel->joystick->SetMaxY(joyMaxY);
	mainPanel->joystick->SetMaxZ(joyMaxZ);
	mainPanel->joystick->SetMaxR(joyMaxR);
	mainPanel->joystick->SetMaxU(joyMaxU);
	mainPanel->joystick->SetMaxV(joyMaxV);
	
	joyMaxXBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->GetMaxX()));
	joyMaxYBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->GetMaxY()));
	joyMaxZBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->GetMaxZ()));
	joyMaxRBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->GetMaxR()));
	joyMaxUBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->GetMaxU()));
	joyMaxVBox->SetValue(wxString::Format(wxT("%d"), mainPanel->joystick->GetMaxV()));
}

////////////////////////////////////////////////////////////
void OptionsDialog::OnRetriggerSafty(GNumberBoxEvent &event)
{
	retriggerSaftyBox->GetValue().ToLong((long *) &trackProc->retriggerSafty );
}

////////////////////////////////////////////////////////////////
void OptionsDialog::OnRetriggerThreshold(GNumberBoxEvent &event)
{
	retriggerThresholdBox->GetValue().ToLong((long *) &trackProc->retriggerThreshold );
}

////////////////////////////////////////////////////////////
void OptionsDialog::OnFlamAdjustment(GNumberBoxEvent &event)
{
	flamAdjustmentBox->GetValue().ToLong((long *) &trackProc->flamAdjustment );
}

////////////////////////////////////////////////////////////
void OptionsDialog::OnRollAdjustment(GNumberBoxEvent &event)
{
	rollAdjustmentBox->GetValue().ToLong((long *) &trackProc->rollAdjustment );
}

/////////////////////////////////////////////////////
void OptionsDialog::OnToolTips(wxCommandEvent &event)
{
	mainPanel->toolTips = toolTipsBox->GetValue();
	if(mainPanel->toolTips){
		wxToolTip::Enable(true);
	    wxToolTip::SetDelay(500);
	}
	else{
		wxToolTip::Enable(false);
	}
}

//////////////////////////////////////////////////////
void OptionsDialog::OnMidiBleed(wxCommandEvent &event)
{
	trackProc->midiBleed = midiBleedBox->GetValue();
}

/////////////////////////////////////////////////////////
void OptionsDialog::OnMidiChannels(wxCommandEvent &event)
{
	trackProc->midiChannel[1] = midiChannel1Box->GetValue();
	trackProc->midiChannel[2] = midiChannel2Box->GetValue();
	trackProc->midiChannel[3] = midiChannel3Box->GetValue();
	trackProc->midiChannel[4] = midiChannel4Box->GetValue();
	trackProc->midiChannel[5] = midiChannel5Box->GetValue();
	trackProc->midiChannel[6] = midiChannel6Box->GetValue();
	trackProc->midiChannel[7] = midiChannel7Box->GetValue();
	trackProc->midiChannel[8] = midiChannel8Box->GetValue();
	trackProc->midiChannel[9] = midiChannel9Box->GetValue();
	trackProc->midiChannel[10] = midiChannel10Box->GetValue();
	trackProc->midiChannel[11] = midiChannel11Box->GetValue();
	trackProc->midiChannel[12] = midiChannel12Box->GetValue();
	trackProc->midiChannel[13] = midiChannel13Box->GetValue();
	trackProc->midiChannel[14] = midiChannel14Box->GetValue();
	trackProc->midiChannel[15] = midiChannel15Box->GetValue();
	trackProc->midiChannel[16] = midiChannel16Box->GetValue();
}

///////////////////////////////////////////////////////
void OptionsDialog::OnFolderText(wxCommandEvent &event)
{

}

///////////////////////////////////////////////////////
void OptionsDialog::OnFolderSelect(GButtonEvent &event)
{
	const wxString& dir = wxDirSelector(wxT("Choose the sample folder"), mainPanel->samples->sampleDir, wxSTAY_ON_TOP, wxDefaultPosition, 0);
	if ( !dir.empty() )
	{
		folderPath->SetValue(dir);
		mainPanel->samples->sampleDir = dir;
	}
}

////////////////////////////////////////////////
void OptionsDialog::OnMouse(wxMouseEvent &event)
{
	ok->SetFocus();
}
