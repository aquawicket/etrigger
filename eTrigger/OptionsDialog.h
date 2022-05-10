//// OptionsDialog.h /////////////////////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <wx/dialog.h>
#include <wx/stattext.h>
#include <wx/combobox.h>
#include <wx/checkbox.h>
#include "../lib/Gwidgets/GButton/GButton.h"
#include "../lib/Gwidgets/GImage/GImage.h"
#include "../lib/Gwidgets/GNumberBox/GNumberBox.h"

#include "MainPanel.h"
#include "Tracks.h"

// XPM Images
#include "../Images/TopLeftCornerSide.xpm"
#include "../Images/TopLeftCornerTop.xpm"
#include "../Images/TopEdge.xpm"
#include "../Images/LeftEdge.xpm"
#include "../Images/Gui.xpm"
#include "../Images/Gui-Hover.xpm"
#include "../Images/Gui-Selected.xpm"
#include "../Images/Engine.xpm"
#include "../Images/Engine-Hover.xpm"
#include "../Images/Engine-Selected.xpm"
#include "../Images/joystickTab.xpm"
#include "../Images/joystickTab-hover.xpm"
#include "../Images/joystickTab-selected.xpm"
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
#include "../Images/folder.xpm"
#include "../Images/folder-hover.xpm"
#include "../Images/folder-click.xpm"
#include "../Images/ok2.xpm"
#include "../Images/ok2-hover.xpm"
#include "../Images/ok2-click.xpm"
#include "../Images/cancel2.xpm"
#include "../Images/cancel2-hover.xpm"
#include "../Images/cancel2-click.xpm"

class MainPanel;

//////////////////////////////////////
class OptionsDialog : public wxDialog
{
	public:
		OptionsDialog(MainPanel *parent, TrackProc &ref);
		~OptionsDialog();

		void UpdateSelection(wxString string);
		void VarsToTemp();
		void VarsToDlg();
		void TempToVars();
		void TempToDlg();
		void OnClose(wxCloseEvent &event);
		void OnGui(GButtonEvent &event);
		void OnEngine(GButtonEvent &event);
		void OnJoystick(GButtonEvent &event);
		void OnSplashScreen(wxCommandEvent &event);
		void OnEnableMeters(wxCommandEvent &event);
		void OnPreLoad(wxCommandEvent &event);
		void OnOnsetType(wxCommandEvent &event);
		void OnAudioBuffer(wxCommandEvent &event);
		void OnFileText(wxCommandEvent &event);
		void OnFileSelect(GButtonEvent &event);
		void OnMouseSensitivity(GNumberBoxEvent &event);
		void OnJoystickPolling(GNumberBoxEvent &event);
		
		void OnFolderText(wxCommandEvent &event);
		void OnFolderSelect(GButtonEvent &event);

		void OnJoyMinX(GNumberBoxEvent &event);
		void OnJoyMinY(GNumberBoxEvent &event);
		void OnJoyMinZ(GNumberBoxEvent &event);
		void OnJoyMinR(GNumberBoxEvent &event);
		void OnJoyMinU(GNumberBoxEvent &event);
		void OnJoyMinV(GNumberBoxEvent &event);

		void OnJoyMaxX(GNumberBoxEvent &event);
		void OnJoyMaxY(GNumberBoxEvent &event);
		void OnJoyMaxZ(GNumberBoxEvent &event);
		void OnJoyMaxR(GNumberBoxEvent &event);
		void OnJoyMaxU(GNumberBoxEvent &event);
		void OnJoyMaxV(GNumberBoxEvent &event);
		void OnJoyMaxDetect(GButtonEvent &event);
		void OnJoyMaxReset(GButtonEvent &event);
		void OnJoyMaxOk(GButtonEvent &event);
		void OnJoyMaxCancel(GButtonEvent &event);
		void OnIONmax(GNumberBoxEvent &event);
		void OnRetriggerSafty(GNumberBoxEvent &event);
		void OnRetriggerThreshold(GNumberBoxEvent &event);
		void OnFlamAdjustment(GNumberBoxEvent &event);
		void OnRollAdjustment(GNumberBoxEvent &event);
		void OnToolTips(wxCommandEvent &event);
		void OnMidiBleed(wxCommandEvent &event);
		void OnMidiChannels(wxCommandEvent &event);
		void OnMouse(wxMouseEvent &event);
		void OnOk(GButtonEvent &event);
		void OnCancel(GButtonEvent &event);
		
		MainPanel *mainPanel;
		TrackProc *trackProc;

		// Temporary data holder
		wxString onsetType;
		bool splashScreen;
		bool toolTips;
		bool enableMeters;
		bool preLoad;
		int audioBuffer;
		wxString initPath;
		wxString initFilename;
		wxString initFolderPath;
		int mouseSensitivity;
		bool midiBleed;
		bool midiChannel[16];
		int retriggerSafty;
		int retriggerThreshold;
		int flamAdjustment;
		int rollAdjustment;
		int pollSpeed;
		int joyMinX;
		int joyMinY;
		int joyMinZ;
		int joyMinR;
		int joyMinU;
		int joyMinV;
		int joyMaxX;
		int joyMaxY;
		int joyMaxZ;
		int joyMaxR;
		int joyMaxU;
		int joyMaxV;

		//Corners and edges
		GImage* topLeftCornerSide;
		GImage* topLeftCornerTop;
		GImage* topEdge1;
		GImage* topEdge2;
		GImage* topEdge3;
		GImage* leftEdge3;
		GImage* leftEdge4;
		GImage* leftEdge5;
		GImage* leftEdge6;
		GImage* leftEdge7;
		GImage* leftEdge8;
		GImage* leftEdge9;
		GImage* leftEdge10;

		//Buttons
		GButton* guiButton;
		GButton* guiSelected;
		GButton* engineButton;
		GButton* engineSelected;
		GButton* joystickButton;
		GButton* joystickSelected;
		GButton* ok;
		GButton* cancel;

		////// Panels //////
		//// GUI Panel
		wxPanel* guiPanel;
		wxCheckBox *splashScreenBox;
		wxCheckBox *enableMetersBox;
		wxCheckBox *preLoadBox;
		wxCheckBox *toolTipsBox;
		wxTextCtrl *filePath;
		GButton *fileSelector;
		GNumberBox *mouseSenseBox;
		
		//// Engine Panel
		wxPanel* enginePanel;
		wxArrayString Types;
		wxComboBox *Type;
		wxArrayString buffers;
		wxComboBox *audioBufferBox;
		wxCheckBox *midiBleedBox;
		wxCheckBox *midiChannelAllBox;
		wxCheckBox *midiChannel1Box;
		wxCheckBox *midiChannel2Box;
		wxCheckBox *midiChannel3Box;
		wxCheckBox *midiChannel4Box;
		wxCheckBox *midiChannel5Box;
		wxCheckBox *midiChannel6Box;
		wxCheckBox *midiChannel7Box;
		wxCheckBox *midiChannel8Box;
		wxCheckBox *midiChannel9Box;
		wxCheckBox *midiChannel10Box;
		wxCheckBox *midiChannel11Box;
		wxCheckBox *midiChannel12Box;
		wxCheckBox *midiChannel13Box;
		wxCheckBox *midiChannel14Box;
		wxCheckBox *midiChannel15Box;
		wxCheckBox *midiChannel16Box;
		GNumberBox *retriggerSaftyBox;
		GNumberBox *retriggerThresholdBox;
		GNumberBox *flamAdjustmentBox;
		GNumberBox *rollAdjustmentBox;

		wxTextCtrl *folderPath;
		GButton *folderSelector;
		
		//// Joystick Panel
		wxPanel* joystickPanel;
		GNumberBox *joyPolling;
		GNumberBox *joyMinXBox;
		GNumberBox *joyMinYBox;
		GNumberBox *joyMinZBox;
		GNumberBox *joyMinRBox;
		GNumberBox *joyMinUBox;
		GNumberBox *joyMinVBox;
		GNumberBox *joyMaxXBox;
		GNumberBox *joyMaxYBox;
		GNumberBox *joyMaxZBox;
		GNumberBox *joyMaxRBox;
		GNumberBox *joyMaxUBox;
		GNumberBox *joyMaxVBox;
		GButton *joyMaxDetect;
		GButton *joyMaxReset;
		GButton *joyMaxOk;
		GButton *joyMaxCancel;
		
	private:
		DECLARE_EVENT_TABLE() 
};

#endif //OPTIONSDIALOG_H

