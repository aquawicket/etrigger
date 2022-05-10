//// MidiDev.cpp ///////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "MidiDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

///////////////////////////////////////
BEGIN_EVENT_TABLE(MidiDialog, wxDialog)
	EVT_GBUTTON(203, MidiDialog::OnOk)
	EVT_GBUTTON(204, MidiDialog::OnCancel)
	EVT_CLOSE(       MidiDialog::OnClose) 
END_EVENT_TABLE() 

/////////////////////////////////
MidiDialog::MidiDialog(Midi *ref)
	: wxDialog(NULL, -1, wxT("Midi Devices"), wxDefaultPosition, wxSize(435, 210), wxDEFAULT_DIALOG_STYLE)
{
	midi = ref;

	CentreOnScreen(wxBOTH);

#ifdef WIN32
	SetBackgroundColour(wxColour(90,90,90));
#endif //WIN32
#ifdef MAC
	wxPanel *background = new wxPanel(this, -1, wxPoint(0,0), this->GetSize(), 0, wxT(""));
	background->SetBackgroundColour(wxColour(90,90,90));
#endif //MAC
	
	wxStaticText *midiInText = new wxStaticText(this, -1, wxT("Midi Input"), wxPoint(20,5), wxDefaultSize, 0, wxT(""));
	wxStaticText *midiOutText = new wxStaticText(this, -1, wxT("Midi Output"), wxPoint(230,5), wxDefaultSize, 0, wxT(""));

	midiIn = new wxListBox(this, -1, wxPoint(10,20), wxSize(200,120), NULL, NULL,wxLB_MULTIPLE, wxDefaultValidator,"");
	midiIn->SetBackgroundColour( wxColor(30,30,30));
	midiIn->SetForegroundColour( wxColor(200,200,200)); 

	midiOut = new wxListBox(this, -1, wxPoint(220,20), 
							wxSize(200,120), NULL, NULL,wxLB_MULTIPLE, wxDefaultValidator);
	midiOut->SetBackgroundColour( wxColor(30,30,30));
	midiOut->SetForegroundColour( wxColor(200,200,200)); 

	ok = new GButton(this, 203, wxPoint(278, 150), ok_xpm, ok_hover_xpm, ok_click_xpm); 
	cancel = new GButton(this, 204, wxPoint(350, 150), cancel_xpm, cancel_hover_xpm, cancel_click_xpm);

	VarsToDlg();
	IsMidiPatchDriverInstalled();
}

////////////////////////////
void MidiDialog::VarsToDlg()
{
	midiIn->Clear();
	midiIn->InsertItems( midi->GetInDevices(), 0);
	midiOut->Clear();
	midiOut->InsertItems( midi->GetOutDevices(), 0);

	for(unsigned int i=0; i<midi->selectedIn.GetCount(); ++i){
		midiIn->SetStringSelection(midi->selectedIn.Item(i));
	}
	for(unsigned int i=0; i<midi->selectedOut.GetCount(); ++i){
		midiOut->SetStringSelection(midi->selectedOut.Item(i));
	}
}

/////////////////////////
MidiDialog::~MidiDialog()
{

}

//////////////////////////////////////////
void MidiDialog::OnOk(GButtonEvent &event)
{
	/// Midi Input Devices ///
	midi->StopCallback();
	wxArrayInt inSelections;
	wxArrayString inStrings;
	midiIn->GetSelections(inSelections);
	for(unsigned int i=0; i<inSelections.GetCount(); ++i){
		inStrings.Add( midiIn->GetString( (int)inSelections.Item(i) ), 1);
	}
	midi->SetInDevices(inStrings);	
	midi->StartCallback();

	/// Midi Output Devices ///
	wxArrayInt outSelections;
	wxArrayString outStrings;
	midiOut->GetSelections(outSelections);
	for(unsigned int i=0; i<outSelections.GetCount(); ++i){
		outStrings.Add( midiOut->GetString( (int)outSelections.Item(i) ), 1);
	}
	midi->SetOutDevices(outStrings);	

    Hide();
}

//////////////////////////////////////////////
void MidiDialog::OnCancel(GButtonEvent &event)
{
	Close();
}

/////////////////////////////////////////////
void MidiDialog::OnClose(wxCloseEvent &event)
{
	VarsToDlg();
	Hide();
}

/////////////////////////////////////////////
void MidiDialog::IsMidiPatchDriverInstalled()
{
	bool hasDriver = 0;
	for(unsigned int i=0; i<midiOut->GetCount(); ++i){
		if(midiOut->GetString(i) == wxT("LoopBe Internal MIDI")){
			hasDriver = 1;
		}
		if(midiOut->GetString(i) == wxT("Out To MIDI Yoke: 1")){
			hasDriver = 1;
		}
		if(midiOut->GetString(i) == wxT("Maple Midi Out: Port 1")){
			hasDriver = 1;
		}
	}

	if(hasDriver == 0){
		NoMidiDriverDialog *noMidiDriverDialog = NULL;
		noMidiDriverDialog = new NoMidiDriverDialog();
		noMidiDriverDialog->Show();
		noMidiDriverDialog->SetFocus();
	}
}



///////////////////////////////////////////////
BEGIN_EVENT_TABLE(NoMidiDriverDialog, wxDialog)
	EVT_GBUTTON      (303, NoMidiDriverDialog::OnOk)
	EVT_GBUTTON      (304, NoMidiDriverDialog::OnCancel)
	EVT_HYPERLINK    (300, NoMidiDriverDialog::OnHyperlink1)
	EVT_HYPERLINK    (301, NoMidiDriverDialog::OnHyperlink2)
	EVT_HYPERLINK    (302, NoMidiDriverDialog::OnHyperlink3)
END_EVENT_TABLE()

////////////////////////////////////////
NoMidiDriverDialog::NoMidiDriverDialog()
      : wxDialog(NULL, -1, wxT("No Midi Output Drivers Installed"), wxDefaultPosition, wxSize(300, 300), wxCAPTION | wxCLOSE_BOX | wxSTAY_ON_TOP)
{
	InitVariables();

	CentreOnScreen(wxBOTH);

#ifdef WIN32 ///////////////////////////////
	SetBackgroundColour(wxColour(90,90,90));
#endif //WIN32 /////////////////////////////
#ifdef MAC ////////////////////////////////////////////////////////////////////////////////
	wxPanel *background = new wxPanel(this, -1, wxPoint(0,0), this->GetSize(), 0, wxT(""));
	background->SetBackgroundColour(wxColour(90,90,90));
#endif //MAC //////////////////////////////////////////////////////////////////////////////
	
	wxStaticText *text1 = new wxStaticText(this, -1, wxT("There are no Midi Patch Drivers Installed"), wxPoint(10,10), wxDefaultSize, 0, wxT(""));
	wxStaticText *text2 = new wxStaticText(this, -1, wxT("To enable eTrigger to send midi to other software,"), wxPoint(10,30), wxDefaultSize, 0, wxT(""));
	wxStaticText *text3 = new wxStaticText(this, -1, wxT("You need to install one of the Midi Output Drivers."), wxPoint(10,50), wxDefaultSize, 0, wxT(""));
	link1 = new wxHyperlinkCtrl(this, 300, wxT("LoopBe1 (recommended)"), wxT("http://nerds.de/data/setuploopbe1.exe"), wxPoint(10, 90), wxDefaultSize, wxHL_DEFAULT_STYLE, wxT(""));
	link1->SetNormalColour(*wxWHITE);
	link2 = new wxHyperlinkCtrl(this, 301, wxT("MidiYoke"), wxT("http://www.midiox.com/zip/MidiYokeSetup.msi"), wxPoint(10, 110), wxDefaultSize, wxHL_DEFAULT_STYLE, wxT(""));
	link2->SetNormalColour(*wxWHITE);
	link3 = new wxHyperlinkCtrl(this, 302, wxT("Maple Virtual Midi Cable "), wxT("http://www.maplemidi.com/MapleVMCv356.zip"), wxPoint(10, 130), wxDefaultSize, wxHL_DEFAULT_STYLE, wxT(""));
	link3->SetNormalColour(*wxWHITE);
	wxStaticText *text4 = new wxStaticText(this, -1, wxT("Please restart eTrigger after installation."), wxPoint(10,170), wxDefaultSize, 0, wxT(""));
	ok = new GButton(this, 303, wxPoint(50, 245), ok_xpm, ok_hover_xpm, ok_click_xpm); 
	cancel = new GButton(this, 304, wxPoint(122, 245), cancel_xpm, cancel_hover_xpm, cancel_click_xpm);
}

/////////////////////////////////////////
NoMidiDriverDialog::~NoMidiDriverDialog()
{
	delete ok;
	delete cancel;
	delete link1;
	delete link2;
	delete link3;
}

////////////////////////////////////////
void NoMidiDriverDialog::InitVariables()
{
	ok = NULL;
	cancel = NULL;
	link1 = NULL;
	link2 = NULL;
	link3 = NULL;
}

//////////////////////////////////////////////////
void NoMidiDriverDialog::OnOk(GButtonEvent &event)
{
	Hide();
	Destroy();
}

//////////////////////////////////////////////////////
void NoMidiDriverDialog::OnCancel(GButtonEvent &event)
{
	Hide();
	Destroy();
}

/////////////////////////////////////////////////////////////
void NoMidiDriverDialog::OnHyperlink1(wxHyperlinkEvent &event)
{
	Hide();
	Destroy();
	::wxLaunchDefaultBrowser(wxT("http://nerds.de/data/setuploopbe1.exe"),0);
}

/////////////////////////////////////////////////////////////
void NoMidiDriverDialog::OnHyperlink2(wxHyperlinkEvent &event)
{
	Hide();
	Destroy();
	::wxLaunchDefaultBrowser(wxT("http://www.midiox.com/zip/MidiYokeSetup.msi"),0);
}

/////////////////////////////////////////////////////////////
void NoMidiDriverDialog::OnHyperlink3(wxHyperlinkEvent &event)
{
	Hide();
	Destroy();
	::wxLaunchDefaultBrowser(wxT("http://www.maplemidi.com/MapleVMCv356.zip"),0);
}
