//// GToggle.cpp ////////////////////////////////////////////////////////////
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////
GToggle::GToggle(wxWindow* parent, int id, const wxPoint& pos, const wxString& off, const wxString& on)
{ 
	if(::wxFileExists(off)){
		state = 0;
		mainPanel = parent;
		myId = id;
		position = pos;
		onOff = false;
		dragging = false;
		image = wxImage(off, wxBITMAP_TYPE_ANY);
	}
	if(::wxFileExists(on)){
		image2 = wxImage(on, wxBITMAP_TYPE_ANY);
	}
}

///////////////////
GToggle::~GToggle()
{ 

}

///////////////////////////////////////////
void GToggle::Render(wxDC &dc)
{
	if(onOff == false){
		dc.DrawBitmap(image, position.x, position.y, true);
	}
	if(onOff == true){
		dc.DrawBitmap(image2, position.x, position.y, true);
	}
}

///////////////////////////////////////////
bool GToggle::HasMouse(wxMouseEvent &event)
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
bool GToggle::OnMouse(wxMouseEvent &event)
{
	wxPoint pos = event.GetPosition();
	if(pos.x > position.x && 
		pos.x < (position.x + image.GetWidth()) && 
		pos.y > position.y &&
		pos.y < (position.y + image.GetHeight())){
		if(image.IsTransparent(pos.x - position.x, pos.y - position.y, 1)){
			//if(state != 0){
			//	state = 0;
			//	mainPanel->Refresh();
			//}
			return false;
		}
		else{
			if(event.LeftDown()){
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
					if(onOff == true){onOff = false;}
					else{onOff = true;}
					mainPanel->Refresh();
					GToggleEvent event(wxEVT_COMMAND_GTOGGLE, myId); 
					mainPanel->GetEventHandler()->ProcessEvent(event);
				}
			}
			else{
				//if(state != 1){
				//	state = 1;
				//	mainPanel->Refresh();
				//}
			}
		}
	}
	//else{
		//if(state != 0){
		//	state = 0;
		//	mainPanel->Refresh();
		//}
	//}
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

bool GToggle::GetValue()
{
	return onOff;
}

void GToggle::SetValue(bool truefalse)
{
	onOff = truefalse;
}