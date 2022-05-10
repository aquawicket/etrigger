//// StatusDialog.cpp /////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "StatusDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


///////// StatusDialog Event ////////////////
DEFINE_EVENT_TYPE(wxEVT_COMMAND_STATUSDIALOG) 
IMPLEMENT_DYNAMIC_CLASS(StatusDialogEvent, wxCommandEvent) 

/////////////////////////////////////////////////////////////////////////////////////////
StatusDialogEvent::StatusDialogEvent(wxEventType commandType, int id) : wxCommandEvent(commandType, id) 
{ 
} 


/////////////////////////////////////
BEGIN_EVENT_TABLE(StatusDialog, wxDialog)
	EVT_GBUTTON(100, StatusDialog::OnClear)
	EVT_CHECKBOX(101, StatusDialog::OnLogToFile) 
	EVT_MOUSEWHEEL(StatusDialog::OnMouseWheel)
	EVT_SIZE(StatusDialog::OnSize) 
	EVT_MOVE(StatusDialog::OnMove)
	EVT_CLOSE(StatusDialog::OnClose)
	EVT_STATUSDIALOG(-1, StatusDialog::OnStatusDialogEvent)
END_EVENT_TABLE() 

/////////////////////////////////////////////////////////////////////////////
StatusDialog::StatusDialog(wxWindow* parent) 
	:wxDialog(parent, -1, wxT("Status"), wxDefaultPosition, wxSize(398, 482), 
	 wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER )
{
	CentreOnScreen(wxBOTH);
	#ifdef WIN32
	position = GetScreenPosition();
	#endif
	#ifdef MAC
	position = GetPosition();
	#endif
	size = GetSize();
	shown = IsShown();

	mySizer = new wxBoxSizer(wxVERTICAL);
	mySizer2 = new wxBoxSizer(wxHORIZONTAL);
	mySizer3 = new wxBoxSizer(wxHORIZONTAL);
	input = new wxListBox(this, -1, wxPoint(10,100), wxSize(200,400), NULL, NULL, wxLB_MULTIPLE, wxDefaultValidator);
	output = new wxListBox(this, -1, wxPoint(300,100), wxSize(200,400), NULL, NULL, wxLB_MULTIPLE, wxDefaultValidator);
	input->SetBackgroundColour(wxColour(30,30,30));
	input->SetForegroundColour(wxColour(99,99,99));
	#ifdef WIN32
	input->Connect(-1, wxEVT_MOUSEWHEEL, wxMouseEventHandler(StatusDialog::OnMouseWheel), NULL, this);
	#endif
	output->SetBackgroundColour(wxColour(30,30,30));
	output->SetForegroundColour(wxColour(99,99,99));
	#ifdef WIN32
	output->Connect(-1, wxEVT_MOUSEWHEEL, wxMouseEventHandler(StatusDialog::OnMouseWheel), NULL, this);
	#endif

	textPanel = new wxPanel(this, -1, wxPoint(0,0), wxSize(400,25), 0, wxT(""));
	textPanel->SetBackgroundColour(wxColour(99,99,99));
	textPanel2 = new wxPanel(this, -1, wxPoint(0,0), wxSize(400,25), 0, wxT(""));
	textPanel2->SetBackgroundColour(wxColour(99,99,99));
	inputText = new wxStaticText(textPanel, -1, wxT("Input"), wxPoint(10,3), wxDefaultSize, 0, wxT(""));
	outputText = new wxStaticText(textPanel2, -1, wxT("Output"), wxPoint(10,3), wxDefaultSize, 0, wxT(""));

	bottomPanel = new wxPanel(this, -1, wxPoint(0,0), wxSize(400,50), 0, wxT(""));
	bottomPanel->SetBackgroundColour(wxColour(99,99,99));
	clear = new GButton(bottomPanel, 100, wxPoint(20,10), clear_xpm);
	logToFileBox = new wxCheckBox(bottomPanel, 101, wxT("Log To File"), wxPoint(200, 10), wxDefaultSize, 0, wxDefaultValidator, wxT(""));

	mySizer->Add(mySizer2, 0, wxEXPAND, 0);
	mySizer->Add(mySizer3, 1, wxEXPAND, 0);
	mySizer->Add(bottomPanel, 0, wxEXPAND, 0);
	mySizer2->Add(textPanel, 1, wxEXPAND, 0);
	mySizer2->Add(textPanel2, 1, wxEXPAND, 0);
	mySizer3->Add(input, 1, wxEXPAND, 0);
	mySizer3->Add(output, 1, wxEXPAND, 0);

	mySizer2->SetItemMinSize(textPanel, 1, 20);
	mySizer2->SetItemMinSize(textPanel2, 1, 20);
	mySizer->SetItemMinSize(bottomPanel, 400, 40);
	SetSizer( mySizer );
}

///////////////////////
StatusDialog::~StatusDialog()
{

}

////////////////////////////////////////////
void StatusDialog::OnClear(GButtonEvent &event)
{
	input->Clear();
	output->Clear();
}

//////////////////////////////////////////////////
void StatusDialog::OnLogToFile(wxCommandEvent &event)
{
	logToFile = logToFileBox->GetValue();
}

///////////////////////////////////////////
void StatusDialog::Input(const wxString &temp)
{

	input->InsertItems(1, &temp, input->GetCount());
	if(input->GetCount() > 100){input->Delete(0);}
	input->ScrollPages(4);

	wxString temp2;
	temp2 = temp + wxT("\n");
	SendStatusToFile(temp2);
}

////////////////////////////////////////////
void StatusDialog::Output(const wxString &temp)
{
	output->InsertItems(1, &temp, output->GetCount());
	if(output->GetCount() > 100){output->Delete(0);}
	output->ScrollPages(4);

    wxString temp2;
	temp2 = temp + wxT("\n");
	SendStatusToFile(temp2);
}

/////////////////////////////////////////////////
void StatusDialog::OnMouseWheel(wxMouseEvent &event)
{	
	//don't let the event trickle down to the parent.
}

//////////////////////////////////////////
void StatusDialog::OnSize(wxSizeEvent &event)
{
	shown = IsShown();
	#ifdef WIN32
	position = GetScreenPosition();
	#endif
	#ifdef MAC
	position = GetPosition();
	#endif
	size = GetSize();
	event.Skip();
}

//////////////////////////////////////////
void StatusDialog::OnMove(wxMoveEvent &event)
{
	shown = IsShown();
	#ifdef WIN32
	position = GetScreenPosition();
	#endif
	#ifdef MAC
	position = GetPosition();
	#endif
	size = GetSize();
	event.Skip();
}

////////////////////////////////////////////
void StatusDialog::OnClose(wxCloseEvent &event)
{
	shown = false;
	event.Skip();
}


////////////////////////////////////////////////////
void StatusDialog::SendStatusToFile(wxString outStatus)
{
	if(logToFile){
		wxFile* save = new wxFile(wxT("statusLog.txt"), wxFile::write_append);
		if(save->IsOpened()){
			save->Write(outStatus += wxT(""), wxConvUTF8);
			save->Close();
			delete save;
		}
	}

}


////////////////////////////////////////////////////////////////
void StatusDialog::OnStatusDialogEvent(StatusDialogEvent &event)
{
	if(event.GetInOut() == 1){
		Input(event.GetValue());
	}
	if(event.GetInOut() == 2){
		Output(event.GetValue());
	}
	
}