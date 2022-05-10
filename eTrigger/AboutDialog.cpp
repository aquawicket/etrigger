//// AboutDialog.cpp //////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "AboutDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

////////////////////////////////////////
BEGIN_EVENT_TABLE(AboutDialog, wxDialog)
	EVT_GBUTTON      (203, AboutDialog::OnOk)
	EVT_GBUTTON      (204, AboutDialog::OnCancel)
	EVT_GBUTTON      (205, AboutDialog::OnRegister)
	EVT_GBUTTON      (206, AboutDialog::OnSendDetailReport)
END_EVENT_TABLE()

///////////////////////////////////////////
AboutDialog::AboutDialog(MainPanel *parent)
      : wxDialog(parent, -1, wxT("About eTrigger"), wxDefaultPosition, wxSize(250, 300), wxCAPTION | wxCLOSE_BOX)
{
	InitVariables();

	mainPanel = parent;
	trackProc = mainPanel->trackProc;
	security = mainPanel->security;

	CentreOnScreen(wxBOTH);

#ifdef WIN32 ///////////////////////////////
	SetBackgroundColour(wxColour(90,90,90));
#endif //WIN32 /////////////////////////////
#ifdef MAC ////////////////////////////////////////////////////////////////////////////////
	wxPanel *background = new wxPanel(this, -1, wxPoint(0,0), this->GetSize(), 0, wxT(""));
	background->SetBackgroundColour(wxColour(90,90,90));
#endif //MAC //////////////////////////////////////////////////////////////////////////////
	
	logo = new Logo(this, -1, wxPoint(20,10), logoSmall_xpm);
	wxStaticText *version = new wxStaticText(this, -1, mainPanel->version, wxPoint(180,65), wxDefaultSize, 0, wxT(""));
	website = new wxHyperlinkCtrl(this, -1, wxT("www.eTrigger.net"), wxT("http://www.eTrigger.net"), wxPoint(82, 180), wxDefaultSize, wxHL_DEFAULT_STYLE, wxT(""));
	wxStaticText *copywright = new wxStaticText(this, -1, wxT("Copywrite 2013 Aquawicket"), wxPoint(55,195), wxDefaultSize, 0, wxT(""));

	security->GetSerialNumberFromFile();
	security->IsExtended();

	if(!security->IsRegistered()){
		wxString temp = ConvTowxString(security->trialDays);
		wxStaticText *trialText = new wxStaticText(this, -1, temp += wxString(wxT(" DAY TRIAL")), wxPoint(90,80), wxDefaultSize, 0, wxT(""));
		wxStaticText *trialText2 = new wxStaticText(this, -1, ConvTowxString(security->GetTrialDaysLeft()) += wxT(" days left"), wxPoint(90,100), wxDefaultSize, 0, wxT(""));
		registerButton = new GButton(this, 205, wxPoint(85, 120), register_xpm, register_hover_xpm, register_click_xpm); 
	}
	else{
		wxStaticText *trialText = new wxStaticText(this, -1, wxT("Registered to"), wxPoint(85,120), wxDefaultSize, 0, wxT(""));
		wxStaticText *trialText2 = new wxStaticText(this, -1, ConvTowxString(security->email), wxPoint(5,140), wxSize(240, 20), wxALIGN_CENTRE, wxT(""));
	}

	sendDetailReport = new GButton(this, 206, wxPoint(52, 215), sendReport_xpm, sendReport_hover_xpm, sendReport_click_xpm); 
	ok = new GButton(this, 203, wxPoint(50, 245), ok_xpm, ok_hover_xpm, ok_click_xpm); 
	cancel = new GButton(this, 204, wxPoint(122, 245), cancel_xpm, cancel_hover_xpm, cancel_click_xpm);
}

///////////////////////////
AboutDialog::~AboutDialog()
{
	//delete logo;
	delete registerButton;
	delete sendDetailReport;
	delete ok;
	delete cancel;
	delete website;
}

/////////////////////////////////
void AboutDialog::InitVariables()
{
	mainPanel = NULL;
	security = NULL;
	trackProc = NULL;
	logo = NULL;
	registerButton = NULL;
	sendDetailReport = NULL;
	ok = NULL;
	cancel = NULL;
	website = NULL;
}

///////////////////////////////////////////
void AboutDialog::OnOk(GButtonEvent &event)
{
	Hide();
}

///////////////////////////////////////////////
void AboutDialog::OnCancel(GButtonEvent &event)
{
	Hide();
}

/////////////////////////////////////////////////
void AboutDialog::OnRegister(GButtonEvent &event)
{
	//mainPanel->Hide();
	RegisterDlg *registerDlg = new RegisterDlg(mainPanel);
	registerDlg->ShowModal();
}

/////////////////////////////////////////////////////////
void AboutDialog::OnSendDetailReport(GButtonEvent &event)
{
	wxString details = mainPanel->details->GetDetails();
	mainPanel->client->SendErrorReport(&details);
	wxMessageBox(wxT("Detail Report Sent"));
}



///////////////////////////////
BEGIN_EVENT_TABLE(Logo, GImage)
	EVT_KEY_DOWN(Logo::OnKeyDown)
END_EVENT_TABLE()

//////////////////////////////////////////////////////////////////////////////////////
Logo::Logo(AboutDialog* parent, wxWindowID id, const wxPoint& pos, const char** image)
	 :GImage(parent, id, pos, image)
{
	aboutDialog = parent;
	adminDialog = NULL;
}

///////////////////////////////////////
void Logo::OnKeyDown(wxKeyEvent &event)
{
	KeyHistory(event.GetKeyCode());
}


///////////////////////////////
void Logo::KeyHistory(char key)
{
	//first shift all over 1
	for(int i=19; i>0; i--){
		keyHistory[i] = keyHistory[i-1];
	}
	
	//add new key
	keyHistory[0] = key;

	//check history for admin code
	if(KeyB::KeyToString(keyHistory[18]) == wxT("A")){ 
	if(KeyB::KeyToString(keyHistory[17]) == wxT("Q")){ 
	if(KeyB::KeyToString(keyHistory[16]) == wxT("U")){ 
	if(KeyB::KeyToString(keyHistory[15]) == wxT("A")){ 
	if(KeyB::KeyToString(keyHistory[14]) == wxT("W")){ 
	if(KeyB::KeyToString(keyHistory[13]) == wxT("I")){ 
	if(KeyB::KeyToString(keyHistory[12]) == wxT("C")){ 
	if(KeyB::KeyToString(keyHistory[11]) == wxT("K")){ 
	if(KeyB::KeyToString(keyHistory[10]) == wxT("E")){ 
	if(KeyB::KeyToString(keyHistory[9])  == wxT("T")){ 
	if(KeyB::KeyToString(keyHistory[8])  == wxT("2")){ 
	if(KeyB::KeyToString(keyHistory[7])  == wxT("3")){ 
	if(KeyB::KeyToString(keyHistory[6])  == wxT("9")){ 
	if(KeyB::KeyToString(keyHistory[5])  == wxT("3")){ 
	if(KeyB::KeyToString(keyHistory[4])  == wxT("1")){ 
	if(KeyB::KeyToString(keyHistory[3])  == wxT("1")){ 
	if(KeyB::KeyToString(keyHistory[2])  == wxT("5")){ 
	if(KeyB::KeyToString(keyHistory[1])  == wxT("2")){ 
	if(KeyB::KeyToString(keyHistory[0])  == wxT("0")){ 
		if(adminDialog ==  NULL){ 
			adminDialog = new AdminDialog(aboutDialog->mainPanel);
			adminDialog->Show();
			adminDialog->SetFocus();
		}
		else{
			adminDialog->Show();
			adminDialog->SetFocus();
		}
	}}}}}}}}}}}}}}}}}}}
}