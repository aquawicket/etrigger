/// Server.h ///////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef SERVER_H
#define SERVER_H

#include <wx/frame.h>
#include <wx/sizer.h>
#include <wx/menu.h>
#include <wx/msgdlg.h>
#include <wx/socket.h>
#include <wx/file.h>
#include <wx/button.h>
#include <wx/listctrl.h>
#include <wx/datetime.h>
#include <wx/thread.h>

#include "../lib-src/Gwidgets/GHelper/GHelper.h"

#include "UserData.h"
#include "tray.h"

class UserData;
class VersionDlg;
class TrayIcon;

///////////////////////////////
class MyFrame : public wxFrame
{
public:
  MyFrame();
  ~MyFrame();

  void OnQuit(wxCommandEvent& event);
  void OnAbout(wxCommandEvent& event);
  void OnServerEvent(wxSocketEvent& event);
  void OnSocketEvent(wxSocketEvent& event);

  void SendVersion(wxSocketBase *sock);
  void SendFile(wxSocketBase *sock);
  void RecieveComputerId(wxSocketBase *sock, int socketID);
  void RecieveEmail(wxSocketBase *sock, int socketID);
  void RecieveOSInfo(wxSocketBase *sock, int socketID);
  void RecieveFirstRunTime(wxSocketBase *sock, int socketID);
  void RecieveLastRunTime(wxSocketBase *sock, int socketID);
  void RecieveErrorReport(wxSocketBase *sock, int socketID);

  bool WriteErrorReportToFile(wxString data, int socketID);

  void OnUpdateVersion(wxCommandEvent& (event));
  void OnMinimizeToTray(wxCommandEvent& (event));
  void LoadVersionFromFile();
  void SaveVersionToFile();

  void MinimizeToTray();
  void RestoreFromTray();

  wxString        version;

  void UpdateStatusBar();

  wxBoxSizer *mySizer;

  wxTextCtrl     *m_text;

private:
  wxSocketServer *m_server;
  wxMenu         *m_menuFile;
  wxMenu         *m_menuView;
  wxMenuBar      *m_menuBar;
  bool            m_busy;

  VersionDlg *versionDlg;

  UserData *userData; //we can currently hold 100 users.

  TrayIcon *trayIcon;

  DECLARE_EVENT_TABLE()
};


///////////////////////////
enum
{
  // id for sockets
  SERVER_ID = 100,
  SOCKET_ID
};


class VersionDlg : public wxDialog
{
public:
	VersionDlg(wxWindow *parent);
	void OnUpdate(wxCommandEvent &event);
	void OnCancel(wxCommandEvent &event);

	wxTextCtrl *version;
	wxButton *update;
	wxButton *close;
	MyFrame *par;

	DECLARE_EVENT_TABLE()
};



#endif //SERVER_H
