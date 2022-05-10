//// GImageSelector.cpp ////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////

#include "GImageSelector.h"

DEFINE_EVENT_TYPE(wxEVT_COMMAND_GIMAGESELECTOR)

IMPLEMENT_DYNAMIC_CLASS(GImageSelectorEvent, wxCommandEvent)  // RTTI

///////////////////////////////////////////////////////////
GImageSelectorEvent::GImageSelectorEvent(wxEventType commandType, int id)
		: wxCommandEvent(commandType, id) 
{ 
} 


//////////////////////////////////////////////////////////////////////////////////////////////////
GImageSelector::GImageSelector(wxWindow* parent, int id, const wxPoint& pos, const wxString& file)
{
	if(::wxFileExists(file)){
		mainPanel = parent;
		myId = id;
		position = pos;
		imageFile = file;
		dragging = false;
		image = wxImage(imageFile, wxBITMAP_TYPE_ANY);
	}
}

/////////////////////////////////
GImageSelector::~GImageSelector()
{ 
}

//////////////////////////////////////////////////
void GImageSelector::Render(wxDC &dc)
{
	dc.DrawBitmap(image, position.x, position.y, true);
}

///////////////////////////////////////////
bool GImageSelector::HasMouse(wxMouseEvent &event)
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

/////////////////////////////////////////////////
bool GImageSelector::OnMouse(wxMouseEvent &event)
{
	wxPoint pos = event.GetPosition();
	if(pos.x > position.x && 
		pos.x < (position.x + image.GetWidth()) && 
		pos.y > position.y &&
		pos.y < (position.y + image.GetHeight())){
		if(image.IsTransparent(pos.x - position.x, pos.y - position.y, 1)){
			return false;
		}
		else{
			if(event.LeftDown()){
				if(::wxGetKeyState((wxKeyCode)100)){
					if(!dragging){
						dragging = true;
						drag.x = pos.x - position.x;
						drag.y = pos.y - position.y;
					}
				}
				else{
					ChangeImage();
					//GImageSelectorEvent event(wxEVT_COMMAND_GIMAGESELECTOR, myId); 
					//mainPanel->GetEventHandler()->ProcessEvent(event);
				}
			}
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

//////////////////////////////////
void GImageSelector::ChangeImage()
{
	wxStandardPaths stdPath; 
    wxString fileLocation = stdPath.GetExecutablePath(); 
#ifdef MAC
	fileLocation.Replace(wxT("/eTrigger.app/Contents/MacOS/eTrigger"), wxT(""), true);
	fileLocation += wxT("/Images");
#endif //MAC
#ifdef WIN32
    fileLocation = wxFileName(fileLocation).GetPath() + wxT("/Images"); 
#endif //WIN32
	wxFileDialog fileDlg(mainPanel, wxString(wxT("Image Selector")), fileLocation, wxString(wxT("")), 
		                                    wxString()/*wxString(wxT("BMP files (*.bmp)|*.bmp"))*/, wxFD_OPEN | wxFD_FILE_MUST_EXIST, wxDefaultPosition);
	int responce = fileDlg.ShowModal();
	if(responce == wxID_OK){
		wxString temp;
		temp = fileDlg.GetDirectory();
#ifdef WIN32
		temp += wxT("\\");
#endif //WIN32
#ifdef MAC
		temp += wxT("/");
#endif //MAC
			
		temp += fileDlg.GetFilename();
		imageFile = temp;
		UpdateImage();
		return;
	}

	//if we get here, there was an error, or we canceled
}

void GImageSelector::UpdateImage()
{
	if(::wxFileExists(imageFile)){
		image = wxImage(imageFile, wxBITMAP_TYPE_ANY);
		mainPanel->Refresh();

		// Create and event 
		GImageSelectorEvent event(wxEVT_COMMAND_GIMAGESELECTOR, myId); 
		mainPanel->GetEventHandler()->ProcessEvent(event);
	}
	else{
		wxMessageBox(wxString::Format(wxT("Cannot find %s"), imageFile));
	}
}