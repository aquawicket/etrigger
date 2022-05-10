//// GImage.cpp ////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////

#include "GImage.h"

//////////////////////////////////////////////////////////////////////////////////
GImage::GImage(wxWindow* parent, int id, const wxPoint& pos, const wxString& file)
{ 
	mainPanel = parent;
	myId = id;
	position = pos;
	rotation = 0;
	xScale = 1;
	yScale = 1;
	rotating = false;
	dragging = false;
	resizeing = false;

	if(::wxFileExists(file)){
		image = wxImage(file, wxBITMAP_TYPE_ANY);
		image2 = wxImage(file, wxBITMAP_TYPE_ANY);
	}
} 

/////////////////
GImage::~GImage()
{ 

}

//////////////////////////////////////////
void GImage::Render(wxDC &dc)
{
	dc.DrawBitmap(image2, position.x, position.y, true);
}

//////////////////////////////////////////
void GImage::Render(wxGraphicsContext &gc)
{
	gc.Translate((position.x + (image2.GetWidth()/2.0)),(position.y + (image2.GetHeight()/2.0)));
	gc.Rotate(rotation);
	gc.Scale(xScale, yScale);
	gc.Translate(-(position.x + (image2.GetWidth()/2.0)),-(position.y + (image2.GetHeight()/2.0)));
	gc.DrawBitmap(image2, position.x, position.y, image2.GetWidth(), image2.GetHeight());
}

///////////////////////////////////////////
bool GImage::HasMouse(wxMouseEvent &event)
{
	wxPoint pos = event.GetPosition();
	if(pos.x > position.x && 
		pos.x < (position.x + image2.GetWidth()) && 
		pos.y > position.y &&
		pos.y < (position.y + image2.GetHeight())){
		if(!image2.IsTransparent(pos.x - position.x, pos.y - position.y, 1)){
			return true;
		}
	}
	return false;
}

/////////////////////////////////////////
bool GImage::OnMouse(wxMouseEvent &event)
{
	wxPoint pos = event.GetPosition();
	if(pos.x > position.x && 
		pos.x < (position.x + image2.GetWidth()) && 
		pos.y > position.y &&
		pos.y < (position.y + image2.GetHeight())){
		if(image2.IsTransparent(pos.x - position.x, pos.y - position.y, 1)){
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
				if(::wxGetKeyState((wxKeyCode)114)){
					if(!rotating){
						rotating = true;
						drag.y = pos.y;
						rotate = rotation;
					}
				}
				if(::wxGetKeyState((wxKeyCode)115)){
					if(!resizeing){
						resizeing = true;
						drag.x = pos.x;
						drag.y = pos.y;
						xResize = xScale;
						yResize = yScale;
					}
				}
				//else{
				//	GButtonEvent event(wxEVT_COMMAND_GBUTTON, myId); 
				//	mainPanel->GetEventHandler()->ProcessEvent(event);
				//}
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
	if(event.Dragging() && rotating && ::wxGetKeyState((wxKeyCode)114)){
		wxPoint pos = event.GetPosition();
		rotation = rotate + (double)(pos.y - drag.y) / 150;
		mainPanel->Refresh();
		return true;
	}
	if(event.Dragging() && resizeing && ::wxGetKeyState((wxKeyCode)115)){
		wxPoint pos = event.GetPosition();
		xScale = xResize + (double)(pos.x - drag.x) / 200;
		yScale = yResize + (double)(pos.y - drag.y) / 200;
		mainPanel->Refresh();
		return true;
	}
	if(event.LeftUp() && dragging){
		dragging = false;
		return false;
	}
	if(event.LeftUp() && rotating){
		rotating = false;
		return false;
	}
	if(event.LeftUp() && resizeing){
		resizeing = false;
		return false;
	}
	return false;
}