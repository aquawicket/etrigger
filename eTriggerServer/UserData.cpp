/// UserData.cpp ///////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////////////


#include "UserData.h"


////////////////////////////////////////////////////////////////
UserData::UserData(wxWindow *parent, wxEvtHandler &handler){
			
	par = parent;
	par2 = (MyFrame*)parent;
	evtHandler = &handler;
	numClients = 0;

	list = new wxListCtrl(par, -1, wxPoint(200,0), wxSize(600,500), wxLC_REPORT | wxLC_VRULES, wxDefaultValidator, wxT(""));
	list->InsertColumn(1, wxT("Socket"), wxLIST_FORMAT_LEFT, 45);
	list->InsertColumn(2, wxT("ComputerID"), wxLIST_FORMAT_LEFT, 100);
	list->InsertColumn(3, wxT("Operating System"), wxLIST_FORMAT_LEFT, 230);
	list->InsertColumn(4, wxT("First Run Time"), wxLIST_FORMAT_LEFT, 110);
	list->InsertColumn(5, wxT("Last Run Time"), wxLIST_FORMAT_LEFT, 110);
	list->InsertColumn(6, wxT("Email"), wxLIST_FORMAT_LEFT, 100);

	par2->mySizer->Add(list, 1, wxEXPAND, 0);
}

///////////////////////////
bool UserData::AddClient(){
			
	if(client[numClients].sock){
		client[numClients].sock->SetEventHandler(*evtHandler, numClients + 1);
		client[numClients].sock->SetNotify(wxSOCKET_INPUT_FLAG | wxSOCKET_LOST_FLAG);
		client[numClients].sock->Notify(true);
		numClients++;
		client[numClients].id = numClients;

		wxString temp = wxString::Format("%d", client[numClients].id);
		list->InsertItem(client[numClients].id, temp);

		return true;
	}
	else{
		return false;
	}
}

/////////////////////////////////////
void UserData::RemoveClient(int num){
			
	client[num-1].sock->Destroy();
	numClients--;
	list->DeleteItem(num-1);

	//lets move the clients after, down.
	for(int i=num-1; i<numClients; ++i){
		client[i] = client[i+1];
		client[i].sock->SetEventHandler(*evtHandler, i + 1); //reset the event ID
		client[i].id = i+1;
		wxString temp = wxString::Format("%d", client[i].id);
		list->SetItem(i, 0, temp, -1);
	}					
}

////////////////////////////////////////////////////////
void UserData::SetComputerId(int socketID, wxString id){

	client[socketID].computerId = id;
	list->SetItem(socketID-1, 1, id, -1);
}

////////////////////////////////////////////////////////
void UserData::SetEmail(int socketID, wxString id){

	client[socketID].email = id;
	list->SetItem(socketID-1, 5, id, -1);
}

/////////////////////////////////////////////////////////
void UserData::SetComputerOS(int socketID, wxString id){
		
	client[socketID].OSinfo = id;
	list->SetItem(socketID-1, 2, id, -1);
}

//////////////////////////////////////////////////////////
void UserData::SetFirstRunTime(int socketID, wxString id){

	long temp;
	id.ToLong(&temp, 0);
	wxDateTime temp2 = wxDateTime((time_t)temp);
	client[socketID].firstRunTime = temp2;
	wxString temp3;
	temp3 += wxString::Format("%d:", temp2.GetHour());
	temp3 += wxString::Format("%d:", temp2.GetMinute());
	temp3 += wxString::Format("%d  ", temp2.GetSecond());		
	temp3 += wxString::Format("%d/", temp2.GetMonth()+1);
	temp3 += wxString::Format("%d/", temp2.GetDay());
	temp3 += wxString::Format("%d", temp2.GetYear());

	list->SetItem(socketID-1, 3, temp3, -1);
}

/////////////////////////////////////////////////////////
void UserData::SetLastRunTime(int socketID, wxString id){

	long temp;
	id.ToLong(&temp, 0);
	wxDateTime temp2 = wxDateTime((time_t)temp);
	client[socketID].lastRunTime = temp2;
	wxString temp3;
	temp3 += wxString::Format("%d:", temp2.GetHour());
	temp3 += wxString::Format("%d:", temp2.GetMinute());
	temp3 += wxString::Format("%d  ", temp2.GetSecond());
	temp3 += wxString::Format("%d/", temp2.GetMonth()+1);
	temp3 += wxString::Format("%d/", temp2.GetDay());
	temp3 += wxString::Format("%d", temp2.GetYear());

	list->SetItem(socketID-1, 4, temp3, -1);
}

/////////////////////////////////////////////////////////
void UserData::SetEtriggerVersion(int socketID, wxString id){
	
	client[socketID].eTriggerVersion = id;
}

/////////////////////////////////////////////////////////
void UserData::SetEmailAddress(int socketID, wxString id){
	
	client[socketID].emailAddress = id;
}

/////////////////////////////////////////////////////////
void UserData::AcceptConnection(wxSocketServer *server){

	client[numClients].sock = server->Accept(false);
}
