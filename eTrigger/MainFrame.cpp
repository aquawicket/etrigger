//// MainFrame.cpp ///////////////////////////////////////////////////////////
//
//
/////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "MainFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// MyFrame //////////////////////////////////
BEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_MOVE	     (MainFrame::OnMove)
END_EVENT_TABLE() 

///////////////////////////////////////////////////////////////////////////////////////////////
MainFrame::MainFrame(wxWindow* parent, const wxString& title, long style, wxString ver) 
		: wxFrame(parent, -1, title, wxDefaultPosition, wxSize(800, 570), wxDEFAULT_FRAME_STYLE)
{ 
    #ifdef WIN32
	SetIcon(wxICON(APPICON));
    #endif //WIN32

	wxIdleEvent::SetMode(wxIDLE_PROCESS_SPECIFIED);
	
	//Version and Frame Title
	version = ver;
	wxString temp = wxString(wxT("eTrigger ")) += version;
	SetTitle(temp);
	
	//Size and Postition
	frameSize = GetSize();
	#ifndef MAC
	framePosition = GetScreenPosition();
	#endif
	#ifdef MAC
	framePosition = GetPosition();
	#endif
	SetMinSize(wxSize(100,30));

	//MainPanel
	mainPanel = new MainPanel(this, version, wxID_ANY, wxPoint(0,0), wxSize(frameSize.x, frameSize.y), wxBORDER_NONE, wxT("mainPanel"));
}

////////////////////////////////////////

///////////////////////
MainFrame::~MainFrame() 
{ 
	Hide();
	DestroyChildren(); //just in case
	Destroy(); //just in case
}

////////////////////////////////////////
void MainFrame::OnMove(wxMoveEvent &event)
{
	#ifndef MAC
	framePosition = GetScreenPosition();
	#endif
	#ifdef MAC
	framePosition = GetPosition();
	#endif
	event.Skip();
}
