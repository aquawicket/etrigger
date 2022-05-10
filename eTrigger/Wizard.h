//// Wizard.h //////////////////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef WIZARD_H
#define WIZARD_H

#include <wx/dialog.h>
#include <wx/image.h>
#include <wx/panel.h>
#include <wx/radiobut.h> 
#include <wx/listbox.h>
#include "../lib/Gwidgets/GImage/GImage.h"
#include "../lib/Gwidgets/GButton/GButton.h"
#include "Tracks.h"

#include "../Images/audiodriver.xpm"
#include "../Images/next.xpm"
#include "../Images/audiodevices.xpm"
#include "../Images/create.xpm"
#include "../Images/newdrum.xpm"
#include "../Images/drumstick.xpm"
#include "../Images/finnished.xpm"

/////////////////////////////////
class WizardDlg : public wxDialog
{
	public:
		WizardDlg(wxWindow* parent, TrackProc &ref);
		~WizardDlg();

		TrackProc *trackProc;

		void MakePanes();

		//Audio Driver Pane
		wxPanel* AudioDriverPane;
		GButton* next1;
		GImage* image1;
		wxRadioButton* mme;
		wxRadioButton* wds;
		wxRadioButton* asio;
		void OnNext1(GButtonEvent &event);

		//Audio Devices Pane
		wxPanel* AudioDevicesPane;
		GButton* next2;
		GImage* image2;
		wxListBox *audioIn;
		void OnNext2(GButtonEvent &event);

		//New Track Pane
		wxPanel* NewTrackPane;
		GImage* image3;
		GButton* next3;
		GButton* finnished;
		void OnNext3(GButtonEvent &event);
		void OnFinnished(GButtonEvent &event);

		// Learn Pane
		wxPanel* LearnPane;
		GImage* image4;
		GButton* next4;
		void OnNext4(GButtonEvent &event);
		

	private:
		DECLARE_EVENT_TABLE() 
};


#endif //WIZARD_H
