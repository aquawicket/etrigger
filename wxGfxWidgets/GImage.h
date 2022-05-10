//// GImage.h //////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////

#ifndef GIMAGE_H
#define GIMAGE_H

#include "GObject.h"
#include <wx/image.h>
#include <wx/dcbuffer.h>
#include <wx/graphics.h>

/////////////////////////////
class GImage : public GObject
{ 
	public: 
		GImage(wxWindow* parent, int id, const wxPoint& pos, const wxString& file); 
		~GImage();
		void Render(wxDC &dc);
		void Render(wxGraphicsContext &gc);
		bool OnMouse(wxMouseEvent &event);
		bool HasMouse(wxMouseEvent &event);

		wxWindow *mainPanel;
		int myId;
		wxImage image;
		wxImage image2;
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

#endif //GIMAGE_H