//// GObjectPanel.h ////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////

#ifndef GOBJECTPANEL_H
#define GOBJECTPANEL_H

#include <wx/panel.h>
#include <wx/image.h>
#include <wx/timer.h>
#include <wx/graphics.h>
#include <vector>
#include "GObject.h"

using namespace std;

class GObjectPanel;

//////////////////////////////
class GTimer: public wxTimer
{
public:
	GTimer(wxWindow *parent);
	void Notify();

	GObjectPanel *gObjectPanel;
};

//////////////////////////////////
class GObjectPanel: public wxPanel
{
	public: 
		GObjectPanel(wxWindow* parent);
		~GObjectPanel();
		void OnPaint(wxPaintEvent &event);
		void OnMouse(wxMouseEvent &event);

		// can this be done?
		int dcContext; //0=wxPaintDC, 1=wxBufferedPaintDC, 2=wxAutoBufferedPaintDC
		bool useGraphicsContext; //tie the dc to a wxGraphicsContext ?
		bool opengl; //this would overwrite all.. A GLCanvas would take over with all new objects.

		vector<GObject*> object;
		GTimer *timer;

		DECLARE_EVENT_TABLE()
};

#endif //GOBJECTPANEL_H