//// MidiMonitor.cpp ////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "MidiMonitor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


///////// MidiMonitor Event ////////////////
DEFINE_EVENT_TYPE(wxEVT_COMMAND_MIDIMONITOR) 
IMPLEMENT_DYNAMIC_CLASS(MidiMonitorEvent, wxCommandEvent) 

/////////////////////////////////////////////////////////////////////////////////////////
MidiMonitorEvent::MidiMonitorEvent(wxEventType commandType, int id) : wxCommandEvent(commandType, id) 
{ 
} 



////////////////////////////////////////
BEGIN_EVENT_TABLE(MidiMonitor, wxDialog)
	EVT_GBUTTON(100, MidiMonitor::OnClear)
	EVT_PAINT(MidiMonitor::OnPaint) 
	EVT_CLOSE(MidiMonitor::OnClose)
	EVT_CHECKBOX(101, MidiMonitor::OnLogToFile)
	EVT_MIDIMONITOR(-1, MidiMonitor::OnMidiMonitorEvent)
END_EVENT_TABLE() 

/////////////////////////////////////////////////////////////////////////////
MidiMonitor::MidiMonitor(wxWindow* parent) 
	:wxDialog(parent, -1, wxT("Midi Monitor"), wxDefaultPosition, wxSize(400, 400), 
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
	input = new wxListBox(this, -1, wxPoint(10,100), wxSize(200,400), NULL,NULL, wxLB_MULTIPLE, wxDefaultValidator);
	input->SetBackgroundColour(wxColour(30,30,30));
	input->SetForegroundColour(wxColour(99,99,99));
	#ifdef WIN32
	input->Connect(-1, wxEVT_MOUSEWHEEL, wxMouseEventHandler(StatusDialog::OnMouseWheel), NULL, this);
	#endif

	bottomPanel = new wxPanel(this, -1, wxPoint(0,0), wxSize(400,50), 0, wxT(""));
	bottomPanel->SetBackgroundColour(wxColour(99,99,99));
	clear = new GButton(bottomPanel, 100, wxPoint(20,10), clear_xpm);
	logToFileBox = new wxCheckBox(bottomPanel, 101, wxT("Log To File"), wxPoint(150, 10), wxDefaultSize, 0, wxDefaultValidator, wxT(""));

	mySizer->Add(input, 1, wxEXPAND, 0);
	mySizer->Add(bottomPanel, 0, wxEXPAND, 0);
	mySizer->SetItemMinSize(bottomPanel, 400, 40);
	SetSizer( mySizer );
}

///////////////////////////
MidiMonitor::~MidiMonitor()
{

}

//////////////////////////////////////////////
void MidiMonitor::OnClear(GButtonEvent &event)
{
	input->Clear();
}

////////////////////////////////////////////////////////////
void MidiMonitor::Input(std::vector<unsigned char>& message)
{
	wxString temp;
	for(unsigned int i=0; i<message.size(); ++i){
		temp += wxString::Format(wxT("%d "), message[i]);
	}
	input->InsertItems(1, &temp, input->GetCount());

	if(input->GetCount() > 100){input->Delete(0);}
	input->ScrollPages(4);

	wxString temp2;
	temp2 = temp + wxT("\n");
	SendDataToFile(temp2);
}

//////////////////////////////////////////////
void MidiMonitor::OnPaint(wxPaintEvent &event)
{
	shown = true;
	#ifdef WIN32
	position = GetScreenPosition();
	#endif
	#ifdef MAC
	position = GetPosition();
	#endif
	size = GetSize();
	event.Skip();
}

//////////////////////////////////////////////
void MidiMonitor::OnClose(wxCloseEvent &event)
{
	shown = false;
	event.Skip();
}

////////////////////////////////////////////////////
void MidiMonitor::OnLogToFile(wxCommandEvent &event)
{
	logToFile = logToFileBox->GetValue();
}

//////////////////////////////////////////////////
void MidiMonitor::SendDataToFile(wxString outData)
{
	if(logToFile){
		wxFile* save = new wxFile(wxT("midiLog.txt"), wxFile::write_append);
		if(save->IsOpened()){
			save->Write(outData += wxT(""), wxConvUTF8);
			save->Close();
			delete save;
		}
	}
}

/////////////////////////////////////////////////////////////
void MidiMonitor::OnMidiMonitorEvent(MidiMonitorEvent &event)
{
	input->InsertItems(1, &event.GetValue(), input->GetCount());

	if(input->GetCount() > 100){input->Delete(0);}
	input->ScrollPages(4);

	wxString temp2;
	temp2 = event.GetValue() + wxT("\n");
	SendDataToFile(temp2);
}
