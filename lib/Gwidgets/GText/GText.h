//// GText.h /////////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef GTEXT_H
#define GTEXT_H

#include <wx/panel.h>
#include <wx/dcbuffer.h> 
#include <wx/msgdlg.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/sysopt.h>
#include <wx/textctrl.h>

/////////////////////////////////////////
class GTextEvent: public wxCommandEvent 
{ 
	public: 
		GTextEvent(wxEventType commandType = wxEVT_NULL, int id = 0 ); 

		virtual wxEvent *Clone() const { return new GTextEvent(*this); } 

	private: 
	DECLARE_DYNAMIC_CLASS(GTextEvent) 
}; 

BEGIN_DECLARE_EVENT_TYPES() 
	DECLARE_EVENT_TYPE(wxEVT_COMMAND_GTEXT, -1) 
END_DECLARE_EVENT_TYPES() 

typedef void (wxEvtHandler::*wxGTextEventFunction)(GTextEvent&); 

#define EVT_GTEXT(id, fn) \
	DECLARE_EVENT_TABLE_ENTRY(wxEVT_COMMAND_GTEXT, id, -1,  \
	(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)  \
	wxStaticCastEvent(wxGTextEventFunction, & fn), (wxObject *) NULL ),


/////////////////////////////////
class TextEdit: public wxTextCtrl
{ 
	
public: 
	TextEdit(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size,
			 long style, wxString& name); 
	~TextEdit(); 
	bool Create(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, 
					long style,	const wxString& name); 
private: 
	void Init();
	void OnChange(wxCommandEvent &event);
	bool enableEvents;

	wxString text;
		
	DECLARE_EVENT_TABLE() 
};

#endif //GTEXT_H
