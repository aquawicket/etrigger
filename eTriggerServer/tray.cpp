//// Tray.cpp //////////////////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "tray.h"

//////////////////////////////////////////
BEGIN_EVENT_TABLE(TrayIcon, wxTaskBarIcon)
	EVT_MENU(100, TrayIcon::OnMinimizeToTray) 
	EVT_MENU(101, TrayIcon::OnRestoreFromTray) 
END_EVENT_TABLE()

TrayIcon::TrayIcon(wxWindow *parent) : wxTaskBarIcon()
{
	SetIcon(wxICON(APPICON));
	par = (MyFrame*)parent;
}

TrayIcon::~TrayIcon()
{
	RemoveIcon();
}

wxMenu* TrayIcon::CreatePopupMenu()
{
    trayMenu = new wxMenu();
    trayMenu->Append(100, wxT("Minimize To Tray"), wxT(""), wxITEM_NORMAL);
    trayMenu->Append(101, wxT("Restore From Tray"), wxT(""), wxITEM_NORMAL);
    return trayMenu;
} 

void TrayIcon::OnMinimizeToTray(wxCommandEvent &event)
{
	par->MinimizeToTray();
}

void TrayIcon::OnRestoreFromTray(wxCommandEvent &event)
{
	par->RestoreFromTray();
}
