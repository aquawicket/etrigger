//// GAnimate.h //////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////

#ifndef GANIMATE_H
#define GANIMATE_H

#include "GObject.h"
#include <wx/stopwatch.h>
#include <wx/msgdlg.h>
#include <wx/thread.h>
#include <vector>

using namespace std;

///////////////////////////////
class GAnimate : public GObject
{ 
	public: 
		GAnimate(wxWindow* parent, int id, const wxPoint& pos, const wxString& file, int speed); 
		~GAnimate();
		void Render(wxDC &dc);
		void Render(wxGraphicsContext &gc);
		bool OnMouse(wxMouseEvent &event);
		bool HasMouse(wxMouseEvent &event);

		wxWindow *mainPanel;
		int myId;
		int frames;
		wxString fileName;
		wxStopWatch sw;
		double theSpeed;
		vector<wxImage> image;
		wxPoint position;
		double rotation;
		double xScale;
		double yScale;
		
		wxPoint drag;
		bool dragging;
		double rotate;
		bool rotating;
		double xResize;
		double yResize;
		bool resizeing;

		bool ready;
};


////// Load Event ////////////////////
class LoadEvent: public wxCommandEvent 
{ 
	public: 
		LoadEvent(wxEventType commandType = wxEVT_NULL, int id = 0 ); 
		virtual wxEvent *Clone() const { return new LoadEvent(*this); } // required for sending with wxPostEvent() 

	DECLARE_DYNAMIC_CLASS(LoadEvent) 
}; 

BEGIN_DECLARE_EVENT_TYPES() 
	DECLARE_EVENT_TYPE(wxEVT_COMMAND_LOAD, -1) 
END_DECLARE_EVENT_TYPES() 

typedef void (wxEvtHandler::*wxLoadEventFunction)(LoadEvent&); 

#define EVT_LOAD(id, fn) \
	DECLARE_EVENT_TABLE_ENTRY(wxEVT_COMMAND_LOAD, id, -1,  \
	(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)  \
	wxStaticCastEvent(wxLoadEventFunction, & fn), (wxObject *) NULL ),


////// Load Thread ///////////////
class LoadThread : public wxThread
{
	public:
		LoadThread(GAnimate *parent);
		~LoadThread(){};
		void *Entry();

		GAnimate *par;
};

#endif //GANIMATE_H