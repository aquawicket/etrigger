//// GToggle.h //////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////

#ifndef GTOGGLE_H
#define GTOGGLE_H

#include "GObject.h"

/////////////////////////////////////////
class GToggleEvent: public wxCommandEvent 
{ 
	public: 
		GToggleEvent(wxEventType commandType = wxEVT_NULL, int id = 0 ); 

		virtual wxEvent *Clone() const { return new GToggleEvent(*this); } 

	private: 
	DECLARE_DYNAMIC_CLASS(GToggleEvent) 
}; 

BEGIN_DECLARE_EVENT_TYPES() 
	DECLARE_EVENT_TYPE(wxEVT_COMMAND_GTOGGLE, -1) 
END_DECLARE_EVENT_TYPES() 

typedef void (wxEvtHandler::*wxGToggleEventFunction)(GToggleEvent&); 

#define EVT_GTOGGLE(id, fn) \
	DECLARE_EVENT_TABLE_ENTRY(wxEVT_COMMAND_GTOGGLE, id, -1,  \
	(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)  \
	wxStaticCastEvent(wxGToggleEventFunction, & fn), (wxObject *) NULL ),


//////////////////////////////
class GToggle : public GObject
{ 
	public: 
		GToggle(wxWindow* parent, int id, const wxPoint& pos, const wxString& off, const wxString& on); 
		~GToggle();
		void Render(wxDC &dc);
		bool OnMouse(wxMouseEvent &event);
		bool HasMouse(wxMouseEvent &event);
		bool GetValue();
		void SetValue(bool truefalse);

		wxWindow *mainPanel;
		int myId;
		wxImage image;
		wxImage image2;
		wxPoint position;
		int state; //0=normal,1=hover
		bool onOff;
		wxPoint drag;
		bool dragging;
};


#endif //GTOGGLE_H