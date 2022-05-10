//// GToggle.h /////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef GTOGGLE_H
#define GTOGGLE_H

#include <wx/panel.h>
#include <wx/dcbuffer.h> 
#include <wx/msgdlg.h>
#include <wx/image.h>

/////////////////////////////////////////
class GToggleEvent: public wxCommandEvent 
{ 
	public: 
		GToggleEvent(wxEventType commandType = wxEVT_NULL, int id = 0 ); 

		virtual wxEvent *Clone() const { return new GToggleEvent(*this); } 

	private: 
	DECLARE_DYNAMIC_CLASS(GToggleEvent) 
}; 

BEGIN_DECLARE_EVENT_TYPES() 
	DECLARE_EVENT_TYPE(wxEVT_COMMAND_GTOGGLE, -1) 
END_DECLARE_EVENT_TYPES() 

typedef void (wxEvtHandler::*wxGToggleEventFunction)(GToggleEvent&); 

#define EVT_GTOGGLE(id, fn) \
	DECLARE_EVENT_TABLE_ENTRY(wxEVT_COMMAND_GTOGGLE, id, -1,  \
	(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)  \
	wxStaticCastEvent(wxGToggleEventFunction, & fn), (wxObject *) NULL ),


/////////////////////////////
class GToggle: public wxPanel
{ 
	public: 
	// Constructors 
		GToggle(); 

		GToggle(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxImage& on, const wxImage& off); 
		GToggle(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxString& on, const wxString& hover); 
		GToggle(wxWindow* parent, wxWindowID id, const wxPoint& pos, const char** on, const char** off); 

		// Destructor 
		virtual ~GToggle(); 

		// Creators
		bool Create(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxImage& on, const wxImage& off); 
		bool Create(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxString& on, const wxString& off);
		bool Create(wxWindow* parent, wxWindowID id, const wxPoint& pos, const char** on, const char** off);	

	private: 
		void DrawBackground(wxDC &dc); 
		void OnEraseBackground(wxEraseEvent& event); 
		void OnPaint(wxPaintEvent &event); 
		void OnMouse(wxMouseEvent &event); 

		wxImage c_on;
		wxImage c_off;

		bool on;

		DECLARE_EVENT_TABLE() 
};

#endif //GTOGGLE_H
