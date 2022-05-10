//// Network.h //////////////////////////////////////////////////////////////////////////
//
// This class talks to eTrigger Server. Through the server we can check for updates,
// check registration, etc.
//
// Connection to the server is attempted in the constructor of the Client:: class, and
// the NetTimer continues to attempt every minute to connect until a connection is made.
//
///////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef NETWORK_H
#define NETWORK_H

#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/textdlg.h>
#include <wx/msgdlg.h>
#include <wx/dialup.h>
#include <wx/socket.h>
#include <wx/url.h>
#include <wx/wfstream.h>
#include <wx/file.h>
#include <wx/timer.h>
#include <wx/process.h>
#include <wx/utils.h>
#include <wx/progdlg.h>

#include "MainPanel.h"

#ifdef WIN32
#include "../_WIN32/release/UPDATER.h"
#endif

#ifdef MAC
//#include "../_MAC/release/UPDATER.h"
#endif

#ifdef LINUX
#include "../_LINUX/UPDATER.H"
#endif

class MainPanel;

/*
// We will use this later for checking for internet connection. 
// if needed.
//////////////////////////////
class Internet : public wxDialUpManager
{
public:
	Internet();
	~Internet();
};
*/

//////////////////////////////
class Client : public wxDialog
{
public:
  Client(MainPanel *parent);
  ~Client();

  void OnConnect(wxCommandEvent& event);
  void OnCloseConnection(wxCommandEvent& event);
  void OnClose(wxCloseEvent &event);
  void OnDownload(wxCommandEvent& event);
  void OnSocketEvent(wxSocketEvent& event);
  void OnProgressUpdate(wxCommandEvent&event);

  void Connect();
  void GetLatestVersion(wxString currentVersion);
  void DownloadFile();
  void InstallUpdate();
  void SendComputerId();
  void SendEmail();
  void SendOSInfo();
  void SendFirstRunTime();
  void SendLastRunTime();
  bool SendErrorReport(wxString *data);

  void Notify();

  MainPanel *mainPanel;
   
  //Internet *internet;

  wxButton *connect;
  wxButton *disconnect;
  wxButton *downloadFile;
  wxProgressDialog *progressDLG;
  int updatePercent;

  wxSocketClient *m_sock;
  wxTextCtrl     *m_text;
  bool            m_busy;

  wxString host;
  wxString host2;
  int port;

  wxString latestVersion;

private:
  DECLARE_EVENT_TABLE()
};



//////////////////////////
enum
{
  // menu items
  CLIENT_QUIT = wxID_EXIT,
  CLIENT_ABOUT = wxID_ABOUT,
  CLIENT_OPEN = 100,
  CLIENT_TEST1,
  CLIENT_TEST2,
  CLIENT_TEST3,
  CLIENT_CLOSE,
#if wxUSE_URL
  CLIENT_TESTURL,
#endif
  CLIENT_DGRAM,

  // id for socket
  SOCKET_ID
};

#endif //NETWORK_H
