//// GAnimate.h //////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////

#ifndef GANIMATE_H
#define GANIMATE_H

#include "GObject.h"
#include <wx/stopwatch.h>
#include <wx/msgdlg.h>

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
		//void Resample();

		wxWindow *mainPanel;
		int myId;
		int frames;
		wxStopWatch sw;
		int theSpeed;
		wxImage image[100];
		wxImage image2[100];
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
};

#endif //GANIMATE_H