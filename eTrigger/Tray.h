//// Tray.h ////////////////////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef TRAY_H
#define TRAY_H

#include <wx/taskbar.h>
#include <wx/icon.h>
#include <wx/menu.h>

#include "MainPanel.h"

class MainPanel;

class TrayIcon : public wxTaskBarIcon
{ 
public:
	TrayIcon(MainPanel *parent);
	~TrayIcon();
	virtual wxMenu* CreatePopupMenu();
	void OnMinimizeToTray(wxCommandEvent &event);
	void OnRestoreFromTray(wxCommandEvent &event);
	void OnCenterOnScreen(wxCommandEvent &event);
	void OnExit(wxCommandEvent &event);

	MainPanel *mainPanel;

	wxMenu *trayMenu;

	DECLARE_EVENT_TABLE();
};

#endif //TRAY_H
