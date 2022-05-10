//// MidiCCDialog.cpp ///////////////////////////////////////////////////////////
//
//  This setting window is LIVE. Any changes made while the program is running
//  are live to the track so the user may sample how the settings will react before
//  pressing ok. If the user hits cancel, the track data is reverted back to what
//  it was just before the settings window was opened.
//
//  The many GImages ,topEdge and leftEdge, are made to be easily replaceable 
//  by new buttons in the future since they are either the same width or height. 
//
///////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "MidiCCDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/////////////////////////////////////
BEGIN_EVENT_TABLE(MidiCCDialog, wxDialog)
	EVT_GBUTTON(205,    MidiCCDialog::OnInput)
	EVT_TEXT(1000,      MidiCCDialog::OnDrumTypeSelect)
	EVT_GBUTTON(220,    MidiCCDialog::OnPedalEvents)
	EVT_GBUTTON(206,    MidiCCDialog::OnOutput)
    EVT_GBUTTON(202,    MidiCCDialog::OnLearn)
	EVT_GBUTTON(203,    MidiCCDialog::OnOk)
	EVT_GBUTTON(204,    MidiCCDialog::OnCancel)
	EVT_LEARN(wxID_ANY, MidiCCDialog::OnLearnEvent)
	EVT_GNUMBERBOX(211, MidiCCDialog::OnMidiOutNote)
	EVT_GNUMBERBOX(212, MidiCCDialog::OnMidiOutChannel)
	EVT_GNUMBERBOX(217, MidiCCDialog::OnLowCompressor) 
	EVT_GNUMBERBOX(218, MidiCCDialog::OnHighCompressor) 
	EVT_CHECKBOX(219,   MidiCCDialog::OnCCReverse)
	EVT_LEFT_DOWN (     MidiCCDialog::OnMouse)
	EVT_CLOSE(          MidiCCDialog::OnClose) 

	EVT_CHECKBOX(221,   MidiCCDialog::OnPedalEventBox)
	EVT_GNUMBERBOX(222, MidiCCDialog::OnPedalEventThreshold)
	EVT_GNUMBERBOX(223, MidiCCDialog::OnPedalEventNote)
	EVT_GNUMBERBOX(224, MidiCCDialog::OnPedalEventVolume)
	EVT_GNUMBERBOX(225, MidiCCDialog::OnPedalSpeedIntensity)

END_EVENT_TABLE() 

//////////////////////////////////////////
MidiCCDialog::MidiCCDialog(MidiCC* parent) 
	     :wxDialog(parent, -1, wxT("Track Settings"), wxDefaultPosition, wxSize(430, 510), wxDEFAULT_DIALOG_STYLE)
{
	InitVariables();

	CentreOnScreen(wxBOTH);

	midiCC = parent; //link to Trigger parent to access variables
	SetTitle(wxString::Format(wxT("Track %d Settings"), midiCC->trackNum));
	
#ifdef WIN32
	SetBackgroundColour(wxColour(30,30,30));
#endif //WIN32
#ifdef MAC
	wxPanel *background = new wxPanel(this, -1, wxPoint(0,0), this->GetSize(), 0, wxT(""));
	background->SetBackgroundColour(wxColour(30,30,30));
#endif //MAC
		
	//corners and edges
	topLeftCornerSideImage = new GImage(this, -1, wxPoint(120,40), TopLeftCornerSide_xpm);
	topLeftCornerTopImage = new GImage(this, -1, wxPoint(125,39), TopLeftCornerTop_xpm);
	topEdge1Image = new GImage(this, -1, wxPoint(155,39), TopEdge_xpm);
	topEdge2Image = new GImage(this, -1, wxPoint(229,39), TopEdge_xpm);
	topEdge3Image = new GImage(this, -1, wxPoint(303,39), TopEdge_xpm);
	//leftEdge1 = new GImage(this, -1, wxPoint(120,140), LeftEdge_xpm);
	leftEdge2Image = new GImage(this, -1, wxPoint(120,173), LeftEdge_xpm);
	leftEdge3Image = new GImage(this, -1, wxPoint(120,206), LeftEdge_xpm);
	leftEdge4Image = new GImage(this, -1, wxPoint(120,239), LeftEdge_xpm);
	leftEdge5Image = new GImage(this, -1, wxPoint(120,272), LeftEdge_xpm);
	leftEdge6Image = new GImage(this, -1, wxPoint(120,305), LeftEdge_xpm);
	leftEdge7Image = new GImage(this, -1, wxPoint(120,338), LeftEdge_xpm);
	leftEdge8Image = new GImage(this, -1, wxPoint(120,371), LeftEdge_xpm);

	//buttons
	inputButton = new GButton(this, 205, wxPoint(10,74), Input_xpm , input_hover_xpm);
	inputSelectedButton = new GButton(this, -1, wxPoint(10,74), Input_Selected_xpm);
	pedalEventsButton = new GButton(this, 220, wxPoint(10,107), pedalEvents_xpm , pedalEvents_hover_xpm);
	pedalEventsSelectedButton = new GButton(this, -1, wxPoint(10,107), pedalEvents_selected_xpm);
	outputButton = new GButton(this, 206, wxPoint(10,140), Output_xpm , Output_Hover_xpm);
    outputSelectedButton = new GButton(this, -1, wxPoint(10,140), Output_Selected_xpm);
	okButton = new GButton(this, 203, wxPoint(264,445), ok2_xpm, ok2_hover_xpm, ok2_click_xpm); 
	cancelButton = new GButton(this, 204, wxPoint(335,445), cancel2_xpm, cancel2_hover_xpm, cancel2_click_xpm);

	///////////////////// Panels ////////////////
	//// Input Panel
	inputPanel = new wxPanel(this, -1, wxPoint(125, 45), wxSize(282,388), 0, wxT(""));
	inputPanel->SetBackgroundColour(wxColour(99,99,99));
	#ifdef WIN32
	inputPanel->Connect(-1, wxEVT_LEFT_DOWN, wxMouseEventHandler(MidiCCDialog::OnMouse), NULL, this);
	#endif
	learnButton = new GButton(inputPanel, 202, wxPoint(105,15), learn_xpm, Learn_Hover_xpm, Learn_Click_xpm);
	deviceText = new wxStaticText(inputPanel, -1, wxT(""), wxPoint(50, 195), wxSize(200, 20), wxALIGN_CENTRE , wxT(""));
	infoText = new wxStaticText(inputPanel, -1, wxT(""), wxPoint(50, 210), wxSize(200, 20), wxALIGN_CENTRE , wxT(""));
	wxStaticText *drumTypeText = new wxStaticText(inputPanel, -1, wxT("Drum Type"), wxPoint(73,242), wxSize(60,20), 0, wxT(""));
	drumTypeBox = new wxComboBox(inputPanel, 1000, wxT(""), wxPoint(133, 240), wxSize(100,20), GetDrumTypes(), wxCB_READONLY, wxDefaultValidator, wxT(""));
	mouseImage = new GImage(inputPanel, -1, wxPoint(60,65), Mouse_xpm); mouseImage->Hide();
	keyboardImage = new GImage(inputPanel, -1, wxPoint(45,50), keyboard_xpm); keyboardImage->Hide();
	midiDeviceImage = new GImage(inputPanel, -1, wxPoint(40,60), MidiDevice_xpm); midiDeviceImage->Hide();
	joystickImage = new GImage(inputPanel, -1, wxPoint(40,50), Joystick_xpm); joystickImage->Hide();
	
	//// Pedal Events Panel
	pedalEventsPanel = new wxPanel(this, -1, wxPoint(125, 45), wxSize(282,388), 0, wxT(""));
	pedalEventsPanel->SetBackgroundColour(wxColour(99,99,99));

	pedalEventBox = new wxCheckBox(pedalEventsPanel, 221, wxT("Enable Pedal Down Event"), wxPoint(20,20), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	pedalEventThresholdBox = new GNumberBox(pedalEventsPanel, 222, wxT(""), wxPoint(20, 40), wxSize(30, 15));
	pedalEventThresholdBox->SetMinMax(0, 127);
	pedalEventThresholdBox->SetDefault(0);
	wxStaticText *pedalEventThresholdText = new wxStaticText(pedalEventsPanel, -1, wxT("Pedal Event Threshold"), wxPoint(60, 40), wxSize(150, 20), 0, wxT(""));
	pedalEventNoteBox = new GNumberBox(pedalEventsPanel, 223, wxT(""), wxPoint(20, 60), wxSize(30, 15));
	pedalEventNoteBox->SetMinMax(1, 127);
	pedalEventNoteBox->SetDefault(1);
	wxStaticText *pedalEventNoteText = new wxStaticText(pedalEventsPanel, -1, wxT("Pedal Event Note"), wxPoint(60, 60), wxSize(150, 20), 0, wxT(""));
	pedalEventVolumeBox = new GNumberBox(pedalEventsPanel, 224, wxT(""), wxPoint(20, 80), wxSize(30, 15));
	pedalEventVolumeBox->SetMinMax(0, 254);
	pedalEventVolumeBox->SetDefault(127);
	wxStaticText *pedalEventVolumeText = new wxStaticText(pedalEventsPanel, -1, wxT("Pedal Event Volume"), wxPoint(60, 80), wxSize(150, 20), 0, wxT(""));
	pedalSpeedIntensityBox = new GNumberBox(pedalEventsPanel, 225, wxT(""), wxPoint(20, 100), wxSize(40, 15));
	pedalSpeedIntensityBox->SetMinMax(0, 1000);
	pedalSpeedIntensityBox->SetDefault(100);
	wxStaticText *pedalSpeedIntensityText = new wxStaticText(pedalEventsPanel, -1, wxT("Pedal Speed Intensity"), wxPoint(70, 100), wxSize(150, 20), 0, wxT(""));

	//// Output Panel
	outputPanel = new wxPanel(this, -1, wxPoint(125, 45), wxSize(282,388), 0, wxT(""));
	outputPanel->SetBackgroundColour(wxColour(99,99,99));
	#ifdef WIN32
	outputPanel->Connect(-1, wxEVT_LEFT_DOWN, wxMouseEventHandler(MidiCCDialog::OnMouse), NULL, this);
	#endif
	wxStaticText *midiNoteText = new wxStaticText(outputPanel, -1, wxT("Midi Note"), wxPoint(60, 60), wxSize(80, 20), 0, wxT(""));
	wxStaticText *midiChannelText = new wxStaticText(outputPanel, -1, wxT("Midi Channel"), wxPoint(60, 80), wxSize(80, 20), 0, wxT(""));
	wxStaticText *lowCompressorText = new wxStaticText(outputPanel, -1, wxT("Limiter (low)"), wxPoint(60,100), wxSize(80, 20),0, wxT(""));
	wxStaticText *highCompressorText = new wxStaticText(outputPanel, -1, wxT("Limiter (high)"), wxPoint(60,120), wxSize(80, 20),0, wxT(""));
	midiOutNoteBox = new GNumberBox(outputPanel, 211, wxT(""), wxPoint(20, 60), wxSize(30, 15));
	midiOutNoteBox->SetMinMax(0, 127);
	midiOutNoteBox->SetDefault(4);
	midiOutChannelBox = new GNumberBox(outputPanel, 212, wxT(""), wxPoint(20, 80), wxSize(30, 15));
	midiOutChannelBox->SetMinMax(1,32); //Should be limited to 10, but this way we can set output type, cc or pc
	midiOutChannelBox->SetDefault(10);
	lowCompressorBox = new GNumberBox(outputPanel, 217, wxT(""), wxPoint(20,100), wxSize(30,15));
	lowCompressorBox->SetMinMax(0,127);
	lowCompressorBox->SetDefault(0);
	highCompressorBox = new GNumberBox(outputPanel, 218, wxT(""), wxPoint(20,120), wxSize(30,15));
	highCompressorBox->SetMinMax(0,127);
	highCompressorBox->SetDefault(127);
	ccReverseBox = new wxCheckBox(outputPanel, 219, wxT("Reverse CC"), wxPoint(20,140), wxDefaultSize, 0, wxDefaultValidator, wxT(""));

	VarsToTemp();
	VarsToDlg();
	UpdateSelection(wxT("input")); //make default input
}

/////////////////////////////
MidiCCDialog::~MidiCCDialog()
{	
}

//////////////////////////////////
void MidiCCDialog::InitVariables()
{
	midiCC = NULL;
	deviceName = wxT("");
	inputDetails = wxT("");
	inputCode = NULL;
	drumType = NULL;
	outputNote = NULL;
	outputChannel = NULL;
	lowCompressor = NULL;
	highCompressor = NULL;
	ccReverse = NULL;
	pedalDownEvent = NULL;
	pedalDownThreshold = NULL;
	pedalVolume = NULL;
	pedalNote = NULL;
	pedalSpeedIntensity = NULL;

	topLeftCornerSideImage = NULL;
	topLeftCornerTopImage = NULL;
	topEdge1Image = NULL;
	topEdge2Image = NULL;
	topEdge3Image = NULL;
	leftEdge1Image = NULL;
	leftEdge2Image = NULL;
	leftEdge3Image = NULL;
	leftEdge4Image = NULL;
	leftEdge5Image = NULL;
	leftEdge6Image = NULL;
	leftEdge7Image = NULL;
	leftEdge8Image = NULL;

	inputButton = NULL;
	inputSelectedButton = NULL;
	pedalEventsButton = NULL;
	pedalEventsSelectedButton = NULL;
	outputButton = NULL;
	outputSelectedButton = NULL;
	okButton = NULL;
	cancelButton = NULL;

	inputPanel = NULL;
	learnButton = NULL;
	deviceText = NULL;
	infoText = NULL;
	drumTypeBox = NULL;
	mouseImage = NULL;
	keyboardImage = NULL;
	midiDeviceImage = NULL;
	joystickImage = NULL;

	pedalEventsPanel = NULL;
	pedalEventBox = NULL;
	pedalEventThresholdBox = NULL;
	pedalEventNoteBox = NULL;
	pedalEventVolumeBox = NULL;
	pedalSpeedIntensityBox = NULL;

	outputPanel = NULL;
	midiOutNoteBox = NULL;
	midiOutChannelBox = NULL;
	lowCompressorBox = NULL;
	highCompressorBox = NULL;
	ccReverseBox = NULL;
}

///////////////////////////////
void MidiCCDialog::VarsToTemp()
{
	//Store the data temporarily in case we hit cancel and want to revert back.
	drumType = midiCC->trackProc->n[midiCC->trackNum].drumType;
	deviceName = midiCC->trackProc->n[midiCC->trackNum].deviceName[0];
	inputDetails = midiCC->trackProc->n[midiCC->trackNum].inputDetails[0];
	inputCode = midiCC->trackProc->n[midiCC->trackNum].inputCode[0];
	outputNote = midiCC->trackProc->n[midiCC->trackNum].outputNote[0];
	outputChannel = midiCC->trackProc->n[midiCC->trackNum].outputChannel[0]; 
	lowCompressor = midiCC->trackProc->n[midiCC->trackNum].lowCompressor[0];
	highCompressor = midiCC->trackProc->n[midiCC->trackNum].highCompressor[0];
	ccReverse = midiCC->trackProc->n[midiCC->trackNum].ccReverse;

	pedalDownEvent = midiCC->trackProc->n[midiCC->trackNum].pedalDownEvent;
	pedalDownThreshold = midiCC->trackProc->n[midiCC->trackNum].pedalDownThreshold;
	pedalVolume = midiCC->trackProc->n[midiCC->trackNum].pedalVolume;
	pedalNote = midiCC->trackProc->n[midiCC->trackNum].pedalNote;
	pedalSpeedIntensity = midiCC->trackProc->n[midiCC->trackNum].pedalSpeedIntensity;
}

////////////////////////////
void MidiCCDialog::VarsToDlg()
{
	//place the track Database data onto the dialog
	deviceText->SetLabel(midiCC->trackProc->n[midiCC->trackNum].deviceName[0]);
	infoText->SetLabel(midiCC->trackProc->n[midiCC->trackNum].inputDetails[0]);
	
	drumTypeBox->SetSelection(midiCC->trackProc->n[midiCC->trackNum].drumType);
	midiOutNoteBox->SetValue(wxString::Format(wxT("%d"), midiCC->trackProc->n[midiCC->trackNum].outputNote[0]));
	midiOutChannelBox->SetValue(wxString::Format(wxT("%d"), midiCC->trackProc->n[midiCC->trackNum].outputChannel[0]));
	lowCompressorBox->SetValue(wxString::Format(wxT("%d"), midiCC->trackProc->n[midiCC->trackNum].lowCompressor[0]));
	highCompressorBox->SetValue(wxString::Format(wxT("%d"), midiCC->trackProc->n[midiCC->trackNum].highCompressor[0]));
	ccReverseBox->SetValue(midiCC->trackProc->n[midiCC->trackNum].ccReverse);

	pedalEventBox->SetValue(midiCC->trackProc->n[midiCC->trackNum].pedalDownEvent);
	pedalEventThresholdBox->SetValue(wxString::Format(wxT("%d"), midiCC->trackProc->n[midiCC->trackNum].pedalDownThreshold));
	pedalEventNoteBox->SetValue(wxString::Format(wxT("%d"), midiCC->trackProc->n[midiCC->trackNum].pedalNote));
	pedalEventVolumeBox->SetValue(wxString::Format(wxT("%d"), midiCC->trackProc->n[midiCC->trackNum].pedalVolume));
	pedalSpeedIntensityBox->SetValue(wxString::Format(wxT("%d"), midiCC->trackProc->n[midiCC->trackNum].pedalSpeedIntensity));

	UpdateInputImage(0);
}

////////////////////////////
void MidiCCDialog::TempToVars()
{
	//Transfer the temporary back if we hit cancel
	midiCC->trackProc->n[midiCC->trackNum].drumType = drumType;
	midiCC->trackProc->n[midiCC->trackNum].deviceName[0] = deviceName;
	midiCC->trackProc->n[midiCC->trackNum].inputDetails[0] = inputDetails;
	midiCC->trackProc->n[midiCC->trackNum].inputCode[0] = inputCode;
	midiCC->trackProc->n[midiCC->trackNum].outputNote[0] = outputNote;
	midiCC->trackProc->n[midiCC->trackNum].outputChannel[0] = outputChannel;
	midiCC->trackProc->n[midiCC->trackNum].lowCompressor[0] = lowCompressor;
	midiCC->trackProc->n[midiCC->trackNum].highCompressor[0] = highCompressor;
	midiCC->trackProc->n[midiCC->trackNum].ccReverse = ccReverse;

	midiCC->trackProc->n[midiCC->trackNum].pedalDownEvent = pedalDownEvent;
	midiCC->trackProc->n[midiCC->trackNum].pedalDownThreshold = pedalDownThreshold;
	midiCC->trackProc->n[midiCC->trackNum].pedalVolume = pedalVolume;
	midiCC->trackProc->n[midiCC->trackNum].pedalNote = pedalNote;
	midiCC->trackProc->n[midiCC->trackNum].pedalSpeedIntensity = pedalSpeedIntensity;
}

////////////////////////////
void MidiCCDialog::TempToDlg()
{
	//place the track Database data onto the dialog
	deviceText->SetLabel(deviceName);
	infoText->SetLabel(inputDetails);
	drumTypeBox->SetSelection(drumType);
	midiOutNoteBox->SetValue(wxString::Format(wxT("%d"), outputNote));
	midiOutChannelBox->SetValue(wxString::Format(wxT("%d"), outputChannel));
	lowCompressorBox->SetValue(wxString::Format(wxT("%d"), lowCompressor));
	highCompressorBox->SetValue(wxString::Format(wxT("%d"), highCompressor));
	ccReverseBox->SetValue(ccReverse);

	pedalEventBox->SetValue(pedalDownEvent);
	pedalEventThresholdBox->SetValue(wxString::Format(wxT("%d"), pedalDownThreshold));
	pedalEventNoteBox->SetValue(wxString::Format(wxT("%d"), pedalNote));
	pedalEventVolumeBox->SetValue(wxString::Format(wxT("%d"), pedalVolume));
	pedalSpeedIntensityBox->SetValue(wxString::Format(wxT("%d"), pedalSpeedIntensity));

	UpdateInputImage(0);
}

/////////////////////////////////////////////
void MidiCCDialog::OnInput(GButtonEvent &event)
{
	UpdateSelection(wxT("input"));
}

/////////////////////////////////////////////
void MidiCCDialog::OnPedalEvents(GButtonEvent &event)
{
	UpdateSelection(wxT("pedalEvents"));
}

//////////////////////////////////////////////
void MidiCCDialog::OnOutput(GButtonEvent &event)
{
	UpdateSelection(wxT("output"));
}

//////////////////////////////////////////
void MidiCCDialog::OnOk(GButtonEvent &event)
{
	//if(midiCC->trackProc->preLoad){
	VarsToTemp();
	Hide();
	//}	else{Destroy();}
}

//////////////////////////////////////////////
void MidiCCDialog::OnCancel(GButtonEvent &event)
{
	Close();
}

void MidiCCDialog::OnClose(wxCloseEvent &event)
{
	TempToVars();
	TempToDlg(); 
	//if(midiCC->trackProc->preLoad)
	//{
	Hide();
	//}	else{Destroy();}
}

void MidiCCDialog::UpdateInputImage(bool hideAll)
{
	//Device Images
	if(midiCC->trackProc->n[midiCC->trackNum].inputCode[0] >= 100000 && 
	   midiCC->trackProc->n[midiCC->trackNum].inputCode[0] < 200000 && !hideAll){midiDeviceImage->Show();}
	else{midiDeviceImage->Hide();}

	if(midiCC->trackProc->n[midiCC->trackNum].inputCode[0] >= 300000 && 
	   midiCC->trackProc->n[midiCC->trackNum].inputCode[0]  < 400000 && !hideAll){joystickImage->Show();}
	else{joystickImage->Hide();}

	if(midiCC->trackProc->n[midiCC->trackNum].inputCode[0] >= 500000 &&
	   midiCC->trackProc->n[midiCC->trackNum].inputCode[0]  < 600000 && !hideAll){mouseImage->Show();}
	else{mouseImage->Hide();}

	if(midiCC->trackProc->n[midiCC->trackNum].inputCode[0] >= 400000 && 
	   midiCC->trackProc->n[midiCC->trackNum].inputCode[0]  < 500000 && !hideAll){keyboardImage->Show();}
	else{keyboardImage->Hide();}
}

/////////////////////////////////////////////////
void MidiCCDialog::UpdateSelection(wxString string)
{
	if(string == wxT("input")){
		inputSelectedButton->Show();
		inputPanel->Show();
		pedalEventsButton->Show();
		outputButton->Show();
		inputButton->Hide();
		pedalEventsSelectedButton->Hide();
		pedalEventsPanel->Hide();
		outputSelectedButton->Hide();
		outputPanel->Hide();

	}

	if(string == wxT("pedalEvents")){
		inputButton->Show();
		pedalEventsSelectedButton->Show();
		pedalEventsPanel->Show();
		outputButton->Show();
		inputSelectedButton->Hide();
		inputPanel->Hide();
		pedalEventsButton->Hide();
		outputSelectedButton->Hide();
		outputPanel->Hide();		
	}

	if(string == wxT("output")){
		inputButton->Show();
		pedalEventsButton->Show();
		outputSelectedButton->Show();
		outputPanel->Show();
		inputSelectedButton->Hide();
		inputPanel->Hide();
		pedalEventsSelectedButton->Hide();
		pedalEventsPanel->Hide();
		outputButton->Hide();	
	}
}

////////////////////////////////////////////////////////
void MidiCCDialog::OnDrumTypeSelect(wxCommandEvent &event)
{
	midiCC->trackProc->n[midiCC->trackNum].drumType = drumTypeBox->GetSelection();
	learnButton->SetFocus();
}

/////////////////////////////////////////////////////
void MidiCCDialog::OnMidiOutNote(GNumberBoxEvent &event)
{
    midiCC->trackProc->n[midiCC->trackNum].outputNote[0] = ConvToInt( midiOutNoteBox->GetValue() );
}

////////////////////////////////////////////////////////
void MidiCCDialog::OnMidiOutChannel(GNumberBoxEvent &event)
{
	midiCC->trackProc->n[midiCC->trackNum].outputChannel[0] = ConvToInt( midiOutChannelBox->GetValue() );
}

///////////////////////////////////////////////////
void MidiCCDialog::OnLowCompressor(GNumberBoxEvent &event) 
{
	int temp = ConvToInt( lowCompressorBox->GetValue() );

	if(temp < midiCC->trackProc->n[midiCC->trackNum].highCompressor[0]){
		midiCC->trackProc->n[midiCC->trackNum].lowCompressor[0] = ConvToInt( lowCompressorBox->GetValue() );
	}
	else{
		lowCompressorBox->SetValue(wxString::Format(wxT("%d"), midiCC->trackProc->n[midiCC->trackNum].highCompressor[0]-1));
		midiCC->trackProc->n[midiCC->trackNum].lowCompressor[0] = ConvToInt( lowCompressorBox->GetValue() );
	}
}

///////////////////////////////////////////////////
void MidiCCDialog::OnHighCompressor(GNumberBoxEvent &event) 
{
	int temp = ConvToInt( highCompressorBox->GetValue() );

	if(temp > midiCC->trackProc->n[midiCC->trackNum].lowCompressor[0]){
		midiCC->trackProc->n[midiCC->trackNum].highCompressor[0] = ConvToInt( highCompressorBox->GetValue() );
	}
	else{
		highCompressorBox->SetValue(wxString::Format(wxT("%d"), midiCC->trackProc->n[midiCC->trackNum].lowCompressor[0]+1));
		midiCC->trackProc->n[midiCC->trackNum].highCompressor[0] = ConvToInt( highCompressorBox->GetValue() );
	}
}

///////////////////////////////////////////////////
void MidiCCDialog::OnCCReverse(wxCommandEvent &event)
{
	midiCC->trackProc->n[midiCC->trackNum].ccReverse = ccReverseBox->GetValue();	
}

//////////////////////////////////////////////////////
void MidiCCDialog::OnPedalEventBox(wxCommandEvent &event)
{
	midiCC->trackProc->n[midiCC->trackNum].pedalDownEvent = pedalEventBox->GetValue();
}

/////////////////////////////////////////////////////////////
void MidiCCDialog::OnPedalEventThreshold(GNumberBoxEvent &event)
{
	midiCC->trackProc->n[midiCC->trackNum].pedalDownThreshold = ConvToInt( pedalEventThresholdBox->GetValue() );
}

////////////////////////////////////////////////////////
void MidiCCDialog::OnPedalEventNote(GNumberBoxEvent &event)
{
	midiCC->trackProc->n[midiCC->trackNum].pedalNote = ConvToInt( pedalEventNoteBox->GetValue() );
}

//////////////////////////////////////////////////////////
void MidiCCDialog::OnPedalEventVolume(GNumberBoxEvent &event)
{
	midiCC->trackProc->n[midiCC->trackNum].pedalVolume = ConvToInt( pedalEventVolumeBox->GetValue() );
}

//////////////////////////////////////////////////////////
void MidiCCDialog::OnPedalSpeedIntensity(GNumberBoxEvent &event)
{
	midiCC->trackProc->n[midiCC->trackNum].pedalSpeedIntensity = ConvToInt( pedalSpeedIntensityBox->GetValue() );
}

/////////////////////////////////////////////
void MidiCCDialog::OnLearn(GButtonEvent &event)
{
	UpdateInputImage(true);
	deviceText->SetLabel(wxT("Learning . . ."));
	infoText->SetLabel(wxT(""));

	LearnThread *test = new LearnThread(this, midiCC->trackProc->n[midiCC->trackNum].midiType);
}

////////////////////////////////////////////////
void MidiCCDialog::OnLearnEvent(LearnEvent &event)
{
	if(Process::devInfo.deviceName != wxT("")){
		deviceText->SetLabel(Process::devInfo.deviceName);
		infoText->SetLabel(Process::devInfo.inputDetails);
		midiCC->trackProc->n[midiCC->trackNum].deviceName[0] = Process::devInfo.deviceName;
		midiCC->trackProc->n[midiCC->trackNum].inputDetails[0] = Process::devInfo.inputDetails;
		midiCC->trackProc->n[midiCC->trackNum].inputCode[0] = Process::LearnReply;
		UpdateInputImage(0);
	}

	else{
		deviceText->SetLabel(wxT("no device selected"));
		infoText->SetLabel(wxT(""));
		midiCC->trackProc->n[midiCC->trackNum].deviceName[0] = wxT("no device selected");
		midiCC->trackProc->n[midiCC->trackNum].inputDetails[0] = wxT("");
		midiCC->trackProc->n[midiCC->trackNum].inputCode[0] = 0;
		UpdateInputImage(0);
	}	
}

/////////////////////////////////////////////
void MidiCCDialog::OnMouse(wxMouseEvent &event)
{
	okButton->SetFocus();
}
