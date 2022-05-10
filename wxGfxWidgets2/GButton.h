//// GButton.h //////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////

#ifndef GBUTTON_H
#define GBUTTON_H

#include "GObject.h"
#include <wx/image.h>
#include <wx/dcbuffer.h>
#include <wx/utils.h>
#include <wx/msgdlg.h>

/////////////////////////////////////////
class GButtonEvent: public wxCommandEvent 
{ 
	public: 
		GButtonEvent(wxEventType commandType = wxEVT_NULL, int id = 0 ); 

		virtual wxEvent *Clone() const { return new GButtonEvent(*this); } 

	private: 
	DECLARE_DYNAMIC_CLASS(GButtonEvent) 
}; 

BEGIN_DECLARE_EVENT_TYPES() 
	DECLARE_EVENT_TYPE(wxEVT_COMMAND_GBUTTON, -1) 
END_DECLARE_EVENT_TYPES() 

typedef void (wxEvtHandler::*wxGButtonEventFunction)(GButtonEvent&); 

#define EVT_GBUTTON(id, fn) \
	DECLARE_EVENT_TABLE_ENTRY(wxEVT_COMMAND_GBUTTON, id, -1,  \
	(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)  \
	wxStaticCastEvent(wxGButtonEventFunction, & fn), (wxObject *) NULL ),

//////////////////////////////
class GButton : public GObject
{ 
	public: 
		GButton(wxWindow* parent, int id, const wxPoint& pos, const wxString& file, const wxString& file2, const wxString& file3); 
		~GButton();
		void Render(wxDC &dc);
		bool OnMouse(wxMouseEvent &event);
		bool HasMouse(wxMouseEvent &event);

		wxWindow *mainPanel;
		int myId;
		wxImage image;
		wxImage image2;
		wxImage image3;
		wxPoint position;
		int state; //0=normal,1=hover,2=click
		wxPoint drag;
		bool dragging;
};

#endif //GBUTTON_H