//// GKnob.cpp ///////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////

#include "GKnob.h" 

DEFINE_EVENT_TYPE(wxEVT_COMMAND_GKNOB) 

IMPLEMENT_DYNAMIC_CLASS(GKnobEvent, wxCommandEvent) 

/////////////////////////////////////////////////////////////////////////////////////////
GKnobEvent::GKnobEvent(wxEventType commandType, int id) : wxCommandEvent(commandType, id) 
{ 
} 

/////////////////////////////////
BEGIN_EVENT_TABLE(GKnob, wxPanel) 
	EVT_PAINT  (GKnob::OnPaint) 
	EVT_ERASE_BACKGROUND (GKnob::OnEraseBackground) 
	EVT_MOUSE_EVENTS (GKnob::OnMouse) 
	EVT_KEY_DOWN(GKnob::OnKeyDown)
END_EVENT_TABLE() 

//////////////
GKnob::GKnob() 
{ 
	Init(); 
} 

///////////////
GKnob::~GKnob() 
{ 
} 

///////////////////////////////////////////////////////////////////////////////////////////////////
GKnob::GKnob(wxWindow* parent, wxWindowID id, const wxPoint& pos, long style, const wxString& name, 
		     const wxImage& back, const wxImage& knob) 
{ 
	Init();
	(void)Create(parent, id, pos, style, name, back, knob); 
} 

///////////////////////////////////////////////////////////////////////////////////////////////////
GKnob::GKnob(wxWindow* parent, wxWindowID id, const wxPoint& pos, long style, const wxString& name, 
		     const wxString& back, const wxString& knob) 
{ 
	Init();
	(void)Create(parent, id, pos, style, name, back, knob); 
}

///////////////////////////////////////////////////////////////////////////////////////////////////
GKnob::GKnob(wxWindow* parent, wxWindowID id, const wxPoint& pos, long style, const wxString& name, 
		     const char** back, const char** knob) 
{ 
	Init();
	(void)Create(parent, id, pos, style, name, back, knob); 
} 

//////////////////
void GKnob::Init() 
{ 
	// Mouse logic 
	m_mouseOffsetY   = 0; 
	storedValue = 141;
	m_draggingKnob  = false; 
	m_wheelKnobMove = false;
	#ifndef LINUX
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	#endif //LINUX
} 

/////////////////////////////////////////////////////////////////////////////////////////////////////////
bool GKnob::Create(wxWindow* parent, wxWindowID id, const wxPoint& pos, long style, const wxString& name, 
		const wxImage& back, const wxImage& knob) 
{ 
	c_back = back;
	c_knob = knob;

	//Back size
	m_BackWidth = c_back.GetWidth();
	m_BackHeight = c_back.GetHeight();

	// Knob size 
	m_knobWidth  = c_knob.GetWidth();
	m_knobHeight = c_knob.GetHeight();
	m_knobPosX = (m_BackWidth / 2) - (m_knobWidth / 2);
	m_knobPosY = (m_BackHeight / 2) - (m_knobHeight / 2);
  
	if(!wxPanel::Create(parent, id, pos, wxSize(back.GetWidth(), back.GetHeight()), style, name)) 
		return false; 

	#ifndef LINUX
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	#endif //LINUX

	return true; 
} 

/////////////////////////////////////////////////////////////////////////////////////////////////////////
bool GKnob::Create(wxWindow* parent, wxWindowID id, const wxPoint& pos, long style, const wxString& name, 
		const wxString& back, const wxString& knob) 
{ 
	const wxImage &temp = wxImage(back, wxBITMAP_TYPE_ANY);
	const wxImage &temp2 = wxImage(knob, wxBITMAP_TYPE_ANY);

	c_back = temp;
	c_knob = temp2;

	//Back size
	m_BackWidth = c_back.GetWidth();
	m_BackHeight = c_back.GetHeight();

	// Knob size 
	m_knobWidth  = c_knob.GetWidth();
	m_knobHeight = c_knob.GetHeight();
	m_knobPosX = (m_BackWidth / 2) - (m_knobWidth / 2);
	m_knobPosY = (m_BackHeight / 2) - (m_knobHeight / 2);
  
	if(!wxPanel::Create(parent, id, pos, wxSize(temp.GetWidth(), temp.GetHeight()), style, name)) 
		return false; 

	#ifndef LINUX
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	#endif //LINUX

	return true; 
} 

/////////////////////////////////////////////////////////////////////////////////////////////////////////
bool GKnob::Create(wxWindow* parent, wxWindowID id, const wxPoint& pos, long style, const wxString& name, 
		const char** back, const char** knob) 
{ 
	const wxImage &temp = back; //wxImage(back);
	const wxImage &temp2 = knob; //wxImage(knob);

	c_back = temp;
	c_knob = temp2;

	//Back size
	m_BackWidth = c_back.GetWidth();
	m_BackHeight = c_back.GetHeight();

	// Knob size 
	m_knobWidth  = c_knob.GetWidth();
	m_knobHeight = c_knob.GetHeight();
	m_knobPosX = (m_BackWidth / 2) - (m_knobWidth / 2);
	m_knobPosY = (m_BackHeight / 2) - (m_knobHeight / 2);
  
	if(!wxPanel::Create(parent, id, pos, wxSize(temp.GetWidth(), temp.GetHeight()), style, name)) 
		return false; 

	#ifndef LINUX
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	#endif //LINUX

	return true; 
} 


//////////////////////////////////////////////
float GKnob::NormalizeValue(float value) const 
{ 
	if(value < m_minValue) 
		return m_minValue; 
	else if (value > m_maxValue) 
		return m_maxValue; 
	else 
		return value; 
} 

/////////////////////////////
float GKnob::GetValue() const 
{ 
	return m_currentValue; 
} 

/////////////////////////////////
void GKnob::SetValue(float value) 
{ 
	value = NormalizeValue(value); 

	if(m_currentValue == value) 
		return; 

	m_currentValue = value;

	Refresh(); 
}

///////////////////////////////
void GKnob::ResetStoredValue()
{
	storedValue = (212 - ((((m_currentValue * 100) / m_maxValue) * 141) / 100));
}

///////////////////////////
float GKnob::GetMin() const 
{ 
	return m_minValue; 
} 

///////////////////////////
float GKnob::GetMax() const 
{ 
	return m_maxValue; 
} 

////////////////////////////////////////////////////
void GKnob::SetRange(float minValue, float maxValue) 
{ 
	if(minValue > maxValue) 
	{ 
		// swap them, we always want min to be less than max 
		float tmp = minValue; 
		minValue = maxValue; 
		maxValue = tmp; 
	} 

	if( m_minValue != minValue || m_maxValue != maxValue) 
	{ 
		m_minValue = minValue; 
		m_maxValue = maxValue; 

		// reset the value to make sure it is in the new range 
		SetValue(m_currentValue); 

		Refresh(); 
	} 
	//else: nothing changed 
} 


/////////////////////////////
bool GKnob::UseMouseCapture() 
{ 
	if(GetWindowStyle() & FDR_NO_MOUSE_CAPTURE) 
		return false; 
	else{
		return true; 
	} 
} 

//////////////////////////////////////////////////
void GKnob::OnEraseBackground(wxEraseEvent &event) 
{ 
} 

//////////////////////////////////////////////////
void GKnob::OnPaint(wxPaintEvent &WXUNUSED(event)) 
{
#ifndef MAC
	SetDoubleBuffered(false);
#endif //!MAC
	
    wxBufferedPaintDC dc(this); 
	DrawBackground(dc); 
	DrawKnob(dc); 
} 


////////////////////////////////////////
void GKnob::OnMouse(wxMouseEvent &event) 
{ 
	wxClientDC dc(this); 
	PrepareDC(dc); 

	wxPoint pos = event.GetPosition(); 
	long x = dc.DeviceToLogicalX(pos.x); 
	long y = dc.DeviceToLogicalY(pos.y); 

	// Left button changed to down inside the fader knob 
	//   we may start dragging... 
	if(x >= m_knobPosX && x <= m_knobPosX + m_knobWidth 
		&& y >= m_knobPosY && y <= m_knobPosY + m_knobHeight)
	{
		if(event.LeftDown()){ 
			// Calculate the vertical offset between mouse pointer and knob center 
			SetFocus();
			m_mouseOffsetY = y;

			m_draggingKnob  = true; 
			m_wheelKnobMove = false; 

			if(UseMouseCapture()) 
				CaptureMouse();
		}
	}

	if(event.GetWheelRotation() > 0){
		SetValue(m_currentValue + 1);
		// Create and event 
		GKnobEvent event(wxEVT_COMMAND_GKNOB, GetId()); 
		event.SetEventObject(this); 

		// Give it some contents 
		event.SetValue(m_currentValue); 

		// Send it 
		GetEventHandler()->ProcessEvent(event); 
	}

	if(event.GetWheelRotation() < 0){
		SetValue(m_currentValue - 1);
		// Create and event 
		GKnobEvent event(wxEVT_COMMAND_GKNOB, GetId()); 
		event.SetEventObject(this); 

		// Give it some contents 
		event.SetValue(m_currentValue); 

		// Send it 
		GetEventHandler()->ProcessEvent(event); 
	}

	if(event.LeftDClick()){
		SetValue(m_maxValue / 2);
		// Create and event 
		GKnobEvent event(wxEVT_COMMAND_GKNOB, GetId()); 
		event.SetEventObject(this); 

		// Give it some contents 
		event.SetValue(m_currentValue); 

		// Send it 
		GetEventHandler()->ProcessEvent(event); 
	}

	// Left button changed to up 
	if(event.LeftUp() ||(event.Leaving() && !UseMouseCapture())) 
	{ 
		m_draggingKnob  = false; 
		m_wheelKnobMove = false; 
		m_mouseOffsetY   = 0;
		storedValue = (212 - ((((m_currentValue * 100) / m_maxValue) * 141) / 100));

		if(HasCapture()){ 
			ReleaseMouse(); 
		}
			return; 
	}

	// Dragging movement ? 
	if(m_draggingKnob){
		if(event.Dragging()) {
			SetValue(ValueFromVertPosition((storedValue -(m_mouseOffsetY - y))));  // (int)Should we limit the precision here ??? 
		}
		else{
			return; 
		}
	}

	// Send event 
	if(m_draggingKnob){
		// Create and event 
		GKnobEvent event(wxEVT_COMMAND_GKNOB, GetId()); 
		event.SetEventObject(this); 

		// Give it some contents 
		event.SetValue(m_currentValue); 

		// Send it 
		GetEventHandler()->ProcessEvent(event); 
	} 

	if(event.RightUp()){
		//Alter this to give the object it's own right click properties
		//FIXME
		//GetParent()->ProcessEvent(event); //Let right clicks bleed through to the parent.
	}
	
}

////////////////////////////////////////
void GKnob::OnKeyDown(wxKeyEvent &event)
{
	if(event.GetKeyCode() == WXK_UP || event.GetKeyCode() == WXK_NUMPAD_UP ||
	   event.GetKeyCode() == WXK_RIGHT || event.GetKeyCode() == WXK_NUMPAD_RIGHT){
			SetValue(m_currentValue + 1);
			// Create and event 
			GKnobEvent event2(wxEVT_COMMAND_GKNOB, GetId()); 
			event2.SetEventObject(this); 

			// Give it some contents 
			event2.SetValue(m_currentValue); 

			// Send it 
			GetEventHandler()->ProcessEvent(event2); 
	}

	if(event.GetKeyCode() == WXK_DOWN || event.GetKeyCode() == WXK_NUMPAD_DOWN ||
		event.GetKeyCode() == WXK_LEFT || event.GetKeyCode() == WXK_NUMPAD_LEFT){
			SetValue(m_currentValue - 1);
			// Create and event 
			GKnobEvent event2(wxEVT_COMMAND_GKNOB, GetId()); 
			event2.SetEventObject(this); 

			// Give it some contents 
			event2.SetValue(m_currentValue); 

			// Send it 
			GetEventHandler()->ProcessEvent(event2); 
	}
}

////////////////////////////////////////////////////
float GKnob::ValueFromVertPosition(wxCoord position) 
{ 
	if(position < 71){position = 71;}
	if(position > 212) {position = 212;}
	position = 212 - position;
	position = (position * 100) / 141; //now gainValue is the percent
	position = (position * m_maxValue) / 100; //now gain value equals between 0 and maxValue;

	return position;
} 


//////////////////////////
void GKnob::CalcGeometry() 
{ 
	int totalWidth  = 0, 
	totalHeight = 0; 

	// Total control size 
	GetClientSize(&totalWidth, &totalHeight); 
	// Calculate track width and position 
	m_BackHeight = totalHeight - m_knobHeight - 4; 
	m_BackPosX = (int)((totalWidth / 2 - m_BackWidth / 2 /*+ HorzOffset*/)); 
	m_BackPosY = (int)((totalHeight - m_BackHeight) / 2) ; 

} 

//////////////////////////////////////////////
wxString GKnob::FormatValue(float value) const 
{ 
	return wxString::Format(wxT("%d"), (int)value); 
} 

////////////////////////////////////
void GKnob::DrawBackground(wxDC &dc) 
{ 
	dc.DrawBitmap( c_back, 0, 0);
} 

//////////////////////////////
void GKnob::DrawKnob(wxDC &dc) 
{ 
	wxPoint offset;
	wxImage temp = c_knob;
	temp.SetMask(true);
	temp.SetMaskColour(255,0,254);

	wxImage temp2 = temp.Rotate( ((212 - ((((m_currentValue * 100) / m_maxValue) * 141) / 100)) / 30), wxPoint(temp.GetWidth() / 2, temp.GetHeight() / 2), false, &offset);
	dc.DrawBitmap( temp2, offset.x + 12, offset.y + 18, true);	
} 
