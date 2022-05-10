//// GImageSelector.h //////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////

#ifndef GIMAGESELECTOR_H
#define GIMAGESELECTOR_H

#include "GObject.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/filedlg.h>
#include <wx/image.h>
#include <wx/dcbuffer.h>
#include <wx/msgdlg.h>

////////////////////////////////////////////////
class GImageSelectorEvent: public wxCommandEvent 
{ 
	public: 
		GImageSelectorEvent(wxEventType commandType = wxEVT_NULL, int id = 0 ); 

		virtual wxEvent *Clone() const { return new GImageSelectorEvent(*this); } 

	private: 
	DECLARE_DYNAMIC_CLASS(GImageSelectorEvent) 
}; 

BEGIN_DECLARE_EVENT_TYPES() 
	DECLARE_EVENT_TYPE(wxEVT_COMMAND_GIMAGESELECTOR, -1) 
END_DECLARE_EVENT_TYPES() 

typedef void (wxEvtHandler::*wxGImageSelectorEventFunction)(GImageSelectorEvent&); 

#define EVT_GIMAGESELECTOR(id, fn) \
	DECLARE_EVENT_TABLE_ENTRY(wxEVT_COMMAND_GIMAGESELECTOR, id, -1,  \
	(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)  \
	wxStaticCastEvent(wxGImageSelectorEventFunction, & fn), (wxObject *) NULL ),



/////////////////////////////////////
class GImageSelector : public GObject
{
public:
	GImageSelector(wxWindow* parent, int id, const wxPoint& pos, const wxString& file); 
	~GImageSelector();
	void Render(wxDC &dc);
	bool OnMouse(wxMouseEvent &event);
	bool HasMouse(wxMouseEvent &event);
	void ChangeImage();
	void UpdateImage();

	wxWindow *mainPanel;
	int myId;
	wxString imageFile;
	wxImage image;
	wxPoint position;
	wxPoint drag;
	bool dragging;
};

#endif //GIMAGESELECTOR_H