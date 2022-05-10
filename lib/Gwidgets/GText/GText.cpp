//// GText.cpp /////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////

#include "GText.h"

DEFINE_EVENT_TYPE(wxEVT_COMMAND_GTEXT) 

IMPLEMENT_DYNAMIC_CLASS(GTextEvent, wxCommandEvent)  // RTTI

///////////////////////////////////////////////////////////
GTextEvent::GTextEvent(wxEventType commandType, int id) 
		: wxCommandEvent(commandType, id) 
{ 
} 


///////////////////////////////////////
BEGIN_EVENT_TABLE(TextEdit, wxTextCtrl)
	EVT_TEXT(-1, TextEdit::OnChange) 
END_EVENT_TABLE() 

///////////////////////////////////////////////////////////////////////////////////////////////////////
TextEdit::TextEdit(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, wxString& name)
{
	enableEvents = false; //don't allow events just yet
	text = name;
	Init();
	(void)Create(parent, id, pos, size, style, name); 
}

/////////////////////
TextEdit::~TextEdit() 
{ 
}

/////////////////////
void TextEdit::Init() 
{ 
    #ifdef __WXMAC__  //Fix to allow Mac to change background color
	//wxSystemOptions::SetOption(wxMAC_TEXTCONTROL_USE_MLTE, 1);
    #endif
} 

//////////////////////////////////////////////////////////////////////////////////////////////
bool TextEdit::Create(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, 
					  long style, const wxString& name) 
{ 
	if(!wxTextCtrl::Create(parent, id, name, pos, size, style, wxDefaultValidator, wxT("")))
		return false; 

	SetBackgroundColour( wxColor(25,25,25)); 
	SetForegroundColour( wxColor(200,200,200)); //FIXME - does not work on mac.
	Refresh();

	enableEvents = true;
	return true;  
} 

//////////////////////////////////////////////
void TextEdit::OnChange(wxCommandEvent &event)
{ 
	/*
	if(enableEvents){  //Wait for wxTextCtrl::Create or value will get NULL'ed
		wxString temp = GetValue();
		text = temp;
	}
	*/

	if(enableEvents){
		// Create event 
		GTextEvent event2(wxEVT_COMMAND_GTEXT, GetId()); 
		event2.SetEventObject(this); 

		// Send it 
		GetEventHandler()->ProcessEvent(event2); 
	}
}
