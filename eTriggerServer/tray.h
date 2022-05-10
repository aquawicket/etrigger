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

#include "server.h"

//#include "../Images/eTriggerServerIcon.xpm"

class MyFrame;

class TrayIcon : public wxTaskBarIcon
{ 
public:
	TrayIcon(wxWindow *parent);
	~TrayIcon();
	virtual wxMenu* CreatePopupMenu();
	void OnMinimizeToTray(wxCommandEvent &event);
	void OnRestoreFromTray(wxCommandEvent &event);

	MyFrame *par;

	wxMenu *trayMenu;
	//wxIcon *icon;

	DECLARE_EVENT_TABLE();
};

#endif //TRAY_H
