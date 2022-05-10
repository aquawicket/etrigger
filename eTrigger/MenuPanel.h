//// MenuPanel.h /////////////////////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef MENUPANEL_H
#define MENUPANEL_H

#include <wx/menu.h>
#include "../lib/Gwidgets/GButton/GButton.h"

#include "../Images/MenuFile.xpm"
#include "../Images/MenuView.xpm"
#include "../Images/MenuTracks.xpm"
#include "../Images/MenuDevices.xpm"
#include "../Images/MenuTools.xpm"
#include "../Images/MenuHelp.xpm"

class MenuPanel: public wxPanel
{
public: 
	MenuPanel(MainPanel* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name);
	~MenuPanel(); 

	void OnPaint(wxPaintEvent& event); 
	void OnFile(GButtonEvent &event);
	void OnView(GButtonEvent &event);
	void OnTracks(GButtonEvent &event);
	void OnDevices(GButtonEvent &event);
	void OnTools(GButtonEvent &event);
	void OnHelp(GButtonEvent &event);

	void OnMenuNew(wxCommandEvent &event);
	void OnMenuOpen(wxCommandEvent &event);
	void OnMenuSave(wxCommandEvent &event);
	void OnMenuSaveAs(wxCommandEvent &event);
	void OnMenuExit(wxCommandEvent &event);
	void OnMenuWindowMode(wxCommandEvent &event);
	void OnMenuFullScreen(wxCommandEvent &event);
	void OnMenuMinimizeToTray(wxCommandEvent &event);
	void OnMenuAddTrigger(wxCommandEvent &event);
	void OnMenuAddMidiCC(wxCommandEvent &event);
	void OnMenuDeleteTrack(wxCommandEvent &event);
	void OnMenuSetupWizard(wxCommandEvent &event);
	void OnMenuAudioDevices(wxCommandEvent &event);
	void OnMenuMidiDevices(wxCommandEvent &event);
	void OnMenuGameDevices(wxCommandEvent &event);
	void OnMenuStatus(wxCommandEvent &event);
	void OnMenuMidiMonitor(wxCommandEvent &event);
	void OnMenuPiano(wxCommandEvent &event);
	void OnMenuSequencer(wxCommandEvent &event);
	void OnMenuSamples(wxCommandEvent &event);
	void OnMenuPlayer(wxCommandEvent &event);
	void OnMenuDebug(wxCommandEvent &event);
	void OnMenuOptions(wxCommandEvent &event);
	void OnMenuManual(wxCommandEvent &event);
	void OnMenuAbout(wxCommandEvent &event);

	MainPanel *mainPanel;
	GButton *file;
	GButton *view;
	GButton *tracks;
	GButton *devices;
	GButton *tools;
	GButton *help;
	wxStaticText *tempo;
	wxMenu *fileMenu;
	wxMenu *viewMenu;
	wxMenu *tracksMenu;
	wxMenu *devicesMenu;
	wxMenu *toolsMenu;
	wxMenu *helpMenu;
	
private:
	DECLARE_EVENT_TABLE() 
};


#endif MENUPANEL_H
