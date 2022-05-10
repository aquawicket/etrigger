//// GButton.cpp ////////////////////////////////////////////////////
//
//
/////////////////////////////////////////////////////////////////////

#include "GButton.h"

DEFINE_EVENT_TYPE(wxEVT_COMMAND_GBUTTON) 

IMPLEMENT_DYNAMIC_CLASS(GButtonEvent, wxCommandEvent)  // RTTI

///////////////////////////////////////////////////////////
GButtonEvent::GButtonEvent(wxEventType commandType, int id) 
		: wxCommandEvent(commandType, id) 
{ 
} 


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GButton::GButton(wxWindow* parent, int id, const wxPoint& pos, const wxString& file, const wxString& file2, const wxString& file3)
{ 
	state = 0;
	mainPanel = parent;
	myId = id;
	position = pos;
	dragging = false;

	if(::wxFileExists(file)){
		image = wxImage(file, wxBITMAP_TYPE_ANY);
	}
	if(::wxFileExists(file2)){
		image2 = wxImage(file2, wxBITMAP_TYPE_ANY);
	}
	if(::wxFileExists(file3)){
		image3 = wxImage(file3, wxBITMAP_TYPE_ANY);
	}
} 

///////////////////
GButton::~GButton()
{ 
}

///////////////////////////////////////////
void GButton::Render(wxDC &dc)
{
	if(state == 0){
		dc.DrawBitmap(image, position.x, position.y, true);
	}
	if(state == 1){
		dc.DrawBitmap(image2, position.x, position.y, true);
	}
	if(state == 3){
		dc.DrawBitmap(image3, position.x, position.y, true);
	}
}

///////////////////////////////////////////
bool GButton::HasMouse(wxMouseEvent &event)
{
	wxPoint pos = event.GetPosition();
	if(pos.x > position.x && 
		pos.x < (position.x + image.GetWidth()) && 
		pos.y > position.y &&
		pos.y < (position.y + image.GetHeight())){
		if(!image.IsTransparent(pos.x - position.x, pos.y - position.y, 1)){
			return true;
		}
	}
	return false;
}

//////////////////////////////////////////
bool GButton::OnMouse(wxMouseEvent &event)
{
	wxPoint pos = event.GetPosition();
	if(pos.x > position.x && 
		pos.x < (position.x + image.GetWidth()) && 
		pos.y > position.y &&
		pos.y < (position.y + image.GetHeight())){
		if(image.IsTransparent(pos.x - position.x, pos.y - position.y, 1)){
			if(state != 0){
				state = 0;
				mainPanel->Refresh();
			}
			return false;
		}
		else{
			if(event.LeftDown()){
				if(state != 3){
					state = 3;
					mainPanel->Refresh();
				}
				if(::wxGetKeyState((wxKeyCode)100)){
					if(!dragging){
						dragging = true;
						drag.x = pos.x - position.x;
						drag.y = pos.y - position.y;
					}
				}
				else{
					GButtonEvent event(wxEVT_COMMAND_GBUTTON, myId); 
					mainPanel->GetEventHandler()->ProcessEvent(event);
				}
			}
			else{
				if(state != 1){
					state = 1;
					mainPanel->Refresh();
				}
			}
		}
	}
	else{
		if(state != 0){
			state = 0;
			mainPanel->Refresh();
		}
	}
	if(event.Dragging() && dragging && ::wxGetKeyState((wxKeyCode)100)){
		wxPoint pos = event.GetPosition();
		position.x = pos.x - drag.x;
		position.y = pos.y - drag.y;
		mainPanel->Refresh();
		return true;
	}
	if(event.LeftUp() && dragging){
		dragging = false;
		return false;
	}
	return false;
}