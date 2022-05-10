//// GMeter.h /////////////////////////////////////////////////////////////////////////////
//
//  This is a graphical VU meter much like what you see on a digital equalizer.
//  You may create a meter and Hit it on a 100% scale (1 - 100).
//  The Timer will create an animated peak falloff if desired.
//
//  The control will draw a meter from green to red.
//
//  Todo:
//		We need a way to start and stop the global timer when we want to enable/diable meters.
//
///////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef GMETER_H
#define GMETER_H

#include <wx/window.h>
#include <wx/panel.h>
#include <wx/dcbuffer.h> 
#include <wx/msgdlg.h>
#include <wx/stopwatch.h>
#include <wx/timer.h>

/////// GMeter Event ///////////////////
class GMeterEvent: public wxCommandEvent 
{ 
	public: 
		GMeterEvent(wxEventType commandType = wxEVT_NULL, int id = 0 ); 

		void SetValue(int value) { level = value; }
		int GetValue() { return level; }

		virtual wxEvent *Clone() const { return new GMeterEvent(*this); } // required for sending with wxPostEvent() 

	private: 
		int level;

	DECLARE_DYNAMIC_CLASS(GMeterEvent) 
}; 

BEGIN_DECLARE_EVENT_TYPES() 
	DECLARE_EVENT_TYPE(wxEVT_COMMAND_GMETER, -1) 
END_DECLARE_EVENT_TYPES() 

typedef void (wxEvtHandler::*wxGMeterEventFunction)(GMeterEvent&); 

#define EVT_GMETER(id, fn) \
	DECLARE_EVENT_TABLE_ENTRY(wxEVT_COMMAND_GMETER, id, -1,  \
	(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)  \
	wxStaticCastEvent(wxGMeterEventFunction, & fn), (wxObject *) NULL ),




////////////////////////////
class GMeter: public wxPanel
{ 

public: 

	GMeter(wxWindow* parent, wxWindowID id,	const wxPoint& pos, const wxSize& size, bool falloff); 
	~GMeter(); 

	bool Create(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size); 
    void OnMouse(wxMouseEvent &event);
	void OnPaint(wxPaintEvent &WXUNUSED(event));
	void OnEraseBackground(wxEraseEvent& event);
	void Hit(int val);
	void OnGMeterEvent(GMeterEvent &event);
	bool Notify(); //return 1 if we need to progess more

    //Settings
	int SPEED1;
	int SPEED2;
	bool PEAK;
	int SPACING;

	wxSize mySize;

	int value;
	int falloff;
	
	wxStopWatch sw;
	long temp;
	long temp2;
	int falltemp;
	int peakfall;

	wxColour hitColor;
	wxColour peakcolor;

	wxMemoryDC *memDC;
	
	bool updateFlag;

	DECLARE_EVENT_TABLE();

};

#endif //GMeter_H
