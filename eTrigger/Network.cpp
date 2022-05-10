//// Network.cpp //////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "Network.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

///////////////////////////////////
BEGIN_EVENT_TABLE(Client, wxDialog)
  EVT_BUTTON(100, Client::OnConnect)
  EVT_BUTTON(101, Client::OnCloseConnection)
  EVT_BUTTON(102, Client::OnDownload)
  EVT_SOCKET(SOCKET_ID,     Client::OnSocketEvent)
  EVT_COMMAND(wxID_ANY, wxEVT_COMMAND_BUTTON_CLICKED, Client::OnProgressUpdate) 
  EVT_CLOSE(Client::OnClose)
END_EVENT_TABLE()

/////////////////////////////////
Client::Client(MainPanel *parent) 
		: wxDialog(parent, -1, wxT("Client"), wxDefaultPosition, wxSize(300,400), wxDEFAULT_DIALOG_STYLE, wxT(""))
{
  mainPanel = parent;

  //Check for internet
  //internet->Create();
  //if(internet->IsOk()){wxMessageBox("wxDialUpManager is ok",wxT(""), wxSTAY_ON_TOP);}

  host = wxT("server.etrigger.net"); //eTrigger Server
  //host = wxT("64.31.98.34"); //eTrigger Server
  port = 3000;

  //Make buttons
  connect = new wxButton(this, 100, wxT("Connect"), wxPoint(10,10), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
  disconnect = new wxButton(this, 101, wxT("Disconnect"), wxPoint(10,40), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
  downloadFile = new wxButton(this, 102, wxT("Download File"), wxPoint(10,70), wxDefaultSize, 0, wxDefaultValidator, wxT(""));

  // Make a textctrl for logging
  m_text  = new wxTextCtrl(this, wxID_ANY,
                           wxT("Client ready\n"),
                           wxPoint(10,175), wxSize(280, 175),
                           wxTE_MULTILINE | wxTE_READONLY);

  // Create the socket
  m_sock = new wxSocketClient();

  // Setup the event handler and subscribe to most events
  m_sock->SetEventHandler(*this, SOCKET_ID);
  m_sock->SetNotify(wxSOCKET_CONNECTION_FLAG | wxSOCKET_INPUT_FLAG | wxSOCKET_LOST_FLAG);
  m_sock->Notify(true);

  m_busy = false;

  updatePercent = 0;

	//first try to connect to a local host for debuging
	#ifdef _DEBUG
    /*
	wxIPV4address addr;
	addr.Hostname(wxT("127.0.0.1"));
	addr.Service(port);
	m_text->AppendText(wxT("Connecting to Local eTrigger Server ...\n"));
	m_sock->Connect(addr, false);
	m_sock->WaitOnConnect(120);
	*/
	#endif

	//Then try to connect to the real eTrigger server.
	if (!m_sock->IsConnected()){
		Connect();
	}
}

/////////////////
Client::~Client()
{
  delete m_sock;
}

//////////////////////
void Client::Connect()
{
	wxIPV4address addr;
	addr.Hostname(host);
	addr.Service(port);

    m_text->AppendText(wxT("Connecting to eTrigger Server ...\n"));
    m_sock->Connect(addr, false);
    //m_sock->WaitOnConnect(120);
 }

//////////////////////////////////////////////////////
void Client::GetLatestVersion(wxString currentVersion)
{
	#define MAX_MSG_SIZE 10000

	wxString s;
	wxChar *buf = new wxChar[MAX_MSG_SIZE];
	wxUint32 len;
	
	if (m_sock->IsConnected()){
		//////////////////////////
		unsigned char c = 0xFE;
		m_sock->SetFlags(wxSOCKET_WAITALL);
		m_sock->Write(&c, 1);

		m_sock->SetFlags(wxSOCKET_WAITALL);

		len = m_sock->ReadMsg(buf, MAX_MSG_SIZE * sizeof(wxChar)).LastCount(); //FIXME - CRASH!!

		if(!m_sock->Error()){
			latestVersion = buf;
		}
		delete[] buf;

		//compair versions
		if(mainPanel->version < latestVersion && !::wxFileExists(wxT("eTrigger-Update.zip"))){
#ifdef WIN32
			wxMessageDialog temp(this, 
			wxT("A newer version of eTrigger is available. Would you like eTrigger to download this update now?"),
			wxT("Download Update?"), wxYES_NO | wxSTAY_ON_TOP, wxDefaultPosition);
		
			if(temp.ShowModal() == wxID_YES){
				DownloadFile();
			}
#endif //WIN32
#ifdef MAC
			wxMessageBox(wxT("A newer version of eTrigger is available. Please download from www.etrigger.net"));
#endif //MAC
		}
	}
	else{
		m_text->AppendText(wxT("Not connected to eTrigger Server\n"));
	}

	#undef MAX_MSG_SIZE

}

///////////////////////////
void Client::DownloadFile()
{
	if (m_sock->IsConnected()){
		//Request File
		// Tell the server which test we are running
		unsigned char c = 0xEE;
		m_sock->Write(&c, 1);

		m_sock->SetFlags(wxSOCKET_WAITALL);

		char *buf;
		int bufSize;

		m_sock->Read(&bufSize, sizeof(bufSize));

		// FIXME *we've got to find a way to do this non-Blocking.
		m_text->AppendText(wxString::Format(wxT("Downloading file ... %d bytes\n"), bufSize));
		buf = new char[bufSize];

		wxCommandEvent MyEvent( wxEVT_COMMAND_BUTTON_CLICKED );  wxPostEvent(this, MyEvent);  

		wxFile *file = new wxFile(wxT("eTrigger-Update.zip"), wxFile::write);
		
		m_sock->SetFlags(wxSOCKET_WAITALL);
		int bytes = 0;
		int b = 0;
		int header = 0;
		int temp = 0;
       
		while (bytes < bufSize)
		{
			m_sock->Read(&header, sizeof(header));
			m_sock->Read(buf, header);
			if (m_sock->Error())
			{
                /* error handling */
			    wxMessageBox(wxT("Error downloading update, please try again later."),wxT(""), wxSTAY_ON_TOP);
				if(::wxFileExists(wxT("eTrigger-Update.zip"))){
					::wxRemoveFile(wxT("eTrigger-Update.zip"));
				}
                break;
			}
    	
			b = m_sock->LastCount();
			if (b == 0) break;
			file->Write(buf, b);
			bytes += b;

			int perc = (bytes * 100) / bufSize;
		
			if(perc > temp){
				updatePercent = perc; 
				wxCommandEvent MyEvent( wxEVT_COMMAND_BUTTON_CLICKED );  wxPostEvent(this, MyEvent);  
				temp++;
			}
		}
		file->Close(); 
	    delete file;
		delete[] buf;

		if(!m_sock->Error()){

			m_text->AppendText(wxT("Download Complete ...\n"));

			wxMessageDialog temp(this, 
			wxT("The newest version of eTrigger is ready to install. Install it now?"),
			wxT("Install Update?"), wxYES_NO | wxSTAY_ON_TOP, wxDefaultPosition);
		
			if(temp.ShowModal() == wxID_YES){
				InstallUpdate();
			}
		}

		m_text->AppendText(m_sock->Error() ? wxT("failed !\n") : wxT("done\n"));
	}
	else{
		m_text->AppendText(wxT("Not connected to eTrigger Server\n"));
	}
}

///////////////////////////////////////////////////
void Client::OnProgressUpdate(wxCommandEvent&event)
{
	if(updatePercent == 0){
		progressDLG = new wxProgressDialog(wxT("Downloading Update..."), wxT("eTrigger-Update.zip"), 100, this,  
								 wxPD_SMOOTH|wxPD_AUTO_HIDE|wxPD_ELAPSED_TIME|wxPD_ESTIMATED_TIME|wxPD_REMAINING_TIME|wxSTAY_ON_TOP/*/wxPD_CAN_ABORT*/);
	}
	else{
		if(progressDLG->Update(updatePercent)){

			if(updatePercent >= 100){
				delete progressDLG;
				updatePercent = 0;
			}
		}
		else{
			//Here's is where we would stop the download somehow.
		}
	}
}

/////////////////////////////
void Client::SendComputerId()
{
	if (m_sock->IsConnected()){
		//////////////////////////
		unsigned char c = 0xDE;
		m_sock->Write(&c, 1);

		const wxChar *msg1;
		size_t len;

		m_text->AppendText(wxT("Sending Computer ID.\n"));
		m_sock->SetFlags(wxSOCKET_WAITALL);

        //#ifdef WIN32
		msg1 = ConvTowxString(mainPanel->security->diskSerial);
		//#endif 
		//#ifdef MAC
		//msg1 = wxT("Not implemented on MAC");
		//#endif
		#ifdef LINUX
		msg1 = wxT("Not implemented on LINUX");
		#endif
		len  = (wxStrlen(msg1) + 1) * sizeof(wxChar);
		m_sock->WriteMsg(msg1, len);
		m_text->AppendText(m_sock->Error() ? wxT("failed !\n") : wxT("Computer ID Sent.\n"));
	}
}

////////////////////////
void Client::SendEmail()
{
	if (m_sock->IsConnected()){
		//////////////////////////
		unsigned char c = 0xDA;
		m_sock->Write(&c, 1);

		const wxChar *msg1;
		size_t len;

		m_text->AppendText(wxT("Sending Computer ID.\n"));
		m_sock->SetFlags(wxSOCKET_WAITALL);

		//#ifdef MAC
		//msg1 = wxT("Not implemented on MAC");
		//#endif
		#ifdef LINUX
		msg1 = wxT("Not implemented on LINUX");
		#endif
		
		wxString temp = ConvTowxString(mainPanel->security->email);
		
		msg1 = temp.c_str();

		len  = (wxStrlen(msg1) + 1) * sizeof(wxChar);
		m_sock->WriteMsg(msg1, len);
		m_text->AppendText(m_sock->Error() ? wxT("failed !\n") : wxT("Email Sent.\n"));
	}
}

/////////////////////////
void Client::SendOSInfo()
{
	if (m_sock->IsConnected()){

		//m_sock->SetFlags(wxSOCKET_WAITALL);
		//////////////////////////
		unsigned char c = 0xCE;
		m_sock->Write(&c, 1);

		const wxChar *msg1;
		size_t len;

		m_text->AppendText(wxT("Sending OS Information.\n"));
		m_sock->SetFlags(wxSOCKET_WAITALL);

		wxString temp = ::wxGetOsDescription();
		msg1 = temp.c_str();
		len  = (wxStrlen(msg1) + 1) * sizeof(wxChar);
		m_sock->WriteMsg(msg1, len); //FIXME - only sending 1 character on LINUX
		m_text->AppendText(m_sock->Error() ? wxT("failed !\n") : wxT("OS info Sent.\n"));
	}
}

///////////////////////////////
void Client::SendFirstRunTime()
{
//#ifdef WIN32
	if (m_sock->IsConnected()){
		//////////////////////////
		unsigned char c = 0xAE;
		m_sock->Write(&c, 1);

		const wxChar *msg1;
		size_t len;

		m_text->AppendText(wxT("Sending First Run Time.\n"));
		m_sock->SetFlags(wxSOCKET_WAITALL);

		wxString temp;
		temp << mainPanel->security->firstRunTime.GetTicks();
		msg1 = temp.c_str();
		len  = (wxStrlen(msg1) + 1) * sizeof(wxChar);
		m_sock->WriteMsg(msg1, len);
		m_text->AppendText(m_sock->Error() ? wxT("failed !\n") : wxT("First Run Time Sent.\n"));
	}
//#endif
}

//////////////////////////////
void Client::SendLastRunTime()
{
//#ifdef WIN32
	if (m_sock->IsConnected()){
		//////////////////////////
		unsigned char c = 0xBE;
		m_sock->Write(&c, 1);

		const wxChar *msg1;
		size_t len;

		m_text->AppendText(wxT("Sending Last Run Time.\n"));
		m_sock->SetFlags(wxSOCKET_WAITALL);

		wxString temp;
		temp << mainPanel->security->prevLastRunTime.GetTicks();
		msg1 = temp.c_str();
		len  = (wxStrlen(msg1) + 1) * sizeof(wxChar);
		m_sock->WriteMsg(msg1, len);
		m_text->AppendText(m_sock->Error() ? wxT("failed !\n") : wxT("Last Run Time Sent.\n"));
	}
//#endif
}

////////////////////////////////////////////
bool Client::SendErrorReport(wxString *data)
{
	if (m_sock->IsConnected()){
		//////////////////////////
		unsigned char c = 0xAA;
		m_sock->Write(&c, 1);

		const wxChar *msg1;
		size_t len;

		m_text->AppendText(wxT("Sending Error Report.\n"));
		m_sock->SetFlags(wxSOCKET_WAITALL);

		msg1 = data->c_str();
		len  = (wxStrlen(msg1) + 1) * sizeof(wxChar);
		m_sock->WriteMsg(msg1, len);
		if(m_sock->Error()){
			m_text->AppendText(wxT("failed !\n"));
			return 0;
		}
		else{
			m_text->AppendText(wxT("Last Run Time Sent.\n"));
			return 1;
		}
	}
	return 0;
}

////////////////////////////
void Client::InstallUpdate()
{
#ifdef WIN32
	//exporting Updater.exe embeded executable file
	if(::wxFileExists(wxT("updater.exe"))){
		::wxRemoveFile(wxT("updater.exe"));
	}

	::wxSleep(1);

	if(!::wxFileExists(wxT("updater.exe"))){
		wxFile *save = new wxFile(wxT("updater.exe"), wxFile::write);
		
	    save->Write(updater, UPDATER_LEN);

		save->Close();
		delete save;
	}
	else{
		wxMessageBox(wxT("Error: Attempting to create updater.exe before deleting old one."));
	}
#endif //WIN32
		wxProcess temp;
#ifdef MAC
		temp.Open(wxString::Format(wxT("updater.app --WID=%d"), ::wxGetProcessId()), wxEXEC_ASYNC);
#endif //MAC
#ifdef WIN32
		temp.Open(wxString::Format(wxT("updater.exe --WID=%d"), ::wxGetProcessId()), wxEXEC_ASYNC);
#endif //WIN32
		temp.Detach();
}


///////////////////////////////////////////////////////
void Client::OnConnect(wxCommandEvent& WXUNUSED(event))
{
	Connect();
}

///////////////////////////////////////////////////////////////
void Client::OnCloseConnection(wxCommandEvent& WXUNUSED(event))
{
    m_sock->Close();
	m_text->AppendText(wxT("Connection Closed\n"));
}

////////////////////////////////////////////////////////
void Client::OnDownload(wxCommandEvent& WXUNUSED(event))
{
	DownloadFile();
}

////////////////////////////////////////////////
void Client::OnSocketEvent(wxSocketEvent& event)
{
  	if (m_sock->IsConnected()){
        m_text->AppendText(wxT("Connection established\n"));
		SendComputerId();
		mainPanel->security->GetSerialNumberFromFile();
		SendEmail();
		SendOSInfo();
		SendFirstRunTime();
		SendLastRunTime();
        GetLatestVersion(mainPanel->version);
    }
    else
    {
        m_sock->Close();
        m_text->AppendText(wxT("Connection Lost\n"));
    }
}

/////////////////////////////////////////
void Client::OnClose(wxCloseEvent &event)
{
	Hide();
}


void Client::Notify()
{
	if (!m_sock->IsConnected()){
		Connect();
	}
}
