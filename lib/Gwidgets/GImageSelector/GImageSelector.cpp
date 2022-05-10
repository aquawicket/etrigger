//// GImageSelector.cpp ///////////////////////////////////////////////////////////
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



////////////////////////////////////
BEGIN_EVENT_TABLE(GImageSelector, wxPanel) 
	EVT_PAINT  (GImageSelector::OnPaint)
	EVT_MOUSE_EVENTS (GImageSelector::OnMouse) 
	//EVT_ERASE_BACKGROUND (GImageSelector::OnEraseBackground) 
END_EVENT_TABLE() 

////////////////////////////////////////////////////////////////////////////////////////////////////////
GImageSelector::GImageSelector(wxWindow* parent, wxWindowID id, const wxPoint &pos, const wxSize &size) 
{ 
	wxPanel::Create(parent, id, pos, size, wxNO_BORDER | wxTRANSPARENT_WINDOW, wxT(""));
	backFocused = false;
} 

/////////////////////////////////
GImageSelector::~GImageSelector() 
{ 

} 

///////////////////////////////////////////////////////////
void GImageSelector::OnPaint(wxPaintEvent &event) 
{ 
	if(::wxFileExists(filePath)){
		wxPaintDC dc(this);
		dc.DrawBitmap(image,0,0,true);
	}

	event.Skip();
} 

/////////////////////////////////////////////////
void GImageSelector::OnMouse(wxMouseEvent &event) 
{ 
	if(event.LeftDown()){ 
		wxStandardPaths stdPath; 
        wxString fileLocation = stdPath.GetExecutablePath(); 
#ifdef MAC
		fileLocation.Replace(wxT("/eTrigger.app/Contents/MacOS/eTrigger"), wxT(""), true);
		fileLocation += wxT("/Images");
#endif //MAC
#ifdef WIN32
        fileLocation = wxFileName(fileLocation).GetPath() + wxT("/Images"); 
#endif //WIN32

		wxFileDialog fileDlg(this, wxString(wxT("Image Selector")), fileLocation, wxString(wxT("")), 
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
			filePath = temp;
			UpdateImage();
			return;
		}

	//if we get here, there was an error, or we canceled
	}
}

void GImageSelector::UpdateImage()
{
	if(::wxFileExists(filePath)){
		image = wxImage(filePath, wxBITMAP_TYPE_ANY);
		Refresh();

		// Create and event 
		GImageSelectorEvent event(wxEVT_COMMAND_GIMAGESELECTOR, GetId()); 
		event.SetEventObject(this); 

		// Send it 
		GetEventHandler()->ProcessEvent(event); 
	}
	else{
		wxMessageBox(wxString::Format(wxT("Cannot find %s"), filePath));
	}
}

void GImageSelector::SetImage(wxString &file)
{
	filePath = file;
	UpdateImage();
}

wxString GImageSelector::GetImage()
{
	return filePath;
}

///////////////////////////////////////////////////////////
void GImageSelector::OnEraseBackground(wxEraseEvent &event) 
{ 
} 
