/// UserData.h ///////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef USERDATA_H
#define USERDATA_H

#include "server.h"

class MyFrame;

typedef struct
{
	wxString computerId;
	wxString email;
	wxString emailAddress;
	wxString OSinfo;
	wxString eTriggerVersion;
	wxDateTime firstRunTime;
	wxDateTime lastRunTime;
	
	//temporary run-time window data
	int id;
	wxSocketBase *sock;

}Client;

///////////////////////////////
class UserData
{
	public:
	
		UserData(wxWindow *parent, wxEvtHandler &handler);
		bool AddClient();
		void RemoveClient(int num);
		void SetComputerId(int socketID, wxString id);
		void SetEmail(int socketID, wxString id);
		void SetComputerOS(int socketID, wxString id);
		void SetFirstRunTime(int socketID, wxString id);
		void SetLastRunTime(int socketID, wxString id);
		void SetEtriggerVersion(int socketID, wxString id);
		void SetEmailAddress(int socketID, wxString id);
		void AcceptConnection(wxSocketServer *server);

		wxWindow *par;
		MyFrame *par2;
		int numClients;
		Client client[100]; //support for 100 clients
		wxEvtHandler *evtHandler;
		wxListCtrl *list;
};



#endif //USERDATA_H
