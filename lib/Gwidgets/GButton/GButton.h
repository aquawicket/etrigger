//// GButton.h /////////////////////////////////////////////////////////////////////////////
//
//  Graphic Button Class
//  This class will allow you to use images files as buttons in wxWidgets.
//  It supports the basic button image, mouse over image, and click image.
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef GBUTTON_H
#define GBUTTON_H

#include <wx/panel.h>
#include <wx/dcbuffer.h> 
#include <wx/msgdlg.h>
#include <wx/image.h>

/////////////////////////////////////////
class GButtonEvent: public wxCommandEvent 
{ 
	public: 
		GButtonEvent(wxEventType commandType = wxEVT_NULL, int id = 0 ); 

		virtual wxEvent *Clone() const { return new GButtonEvent(*this); } 

	private: 
	DECLARE_DYNAMIC_CLASS(GButtonEvent) 
}; 

BEGIN_DECLARE_EVENT_TYPES() 
	DECLARE_EVENT_TYPE(wxEVT_COMMAND_GBUTTON, -1) 
END_DECLARE_EVENT_TYPES() 

typedef void (wxEvtHandler::*wxGButtonEventFunction)(GButtonEvent&); 

#define EVT_GBUTTON(id, fn) \
	DECLARE_EVENT_TABLE_ENTRY(wxEVT_COMMAND_GBUTTON, id, -1,  \
	(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)  \
	wxStaticCastEvent(wxGButtonEventFunction, & fn), (wxObject *) NULL ),


/////////////////////////////
class GButton: public wxPanel
{ 
	public: 
		GButton(); 

		GButton(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxImage& button);
		GButton(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxString& button);
		GButton(wxWindow* parent, wxWindowID id, const wxPoint& pos, const char** button);
		GButton(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxImage& button,
			    const wxImage& hover); 
		GButton(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxString& button,
			    const wxString& hover); 
		GButton(wxWindow* parent, wxWindowID id, const wxPoint& pos, const char** button,
			    const char** hover); 
		GButton(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxImage& button,
			    const wxImage& hover, const wxImage& click); 
		GButton(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxString& button,
			    const wxString& hover, const wxString& click); 
		GButton(wxWindow* parent, wxWindowID id, const wxPoint& pos, const char** button,
			    const char** hover, const char** click); 
		GButton(wxWindow* parent, wxWindowID id, const wxPoint& pos, const char** button,
			    const char** hover, const char** click, const char** focusedButton,
			    const char** focusedHover, const char** focusedClick); 

		// Destructor 
		virtual ~GButton(); 

		// Creators
		bool Create(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxImage& button); 
		bool Create(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxString& button);
		bool Create(wxWindow* parent, wxWindowID id, const wxPoint& pos, const char** button);
		bool Create(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxImage& button,
			        const wxImage& hover); 
		bool Create(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxString& button, 
			        const wxString& hover);
		bool Create(wxWindow* parent, wxWindowID id, const wxPoint& pos, const char** button, 
			        const char** hover);
		bool Create(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxImage& button,
			        const wxImage& hover, const wxImage& click); 
		bool Create(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxString& button, 
			        const wxString& hover, const wxString& click);
		bool Create(wxWindow* parent, wxWindowID id, const wxPoint& pos, const char** button, 
			        const char** hover, const char** click); 
		bool Create(wxWindow* parent, wxWindowID id, const wxPoint& pos, const char** button, 
			        const char** hover, const char** click, const char** focusedButton,
					const char** focusedHover, const char** focusedClick); 

		bool focused;
	
	private: 
		void DrawBackground(wxDC &dc); 
		void OnEraseBackground(wxEraseEvent& event); 
		void OnPaint(wxPaintEvent &event); 
		void OnMouse(wxMouseEvent &event); 

		bool allowHover;
		bool allowClick;
		bool allowFocused;

		wxImage c_button;
		wxImage c_hover;
		wxImage c_click;
		wxImage c_focusedButton;
		wxImage c_focusedHover;
		wxImage c_focusedClick;

		bool hover;
		bool click;

		DECLARE_EVENT_TABLE() 
};

#endif //GBUTTON_H
