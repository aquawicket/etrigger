//// TriggerDialog.cpp ///////////////////////////////////////////////////////////
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
#include "TriggerDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////
BEGIN_EVENT_TABLE(TriggerDialog, wxDialog)

    //Main Window Events
	EVT_GBUTTON(205, TriggerDialog::OnInput)
	EVT_GBUTTON(240, TriggerDialog::OnRetrigger)
	EVT_GBUTTON(236, TriggerDialog::OnDynamics)
	EVT_GBUTTON(206, TriggerDialog::OnOutput)
	EVT_GBUTTON(239, TriggerDialog::OnMultiZone)
	EVT_GBUTTON(208, TriggerDialog::OnZone1)
	EVT_GBUTTON(209, TriggerDialog::OnZone2)
	EVT_GBUTTON(210, TriggerDialog::OnZone3)
	EVT_GBUTTON(203, TriggerDialog::OnOk)
	EVT_GBUTTON(204, TriggerDialog::OnCancel)
	EVT_CLOSE(       TriggerDialog::OnClose) 
	EVT_LEFT_DOWN (  TriggerDialog::OnMouse)
	EVT_MOUSEWHEEL(  TriggerDialog::OnMouseWheel)

	//Input Panel Events
    EVT_GBUTTON(202, TriggerDialog::OnLearn)
	EVT_LEARN(-1,    TriggerDialog::OnLearnEvent)
	EVT_TEXT(1000,   TriggerDialog::OnDrumTypeSelect)
	EVT_GKNOB(106,   TriggerDialog::OnKnob)
	EVT_TEXT(207,    TriggerDialog::OnZonesSelect)

	//Retrigger Panel
	EVT_GBUTTON(241,    TriggerDialog::OnRetriggerDetect)
	EVT_GNUMBERBOX(214, TriggerDialog::OnRetriggerBox) 
	EVT_GBUTTON(242,    TriggerDialog::OnRetriggerReset)
	EVT_GBUTTON(243,    TriggerDialog::OnRetriggerOk)
	EVT_GBUTTON(244,    TriggerDialog::OnRetriggerCancel)

	//Dynamics Panel Events
	EVT_GCURVE(237,     TriggerDialog::OnCurve)
	EVT_GSLIDER(255,    TriggerDialog::OnCompressorSlider)
	EVT_GSLIDER(256,    TriggerDialog::OnCutOffSlider)
	EVT_GSLIDER(500,    TriggerDialog::OnLowPercentSlider)
	EVT_GSLIDER(501,    TriggerDialog::OnHighPercentSlider)
	EVT_GNUMBERBOX(221, TriggerDialog::OnAntiMachineGun)
	EVT_CHECKBOX(337,   TriggerDialog::OnMidiCCControlledBox)
	EVT_GNUMBERBOX(238, TriggerDialog::OnMidiCCControlledNumber)
	EVT_GBUTTON(262,    TriggerDialog::OnVelocityDialog)
	EVT_GNUMBERBOX(700, TriggerDialog::OnCrosstalk)

	//Output Panel Events
	EVT_RADIOBUTTON(257, TriggerDialog::OnBasicOutput) 
	EVT_RADIOBUTTON(258, TriggerDialog::OnAlternatingOutput) 
	EVT_RADIOBUTTON(259, TriggerDialog::OnMidiCCControlledOutput) 
	EVT_RADIOBUTTON(260, TriggerDialog::OnVelocityControlledOutput) 
	EVT_RADIOBUTTON(450, TriggerDialog::OnZoneControlledOutput) 
	EVT_RADIOBUTTON(701, TriggerDialog::OnSequenceOutput) 
	EVT_RADIOBUTTON(702, TriggerDialog::OnMouseOutput) 
	EVT_GNUMBERBOX(212,  TriggerDialog::OnMidiOutChannel) 	
	EVT_CHECKBOX(220,    TriggerDialog::OnNoteOff)
	EVT_BUTTON(700,      TriggerDialog::OnSample)

	//basic Output
	EVT_GNUMBERBOX(211,  TriggerDialog::OnMidiOutNote)

	//alternating Output
	EVT_GNUMBERBOX(235, TriggerDialog::OnAlternateReset)
	EVT_CHECKBOX(300,   TriggerDialog::OnAlternateBox)
	EVT_CHECKBOX(402,   TriggerDialog::OnAlternateRandomize)
	EVT_GNUMBERBOX(225, TriggerDialog::OnAlternateNoteBox1)
	EVT_GNUMBERBOX(226, TriggerDialog::OnAlternateNoteBox2)
	EVT_GNUMBERBOX(227, TriggerDialog::OnAlternateNoteBox3)
	EVT_GNUMBERBOX(228, TriggerDialog::OnAlternateNoteBox4)
	EVT_GNUMBERBOX(229, TriggerDialog::OnAlternateNoteBox5)
	EVT_GNUMBERBOX(230, TriggerDialog::OnAlternateNoteBox6)
	EVT_GNUMBERBOX(231, TriggerDialog::OnAlternateNoteBox7)
	EVT_GNUMBERBOX(232, TriggerDialog::OnAlternateNoteBox8)
	EVT_GNUMBERBOX(233, TriggerDialog::OnAlternateNoteBox9)
	EVT_GNUMBERBOX(234, TriggerDialog::OnAlternateNoteBox10)

	//midiCC Controlled Output
	EVT_GNUMBERBOX(261, TriggerDialog::OnMidiCCControlledOutputNote)
	EVT_CHECKBOX(310,   TriggerDialog::OnMidiCCBox)
	EVT_GNUMBERBOX(320, TriggerDialog::OnMidiCCNoteBox1)
	EVT_GNUMBERBOX(321, TriggerDialog::OnMidiCCNoteBox2)
	EVT_GNUMBERBOX(322, TriggerDialog::OnMidiCCNoteBox3)
	EVT_GNUMBERBOX(323, TriggerDialog::OnMidiCCNoteBox4)
	EVT_GNUMBERBOX(324, TriggerDialog::OnMidiCCNoteBox5)
	EVT_GNUMBERBOX(325, TriggerDialog::OnMidiCCNoteBox6)
	EVT_GNUMBERBOX(326, TriggerDialog::OnMidiCCNoteBox7)
	EVT_GNUMBERBOX(327, TriggerDialog::OnMidiCCNoteBox8)
	EVT_GNUMBERBOX(328, TriggerDialog::OnMidiCCNoteBox9)
	EVT_GNUMBERBOX(329, TriggerDialog::OnMidiCCNoteBox10)
	EVT_GSLIDER(400,    TriggerDialog::OnMidiCCControlledSlider)

	//velocity Controlled Output
	EVT_CHECKBOX(330,   TriggerDialog::OnVelocityBox)
	EVT_GNUMBERBOX(340, TriggerDialog::OnVelocityNoteBox1)
	EVT_GNUMBERBOX(341, TriggerDialog::OnVelocityNoteBox2)
	EVT_GNUMBERBOX(342, TriggerDialog::OnVelocityNoteBox3)
	EVT_GNUMBERBOX(343, TriggerDialog::OnVelocityNoteBox4)
	EVT_GNUMBERBOX(344, TriggerDialog::OnVelocityNoteBox5)
	EVT_GNUMBERBOX(345, TriggerDialog::OnVelocityNoteBox6)
	EVT_GNUMBERBOX(346, TriggerDialog::OnVelocityNoteBox7)
	EVT_GNUMBERBOX(347, TriggerDialog::OnVelocityNoteBox8)
	EVT_GNUMBERBOX(348, TriggerDialog::OnVelocityNoteBox9)
	EVT_GNUMBERBOX(349, TriggerDialog::OnVelocityNoteBox10)
	EVT_GSLIDER(401,    TriggerDialog::OnVelocityControlledSlider)

	//zone Controlled Output
	EVT_CHECKBOX(451,   TriggerDialog::OnZoneBox)
	EVT_GNUMBERBOX(452, TriggerDialog::OnZoneNoteBox1)
	EVT_GNUMBERBOX(453, TriggerDialog::OnZoneNoteBox2)
	EVT_GNUMBERBOX(454, TriggerDialog::OnZoneNoteBox3)
	EVT_GNUMBERBOX(455, TriggerDialog::OnZoneNoteBox4)
	EVT_GNUMBERBOX(456, TriggerDialog::OnZoneNoteBox5)
	EVT_GNUMBERBOX(457, TriggerDialog::OnZoneNoteBox6)
	EVT_GNUMBERBOX(458, TriggerDialog::OnZoneNoteBox7)
	EVT_GNUMBERBOX(459, TriggerDialog::OnZoneNoteBox8)
	EVT_GNUMBERBOX(460, TriggerDialog::OnZoneNoteBox9)
	EVT_GNUMBERBOX(462, TriggerDialog::OnZoneNoteBox10)
	EVT_GSLIDER(462,    TriggerDialog::OnZoneControlledSlider)
	
	//sequence Output
	EVT_GBUTTON(703,    TriggerDialog::OnFileSelect)
	EVT_CHECKBOX(704,   TriggerDialog::OnSequenceOverlap)

	//mouse Output
	EVT_GNUMBERBOX(705,  TriggerDialog::OnMouseXBox)
	EVT_GNUMBERBOX(706,  TriggerDialog::OnMouseYBox)

	//Multi-Zone Panel Events
	EVT_GNUMBERBOX(219, TriggerDialog::OnMultiZoneWaitTime)

	EVT_GBUTTON(605,    TriggerDialog::OnWaitTimeDetect)
	EVT_GBUTTON(606,    TriggerDialog::OnWaitTimeReset)
	EVT_GBUTTON(607,    TriggerDialog::OnWaitTimeOk)
	EVT_GBUTTON(608,    TriggerDialog::OnWaitTimeCancel)

	EVT_GNUMBERBOX(245, TriggerDialog::OnPriority1)
	EVT_GNUMBERBOX(246, TriggerDialog::OnPriority2) 
	EVT_GNUMBERBOX(247, TriggerDialog::OnPriority3)
	EVT_GNUMBERBOX(248, TriggerDialog::OnGravity1)
	EVT_GNUMBERBOX(249, TriggerDialog::OnGravity2) 
	EVT_GNUMBERBOX(250, TriggerDialog::OnGravity3) 
	EVT_GNUMBERBOX(600, TriggerDialog::OnVelocityBalance) 
	EVT_CHECKBOX(251,   TriggerDialog::OnHasRim)
	EVT_CHECKBOX(252,   TriggerDialog::OnEnableCC)
	EVT_GNUMBERBOX(253, TriggerDialog::OnCCOutputChannel) 
	EVT_GNUMBERBOX(254, TriggerDialog::OnCCOutputNote) 
	EVT_GNUMBERBOX(331, TriggerDialog::OnCCOutputHighCompressor) 
	EVT_GNUMBERBOX(332, TriggerDialog::OnCCOutputLowCompressor) 
	EVT_BUTTON(601,     TriggerDialog::OnVelToPosAvg)
	
END_EVENT_TABLE() 

/////////////////////////////////////////////
TriggerDialog::TriggerDialog(Trigger* parent) 
	     :wxDialog(parent, -1, wxT("Track Settings"), wxDefaultPosition, wxSize(520, 510), wxDEFAULT_DIALOG_STYLE)
{
	InitVariables();

	CentreOnScreen(wxBOTH);

	trigger = parent; //link to Trigger parent to access variables
	SetTitle(wxString::Format(wxT("Track %d Settings"), trigger->trackNum));
	
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
	topEdge4Image = new GImage(this, -1, wxPoint(377,39), TopEdge_xpm);
	leftEdge3Image = new GImage(this, -1, wxPoint(120,206), LeftEdge_xpm);
	leftEdge4Image = new GImage(this, -1, wxPoint(120,239), LeftEdge_xpm);
	leftEdge5Image = new GImage(this, -1, wxPoint(120,272), LeftEdge_xpm);
	leftEdge6Image = new GImage(this, -1, wxPoint(120,305), LeftEdge_xpm);
	leftEdge7Image = new GImage(this, -1, wxPoint(120,338), LeftEdge_xpm);
	leftEdge8Image = new GImage(this, -1, wxPoint(120,371), LeftEdge_xpm);

	//buttons
	zone1Button = new GButton(this, 208, wxPoint(155,14), zone1_xpm, Zone1_Hover_xpm);
	zone2Button = new GButton(this, 209, wxPoint(229,14), zone2_xpm, Zone2_Hover_xpm);
	zone3Button = new GButton(this, 210, wxPoint(303,14), zone3_xpm, Zone3_Hover_xpm);
	zone1SelectedButton = new GButton(this, -1, wxPoint(155,14), Zone1_Selected_xpm);
	zone2SelectedButton = new GButton(this, -1, wxPoint(229,14), Zone2_Selected_xpm);
	zone3SelectedButton = new GButton(this, -1, wxPoint(303,14), Zone3_Selected_xpm);
	inputButton = new GButton(this, 205, wxPoint(10,74), Input_xpm , input_hover_xpm);
	inputSelectedButton = new GButton(this, -1, wxPoint(10,74), Input_Selected_xpm);
	retriggerButton = new GButton(this, 240, wxPoint(10,107), retrigger_xpm , retrigger_hover_xpm);
	retriggerSelectedButton = new GButton(this, -1, wxPoint(10,107), retrigger_selected_xpm);
	dynamicsButton = new GButton(this, 236, wxPoint(10,140), dynamics_xpm , dynamics_hover_xpm);
	dynamicsSelectedButton = new GButton(this, -1, wxPoint(10,140), dynamics_selected_xpm);		
	outputButton = new GButton(this, 206, wxPoint(10,173), Output_xpm , Output_Hover_xpm);
    outputSelectedButton = new GButton(this, -1, wxPoint(10,173), Output_Selected_xpm);
	multiZoneButton = new GButton(this, 239, wxPoint(10,206), multiZone_xpm , multiZone_hover_xpm);
    multiZoneSelectedButton = new GButton(this, -1, wxPoint(10,206), multiZone_selected_xpm);
	okButton = new GButton(this, 203, wxPoint(314,445), ok2_xpm, ok2_hover_xpm, ok2_click_xpm); 
	cancelButton = new GButton(this, 204, wxPoint(385,445), cancel2_xpm, cancel2_hover_xpm, cancel2_click_xpm);

	///////////////////// Panels ////////////////
	//// Input Panel
	inputPanel = new wxPanel(this, 99, wxPoint(125,45), wxSize(340,388), 0, wxT(""));
	inputPanel->SetBackgroundColour(wxColour(99,99,99));
	#ifdef WIN32
	inputPanel->Connect(-1, wxEVT_LEFT_DOWN, wxMouseEventHandler(TriggerDialog::OnMouse), NULL, this); 
	#endif	

	learnButton = new GButton(inputPanel, 202, wxPoint(125,15), learn_xpm, Learn_Hover_xpm, Learn_Click_xpm);
	device = new wxStaticText(inputPanel, -1, wxT(""), wxPoint(50,195), wxSize(200,20), wxALIGN_CENTRE , wxT(""));
	info = new wxStaticText(inputPanel, -1, wxT(""), wxPoint(50,210), wxSize(200,20), wxALIGN_CENTRE , wxT(""));
	wxStaticText *drumTypeText = new wxStaticText(inputPanel, -1, wxT("Drum Type"), wxPoint(63,242), wxSize(70,20), 0, wxT(""));
	drumTypeBox = new wxComboBox(inputPanel, 1000, wxT(""), wxPoint(133, 240), wxSize(110,20), GetDrumTypes(), wxCB_READONLY, wxDefaultValidator, wxT(""));
	wxStaticText *zonesText = new wxStaticText(inputPanel, -1, wxT("Zones"), wxPoint(200,350), wxSize(45,20), 0, wxT(""));
    for(int val=1; val<4; ++val){ zonenums.Add(wxString::Format(wxT("%d"), val)); }
	zonesSelectBox = new wxComboBox(inputPanel, 207, wxT(""), wxPoint(138,345), wxSize(50,20), zonenums, wxCB_READONLY, wxDefaultValidator, wxT(""));
	#ifdef WIN32
	zonesSelectBox->Connect(-1, wxEVT_MOUSEWHEEL, wxMouseEventHandler(TriggerDialog::OnMouseWheel), NULL, this);
	#endif
	keyboardImage = new GImage(inputPanel, -1, wxPoint(65,50), keyboard_xpm); keyboardImage->Hide();
	audioDeviceImage = new GImage(inputPanel, -1, wxPoint(55,60), AudioDevice_xpm); audioDeviceImage->Hide();
	midiDeviceImage = new GImage(inputPanel, -1, wxPoint(60,60), MidiDevice_xpm); midiDeviceImage->Hide();
	joystickImage = new GImage(inputPanel, -1, wxPoint(60,50), Joystick_xpm); joystickImage->Hide();
	knob = new GKnob(inputPanel, 106, wxPoint(140,275), wxWANTS_CHARS,  wxT(""), knobback_xpm, knob2_xpm);
	knob->SetRange(0, 1000);  
	knobValue = new wxStaticText(inputPanel, -1, wxT(""), wxPoint(154,323), wxDefaultSize, wxALIGN_CENTRE, wxT(""));
	knobValue->SetForegroundColour(wxColour(40,40,40));


	//// Retrigger Panel
	retriggerPanel = new wxPanel(this, 99, wxPoint(125,45), wxSize(340,388), 0, wxT(""));
	retriggerPanel->SetBackgroundColour(wxColour(99,99,99));

	retriggerDetectButton = new GButton(retriggerPanel, 241, wxPoint(120,50), detect_xpm, detect_hover_xpm, detect_click_xpm);
	retriggerBox = new GNumberBox(retriggerPanel, 214, wxT(""), wxPoint(140,200), wxSize(30,15));
	retriggerBox->SetMinMax(0,200);
	retriggerBox->SetDefault(0);
	retriggerResetButton = new GButton(retriggerPanel, 242, wxPoint(45,350), reset_xpm, reset_hover_xpm, reset_click_xpm);
	retriggerOkButton = new GButton(retriggerPanel, 243, wxPoint(120,350),  ok3_xpm, ok3_hover_xpm, ok3_click_xpm);
	retriggerCancelButton = new GButton(retriggerPanel, 244, wxPoint(195,350), cancel3_xpm, cancel3_hover_xpm, cancel3_click_xpm);
	retriggerResetButton->Hide();
	retriggerOkButton->Hide();
	retriggerCancelButton->Hide();

	//// Dynamics Panel
	dynamicsPanel = new wxPanel(this, 99, wxPoint(125,45), wxSize(340,388), 0, wxT(""));
	dynamicsPanel->SetBackgroundColour(wxColour(99,99,99));
	curve = new GCurve(dynamicsPanel, 237, wxPoint(15,30));
	compressorSlider = new GSlider(dynamicsPanel, 255, wxPoint(270,27), 0, wxT(""), compressorSlit_xpm, compressorSlit_xpm,
						           blueSlider_xpm, blueSlider_xpm, blueSlider_xpm, blueSlider_xpm);
	compressorSlider->SetRange(0, 127);
	compressorSlider->AddKnob();
	compressorSlider->SetDefault(0, 0);
	compressorSlider->SetDefault(1, 127);
	cutoffSlider = new GSlider(dynamicsPanel, 256, wxPoint(300,27), 0, wxT(""), cutoffSlit_xpm, cutoffSlit_xpm,
						           redSlider_xpm, redSlider_xpm, redSlider_xpm, redSlider_xpm);
	cutoffSlider->SetRange(0, 127); 
	cutoffSlider->AddKnob();
	cutoffSlider->SetDefault(0, 0);
	cutoffSlider->SetDefault(1, 127);
	highCompressorText = new wxStaticText(dynamicsPanel, -1, wxT("0"), wxPoint(283,13), wxSize(20,15), wxALIGN_CENTRE, wxT(""));
	highLimiterText = new wxStaticText(dynamicsPanel, -1, wxT("0"), wxPoint(313,13), wxSize(20,15), wxALIGN_CENTRE, wxT(""));
	lowCompressorText = new wxStaticText(dynamicsPanel, -1, wxT("0"), wxPoint(283,233), wxSize(20,15), wxALIGN_CENTRE, wxT(""));
	lowLimiterText = new wxStaticText(dynamicsPanel, -1, wxT("0"), wxPoint(313,233), wxSize(20,15), wxALIGN_CENTRE, wxT(""));
	
	lowPercentSlider = new GSlider(dynamicsPanel, 500, wxPoint(270,270), 0, wxT(""), lowPercent_xpm, lowPercent_xpm,
						           blueSlider_xpm, blueSlider_xpm, blueSlider_xpm, blueSlider_xpm);
	lowPercentSlider->SetRange(0, 100);
	lowPercentSlider->SetValue(0, 50);
	lowPercentSlider->SetDefault(0, 50);
	highPercentSlider = new GSlider(dynamicsPanel, 501, wxPoint(300,270), 0, wxT(""), highPercent_xpm, highPercent_xpm,
						           blueSlider_xpm, blueSlider_xpm, blueSlider_xpm, blueSlider_xpm);
	highPercentSlider->SetRange(0, 100);
	highPercentSlider->SetValue(0, 50);
	highPercentSlider->SetDefault(0, 50);
	lowPercentText = new wxStaticText(dynamicsPanel, -1, wxT("0"), wxPoint(283,250), wxSize(20,15), wxALIGN_CENTRE, wxT(""));
	highPercentText = new wxStaticText(dynamicsPanel, -1, wxT("0"), wxPoint(313,250), wxSize(20,15), wxALIGN_CENTRE, wxT(""));

	wxStaticText *AntiMachineGunText = new wxStaticText(dynamicsPanel, -1, wxT("Anti-MachineGun"), wxPoint(60,260), wxSize(120, 20),0, wxT(""));
	antiMachineGunBox = new GNumberBox(dynamicsPanel, 221, wxT(""), wxPoint(20,260), wxSize(30,15));
	antiMachineGunBox->SetMinMax(0,3000);
	antiMachineGunBox->SetDefault(100);
	MidiCCControlledBox = new wxCheckBox(dynamicsPanel, 337, wxT("Midi CC Controlled Velocity"), wxPoint(20,290), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	MidiCCControlledNumber = new GNumberBox(dynamicsPanel, 238, wxT(""), wxPoint(220,290), wxSize(30,15));
	MidiCCControlledNumber->SetMinMax(0, 127);
	MidiCCControlledNumber->SetDefault(4);
	velocityDialogButton = new GButton(dynamicsPanel, 262, wxPoint(100,330), fullVelControl_xpm, fullVelControl_hover_xpm, fullVelControl_click_xpm);

	wxStaticText *crosstalkText = new wxStaticText(dynamicsPanel, -1, wxT("Crosstalk"), wxPoint(60,360), wxSize(120, 20),0, wxT(""));
	crosstalkBox = new GNumberBox(dynamicsPanel, 700, wxT(""), wxPoint(20,360), wxSize(30,15));

	//// Output Panel
	outputPanel = new wxPanel(this, -1, wxPoint(125,45), wxSize(340,388), 0, wxT(""));
	outputPanel->SetBackgroundColour(wxColour(99,99,99));
	#ifdef WIN32
	outputPanel->Connect(-1, wxEVT_LEFT_DOWN, wxMouseEventHandler(TriggerDialog::OnMouse), NULL, this); 
	#endif

	basicOutputButton = new wxRadioButton(outputPanel, 257, wxT("Basic Output"), wxPoint(10,20), wxDefaultSize, 0,wxDefaultValidator, wxT(""));
	alternatingOutputButton = new wxRadioButton(outputPanel, 258, wxT("Alternating Output"), wxPoint(10,40), wxDefaultSize, 0,wxDefaultValidator, wxT(""));
	midiCCControlledOutputButton = new wxRadioButton(outputPanel, 259, wxT("MidiCC Controlled Output"), wxPoint(10,60), wxDefaultSize, 0,wxDefaultValidator, wxT(""));
	velocityControlledOutputButton = new wxRadioButton(outputPanel, 260, wxT("Velocity Controlled Output"), wxPoint(10,80), wxDefaultSize, 0,wxDefaultValidator, wxT(""));
	zoneControlledOutputButton = new wxRadioButton(outputPanel, 450, wxT("Zone Controlled Output"), wxPoint(10,100), wxDefaultSize, 0,wxDefaultValidator, wxT(""));
	sequenceOutputButton = new wxRadioButton(outputPanel, 701, wxT("Sequence Output"), wxPoint(10,120), wxDefaultSize, 0,wxDefaultValidator, wxT(""));
	mouseOutputButton = new wxRadioButton(outputPanel, 702, wxT("Mouse Output"), wxPoint(10,140), wxDefaultSize, 0,wxDefaultValidator, wxT(""));
	wxStaticText *midiChannelText = new wxStaticText(outputPanel, -1, wxT("Midi Channel"), wxPoint(50,160), wxSize(100,20), 0, wxT(""));		
	midiOutChannelBox = new GNumberBox(outputPanel, 212, wxT(""), wxPoint(10,160), wxSize(30,15));
	midiOutChannelBox->SetMinMax(1, 64); //Should be limited to 10, but this way we can set output type, note,cc,pc,etc
	midiOutChannelBox->SetDefault(10);
	noteOffBox = new wxCheckBox(outputPanel, 220, wxT("Note Off Signals"), wxPoint(10,180), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	//outputSample = new wxButton(outputPanel, 700, wxT("Sample"), wxPoint(10, 200), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	sampleText = new wxStaticText(outputPanel, -1, wxT(""), wxPoint(10, 220), wxDefaultSize, 0, wxT(""));

	//// Output Panel
	//basic Output
	basicOutputPanel = new wxPanel(outputPanel, -1, wxPoint(200,0), wxSize(280,388), 0, wxT(""));
	basicOutputPanel->SetBackgroundColour(wxColour(99,99,99));
	midiNoteText = new wxStaticText(basicOutputPanel, -1, wxT("Midi Note"), wxPoint(45,20), wxSize(80,20), 0, wxT(""));
	midiOutNoteBox = new GNumberBox(basicOutputPanel, 211, wxT(""), wxPoint(5,20), wxSize(30,15));
	midiOutNoteBox->SetMinMax(0, 127);
	midiOutNoteBox->SetDefault(1);

	//alternating Output
	alternatingOutputPanel = new wxPanel(outputPanel, -1, wxPoint(200,0), wxSize(280,388), 0, wxT(""));
	alternatingOutputPanel->SetBackgroundColour(wxColour(99,99,99));
	alternateResetText = new wxStaticText(alternatingOutputPanel, 402, wxT("Reset Time"), wxPoint(45,20), wxSize(80,20), 0, wxT(""));
	alternateResetBox = new GNumberBox(alternatingOutputPanel, 235, wxT(""), wxPoint(5,20), wxSize(30,15));
	alternateResetBox->SetMinMax(1, 3000);
	alternateResetBox->SetDefault(1000);
	alternateResetBox->SetToolTip(wxT("The amount of milliseconds to wait for a trigger before resetting back to the first note.")); 	
	alternateRandomBox = new wxCheckBox(alternatingOutputPanel, 402, wxT("Randomize"), wxPoint(5,40), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	alternateBox[0] = new wxCheckBox(alternatingOutputPanel, 300, wxT(""), wxPoint(5,100), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	alternateBox[1] = new wxCheckBox(alternatingOutputPanel, 300, wxT(""), wxPoint(5,120), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	alternateBox[2] = new wxCheckBox(alternatingOutputPanel, 300, wxT(""), wxPoint(5,140), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	alternateBox[3] = new wxCheckBox(alternatingOutputPanel, 300, wxT(""), wxPoint(5,160), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	alternateBox[4] = new wxCheckBox(alternatingOutputPanel, 300, wxT(""), wxPoint(5,180), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	alternateBox[5] = new wxCheckBox(alternatingOutputPanel, 300, wxT(""), wxPoint(5,200), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	alternateBox[6] = new wxCheckBox(alternatingOutputPanel, 300, wxT(""), wxPoint(5,220), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	alternateBox[7] = new wxCheckBox(alternatingOutputPanel, 300, wxT(""), wxPoint(5,240), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	alternateNoteBox[0] = new GNumberBox(alternatingOutputPanel, 225, wxT(""), wxPoint(25,60), wxSize(30,15));
	alternateNoteBox[0]->SetMinMax(0, 127);
	alternateNoteBox[0]->SetDefault(1);
	alternateNoteBox[0]->SetToolTip(wxT("The first note that will play when triggered."));
	alternateNoteBox[1] = new GNumberBox(alternatingOutputPanel, 226, wxT(""), wxPoint(25,80), wxSize(30,15));
	alternateNoteBox[1]->SetMinMax(0, 127);
	alternateNoteBox[1]->SetDefault(2);
	alternateNoteBox[1]->SetToolTip(wxT("The second note that will play when triggered."));
	alternateNoteBox[2] = new GNumberBox(alternatingOutputPanel, 227, wxT(""), wxPoint(25,100), wxSize(30,15));
	alternateNoteBox[2]->SetMinMax(0, 127);
	alternateNoteBox[2]->SetDefault(3);
	alternateNoteBox[2]->SetToolTip(wxT("The third note that will play when triggered."));
	alternateNoteBox[3] = new GNumberBox(alternatingOutputPanel, 228, wxT(""), wxPoint(25,120), wxSize(30,15));
	alternateNoteBox[3]->SetMinMax(0, 127);
	alternateNoteBox[3]->SetDefault(4);
	alternateNoteBox[4] = new GNumberBox(alternatingOutputPanel, 229, wxT(""), wxPoint(25,140), wxSize(30,15));
	alternateNoteBox[4]->SetMinMax(0, 127);
	alternateNoteBox[4]->SetDefault(5);
	alternateNoteBox[5] = new GNumberBox(alternatingOutputPanel, 230, wxT(""), wxPoint(25,160), wxSize(30,15));
	alternateNoteBox[5]->SetMinMax(0, 127);
	alternateNoteBox[5]->SetDefault(6);
	alternateNoteBox[6] = new GNumberBox(alternatingOutputPanel, 231, wxT(""), wxPoint(25,180), wxSize(30,15));
	alternateNoteBox[6]->SetMinMax(0, 127);
	alternateNoteBox[6]->SetDefault(7);
	alternateNoteBox[7] = new GNumberBox(alternatingOutputPanel, 232, wxT(""), wxPoint(25,200), wxSize(30,15));
	alternateNoteBox[7]->SetMinMax(0, 127);
	alternateNoteBox[7]->SetDefault(8);
	alternateNoteBox[8] = new GNumberBox(alternatingOutputPanel, 233, wxT(""), wxPoint(25,220), wxSize(30,15));
	alternateNoteBox[8]->SetMinMax(0, 127);
	alternateNoteBox[8]->SetDefault(9);
	alternateNoteBox[9] = new GNumberBox(alternatingOutputPanel, 234, wxT(""), wxPoint(25,240), wxSize(30,15));
	alternateNoteBox[9]->SetMinMax(0, 127);
	alternateNoteBox[9]->SetDefault(10);

	//MidiCC Controlled Output
	midiCCControlledOutputPanel = new wxPanel(outputPanel, -1, wxPoint(200,0), wxSize(350,388), 0, wxT(""));
	midiCCControlledOutputPanel->SetBackgroundColour(wxColour(99,99,99));
	midiCCControlledOutputNoteText = new wxStaticText(midiCCControlledOutputPanel, -1, wxT("Midi CC Note"), wxPoint(45,20), wxSize(100,20), 0, wxT(""));
	midiCCControlledInputNoteBox = new GNumberBox(midiCCControlledOutputPanel, 261, wxT(""), wxPoint(5,20), wxSize(30,15));
	midiCCControlledInputNoteBox->SetMinMax(0, 127);
	midiCCControlledInputNoteBox->SetDefault(0);
	midiCCControlledInputNoteBox->SetToolTip(wxT("The incommping midiCC channel that will controll the output played")); 
	midiCCBox[0] = new wxCheckBox(midiCCControlledOutputPanel, 310, wxT(""), wxPoint(5,200), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	midiCCBox[1] = new wxCheckBox(midiCCControlledOutputPanel, 310, wxT(""), wxPoint(5,180), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	midiCCBox[2] = new wxCheckBox(midiCCControlledOutputPanel, 310, wxT(""), wxPoint(5,160), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	midiCCBox[3] = new wxCheckBox(midiCCControlledOutputPanel, 310, wxT(""), wxPoint(5,140), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	midiCCBox[4] = new wxCheckBox(midiCCControlledOutputPanel, 310, wxT(""), wxPoint(5,120), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	midiCCBox[5] = new wxCheckBox(midiCCControlledOutputPanel, 310, wxT(""), wxPoint(5,100), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	midiCCBox[6] = new wxCheckBox(midiCCControlledOutputPanel, 310, wxT(""), wxPoint(5,80), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	midiCCBox[7] = new wxCheckBox(midiCCControlledOutputPanel, 310, wxT(""), wxPoint(5,60), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	midiCCNoteBox[0] = new GNumberBox(midiCCControlledOutputPanel, 320, wxT(""), wxPoint(25,240), wxSize(30,15));
	midiCCNoteBox[0]->SetMinMax(0, 127);
	midiCCNoteBox[1] = new GNumberBox(midiCCControlledOutputPanel, 321, wxT(""), wxPoint(25,220), wxSize(30,15));
	midiCCNoteBox[1]->SetMinMax(0, 127);
	midiCCNoteBox[2] = new GNumberBox(midiCCControlledOutputPanel, 322, wxT(""), wxPoint(25,200), wxSize(30,15));
	midiCCNoteBox[2]->SetMinMax(0, 127);
	midiCCNoteBox[3] = new GNumberBox(midiCCControlledOutputPanel, 323, wxT(""), wxPoint(25,180), wxSize(30,15));
	midiCCNoteBox[3]->SetMinMax(0, 127);
	midiCCNoteBox[4] = new GNumberBox(midiCCControlledOutputPanel, 324, wxT(""), wxPoint(25,160), wxSize(30,15));
	midiCCNoteBox[4]->SetMinMax(0, 127);
	midiCCNoteBox[5] = new GNumberBox(midiCCControlledOutputPanel, 325, wxT(""), wxPoint(25,140), wxSize(30,15));
	midiCCNoteBox[5]->SetMinMax(0, 127);
	midiCCNoteBox[6] = new GNumberBox(midiCCControlledOutputPanel, 326, wxT(""), wxPoint(25,120), wxSize(30,15));
	midiCCNoteBox[6]->SetMinMax(0, 127);
	midiCCNoteBox[7] = new GNumberBox(midiCCControlledOutputPanel, 327, wxT(""), wxPoint(25,100), wxSize(30,15));
	midiCCNoteBox[7]->SetMinMax(0, 127);
	midiCCNoteBox[8] = new GNumberBox(midiCCControlledOutputPanel, 328, wxT(""), wxPoint(25,80), wxSize(30,15));
	midiCCNoteBox[8]->SetMinMax(0, 127);
	midiCCNoteBox[9] = new GNumberBox(midiCCControlledOutputPanel, 329, wxT(""), wxPoint(25,60), wxSize(30,15));
	midiCCNoteBox[9]->SetMinMax(0, 127);
	midiCCText[0] = new wxStaticText(midiCCControlledOutputPanel, -1, wxT(""), wxPoint(58,240), wxSize(55,20), wxST_NO_AUTORESIZE, wxT(""));
	midiCCText[1] = new wxStaticText(midiCCControlledOutputPanel, -1, wxT(""), wxPoint(58,220), wxSize(55,20), wxST_NO_AUTORESIZE, wxT(""));
	midiCCText[2] = new wxStaticText(midiCCControlledOutputPanel, -1, wxT(""), wxPoint(58,200), wxSize(55,20), wxST_NO_AUTORESIZE, wxT(""));
	midiCCText[3] = new wxStaticText(midiCCControlledOutputPanel, -1, wxT(""), wxPoint(58,180), wxSize(55,20), wxST_NO_AUTORESIZE, wxT(""));
	midiCCText[4] = new wxStaticText(midiCCControlledOutputPanel, -1, wxT(""), wxPoint(58,160), wxSize(55,20), wxST_NO_AUTORESIZE, wxT(""));
	midiCCText[5] = new wxStaticText(midiCCControlledOutputPanel, -1, wxT(""), wxPoint(58,140), wxSize(55,20), wxST_NO_AUTORESIZE, wxT(""));
	midiCCText[6] = new wxStaticText(midiCCControlledOutputPanel, -1, wxT(""), wxPoint(58,120), wxSize(55,20), wxST_NO_AUTORESIZE, wxT(""));
	midiCCText[7] = new wxStaticText(midiCCControlledOutputPanel, -1, wxT(""), wxPoint(58,100), wxSize(55,20), wxST_NO_AUTORESIZE, wxT(""));
	midiCCText[8] = new wxStaticText(midiCCControlledOutputPanel, -1, wxT(""), wxPoint(58,80), wxSize(55,20), wxST_NO_AUTORESIZE, wxT(""));
	midiCCText[9] = new wxStaticText(midiCCControlledOutputPanel, -1, wxT(""), wxPoint(58,60), wxSize(55,20), wxST_NO_AUTORESIZE, wxT(""));
	midiCCControlledSlider = new GSlider(midiCCControlledOutputPanel, 400, wxPoint(115,40), 0, wxT(""), longSlider_xpm, longSlider_xpm,
						           blueSlider_xpm, blueSlider_xpm, blueSlider_xpm, blueSlider_xpm);
	midiCCControlledSlider->SetRange(2, 127);
	midiCCControlledSlider->SetDefault(0, 64);
	midiCCControlledSlider->SetValue(0, 64);

	//Velocity Controlled Output
	velocityControlledOutputPanel = new wxPanel(outputPanel, -1, wxPoint(200,0), wxSize(350,388), 0, wxT(""));
	velocityControlledOutputPanel->SetBackgroundColour(wxColour(99,99,99));
	velocityBox[0] = new wxCheckBox(velocityControlledOutputPanel, 330, wxT(""), wxPoint(5,200), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	velocityBox[1] = new wxCheckBox(velocityControlledOutputPanel, 330, wxT(""), wxPoint(5,180), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	velocityBox[2] = new wxCheckBox(velocityControlledOutputPanel, 330, wxT(""), wxPoint(5,160), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	velocityBox[3] = new wxCheckBox(velocityControlledOutputPanel, 330, wxT(""), wxPoint(5,140), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	velocityBox[4] = new wxCheckBox(velocityControlledOutputPanel, 330, wxT(""), wxPoint(5,120), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	velocityBox[5] = new wxCheckBox(velocityControlledOutputPanel, 330, wxT(""), wxPoint(5,100), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	velocityBox[6] = new wxCheckBox(velocityControlledOutputPanel, 330, wxT(""), wxPoint(5,80), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	velocityBox[7] = new wxCheckBox(velocityControlledOutputPanel, 330, wxT(""), wxPoint(5,60), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	velocityNoteBox[0] = new GNumberBox(velocityControlledOutputPanel, 340, wxT(""), wxPoint(25,240), wxSize(30,15));
	velocityNoteBox[0]->SetMinMax(0, 127);
	velocityNoteBox[1] = new GNumberBox(velocityControlledOutputPanel, 341, wxT(""), wxPoint(25,220), wxSize(30,15));
	velocityNoteBox[1]->SetMinMax(0, 127);
	velocityNoteBox[2] = new GNumberBox(velocityControlledOutputPanel, 342, wxT(""), wxPoint(25,200), wxSize(30,15));
	velocityNoteBox[2]->SetMinMax(0, 127);
	velocityNoteBox[3] = new GNumberBox(velocityControlledOutputPanel, 343, wxT(""), wxPoint(25,180), wxSize(30,15));
	velocityNoteBox[3]->SetMinMax(0, 127);
	velocityNoteBox[4] = new GNumberBox(velocityControlledOutputPanel, 344, wxT(""), wxPoint(25,160), wxSize(30,15));
	velocityNoteBox[4]->SetMinMax(0, 127);
	velocityNoteBox[5] = new GNumberBox(velocityControlledOutputPanel, 345, wxT(""), wxPoint(25,140), wxSize(30,15));
	velocityNoteBox[5]->SetMinMax(0, 127);
	velocityNoteBox[6] = new GNumberBox(velocityControlledOutputPanel, 346, wxT(""), wxPoint(25,120), wxSize(30,15));
	velocityNoteBox[6]->SetMinMax(0, 127);
	velocityNoteBox[7] = new GNumberBox(velocityControlledOutputPanel, 347, wxT(""), wxPoint(25,100), wxSize(30,15));
	velocityNoteBox[7]->SetMinMax(0, 127);
	velocityNoteBox[8] = new GNumberBox(velocityControlledOutputPanel, 348, wxT(""), wxPoint(25,80), wxSize(30,15));
	velocityNoteBox[8]->SetMinMax(0, 127);
	velocityNoteBox[9] = new GNumberBox(velocityControlledOutputPanel, 349, wxT(""), wxPoint(25,60), wxSize(30,15));
	velocityNoteBox[9]->SetMinMax(0, 127);
	velocityText[0] = new wxStaticText(velocityControlledOutputPanel, -1, wxT(""), wxPoint(58,240), wxSize(55,20), wxST_NO_AUTORESIZE, wxT(""));
	velocityText[1] = new wxStaticText(velocityControlledOutputPanel, -1, wxT(""), wxPoint(58,220), wxSize(55,20), wxST_NO_AUTORESIZE, wxT(""));
	velocityText[2] = new wxStaticText(velocityControlledOutputPanel, -1, wxT(""), wxPoint(58,200), wxSize(55,20), wxST_NO_AUTORESIZE, wxT(""));
	velocityText[3] = new wxStaticText(velocityControlledOutputPanel, -1, wxT(""), wxPoint(58,180), wxSize(55,20), wxST_NO_AUTORESIZE, wxT(""));
	velocityText[4] = new wxStaticText(velocityControlledOutputPanel, -1, wxT(""), wxPoint(58,160), wxSize(55,20), wxST_NO_AUTORESIZE, wxT(""));
	velocityText[5] = new wxStaticText(velocityControlledOutputPanel, -1, wxT(""), wxPoint(58,140), wxSize(55,20), wxST_NO_AUTORESIZE, wxT(""));
	velocityText[6] = new wxStaticText(velocityControlledOutputPanel, -1, wxT(""), wxPoint(58,120), wxSize(55,20), wxST_NO_AUTORESIZE, wxT(""));
	velocityText[7] = new wxStaticText(velocityControlledOutputPanel, -1, wxT(""), wxPoint(58,100), wxSize(55,20), wxST_NO_AUTORESIZE, wxT(""));
	velocityText[8] = new wxStaticText(velocityControlledOutputPanel, -1, wxT(""), wxPoint(58,80), wxSize(55,20), wxST_NO_AUTORESIZE, wxT(""));
	velocityText[9] = new wxStaticText(velocityControlledOutputPanel, -1, wxT(""), wxPoint(58,60), wxSize(55,20), wxST_NO_AUTORESIZE, wxT(""));
	velocityControlledSlider = new GSlider(velocityControlledOutputPanel, 401, wxPoint(115,40), 0, wxT(""), longSlider_xpm, longSlider_xpm,
						           blueSlider_xpm, blueSlider_xpm, blueSlider_xpm, blueSlider_xpm);
	velocityControlledSlider->SetRange(2, 127);
	velocityControlledSlider->SetDefault(0, 64);
	velocityControlledSlider->SetValue(0, 64);

	//// Zone Controlled Output
	zoneControlledOutputPanel = new wxPanel(outputPanel, -1, wxPoint(200,0), wxSize(350,388), 0, wxT(""));
	zoneControlledOutputPanel->SetBackgroundColour(wxColour(99,99,99));
	zoneBox[0] = new wxCheckBox(zoneControlledOutputPanel, 451, wxT(""), wxPoint(5,200), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	zoneBox[1] = new wxCheckBox(zoneControlledOutputPanel, 451, wxT(""), wxPoint(5,180), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	zoneBox[2] = new wxCheckBox(zoneControlledOutputPanel, 451, wxT(""), wxPoint(5,160), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	zoneBox[3] = new wxCheckBox(zoneControlledOutputPanel, 451, wxT(""), wxPoint(5,140), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	zoneBox[4] = new wxCheckBox(zoneControlledOutputPanel, 451, wxT(""), wxPoint(5,120), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	zoneBox[5] = new wxCheckBox(zoneControlledOutputPanel, 451, wxT(""), wxPoint(5,100), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	zoneBox[6] = new wxCheckBox(zoneControlledOutputPanel, 451, wxT(""), wxPoint(5,80), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	zoneBox[7] = new wxCheckBox(zoneControlledOutputPanel, 451, wxT(""), wxPoint(5,60), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	zoneNoteBox[0] = new GNumberBox(zoneControlledOutputPanel, 452, wxT(""), wxPoint(25,240), wxSize(30,15));
	zoneNoteBox[0]->SetMinMax(0, 127);
	zoneNoteBox[1] = new GNumberBox(zoneControlledOutputPanel, 453, wxT(""), wxPoint(25,220), wxSize(30,15));
	zoneNoteBox[1]->SetMinMax(0, 127);
	zoneNoteBox[2] = new GNumberBox(zoneControlledOutputPanel, 454, wxT(""), wxPoint(25,200), wxSize(30,15));
	zoneNoteBox[2]->SetMinMax(0, 127);
	zoneNoteBox[3] = new GNumberBox(zoneControlledOutputPanel, 455, wxT(""), wxPoint(25,180), wxSize(30,15));
	zoneNoteBox[3]->SetMinMax(0, 127);
	zoneNoteBox[4] = new GNumberBox(zoneControlledOutputPanel, 456, wxT(""), wxPoint(25,160), wxSize(30,15));
	zoneNoteBox[4]->SetMinMax(0, 127);
	zoneNoteBox[5] = new GNumberBox(zoneControlledOutputPanel, 457, wxT(""), wxPoint(25,140), wxSize(30,15));
	zoneNoteBox[5]->SetMinMax(0, 127);
	zoneNoteBox[6] = new GNumberBox(zoneControlledOutputPanel, 458, wxT(""), wxPoint(25,120), wxSize(30,15));
	zoneNoteBox[6]->SetMinMax(0, 127);
	zoneNoteBox[7] = new GNumberBox(zoneControlledOutputPanel, 459, wxT(""), wxPoint(25,100), wxSize(30,15));
	zoneNoteBox[7]->SetMinMax(0, 127);
	zoneNoteBox[8] = new GNumberBox(zoneControlledOutputPanel, 460, wxT(""), wxPoint(25,80), wxSize(30,15));
	zoneNoteBox[8]->SetMinMax(0, 127);
	zoneNoteBox[9] = new GNumberBox(zoneControlledOutputPanel, 461, wxT(""), wxPoint(25,60), wxSize(30,15));
	zoneNoteBox[9]->SetMinMax(0, 127);
	zoneText[0] = new wxStaticText(zoneControlledOutputPanel, -1, wxT(""), wxPoint(58,240), wxSize(55,20), wxST_NO_AUTORESIZE, wxT(""));
	zoneText[1] = new wxStaticText(zoneControlledOutputPanel, -1, wxT(""), wxPoint(58,220), wxSize(55,20), wxST_NO_AUTORESIZE, wxT(""));
	zoneText[2] = new wxStaticText(zoneControlledOutputPanel, -1, wxT(""), wxPoint(58,200), wxSize(55,20), wxST_NO_AUTORESIZE, wxT(""));
	zoneText[3] = new wxStaticText(zoneControlledOutputPanel, -1, wxT(""), wxPoint(58,180), wxSize(55,20), wxST_NO_AUTORESIZE, wxT(""));
	zoneText[4] = new wxStaticText(zoneControlledOutputPanel, -1, wxT(""), wxPoint(58,160), wxSize(55,20), wxST_NO_AUTORESIZE, wxT(""));
	zoneText[5] = new wxStaticText(zoneControlledOutputPanel, -1, wxT(""), wxPoint(58,140), wxSize(55,20), wxST_NO_AUTORESIZE, wxT(""));
	zoneText[6] = new wxStaticText(zoneControlledOutputPanel, -1, wxT(""), wxPoint(58,120), wxSize(55,20), wxST_NO_AUTORESIZE, wxT(""));
	zoneText[7] = new wxStaticText(zoneControlledOutputPanel, -1, wxT(""), wxPoint(58,100), wxSize(55,20), wxST_NO_AUTORESIZE, wxT(""));
	zoneText[8] = new wxStaticText(zoneControlledOutputPanel, -1, wxT(""), wxPoint(58,80), wxSize(55,20), wxST_NO_AUTORESIZE, wxT(""));
	zoneText[9] = new wxStaticText(zoneControlledOutputPanel, -1, wxT(""), wxPoint(58,60), wxSize(55,20), wxST_NO_AUTORESIZE, wxT(""));
	zoneControlledSlider = new GSlider(zoneControlledOutputPanel, 462, wxPoint(115,40), 0, wxT(""), longSlider_xpm, longSlider_xpm,
						           blueSlider_xpm, blueSlider_xpm, blueSlider_xpm, blueSlider_xpm);
	zoneControlledSlider->SetRange(2, 127);
	zoneControlledSlider->SetDefault(0, 64);
	zoneControlledSlider->SetValue(0, 64);

	//// Sequence Output
	sequenceOutputPanel = new wxPanel(outputPanel, -1, wxPoint(200,0), wxSize(350,388), 0, wxT(""));
	sequenceOutputPanel->SetBackgroundColour(wxColour(99,99,99));
	filePath = new wxTextCtrl(sequenceOutputPanel, -1, wxT(""), wxPoint(0, 120), wxSize(85,16), wxNO_BORDER, wxDefaultValidator, wxT(""));
	filePath->SetBackgroundColour(wxColour(30,30,30));
	filePath->SetForegroundColour(wxColour(200,200,200));
	fileSelector = new GButton(sequenceOutputPanel, 703, wxPoint(85,110), folder_xpm, folder_hover_xpm, folder_click_xpm);
	sequenceOverlapBox = new wxCheckBox(sequenceOutputPanel, 704, wxT("Overlap"), wxPoint(20,160), wxDefaultSize, 0, wxDefaultValidator, wxT(""));


	//Mouse Output
	mouseOutputPanel = new wxPanel(outputPanel, -1, wxPoint(200,0), wxSize(280,388), 0, wxT(""));
	mouseOutputPanel->SetBackgroundColour(wxColour(99,99,99));
	mouseText = new wxStaticText(mouseOutputPanel, -1, wxT("Mouse X,Y"), wxPoint(25,20), wxSize(80,20), 0, wxT(""));
	mouseXBox = new GNumberBox(mouseOutputPanel, 705, wxT(""), wxPoint(25,50), wxSize(30,15));
	mouseYBox = new GNumberBox(mouseOutputPanel, 706, wxT(""), wxPoint(65,50), wxSize(30,15));
	mouseXBox->SetMinMax(0, 10000);
	mouseXBox->SetDefault(0);
	mouseYBox->SetMinMax(0, 10000);
	mouseYBox->SetDefault(0);

	//// Multi Zone Panel
	multiZonePanel = new wxPanel(this, -1, wxPoint(125,45), wxSize(340,388), 0, wxT(""));
	multiZonePanel->SetBackgroundColour(wxColour(99,99,99));
	
	wxStaticText *multiZoneWaitTimeText = new wxStaticText(multiZonePanel, -1, wxT("WaitTime"), wxPoint(60,20), wxSize(65, 20),0, wxT(""));
	multiZoneWaitTimeBox = new GNumberBox(multiZonePanel, 219, wxT(""), wxPoint(20,20), wxSize(30,15));
	multiZoneWaitTimeBox->SetMinMax(0,3000);
	multiZoneWaitTimeBox->SetDefault(10);
	multiZoneWaitTimeBox->SetToolTip(wxT("This is how long in milliseconds the track will wait for all zones to send a signal before processing output"));

	waitTimeDetectButton = new GButton(multiZonePanel, 605, wxPoint(150,20), detect_xpm, detect_hover_xpm, detect_click_xpm);
	waitTimeResetButton = new GButton(multiZonePanel, 606, wxPoint(120,20), reset_xpm, reset_hover_xpm, reset_click_xpm);
	waitTimeOkButton = new GButton(multiZonePanel, 607, wxPoint(195,20),  ok3_xpm, ok3_hover_xpm, ok3_click_xpm);
	waitTimeCancelButton = new GButton(multiZonePanel, 608, wxPoint(270,20), cancel3_xpm, cancel3_hover_xpm, cancel3_click_xpm);
	waitTimeResetButton->Hide();
	waitTimeOkButton->Hide();
	waitTimeCancelButton->Hide();

	priority1 = new GNumberBox(multiZonePanel, 245, wxT(""), wxPoint(20,60), wxSize(30,15));
	priority1->SetMinMax(-127, 127);
	priority1->SetDefault(0);
	wxStaticText *priority1Text = new wxStaticText(multiZonePanel, -1, wxT("Zone 1 Priority"), wxPoint(60,60), wxSize(120, 20),0, wxT(""));
	priority2 = new GNumberBox(multiZonePanel, 246, wxT(""), wxPoint(20,80), wxSize(30,15));
	priority2->SetMinMax(-127, 127);
	priority2->SetDefault(0);
	wxStaticText *priority2Text = new wxStaticText(multiZonePanel, -1, wxT("Zone 2 Priority"), wxPoint(60,80), wxSize(120, 20),0, wxT(""));
	priority3 = new GNumberBox(multiZonePanel, 247, wxT(""), wxPoint(20,100), wxSize(30,15));
	priority3->SetMinMax(-127, 127);
	priority3->SetDefault(0);
	wxStaticText *priority3Text = new wxStaticText(multiZonePanel, -1, wxT("Zone 3 Priority"), wxPoint(60,100), wxSize(140, 20),0, wxT(""));

	gravity1 = new GNumberBox(multiZonePanel, 248, wxT(""), wxPoint(20,120), wxSize(30,15));
	gravity1->SetMinMax(-127, 127);
	gravity1->SetDefault(0);
	wxStaticText *gravity1Text = new wxStaticText(multiZonePanel, -1, wxT("Zone 1 Position Gravity"), wxPoint(60,120), wxSize(150, 20),0, wxT(""));
	gravity2 = new GNumberBox(multiZonePanel, 249, wxT(""), wxPoint(20,140), wxSize(30,15));
	gravity2->SetMinMax(-127, 127);
	gravity2->SetDefault(0);
	wxStaticText *gravity2Text = new wxStaticText(multiZonePanel, -1, wxT("Zone 2 Position Gravity"), wxPoint(60,140), wxSize(150, 20),0, wxT(""));
	gravity3 = new GNumberBox(multiZonePanel, 250, wxT(""), wxPoint(20,160), wxSize(30,15));
	gravity3->SetMinMax(-127, 127);
	gravity3->SetDefault(0);
	wxStaticText *gravity3Text = new wxStaticText(multiZonePanel, -1, wxT("Zone 3 Position Gravity"), wxPoint(60,160), wxSize(150, 20),0, wxT(""));
	velocityBalanceBox = new GNumberBox(multiZonePanel, 600, wxT(""), wxPoint(20,180), wxSize(30,15));
	velocityBalanceBox->SetMinMax(0, 127);
	velocityBalanceBox->SetDefault(0);
	wxStaticText *velocityBalanceText = new wxStaticText(multiZonePanel, -1, wxT("Velocity Balance"), wxPoint(60,180), wxSize(120, 20),0, wxT(""));
	
	//// NEW
	velToPosAvgButton = new wxButton(multiZonePanel, 601, wxT("Average"), wxPoint(210,180), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	
	hasRimBox = new wxCheckBox(multiZonePanel, 251, wxT("Last Zone is a Rim"), wxPoint(20,200), wxDefaultSize, 0, wxDefaultValidator, wxT(""));

	enableCCBox = new wxCheckBox(multiZonePanel, 252, wxT("Enable CC Output"), wxPoint(20,240), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	ccOutputChannelBox = new GNumberBox(multiZonePanel, 253, wxT(""), wxPoint(20,260), wxSize(30,15));
	ccOutputChannelBox->SetMinMax(1,16);
	ccOutputChannelBox->SetDefault(10);
	wxStaticText *ccOutputChannelText = new wxStaticText(multiZonePanel, -1, wxT("Midi CC Output Channel"), wxPoint(60,260), wxSize(160, 20),0, wxT(""));
	ccOutputNoteBox = new GNumberBox(multiZonePanel, 254, wxT(""), wxPoint(20,280), wxSize(30,15));
	ccOutputNoteBox->SetMinMax(0,127);
	ccOutputNoteBox->SetDefault(1);
	wxStaticText *ccOutputNoteText = new wxStaticText(multiZonePanel, -1, wxT("Midi CC Output Note"), wxPoint(60,280), wxSize(140, 20),0, wxT(""));
	ccOutputHighCompressorBox = new GNumberBox(multiZonePanel, 331, wxT(""), wxPoint(20,300), wxSize(30,15));
	ccOutputHighCompressorBox->SetMinMax(0,127);
	ccOutputHighCompressorBox->SetDefault(127);
	wxStaticText *ccOutputHighCompressorText = new wxStaticText(multiZonePanel, -1, wxT("Limiter (High)"), wxPoint(60,300), wxSize(120, 20),0, wxT(""));
	ccOutputLowCompressorBox = new GNumberBox(multiZonePanel, 332, wxT(""), wxPoint(20,320), wxSize(30,15));
	ccOutputLowCompressorBox->SetMinMax(0,127);
	ccOutputLowCompressorBox->SetDefault(0);
	wxStaticText *ccOutputLowCompressorText = new wxStaticText(multiZonePanel, -1, wxT("Limiter (Low)"), wxPoint(60,320), wxSize(120, 20),0, wxT(""));

	currentZone = 0;
	VarsToTemp(); //backup settings
	VarsToDlg(); //then put them onto the dialog
	UpdateSelection(wxT("input")); //make default input
	UpdateZones();
}

///////////////////////////////
TriggerDialog::~TriggerDialog()
{	
}

///////////////////////////////////
void TriggerDialog::InitVariables()
{
	trigger = NULL;
	drumType = NULL;
	trigger = NULL;
	zones = NULL;
	for(register int z=0; z<3; ++z){deviceName[z] = wxT("");}
	for(register int z=0; z<3; ++z){inputDetails[z] = wxT("");}
	for(register int z=0; z<3; ++z){inputCode[z] = NULL;}
	for(register int z=0; z<3; ++z){audioThreshold[z] = NULL;}
	multiZoneWaitTime = NULL;
	for(register int z=0; z<3; ++z){preVolume[z] = NULL;}
	for(register int z=0; z<3; ++z){preGain[z] = NULL;}
	for(register int z=0; z<3; ++z){retrigger[z] = NULL;}
	for(register int z=0; z<3; ++z){crosstalk[z] = NULL;}
	for(register int z=0; z<3; ++z){highCompressor[z] = NULL;}
	for(register int z=0; z<3; ++z){highPercent[z] = NULL;}
	for(register int z=0; z<3; ++z){lowCompressor[z] = NULL;}
	for(register int z=0; z<3; ++z){lowPercent[z] = NULL;}
	for(register int z=0; z<3; ++z){highLimiter[z] = NULL;}
	for(register int z=0; z<3; ++z){lowLimiter[z] = NULL;}
	bool ccReverse = NULL;
	for(register int z=0; z<3; ++z){noteOff[z] = NULL;}
	pointsZone1.clear();
	pointsZone2.clear();
	pointsZone3.clear();
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
	for(register int z=0; z<3; ++z){alternateReset[z] = NULL;}
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
	zoneControlledOutput = NULL;
	for(register int z=0; z<100; ++z){zoneControlledCheckBox[z] = NULL;}
	for(register int z=0; z<100; ++z){zoneControlledNotes[z] = NULL;}
	for(register int z=0; z<100; ++z){zoneControlledSliders[z] = NULL;}
	for(register int z=0; z<3; ++z){sequenceOutput[z] = NULL;}
	for(register int z=0; z<3; ++z){sequenceFile[z] = wxT("");}
	for(register int z=0; z<3; ++z){mouseOutput[z] = NULL;}
	for(register int z=0; z<3; ++z){mouseX[z] = NULL;}
	for(register int z=0; z<3; ++z){mouseY[z] = NULL;}
	for(register int z=0; z<3; ++z){outputChannel[z] = NULL;} 
	for(register int z=0; z<3; ++z){outputNote[z] = NULL;}
	for(register int z=0; z<3; ++z){priority[z] = NULL;}
	for(register int z=0; z<3; ++z){gravity[z] = NULL;}
	velocityBalance = NULL;
	hasRim = NULL;
	enableCC = NULL; 
	ccOutputChannel = NULL;
	ccOutputNote = NULL;
	ccOutputHighCompressor = NULL;
	ccOutputLowCompressor = NULL;
	for(register int z=0; z<3; ++z){sampleFolder[z] = wxT("");}

	//Corners and edges
	topLeftCornerSideImage = NULL;
	topLeftCornerTopImage = NULL;
	topEdge1Image = NULL;
	topEdge2Image = NULL;
	topEdge3Image = NULL;
	topEdge4Image = NULL;
	leftEdge1Image = NULL;
	leftEdge2Image = NULL;
	leftEdge3Image = NULL;
	leftEdge4Image = NULL;
	leftEdge5Image = NULL;
	leftEdge6Image = NULL;
	leftEdge7Image = NULL;
	leftEdge8Image = NULL;
   
	zone1Button = NULL;
	zone2Button = NULL;
	zone3Button = NULL;
	zone1SelectedButton = NULL;
	zone2SelectedButton = NULL;
	zone3SelectedButton = NULL;
	inputButton = NULL;
	inputSelectedButton = NULL;
	retriggerButton = NULL;
	retriggerSelectedButton = NULL;
	dynamicsButton = NULL;
	dynamicsSelectedButton = NULL;
	outputButton = NULL;
	outputSelectedButton = NULL;
	multiZoneButton = NULL;
	multiZoneSelectedButton = NULL;
	okButton = NULL;
	cancelButton = NULL;
		
	inputPanel = NULL;
	learnButton = NULL;
	device = NULL;
	info = NULL;
	drumTypeBox = NULL;
	zonesSelectBox = NULL;
	//zonenums = NULL;  FIXME  cannot make wxArrayString null
	knob = NULL;
	knobValue = NULL;
	keyboardImage = NULL;
	audioDeviceImage = NULL;
	midiDeviceImage = NULL;
	joystickImage = NULL;
		
	retriggerPanel = NULL;
	retriggerBox = NULL;
	retriggerDetectButton = NULL;
	retriggerResetButton = NULL;
	retriggerOkButton = NULL;
	retriggerCancelButton = NULL;
		
	dynamicsPanel = NULL;
	curve = NULL;
	compressorSlider = NULL;
	cutoffSlider = NULL;
	lowPercentSlider = NULL;
	highPercentSlider = NULL;
	lowCompressorText = NULL;
	highCompressorText = NULL;
	lowLimiterText = NULL;
	highLimiterText = NULL;
	lowPercentText = NULL;
	highPercentText = NULL;
	antiMachineGunBox = NULL;
	MidiCCControlledBox = NULL;
	MidiCCControlledNumber = NULL;
	velocityDialogButton = NULL;
	velocityDialog = NULL;
		
	outputPanel = NULL;
	basicOutputButton = NULL;
	alternatingOutputButton = NULL;
	midiCCControlledOutputButton = NULL;
	velocityControlledOutputButton = NULL;
	zoneControlledOutputButton = NULL;
	sequenceOutputButton = NULL;
	midiOutChannelBox = NULL;	
	noteOffBox = NULL;
		
	sampleDialog = NULL;
	outputSample = NULL;
	sampleText = NULL;
		
	basicOutputPanel = NULL;
	midiNoteText = NULL;
	midiOutNoteBox = NULL;
		
	alternatingOutputPanel = NULL;
	alternateResetText = NULL;
	alternateResetBox = NULL;
	alternateRandomBox = NULL;
	alternateBox[8] = NULL;
	alternateNoteBox[10] = NULL;
		
	midiCCControlledOutputPanel = NULL;
	midiCCControlledOutputNoteText = NULL;
	midiCCControlledInputNoteBox = NULL;
	midiCCBox[8] = NULL;
	midiCCNoteBox[10] = NULL;
	midiCCText[10] = NULL;
	midiCCControlledSlider = NULL;
		
	velocityControlledOutputPanel = NULL;
	velocityBox[8] = NULL;
	velocityNoteBox[10] = NULL;
	velocityText[10] = NULL;
	velocityControlledSlider = NULL;
		
	zoneControlledOutputPanel = NULL;
	zoneBox[8] = NULL;
	zoneNoteBox[10] = NULL;
	zoneText[10] = NULL;
	zoneControlledSlider = NULL;
		
	multiZonePanel = NULL;
	multiZoneWaitTimeBox = NULL;
	waitTimeDetectButton = NULL;
	waitTimeResetButton = NULL;
	waitTimeOkButton = NULL;
	waitTimeCancelButton = NULL;
	priority1 = NULL;
	priority2 = NULL;
	priority3 = NULL;
	gravity1 = NULL;
	gravity2 = NULL;
	gravity3 = NULL;
	velocityBalanceBox = NULL;
	hasRimBox = NULL;
	enableCCBox = NULL; 
	ccOutputChannelBox = NULL;
	ccOutputNoteBox = NULL;
	ccOutputHighCompressorBox = NULL;
	ccOutputLowCompressorBox = NULL;
	velToPosAvgButton = NULL;
	velToPosAvgDlg = NULL;
}

////////////////////////////////
void TriggerDialog::VarsToTemp()
{
	//Store the data temporarily in case we hit cancel and want to revert back.
	drumType = trigger->trackProc->n[trigger->trackNum].drumType;
	zones = trigger->trackProc->n[trigger->trackNum].zones;
	multiZoneWaitTime = trigger->trackProc->n[trigger->trackNum].multiZoneWaitTime;
	velocityBalance = trigger->trackProc->n[trigger->trackNum].velocityBalance;
	hasRim = trigger->trackProc->n[trigger->trackNum].hasRim;
	enableCC = trigger->trackProc->n[trigger->trackNum].enableCC;
	ccOutputChannel = trigger->trackProc->n[trigger->trackNum].ccOutputChannel;
	ccOutputNote = trigger->trackProc->n[trigger->trackNum].ccOutputNote;
	ccOutputHighCompressor = trigger->trackProc->n[trigger->trackNum].ccOutputHighCompressor;
	ccOutputLowCompressor = trigger->trackProc->n[trigger->trackNum].ccOutputLowCompressor;
	
	for(int i=0; i<3; ++i){
		deviceName[i] = trigger->trackProc->n[trigger->trackNum].deviceName[i];
		inputDetails[i] = trigger->trackProc->n[trigger->trackNum].inputDetails[i];
		inputCode[i] = trigger->trackProc->n[trigger->trackNum].inputCode[i];
        preGain[i] = trigger->trackProc->n[trigger->trackNum].preGain[i];
		preVolume[i] = trigger->trackProc->n[trigger->trackNum].preVolume[i];
		outputNote[i] = trigger->trackProc->n[trigger->trackNum].outputNote[i];
		outputChannel[i] = trigger->trackProc->n[trigger->trackNum].outputChannel[i]; 
		audioThreshold[i] = trigger->trackProc->n[trigger->trackNum].audioThreshold[i];
		retrigger[i] = trigger->trackProc->n[trigger->trackNum].retrigger[i];
		crosstalk[i] = trigger->trackProc->n[trigger->trackNum].crosstalk[i];
		lowCompressor[i] = trigger->trackProc->n[trigger->trackNum].lowCompressor[i];
		highCompressor[i] = trigger->trackProc->n[trigger->trackNum].highCompressor[i];
		lowLimiter[i] = trigger->trackProc->n[trigger->trackNum].lowLimiter[i];
		highLimiter[i] = trigger->trackProc->n[trigger->trackNum].highLimiter[i];
		lowPercent[i] = trigger->trackProc->n[trigger->trackNum].lowPercent[i];
		highPercent[i] = trigger->trackProc->n[trigger->trackNum].highPercent[i];
		antiMachineGunTime[i] = trigger->trackProc->n[trigger->trackNum].antiMachineGunTime[i];
		noteOff[i] = trigger->trackProc->n[trigger->trackNum].noteOff[i];
		basicOutput[i] = trigger->trackProc->n[trigger->trackNum].basicOutput[i];
		alternateOutput[i] = trigger->trackProc->n[trigger->trackNum].alternateOutput[i];
		alternateRandom[i] = trigger->trackProc->n[trigger->trackNum].alternateRandom[i];
		midiCCControlledOutput[i] = trigger->trackProc->n[trigger->trackNum].midiCCControlledOutput[i];
		velocityControlledOutput[i] = trigger->trackProc->n[trigger->trackNum].velocityControlledOutput[i];
		zoneControlledOutput = trigger->trackProc->n[trigger->trackNum].zoneControlledOutput;
		sequenceOutput[i] = trigger->trackProc->n[trigger->trackNum].sequenceOutput[i];
		sequenceFile[i] = trigger->trackProc->n[trigger->trackNum].sequenceFile[i];
		sequenceOverlap[i] = trigger->trackProc->n[trigger->trackNum].sequenceOverlap[i];
		mouseOutput[i] = trigger->trackProc->n[trigger->trackNum].mouseOutput[i];
		mouseX[i] = trigger->trackProc->n[trigger->trackNum].mouseX[i];
		mouseY[i] = trigger->trackProc->n[trigger->trackNum].mouseY[i];
		midiCCControlledInputNote[i] = trigger->trackProc->n[trigger->trackNum].midiCCControlledInputNote[i];
		alternateReset[i] = trigger->trackProc->n[trigger->trackNum].alternateReset[i];
		//sampleFolder[i] = trigger->trackProc->n[trigger->trackNum].sampleFolder[i];
        
		for(int n=0; n<100; ++n){
			alternateCheckBox[i][n] = trigger->trackProc->n[trigger->trackNum].alternateCheckBox[i][n];
    		alternateNotes[i][n] = trigger->trackProc->n[trigger->trackNum].alternateNotes[i][n];
			midiCCControlledCheckBox[i][n] = trigger->trackProc->n[trigger->trackNum].midiCCControlledCheckBox[i][n];
     		midiCCControlledNotes[i][n] = trigger->trackProc->n[trigger->trackNum].midiCCControlledNotes[i][n];
			midiCCControlledSliders[i][n] = trigger->trackProc->n[trigger->trackNum].midiCCControlledSliders[i][n];
			velocityControlledCheckBox[i][n] = trigger->trackProc->n[trigger->trackNum].velocityControlledCheckBox[i][n];
		    velocityControlledNotes[i][n] = trigger->trackProc->n[trigger->trackNum].velocityControlledNotes[i][n];
			velocityControlledSliders[i][n] = trigger->trackProc->n[trigger->trackNum].velocityControlledSliders[i][n];
			zoneControlledCheckBox[n] = trigger->trackProc->n[trigger->trackNum].zoneControlledCheckBox[n];
		    zoneControlledNotes[n] = trigger->trackProc->n[trigger->trackNum].zoneControlledNotes[n];
			zoneControlledSliders[n] = trigger->trackProc->n[trigger->trackNum].zoneControlledSliders[n];
		}

		pointsZone1 = trigger->trackProc->n[trigger->trackNum].pointsZone1;
		pointsZone2 = trigger->trackProc->n[trigger->trackNum].pointsZone2;
		pointsZone3 = trigger->trackProc->n[trigger->trackNum].pointsZone3;

		for(int z=0; z<127; ++z){
			curveVelocities[i][z] = trigger->trackProc->n[trigger->trackNum].dynamics[i][z];
		}

		midiCCControlledVelocity[i] = trigger->trackProc->n[trigger->trackNum].midiCCControlledVelocity[i];
		midiCCControlledVelocityNote[i] = trigger->trackProc->n[trigger->trackNum].midiCCControlledVelocityNote[i];

		priority[i] = trigger->trackProc->n[trigger->trackNum].priority[i];
		gravity[i] = trigger->trackProc->n[trigger->trackNum].gravity[i];		
	}
}

///////////////////////////////
void TriggerDialog::VarsToDlg()
{
	//place the track Database data onto the dialog
	device->SetLabel(trigger->trackProc->n[trigger->trackNum].deviceName[currentZone]);
	info->SetLabel(trigger->trackProc->n[trigger->trackNum].inputDetails[currentZone]);
	knob->SetValue(trigger->trackProc->n[trigger->trackNum].preGain[currentZone]); //pulling from (volume[currentZone] * 1000 / 254 - 127) is the same
	knob->ResetStoredValue(); //so the knob dosn't jump after switching zones
	int temp = trigger->trackProc->n[trigger->trackNum].preVolume[currentZone];
	knobValue->SetLabel(wxString::Format(wxT("%d"), temp));
	drumTypeBox->SetSelection(trigger->trackProc->n[trigger->trackNum].drumType);
	zonesSelectBox->SetValue(wxString::Format(wxT("%d"), trigger->trackProc->n[trigger->trackNum].zones));
	midiOutNoteBox->Set(trigger->trackProc->n[trigger->trackNum].outputNote[currentZone]);
	midiOutChannelBox->Set(trigger->trackProc->n[trigger->trackNum].outputChannel[currentZone]);
	retriggerBox->Set(trigger->trackProc->n[trigger->trackNum].retrigger[currentZone]);
	crosstalkBox->Set(trigger->trackProc->n[trigger->trackNum].crosstalk[currentZone]);
	
	compressorSlider->SetValue(0, trigger->trackProc->n[trigger->trackNum].lowCompressor[currentZone]);
	compressorSlider->SetValue(1, trigger->trackProc->n[trigger->trackNum].highCompressor[currentZone]);
	cutoffSlider->SetValue(0, trigger->trackProc->n[trigger->trackNum].lowLimiter[currentZone]);
	cutoffSlider->SetValue(1, trigger->trackProc->n[trigger->trackNum].highLimiter[currentZone]);
	lowPercentSlider->SetValue(0, trigger->trackProc->n[trigger->trackNum].lowPercent[currentZone]);
	highPercentSlider->SetValue(0, trigger->trackProc->n[trigger->trackNum].highPercent[currentZone]);
	lowCompressorText->SetLabel(wxString::Format(wxT("%d"), trigger->trackProc->n[trigger->trackNum].lowCompressor[currentZone]));
	highCompressorText->SetLabel(wxString::Format(wxT("%d"), trigger->trackProc->n[trigger->trackNum].highCompressor[currentZone]));
	lowLimiterText->SetLabel(wxString::Format(wxT("%d"), trigger->trackProc->n[trigger->trackNum].lowLimiter[currentZone]));
	highLimiterText->SetLabel(wxString::Format(wxT("%d"), trigger->trackProc->n[trigger->trackNum].highLimiter[currentZone]));
	lowPercentText->SetLabel(wxString::Format(wxT("%d"), trigger->trackProc->n[trigger->trackNum].lowPercent[currentZone]));
	highPercentText->SetLabel(wxString::Format(wxT("%d"), trigger->trackProc->n[trigger->trackNum].highPercent[currentZone]));

	multiZoneWaitTimeBox->Set(trigger->trackProc->n[trigger->trackNum].multiZoneWaitTime);
	priority1->Set(trigger->trackProc->n[trigger->trackNum].priority[0]);
	priority2->Set(trigger->trackProc->n[trigger->trackNum].priority[1]);
	priority3->Set(trigger->trackProc->n[trigger->trackNum].priority[2]);
	gravity1->Set(trigger->trackProc->n[trigger->trackNum].gravity[0]);
	gravity2->Set(trigger->trackProc->n[trigger->trackNum].gravity[1]);
	gravity3->Set(trigger->trackProc->n[trigger->trackNum].gravity[2]);
	velocityBalanceBox->Set(trigger->trackProc->n[trigger->trackNum].velocityBalance);
	hasRimBox->SetValue(trigger->trackProc->n[trigger->trackNum].hasRim);
	enableCCBox->SetValue(trigger->trackProc->n[trigger->trackNum].enableCC);
	ccOutputChannelBox->Set(trigger->trackProc->n[trigger->trackNum].ccOutputChannel);
	ccOutputNoteBox->Set(trigger->trackProc->n[trigger->trackNum].ccOutputNote);
	ccOutputHighCompressorBox->Set(trigger->trackProc->n[trigger->trackNum].ccOutputHighCompressor);
	ccOutputLowCompressorBox->Set(trigger->trackProc->n[trigger->trackNum].ccOutputLowCompressor);
	
	antiMachineGunBox->Set(trigger->trackProc->n[trigger->trackNum].antiMachineGunTime[currentZone]);
	noteOffBox->SetValue(trigger->trackProc->n[trigger->trackNum].noteOff[currentZone]);
	basicOutputButton->SetValue(trigger->trackProc->n[trigger->trackNum].basicOutput[currentZone]);
	alternatingOutputButton->SetValue(trigger->trackProc->n[trigger->trackNum].alternateOutput[currentZone]);
	midiCCControlledOutputButton->SetValue(trigger->trackProc->n[trigger->trackNum].midiCCControlledOutput[currentZone]);
	midiCCControlledInputNoteBox->Set(trigger->trackProc->n[trigger->trackNum].midiCCControlledInputNote[currentZone]);
	velocityControlledOutputButton->SetValue(trigger->trackProc->n[trigger->trackNum].velocityControlledOutput[currentZone]);
	zoneControlledOutputButton->SetValue(trigger->trackProc->n[trigger->trackNum].zoneControlledOutput);
	sequenceOutputButton->SetValue(trigger->trackProc->n[trigger->trackNum].sequenceOutput[currentZone]);
	filePath->SetValue(trigger->trackProc->n[trigger->trackNum].sequenceFile[currentZone]);
	sequenceOverlapBox->SetValue(trigger->trackProc->n[trigger->trackNum].sequenceOverlap[currentZone]);
	mouseOutputButton->SetValue(trigger->trackProc->n[trigger->trackNum].mouseOutput[currentZone]);
	mouseXBox->Set(trigger->trackProc->n[trigger->trackNum].mouseX[currentZone]);
	mouseYBox->Set(trigger->trackProc->n[trigger->trackNum].mouseY[currentZone]);
	alternateResetBox->Set(trigger->trackProc->n[trigger->trackNum].alternateReset[currentZone]);
	alternateRandomBox->SetValue(trigger->trackProc->n[trigger->trackNum].alternateRandom[currentZone]);

	//sampleText->SetLabel(trigger->trackProc->n[trigger->trackNum].sampleFolder[currentZone]);

	for(int n=0; n<8; ++n){
		alternateBox[n]->SetValue(trigger->trackProc->n[trigger->trackNum].alternateCheckBox[currentZone][n+2]);
	}
	UpdateAlternateBoxes();

	for(int n=0; n<10; ++n){
		alternateNoteBox[n]->Set(trigger->trackProc->n[trigger->trackNum].alternateNotes[currentZone][n]);
	}

	for(int n=0; n<8; ++n){
		midiCCBox[n]->SetValue(trigger->trackProc->n[trigger->trackNum].midiCCControlledCheckBox[currentZone][n+2]);
	}
	UpdateMidiCCBoxes();
	UpdateMidiCCSliders();
	//Set sliders here.
	for(int n=0; n<midiCCControlledSlider->knobCount; ++n){
		midiCCControlledSlider->SetValue(n, trigger->trackProc->n[trigger->trackNum].midiCCControlledSliders[currentZone][n]);
	}
	UpdateMidiCCText();
	
	for(int n=0; n<10; ++n){
		midiCCNoteBox[n]->Set(trigger->trackProc->n[trigger->trackNum].midiCCControlledNotes[currentZone][n]);
	}

	for (int n=0; n<8; ++n){
		velocityBox[n]->SetValue(trigger->trackProc->n[trigger->trackNum].velocityControlledCheckBox[currentZone][n+2]);
	}
	UpdateVelocityBoxes();
	UpdateVelocitySliders();
	//Set sliders here.
	for(int n=0; n<velocityControlledSlider->knobCount; ++n){
		velocityControlledSlider->SetValue(n, trigger->trackProc->n[trigger->trackNum].velocityControlledSliders[currentZone][n]);
	}
	UpdateVelocityText();

	for(int n=0; n<10; ++n){
		velocityNoteBox[n]->Set(trigger->trackProc->n[trigger->trackNum].velocityControlledNotes[currentZone][n]);
	}

	for (int n=0; n<8; ++n){
		zoneBox[n]->SetValue(trigger->trackProc->n[trigger->trackNum].zoneControlledCheckBox[n+2]);
	}
	UpdateZoneBoxes();
	UpdateZoneSliders();
	//Set sliders here.
	for(int n=0; n<zoneControlledSlider->knobCount; ++n){
		zoneControlledSlider->SetValue(n, trigger->trackProc->n[trigger->trackNum].zoneControlledSliders[n]);
	}
	UpdateZoneText();

	for(int n=0; n<10; ++n){
		zoneNoteBox[n]->Set(trigger->trackProc->n[trigger->trackNum].zoneControlledNotes[n]);
	}

	if(currentZone == 0){
		curve->points = trigger->trackProc->n[trigger->trackNum].pointsZone1;
		curve->Refresh();
	}
	if(currentZone == 1){
		curve->points = trigger->trackProc->n[trigger->trackNum].pointsZone2;
		curve->Refresh();
	}
	if(currentZone == 2){
		curve->points = trigger->trackProc->n[trigger->trackNum].pointsZone3;
		curve->Refresh();
	}

	curve->SetLowCompressor(trigger->trackProc->n[trigger->trackNum].lowCompressor[currentZone]);
	curve->SetHighCompressor(trigger->trackProc->n[trigger->trackNum].highCompressor[currentZone]);
	curve->SetLowLimiter(trigger->trackProc->n[trigger->trackNum].lowLimiter[currentZone]);
	curve->SetHighLimiter(trigger->trackProc->n[trigger->trackNum].highLimiter[currentZone]);
	curve->SetLowPercent(trigger->trackProc->n[trigger->trackNum].lowPercent[currentZone]);
	curve->SetHighPercent(trigger->trackProc->n[trigger->trackNum].highPercent[currentZone]);

	MidiCCControlledBox->SetValue(trigger->trackProc->n[trigger->trackNum].midiCCControlledVelocity[currentZone]);
	MidiCCControlledNumber->Set(trigger->trackProc->n[trigger->trackNum].midiCCControlledVelocityNote[currentZone]);

	UpdateInputImage(0);
	UpdateOutputType();
}

////////////////////////////////
void TriggerDialog::TempToVars()
{
	//Transfer the temporary back if we hit cancel
	trigger->trackProc->n[trigger->trackNum].drumType = drumType;
	trigger->trackProc->n[trigger->trackNum].zones = zones;
	trigger->trackProc->n[trigger->trackNum].multiZoneWaitTime = multiZoneWaitTime;
	trigger->trackProc->n[trigger->trackNum].velocityBalance = velocityBalance;
	trigger->trackProc->n[trigger->trackNum].hasRim = hasRim;
	trigger->trackProc->n[trigger->trackNum].enableCC = enableCC;
	trigger->trackProc->n[trigger->trackNum].ccOutputChannel = ccOutputChannel;
	trigger->trackProc->n[trigger->trackNum].ccOutputNote = ccOutputNote;
	trigger->trackProc->n[trigger->trackNum].ccOutputHighCompressor = ccOutputHighCompressor;
	trigger->trackProc->n[trigger->trackNum].ccOutputLowCompressor = ccOutputLowCompressor;
	
	for(int i=0; i<3; ++i){
		trigger->trackProc->n[trigger->trackNum].deviceName[i] = deviceName[i];
		trigger->trackProc->n[trigger->trackNum].inputDetails[i] = inputDetails[i];
		trigger->trackProc->n[trigger->trackNum].inputCode[i] = inputCode[i];
		trigger->trackProc->n[trigger->trackNum].preGain[i] = preGain[i];
		trigger->trackProc->n[trigger->trackNum].preVolume[i] = preVolume[i];
		trigger->trackProc->n[trigger->trackNum].outputNote[i] = outputNote[i];
		trigger->trackProc->n[trigger->trackNum].outputChannel[i] = outputChannel[i];
		trigger->trackProc->n[trigger->trackNum].audioThreshold[i] = audioThreshold[i];
		trigger->trackProc->n[trigger->trackNum].retrigger[i] = retrigger[i];
		trigger->trackProc->n[trigger->trackNum].crosstalk[i] = crosstalk[i];
		trigger->trackProc->n[trigger->trackNum].lowCompressor[i] = lowCompressor[i];
		trigger->trackProc->n[trigger->trackNum].highCompressor[i] = highCompressor[i];
		trigger->trackProc->n[trigger->trackNum].lowLimiter[i] = lowLimiter[i];
		trigger->trackProc->n[trigger->trackNum].highLimiter[i] = highLimiter[i];
		trigger->trackProc->n[trigger->trackNum].lowPercent[i] = lowPercent[i];
		trigger->trackProc->n[trigger->trackNum].highPercent[i] = highPercent[i];
		trigger->trackProc->n[trigger->trackNum].antiMachineGunTime[i] = antiMachineGunTime[i];
		trigger->trackProc->n[trigger->trackNum].noteOff[i] = noteOff[i];
		trigger->trackProc->n[trigger->trackNum].basicOutput[i] = basicOutput[i];
		trigger->trackProc->n[trigger->trackNum].alternateOutput[i] = alternateOutput[i];
		trigger->trackProc->n[trigger->trackNum].midiCCControlledOutput[i] = midiCCControlledOutput[i];
		trigger->trackProc->n[trigger->trackNum].velocityControlledOutput[i] = velocityControlledOutput[i];
		trigger->trackProc->n[trigger->trackNum].zoneControlledOutput = zoneControlledOutput;
		trigger->trackProc->n[trigger->trackNum].sequenceOutput[i] = sequenceOutput[i];
		trigger->trackProc->n[trigger->trackNum].sequenceFile[i] = sequenceFile[i];
		trigger->trackProc->n[trigger->trackNum].sequenceOverlap[i] = sequenceOverlap[i];
		trigger->trackProc->n[trigger->trackNum].mouseOutput[i] = mouseOutput[i];
		trigger->trackProc->n[trigger->trackNum].mouseX[i] = mouseX[i];
		trigger->trackProc->n[trigger->trackNum].mouseY[i] = mouseY[i];
		trigger->trackProc->n[trigger->trackNum].midiCCControlledInputNote[i] = midiCCControlledInputNote[i];
		trigger->trackProc->n[trigger->trackNum].alternateReset[i] = alternateReset[i];
		trigger->trackProc->n[trigger->trackNum].alternateRandom[i] = alternateRandom[i];

		//trigger->trackProc->n[trigger->trackNum].sampleFolder[i] = sampleFolder[i];

		for(int n=0; n<100; ++n){
			trigger->trackProc->n[trigger->trackNum].alternateCheckBox[i][n] = alternateCheckBox[i][n];
			trigger->trackProc->n[trigger->trackNum].alternateNotes[i][n] = alternateNotes[i][n];
			trigger->trackProc->n[trigger->trackNum].midiCCControlledCheckBox[i][n] = midiCCControlledCheckBox[i][n];
			trigger->trackProc->n[trigger->trackNum].midiCCControlledNotes[i][n] = midiCCControlledNotes[i][n];
			trigger->trackProc->n[trigger->trackNum].midiCCControlledSliders[i][n] = midiCCControlledSliders[i][n];
			trigger->trackProc->n[trigger->trackNum].velocityControlledCheckBox[i][n] = velocityControlledCheckBox[i][n];
			trigger->trackProc->n[trigger->trackNum].velocityControlledNotes[i][n] = velocityControlledNotes[i][n];
			trigger->trackProc->n[trigger->trackNum].velocityControlledSliders[i][n] = velocityControlledSliders[i][n];
			trigger->trackProc->n[trigger->trackNum].zoneControlledCheckBox[n] = zoneControlledCheckBox[n];
			trigger->trackProc->n[trigger->trackNum].zoneControlledNotes[n] = zoneControlledNotes[n];
			trigger->trackProc->n[trigger->trackNum].zoneControlledSliders[n] = zoneControlledSliders[n];
		}		

		trigger->trackProc->n[trigger->trackNum].pointsZone1 = pointsZone1;
		trigger->trackProc->n[trigger->trackNum].pointsZone2 = pointsZone2;
		trigger->trackProc->n[trigger->trackNum].pointsZone3 = pointsZone3;

		for(int z=0; z<127; ++z){
			trigger->trackProc->n[trigger->trackNum].dynamics[i][z] = curveVelocities[i][z];
		}

		trigger->trackProc->n[trigger->trackNum].midiCCControlledVelocity[i] = midiCCControlledVelocity[i];
		trigger->trackProc->n[trigger->trackNum].midiCCControlledVelocityNote[i] = midiCCControlledVelocityNote[i];

		trigger->trackProc->n[trigger->trackNum].priority[i] = priority[i];
		trigger->trackProc->n[trigger->trackNum].gravity[i] = gravity[i];
	}
}

///////////////////////////////
void TriggerDialog::TempToDlg()
{
	//place the track Database data onto the dialog
	device->SetLabel(deviceName[currentZone]);
	info->SetLabel(inputDetails[currentZone]);
	knob->SetValue(preGain[currentZone]); //pulling from (volume[currentZone] * 1000 / 254 - 127) is the same
	knob->ResetStoredValue(); //so the knob dosn't jump after switching zones
	int temp = preVolume[currentZone];
	knobValue->SetLabel(wxString::Format(wxT("%d"), temp));
	drumTypeBox->SetSelection(drumType);
	zonesSelectBox->SetValue(wxString::Format(wxT("%d"), zones));
	midiOutNoteBox->Set(outputNote[currentZone]);
	midiOutChannelBox->Set(outputChannel[currentZone]);
	retriggerBox->Set(retrigger[currentZone]);
	crosstalkBox->Set(crosstalk[currentZone]);

	compressorSlider->SetValue(0, lowCompressor[currentZone]);
	compressorSlider->SetValue(1, highCompressor[currentZone]);
	cutoffSlider->SetValue(0, lowLimiter[currentZone]);
	cutoffSlider->SetValue(1, highLimiter[currentZone]);
	lowPercentSlider->SetValue(0, lowPercent[currentZone]);
	highPercentSlider->SetValue(0, highPercent[currentZone]);
	lowCompressorText->SetLabel(wxString::Format(wxT("%d"), lowCompressor[currentZone]));
	highCompressorText->SetLabel(wxString::Format(wxT("%d"), highCompressor[currentZone]));
	lowLimiterText->SetLabel(wxString::Format(wxT("%d"), lowLimiter[currentZone]));
	highLimiterText->SetLabel(wxString::Format(wxT("%d"), highLimiter[currentZone]));
	lowPercentText->SetLabel(wxString::Format(wxT("%d"), lowPercent[currentZone]));
	highPercentText->SetLabel(wxString::Format(wxT("%d"), highPercent[currentZone]));

	multiZoneWaitTimeBox->Set(multiZoneWaitTime);
	priority1->Set(priority[0]);
	priority2->Set(priority[1]);
	priority3->Set(priority[2]);
	gravity1->Set(gravity[0]);
	gravity2->Set(gravity[1]);
	gravity3->Set(gravity[2]);
	velocityBalanceBox->Set(velocityBalance);
	hasRimBox->SetValue(hasRim);
	enableCCBox->SetValue(enableCC);
	ccOutputChannelBox->Set(ccOutputChannel);
	ccOutputNoteBox->Set(ccOutputNote);
	ccOutputHighCompressorBox->Set(ccOutputHighCompressor);
	ccOutputLowCompressorBox->Set(ccOutputLowCompressor);
	antiMachineGunBox->Set(antiMachineGunTime[currentZone]);
	noteOffBox->SetValue(noteOff[currentZone]);
	basicOutputButton->SetValue(basicOutput[currentZone]);
	alternatingOutputButton->SetValue(alternateOutput[currentZone]);
	midiCCControlledOutputButton->SetValue(midiCCControlledOutput[currentZone]);
	midiCCControlledInputNoteBox->Set(midiCCControlledInputNote[currentZone]);
	velocityControlledOutputButton->SetValue(velocityControlledOutput[currentZone]);
	zoneControlledOutputButton->SetValue(zoneControlledOutput);
	sequenceOutputButton->SetValue(sequenceOutput[currentZone]);
	mouseOutputButton->SetValue(mouseOutput[currentZone]);
	alternateResetBox->Set(alternateReset[currentZone]);
	alternateRandomBox->SetValue(alternateRandom[currentZone]);

	sampleText->SetLabel(sampleFolder[currentZone]);

	alternateBox[0]->SetValue(alternateCheckBox[currentZone][2]);
	alternateBox[1]->SetValue(alternateCheckBox[currentZone][3]);
	alternateBox[2]->SetValue(alternateCheckBox[currentZone][4]);
	alternateBox[3]->SetValue(alternateCheckBox[currentZone][5]);
	alternateBox[4]->SetValue(alternateCheckBox[currentZone][6]);
	alternateBox[5]->SetValue(alternateCheckBox[currentZone][7]);
	alternateBox[6]->SetValue(alternateCheckBox[currentZone][8]);
	alternateBox[7]->SetValue(alternateCheckBox[currentZone][9]);
	UpdateAlternateBoxes();

	alternateNoteBox[0]->Set(alternateNotes[currentZone][0]);
	alternateNoteBox[1]->Set(alternateNotes[currentZone][1]);
	alternateNoteBox[2]->Set(alternateNotes[currentZone][2]);
	alternateNoteBox[3]->Set(alternateNotes[currentZone][3]);
	alternateNoteBox[4]->Set(alternateNotes[currentZone][4]);
	alternateNoteBox[5]->Set(alternateNotes[currentZone][5]);
	alternateNoteBox[6]->Set(alternateNotes[currentZone][6]);
	alternateNoteBox[7]->Set(alternateNotes[currentZone][7]);
	alternateNoteBox[8]->Set(alternateNotes[currentZone][8]);
	alternateNoteBox[9]->Set(alternateNotes[currentZone][9]);

	midiCCBox[0]->SetValue(midiCCControlledCheckBox[currentZone][2]);
	midiCCBox[1]->SetValue(midiCCControlledCheckBox[currentZone][3]);
	midiCCBox[2]->SetValue(midiCCControlledCheckBox[currentZone][4]);
	midiCCBox[3]->SetValue(midiCCControlledCheckBox[currentZone][5]);
	midiCCBox[4]->SetValue(midiCCControlledCheckBox[currentZone][6]);
	midiCCBox[5]->SetValue(midiCCControlledCheckBox[currentZone][7]);
	midiCCBox[6]->SetValue(midiCCControlledCheckBox[currentZone][8]);
	midiCCBox[7]->SetValue(midiCCControlledCheckBox[currentZone][9]);
	UpdateMidiCCBoxes();
	UpdateMidiCCSliders();
	//Set sliders here.
	for(int n=0; n<midiCCControlledSlider->knobCount; ++n){
		midiCCControlledSlider->SetValue(n, midiCCControlledSliders[currentZone][n]);
	}
	UpdateMidiCCText();

	midiCCNoteBox[0]->Set(midiCCControlledNotes[currentZone][0]);
	midiCCNoteBox[1]->Set(midiCCControlledNotes[currentZone][1]);
	midiCCNoteBox[2]->Set(midiCCControlledNotes[currentZone][2]);
	midiCCNoteBox[3]->Set(midiCCControlledNotes[currentZone][3]);
	midiCCNoteBox[4]->Set(midiCCControlledNotes[currentZone][4]);
	midiCCNoteBox[5]->Set(midiCCControlledNotes[currentZone][5]);
	midiCCNoteBox[6]->Set(midiCCControlledNotes[currentZone][6]);
	midiCCNoteBox[7]->Set(midiCCControlledNotes[currentZone][7]);
	midiCCNoteBox[8]->Set(midiCCControlledNotes[currentZone][8]);
	midiCCNoteBox[9]->Set(midiCCControlledNotes[currentZone][9]);

	velocityBox[0]->SetValue(velocityControlledCheckBox[currentZone][2]);
	velocityBox[1]->SetValue(velocityControlledCheckBox[currentZone][3]);
	velocityBox[2]->SetValue(velocityControlledCheckBox[currentZone][4]);
	velocityBox[3]->SetValue(velocityControlledCheckBox[currentZone][5]);
	velocityBox[4]->SetValue(velocityControlledCheckBox[currentZone][6]);
	velocityBox[5]->SetValue(velocityControlledCheckBox[currentZone][7]);
	velocityBox[6]->SetValue(velocityControlledCheckBox[currentZone][8]);
	velocityBox[7]->SetValue(velocityControlledCheckBox[currentZone][9]);
	UpdateVelocityBoxes();
	UpdateVelocitySliders();
	//Set sliders here.
	for(int n=0; n<velocityControlledSlider->knobCount; ++n){
		velocityControlledSlider->SetValue(n, velocityControlledSliders[currentZone][n]);
	}
	UpdateVelocityText();

	velocityNoteBox[0]->Set(velocityControlledNotes[currentZone][0]);
	velocityNoteBox[1]->Set(velocityControlledNotes[currentZone][1]);
	velocityNoteBox[2]->Set(velocityControlledNotes[currentZone][2]);
	velocityNoteBox[3]->Set(velocityControlledNotes[currentZone][3]);
	velocityNoteBox[4]->Set(velocityControlledNotes[currentZone][4]);
	velocityNoteBox[5]->Set(velocityControlledNotes[currentZone][5]);
	velocityNoteBox[6]->Set(velocityControlledNotes[currentZone][6]);
	velocityNoteBox[7]->Set(velocityControlledNotes[currentZone][7]);
	velocityNoteBox[8]->Set(velocityControlledNotes[currentZone][8]);
	velocityNoteBox[9]->Set(velocityControlledNotes[currentZone][9]);

	zoneBox[0]->SetValue(zoneControlledCheckBox[2]);
	zoneBox[1]->SetValue(zoneControlledCheckBox[3]);
	zoneBox[2]->SetValue(zoneControlledCheckBox[4]);
	zoneBox[3]->SetValue(zoneControlledCheckBox[5]);
	zoneBox[4]->SetValue(zoneControlledCheckBox[6]);
	zoneBox[5]->SetValue(zoneControlledCheckBox[7]);
	zoneBox[6]->SetValue(zoneControlledCheckBox[8]);
	zoneBox[7]->SetValue(zoneControlledCheckBox[9]);
	UpdateZoneBoxes();
	UpdateZoneSliders();
	//Set sliders here.
	for(int n=0; n<zoneControlledSlider->knobCount; ++n){
		zoneControlledSlider->SetValue(n, zoneControlledSliders[n]);
	}
	UpdateZoneText();

	zoneNoteBox[0]->Set(zoneControlledNotes[0]);
	zoneNoteBox[1]->Set(zoneControlledNotes[1]);
	zoneNoteBox[2]->Set(zoneControlledNotes[2]);
	zoneNoteBox[3]->Set(zoneControlledNotes[3]);
	zoneNoteBox[4]->Set(zoneControlledNotes[4]);
	zoneNoteBox[5]->Set(zoneControlledNotes[5]);
	zoneNoteBox[6]->Set(zoneControlledNotes[6]);
	zoneNoteBox[7]->Set(zoneControlledNotes[7]);
	zoneNoteBox[8]->Set(zoneControlledNotes[8]);
	zoneNoteBox[9]->Set(zoneControlledNotes[9]);

	if(currentZone == 0){
		curve->points = pointsZone1;
		curve->Refresh();
	}
	if(currentZone == 1){
		curve->points = pointsZone2;
		curve->Refresh();
	}
	if(currentZone == 2){
		curve->points = pointsZone3;
		curve->Refresh();
	}

	curve->SetLowCompressor(lowCompressor[currentZone]);
	curve->SetHighCompressor(highCompressor[currentZone]);
	curve->SetLowLimiter(lowLimiter[currentZone]);
	curve->SetHighLimiter(highLimiter[currentZone]);
	curve->SetLowPercent(lowPercent[currentZone]);
	curve->SetHighPercent(highPercent[currentZone]);

	MidiCCControlledBox->SetValue(midiCCControlledVelocity[currentZone]);
	MidiCCControlledNumber->Set(midiCCControlledVelocityNote[currentZone]);

	UpdateZones();
	UpdateInputImage(0);
	UpdateOutputType();
}
////////////////////////////////////////////////
void TriggerDialog::OnInput(GButtonEvent &event)
{
	UpdateSelection(wxT("input"));
}

////////////////////////////////////////////////////
void TriggerDialog::OnRetrigger(GButtonEvent &event)
{
	UpdateSelection(wxT("retrigger"));
}

////////////////////////////////////////////////////
void TriggerDialog::OnCrosstalk(GNumberBoxEvent &event)
{
	crosstalkBox->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].crosstalk[currentZone]);
}

//////////////////////////////////////////////////////
void TriggerDialog::OnAlternation(GButtonEvent &event)
{
	UpdateSelection(wxT("alternation"));
}

///////////////////////////////////////////////////
void TriggerDialog::OnDynamics(GButtonEvent &event)
{
	UpdateSelection(wxT("dynamics"));
}

/////////////////////////////////////////////////
void TriggerDialog::OnOutput(GButtonEvent &event)
{
	UpdateSelection(wxT("output"));
}

////////////////////////////////////////////////////
void TriggerDialog::OnMultiZone(GButtonEvent &event)
{
	UpdateSelection(wxT("multiZone"));
}

////////////////////////////////////////////////
void TriggerDialog::OnZone1(GButtonEvent &event)
{
	if(zonesSelectBox->GetValue() == wxT("2")){
		zone1SelectedButton->Show();
		zone2Button->Show();
		zone1Button->Hide();
		zone2SelectedButton->Hide();
	}
	if(zonesSelectBox->GetValue() == wxT("3")){
		zone2Button->Show();
		zone3Button->Show();
		zone1SelectedButton->Show();
		zone1Button->Hide();
		zone2SelectedButton->Hide();
		zone3SelectedButton->Hide();
	}

	currentZone = 0;
	VarsToDlg();
}

////////////////////////////////////////////////
void TriggerDialog::OnZone2(GButtonEvent &event)
{
	if(zonesSelectBox->GetValue() == wxT("2")){
		zone1Button->Show();
		zone2SelectedButton->Show();
		zone2Button->Hide();
		zone1SelectedButton->Hide();		
	}
	if(zonesSelectBox->GetValue() == wxT("3")){
		zone1Button->Show();
		zone3Button->Show();
		zone2SelectedButton->Show();
		zone2Button->Hide();
		zone1SelectedButton->Hide();
		zone3SelectedButton->Hide();
	}

	currentZone = 1;
	VarsToDlg();
}

////////////////////////////////////////////////
void TriggerDialog::OnZone3(GButtonEvent &event)
{
		zone1Button->Show();
		zone2Button->Show();
		zone3SelectedButton->Show();
		zone3Button->Hide();
		zone1SelectedButton->Hide();
		zone2SelectedButton->Hide();	

	currentZone = 2;
	VarsToDlg();
}

/////////////////////////////////////////////
void TriggerDialog::OnOk(GButtonEvent &event)
{
	Process::Learning = false;
	Process::detectingRetrigger = false;
	retriggerDetectButton->Show();
	retriggerResetButton->Hide();
	retriggerOkButton->Hide();
	retriggerCancelButton->Hide();

	Process::waitTimeTrackNum = 0;
	Process::detectingWaitTime = false;
	waitTimeDetectButton->Show();
	waitTimeResetButton->Hide();
	waitTimeOkButton->Hide();
	waitTimeCancelButton->Hide();

	VarsToTemp(); 
	Hide();	
}

/////////////////////////////////////////////////
void TriggerDialog::OnCancel(GButtonEvent &event)
{
	Close();
}

////////////////////////////////////////////////
void TriggerDialog::OnClose(wxCloseEvent &event)
{
	Process::Learning = false;
	Process::detectingRetrigger = false;
	retriggerDetectButton->Show();
	retriggerResetButton->Hide();
	retriggerOkButton->Hide();
	retriggerCancelButton->Hide();

	Process::waitTimeTrackNum = 0;
	Process::detectingWaitTime = false;
	waitTimeDetectButton->Show();
	waitTimeResetButton->Hide();
	waitTimeOkButton->Hide();
	waitTimeCancelButton->Hide();

	TempToVars();
	TempToDlg(); 
	Hide();
}

//////////////////////////////////////////////////
void TriggerDialog::UpdateInputImage(bool hideAll)
{
	//Device Images
	if(trigger->trackProc->n[trigger->trackNum].inputCode[currentZone] >= 100000 && 
	   trigger->trackProc->n[trigger->trackNum].inputCode[currentZone]  < 200000 && !hideAll){midiDeviceImage->Show();}
	else{midiDeviceImage->Hide();}

	if(trigger->trackProc->n[trigger->trackNum].inputCode[currentZone] >= 200000 && 
	   trigger->trackProc->n[trigger->trackNum].inputCode[currentZone]  < 300000 && !hideAll){audioDeviceImage->Show();}
	else{audioDeviceImage->Hide();}

	if(trigger->trackProc->n[trigger->trackNum].inputCode[currentZone] >= 300000 && 
	   trigger->trackProc->n[trigger->trackNum].inputCode[currentZone]  < 400000 && !hideAll){joystickImage->Show();}
	else{joystickImage->Hide();}

	if(trigger->trackProc->n[trigger->trackNum].inputCode[currentZone] >= 400000 && 
	   trigger->trackProc->n[trigger->trackNum].inputCode[currentZone]  < 500000 && !hideAll){keyboardImage->Show();}
	else{keyboardImage->Hide();}
}

////////////////////////////////////////////////////
void TriggerDialog::UpdateSelection(wxString string)
{
	if(string == wxT("input")){
		inputSelectedButton->Show();
		inputPanel->Show();
		retriggerButton->Show();
		dynamicsButton->Show();
		outputButton->Show();
		inputButton->Hide();
		retriggerSelectedButton->Hide();
		retriggerPanel->Hide();
		dynamicsSelectedButton->Hide();
		dynamicsPanel->Hide();
		outputSelectedButton->Hide();
		outputPanel->Hide();

		if(trigger->trackProc->n[trigger->trackNum].zones > 1){
			multiZoneButton->Show();
			multiZoneSelectedButton->Hide();
			multiZonePanel->Hide();
		}
	}

	if(string == wxT("retrigger")){
		inputButton->Show();
		retriggerSelectedButton->Show();
		retriggerPanel->Show();
		dynamicsButton->Show();
		outputButton->Show();	
		inputSelectedButton->Hide();
		inputPanel->Hide();
		retriggerButton->Hide();
		dynamicsSelectedButton->Hide();
		dynamicsPanel->Hide();
		outputSelectedButton->Hide();
		outputPanel->Hide();

		if(trigger->trackProc->n[trigger->trackNum].zones > 1){
			multiZoneButton->Show();
			multiZoneSelectedButton->Hide();
			multiZonePanel->Hide();
		}
	}

	if(string == wxT("dynamics")){
		inputButton->Show();
		retriggerButton->Show();
		dynamicsSelectedButton->Show();
		dynamicsPanel->Show();
		outputButton->Show();
		inputSelectedButton->Hide();
		inputPanel->Hide();	
		retriggerSelectedButton->Hide();
		retriggerPanel->Hide();
		dynamicsButton->Hide();
		outputSelectedButton->Hide();
		outputPanel->Hide();

		if(trigger->trackProc->n[trigger->trackNum].zones > 1){
			multiZoneButton->Show();
			multiZoneSelectedButton->Hide();
			multiZonePanel->Hide();
		}
	}

	if(string == wxT("output")){
		inputButton->Show();
		retriggerButton->Show();
		dynamicsButton->Show();
		outputSelectedButton->Show();
		outputPanel->Show();
		inputSelectedButton->Hide();
		inputPanel->Hide();
		retriggerSelectedButton->Hide();
		retriggerPanel->Hide();
		dynamicsSelectedButton->Hide();
		dynamicsPanel->Hide();
		outputButton->Hide();
		
		if(trigger->trackProc->n[trigger->trackNum].zones > 1){
			multiZoneButton->Show();
			multiZoneSelectedButton->Hide();
			multiZonePanel->Hide();
		}
	}

	if(string == wxT("multiZone")){
		inputButton->Show();
		retriggerButton->Show();
		dynamicsButton->Show();
		outputButton->Show();
		multiZoneSelectedButton->Show();
		multiZonePanel->Show();
		inputSelectedButton->Hide();
		inputPanel->Hide();
		retriggerSelectedButton->Hide();
		retriggerPanel->Hide();
		dynamicsSelectedButton->Hide();
		dynamicsPanel->Hide();
		outputSelectedButton->Hide();
		outputPanel->Hide();
		multiZoneButton->Hide();
	}
}

/////////////////////////////////
void TriggerDialog::UpdateZones()
{
	if(zonesSelectBox->GetValue() == wxT("1")){
		zone1Button->Hide();
		zone2Button->Hide();
		zone3Button->Hide();
		zone1SelectedButton->Hide();
		zone2SelectedButton->Hide();
		zone3SelectedButton->Hide();
		multiZoneButton->Hide();
		multiZoneSelectedButton->Hide();
		multiZonePanel->Hide();
		trigger->trackProc->n[trigger->trackNum].zoneControlledOutput = false;
		zoneControlledOutputButton->Disable();
		trigger->trackProc->n[trigger->trackNum].basicOutput[0] = true;
	}

	if(zonesSelectBox->GetValue() == wxT("2")){
		zone1Button->Hide();
		zone2Button->Show();
		zone3Button->Hide();
		zone1SelectedButton->Show();
		zone2SelectedButton->Hide();
		zone3SelectedButton->Hide();
		multiZoneButton->Show();
		zoneControlledOutputButton->Enable();
	}

	if(zonesSelectBox->GetValue() == wxT("3")){
		zone1Button->Hide();
		zone2Button->Show();
		zone3Button->Show();
		zone1SelectedButton->Show();
		zone2SelectedButton->Hide();
		zone3SelectedButton->Hide();
		multiZoneButton->Show();
		zoneControlledOutputButton->Enable();
	}

	currentZone = 0;
	VarsToDlg();
}

//////////////////////////////////////
void TriggerDialog::UpdateOutputType()
{
	if((basicOutputButton->GetValue() == false) &&
		(alternatingOutputButton->GetValue() == false) &&
		(midiCCControlledOutputButton->GetValue() == false) &&
		(velocityControlledOutputButton->GetValue() == false) &&
		(zoneControlledOutputButton->GetValue() == false) &&
		(sequenceOutputButton->GetValue() == false) &&
		(mouseOutputButton->GetValue() == false)){
		basicOutputButton->SetValue(true);
	}

	if(basicOutputButton->GetValue() == true){
		trigger->trackProc->n[trigger->trackNum].basicOutput[currentZone] = true;
		trigger->trackProc->n[trigger->trackNum].alternateOutput[currentZone] = false;
		trigger->trackProc->n[trigger->trackNum].midiCCControlledOutput[currentZone] = false;
		trigger->trackProc->n[trigger->trackNum].velocityControlledOutput[currentZone] = false;
		trigger->trackProc->n[trigger->trackNum].zoneControlledOutput = false;
		trigger->trackProc->n[trigger->trackNum].sequenceOutput[currentZone] = false;
		trigger->trackProc->n[trigger->trackNum].mouseOutput[currentZone] = false;
		basicOutputPanel->Show();
		alternatingOutputPanel->Hide();
		midiCCControlledOutputPanel->Hide();
		velocityControlledOutputPanel->Hide();
		zoneControlledOutputPanel->Hide();
		sequenceOutputPanel->Hide();
		mouseOutputPanel->Hide();
	}
	if(alternatingOutputButton->GetValue() == true){
		trigger->trackProc->n[trigger->trackNum].basicOutput[currentZone] = false;
		trigger->trackProc->n[trigger->trackNum].alternateOutput[currentZone] = true;
		trigger->trackProc->n[trigger->trackNum].midiCCControlledOutput[currentZone] = false;
		trigger->trackProc->n[trigger->trackNum].velocityControlledOutput[currentZone] = false;
		trigger->trackProc->n[trigger->trackNum].zoneControlledOutput = false;
		trigger->trackProc->n[trigger->trackNum].sequenceOutput[currentZone] = false;
		trigger->trackProc->n[trigger->trackNum].mouseOutput[currentZone] = false;
		basicOutputPanel->Hide();
		alternatingOutputPanel->Show();
		midiCCControlledOutputPanel->Hide();
        velocityControlledOutputPanel->Hide();
		zoneControlledOutputPanel->Hide();
		sequenceOutputPanel->Hide();
		mouseOutputPanel->Hide();
	}
	if(midiCCControlledOutputButton->GetValue() == true){
		trigger->trackProc->n[trigger->trackNum].basicOutput[currentZone] = false;
		trigger->trackProc->n[trigger->trackNum].alternateOutput[currentZone] = false;
		trigger->trackProc->n[trigger->trackNum].midiCCControlledOutput[currentZone] = true;
		trigger->trackProc->n[trigger->trackNum].velocityControlledOutput[currentZone] = false;
		trigger->trackProc->n[trigger->trackNum].zoneControlledOutput = false;
		trigger->trackProc->n[trigger->trackNum].sequenceOutput[currentZone] = false;
		trigger->trackProc->n[trigger->trackNum].mouseOutput[currentZone] = false;
		basicOutputPanel->Hide();
		alternatingOutputPanel->Hide();
		midiCCControlledOutputPanel->Show();
		velocityControlledOutputPanel->Hide();
		zoneControlledOutputPanel->Hide();
		sequenceOutputPanel->Hide();
		mouseOutputPanel->Hide();
	}
	if(velocityControlledOutputButton->GetValue() == true){
		trigger->trackProc->n[trigger->trackNum].basicOutput[currentZone] = false;
		trigger->trackProc->n[trigger->trackNum].alternateOutput[currentZone] = false;
		trigger->trackProc->n[trigger->trackNum].midiCCControlledOutput[currentZone] = false;
		trigger->trackProc->n[trigger->trackNum].velocityControlledOutput[currentZone] = true;
		trigger->trackProc->n[trigger->trackNum].zoneControlledOutput = false;
		trigger->trackProc->n[trigger->trackNum].sequenceOutput[currentZone] = false;
		trigger->trackProc->n[trigger->trackNum].mouseOutput[currentZone] = false;
		basicOutputPanel->Hide();
		alternatingOutputPanel->Hide();
		midiCCControlledOutputPanel->Hide();
		velocityControlledOutputPanel->Show();
		zoneControlledOutputPanel->Hide();
		sequenceOutputPanel->Hide();
		mouseOutputPanel->Hide();
	}
	if(zoneControlledOutputButton->GetValue() == true){
		for(int i=0; i<3; ++i){
			trigger->trackProc->n[trigger->trackNum].basicOutput[i] = false;
			trigger->trackProc->n[trigger->trackNum].alternateOutput[i] = false;
			trigger->trackProc->n[trigger->trackNum].midiCCControlledOutput[i] = false;
			trigger->trackProc->n[trigger->trackNum].velocityControlledOutput[i] = false;
			trigger->trackProc->n[trigger->trackNum].sequenceOutput[i] = false;
			trigger->trackProc->n[trigger->trackNum].mouseOutput[currentZone] = false;
		}
		trigger->trackProc->n[trigger->trackNum].zoneControlledOutput = true;
		basicOutputPanel->Hide();
		alternatingOutputPanel->Hide();
		midiCCControlledOutputPanel->Hide();
		velocityControlledOutputPanel->Hide();
		zoneControlledOutputPanel->Show();
		sequenceOutputPanel->Hide();
		mouseOutputPanel->Hide();
	}
	if(sequenceOutputButton->GetValue() == true){
		trigger->trackProc->n[trigger->trackNum].basicOutput[currentZone] = false;
		trigger->trackProc->n[trigger->trackNum].alternateOutput[currentZone] = false;
		trigger->trackProc->n[trigger->trackNum].midiCCControlledOutput[currentZone] = false;
		trigger->trackProc->n[trigger->trackNum].velocityControlledOutput[currentZone] = true;
		trigger->trackProc->n[trigger->trackNum].zoneControlledOutput = false;
		trigger->trackProc->n[trigger->trackNum].sequenceOutput[currentZone] = true;
		trigger->trackProc->n[trigger->trackNum].mouseOutput[currentZone] = false;
		basicOutputPanel->Hide();
		alternatingOutputPanel->Hide();
		midiCCControlledOutputPanel->Hide();
		velocityControlledOutputPanel->Hide();
		zoneControlledOutputPanel->Hide();
		sequenceOutputPanel->Show();
		mouseOutputPanel->Hide();
	}
	if(mouseOutputButton->GetValue() == true){
		trigger->trackProc->n[trigger->trackNum].basicOutput[currentZone] = false;
		trigger->trackProc->n[trigger->trackNum].alternateOutput[currentZone] = false;
		trigger->trackProc->n[trigger->trackNum].midiCCControlledOutput[currentZone] = false;
		trigger->trackProc->n[trigger->trackNum].velocityControlledOutput[currentZone] = false;
		trigger->trackProc->n[trigger->trackNum].zoneControlledOutput = false;
		trigger->trackProc->n[trigger->trackNum].sequenceOutput[currentZone] = false;
		trigger->trackProc->n[trigger->trackNum].mouseOutput[currentZone] = true;
		basicOutputPanel->Hide();
		alternatingOutputPanel->Hide();
		midiCCControlledOutputPanel->Hide();
		velocityControlledOutputPanel->Hide();
		zoneControlledOutputPanel->Hide();
		sequenceOutputPanel->Hide();
		mouseOutputPanel->Show();
	}
}

///////////////////////////////////////////////////////////
void TriggerDialog::OnDrumTypeSelect(wxCommandEvent &event)
{
	trigger->trackProc->n[trigger->trackNum].drumType = drumTypeBox->GetSelection();
	learnButton->SetFocus();
}

////////////////////////////////////////////////////////
void TriggerDialog::OnZonesSelect(wxCommandEvent &event)
{
	trigger->trackProc->n[trigger->trackNum].zones = ConvToInt( zonesSelectBox->GetValue() );
	UpdateZones();
	learnButton->SetFocus();
}

/////////////////////////////////////////////////////////
void TriggerDialog::OnMidiOutNote(GNumberBoxEvent &event)
{
    midiOutNoteBox->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].outputNote[currentZone]);
}

////////////////////////////////////////////////////////////
void TriggerDialog::OnMidiOutChannel(GNumberBoxEvent &event)
{
	midiOutChannelBox->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].outputChannel[currentZone]);
}

//////////////////////////////////////////////////////////
void TriggerDialog::OnRetriggerDetect(GButtonEvent &event)
{
	retriggerDetectButton->Hide();
	retriggerResetButton->Show();
	retriggerOkButton->Show();
	retriggerCancelButton->Show();

	Process::retriggerTrackNum = trigger->trackNum;
	Process::retriggerZoneNum = currentZone;
	Process::detectingRetrigger = true;
}

/////////////////////////////////////////////////////////
void TriggerDialog::OnRetriggerReset(GButtonEvent &event)
{
	trigger->trackProc->n[trigger->trackNum].retrigger[currentZone] = 0;
	retriggerBox->SetValue(wxString::Format(wxT("%d"), trigger->trackProc->n[trigger->trackNum].retrigger[currentZone]));
}

//////////////////////////////////////////////////////
void TriggerDialog::OnRetriggerOk(GButtonEvent &event)
{
	retriggerDetectButton->Show();
	retriggerResetButton->Hide();
	retriggerOkButton->Hide();
	retriggerCancelButton->Hide();

	Process::detectingRetrigger = false;
}

//////////////////////////////////////////////////////////
void TriggerDialog::OnRetriggerCancel(GButtonEvent &event)
{
	retriggerDetectButton->Show();
	retriggerResetButton->Hide();
	retriggerOkButton->Hide();
	retriggerCancelButton->Hide();

	Process::detectingRetrigger = false;
	trigger->trackProc->n[trigger->trackNum].retrigger[currentZone] = retrigger[currentZone];
	retriggerBox->SetValue(wxString::Format(wxT("%d"), trigger->trackProc->n[trigger->trackNum].retrigger[currentZone]));
}

//////////////////////////////////////////////////////////
void TriggerDialog::OnRetriggerBox(GNumberBoxEvent &event) 
{
	retriggerBox->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].retrigger[currentZone]);
}

/////////////////////////////////////////////////////////
void TriggerDialog::OnWaitTimeDetect(GButtonEvent &event)
{
	waitTimeDetectButton->Hide();
	waitTimeResetButton->Show();
	waitTimeOkButton->Show();
	waitTimeCancelButton->Show();

	trigger->trackProc->n[trigger->trackNum].multiZoneWaitTime = 0;
	multiZoneWaitTimeBox->SetValue(wxString::Format(wxT("%d"), 0));
	Process::waitTimeTrackNum = trigger->trackNum;
	Process::detectingWaitTime = true;
}

////////////////////////////////////////////////////////
void TriggerDialog::OnWaitTimeReset(GButtonEvent &event)
{
	trigger->trackProc->n[trigger->trackNum].multiZoneWaitTime = 0;
	multiZoneWaitTimeBox->SetValue(wxString::Format(wxT("%d"), 0));
}

/////////////////////////////////////////////////////
void TriggerDialog::OnWaitTimeOk(GButtonEvent &event)
{
	waitTimeDetectButton->Show();
	waitTimeResetButton->Hide();
	waitTimeOkButton->Hide();
	waitTimeCancelButton->Hide();

	Process::waitTimeTrackNum = 0;
	Process::detectingWaitTime = false;
}

/////////////////////////////////////////////////////////
void TriggerDialog::OnWaitTimeCancel(GButtonEvent &event)
{
	waitTimeDetectButton->Show();
	waitTimeResetButton->Hide();
	waitTimeOkButton->Hide();
	waitTimeCancelButton->Hide();

	Process::waitTimeTrackNum = 0;
	Process::detectingWaitTime = false;
	trigger->trackProc->n[trigger->trackNum].multiZoneWaitTime = multiZoneWaitTime;
	multiZoneWaitTimeBox->SetValue(wxString::Format(wxT("%d"), trigger->trackProc->n[trigger->trackNum].multiZoneWaitTime));
}

///////////////////////////////////////////////////////////
void TriggerDialog::OnCompressorSlider(GSliderEvent &event)
{
	if(event.GetKnobNumber() == 0){
		if((int)event.GetValue() < trigger->trackProc->n[trigger->trackNum].highCompressor[currentZone]){
			trigger->trackProc->n[trigger->trackNum].lowCompressor[currentZone] = (int)event.GetValue();
			curve->SetLowCompressor(trigger->trackProc->n[trigger->trackNum].lowCompressor[currentZone]);
			lowCompressorText->SetLabel(wxString::Format(wxT("%d"), trigger->trackProc->n[trigger->trackNum].lowCompressor[currentZone]));
		}
		else{
			compressorSlider->SetValue(0, trigger->trackProc->n[trigger->trackNum].highCompressor[currentZone]-1);
			trigger->trackProc->n[trigger->trackNum].lowCompressor[currentZone] = (int)event.GetValue();
			curve->SetLowCompressor(trigger->trackProc->n[trigger->trackNum].lowCompressor[currentZone]);
			lowCompressorText->SetLabel(wxString::Format(wxT("%d"), trigger->trackProc->n[trigger->trackNum].lowCompressor[currentZone]));
		}
	}

	if(event.GetKnobNumber() == 1){
		if((int)event.GetValue() > trigger->trackProc->n[trigger->trackNum].lowCompressor[currentZone]){
			trigger->trackProc->n[trigger->trackNum].highCompressor[currentZone] = (int)event.GetValue();
			curve->SetHighCompressor(trigger->trackProc->n[trigger->trackNum].highCompressor[currentZone]);
			highCompressorText->SetLabel(wxString::Format(wxT("%d"), trigger->trackProc->n[trigger->trackNum].highCompressor[currentZone]));
		}
		else{
			compressorSlider->SetValue(1, trigger->trackProc->n[trigger->trackNum].lowCompressor[currentZone]+1);
			trigger->trackProc->n[trigger->trackNum].highCompressor[currentZone] = (int)event.GetValue();
			curve->SetHighCompressor(trigger->trackProc->n[trigger->trackNum].highCompressor[currentZone]);
			highCompressorText->SetLabel(wxString::Format(wxT("%d"), trigger->trackProc->n[trigger->trackNum].highCompressor[currentZone]));
		}
	}

	for(int i=0; i<127; ++i){
		trigger->trackProc->n[trigger->trackNum].dynamics[currentZone][i] = curve->velocities[i];
	}
}

///////////////////////////////////////////////////////
void TriggerDialog::OnCutOffSlider(GSliderEvent &event)
{
	if(event.GetKnobNumber() == 0){
		if((int)event.GetValue() < trigger->trackProc->n[trigger->trackNum].highLimiter[currentZone]){
			trigger->trackProc->n[trigger->trackNum].lowLimiter[currentZone] = (int)event.GetValue();
			curve->SetLowLimiter(trigger->trackProc->n[trigger->trackNum].lowLimiter[currentZone]);
			lowLimiterText->SetLabel(wxString::Format(wxT("%d"), trigger->trackProc->n[trigger->trackNum].lowLimiter[currentZone]));
		}
		else{
			cutoffSlider->SetValue(0, trigger->trackProc->n[trigger->trackNum].highLimiter[currentZone]-1);
			trigger->trackProc->n[trigger->trackNum].lowLimiter[currentZone] = (int)event.GetValue();
			curve->SetLowLimiter(trigger->trackProc->n[trigger->trackNum].lowLimiter[currentZone]);
			lowLimiterText->SetLabel(wxString::Format(wxT("%d"), trigger->trackProc->n[trigger->trackNum].lowLimiter[currentZone]));
		}
	}

	if(event.GetKnobNumber() == 1){
		if((int)event.GetValue() > trigger->trackProc->n[trigger->trackNum].lowLimiter[currentZone]){
			trigger->trackProc->n[trigger->trackNum].highLimiter[currentZone] = (int)event.GetValue();
			curve->SetHighLimiter(trigger->trackProc->n[trigger->trackNum].highLimiter[currentZone]);
			highLimiterText->SetLabel(wxString::Format(wxT("%d"), trigger->trackProc->n[trigger->trackNum].highLimiter[currentZone]));
		}
		else{
			cutoffSlider->SetValue(1, trigger->trackProc->n[trigger->trackNum].lowLimiter[currentZone]+1);
			trigger->trackProc->n[trigger->trackNum].highLimiter[currentZone] = (int)event.GetValue();
			curve->SetHighLimiter(trigger->trackProc->n[trigger->trackNum].highLimiter[currentZone]);
			highLimiterText->SetLabel(wxString::Format(wxT("%d"), trigger->trackProc->n[trigger->trackNum].highLimiter[currentZone]));
		}
	}
}

///////////////////////////////////////////////////////////////
void TriggerDialog::OnMultiZoneWaitTime(GNumberBoxEvent &event) 
{
	multiZoneWaitTimeBox->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].multiZoneWaitTime);
	
}

////////////////////////////////////////////////////////////
void TriggerDialog::OnAntiMachineGun(GNumberBoxEvent &event) 
{
	antiMachineGunBox->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].antiMachineGunTime[currentZone]);
}

////////////////////////////////////////////////////
void TriggerDialog::OnNoteOff(wxCommandEvent &event)
{
	trigger->trackProc->n[trigger->trackNum].noteOff[currentZone] = noteOffBox->GetValue();	
}

////////////////////////////////////////////////////////////
void TriggerDialog::OnAlternateReset(GNumberBoxEvent &event)
{
	alternateResetBox->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].alternateReset[currentZone] );
}

/////////////////////////////////////////////////////////
void TriggerDialog::OnAlternateBox(wxCommandEvent &event)
{
	UpdateAlternateBoxes();
}

//////////////////////////////////////////
void TriggerDialog::UpdateAlternateBoxes()
{
	if(alternateBox[0]->GetValue()){
		trigger->trackProc->n[trigger->trackNum].alternateCheckBox[currentZone][2] = 1;
		alternateBox[1]->Enable();
		alternateNoteBox[2]->Enable();
	}
	else{
		trigger->trackProc->n[trigger->trackNum].alternateCheckBox[currentZone][2] = 0;
		alternateBox[1]->Disable();
		alternateBox[1]->SetValue(0);
		alternateNoteBox[2]->Disable();
	}

	if(alternateBox[1]->GetValue()){
		trigger->trackProc->n[trigger->trackNum].alternateCheckBox[currentZone][3] = 1;
		alternateBox[2]->Enable();
		alternateNoteBox[3]->Enable();
	}
	else{
		trigger->trackProc->n[trigger->trackNum].alternateCheckBox[currentZone][3] = 0;
		alternateBox[2]->Disable();
		alternateBox[2]->SetValue(0);
		alternateNoteBox[3]->Disable();
	}

	if(alternateBox[2]->GetValue()){
		trigger->trackProc->n[trigger->trackNum].alternateCheckBox[currentZone][4] = 1;
		alternateBox[3]->Enable();
		alternateNoteBox[4]->Enable();
	}
	else{
		trigger->trackProc->n[trigger->trackNum].alternateCheckBox[currentZone][4] = 0;
		alternateBox[3]->Disable();
		alternateBox[3]->SetValue(0);
		alternateNoteBox[4]->Disable();
	}

	if(alternateBox[3]->GetValue()){
		trigger->trackProc->n[trigger->trackNum].alternateCheckBox[currentZone][5] = 1;
		alternateBox[4]->Enable();
		alternateNoteBox[5]->Enable();
	}
	else{
		trigger->trackProc->n[trigger->trackNum].alternateCheckBox[currentZone][5] = 0;
		alternateBox[4]->Disable();
		alternateBox[4]->SetValue(0);
		alternateNoteBox[5]->Disable();
	}

	if(alternateBox[4]->GetValue()){
		trigger->trackProc->n[trigger->trackNum].alternateCheckBox[currentZone][6] = 1;
		alternateBox[5]->Enable();
		alternateNoteBox[6]->Enable();
	}
	else{
		trigger->trackProc->n[trigger->trackNum].alternateCheckBox[currentZone][6] = 0;
		alternateBox[5]->Disable();
		alternateBox[5]->SetValue(0);
		alternateNoteBox[6]->Disable();
	}

	if(alternateBox[5]->GetValue()){
		trigger->trackProc->n[trigger->trackNum].alternateCheckBox[currentZone][7] = 1;
		alternateBox[6]->Enable();
		alternateNoteBox[7]->Enable();
	}
	else{
		trigger->trackProc->n[trigger->trackNum].alternateCheckBox[currentZone][7] = 0;
		alternateBox[6]->Disable();
		alternateBox[6]->SetValue(0);
		alternateNoteBox[7]->Disable();
	}

	if(alternateBox[6]->GetValue()){
		trigger->trackProc->n[trigger->trackNum].alternateCheckBox[currentZone][8] = 1;
		alternateBox[7]->Enable();
		alternateNoteBox[8]->Enable();
	}
	else{
		trigger->trackProc->n[trigger->trackNum].alternateCheckBox[currentZone][8] = 0;
		alternateBox[7]->Disable();
		alternateBox[7]->SetValue(0);
		alternateNoteBox[8]->Disable();
	}

	if(alternateBox[7]->GetValue()){
		trigger->trackProc->n[trigger->trackNum].alternateCheckBox[currentZone][9] = 1;
		alternateNoteBox[9]->Enable();
	}
	else{
		trigger->trackProc->n[trigger->trackNum].alternateCheckBox[currentZone][9] = 0;
		alternateNoteBox[9]->Disable();
	}
}

///////////////////////////////////////////////////////////////
void TriggerDialog::OnAlternateRandomize(wxCommandEvent &event)
{
	trigger->trackProc->n[trigger->trackNum].alternateRandom[currentZone] = alternateRandomBox->GetValue();
}

///////////////////////////////////////////////////////////////
void TriggerDialog::OnAlternateNoteBox1(GNumberBoxEvent &event)
{
	alternateNoteBox[0]->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].alternateNotes[currentZone][0] );
}

///////////////////////////////////////////////////////////////
void TriggerDialog::OnAlternateNoteBox2(GNumberBoxEvent &event)
{
	alternateNoteBox[1]->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].alternateNotes[currentZone][1] );
}

///////////////////////////////////////////////////////////////
void TriggerDialog::OnAlternateNoteBox3(GNumberBoxEvent &event)
{
	alternateNoteBox[2]->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].alternateNotes[currentZone][2] );
}

///////////////////////////////////////////////////////////////
void TriggerDialog::OnAlternateNoteBox4(GNumberBoxEvent &event)
{
	alternateNoteBox[3]->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].alternateNotes[currentZone][3] );
}

///////////////////////////////////////////////////////////////
void TriggerDialog::OnAlternateNoteBox5(GNumberBoxEvent &event)
{
	alternateNoteBox[4]->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].alternateNotes[currentZone][4] );
}

///////////////////////////////////////////////////////////////
void TriggerDialog::OnAlternateNoteBox6(GNumberBoxEvent &event)
{
	alternateNoteBox[5]->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].alternateNotes[currentZone][5] );
}

///////////////////////////////////////////////////////////////
void TriggerDialog::OnAlternateNoteBox7(GNumberBoxEvent &event)
{
	alternateNoteBox[6]->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].alternateNotes[currentZone][6] );
}

///////////////////////////////////////////////////////////////
void TriggerDialog::OnAlternateNoteBox8(GNumberBoxEvent &event)
{
	alternateNoteBox[7]->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].alternateNotes[currentZone][7] );
}

///////////////////////////////////////////////////////////////
void TriggerDialog::OnAlternateNoteBox9(GNumberBoxEvent &event)
{
	alternateNoteBox[8]->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].alternateNotes[currentZone][8] );
}

////////////////////////////////////////////////////////////////
void TriggerDialog::OnAlternateNoteBox10(GNumberBoxEvent &event)
{
	alternateNoteBox[9]->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].alternateNotes[currentZone][9] );
}

/////////////////////////////////////////////
void TriggerDialog::OnKnob(GKnobEvent &event) 
{ 
	trigger->trackProc->n[trigger->trackNum].preGain[currentZone] = (int)knob->GetValue(); //audio
	trigger->trackProc->n[trigger->trackNum].preVolume[currentZone] = ((((int)knob->GetValue() * 254) / 1000) - 127); //midi, joystick, keyboard
	//unsigned int temp = trigger->trackProc->n[trigger->trackNum].preVolume[currentZone] - 127;
	knobValue->SetLabel(wxString::Format(wxT("%d"), trigger->trackProc->n[trigger->trackNum].preVolume[currentZone]));
}

///////////////////////////////////////////////
void TriggerDialog::OnCurve(GCurveEvent &event)
{
	if(currentZone == 0){
		trigger->trackProc->n[trigger->trackNum].pointsZone1 = curve->points;
	}
	if(currentZone == 1){
		trigger->trackProc->n[trigger->trackNum].pointsZone2 = curve->points;
	}
	if(currentZone == 2){
		trigger->trackProc->n[trigger->trackNum].pointsZone3 = curve->points;
	}

	for(int i=0; i<127; ++i){
		trigger->trackProc->n[trigger->trackNum].dynamics[currentZone][i] = curve->velocities[i];
	}

	//if(velocityDialog != NULL){ //FIXME - this is not safe and it's SLOW.
	//	velocityDialog->UpdateSliders();
	//}

}

////////////////////////////////////////////////////////////////
void TriggerDialog::OnMidiCCControlledBox(wxCommandEvent &event)
{
	trigger->trackProc->n[trigger->trackNum].midiCCControlledVelocity[currentZone] = MidiCCControlledBox->GetValue();
}

////////////////////////////////////////////////////////////////////
void TriggerDialog::OnMidiCCControlledNumber(GNumberBoxEvent &event)
{
	MidiCCControlledNumber->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].midiCCControlledVelocityNote[currentZone]);
}

//////////////////////////////////////////////////////
void TriggerDialog::OnMidiCCBox(wxCommandEvent &event)
{
	UpdateMidiCCBoxes();
	UpdateMidiCCSliders();

	//store new postitions
	for(int n=0; n<midiCCControlledSlider->knobCount; ++n){
		trigger->trackProc->n[trigger->trackNum].midiCCControlledSliders[currentZone][n] = midiCCControlledSlider->GetValue(n);
	}

	UpdateMidiCCText();
}

///////////////////////////////////////
void TriggerDialog::UpdateMidiCCBoxes()
{
	if(midiCCBox[0]->GetValue()){
		trigger->trackProc->n[trigger->trackNum].midiCCControlledCheckBox[currentZone][2] = 1;
		midiCCBox[1]->Enable();
		midiCCNoteBox[2]->Enable();
	}
	else{
		trigger->trackProc->n[trigger->trackNum].midiCCControlledCheckBox[currentZone][2] = 0;
		midiCCBox[1]->Disable();
		midiCCBox[1]->SetValue(0);
		midiCCNoteBox[2]->Disable();
	}

	if(midiCCBox[1]->GetValue()){
		trigger->trackProc->n[trigger->trackNum].midiCCControlledCheckBox[currentZone][3] = 1;
		midiCCBox[2]->Enable();
		midiCCNoteBox[3]->Enable();
	}
	else{
		trigger->trackProc->n[trigger->trackNum].midiCCControlledCheckBox[currentZone][3] = 0;
		midiCCBox[2]->Disable();
		midiCCBox[2]->SetValue(0);
		midiCCNoteBox[3]->Disable();
	}

	if(midiCCBox[2]->GetValue()){
		trigger->trackProc->n[trigger->trackNum].midiCCControlledCheckBox[currentZone][4] = 1;
		midiCCBox[3]->Enable();
		midiCCNoteBox[4]->Enable();
	}
	else{
		trigger->trackProc->n[trigger->trackNum].midiCCControlledCheckBox[currentZone][4] = 0;
		midiCCBox[3]->Disable();
		midiCCBox[3]->SetValue(0);
		midiCCNoteBox[4]->Disable();
	}

	if(midiCCBox[3]->GetValue()){
		trigger->trackProc->n[trigger->trackNum].midiCCControlledCheckBox[currentZone][5] = 1;
		midiCCBox[4]->Enable();
		midiCCNoteBox[5]->Enable();
	}
	else{
		trigger->trackProc->n[trigger->trackNum].midiCCControlledCheckBox[currentZone][5] = 0;
		midiCCBox[4]->Disable();
		midiCCBox[4]->SetValue(0);
		midiCCNoteBox[5]->Disable();
	}

	if(midiCCBox[4]->GetValue()){
		trigger->trackProc->n[trigger->trackNum].midiCCControlledCheckBox[currentZone][6] = 1;
		midiCCBox[5]->Enable();
		midiCCNoteBox[6]->Enable();
	}
	else{
		trigger->trackProc->n[trigger->trackNum].midiCCControlledCheckBox[currentZone][6] = 0;
		midiCCBox[5]->Disable();
		midiCCBox[5]->SetValue(0);
		midiCCNoteBox[6]->Disable();
	}

	if(midiCCBox[5]->GetValue()){
		trigger->trackProc->n[trigger->trackNum].midiCCControlledCheckBox[currentZone][7] = 1;
		midiCCBox[6]->Enable();
		midiCCNoteBox[7]->Enable();
	}
	else{
		trigger->trackProc->n[trigger->trackNum].midiCCControlledCheckBox[currentZone][7] = 0;
		midiCCBox[6]->Disable();
		midiCCBox[6]->SetValue(0);
		midiCCNoteBox[7]->Disable();
	}

	if(midiCCBox[6]->GetValue()){
		trigger->trackProc->n[trigger->trackNum].midiCCControlledCheckBox[currentZone][8] = 1;
		midiCCBox[7]->Enable();
		midiCCNoteBox[8]->Enable();
	}
	else{
		trigger->trackProc->n[trigger->trackNum].midiCCControlledCheckBox[currentZone][8] = 0;
		midiCCBox[7]->Disable();
		midiCCBox[7]->SetValue(0);
		midiCCNoteBox[8]->Disable();
	}

	if(midiCCBox[7]->GetValue()){
		trigger->trackProc->n[trigger->trackNum].midiCCControlledCheckBox[currentZone][9] = 1;
		midiCCNoteBox[9]->Enable();
	}
	else{
		trigger->trackProc->n[trigger->trackNum].midiCCControlledCheckBox[currentZone][9] = 0;
		midiCCNoteBox[9]->Disable();
	}
}

/////////////////////////////////////////
void TriggerDialog::UpdateMidiCCSliders()
{
	//Set Knob Count
	int knobCount = 0;
	while(trigger->trackProc->n[trigger->trackNum].midiCCControlledCheckBox[currentZone][knobCount+1] != 0){
		knobCount++;
	}
	while(midiCCControlledSlider->knobCount < knobCount){
		midiCCControlledSlider->AddKnob();
	}
	while(midiCCControlledSlider->knobCount > knobCount){
		midiCCControlledSlider->DeleteKnob();
	}
}

//////////////////////////////////////
void TriggerDialog::UpdateMidiCCText()
{
	//1
	wxString tempString = wxT("1-");
	tempString += wxString::Format(wxT("%d"), trigger->trackProc->n[trigger->trackNum].midiCCControlledSliders[currentZone][0]-1);
	midiCCText[0]->SetLabel(tempString);

	for(int n=0; n<9; ++n){
		tempString = wxString::Format(wxT("%d-"), trigger->trackProc->n[trigger->trackNum].midiCCControlledSliders[currentZone][n]);
		if(trigger->trackProc->n[trigger->trackNum].midiCCControlledCheckBox[currentZone][n+2]){
			tempString += wxString::Format(wxT("%d"), trigger->trackProc->n[trigger->trackNum].midiCCControlledSliders[currentZone][n+1]-1);
		
			if(n+2 < 10){
				midiCCText[n+2]->Show();
			}
		}
		else{
			tempString += wxT("127");

			if(n+2 < 10){
				midiCCText[n+2]->Hide();
			}
		}
		midiCCText[n+1]->SetLabel(tempString);
	}
}

////////////////////////////////////////////////////////////
void TriggerDialog::OnMidiCCNoteBox1(GNumberBoxEvent &event)
{
	midiCCNoteBox[0]->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].midiCCControlledNotes[currentZone][0] );
}

////////////////////////////////////////////////////////////
void TriggerDialog::OnMidiCCNoteBox2(GNumberBoxEvent &event)
{
	midiCCNoteBox[1]->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].midiCCControlledNotes[currentZone][1] );
}

////////////////////////////////////////////////////////////
void TriggerDialog::OnMidiCCNoteBox3(GNumberBoxEvent &event)
{
	midiCCNoteBox[2]->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].midiCCControlledNotes[currentZone][2] );
}

////////////////////////////////////////////////////////////
void TriggerDialog::OnMidiCCNoteBox4(GNumberBoxEvent &event)
{
	midiCCNoteBox[3]->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].midiCCControlledNotes[currentZone][3] );
}

////////////////////////////////////////////////////////////
void TriggerDialog::OnMidiCCNoteBox5(GNumberBoxEvent &event)
{
	midiCCNoteBox[4]->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].midiCCControlledNotes[currentZone][4] );
}

////////////////////////////////////////////////////////////
void TriggerDialog::OnMidiCCNoteBox6(GNumberBoxEvent &event)
{
	midiCCNoteBox[5]->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].midiCCControlledNotes[currentZone][5] );
}

////////////////////////////////////////////////////////////
void TriggerDialog::OnMidiCCNoteBox7(GNumberBoxEvent &event)
{
	midiCCNoteBox[6]->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].midiCCControlledNotes[currentZone][6] );
}

////////////////////////////////////////////////////////////
void TriggerDialog::OnMidiCCNoteBox8(GNumberBoxEvent &event)
{
	midiCCNoteBox[7]->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].midiCCControlledNotes[currentZone][7] );
}

////////////////////////////////////////////////////////////
void TriggerDialog::OnMidiCCNoteBox9(GNumberBoxEvent &event)
{
	midiCCNoteBox[8]->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].midiCCControlledNotes[currentZone][8] );
}

/////////////////////////////////////////////////////////////
void TriggerDialog::OnMidiCCNoteBox10(GNumberBoxEvent &event)
{
	midiCCNoteBox[9]->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].midiCCControlledNotes[currentZone][9] );
}

/////////////////////////////////////////////////////////////////
void TriggerDialog::OnMidiCCControlledSlider(GSliderEvent &event)
{
	for(int i=0; i<100; ++i){
		if(event.GetKnobNumber() == i){
			trigger->trackProc->n[trigger->trackNum].midiCCControlledSliders[currentZone][i] = (int)event.GetValue();
		}
	}

	UpdateMidiCCText();
}

////////////////////////////////////////////////////////
void TriggerDialog::OnVelocityBox(wxCommandEvent &event)
{
	UpdateVelocityBoxes();
	UpdateVelocitySliders();

	//store new postitions
	for(int n=0; n<velocityControlledSlider->knobCount; ++n){
		trigger->trackProc->n[trigger->trackNum].velocityControlledSliders[currentZone][n] = velocityControlledSlider->GetValue(n);
	}

	UpdateVelocityText();
}

/////////////////////////////////////////
void TriggerDialog::UpdateVelocityBoxes()
{
	if(velocityBox[0]->GetValue()){
		trigger->trackProc->n[trigger->trackNum].velocityControlledCheckBox[currentZone][2] = 1;
		velocityBox[1]->Enable();
		velocityNoteBox[2]->Enable();
	}
	else{
		trigger->trackProc->n[trigger->trackNum].velocityControlledCheckBox[currentZone][2] = 0;
		velocityBox[1]->Disable();
		velocityBox[1]->SetValue(0);
		velocityNoteBox[2]->Disable();
	}

	if(velocityBox[1]->GetValue()){
		trigger->trackProc->n[trigger->trackNum].velocityControlledCheckBox[currentZone][3] = 1;
		velocityBox[2]->Enable();
		velocityNoteBox[3]->Enable();
	}
	else{
		trigger->trackProc->n[trigger->trackNum].velocityControlledCheckBox[currentZone][3] = 0;
		velocityBox[2]->Disable();
		velocityBox[2]->SetValue(0);
		velocityNoteBox[3]->Disable();
	}

	if(velocityBox[2]->GetValue()){
		trigger->trackProc->n[trigger->trackNum].velocityControlledCheckBox[currentZone][4] = 1;
		velocityBox[3]->Enable();
		velocityNoteBox[4]->Enable();
	}
	else{
		trigger->trackProc->n[trigger->trackNum].velocityControlledCheckBox[currentZone][4] = 0;
		velocityBox[3]->Disable();
		velocityBox[3]->SetValue(0);
		velocityNoteBox[4]->Disable();
	}

	if(velocityBox[3]->GetValue()){
		trigger->trackProc->n[trigger->trackNum].velocityControlledCheckBox[currentZone][5] = 1;
		velocityBox[4]->Enable();
		velocityNoteBox[5]->Enable();
	}
	else{
		trigger->trackProc->n[trigger->trackNum].velocityControlledCheckBox[currentZone][5] = 0;
		velocityBox[4]->Disable();
		velocityBox[4]->SetValue(0);
		velocityNoteBox[5]->Disable();
	}

	if(velocityBox[4]->GetValue()){
		trigger->trackProc->n[trigger->trackNum].velocityControlledCheckBox[currentZone][6] = 1;
		velocityBox[5]->Enable();
		velocityNoteBox[6]->Enable();
	}
	else{
		trigger->trackProc->n[trigger->trackNum].velocityControlledCheckBox[currentZone][6] = 0;
		velocityBox[5]->Disable();
		velocityBox[5]->SetValue(0);
		velocityNoteBox[6]->Disable();
	}

	if(velocityBox[5]->GetValue()){
		trigger->trackProc->n[trigger->trackNum].velocityControlledCheckBox[currentZone][7] = 1;
		velocityBox[6]->Enable();
		velocityNoteBox[7]->Enable();
	}
	else{
		trigger->trackProc->n[trigger->trackNum].velocityControlledCheckBox[currentZone][7] = 0;
		velocityBox[6]->Disable();
		velocityBox[6]->SetValue(0);
		velocityNoteBox[7]->Disable();
	}

	if(velocityBox[6]->GetValue()){
		trigger->trackProc->n[trigger->trackNum].velocityControlledCheckBox[currentZone][8] = 1;
		velocityBox[7]->Enable();
		velocityNoteBox[8]->Enable();
	}
	else{
		trigger->trackProc->n[trigger->trackNum].velocityControlledCheckBox[currentZone][8] = 0;
		velocityBox[7]->Disable();
		velocityBox[7]->SetValue(0);
		velocityNoteBox[8]->Disable();
	}

	if(velocityBox[7]->GetValue()){
		trigger->trackProc->n[trigger->trackNum].velocityControlledCheckBox[currentZone][9] = 1;
		velocityNoteBox[9]->Enable();
	}
	else{
		trigger->trackProc->n[trigger->trackNum].velocityControlledCheckBox[currentZone][9] = 0;
		velocityNoteBox[9]->Disable();
	}
}

///////////////////////////////////////////
void TriggerDialog::UpdateVelocitySliders()
{
	//Set Knob Count
	int knobCount = 0;
	while(trigger->trackProc->n[trigger->trackNum].velocityControlledCheckBox[currentZone][knobCount+1] != 0){
		knobCount++;
	}
	while(velocityControlledSlider->knobCount < knobCount){
		velocityControlledSlider->AddKnob();
	}
	while(velocityControlledSlider->knobCount > knobCount){
		velocityControlledSlider->DeleteKnob();
	}
}

////////////////////////////////////////
void TriggerDialog::UpdateVelocityText()
{
	//1
	wxString tempString = wxT("1-");
	tempString += wxString::Format(wxT("%d"), trigger->trackProc->n[trigger->trackNum].velocityControlledSliders[currentZone][0]-1);
	velocityText[0]->SetLabel(tempString);

	for(int n=0; n<9; ++n){
		tempString = wxString::Format(wxT("%d-"), trigger->trackProc->n[trigger->trackNum].velocityControlledSliders[currentZone][n]);
		if(trigger->trackProc->n[trigger->trackNum].velocityControlledCheckBox[currentZone][n+2]){
			tempString += wxString::Format(wxT("%d"), trigger->trackProc->n[trigger->trackNum].velocityControlledSliders[currentZone][n+1]-1);
		
			if(n+2 < 10){
				velocityText[n+2]->Show();
			}
		}
		else{
			tempString += wxT("127");

			if(n+2 < 10){
				velocityText[n+2]->Hide();
			}
		}
		velocityText[n+1]->SetLabel(tempString);
	}
}

//////////////////////////////////////////////////////////////
void TriggerDialog::OnVelocityNoteBox1(GNumberBoxEvent &event)
{
	velocityNoteBox[0]->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].velocityControlledNotes[currentZone][0] );
}

//////////////////////////////////////////////////////////////
void TriggerDialog::OnVelocityNoteBox2(GNumberBoxEvent &event)
{
	velocityNoteBox[1]->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].velocityControlledNotes[currentZone][1] );
}

//////////////////////////////////////////////////////////////
void TriggerDialog::OnVelocityNoteBox3(GNumberBoxEvent &event)
{
	velocityNoteBox[2]->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].velocityControlledNotes[currentZone][2] );
}

//////////////////////////////////////////////////////////////
void TriggerDialog::OnVelocityNoteBox4(GNumberBoxEvent &event)
{
	velocityNoteBox[3]->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].velocityControlledNotes[currentZone][3] );
}

//////////////////////////////////////////////////////////////
void TriggerDialog::OnVelocityNoteBox5(GNumberBoxEvent &event)
{
	velocityNoteBox[4]->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].velocityControlledNotes[currentZone][4] );
}

//////////////////////////////////////////////////////////////
void TriggerDialog::OnVelocityNoteBox6(GNumberBoxEvent &event)
{
	velocityNoteBox[5]->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].velocityControlledNotes[currentZone][5] );
}

//////////////////////////////////////////////////////////////
void TriggerDialog::OnVelocityNoteBox7(GNumberBoxEvent &event)
{
	velocityNoteBox[6]->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].velocityControlledNotes[currentZone][6] );
}

//////////////////////////////////////////////////////////////
void TriggerDialog::OnVelocityNoteBox8(GNumberBoxEvent &event)
{
	velocityNoteBox[7]->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].velocityControlledNotes[currentZone][7] );
}

//////////////////////////////////////////////////////////////
void TriggerDialog::OnVelocityNoteBox9(GNumberBoxEvent &event)
{
	velocityNoteBox[8]->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].velocityControlledNotes[currentZone][8] );
}

///////////////////////////////////////////////////////////////
void TriggerDialog::OnVelocityNoteBox10(GNumberBoxEvent &event)
{
	velocityNoteBox[9]->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].velocityControlledNotes[currentZone][9] );
}

///////////////////////////////////////////////////////////////////
void TriggerDialog::OnVelocityControlledSlider(GSliderEvent &event)
{
	for(int i=0; i<100; ++i){
		if(event.GetKnobNumber() == i){
			trigger->trackProc->n[trigger->trackNum].velocityControlledSliders[currentZone][i] = (int)event.GetValue();
		}
	}

	UpdateVelocityText();
}

/////////////////////////////////////////////////////////
void TriggerDialog::OnVelocityDialog(GButtonEvent &event)
{
	velocityDialog = new VelocityDialog(this);
	velocityDialog->ShowModal();
}

////////////////////////////////////////////////
void TriggerDialog::OnLearn(GButtonEvent &event)
{
	UpdateInputImage(true);
	device->SetLabel(wxT("Learning . . ."));
	info->SetLabel(wxT(""));

	LearnThread *learnThread = new LearnThread(this, trigger->trackProc->n[trigger->trackNum].midiType);
}

///////////////////////////////////////////////////
void TriggerDialog::OnLearnEvent(LearnEvent &event)
{
	if(Process::devInfo.deviceName != wxT("")){
		device->SetLabel(Process::devInfo.deviceName); //Causes crashes on MAC
		info->SetLabel(Process::devInfo.inputDetails);
		trigger->trackProc->n[trigger->trackNum].deviceName[currentZone] = Process::devInfo.deviceName;
		trigger->trackProc->n[trigger->trackNum].inputDetails[currentZone] = Process::devInfo.inputDetails;
		trigger->trackProc->n[trigger->trackNum].inputCode[currentZone] = Process::LearnReply;
		//trigger->trackProc->n[trigger->trackNum].outputNote[currentZone] = Process::LearnReply;
		UpdateInputImage(0);
	}

	else{
		device->SetLabel(wxT("no device selected"));
		info->SetLabel(wxT(""));
		trigger->trackProc->n[trigger->trackNum].deviceName[currentZone] = wxT("no device selected");
		trigger->trackProc->n[trigger->trackNum].inputDetails[currentZone] = wxT("");
		trigger->trackProc->n[trigger->trackNum].inputCode[currentZone] = 0;
		UpdateInputImage(0);
	}	
}

///////////////////////////////////////////////////////
void TriggerDialog::OnPriority1(GNumberBoxEvent &event)
{
	priority1->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].priority[0]);
}

///////////////////////////////////////////////////////
void TriggerDialog::OnPriority2(GNumberBoxEvent &event)
{
	priority2->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].priority[1]);
}

///////////////////////////////////////////////////////
void TriggerDialog::OnPriority3(GNumberBoxEvent &event)
{
	priority3->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].priority[2]);
}

//////////////////////////////////////////////////////
void TriggerDialog::OnGravity1(GNumberBoxEvent &event)
{
	gravity1->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].gravity[0]);
}

//////////////////////////////////////////////////////
void TriggerDialog::OnGravity2(GNumberBoxEvent &event)
{
	gravity2->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].gravity[1]);
}	

//////////////////////////////////////////////////////
void TriggerDialog::OnGravity3(GNumberBoxEvent &event)
{
	gravity3->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].gravity[2]);
}

/////////////////////////////////////////////////////////////
void TriggerDialog::OnVelocityBalance(GNumberBoxEvent &event)
{
	velocityBalanceBox->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].velocityBalance);
}
///////////////////////////////////////////////////
void TriggerDialog::OnHasRim(wxCommandEvent &event)
{
	trigger->trackProc->n[trigger->trackNum].hasRim = hasRimBox->GetValue();	
}

/////////////////////////////////////////////////////
void TriggerDialog::OnEnableCC(wxCommandEvent &event)
{
	trigger->trackProc->n[trigger->trackNum].enableCC = enableCCBox->GetValue();	
}

////////////////////////////////////////////////////////
void TriggerDialog::OnBasicOutput(wxCommandEvent &event)
{
	UpdateOutputType();
}

//////////////////////////////////////////////////////////////
void TriggerDialog::OnAlternatingOutput(wxCommandEvent &event)
{
	UpdateOutputType();
}

///////////////////////////////////////////////////////////////////
void TriggerDialog::OnMidiCCControlledOutput(wxCommandEvent &event)
{
	UpdateOutputType();
}

////////////////////////////////////////////////////////////////////////
void TriggerDialog::OnMidiCCControlledOutputNote(GNumberBoxEvent &event)
{
	midiCCControlledInputNoteBox->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].midiCCControlledInputNote[currentZone]);
}

/////////////////////////////////////////////////////////////////////
void TriggerDialog::OnVelocityControlledOutput(wxCommandEvent &event)
{
	UpdateOutputType();
}

//////////////////////////////////////////////////////////////////
void TriggerDialog::OnZoneControlledOutput(wxCommandEvent &event)
{
	UpdateOutputType();
}
////////////////////////////////////////////////////
void TriggerDialog::OnZoneBox(wxCommandEvent &event)
{
	UpdateZoneBoxes();
	UpdateZoneSliders();

	//store new postitions
	for(int n=0; n<zoneControlledSlider->knobCount; ++n){
		trigger->trackProc->n[trigger->trackNum].zoneControlledSliders[n] = zoneControlledSlider->GetValue(n);
	}

	UpdateZoneText();
}
//////////////////////////////////////////////////////////
void TriggerDialog::OnZoneNoteBox1(GNumberBoxEvent &event)
{
	zoneNoteBox[0]->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].zoneControlledNotes[0] );
}

//////////////////////////////////////////////////////////
void TriggerDialog::OnZoneNoteBox2(GNumberBoxEvent &event)
{
	zoneNoteBox[1]->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].zoneControlledNotes[1] );
}

//////////////////////////////////////////////////////////
void TriggerDialog::OnZoneNoteBox3(GNumberBoxEvent &event)
{
	zoneNoteBox[2]->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].zoneControlledNotes[2] );
}

//////////////////////////////////////////////////////////
void TriggerDialog::OnZoneNoteBox4(GNumberBoxEvent &event)
{
	zoneNoteBox[3]->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].zoneControlledNotes[3] );
}

//////////////////////////////////////////////////////////
void TriggerDialog::OnZoneNoteBox5(GNumberBoxEvent &event)
{
	zoneNoteBox[4]->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].zoneControlledNotes[4] );
}

//////////////////////////////////////////////////////////
void TriggerDialog::OnZoneNoteBox6(GNumberBoxEvent &event)
{
	zoneNoteBox[5]->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].zoneControlledNotes[5] );
}

//////////////////////////////////////////////////////////
void TriggerDialog::OnZoneNoteBox7(GNumberBoxEvent &event)
{
	zoneNoteBox[6]->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].zoneControlledNotes[6] );
}

///////////////////////////////////////////////////////////
void TriggerDialog::OnZoneNoteBox8(GNumberBoxEvent &event)
{
	zoneNoteBox[7]->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].zoneControlledNotes[7] );
}

//////////////////////////////////////////////////////////
void TriggerDialog::OnZoneNoteBox9(GNumberBoxEvent &event)
{
	zoneNoteBox[8]->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].zoneControlledNotes[8] );
}

///////////////////////////////////////////////////////////
void TriggerDialog::OnZoneNoteBox10(GNumberBoxEvent &event)
{
	zoneNoteBox[9]->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].zoneControlledNotes[9] );
}

///////////////////////////////////////////////////////////////
void TriggerDialog::OnZoneControlledSlider(GSliderEvent &event)
{
	for(int i=0; i<100; ++i){
		if(event.GetKnobNumber() == i){
			trigger->trackProc->n[trigger->trackNum].zoneControlledSliders[i] = (int)event.GetValue();
		}
	}

	UpdateZoneText();
}

///////////////////////////////////////////////////////////
void TriggerDialog::OnSequenceOutput(wxCommandEvent &event)
{
	UpdateOutputType();
}

/////////////////////////////////////////////////////
void TriggerDialog::OnFileSelect(GButtonEvent &event)
{
	wxStandardPaths stdPath; 
    wxString fileLocation = stdPath.GetExecutablePath(); 
#ifdef MAC
	fileLocation.Replace(wxT("eTrigger.app/Contents/MacOS/eTrigger"), wxT(""), true);
	fileLocation += wxT("/Sequencer");
#endif //MAC
#ifdef WIN32
    fileLocation = wxFileName(fileLocation).GetPath() + wxT("/Sequencer");
#endif WIN32

	wxFileDialog fileDlg(this, wxString(wxT("Load eTrigger Sequence")), fileLocation, wxString(wxT("")), 
		                                    wxString(wxT("eTrigger Sequence (*.seq)|*.seq")), wxFD_OPEN | wxFD_FILE_MUST_EXIST, wxDefaultPosition);

	if(fileDlg.ShowModal() == wxID_OK){
		wxString temp;
		temp = fileDlg.GetDirectory();
#ifdef WIN32
		temp += wxT("\\");
#endif //WIN32
#ifdef MAC
		temp += wxT("/");
#endif //MAC
		temp += fileDlg.GetFilename();
		filePath->SetValue(temp);
		trigger->trackProc->n[trigger->trackNum].sequenceFile[currentZone] = temp;

		return;
	}
	else{
		filePath->SetValue(wxT(""));
		trigger->trackProc->n[trigger->trackNum].sequenceFile[currentZone] = wxT("");
	}
}

//////////////////////////////////////////////////////////
void TriggerDialog::OnSequenceOverlap(wxCommandEvent &event)
{
	trigger->trackProc->n[trigger->trackNum].sequenceOverlap[currentZone] = sequenceOverlapBox->GetValue();
}

///////////////////////////////////////////////////////////
void TriggerDialog::OnMouseOutput(wxCommandEvent &event)
{
	UpdateOutputType();
}

///////////////////////////////////////////////////////
void TriggerDialog::OnMouseXBox(GNumberBoxEvent &event)
{
	mouseXBox->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].mouseX[currentZone]);
}

///////////////////////////////////////////////////////
void TriggerDialog::OnMouseYBox(GNumberBoxEvent &event)
{
	mouseYBox->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].mouseY[currentZone]);
}

////////////////////////////////////
void TriggerDialog::UpdateZoneText()
{
	//1
	wxString tempString = wxT("1-");
	tempString += wxString::Format(wxT("%d"), trigger->trackProc->n[trigger->trackNum].zoneControlledSliders[0]-1);
	zoneText[0]->SetLabel(tempString);

	for(int n=0; n<9; ++n){
		tempString = wxString::Format(wxT("%d-"), trigger->trackProc->n[trigger->trackNum].zoneControlledSliders[n]);
		if(trigger->trackProc->n[trigger->trackNum].zoneControlledCheckBox[n+2]){
			tempString += wxString::Format(wxT("%d"), trigger->trackProc->n[trigger->trackNum].zoneControlledSliders[n+1]-1);
		
			if(n+2 < 10){
				zoneText[n+2]->Show();
			}
		}
		else{
			tempString += wxT("127");

			if(n+2 < 10){
				zoneText[n+2]->Hide();
			}
		}
		zoneText[n+1]->SetLabel(tempString);
	}
}

//////////////////////////////////////
void TriggerDialog::UpdateZoneBoxes()
{
	if(zoneBox[0]->GetValue()){
		trigger->trackProc->n[trigger->trackNum].zoneControlledCheckBox[2] = 1;
		zoneBox[1]->Enable();
		zoneNoteBox[2]->Enable();
	}
	else{
		trigger->trackProc->n[trigger->trackNum].zoneControlledCheckBox[2] = 0;
		zoneBox[1]->Disable();
		zoneBox[1]->SetValue(0);
		zoneNoteBox[2]->Disable();
	}

	if(zoneBox[1]->GetValue()){
		trigger->trackProc->n[trigger->trackNum].zoneControlledCheckBox[3] = 1;
		zoneBox[2]->Enable();
		zoneNoteBox[3]->Enable();
	}
	else{
		trigger->trackProc->n[trigger->trackNum].zoneControlledCheckBox[3] = 0;
		zoneBox[2]->Disable();
		zoneBox[2]->SetValue(0);
		zoneNoteBox[3]->Disable();
	}

	if(zoneBox[2]->GetValue()){
		trigger->trackProc->n[trigger->trackNum].zoneControlledCheckBox[4] = 1;
		zoneBox[3]->Enable();
		zoneNoteBox[4]->Enable();
	}
	else{
		trigger->trackProc->n[trigger->trackNum].zoneControlledCheckBox[4] = 0;
		zoneBox[3]->Disable();
		zoneBox[3]->SetValue(0);
		zoneNoteBox[4]->Disable();
	}

	if(zoneBox[3]->GetValue()){
		trigger->trackProc->n[trigger->trackNum].zoneControlledCheckBox[5] = 1;
		zoneBox[4]->Enable();
		zoneNoteBox[5]->Enable();
	}
	else{
		trigger->trackProc->n[trigger->trackNum].zoneControlledCheckBox[5] = 0;
		zoneBox[4]->Disable();
		zoneBox[4]->SetValue(0);
		zoneNoteBox[5]->Disable();
	}

	if(zoneBox[4]->GetValue()){
		trigger->trackProc->n[trigger->trackNum].zoneControlledCheckBox[6] = 1;
		zoneBox[5]->Enable();
		zoneNoteBox[6]->Enable();
	}
	else{
		trigger->trackProc->n[trigger->trackNum].zoneControlledCheckBox[6] = 0;
		zoneBox[5]->Disable();
		zoneBox[5]->SetValue(0);
		zoneNoteBox[6]->Disable();
	}

	if(zoneBox[5]->GetValue()){
		trigger->trackProc->n[trigger->trackNum].zoneControlledCheckBox[7] = 1;
		zoneBox[6]->Enable();
		zoneNoteBox[7]->Enable();
	}
	else{
		trigger->trackProc->n[trigger->trackNum].zoneControlledCheckBox[7] = 0;
		zoneBox[6]->Disable();
		zoneBox[6]->SetValue(0);
		zoneNoteBox[7]->Disable();
	}

	if(zoneBox[6]->GetValue()){
		trigger->trackProc->n[trigger->trackNum].zoneControlledCheckBox[8] = 1;
		zoneBox[7]->Enable();
		zoneNoteBox[8]->Enable();
	}
	else{
		trigger->trackProc->n[trigger->trackNum].zoneControlledCheckBox[8] = 0;
		zoneBox[7]->Disable();
		zoneBox[7]->SetValue(0);
		zoneNoteBox[8]->Disable();
	}

	if(zoneBox[7]->GetValue()){
		trigger->trackProc->n[trigger->trackNum].zoneControlledCheckBox[9] = 1;
		zoneNoteBox[9]->Enable();
	}
	else{
		trigger->trackProc->n[trigger->trackNum].zoneControlledCheckBox[9] = 0;
		zoneNoteBox[9]->Disable();
	}
}

////////////////////////////////////////
void TriggerDialog::UpdateZoneSliders()
{
	//Set Knob Count
	int knobCount = 0;
	while(trigger->trackProc->n[trigger->trackNum].zoneControlledCheckBox[knobCount+1] != 0){
		knobCount++;
	}
	while(zoneControlledSlider->knobCount < knobCount){
		zoneControlledSlider->AddKnob();
	}
	while(zoneControlledSlider->knobCount > knobCount){
		zoneControlledSlider->DeleteKnob();
	}
}

/////////////////////////////////////////////////////////////
void TriggerDialog::OnCCOutputChannel(GNumberBoxEvent &event)
{
	ccOutputChannelBox->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].ccOutputChannel);
}

//////////////////////////////////////////////////////////
void TriggerDialog::OnCCOutputNote(GNumberBoxEvent &event)
{
	ccOutputNoteBox->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].ccOutputNote);
}

////////////////////////////////////////////////////////////////////
void TriggerDialog::OnCCOutputHighCompressor(GNumberBoxEvent &event)
{
	ccOutputHighCompressorBox->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].ccOutputHighCompressor);
}

///////////////////////////////////////////////////////////////////
void TriggerDialog::OnCCOutputLowCompressor(GNumberBoxEvent &event)
{
	ccOutputLowCompressorBox->GetValue().ToLong((long *) &trigger->trackProc->n[trigger->trackNum].ccOutputLowCompressor);
}

////////////////////////////////////////////////
void TriggerDialog::OnMouse(wxMouseEvent &event)
{
	okButton->SetFocus();
}

/////////////////////////////////////////////////////
void TriggerDialog::OnMouseWheel(wxMouseEvent &event)
{	
	//don't let the event trickle down to the parent.
}

///////////////////////////////////////////////////////////
void TriggerDialog::OnLowPercentSlider(GSliderEvent &event)
{
	trigger->trackProc->n[trigger->trackNum].lowPercent[currentZone] = (int)event.GetValue();
	curve->SetLowPercent(trigger->trackProc->n[trigger->trackNum].lowPercent[currentZone]);
	lowPercentText->SetLabel(wxString::Format(wxT("%d"), trigger->trackProc->n[trigger->trackNum].lowPercent[currentZone]));
	
	for(int i=0; i<127; ++i){
		trigger->trackProc->n[trigger->trackNum].dynamics[currentZone][i] = curve->velocities[i];
	}
}

////////////////////////////////////////////////////////////
void TriggerDialog::OnHighPercentSlider(GSliderEvent &event)
{
	trigger->trackProc->n[trigger->trackNum].highPercent[currentZone] = (int)event.GetValue();
	curve->SetHighPercent(trigger->trackProc->n[trigger->trackNum].highPercent[currentZone]);
	highPercentText->SetLabel(wxString::Format(wxT("%d"), trigger->trackProc->n[trigger->trackNum].highPercent[currentZone]));

	for(int i=0; i<127; ++i){
		trigger->trackProc->n[trigger->trackNum].dynamics[currentZone][i] = curve->velocities[i];
	}
}

////////////////////////////////////////////////////////
void TriggerDialog::OnVelToPosAvg(wxCommandEvent &event)
{
	if(velToPosAvgDlg == NULL){
		velToPosAvgDlg = new VelToPosAvgDlg(trigger);
		velToPosAvgDlg->Show();
		velToPosAvgDlg->SetFocus();
	}
	else{
		velToPosAvgDlg->Show();
		velToPosAvgDlg->SetFocus();
	}
}

///////////////////////////////////////////////////
void TriggerDialog::OnSample(wxCommandEvent &event)
{
	/*
	if(sampleDialog == NULL){
		sampleDialog = new SampleDialog(this);
		sampleDialog->Show();
		sampleDialog->SetFocus();
		sampleDialog->SetActiveSample(trigger->trackProc->n[trigger->trackNum].sampleFolder[currentZone]);
	}
	else{
		sampleDialog->Show();
		sampleDialog->SetFocus();
		sampleDialog->SetActiveSample(trigger->trackProc->n[trigger->trackNum].sampleFolder[currentZone]);
	}
	*/
}

////////////////////////////////////////////////////
void TriggerDialog::SetSampleFolder(wxString folder)
{
	//trigger->trackProc->n[trigger->trackNum].sampleFolder[currentZone] = folder;
	//sampleText->SetLabel(folder);
}