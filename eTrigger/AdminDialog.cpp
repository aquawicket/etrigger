//// AdminDialog.cpp /////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "AdminDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

///// CRASH GENERATOR /////////////////////////////////////////////////////////////
static void bar(const wxChar *p){ char *pc = 0;  *pc = *p; printf("bar: %s\n", p);}
void baz(const wxString& s){ printf("baz: %s\n", s.c_str()); }
void foo(int n){ if ( n % 2 ) baz(wxT("odd")); else bar(wxT("even")); }
void CRASH(){ foo(32); foo(17);} //Call CRASH(); to crash the program
///////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
BEGIN_EVENT_TABLE(AdminDialog, wxDialog)
	EVT_BUTTON(100, AdminDialog::OnClient)
	EVT_BUTTON(101, AdminDialog::OnCrash)
END_EVENT_TABLE() 

///////////////////////////////////////////
AdminDialog::AdminDialog(MainPanel *parent) 
      : wxDialog(parent, -1, wxT("Admin"), wxDefaultPosition, wxSize(700, 300), wxDEFAULT_DIALOG_STYLE, wxT(""))
{
	InitVariables();

	mainPanel = parent;
	security = mainPanel->security;
	
	clientButton = new wxButton(this, 100, wxT("eTrigger Client"), wxPoint(10,10), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	crashButton = new wxButton(this, 101, wxT("CRASH eTrigger"), wxPoint(140,10), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
    diskSerial = new wxStaticText(this, -1, wxT(""), wxPoint(10,40), wxDefaultSize, 0, wxT(""));
	
	wxString temp = wxT("Disk Serial: ");
	temp += ConvTowxString(security->diskSerial);
	//wxMessageBox(ConvTowxString(security->diskSerial));
	diskSerial->SetLabel(temp);

	diskSerialEncoded  = new wxStaticText(this, -1, wxT(""), wxPoint(10,60), wxDefaultSize, 0, wxT(""));
	wxString temp2 = wxT("Disk Serial Encoded: ");
	security->Encrypt();
	temp2 += ConvTowxString(security->diskSerialEncoded);
	diskSerialEncoded->SetLabel(temp2);

	serialNumber  = new wxStaticText(this, -1, wxT(""), wxPoint(10,80), wxDefaultSize, 0, wxT(""));
	wxString temp7 = wxT("Serial: ");
	security->GetSerialNumberFromFile();
	temp7 += ConvTowxString(security->serialNumber);
	serialNumber->SetLabel(temp7);

	serialPassed  = new wxStaticText(this, -1, wxT(""), wxPoint(10,100), wxDefaultSize, 0, wxT(""));
	wxString temp10 = wxT("Serial Number Passed: ");
	if(security->IsRegistered()){ temp10 += wxT("TRUE"); }
	else{ temp10 += wxT("FALSE"); }
	serialPassed->SetLabel(temp10);

	currentTime  = new wxStaticText(this, -1, wxT(""), wxPoint(10,120), wxDefaultSize, 0, wxT(""));
	wxString temp3 = wxT("Current Time: ");
	temp3 += ConvTowxString(security->currentTime.GetHour()) += wxT(":");
	temp3 += ConvTowxString(security->currentTime.GetMinute()) += wxT(":");
	temp3 += ConvTowxString(security->currentTime.GetSecond()) += wxT("  ");
	temp3 += ConvTowxString(security->currentTime.GetMonth()+1) += wxT("/");
	temp3 += ConvTowxString(security->currentTime.GetDay()) += wxT("/");
	temp3 += ConvTowxString(security->currentTime.GetYear());
	currentTime->SetLabel(temp3);

	firstRunTime  = new wxStaticText(this, -1, wxT(""), wxPoint(10,140), wxDefaultSize, 0, wxT(""));
	wxString temp4 = wxT("First Run Time: "); 
	temp4 += ConvTowxString(security->firstRunTime.GetHour()) += wxT(":");
	temp4 += ConvTowxString(security->firstRunTime.GetMinute()) += wxT(":");
	temp4 += ConvTowxString(security->firstRunTime.GetSecond()) += wxT("  ");
	temp4 += ConvTowxString(security->firstRunTime.GetMonth()+1) += wxT("/");
	temp4 += ConvTowxString(security->firstRunTime.GetDay()) += wxT("/");
	temp4 += ConvTowxString(security->firstRunTime.GetYear());
	firstRunTime->SetLabel(temp4);

	lastRunTime  = new wxStaticText(this, -1, wxT(""), wxPoint(10,160), wxDefaultSize, 0, wxT(""));
	wxString temp5 = wxT("Last Run Time: "); 
	temp5 += ConvTowxString(security->prevLastRunTime.GetHour()) += wxT(":");
	temp5 += ConvTowxString(security->prevLastRunTime.GetMinute()) += wxT(":");
	temp5 += ConvTowxString(security->prevLastRunTime.GetSecond()) += wxT("  ");
	temp5 += ConvTowxString(security->prevLastRunTime.GetMonth()+1) += wxT("/");
	temp5 += ConvTowxString(security->prevLastRunTime.GetDay()) += wxT("/");
	temp5 += ConvTowxString(security->prevLastRunTime.GetYear());
	lastRunTime->SetLabel(temp5);

	OSinfo = new wxStaticText(this, -1, wxT(""), wxPoint(10,180), wxDefaultSize, 0, wxT(""));
	wxString temp6;
	temp6 += ::wxGetOsDescription();
	if(::wxIsPlatform64Bit()){ temp6 += wxT(" 64bit"); }
	else{ temp6 += wxT(" 32bit"); }

	//temp6 += ::wxGetEmailAddress();
	OSinfo->SetLabel(temp6);

	Show();
}

///////////////////////////
AdminDialog::~AdminDialog()
{
	delete clientButton;
	delete crashButton;
	delete diskSerial;
	delete diskSerialEncoded;
	delete serialNumber;
	delete serialPassed;
	delete currentTime;
	delete firstRunTime;
	delete lastRunTime;
	delete OSinfo;
}

/////////////////////////////////
void AdminDialog::InitVariables()
{
	mainPanel = NULL;
	security = NULL;
	clientButton = NULL;
	crashButton = NULL;
	diskSerial = NULL;
	diskSerialEncoded = NULL;
	serialNumber = NULL;
	serialPassed = NULL;
	currentTime = NULL;
	firstRunTime = NULL;
	lastRunTime = NULL;
	OSinfo = NULL;
}

/////////////////////////////////////////////////
void AdminDialog::OnClient(wxCommandEvent& event)
{
	mainPanel->client->Show();
}


////////////////////////////////////////////////
void AdminDialog::OnCrash(wxCommandEvent& event)
{
	//CRASH();  //This will crash the program for test purposes.
	////////////////////////////////////////////////

	//move mouse
	int x = 10;
    int y = 10;
	double fScreenWidth    = ::GetSystemMetrics( SM_CXSCREEN )-1; 
	double fScreenHeight  = ::GetSystemMetrics( SM_CYSCREEN )-1; 
	double fx = x*(65535.0f/fScreenWidth);
	double fy = y*(65535.0f/fScreenHeight);
	INPUT  Input={0};
	Input.type      = INPUT_MOUSE;
	Input.mi.dwFlags  = MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE;
	Input.mi.dx = fx;
	Input.mi.dy = fy;
	::SendInput(1,&Input,sizeof(INPUT));

	//INPUT
	//Input={0};
    // left mouse down 
    Input.type      = INPUT_MOUSE;
    Input.mi.dwFlags  = MOUSEEVENTF_LEFTDOWN;
    ::SendInput(1,&Input,sizeof(INPUT));

    // left mouse up
    ::ZeroMemory(&Input,sizeof(INPUT));
    Input.type      = INPUT_MOUSE;
    Input.mi.dwFlags  = MOUSEEVENTF_LEFTUP;
    ::SendInput(1,&Input,sizeof(INPUT));
}
