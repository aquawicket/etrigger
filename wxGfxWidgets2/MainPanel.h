//// MainPanel.h /////////////////////////////////////////////////////////////////////////////
//
//
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef MAINPANEL_H
#define MAINPANEL_H

#include "GObjectPanel.h"
#include "GImage.h"
#include "GAnimate.h"
#include "GButton.h"
#include "GToggle.h"
#include "GImageSelector.h"
#include "GSlider.h"
#include <wx/stattext.h>
#include <wx/menu.h>

////////////////////////////////////
class MainPanel: public GObjectPanel
{
	public:
		MainPanel(wxWindow* Parent);
		~MainPanel();
		void OnMouse(wxMouseEvent &event);
		void OnNewGImage(wxCommandEvent &event);
		void OnGButton1(GButtonEvent &event);
		void OnGToggle1(GToggleEvent &event);
		void OnGImageSelector1(GImageSelectorEvent &event);
		void OnGSlider1(GSliderEvent &event);

		wxStaticText *mouseXY;
		wxStaticText *theEvent;

		wxMenu *menu;

		DECLARE_EVENT_TABLE()
};

#endif //MAINPANEL_H