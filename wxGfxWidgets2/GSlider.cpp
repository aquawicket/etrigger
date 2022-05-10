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


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GSlider::GSlider(wxWindow* parent, int id, const wxPoint& pos, const wxString& sliderBG, const wxString& sliderKnob)
{ 
	mainPanel = parent;
	myId = id;
	position = pos;
	dragging = false;

	Init();
  
	if(::wxFileExists(sliderBG)){
		c_back = wxImage(sliderBG, wxBITMAP_TYPE_ANY);
		c_backFocused = wxImage(sliderBG, wxBITMAP_TYPE_ANY);
	}
	if(::wxFileExists(sliderKnob)){
		knobs.resize(1);
		knobs[0].slider = wxImage(sliderKnob, wxBITMAP_TYPE_ANY);
		knobs[0].focused = wxImage(sliderKnob, wxBITMAP_TYPE_ANY);
		knobs[0].knobWidth = knobs[0].slider.GetWidth();
		knobs[0].knobHeight = knobs[0].slider.GetHeight();
		knobs[0].hover = false;
		knobs[0].click = false;
		knobs[0].knobFocused = false;
		knobCount = 1;
	}

	SetRange(0, 500); 
	SetDefault(0, 40);
	SetValue(0, 50);
}


///////////////////
GSlider::~GSlider() 
{ 
} 

////////////////////
void GSlider::Init() 
{ 
	m_draggingFader  = false; 
	activeKnob = 0;

	hover = false;
	click = false;
	backFocused = false;
	knobFocused = false;
} 


///////////////////////////////////////////
bool GSlider::HasMouse(wxMouseEvent &event)
{
	wxPoint pos = event.GetPosition();
	if(pos.x > position.x && 
		pos.x < (position.x + c_back.GetWidth()) && 
		pos.y > position.y &&
		pos.y < (position.y + c_back.GetHeight())){
		if(!c_back.IsTransparent(pos.x - position.x, pos.y - position.y, 1)){
			return true;
		}
	}
	return false;
}

//////////////////////////////////////////
bool GSlider::OnMouse(wxMouseEvent &event)
{
	wxPoint pos = event.GetPosition();
	if(pos.x > position.x && 
		pos.x < (position.x + c_back.GetWidth()) && 
		pos.y > position.y &&
		pos.y < (position.y + c_back.GetHeight())){
		if(c_back.IsTransparent(pos.x - position.x, pos.y - position.y, 1)){
			//if(state != 0){
			//	state = 0;
			//	mainPanel->Refresh();
			//}
			return false;
		}
		else{
			if(event.LeftDown()){
				for(unsigned int i=0; i<knobs.size(); ++i){
					if(pos.x >= (position.x + knobs[i].knobPosX) && 
					   pos.x <= (position.x + knobs[i].knobPosX + knobs[i].knobWidth) && 
					   pos.y >= (position.y + knobs[i].knobPosY)&&
					   pos.y <= (position.y + knobs[i].knobPosY + knobs[i].knobHeight)){
							//onKnob = true;
							m_draggingFader  = true;
							activeKnob = i;
							knobs[i].mouseOffsetY = pos.y - (position.y + knobs[i].knobPosY + knobs[i].knobHeight / 2); // Calculate the vertical offset between mouse pointer and knob center 
							if(knobs[i].knobFocused == false){
								knobs[i].knobFocused = true; mainPanel->Refresh();
							}
							for(unsigned int n = 0; n<knobs.size(); ++n){ //turn the focus off for all other knobs
								if(n != i){knobs[n].knobFocused = false; mainPanel->Refresh();}
							}
					}
				}
				//if(state != 3){
				//	state = 3;
				//	mainPanel->Refresh();
				//}
				if(::wxGetKeyState((wxKeyCode)100)){
					if(!dragging){
						dragging = true;
						drag.x = pos.x - position.x;
						drag.y = pos.y - position.y;
					}
				}
				else{
					//GButtonEvent event(wxEVT_COMMAND_GBUTTON, myId); 
					//mainPanel->GetEventHandler()->ProcessEvent(event);
				}
			}
			if(event.LeftDClick()){
				for(unsigned int i=0; i<knobs.size(); ++i){
					if(pos.x >= (position.x + knobs[i].knobPosX) && 
					   pos.x <= (position.x + knobs[i].knobPosX + knobs[i].knobWidth) && 
					   pos.y >= (position.y + knobs[i].knobPosY)&&
					   pos.y <= (position.y + knobs[i].knobPosY + knobs[i].knobHeight)){
							//onKnob = true;
							SetValue(i, knobs[i].defaultValue);
							// Create and event 
							GSliderEvent event(wxEVT_COMMAND_GSLIDER, myId); 
							//event.SetEventObject(this); 

							// Give it some contents 
							event.SetKnobNumber(activeKnob);
							event.SetValue(knobs[activeKnob].currentValue); 

							// Send it 
							mainPanel->GetEventHandler()->ProcessEvent(event);
					}
				}
			}

			//else{
			//	if(state != 1){
			//		state = 1;
			//		mainPanel->Refresh();
			//	}
			//}
		}
	}
	//else{
	//	if(state != 0){
	//		state = 0;
	//		mainPanel->Refresh();
	//	}
	//}
	if(event.Dragging() && dragging && ::wxGetKeyState((wxKeyCode)100)){
		wxPoint pos = event.GetPosition();
		position.x = pos.x - drag.x;
		position.y = pos.y - drag.y;
		mainPanel->Refresh();
		return true;
	}
	if(event.Dragging() && m_draggingFader){
		wxPoint pos = event.GetPosition();
		SetValue(activeKnob, ValueFromVertPosition(pos.y - (position.y + knobs[activeKnob].mouseOffsetY)));  // (int)Should we limit the precision here ??? 
		// Create and event 
		GSliderEvent event(wxEVT_COMMAND_GSLIDER, myId); 
		//event.SetEventObject(this); 

		// Give it some contents 
		event.SetKnobNumber(activeKnob);
		event.SetValue(knobs[activeKnob].currentValue); 

		// Send it 
		mainPanel->GetEventHandler()->ProcessEvent(event); 
		mainPanel->Refresh();
		return true;
	}
	if(event.LeftUp() || event.Leaving()){
		m_draggingFader = false; 
		knobs[activeKnob].mouseOffsetY   = 0;
		dragging = false;
		return false;
	}
	return false;
}

/*
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
*/

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

		mainPanel->Refresh(); 
	} 
	//else: nothing changed 
} 

///////////////////////////////
/*
bool GSlider::UseMouseCapture() 
{ 
	if(GetWindowStyle() & FDR_NO_MOUSE_CAPTURE) 
		return false; 
	else{
		return true; 
	} 
} 
*/

////////////////////////////////////////
/*
void GSlider::OnSize(wxSizeEvent &event) 
{ 
	for(unsigned int i=0; i<knobs.size(); ++i){
		CalcGeometry(i); 
	}
	Refresh();   // For any mysterious reason... 
	event.Skip(); 
}
*/

///////////////////////////////////////////
void GSlider::Render(wxDC &dc)
{
	DrawBackground(dc); 
	DrawFaders(dc); 
}


//////////////////////////////////////////////
/*
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
*/

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
		dc.DrawBitmap( c_back, position.x, position.y, true);
	}
	if(backFocused){
		dc.DrawBitmap( c_backFocused, position.x, position.y, true);
	}
} 

///////////////////////////////// 
void GSlider::DrawFaders(wxDC &dc) 
{ 
	for(unsigned int i=0; i<knobs.size(); ++i){
		if(knobs[i].knobFocused == true){
			dc.DrawBitmap( knobs[i].focused, position.x + knobs[i].knobPosX, position.y + knobs[i].knobPosY, true);
		}
		else{
			dc.DrawBitmap( knobs[i].slider, position.x + knobs[i].knobPosX, position.y + knobs[i].knobPosY, true);
			//wxMessageBox(wxString::Format(wxT("%d"), knobs[i].knobPosX));

		}
	}
}

////////////////////////////////
float GSlider::GetValue(int num)
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
	mainPanel->Refresh(); 

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
	//GetClientSize(&totalWidth, &totalHeight); 
	totalWidth = c_back.GetSize().x; 
	totalHeight = c_back.GetSize().y; 

	// Calculate track width and position 
	m_trackHeight = totalHeight - knobs[num].knobHeight - 4; 
	m_trackPosX = (int)((totalWidth / 2 - m_trackWidth / 2)); 
	m_trackPosY = (int)((totalHeight - m_trackHeight) / 2) ; 

	// Calculate knob position 
	knobs[num].knobPosX = (int)(((totalWidth - knobs[num].knobWidth) / 2)); 
	knobs[num].knobPosY  = ValueToVertPosition(knobs[num].currentValue) - (int)(knobs[num].knobHeight / 2); 
} 

//////////////////////////////////////////
/*
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
*/

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
