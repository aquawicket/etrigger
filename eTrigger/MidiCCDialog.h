//// MidiCCDialog.h /////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef MIDICCDIALOG_H
#define MIDICCDIALOG_H

#include <wx/dialog.h>
#include <wx/stattext.h>
#include <wx/checkbox.h>
#include "MidiCC.h"
#include "../lib/Gwidgets/GButton/GButton.h"
#include "../lib/Gwidgets/GKnob/GKnob.h"
#include "../lib/Gwidgets/GImage/GImage.h"
#include "../lib/Gwidgets/GNumberBox/GNumberBox.h"
#include "Process.h"
#include "DrumTypeCodes.h"

// XPM Images
#include "../Images/TopLeftCornerSide.xpm"
#include "../Images/TopLeftCornerTop.xpm"
#include "../Images/TopEdge.xpm"
#include "../Images/LeftEdge.xpm"
#include "../Images/Input.xpm"
#include "../Images/input-hover.xpm"
#include "../Images/Input-Selected.xpm"
#include "../Images/pedalEvents.xpm"
#include "../Images/pedalEvents-hover.xpm"
#include "../Images/pedalEvents-selected.xpm"
#include "../Images/Output.xpm"
#include "../Images/Output-Hover.xpm"
#include "../Images/Output-Selected.xpm"
#include "../Images/learn.xpm"
#include "../Images/Learn-Hover.xpm"
#include "../Images/Learn-Click.xpm"
#include "../Images/keyboard.xpm"
#include "../Images/Mouse.xpm"
#include "../Images/MidiDevice.xpm"
#include "../Images/Joystick.xpm"
#include "../Images/ok2.xpm"
#include "../Images/ok2-hover.xpm"
#include "../Images/ok2-click.xpm"
#include "../Images/cancel2.xpm"
#include "../Images/cancel2-hover.xpm"
#include "../Images/cancel2-click.xpm"

class MidiCC;
class LearnEvent;


class MidiCCDialog : public wxDialog
{
	public:
		MidiCCDialog(MidiCC* parent);
		~MidiCCDialog();
		void InitVariables();

		//MAIN WINDOW
		void UpdateSelection(wxString string);
		void UpdateInputImage(bool hideAll);
		void VarsToTemp();
		void VarsToDlg();
		void TempToVars();
		void TempToDlg();
		void OnInput(GButtonEvent &event);
		void OnPedalEvents(GButtonEvent &event);
		void OnOutput(GButtonEvent &event);
		void OnLearn(GButtonEvent &event);
		void OnLearnEvent(LearnEvent &event);
		void OnDrumTypeSelect(wxCommandEvent &event);
		void OnPedalEventBox(wxCommandEvent &event);
		void OnPedalEventThreshold(GNumberBoxEvent &event);
		void OnPedalEventNote(GNumberBoxEvent &event);
		void OnPedalEventVolume(GNumberBoxEvent &event);
		void OnPedalSpeedIntensity(GNumberBoxEvent &event);
		void OnMidiOutNote(GNumberBoxEvent &event);
		void OnMidiOutChannel(GNumberBoxEvent &event);
		void OnLowCompressor(GNumberBoxEvent &event); 
		void OnHighCompressor(GNumberBoxEvent &event); 
		void OnCCReverse(wxCommandEvent &event);
		void OnMouse(wxMouseEvent &event);
		void OnOk(GButtonEvent &event);
		void OnCancel(GButtonEvent &event);
		void OnClose(wxCloseEvent &event);
		
		MidiCC* midiCC;

		// Temporary data holder
		wxString deviceName;
		wxString inputDetails;
		int inputCode;
		int drumType;
		int outputNote;
		int outputChannel;
		int lowCompressor;
		int highCompressor;
		bool ccReverse;

		bool pedalDownEvent;
		int pedalDownThreshold;
		int pedalVolume;
		int pedalNote;
		int pedalSpeedIntensity;
		
		//Corners and edges
		GImage *topLeftCornerSideImage;
		GImage *topLeftCornerTopImage;
		GImage *topEdge1Image;
		GImage *topEdge2Image;
		GImage *topEdge3Image;
		GImage *leftEdge1Image;
		GImage *leftEdge2Image;
		GImage *leftEdge3Image;
		GImage *leftEdge4Image;
		GImage *leftEdge5Image;
		GImage *leftEdge6Image;
		GImage *leftEdge7Image;
		GImage *leftEdge8Image;

		//Buttons
		GButton *inputButton;
		GButton *inputSelectedButton;
		GButton *pedalEventsButton;
		GButton *pedalEventsSelectedButton;
		GButton *outputButton;
		GButton *outputSelectedButton;
		GButton *okButton;
		GButton *cancelButton;

		////// Panels //////

		////Input Panel
		wxPanel *inputPanel;
		GButton *learnButton;
		wxStaticText *deviceText;
		wxStaticText *infoText;
		wxComboBox *drumTypeBox;
		GImage *mouseImage;
		GImage *keyboardImage;
		GImage *midiDeviceImage;
		GImage *joystickImage;

		//// Pedal Events Panel
		wxPanel *pedalEventsPanel;
		wxCheckBox *pedalEventBox;
		GNumberBox *pedalEventThresholdBox;
		GNumberBox *pedalEventNoteBox;
		GNumberBox *pedalEventVolumeBox;
		GNumberBox *pedalSpeedIntensityBox;

		////Output Panel
		wxPanel *outputPanel;
		GNumberBox *midiOutNoteBox;
		GNumberBox *midiOutChannelBox;
		GNumberBox *lowCompressorBox;
		GNumberBox *highCompressorBox;
		wxCheckBox *ccReverseBox;

	private:
		DECLARE_EVENT_TABLE() 
};

#endif //MIDICCDIALOG_H

