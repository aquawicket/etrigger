//// Tray.cpp //////////////////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "Tray.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////
BEGIN_EVENT_TABLE(TrayIcon, wxTaskBarIcon)
	EVT_MENU(100, TrayIcon::OnMinimizeToTray) 
	EVT_MENU(101, TrayIcon::OnRestoreFromTray)
	EVT_MENU(103, TrayIcon::OnCenterOnScreen)
	EVT_MENU(102, TrayIcon::OnExit) 
END_EVENT_TABLE()

/////////////////////////////////////
TrayIcon::TrayIcon(MainPanel *parent)
		: wxTaskBarIcon()
{
	mainPanel = parent;

	#ifdef WIN32
	SetIcon(wxICON(APPICON), wxT("eTrigger"));
	#endif //WIN32
}

/////////////////////
TrayIcon::~TrayIcon()
{
	RemoveIcon();
}

///////////////////////////////////
wxMenu* TrayIcon::CreatePopupMenu()
{
    trayMenu = new wxMenu(wxT("eTrigger"));

  
    trayMenu->Append(100, wxT("Minimize To Tray"), wxT(""), wxITEM_NORMAL);
    trayMenu->Append(101, wxT("Restore From Tray"), wxT(""), wxITEM_NORMAL);

	#ifndef VST
	trayMenu->Append(103, wxT("Center On Screen"), wxT(""), wxITEM_NORMAL);
	#endif //VST

	trayMenu->Append(102, wxT("Exit"), wxT(""), wxITEM_NORMAL);
   
    return trayMenu;
} 

//////////////////////////////////////////////////////
void TrayIcon::OnMinimizeToTray(wxCommandEvent &event)
{
	wxCommandEvent temp;
	mainPanel->OnMenuMinimizeToTray(temp);
}

///////////////////////////////////////////////////////
void TrayIcon::OnRestoreFromTray(wxCommandEvent &event)
{
	mainPanel->RestoreFromTray();
}

//////////////////////////////////////////////////////
void TrayIcon::OnCenterOnScreen(wxCommandEvent &event)
{
	#ifndef VST
	mainPanel->par->Show();
	mainPanel->par->Iconize(false);
	mainPanel->par->CenterOnScreen(wxBOTH);
	#endif //VST
}

////////////////////////////////////////////
void TrayIcon::OnExit(wxCommandEvent &event)
{
	wxCommandEvent temp;
	mainPanel->OnMenuExit(temp);
}
