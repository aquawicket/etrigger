//// GToggle.cpp ///////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////

#include "GToggle.h"

DEFINE_EVENT_TYPE(wxEVT_COMMAND_GTOGGLE) 

IMPLEMENT_DYNAMIC_CLASS(GToggleEvent, wxCommandEvent)  // RTTI

///////////////////////////////////////////////////////////
GToggleEvent::GToggleEvent(wxEventType commandType, int id) 
		: wxCommandEvent(commandType, id) 
{ 
} 

////////////////////////////////////
BEGIN_EVENT_TABLE(GToggle, wxPanel) 
	EVT_PAINT  (GToggle::OnPaint) 
	EVT_MOUSE_EVENTS (GToggle::OnMouse) 
	EVT_ERASE_BACKGROUND(GToggle::OnEraseBackground) 
END_EVENT_TABLE() 

//////////////////
GToggle::GToggle() 
{ 
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
} 

///////////////////
GToggle::~GToggle() 
{ 
} 

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
GToggle::GToggle(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxImage& on, const wxImage& off) 
{ 
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	(void)Create(parent, id, pos, on, off); 
} 

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
GToggle::GToggle(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxString& on, const wxString& off)
{
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	(void)Create(parent, id, pos, on, off); 
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
GToggle::GToggle(wxWindow* parent, wxWindowID id, const wxPoint& pos, const char** on, const char** off)
{
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	(void)Create(parent, id, pos, on, off); 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool GToggle::Create(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxImage& on, const wxImage& off) 
{ 
	c_on = on;
	c_off = off;
  
	if(!wxPanel::Create(parent, id, pos, wxSize(on.GetWidth(), on.GetHeight()), 0, wxT(""))) 
		return false; 

	return true; 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool GToggle::Create(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxString& on, const wxString& off) 
{ 
	const wxImage &temp = wxImage(on, wxBITMAP_TYPE_ANY);
	const wxImage &temp2 = wxImage(off, wxBITMAP_TYPE_ANY);
	c_on = temp;
	c_off = temp2;
  
	if(!wxPanel::Create(parent, id, pos, wxSize(temp.GetWidth(), temp.GetHeight()), 0, wxT(""))) 
		return false; 

	return true; 
} 

////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool GToggle::Create(wxWindow* parent, wxWindowID id, const wxPoint& pos, const char** on, const char** off) 
{ 
	const wxImage &temp = on;//wxImage(on);
	const wxImage &temp2 = off;//wxImage(off);
	c_on = temp;
	c_off = temp2;
  
	if(!wxPanel::Create(parent, id, pos, wxSize(temp.GetWidth(), temp.GetHeight()), 0, wxT(""))) 
		return false; 

	return true; 
} 

////////////////////////////////////////////////////
void GToggle::OnPaint(wxPaintEvent &WXUNUSED(event)) 
{ 
#ifndef MAC
	SetDoubleBuffered(false);
#endif //!MAC
	wxBufferedPaintDC dc(this); 
	DrawBackground(dc); 
} 

void GToggle::OnEraseBackground(wxEraseEvent& event)
{
	
}

//////////////////////////////////////////
void GToggle::OnMouse(wxMouseEvent &event) 
{ 
	if(event.LeftDown()) 
	{  
		//click is on
		if(!on){on = true;}
		else{on = false;}
		Refresh();

		// Create and event 
		GToggleEvent event(wxEVT_COMMAND_GTOGGLE, GetId()); 
		event.SetEventObject(this); 

		// Send it 
		GetEventHandler()->ProcessEvent(event); 
	} 

	if(event.LeftUp())
	{
		//click is off
	}

	if(event.Leaving())
	{
		//hover and click are off
	}

	if(event.RightUp())
	{
		//Alter this to give the object it's own right click properties
		//FIXME
		//GetParent()->ProcessEvent(event); //Let right clicks bleed through to the parent.
	}
} 

//////////////////////////////////////
void GToggle::DrawBackground(wxDC &dc) 
{ 
	if(on){dc.DrawBitmap( c_on, 0, 0);}
	else{dc.DrawBitmap( c_off, 0, 0);}
}
