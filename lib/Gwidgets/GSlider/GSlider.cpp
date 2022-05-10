//// GSlider.cpp ///////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////

#include "GSlider.h" 

DEFINE_EVENT_TYPE(wxEVT_COMMAND_GSLIDER) 

IMPLEMENT_DYNAMIC_CLASS(GSliderEvent, wxCommandEvent) 

///////////////////////////////////////////////////////////
GSliderEvent::GSliderEvent(wxEventType commandType, int id) 
		     : wxCommandEvent(commandType, id) 
{ 
} 

///////////////////////////////////
BEGIN_EVENT_TABLE(GSlider, wxPanel) 
	EVT_SIZE   (GSlider::OnSize) 
	EVT_PAINT  (GSlider::OnPaint) 
	EVT_ERASE_BACKGROUND (GSlider::OnEraseBackground) 
	EVT_KILL_FOCUS(GSlider::OnKillFocus) 
	EVT_MOUSE_EVENTS (GSlider::OnMouse) 
	EVT_KEY_DOWN(GSlider::OnKeyDown)
END_EVENT_TABLE() 

////////////////// 
GSlider::GSlider() 
{ 
	Init(); 
} 

///////////////////////////////////////////////////////////////////////////////////////////////////////
GSlider::GSlider(wxWindow* parent, wxWindowID id, const wxPoint& pos, long style, const wxString& name, 
		         const wxImage& back, const wxImage& backFocused, const wxImage& slider
		  ,const wxImage& hover, const wxImage& click, const wxImage& focused) 
{ 
	Init();

	(void)Create(parent, id, pos, style, name, back, backFocused, slider, hover, click, focused); 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
GSlider::GSlider(wxWindow* parent, wxWindowID id, const wxPoint& pos, long style, const wxString& name, 
		         const wxString& back, const wxString& backFocused, const wxString& slider
		  ,const wxString& hover, const wxString& click, const wxString& focused) 
{ 
	Init();

	(void)Create(parent, id, pos, style, name, back, backFocused, slider, hover, click, focused); 
} 

///////////////////////////////////////////////////////////////////////////////////////////////////////
GSlider::GSlider(wxWindow* parent, wxWindowID id, const wxPoint& pos, long style, const wxString& name, 
		         const char** back, const char** backFocused, const char** slider, const char** hover, 
				 const char** click, const char** focused)
{ 
	Init();

	(void)Create(parent, id, pos, style, name, back, backFocused, slider, hover, click, focused); 
} 

///////////////////
GSlider::~GSlider() 
{ 
} 

////////////////////
void GSlider::Init() 
{ 
	// Mouse logic 
	//m_mouseOffsetY   = 0; 
	m_draggingFader  = false; 
	activeKnob = 0;

	hover = false;
	click = false;
	backFocused = false;
	knobFocused = false;

#ifndef LINUX
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
#endif //LINUX
} 

///////////////////////////////////////////////////////////////////////////////////////////////////////////
bool GSlider::Create(wxWindow* parent, wxWindowID id, const wxPoint& pos, long style, const wxString& name, 
		             const wxImage& back, const wxImage& backFocused, const wxImage& slider, const wxImage& hover, 
		             const wxImage& click, const wxImage& focused) 
{ 
	/// Multiple Knobs ////////
	knobs.resize(1);
	knobs[0].slider = slider;
	knobs[0].focused = focused;
	knobs[0].knobWidth = knobs[0].slider.GetWidth();
	knobs[0].knobHeight = knobs[0].slider.GetHeight();
	knobs[0].hover = false;
	knobs[0].click = false;
	knobs[0].knobFocused = false;
	knobCount = 1;
	///////////////////////////

	c_back = back;
	c_backFocused = backFocused;
  
	if(!wxPanel::Create(parent, id, pos, wxSize(back.GetWidth(), back.GetHeight()), style, name)) 
		return false; 

#ifndef LINUX
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
#endif //LINUX

	return true; 
} 

///////////////////////////////////////////////////////////////////////////////////////////////////////////
bool GSlider::Create(wxWindow* parent, wxWindowID id, const wxPoint& pos, long style, const wxString& name, 
		             const wxString& back, const wxString& backFocused, const wxString& slider, const wxString& hover, 
		             const wxString& click, const wxString& focused) 
{ 
	const wxImage &temp = wxImage(back, wxBITMAP_TYPE_ANY);
	const wxImage &temp2 = wxImage(backFocused, wxBITMAP_TYPE_ANY);
	const wxImage &temp3 = wxImage(slider, wxBITMAP_TYPE_ANY);
	const wxImage &temp4 = wxImage(hover, wxBITMAP_TYPE_ANY);
	const wxImage &temp5 = wxImage(click, wxBITMAP_TYPE_ANY);
	const wxImage &temp6 = wxImage(focused, wxBITMAP_TYPE_ANY);

	/// Multiple Knobs ////////
	knobs.resize(1);
	knobs[0].slider = temp3;
	knobs[0].focused = temp6;
	knobs[0].knobWidth = knobs[0].slider.GetWidth();
	knobs[0].knobHeight = knobs[0].slider.GetHeight();
	knobs[0].hover = false;
	knobs[0].click = false;
	knobs[0].knobFocused = false;
	knobCount = 1;
	////////////////////////////

	c_back = temp;
	c_backFocused = temp2;

	if(!wxPanel::Create(parent, id, pos, wxSize(temp.GetWidth(), temp.GetHeight()), style, name)) 
		return false; 

#ifndef LINUX
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
#endif //LINUX

	return true; 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
bool GSlider::Create(wxWindow* parent, wxWindowID id, const wxPoint& pos, long style, const wxString& name, 
		             const char** back, const char** backFocused, const char** slider, const char** hover, 
		             const char** click, const char** focused) 
{ 
	const wxImage &temp = back;//wxImage(back);
	const wxImage &temp2 = backFocused;//wxImage(backFocused);
	const wxImage &temp3 = slider;//wxImage(slider);
	const wxImage &temp4 = hover;//wxImage(hover);
	const wxImage &temp5 = click;//wxImage(click);
	const wxImage &temp6 = focused;//wxImage(focused);

	/// Multiple Knobs ////////
	knobs.resize(1);
	knobs[0].slider = temp3;
	knobs[0].focused = temp6;
	knobs[0].knobWidth = knobs[0].slider.GetWidth();
	knobs[0].knobHeight = knobs[0].slider.GetHeight();
	knobs[0].hover = false;
	knobs[0].click = false;
	knobs[0].knobFocused = false;
	knobCount = 1;
	///////////////////////////


	c_back = temp;
	c_backFocused = temp2;
  
	if(!wxPanel::Create(parent, id, pos, wxSize(temp.GetWidth(), temp.GetHeight()), style, name)) 
		return false; 

#ifndef LINUX
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
#endif //LINUX

	return true; 
}

//////////////////////////////////////////
float GSlider::NormalizeValue(float value) const 
{ 
	// normalize the value to fit in the range 
	if(value < m_minValue) 
		return m_minValue; 
	else if (value > m_maxValue) 
		return m_maxValue; 
	else 
		return value; 
} 

///////////////////////
float GSlider::GetMin() const 
{ 
	return m_minValue; 
} 

///////////////////////
float GSlider::GetMax() const 
{ 
	return m_maxValue; 
} 

//////////////////////////////////////////////////////
void GSlider::SetRange(float minValue, float maxValue) 
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

		// reset the values to make sure their in the new range 
		//////Multiple konbs///////////
		for(unsigned int i=0; i<knobs.size(); ++i){
			SetValue(i, knobs[i].currentValue);
		}
		//////////////////////////////

		Refresh(); 
	} 
	//else: nothing changed 
} 

///////////////////////////////
bool GSlider::UseMouseCapture() 
{ 
	if(GetWindowStyle() & FDR_NO_MOUSE_CAPTURE) 
		return false; 
	else{
		return true; 
	} 
} 

////////////////////////////////////////
void GSlider::OnSize(wxSizeEvent &event) 
{ 
	for(unsigned int i=0; i<knobs.size(); ++i){
		CalcGeometry(i); 
	}
	Refresh();   // For any mysterious reason... 
	event.Skip(); 
}  

////////////////////////////////////////////////////
void GSlider::OnEraseBackground(wxEraseEvent &event) 
{ 
} 

////////////////////////////////////////////////////
void GSlider::OnPaint(wxPaintEvent &WXUNUSED(event)) 
{ 
#ifndef MAC
	SetDoubleBuffered(false);
#endif //!MAC
    //wxBufferedPaintDC dc(this); 
	//PrepareDC(dc); 
	wxPaintDC dc(this);

	DrawBackground(dc); 
	DrawFaders(dc); 
} 

//////////////////////////////////////////////
void GSlider::OnKillFocus(wxFocusEvent &event)
{
	//////// Multiple Knobs ///////////
	for(unsigned int i=0; i<knobs.size(); ++i){
		if(knobs[i].knobFocused == true){
			knobs[i].knobFocused = false;
			Refresh();
		}
	}
}

/////////////////////////////////////////////////
wxCoord GSlider::ValueToVertPosition(float value) 
{ 
	value = NormalizeValue(value); 

	float ratio = (value - m_minValue) / (m_maxValue - m_minValue); 
	return (wxCoord)(m_trackPosY + (m_trackHeight - 1) - ratio * (m_trackHeight - 1)); 
} 

//////////////////////////////////////////////////////
float GSlider::ValueFromVertPosition(wxCoord position) 
{ 
	float ratio = (float)(m_trackPosY + m_trackHeight -1 - position) / (float)(m_trackHeight - 1); 
	return (float)(ratio * (m_maxValue - m_minValue) + m_minValue); 
} 

////////////////////////////////////////////////
wxString GSlider::FormatValue(float value) const 
{ 
	return wxString::Format(wxT("%d"), (int)value); 
} 

//////////////////////////////////////
void GSlider::DrawBackground(wxDC &dc) 
{ 
	if(!backFocused){
		dc.DrawBitmap( c_back, 0, 0, true);
	}
	if(backFocused){
		dc.DrawBitmap( c_backFocused, 0, 0, true);
	}
} 

///////////////////////////////// 
void GSlider::DrawFaders(wxDC &dc) 
{ 
	/*
	if(hover == true){
		dc.DrawBitmap( c_hover, m_knobPosX, m_knobPosY);
	}
    if(click == true){
			dc.DrawBitmap( c_click, m_knobPosX, m_knobPosY);
    }
	if(click == false && hover == false){
		dc.DrawBitmap( c_slider, m_knobPosX, m_knobPosY);
	}
	*/

	//////////// MULTIPLE KNOBS ///////////////
	for(unsigned int i=0; i<knobs.size(); ++i){
		if(knobs[i].knobFocused == true){
			dc.DrawBitmap( knobs[i].focused, knobs[i].knobPosX, knobs[i].knobPosY);
		}
		else{
			dc.DrawBitmap( knobs[i].slider, knobs[i].knobPosX, knobs[i].knobPosY);
		}
	}
	////////////////////////////////////////////
}

//////////////////////////////////////
float GSlider::GetValue(int num) const
{
	return knobs[num].currentValue;
}

////////////////////////////////////////////
void GSlider::SetValue(int num, float value)
{
	value = NormalizeValue(value); 

	if(knobs[num].currentValue == value) 
		return; 

	knobs[num].currentValue = value; 

	CalcGeometry(num); 
	Refresh(); 

}

//////////////////////////////////////////////
void GSlider::SetDefault(int num, float value)
{
	knobs[num].defaultValue = value;
}

///////////////////////////////////
void GSlider::CalcGeometry(int num) 
{ 
	// calculate size and position of everything 
	int totalWidth  = 0; 
	int totalHeight = 0; 

	// Total control size 
	GetClientSize(&totalWidth, &totalHeight); 

	// Calculate track width and position 
	m_trackHeight = totalHeight - knobs[num].knobHeight - 4; 
	m_trackPosX = (int)((totalWidth / 2 - m_trackWidth / 2)); 
	m_trackPosY = (int)((totalHeight - m_trackHeight) / 2) ; 

	// Calculate knob position 
	knobs[num].knobPosX = (int)(((totalWidth - knobs[num].knobWidth) / 2)); 
	knobs[num].knobPosY  = ValueToVertPosition(knobs[num].currentValue) - (int)(knobs[num].knobHeight / 2); 
} 


//////////////////////////////////////////
void GSlider::OnMouse(wxMouseEvent &event) 
{ 
	wxClientDC dc(this); 
	PrepareDC(dc); 

	wxPoint pos = event.GetPosition(); 
	long x = dc.DeviceToLogicalX(pos.x); 
	long y = dc.DeviceToLogicalY(pos.y); 
	bool onKnob = false;

	// Left button changed to down inside a fader knob 
	// so we may start dragging... 
	for(unsigned int i=0; i<knobs.size(); ++i){

		if(x >= knobs[i].knobPosX && x <= knobs[i].knobPosX + knobs[i].knobWidth 
			&& y >= knobs[i].knobPosY && y <= knobs[i].knobPosY + knobs[i].knobHeight)
		{
			//if(hover == FALSE){hover = TRUE; Refresh();}

			if(event.LeftDown()){ 
				
				onKnob = true;
				SetFocus();
				// Calculate the vertical offset between mouse pointer and knob center 
				knobs[i].mouseOffsetY = y - (knobs[i].knobPosY + knobs[i].knobHeight / 2); 

				m_draggingFader  = true;
				activeKnob = i;

				if(knobs[i].knobFocused == false){
					knobs[i].knobFocused = true; Refresh();
				}

				//turn the focus off for all other knobs
				for(unsigned int n = 0; n<knobs.size(); ++n){
					if(n != i){knobs[n].knobFocused = false; Refresh();}
				}
				//if(click == false){click = true; Refresh();}

				if(UseMouseCapture()) {
					CaptureMouse();
				}
			}

			if(event.LeftDClick()){
				onKnob = true;
				SetValue(i, knobs[i].defaultValue);
				// Create and event 
				GSliderEvent event(wxEVT_COMMAND_GSLIDER, GetId()); 
				event.SetEventObject(this); 

				// Give it some contents 
				event.SetKnobNumber(activeKnob);
				event.SetValue(knobs[i].currentValue); 

				// Send it 
				GetEventHandler()->ProcessEvent(event); 
			}
		}
	}
	
    if(!onKnob){
		if(event.LeftDown()){
			//FIXME
			//GetParent()->ProcessEvent(event); //Let left clicks bleed through the slider background to the parent.
		}
		//if(!event.LeftIsDown() && hover == TRUE){hover = FALSE; Refresh();}
	}


	if(event.GetWheelRotation() > 0){
			SetValue(activeKnob, knobs[activeKnob].currentValue + 1);
			// Create and event 
			GSliderEvent event(wxEVT_COMMAND_GSLIDER, GetId()); 
			event.SetEventObject(this); 

			// Give it some contents 
			event.SetKnobNumber(activeKnob);
			event.SetValue(knobs[activeKnob].currentValue); 

			// Send it 
			GetEventHandler()->ProcessEvent(event); 
		}

	if(event.GetWheelRotation() < 0){
			SetValue(activeKnob, knobs[activeKnob].currentValue - 1);
			// Create and event 
			GSliderEvent event(wxEVT_COMMAND_GSLIDER, GetId()); 
			event.SetEventObject(this); 

			// Give it some contents 
			event.SetKnobNumber(activeKnob);
			event.SetValue(knobs[activeKnob].currentValue); 

			// Send it 
			GetEventHandler()->ProcessEvent(event); 
	}

	// Left button changed to up 
	if(event.LeftUp() || (event.Leaving() && !UseMouseCapture())) 
	{ 
		m_draggingFader  = false; 
		knobs[activeKnob].mouseOffsetY   = 0; 

		if(HasCapture()) 
			ReleaseMouse(); 

		//if(hover == TRUE){hover = FALSE; Refresh();}
		//if(click == TRUE){click = FALSE; Refresh();}

		//return; 
	} 

	// Dragging movement ? 
	if(m_draggingFader) 
		if(event.Dragging()) 
			SetValue(activeKnob, ValueFromVertPosition(y - knobs[activeKnob].mouseOffsetY));  // (int)Should we limit the precision here ??? 
		else 
			return; 

	// Send event 
	if(m_draggingFader) 
	{ 
		// Create and event 
		GSliderEvent event(wxEVT_COMMAND_GSLIDER, GetId()); 
		event.SetEventObject(this); 

		// Give it some contents 
		event.SetKnobNumber(activeKnob);
		event.SetValue(knobs[activeKnob].currentValue); 

		// Send it 
		GetEventHandler()->ProcessEvent(event); 
	} 

	if(event.RightUp())
	{
		//Alter this to give the object it's own right click properties
		//FIXME
		//GetParent()->ProcessEvent(event); //Let right clicks bleed through to the parent.
	}
} 


//////////////////////////////////////////
void GSlider::OnKeyDown(wxKeyEvent &event)
{
	if(event.GetKeyCode() == WXK_UP || event.GetKeyCode() == WXK_NUMPAD_UP){
			SetValue(activeKnob, knobs[activeKnob].currentValue + 1);
			// Create and event 
			GSliderEvent event(wxEVT_COMMAND_GSLIDER, GetId()); 
			event.SetEventObject(this); 

			// Give it some contents 
			event.SetKnobNumber(activeKnob);
			event.SetValue(knobs[activeKnob].currentValue); 

			// Send it 
			GetEventHandler()->ProcessEvent(event); 
	}

	if(event.GetKeyCode() == WXK_DOWN || event.GetKeyCode() == WXK_NUMPAD_DOWN){
		   SetValue(activeKnob, knobs[activeKnob].currentValue - 1);
			// Create and event 
			GSliderEvent event(wxEVT_COMMAND_GSLIDER, GetId()); 
			event.SetEventObject(this); 

			// Give it some contents 
			event.SetKnobNumber(activeKnob);
			event.SetValue(knobs[activeKnob].currentValue); 

			// Send it 
			GetEventHandler()->ProcessEvent(event); 
	}
}

///////////////////////
void GSlider::AddKnob()
{
	knobs.push_back(knobs[0]);

	for(unsigned int i=0; i<knobs.size(); ++i){
		SetDefault(i, (m_maxValue / (knobs.size() + 1)) * (i + 1));
		SetValue(i, (m_maxValue / (knobs.size() + 1)) * (i + 1));
	}

	knobCount = knobs.size();
}

//////////////////////////
void GSlider::DeleteKnob()
{
	knobs.pop_back();

	for(unsigned int i=0; i<knobs.size(); ++i){
		SetDefault(i, (m_maxValue / (knobs.size() + 1)) * (i + 1));
		SetValue(i, (m_maxValue / (knobs.size() + 1)) * (i + 1));
	}

	knobCount = knobs.size();
}
