//// Trigger.h //////////////////////////////////////////////////////////////////////////
//
//
/////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef TRIGGER_H
#define TRIGGER_H

#include <wx/window.h>
#include <wx/msgdlg.h>
#include <wx/stattext.h>
#include <wx/image.h>
#include <wx/menu.h>

#include "../lib/Gwidgets/GButton/GButton.h"
#include "../lib/Gwidgets/GMeter/GMeter.h"
#include "../lib/Gwidgets/GSlider/GSlider.h"
#include "../lib/Gwidgets/GKnob/GKnob.h"
#include "../lib/Gwidgets/GText/GText.h"
#include "../lib/Gwidgets/GImageSelector/GImageSelector.h"

#include "Tracks.h"
#include "Midi.h"
#include "TriggerDialog.h"

#include "../Images/track.xpm"
#include "../Images/track-focused.xpm"
#include "../Images/setup.xpm"
#include "../Images/setup-hover.xpm"
#include "../Images/setup-click.xpm"
#include "../Images/setup-focused.xpm"
#include "../Images/setup-hover-focused.xpm"
#include "../Images/setup-click-focused.xpm"
#include "../Images/slider.xpm"
#include "../Images/slider-focused.xpm"
#include "../Images/knob.xpm"
#include "../Images/knob-focused.xpm"

#define FDR_NO_MOUSE_CAPTURE 0x0001 

class TriggerDialog;
class TrackPanel;
class TrackProc;

///////////////////////////////
class Trigger: public wxWindow
{ 
	public: 
		Trigger(TrackPanel *parent, TrackProc *ref, wxPoint pos, int num);
		~Trigger(); 
		void UpdateDialog();

		TrackProc *trackProc;
		int trackNum;

		bool focused;
		int counter;
		GMeter *meter;
		GSlider *slider;
		void SetTrackNum(int num);
		bool preLoad;
		TriggerDialog *triggerDialog;

	private:
		void OnEraseBackground(wxEraseEvent& event); 
		void OnPaint(wxPaintEvent &WXUNUSED(event));
		void DrawBackground(wxDC &dc);
		void OnSetup(GButtonEvent &event);
		void OnMenuDeleteTrack(wxCommandEvent &event);
		void OnMenuAddTrigger(wxCommandEvent &event);
		void OnMenuAddMidiCC(wxCommandEvent &event);
		void OnFocus(wxFocusEvent &event);
		void OnKillFocus(wxFocusEvent &event);
		void OnSlider(GSliderEvent& event);
		void OnMouse(wxMouseEvent &event);
		void OnMouseWheel(wxMouseEvent &event);
		bool UseMouseCapture();
		void OnImageChange(GImageSelectorEvent &event);
		void OnTextChange(GTextEvent &event);

		//wxImage *image1;
		//wxImage *image2;
		GImage *background;
		TextEdit *text;
		GButton *setup;
		GImageSelector *image;

		bool draggingTrack;
		wxPoint trackPoint;
		wxPoint mousePoint;
		int dropSpot;

	public:
		GKnob *knob;

	private:
		DECLARE_EVENT_TABLE(); 
};

#endif //TRIGGER_H

