//// JoystickDialog.cpp ///////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "JoystickDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

///////////////////////////////////
BEGIN_EVENT_TABLE(JoystickDialog, wxDialog)
	EVT_GBUTTON(203, JoystickDialog::OnOk)
	EVT_GBUTTON(204, JoystickDialog::OnCancel)
	EVT_CLOSE(       JoystickDialog::OnClose) 
END_EVENT_TABLE() 


/////////////////////////////////////////////
JoystickDialog::JoystickDialog(Joystick *ref)
	:wxDialog(NULL, -1, wxT("Game Devices"), wxDefaultPosition, wxSize(230, 210), wxDEFAULT_DIALOG_STYLE)
{
	joystick = ref;

	CentreOnScreen(wxBOTH);

#ifdef WIN32
	SetBackgroundColour(wxColour(90,90,90));
#endif //WIN32
#ifdef MAC
	wxPanel *background = new wxPanel(this, -1, wxPoint(0,0), this->GetSize(), 0, wxT(""));
	background->SetBackgroundColour(wxColour(90,90,90));
#endif //MAC

	joys = new wxListBox(this, -1, wxPoint(10,20), wxSize(200,120), NULL, NULL, wxLB_MULTIPLE, wxDefaultValidator);
	joys->SetBackgroundColour( wxColor(30,30,30));
	joys->SetForegroundColour( wxColor(200,200,200)); 

	ok = new GButton(this, 203, wxPoint(68, 150), ok_xpm, ok_hover_xpm, ok_click_xpm); 
	cancel = new GButton(this, 204, wxPoint(140, 150), cancel_xpm, cancel_hover_xpm, cancel_click_xpm);

	VarsToDlg();
}

////////////////////////////////
void JoystickDialog::VarsToDlg()
{
	joys->Clear();
	joys->InsertItems( joystick->GetDevices(), 0);

	for(unsigned int i=0; i<joystick->selected.GetCount(); ++i){
		joys->SetStringSelection(joystick->selected.Item(i));
	}
}

//////////////////////////////////////////////
void JoystickDialog::OnOk(GButtonEvent &event)
{
	wxArrayInt inSelections;
	wxArrayString inStrings;
	joys->GetSelections(inSelections);
	for(unsigned int i=0; i<inSelections.GetCount(); ++i){
		inStrings.Add( joys->GetString( (int)inSelections.Item(i) ), 1);
	}

	joystick->SetDevices(inStrings);

	Hide();
}

//////////////////////////////////////////////////
void JoystickDialog::OnCancel(GButtonEvent &event)
{
	Close();
}

/////////////////////////////////////////////////
void JoystickDialog::OnClose(wxCloseEvent &event)
{
	VarsToDlg();
	Hide();
}
