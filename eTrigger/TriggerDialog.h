//// TriggerDialog.h /////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef TRIGGERDIALOG_H
#define TRIGGERDIALOG_H

#include <wx/dialog.h>
#include <wx/stattext.h>
#include <wx/combobox.h>
#include <wx/checkbox.h>
#include <wx/radiobut.h>
#include <wx/button.h>

#include "Trigger.h"
#include "VelocityDialog.h"
#include "SampleDialog.h"

#include "../lib/Gwidgets/GButton/GButton.h"
#include "../lib/Gwidgets/GKnob/GKnob.h"
#include "../lib/Gwidgets/GImage/GImage.h"
#include "../lib/Gwidgets/GNumberBox/GNumberBox.h"
#include "../lib/Gwidgets/GCurve/GCurve.h"
#include "Process.h"
#include "SampleDialog.h"
#include "DrumTypeCodes.h"

// XPM Images
#include "../Images/TopLeftCornerSide.xpm"
#include "../Images/TopLeftCornerTop.xpm"
#include "../Images/TopEdge.xpm"
#include "../Images/LeftEdge.xpm"
#include "../Images/zone1.xpm"
#include "../Images/Zone1-Hover.xpm"
#include "../Images/Zone1-Selected.xpm"
#include "../Images/zone2.xpm"
#include "../Images/Zone2-Hover.xpm"
#include "../Images/Zone2-Selected.xpm"
#include "../Images/zone3.xpm"
#include "../Images/Zone3-Hover.xpm"
#include "../Images/Zone3-Selected.xpm"
#include "../Images/Input.xpm"
#include "../Images/input-hover.xpm"
#include "../Images/Input-Selected.xpm"
#include "../Images/learn.xpm"
#include "../Images/Learn-Hover.xpm"
#include "../Images/Learn-Click.xpm"
#include "../Images/retrigger.xpm"
#include "../Images/retrigger-hover.xpm"
#include "../Images/retrigger-selected.xpm"
#include "../Images/detect.xpm"
#include "../Images/detect-hover.xpm"
#include "../Images/detect-click.xpm"
#include "../Images/reset.xpm"
#include "../Images/reset-hover.xpm"
#include "../Images/reset-click.xpm"
#include "../Images/ok3.xpm"
#include "../Images/ok3-hover.xpm"
#include "../Images/ok3-click.xpm"
#include "../Images/cancel3.xpm"
#include "../Images/cancel3-hover.xpm"
#include "../Images/cancel3-click.xpm"
#include "../Images/dynamics.xpm"
#include "../Images/dynamics-hover.xpm"
#include "../Images/dynamics-selected.xpm"
#include "../Images/compressorSlit.xpm"
#include "../Images/lowPercent.xpm"
#include "../Images/highPercent.xpm"
#include "../Images/cutoffSlit.xpm"
#include "../Images/blueSlider.xpm"
#include "../Images/redSlider.xpm"
#include "../Images/fullVelControl.xpm"
#include "../Images/fullVelControl-hover.xpm"
#include "../Images/fullVelControl-click.xpm"
#include "../Images/alternation.xpm"
#include "../Images/Output.xpm"
#include "../Images/Output-Hover.xpm"
#include "../Images/Output-Selected.xpm"
#include "../Images/multiZone.xpm"
#include "../Images/multiZone-hover.xpm"
#include "../Images/multiZone-selected.xpm"
#include "../Images/keyboard.xpm"
#include "../Images/AudioDevice.xpm"
#include "../Images/MidiDevice.xpm"
#include "../Images/Joystick.xpm"
#include "../Images/knobback.xpm"
#include "../Images/knob2.xpm"
#include "../Images/longSlider.xpm"
#include "../Images/ok2.xpm"
#include "../Images/ok2-hover.xpm"
#include "../Images/ok2-click.xpm"
#include "../Images/cancel2.xpm"
#include "../Images/cancel2-hover.xpm"
#include "../Images/cancel2-click.xpm"
#include "../Images/folder.xpm"
#include "../Images/folder-hover.xpm"
#include "../Images/folder-click.xpm"

#include "VelToPosAvgDlg.h"

class Trigger;
class LearnEvent;
class VelocityDialog;
class SampleDialog;
class VelToPosDlg;

class TriggerDialog : public wxDialog
{
	public:
		TriggerDialog(Trigger* parent);
		~TriggerDialog();
		void InitVariables();

		//MAIN WINDOW
		void UpdateSelection(wxString string);
		void UpdateZones();
		void UpdateInputImage(bool hideAll);
		void UpdateOutputType();
		void VarsToTemp();
		void VarsToDlg();
		void TempToVars();
		void TempToDlg();
		void OnZone1(GButtonEvent &event);
		void OnZone2(GButtonEvent &event);
		void OnZone3(GButtonEvent &event);
		void OnInput(GButtonEvent &event);
		void OnRetrigger(GButtonEvent &event);
		void OnDynamics(GButtonEvent &event);
		void OnAlternation(GButtonEvent &event);
		void OnOutput(GButtonEvent &event);
		void OnMultiZone(GButtonEvent &event);
		void OnLearn(GButtonEvent &event);
		void OnLearnEvent(LearnEvent &event);
		void OnDrumTypeSelect(wxCommandEvent &event);
		void OnZonesSelect(wxCommandEvent &event);
		void OnMidiOutNote(GNumberBoxEvent &event);
		void OnMidiOutChannel(GNumberBoxEvent &event);
		void OnRetriggerDetect(GButtonEvent &event);
		void OnRetriggerReset(GButtonEvent &event);
		void OnRetriggerOk(GButtonEvent &event);
		void OnRetriggerCancel(GButtonEvent &event);
		void OnRetriggerBox(GNumberBoxEvent &event); 
		void OnCrosstalk(GNumberBoxEvent &event);

		void OnWaitTimeDetect(GButtonEvent &event);
		void OnWaitTimeReset(GButtonEvent &event);
		void OnWaitTimeOk(GButtonEvent &event);
		void OnWaitTimeCancel(GButtonEvent &event);
		void OnWaitTimeBox(GNumberBoxEvent &event);  

		void OnCompressorSlider(GSliderEvent &event);
		void OnCutOffSlider(GSliderEvent &event);
		void OnLowPercentSlider(GSliderEvent &event);
		void OnHighPercentSlider(GSliderEvent &event);
		void OnMultiZoneWaitTime(GNumberBoxEvent &event);
		void OnAntiMachineGun(GNumberBoxEvent &event);
        void OnNoteOff(wxCommandEvent &event);
		void OnAlternateReset(GNumberBoxEvent &event);
		void OnAlternateBox(wxCommandEvent &event);
		void OnAlternateRandomize(wxCommandEvent &event);
		void OnAlternateNoteBox1(GNumberBoxEvent &event);
		void OnAlternateNoteBox2(GNumberBoxEvent &event);
		void OnAlternateNoteBox3(GNumberBoxEvent &event);
		void OnAlternateNoteBox4(GNumberBoxEvent &event);
		void OnAlternateNoteBox5(GNumberBoxEvent &event);
		void OnAlternateNoteBox6(GNumberBoxEvent &event);
		void OnAlternateNoteBox7(GNumberBoxEvent &event);
		void OnAlternateNoteBox8(GNumberBoxEvent &event);
		void OnAlternateNoteBox9(GNumberBoxEvent &event);
		void OnAlternateNoteBox10(GNumberBoxEvent &event);
		void UpdateAlternateBoxes();
		void OnKnob(GKnobEvent &event);
		void OnCurve(GCurveEvent &event);
		void OnMidiCCControlledBox(wxCommandEvent &event);
		void OnMidiCCControlledNumber(GNumberBoxEvent &event);
		void OnMidiCCBox(wxCommandEvent &event);
	    void OnMidiCCNoteBox1(GNumberBoxEvent &event);
	    void OnMidiCCNoteBox2(GNumberBoxEvent &event);
	    void OnMidiCCNoteBox3(GNumberBoxEvent &event);
	    void OnMidiCCNoteBox4(GNumberBoxEvent &event);
	    void OnMidiCCNoteBox5(GNumberBoxEvent &event);
	    void OnMidiCCNoteBox6(GNumberBoxEvent &event);
	    void OnMidiCCNoteBox7(GNumberBoxEvent &event);
	    void OnMidiCCNoteBox8(GNumberBoxEvent &event);
	    void OnMidiCCNoteBox9(GNumberBoxEvent &event);
	    void OnMidiCCNoteBox10(GNumberBoxEvent &event);
		void OnMidiCCControlledSlider(GSliderEvent &event);
		void UpdateMidiCCText();
		void UpdateMidiCCBoxes();
		void UpdateMidiCCSliders();
		void OnVelocityBox(wxCommandEvent &event);
	    void OnVelocityNoteBox1(GNumberBoxEvent &event);
	    void OnVelocityNoteBox2(GNumberBoxEvent &event);
	    void OnVelocityNoteBox3(GNumberBoxEvent &event);
	    void OnVelocityNoteBox4(GNumberBoxEvent &event);
	    void OnVelocityNoteBox5(GNumberBoxEvent &event);
	    void OnVelocityNoteBox6(GNumberBoxEvent &event);
	    void OnVelocityNoteBox7(GNumberBoxEvent &event);
	    void OnVelocityNoteBox8(GNumberBoxEvent &event);
	    void OnVelocityNoteBox9(GNumberBoxEvent &event);
	    void OnVelocityNoteBox10(GNumberBoxEvent &event);
		void OnVelocityControlledSlider(GSliderEvent &event);
		void UpdateVelocityText();
		void UpdateVelocityBoxes();
		void UpdateVelocitySliders();
		void OnVelocityDialog(GButtonEvent &event);
		void OnPriority1(GNumberBoxEvent &event);
		void OnPriority2(GNumberBoxEvent &event);
		void OnPriority3(GNumberBoxEvent &event);
		void OnGravity1(GNumberBoxEvent &event);
		void OnGravity2(GNumberBoxEvent &event);
		void OnGravity3(GNumberBoxEvent &event);
		void OnVelocityBalance(GNumberBoxEvent &event);
		void OnHasRim(wxCommandEvent &event);
		void OnEnableCC(wxCommandEvent &event);
		void OnBasicOutput(wxCommandEvent &event);
	    void OnAlternatingOutput(wxCommandEvent &event);
	    void OnMidiCCControlledOutput(wxCommandEvent &event);
		void OnMidiCCControlledOutputNote(GNumberBoxEvent &event);
	    void OnVelocityControlledOutput(wxCommandEvent &event);
		void OnZoneControlledOutput(wxCommandEvent &event);
		void OnZoneBox(wxCommandEvent &event);
	    void OnZoneNoteBox1(GNumberBoxEvent &event);
	    void OnZoneNoteBox2(GNumberBoxEvent &event);
	    void OnZoneNoteBox3(GNumberBoxEvent &event);
	    void OnZoneNoteBox4(GNumberBoxEvent &event);
	    void OnZoneNoteBox5(GNumberBoxEvent &event);
	    void OnZoneNoteBox6(GNumberBoxEvent &event);
	    void OnZoneNoteBox7(GNumberBoxEvent &event);
	    void OnZoneNoteBox8(GNumberBoxEvent &event);
	    void OnZoneNoteBox9(GNumberBoxEvent &event);
	    void OnZoneNoteBox10(GNumberBoxEvent &event);
		void OnZoneControlledSlider(GSliderEvent &event);
		void OnSequenceOutput(wxCommandEvent &event);
		void OnFileSelect(GButtonEvent &event);
		void OnSequenceOverlap(wxCommandEvent &event);
		void OnMouseOutput(wxCommandEvent &event);
		void OnMouseXBox(GNumberBoxEvent &event);
		void OnMouseYBox(GNumberBoxEvent &event);
		void UpdateZoneText();
		void UpdateZoneBoxes();
		void UpdateZoneSliders();
		void OnCCOutputChannel(GNumberBoxEvent &event);
		void OnCCOutputNote(GNumberBoxEvent &event);
		void OnCCOutputHighCompressor(GNumberBoxEvent &event);
		void OnCCOutputLowCompressor(GNumberBoxEvent &event);
		void OnMouse(wxMouseEvent &event);
		void OnMouseWheel(wxMouseEvent &event);
		void OnOk(GButtonEvent &event);
		void OnCancel(GButtonEvent &event);
		void OnClose(wxCloseEvent &event);
		void OnVelToPosAvg(wxCommandEvent &event);
		void OnSample(wxCommandEvent &event);
		void SetSampleFolder(wxString folder);
		
		Trigger* trigger;

		// Temporary data holder
		wxString deviceName[3];
		wxString inputDetails[3];
		int inputCode[3];
		int drumType;
		int zones;
		int outputNote[3];
		int outputChannel[3];
		int audioThreshold[3];
		int retrigger[3];
		int crosstalk[3];
		int preGain[3];
		int preVolume[3];
		int highCompressor[3];
		int lowCompressor[3];
		int highPercent[3];
		int lowPercent[3];
		int highLimiter[3];
		int lowLimiter[3];
		int multiZoneWaitTime;
		bool noteOff[3];
		int antiMachineGunTime[3];
		bool basicOutput[3];
		bool alternateOutput[3];
		bool alternateRandom[3];
		int alternateReset[3];
		bool alternateCheckBox[3][100];
		int alternateNotes[3][100];
		bool midiCCControlledOutput[3];
		int midiCCControlledInputNote[3];
		bool midiCCControlledCheckBox[3][100];
		int midiCCControlledNotes[3][100];
		int midiCCControlledSliders[3][100];
		bool velocityControlledOutput[3];
		bool velocityControlledCheckBox[3][100];
		int velocityControlledNotes[3][100];
		int velocityControlledSliders[3][100];
		bool zoneControlledOutput;
		bool zoneControlledCheckBox[100];
		int zoneControlledNotes[100];
		int zoneControlledSliders[100];
		bool sequenceOutput[3];
		wxString sequenceFile[3];
		bool sequenceOverlap[3];
		bool mouseOutput[3];
		int mouseX[3];
		int mouseY[3];
		std::vector< wxPoint > pointsZone1;
		std::vector< wxPoint > pointsZone2;
		std::vector< wxPoint > pointsZone3;
		int curveVelocities[3][127];
		bool midiCCControlledVelocity[3];
		int midiCCControlledVelocityNote[3];
		int priority[3];
		int gravity[3];
		int velocityBalance;
		bool hasRim;
		bool enableCC; 
		int ccOutputChannel;
		int ccOutputNote;
		int ccOutputHighCompressor;
		int ccOutputLowCompressor;
		wxString sampleFolder[3];

		int currentZone;
	
		//Corners and edges
		GImage *topLeftCornerSideImage;
		GImage *topLeftCornerTopImage;
		GImage *topEdge1Image;
		GImage *topEdge2Image;
		GImage *topEdge3Image;
		GImage *topEdge4Image;
		GImage *leftEdge1Image;
		GImage *leftEdge2Image;
		GImage *leftEdge3Image;
		GImage *leftEdge4Image;
		GImage *leftEdge5Image;
		GImage *leftEdge6Image;
		GImage *leftEdge7Image;
		GImage *leftEdge8Image;

        //Buttons
		GButton *zone1Button;
		GButton *zone2Button;
		GButton *zone3Button;
		GButton *zone1SelectedButton;
		GButton *zone2SelectedButton;
		GButton *zone3SelectedButton;
		GButton *inputButton;
		GButton *inputSelectedButton;
		GButton *retriggerButton;
		GButton *retriggerSelectedButton;
		GButton *dynamicsButton;
		GButton *dynamicsSelectedButton;
		GButton *outputButton;
		GButton *outputSelectedButton;
		GButton *multiZoneButton;
		GButton *multiZoneSelectedButton;
		GButton *okButton;
		GButton *cancelButton;

		////// Panels //////

		////Input Panel
		wxPanel *inputPanel;
		GButton *learnButton;
		wxStaticText *device;
		wxStaticText *info;
		wxComboBox *drumTypeBox;
		wxComboBox *zonesSelectBox;
		wxArrayString zonenums;
		GKnob *knob;
		wxStaticText *knobValue;
		GImage *keyboardImage;
		GImage *audioDeviceImage;
		GImage *midiDeviceImage;
		GImage *joystickImage;

		////Retrigger Panel
		wxPanel* retriggerPanel;
		GNumberBox *retriggerBox;
		GButton *retriggerDetectButton;
		GButton *retriggerResetButton;
		GButton *retriggerOkButton;
		GButton *retriggerCancelButton;

		////Dynamics Panel
		wxPanel *dynamicsPanel;
		GCurve *curve;
		GSlider *compressorSlider;
		GSlider *cutoffSlider;
		GSlider *lowPercentSlider;
		GSlider *highPercentSlider;
		wxStaticText *lowCompressorText;
		wxStaticText *highCompressorText;
		wxStaticText *lowLimiterText;
		wxStaticText *highLimiterText;
		wxStaticText *lowPercentText;
		wxStaticText *highPercentText;
		GNumberBox *antiMachineGunBox;
		wxCheckBox *MidiCCControlledBox;
		GNumberBox *MidiCCControlledNumber;
		GButton *velocityDialogButton;
		VelocityDialog *velocityDialog;
		GNumberBox *crosstalkBox;

		////Output Panel
		wxPanel* outputPanel;
		wxRadioButton *basicOutputButton;
		wxRadioButton *alternatingOutputButton;
		wxRadioButton *midiCCControlledOutputButton;
		wxRadioButton *velocityControlledOutputButton;
		wxRadioButton *zoneControlledOutputButton;
		wxRadioButton *sequenceOutputButton;
		wxRadioButton *mouseOutputButton;
		GNumberBox *midiOutChannelBox;	
		wxCheckBox *noteOffBox;

		//Sample Output
		SampleDialog *sampleDialog;
		wxButton *outputSample;
		wxStaticText *sampleText;

		//basic Output
		wxPanel* basicOutputPanel;
		wxStaticText *midiNoteText;
		GNumberBox *midiOutNoteBox;

		//alternating Output
		wxPanel* alternatingOutputPanel;
		wxStaticText *alternateResetText;
		GNumberBox *alternateResetBox;
		wxCheckBox *alternateRandomBox;
		wxCheckBox *alternateBox[8];
		GNumberBox *alternateNoteBox[10];

		//MidiCC Controlled Output
		wxPanel* midiCCControlledOutputPanel;
		wxStaticText *midiCCControlledOutputNoteText;
		GNumberBox *midiCCControlledInputNoteBox;
		wxCheckBox *midiCCBox[8];
		GNumberBox *midiCCNoteBox[10];
		wxStaticText *midiCCText[10];
		GSlider *midiCCControlledSlider;

		//Velocity Controlled Output
		wxPanel* velocityControlledOutputPanel;
		wxCheckBox *velocityBox[8];
		GNumberBox *velocityNoteBox[10];
		wxStaticText *velocityText[10];
		GSlider *velocityControlledSlider;

		//Zone Controlled Output
		wxPanel* zoneControlledOutputPanel;
		wxCheckBox *zoneBox[8];
		GNumberBox *zoneNoteBox[10];
		wxStaticText *zoneText[10];
		GSlider *zoneControlledSlider;

		//Sequence Output
		wxPanel* sequenceOutputPanel;
		wxButton* newSequenceButton;
		wxTextCtrl *filePath;
		GButton *fileSelector;
		wxCheckBox *sequenceOverlapBox;

		//Mouse Output
		wxPanel* mouseOutputPanel;
		wxStaticText *mouseText;
		GNumberBox *mouseXBox;
		GNumberBox *mouseYBox;

		////MultiZone Panel
		wxPanel* multiZonePanel;
		GNumberBox *multiZoneWaitTimeBox;
		GButton *waitTimeDetectButton;
		GButton *waitTimeResetButton;
		GButton *waitTimeOkButton;
		GButton *waitTimeCancelButton;
		GNumberBox *priority1;
		GNumberBox *priority2;
		GNumberBox *priority3;
		GNumberBox *gravity1;
		GNumberBox *gravity2;
		GNumberBox *gravity3;
		GNumberBox *velocityBalanceBox;
		wxCheckBox *hasRimBox;
		wxCheckBox *enableCCBox; 
		GNumberBox *ccOutputChannelBox;
		GNumberBox *ccOutputNoteBox;
		GNumberBox *ccOutputHighCompressorBox;
		GNumberBox *ccOutputLowCompressorBox;
		wxButton *velToPosAvgButton;
		VelToPosAvgDlg *velToPosAvgDlg;

	private:
		DECLARE_EVENT_TABLE() 
};

#endif //TRIGGERDIALOG_H
