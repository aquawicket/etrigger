//// GAnimate.cpp ////////////////////////////////////////////////////
//
//
/////////////////////////////////////////////////////////////////////

#include "GAnimate.h"
//#include "windows.h"

//////////////////////////////////////////////////////////////////////////////////////
GAnimate::GAnimate(wxWindow* parent, int id, const wxPoint& pos, const wxString& file, int speed)
{ 
	ready = false;
	mainPanel = parent;
	fileName = file;
	myId = id;
	frames = 0;
	theSpeed = speed;
	position = pos;
	rotation = 0;
	xScale = 1;
	yScale = 1;
	rotating = false;
	dragging = false;
	resizeing = false;

	LoadThread *loadThread = new LoadThread(this);
	/*
	for(int i = 0; i<500; i++){
		wxString temp = file;
		temp.Replace(wxT("#"), wxString::Format("%d", i));
		if(::wxFileExists(temp)){
			image[i] = wxImage(temp, wxBITMAP_TYPE_ANY);
			frames++;
		}
		else{
			i = 500;
			continue;
		}
	}
	*/
	//sw.Start();
}

/////////////////////
GAnimate::~GAnimate()
{ 
	image.clear();
}

void GAnimate::Render(wxDC &dc)
{
	if(!ready){
		dc.DrawText(wxT("Loading..."), position.x+3, position.y+3);
		return;
	}
	double temp = (double)sw.Time() / theSpeed;
	if(temp >= frames){
		sw.Start();
		temp = 0;//sw.Time() / theSpeed;
	}
	//OutputDebugString(wxString::Format(wxT("%f\n"), temp));
	dc.DrawBitmap(image[(int)temp], position.x, position.y, true);
}

////////////////////////////////////////////
void GAnimate::Render(wxGraphicsContext &gc)
{
	if(!ready){
		wxFont font(12,wxFONTFAMILY_DECORATIVE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL);
		gc.SetFont(font,*wxBLACK);
		gc.DrawText(wxT("Loading..."), position.x+3, position.y+3);
		return;
	}
	double temp = (double)sw.Time() / theSpeed;
	if(temp >= frames){
		sw.Start();
		temp = 0;//sw.Time() / theSpeed;
	}
	gc.PushState();
	gc.Translate((position.x + (image[(int)temp].GetWidth()/2.0)),(position.y + (image[(int)temp].GetHeight()/2.0)));
	gc.Rotate(rotation);
	gc.Scale(xScale, yScale);
	gc.Translate(-(position.x + (image[(int)temp].GetWidth()/2.0)),-(position.y + (image[(int)temp].GetHeight()/2.0)));
	gc.DrawBitmap(image[(int)temp], position.x, position.y, image[(int)temp].GetWidth(), image[(int)temp].GetHeight());
	gc.PopState();
}

///////////////////////////////////////////
bool GAnimate::HasMouse(wxMouseEvent &event)
{
	if(!ready){return false;}
	wxPoint pos = event.GetPosition();
	if(pos.x > position.x && 
		pos.x < (position.x + image[0].GetWidth()) && 
		pos.y > position.y &&
		pos.y < (position.y + image[0].GetHeight())){
		if(!image[0].IsTransparent(pos.x - position.x, pos.y - position.y, 1)){
			return true;
		}
	}
	return false;
}

//////////////////////////////////////////
bool GAnimate::OnMouse(wxMouseEvent &event)
{
	if(!ready){return false;}
	wxPoint pos = event.GetPosition();
	if(pos.x > position.x && 
		pos.x < (position.x + image[0].GetWidth()) && 
		pos.y > position.y &&
		pos.y < (position.y + image[0].GetHeight())){
		if(image[0].IsTransparent(pos.x - position.x, pos.y - position.y, 1)){
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
					//GButtonEvent event(wxEVT_COMMAND_GBUTTON, myId); 
					//mainPanel->GetEventHandler()->ProcessEvent(event);
				//}
			}
			//else{
				//if(state != 1){
				//	state = 1;
				//	mainPanel->Refresh();
				//}
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





///////// Load Event ////////////////
DEFINE_EVENT_TYPE(wxEVT_COMMAND_LOAD) 
IMPLEMENT_DYNAMIC_CLASS(LoadEvent, wxCommandEvent) 

/////////////////////////////////////////////////////////////////////////////////////////
LoadEvent::LoadEvent(wxEventType commandType, int id) : wxCommandEvent(commandType, id) 
{ 
} 

//////// Load Thread /////////////////////////////////
LoadThread::LoadThread(GAnimate *parent) : wxThread()
{
	par = parent;
	Create();
	Run();
}

//////////////////////////
void *LoadThread::Entry()
{
	for(int i = 0; i<500; i++){
		wxString temp = par->fileName;
		temp.Replace(wxT("#"), wxString::Format("%d", i));
		if(::wxFileExists(temp)){
			par->image.push_back(wxImage(temp, wxBITMAP_TYPE_ANY));
			par->frames++;
		}
		else{
			i = 500;
			continue;
		}
	}
	par->ready = true;

	//LoadEvent event(wxEVT_COMMAND_LOAD, GetId()); 
	//wxPostEvent(par->GetEventHandler(), event);

	return 0;
}