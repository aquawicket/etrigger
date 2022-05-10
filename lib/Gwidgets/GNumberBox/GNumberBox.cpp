//// GNumberBox.cpp ///////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////

#include "GNumberBox.h"

DEFINE_EVENT_TYPE(wxEVT_COMMAND_GNUMBERBOX) 

IMPLEMENT_DYNAMIC_CLASS(GNumberBoxEvent, wxCommandEvent)  // RTTI

///////////////////////////////////////////////////////////
GNumberBoxEvent::GNumberBoxEvent(wxEventType commandType, int id) 
		: wxCommandEvent(commandType, id) 
{ 
} 

////////////////////////////////////
BEGIN_EVENT_TABLE(GNumberBox, wxTextCtrl) 
	EVT_MOUSE_EVENTS (GNumberBox::OnMouse)
	EVT_TEXT(-1, GNumberBox::OnTextChange) 
	#ifdef WIN32
	//EVT_MOUSE_CAPTURE_LOST(GNumberBox::OnMouseCaptureLost)
	#endif
	EVT_KEY_DOWN(GNumberBox::OnKeyDown)
END_EVENT_TABLE() 


//////////////////
GNumberBox::GNumberBox(wxWindow *parent, wxWindowID id, const wxString& value, const wxPoint& pos, const wxSize& size)
         :wxTextCtrl(parent, id, value, pos, size, wxNO_BORDER | wxTE_CENTRE, wxTextValidator(wxFILTER_NUMERIC), wxT(""))
{ 
#ifndef MAC
	SetBackgroundColour(wxColour(30,30,30)); //FIXME - does not work on MAC	
	SetForegroundColour(wxColour(255,255,255)); 
#endif //!MAC
	minValue = 0;
	maxValue = 100;
} 

///////////////////
GNumberBox::~GNumberBox() 
{ 
} 

void GNumberBox::OnTextChange(wxCommandEvent &event)
{
	int value;
	GetValue().ToLong((long *) &value);
#ifndef MAC
	if(value < minValue){value = minValue; ChangeValue(wxString::Format(wxT("%d"), value));}
	if(value > maxValue){value = maxValue; ChangeValue(wxString::Format(wxT("%d"), value));}
#endif
#ifdef MAC
	if(value < minValue){value = minValue; SetValue(wxString::Format(wxT("%d"), value));}
	if(value > maxValue){value = maxValue; SetValue(wxString::Format(wxT("%d"), value));}
#endif

	storedValue = value;

	// Create an event 
	GNumberBoxEvent event2(wxEVT_COMMAND_GNUMBERBOX, GetId()); 
	event2.SetEventObject(this); 

	// Send it 
	GetEventHandler()->ProcessEvent(event2); 
}

void GNumberBox::SetMinMax(int min, int max)
{
	minValue = min;
	maxValue = max;

    #ifndef MAC
	SetMaxLength(wxString::Format(wxT("%d"), maxValue).Length());
	#endif
}

void GNumberBox::SetDefault(int value)
{
	defaultValue = value;
}

void GNumberBox::Set(int value)
{
	if(value < minValue){value = minValue;}
	if(value > maxValue){value = maxValue;}
#ifndef MAC
	ChangeValue(wxString::Format(wxT("%d"),value));
#endif
#ifdef MAC
	SetValue(wxString::Format(wxT("%d"),value));
#endif
	
	storedValue = value;
}

#ifndef LINUX
///////////////////////////////
bool GNumberBox::UseMouseCapture()
{ 
	if(GetWindowStyle() & FDR_NO_MOUSE_CAPTURE)
		return false;
	else{
		return true;
	}
}
#endif

////////////////////////////////////////////////////////////////
#ifdef WIN32
void GNumberBox::OnMouseCaptureLost(wxMouseCaptureLostEvent &event)
{
	event.Skip(true);
}
#endif


//////////////////////////////////////////
void GNumberBox::OnMouse(wxMouseEvent &event)
{ 
	if(event.GetWheelRotation() > 0){
		Set(storedValue + 1);
		SetSelection(0,GetLineLength(0)); 

		// Create an event 
		GNumberBoxEvent event2(wxEVT_COMMAND_GNUMBERBOX, GetId()); 
		event2.SetEventObject(this); 

		// Send it 
		GetEventHandler()->ProcessEvent(event2); 
	}

	if(event.GetWheelRotation() < 0){
		Set(storedValue - 1); 
		SetSelection(0,GetLineLength(0)); 

		// Create an event 
		GNumberBoxEvent event2(wxEVT_COMMAND_GNUMBERBOX, GetId()); 
		event2.SetEventObject(this); 

		// Send it 
		GetEventHandler()->ProcessEvent(event2); 
	}

	if(event.LeftDown()){ 
		SetFocus();
		GetValue().ToLong((long *) &storedValue);
		mousePoint = event.GetPosition(); 
		dragging = true;
		#ifndef LINUX
		if(UseMouseCapture()) {CaptureMouse();}
		#endif
		SetSelection(0,GetLineLength(0)); 
	}

	if(event.LeftDClick()){
		Set(defaultValue);
		SetSelection(0,GetLineLength(0));

		// Create an event 
		GNumberBoxEvent event2(wxEVT_COMMAND_GNUMBERBOX, GetId()); 
		event2.SetEventObject(this); 

		// Send it 
		GetEventHandler()->ProcessEvent(event2); 
	}

	// Left button changed to up 
	if(event.LeftUp()/* || (event.Leaving() && !UseMouseCapture())*/) 
	{ 
		dragging = false;
		if(HasCapture()) 
			ReleaseMouse(); 

		return; 
	} 

	// Dragging movement ? 
	if(event.Dragging() && dragging){
			wxPoint tempPoint = event.GetPosition();
			Set(storedValue - tempPoint.y + mousePoint.y);
			SetSelection(0,GetLineLength(0)); 
			mousePoint = event.GetPosition();
	}
		else 
			return; 

	// Send event 
	if(dragging) 
	{ 
		// Create an event 
		GNumberBoxEvent event(wxEVT_COMMAND_GNUMBERBOX, GetId()); 
		event.SetEventObject(this); 

		// Send it 
		GetEventHandler()->ProcessEvent(event); 
	}

} 

//////////////////////////////////////////////
void GNumberBox::OnKeyDown(wxKeyEvent &event)
{
	if(event.GetKeyCode() == WXK_UP || event.GetKeyCode() == WXK_NUMPAD_UP){
		Set(storedValue + 1);
		SetSelection(0,GetLineLength(0)); 

		// Create an event 
		GNumberBoxEvent event2(wxEVT_COMMAND_GNUMBERBOX, GetId()); 
		event2.SetEventObject(this); 

		// Send it 
		GetEventHandler()->ProcessEvent(event2); 
	}

	if(event.GetKeyCode() == WXK_DOWN || event.GetKeyCode() == WXK_NUMPAD_DOWN){
		Set(storedValue - 1); 
		SetSelection(0,GetLineLength(0)); 

		// Create an event 
		GNumberBoxEvent event2(wxEVT_COMMAND_GNUMBERBOX, GetId()); 
		event2.SetEventObject(this); 

		// Send it 
		GetEventHandler()->ProcessEvent(event2); 
	}

	event.Skip(true);
}
