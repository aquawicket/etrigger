/// Server.cpp /////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "server.h"



//Thread class----------------------        
class ServerThread : public wxThread
{                                   //class containing server thread
    MyFrame*   m_pServer;  //Our server
    wxSocketBase* m_pSocket;        //The client socket for read/write ops
	int ID;
	unsigned char c;
public:
    ServerThread(MyFrame* pServer, wxSocketBase* pSocket, int socketID, unsigned char code) :
            m_pServer(pServer), m_pSocket(pSocket), ID(socketID), c(code) {}
    ~ServerThread() { }

    virtual ExitCode Entry()        //on run entry method
    {
  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  //Put all You want this thread to do !
   
   
   //--------- start chat
    //m_pServer->ServerChat(m_pSocket);
    //chat end
		switch (c)
		{
			case 0xCE: m_pServer->RecieveOSInfo(m_pSocket, ID); Delete(); break;
			case 0xDE: m_pServer->RecieveComputerId(m_pSocket, ID); Delete(); break;
			case 0xDA: m_pServer->RecieveEmail(m_pSocket, ID); Delete(); break;
			case 0xEE: m_pServer->SendFile(m_pSocket); Delete(); break;
			case 0xFE: m_pServer->SendVersion(m_pSocket); Delete(); break;
			case 0xAE: m_pServer->RecieveFirstRunTime(m_pSocket, ID); Delete(); break;
			case 0xBE: m_pServer->RecieveLastRunTime(m_pSocket, ID); Delete(); break;
			case 0xAA: m_pServer->RecieveErrorReport(m_pSocket, ID); Delete(); break;
			default:
			m_pServer->m_text->AppendText(wxT("\nUNKNOWN EVENT ID SENT FROM CLIENT\n"));
			Delete();
		}
   
   
        return 0;
    }
    
    virtual void OnExit() {         //on thread exit method
   //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   //put here what will thread do on exit
   
    }
}; 


//////////////////////////////////////
BEGIN_EVENT_TABLE(MyFrame, wxFrame)
  EVT_MENU(wxID_EXIT,  MyFrame::OnQuit)
  EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
  EVT_MENU(10, MyFrame::OnUpdateVersion)
  EVT_MENU(11, MyFrame::OnMinimizeToTray)
  EVT_SOCKET(SERVER_ID,  MyFrame::OnServerEvent)
  EVT_SOCKET(-1,  MyFrame::OnSocketEvent)
END_EVENT_TABLE()

///////////////////////////////////////////////////////////////////////////////////////////////////////////
MyFrame::MyFrame() : wxFrame((wxFrame *)NULL, wxID_ANY, wxT("eTrigger Server"), wxDefaultPosition, wxSize(800, 600))
{
	#ifdef WIN32
	SetIcon(wxICON(APPICON));
    #endif //WIN32
	
	m_menuFile = new wxMenu();
	m_menuFile->Append(wxID_ABOUT, wxT("&About...\tCtrl-A"));
	m_menuFile->AppendSeparator();
	m_menuFile->Append(wxID_EXIT, wxT("E&xit\tAlt-X"));
	m_menuFile->Append(10, wxT("Update Version"));
	m_menuView = new wxMenu();
	m_menuView->Append(11, wxT("Minimize To Tray"));
	m_menuBar = new wxMenuBar();
	m_menuBar->Append(m_menuFile, wxT("&File"));
	m_menuBar->Append(m_menuView, wxT("&View"));
	SetMenuBar(m_menuBar);

#if wxUSE_STATUSBAR
	// Status bar
	CreateStatusBar(3);
#endif // wxUSE_STATUSBAR

	mySizer = new wxBoxSizer(wxHORIZONTAL);

	LoadVersionFromFile();

	m_text  = new wxTextCtrl(this, wxID_ANY, wxT("eTrigger Server Started\n"), wxPoint(0,0), wxSize(200, 500), wxTE_MULTILINE | wxTE_READONLY);
	mySizer->Add(m_text, 0, wxEXPAND, 0);

	wxIPV4address addr;
	addr.Service(3000);

	m_server = new wxSocketServer(addr);

	// We use Ok() here to see if the server is really listening
	if (! m_server->Ok()){
		m_text->AppendText(wxT("\nCOULD NOT LISTEN ON PORT\n"));
		return;
	}
	else{
		m_text->AppendText(wxT("Server listening.\n\n"));
	}

	// Setup the event handler and subscribe to connection events
	m_server->SetEventHandler(*this, SERVER_ID);
	m_server->SetNotify(wxSOCKET_CONNECTION_FLAG);
	m_server->Notify(true);

	m_busy = false;

	userData = new UserData(this, *this);
	UpdateStatusBar();
	SetSizer( mySizer );

	//Create Tray Icon
	trayIcon = new TrayIcon(this);
}

///////////////////
MyFrame::~MyFrame()
{
    delete m_server;
    delete userData;
	//trayIcon->RemoveIcon();
	delete trayIcon;
}

/////////////////////////////////////////////////////
void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	SaveVersionToFile();
    Close(true);
}

//////////////////////////////////////////////////////
void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
  wxMessageBox( wxT("eTrigger Server 0.307b\n"), wxT("About eTrigger Server"), wxOK | wxICON_INFORMATION, this);
}

//////////////////////////////////////////////////////
void MyFrame::OnUpdateVersion(wxCommandEvent& (event))
{
   versionDlg = new VersionDlg(this);
   versionDlg->Show();
}

///////////////////////////////////////////////////////
void MyFrame::OnMinimizeToTray(wxCommandEvent& (event))
{
	MinimizeToTray();
}


/////////////////////////////////////////////
void MyFrame::SendVersion(wxSocketBase *sock)
{
	const wxChar *msg1;
	size_t len;

	m_text->AppendText(wxT("Client requested version info.\n"));
	//sock->SetFlags(wxSOCKET_BLOCK);

	msg1 = version.c_str();
	len  = (wxStrlen(msg1) + 1) * sizeof(wxChar);
	sock->WriteMsg(msg1, len);
	if(sock->Error()){
		m_text->AppendText(wxT("\nERROR SENDING VERSION INFO\n"));
	}
	else{
		m_text->AppendText(wxT("Version Info sent.\n"));
	}
}

//////////////////////////////////////////
void MyFrame::SendFile(wxSocketBase *sock)
{
  m_text->AppendText(wxT("Client requested update file.\n"));

  //sock->SetFlags(wxSOCKET_WAITALL);

  // Write it back
  //Does the file exists?
  char *buf;
  int bufSize;

    //We need to send this in a non Blocking way
	if(wxFile::Exists(wxT("eTrigger-Update.zip"))){
		wxFile *open = new wxFile(wxT("eTrigger-Update.zip"), wxFile::read);
		if(open->IsOpened()){
			if(!open->Eof()){
				buf = new char[open->Length()];
				bufSize = open->Read(buf, open->Length());
			}
			open->Close();
		}
		delete open;

		sock->Write(&bufSize, sizeof(bufSize));
		m_text->AppendText(wxString::Format(wxT("Sending Update File - %d bytes\n"), bufSize));
		
		wxFile *file = new wxFile(wxT("eTrigger-Update.zip"), wxFile::read);
		//sock->SetFlags(wxSOCKET_WAITALL);
        int bytes = 0;
		int b = 0;

		while (bytes<bufSize)
		{
			b = file->Read(buf, 10*1024);
			sock->Write(&b, sizeof(b)); //send byte header
			sock->Write(buf, b);
			if (sock->Error()){			
               m_text->AppendText(wxT("\nERROR SENDING UPDATE\n"));
               break;
			}
       
			bytes += b;
		}
		file->Close();
		delete file;
		
		
		m_text->AppendText(wxT("File Sent Successfully\n"));
		delete[] buf;
	}
	else{
		m_text->AppendText(wxT("\neTrigger-Update.zip MISSING !!!\n"));
	}  
}

///////////////////////////////////////////////////
void MyFrame::RecieveComputerId(wxSocketBase *sock, int socketID)
{
	#define MAX_MSG_SIZE 10000

	wxString s;
	wxChar *buf = new wxChar[MAX_MSG_SIZE];
	//wxUint32 len;

	//sock->SetFlags(wxSOCKET_BLOCK | wxSOCKET_WAITALL );

	sock->ReadMsg(buf, MAX_MSG_SIZE * sizeof(wxChar));

	if(sock->Error()){
		m_text->AppendText(wxT("\nERROR RECIEVING COMPUTER ID\n"));
	}
	else{
		wxString pcID = buf;
		m_text->AppendText(wxT("Recieved Computer ID.\n"));

		userData->SetComputerId(socketID, pcID);
	}

	delete[] buf;

	#undef MAX_MSG_SIZE
}

////////////////////////////////////////////////////////////
void MyFrame::RecieveEmail(wxSocketBase *sock, int socketID)
{
	#define MAX_MSG_SIZE 10000

	wxString s;
	wxChar *buf = new wxChar[MAX_MSG_SIZE];
	wxUint32 len;

	//sock->SetFlags(wxSOCKET_WAITALL);

	len = sock->ReadMsg(buf, MAX_MSG_SIZE * sizeof(wxChar)).LastCount();

	if(sock->Error()){
		m_text->AppendText(wxT("\nERROR RECIEVING EMAIL\n"));
	}
	else{
		wxString email = buf;
		m_text->AppendText(wxT("Recieved Email.\n"));

		userData->SetEmail(socketID, email);
	}

	delete[] buf;

	#undef MAX_MSG_SIZE
}

/////////////////////////////////////////////////////////////
void MyFrame::RecieveOSInfo(wxSocketBase *sock, int socketID)
{
	#define MAX_MSG_SIZE 10000

	wxString s;
	wxChar *buf = new wxChar[MAX_MSG_SIZE];
	wxUint32 len;

	//sock->SetFlags(wxSOCKET_WAITALL);

	len = sock->ReadMsg(buf, MAX_MSG_SIZE * sizeof(wxChar)).LastCount();

	if(sock->Error()){
		m_text->AppendText(wxT("\nERROR RECIEVING OS INFO\n"));
	}
	else{
		wxString pcOS = buf;
		m_text->AppendText(wxT("Recieved OS Information.\n"));

		userData->SetComputerOS(socketID, pcOS);
	}

	delete[] buf;

	#undef MAX_MSG_SIZE
}

///////////////////////////////////////////////////////////////////
void MyFrame::RecieveFirstRunTime(wxSocketBase *sock, int socketID)
{
	#define MAX_MSG_SIZE 10000

	wxString s;
	wxChar *buf = new wxChar[MAX_MSG_SIZE];
	wxUint32 len;

	//sock->SetFlags(wxSOCKET_WAITALL);

	len = sock->ReadMsg(buf, MAX_MSG_SIZE * sizeof(wxChar)).LastCount();

	if(sock->Error()){
		m_text->AppendText(wxT("\nERROR RECIEVING FIRST RUN TIME\n"));
	}
	else{
		wxString pcFirstRunTime = buf;
		m_text->AppendText(wxT("Recieved First Run Time.\n"));
	
		userData->SetFirstRunTime(socketID, pcFirstRunTime);
	}

	delete[] buf;

	#undef MAX_MSG_SIZE
}

//////////////////////////////////////////////////////////////////
void MyFrame::RecieveLastRunTime(wxSocketBase *sock, int socketID)
{
	#define MAX_MSG_SIZE 10000

	wxString s;
	wxChar *buf = new wxChar[MAX_MSG_SIZE];
	wxUint32 len;

	//sock->SetFlags(wxSOCKET_WAITALL);

	len = sock->ReadMsg(buf, MAX_MSG_SIZE * sizeof(wxChar)).LastCount();

	if(sock->Error()){
		m_text->AppendText(wxT("\nERROR RECIEVING LAST RUN TIME\n"));
	}
	else{
		wxString pcLastRunTime = buf;
		m_text->AppendText(wxT("Recieved Last Run Time.\n"));

		userData->SetLastRunTime(socketID, pcLastRunTime);
	}
	delete[] buf;

	#undef MAX_MSG_SIZE
}

//////////////////////////////////////////////////////////////////
void MyFrame::RecieveErrorReport(wxSocketBase *sock, int socketID)
{
	#define MAX_MSG_SIZE 100000

	wxString s;
	wxChar *buf = new wxChar[MAX_MSG_SIZE];
	wxUint32 len;

	//sock->SetFlags(wxSOCKET_WAITALL);

	len = sock->ReadMsg(buf, MAX_MSG_SIZE * sizeof(wxChar)).LastCount();

	if(sock->Error()){
		m_text->AppendText(wxT("\nERROR RECIEVING DEBUG REPORT\n"));
	}
	else{
		wxString errorReport = buf;
		m_text->AppendText(wxT("Recieved Debug Report.\n"));

		if(!WriteErrorReportToFile(errorReport, socketID)){
			m_text->AppendText(wxT("\nERROR WRITING DEBUG REPORT TO FILE\n"));
		}
	}

	delete[] buf;

	#undef MAX_MSG_SIZE
}

/////////////////////////////////////////////////////////////////
bool MyFrame::WriteErrorReportToFile(wxString data, int socketID)
{
	wxString filename;
	filename = userData->client[socketID].computerId;

	if(!::wxDirExists(wxT(".\\ErrorReports"))){
		::wxMkdir(wxT(".\\ErrorReports"), 0777);
	}

	wxString temp;
	for(int i=0; i<1000; ++i){
		temp = wxT(".\\ErrorReports\\");
		temp += filename;
		temp += wxString::Format(wxT("(%d)"), i);
		temp += wxT(".txt");
		if(!::wxFileExists(temp)){
			filename = temp;
			break;
		}
	}

	//If by chance the user has submited over 1000 error reports. 
	//the rest will be overwritten into a computerID.noextention file over and over.

	wxFile* save = new wxFile(filename, wxFile::write);
	if(save->IsOpened()){
		save->Write(data);
		save->Close();
		delete save;
		return true;
	}

	return false;
}

/////////////////////////////////////////////////
void MyFrame::OnServerEvent(wxSocketEvent& event)
{


  switch(event.GetSocketEvent())
  {
    case wxSOCKET_CONNECTION : /*m_text->AppendText(wxT("wxSOCKET_CONNECTION\n"));*/ break;
    default                  : m_text->AppendText(wxT("\nUNEXPECTED EVENT !!!\n")); break;
  }

  // Accept new connection if there is one in the pending
  // connections queue, else exit. We use Accept(false) for
  // non-blocking accept (although if we got here, there
  // should ALWAYS be a pending connection).

  userData->AcceptConnection(m_server);

  if(userData->AddClient())
  {
    m_text->AppendText(_("New client connection accepted\n"));
  }
  else
  {
    m_text->AppendText(_("\nERROR: COULD NOT ACCEPT NEW CONNECTION\n"));
    return;
  }

  UpdateStatusBar();
}

/////////////////////////////////////////////////
void MyFrame::OnSocketEvent(wxSocketEvent& event)
{
  wxSocketBase *sock = event.GetSocket();

  // First, print a message
  switch(event.GetSocketEvent())
  {
    case wxSOCKET_INPUT : /*m_text->AppendText(wxT("wxSOCKET_INPUT\n"));*/ break;
    case wxSOCKET_LOST  : /*m_text->AppendText(wxT("wxSOCKET_LOST\n"));*/ break;
    default             : m_text->AppendText(wxT("\nUNEXPECTED EVENT !!!\n")); break;
  }

  // Now we process the event
  switch(event.GetSocketEvent())
  {
    case wxSOCKET_INPUT:
    {
      // We disable input events, so that the test doesn't trigger
      // wxSocketEvent again.
      sock->SetNotify(wxSOCKET_LOST_FLAG);

      // Which action did the client request?
      unsigned char c;
      sock->Read(&c, 1);

	  //ServerThread* pThread = new ServerThread(this, sock, event.GetId(), c);        
      //pThread->Create();                   
      //pThread->Run();
	  
	  
      switch (c)
      {
	    case 0xCE: RecieveOSInfo(sock, event.GetId()); break;
		case 0xDE: RecieveComputerId(sock, event.GetId()); break;
		case 0xDA: RecieveEmail(sock, event.GetId()); break;
		case 0xFE: SendVersion(sock); break;
		case 0xAE: RecieveFirstRunTime(sock, event.GetId()); break;
		case 0xBE: RecieveLastRunTime(sock, event.GetId()); break;
		case 0xAA: RecieveErrorReport(sock, event.GetId()); break;
		case 0xEE:{ ServerThread* pThread = new ServerThread(this, sock, event.GetId(), c);        
				   pThread->Create();                   
				   pThread->Run(); break;}
        default:
          m_text->AppendText(wxT("\nUNKNOWN EVENT ID SENT FROM CLIENT\n"));
      }
	  
	  


      // Enable input events again.
      sock->SetNotify(wxSOCKET_LOST_FLAG | wxSOCKET_INPUT_FLAG);
      break;
    }
    case wxSOCKET_LOST:
    {
		
      // Destroy() should be used instead of delete wherever possible,
      // due to the fact that wxSocket uses 'delayed events' (see the
      // documentation for wxPostEvent) and we don't want an event to
      // arrive to the event handler (the frame, here) after the socket
      // has been deleted. Also, we might be doing some other thing with
      // the socket at the same time; for example, we might be in the
      // middle of a test or something. Destroy() takes care of all
      // this for us.
	
      m_text->AppendText(wxT("Deleting socket.\n\n"));
	  
	  userData->RemoveClient(event.GetId());

      break;
    }
    default: ;
  }

  UpdateStatusBar();
}

/////////////////////////////////
void MyFrame::SaveVersionToFile()
{
	//If the file does not exist, it will create it. 
	wxFile* save = new wxFile(wxT("version.txt"), wxFile::write);
	if(save->IsOpened()){
		
		int strlength = version.length();
		save->Write(&strlength, sizeof(strlength));
		save->Write(version);

		save->Close();
		delete save;
	}
}

///////////////////////////////////
void MyFrame::LoadVersionFromFile()
{
	//Does the file exists?
	if(wxFile::Exists(wxT("version.txt"))){
		wxFile *open = new wxFile(wxT("version.txt"), wxFile::read);
		if(open->IsOpened()){
			if(!open->Eof()){
				int strlength;
				open->Read(&strlength, sizeof(strlength));
				char *cha = new char[strlength + 1];
				open->Read(cha, strlength);	cha[strlength] = 0;
				//FIXME
				//wxString str = Conv(cha);
				wxString str = cha;
				delete[] cha;

				version = str;
			}
			else{
				wxMessageBox(wxT("Error: version.txt is empty"));
			}
			open->Close();
		}
		delete open;
	}
	else{
		wxMessageBox(wxT("Error: version.txt does not exist"));
	}
}

///////////////////////////////
void MyFrame::UpdateStatusBar()
{
#if wxUSE_STATUSBAR
	wxString s;
	wxString v;
	s.Printf(wxT("%d clients connected"), userData->numClients);
	v.Printf(wxT("Current eTrigger Version: %s"), version);
	SetStatusText(s, 2);
	SetStatusText(v, 1);
#endif // wxUSE_STATUSBAR
}

//////////////////////////////
void MyFrame::MinimizeToTray()
{
	Hide();
}
///////////////////////////////
void MyFrame::RestoreFromTray()
{
	Show();
}



//////////////////////////////////////
BEGIN_EVENT_TABLE(VersionDlg, wxDialog)
	EVT_BUTTON(101, VersionDlg::OnUpdate) 
	EVT_BUTTON(102, VersionDlg::OnCancel) 
END_EVENT_TABLE()

//////////////////////////////////////////////////////////////////////////////////////////////////////////
VersionDlg::VersionDlg(wxWindow *parent) 
           : wxDialog(parent, -1, wxT("eTrigger Version"), wxDefaultPosition, wxSize(180,70), 0, wxT(""))
{
	par = (MyFrame*)parent;
	version = new wxTextCtrl(this, 100, par->version, wxPoint(40,10), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
    update = new wxButton(this, 101, wxT("Update"), wxPoint(10, 40), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	close = new wxButton(this, 102, wxT("Close"), wxPoint(90, 40), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
}

////////////////////////////////////////////////
void VersionDlg::OnUpdate(wxCommandEvent &event)
{
	par->version = version->GetValue();
	par->UpdateStatusBar();
	par->SaveVersionToFile();
}

////////////////////////////////////////////////
void VersionDlg::OnCancel(wxCommandEvent &event)
{
	Destroy();
}







