//// MidiCC.h //////////////////////////////////////////////////////////////////////////
//
//
/////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef MIDICC_H
#define MIDICC_H

#include <wx/image.h>
#include <wx/menu.h>
#include <wx/msgdlg.h>
#include <wx/stattext.h>
#include <wx/window.h>

#include "../lib/Gwidgets/GButton/GButton.h"
#include "../lib/Gwidgets/GMeter/GMeter.h"
#include "../lib/Gwidgets/GText/GText.h"
#include "../lib/Gwidgets/GImageSelector/GImageSelector.h"

#include "MidiCCDialog.h"
#include "Midi.h"
#include "Tracks.h"

#include "../Images/midicc.xpm"
#include "../Images/midicc-focused.xpm"
#include "../Images/setup.xpm"
#include "../Images/setup-hover.xpm"
#include "../Images/setup-click.xpm"
#include "../Images/setup-focused.xpm"
#include "../Images/setup-hover-focused.xpm"
#include "../Images/setup-click-focused.xpm"

#define FDR_NO_MOUSE_CAPTURE 0x0001 

class MidiCCDialog;
class TrackPanel;
class TrackProc;

///////////////////////////////
class MidiCC: public wxWindow
{ 
	public: 
		MidiCC(TrackPanel *parent, TrackProc *ref, wxPoint pos, int num); 
		~MidiCC();
		void UpdateDialog();

		TrackProc *trackProc;
		int trackNum;
		bool focused;
		int counter;
		GMeter *meter;
		void SetTrackNum(int num);
		MidiCCDialog *midiCCDialog;
		
	private:
		void OnPaint(wxPaintEvent &WXUNUSED(event));
		void OnEraseBackground(wxEraseEvent& event);
		void DrawBackground(wxDC &dc);
		void OnSetup(GButtonEvent &event);
		void OnMenuDeleteTrack(wxCommandEvent &event);
		void OnMenuAddTrigger(wxCommandEvent &event);
		void OnMenuAddMidiCC(wxCommandEvent &event);
		void OnFocus(wxFocusEvent &event);
		void OnKillFocus(wxFocusEvent &event);
		void OnMouse(wxMouseEvent &event);
		void OnMouseWheel(wxMouseEvent &event);
		bool UseMouseCapture();
		void OnImageChange(GImageSelectorEvent &event);
		void OnTextChange(GTextEvent &event);

		wxImage *image1;
		wxImage *image2;
		TextEdit *text;
		GButton *setup;
		GImageSelector *image;

		bool draggingTrack;
		wxPoint trackPoint;
		wxPoint mousePoint;
		int dropSpot;

	public:

		DECLARE_EVENT_TABLE(); 
};

#endif //MIDICC_H
