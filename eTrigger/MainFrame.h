//// MainFrame.h /////////////////////////////////////////////////////////////////////////////
//
// Main's job is CENTRAL CONTROL of EVERYTHING :(
//
/////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/frame.h> 
#include "MainPanel.h"

class MainPanel;

//////////////////////////////
class MainFrame: public wxFrame 
{ 
	public: 
		MainFrame(wxWindow* parent, const wxString& title, long style, wxString ver);
		~MainFrame();
		void OnMove(wxMoveEvent &event);
			
		MainPanel *mainPanel;
		
		wxIcon *icon;

		//Window States
		wxSize frameSize;
		wxPoint framePosition;
		bool maximized;
		
		//Other Variables
		wxString version;
		bool splashScreen;

		//Event Handler
		DECLARE_NO_COPY_CLASS(MainFrame)
		DECLARE_EVENT_TABLE();
};

#endif //MAINFRAME_H
