//// MenuPanel.cpp ///////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "MenuPanel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/////////////////////////////////////
BEGIN_EVENT_TABLE(MenuPanel, wxPanel)
    EVT_PAINT(MenuPanel::OnPaint) 
	EVT_GBUTTON(100, MenuPanel::OnFile)
	EVT_GBUTTON(200, MenuPanel::OnView)
	EVT_GBUTTON(300, MenuPanel::OnTracks)
	EVT_GBUTTON(400, MenuPanel::OnDevices)
	EVT_GBUTTON(500, MenuPanel::OnTools)
	EVT_GBUTTON(600, MenuPanel::OnHelp)

	EVT_MENU(101, MenuPanel::OnMenuNew)
	EVT_MENU(102, MenuPanel::OnMenuOpen)
	EVT_MENU(104, MenuPanel::OnMenuSave)
	EVT_MENU(105, MenuPanel::OnMenuSaveAs)
	EVT_MENU(106, MenuPanel::OnMenuExit)
	
	EVT_MENU(201, MenuPanel::OnMenuMinimizeToTray)
	EVT_MENU(202, MenuPanel::OnMenuWindowMode)
	EVT_MENU(203, MenuPanel::OnMenuFullScreen)

	EVT_MENU(301, MenuPanel::OnMenuAddTrigger)
	EVT_MENU(302, MenuPanel::OnMenuAddMidiCC)
	EVT_MENU(303, MenuPanel::OnMenuDeleteTrack)
	EVT_MENU(304, MenuPanel::OnMenuSetupWizard)

	EVT_MENU(401, MenuPanel::OnMenuAudioDevices)
	EVT_MENU(402, MenuPanel::OnMenuMidiDevices)
	EVT_MENU(403, MenuPanel::OnMenuGameDevices)
	
	EVT_MENU(501, MenuPanel::OnMenuStatus)
	EVT_MENU(502, MenuPanel::OnMenuMidiMonitor)
	EVT_MENU(503, MenuPanel::OnMenuPiano)
	EVT_MENU(603, MenuPanel::OnMenuSequencer)
	EVT_MENU(604, MenuPanel::OnMenuSamples)
	EVT_MENU(701, MenuPanel::OnMenuPlayer)
	EVT_MENU(504, MenuPanel::OnMenuOptions)
	EVT_MENU(505, MenuPanel::OnMenuDebug)

	EVT_MENU(601, MenuPanel::OnMenuManual)
	EVT_MENU(602, MenuPanel::OnMenuAbout)
END_EVENT_TABLE() 

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MenuPanel::MenuPanel(MainPanel* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
             :wxPanel(parent, id, pos, size, style, name)
{
	mainPanel = parent;

	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	SetBackgroundColour(wxColour(50,50,50));
	
	file = new GButton(this, 100, wxPoint(0,0), MenuFile_xpm);
	view = new GButton(this, 200, wxPoint(43,0), MenuView_xpm);
	tracks = new GButton(this, 300, wxPoint(99,0), MenuTracks_xpm);
	devices = new GButton(this, 400, wxPoint(169,0), MenuDevices_xpm);
	tools = new GButton(this, 500, wxPoint(249,0), MenuTools_xpm);
	help = new GButton(this, 600, wxPoint(310,0), MenuHelp_xpm);
	tempo = new wxStaticText(this, -1, "0 Bpm", wxPoint(500,5), wxDefaultSize, 0, wxT(""));
	tempo->SetForegroundColour(wxColour(128,128,128,1));

	fileMenu = new wxMenu;
	fileMenu->Append( 101, wxT("New") );
	fileMenu->Append( 102, wxT("Open") );
	fileMenu->Append( 101, wxT("Close") );
	fileMenu->Append( 104, wxT("Save") ); 
	fileMenu->Append( 105, wxT("Save As") );
	#ifndef VST
	fileMenu->Append( 106, wxT("E&xit") );
	#endif //VST

	viewMenu = new wxMenu;
	#ifdef WIN32
	viewMenu->Append( 201, wxT("Minimize to Tray") );
	#endif //WIN32
	viewMenu->Append( 202, wxT("Window Mode") );
	viewMenu->Append( 203, wxT("FullScreen") );

	tracksMenu = new wxMenu;
	tracksMenu->Append(301, wxT("Add Trigger") );
	tracksMenu->Append(302, wxT("Add Midi CC") );
	tracksMenu->Append(303, wxT("Delete Selected Track") );
	tracksMenu->InsertSeparator(3);
	tracksMenu->Append(304, wxT("Setup Wizard") );
	tracksMenu->Enable(303, false);  //start it off disabled
	tracksMenu->Enable(304, false);  //SETUP WIZARD TEMPORARILY DISABLED

	devicesMenu = new wxMenu;
	devicesMenu->Append(401, wxT("Audio Devices") );
	devicesMenu->Append(402, wxT("Midi Devices") );
#ifndef MAC
	devicesMenu->Append(403, wxT("Game Devices") );
#endif //MAC

	toolsMenu = new wxMenu;
	toolsMenu->Append(501, wxT("Status") );
	toolsMenu->Append(502, wxT("Midi Monitor") );
	toolsMenu->Append(503, wxT("Piano") );
	toolsMenu->Append(603, wxT("Sequencer (BETA)") );
	//toolsMenu->Append(604, wxT("Samples") );
	toolsMenu->Append(701, wxT("Player (BETA)") );
	toolsMenu->Append(504, wxT("Options") );	
//#ifdef _DEBUG
	toolsMenu->Append(505, wxT("Debug"));
//#endif

	helpMenu = new wxMenu;
	helpMenu->Append(601, wxT("&Manual") );
	helpMenu->InsertSeparator(1);
	helpMenu->Append(602, wxT("&About eTrigger") );
}

///////////////////////////
MenuPanel::~MenuPanel()
{
	delete fileMenu;
	delete viewMenu;
	delete tracksMenu;
	delete devicesMenu;
	delete toolsMenu;
	delete helpMenu;
}

////////////////////////////////////////////
void MenuPanel::OnPaint(wxPaintEvent& event)
{ 
#ifndef MAC
	SetDoubleBuffered(false);
#endif //!MAC
	wxBufferedPaintDC dc(this); 
	dc.SetBackground(wxColour(50, 50, 50));
	dc.Clear(); 
}

///////////////////////////////////////////
void MenuPanel::OnFile(GButtonEvent &event)
{
	PopupMenu(fileMenu, wxPoint(0,25));
}

///////////////////////////////////////////
void MenuPanel::OnView(GButtonEvent &event)
{
	PopupMenu(viewMenu, wxPoint(43,25));
}

/////////////////////////////////////////////
void MenuPanel::OnTracks(GButtonEvent &event)
{
	PopupMenu(tracksMenu, wxPoint(99,25));
}

//////////////////////////////////////////////
void MenuPanel::OnDevices(GButtonEvent &event)
{
	PopupMenu(devicesMenu, wxPoint(169,25));
}

////////////////////////////////////////////
void MenuPanel::OnTools(GButtonEvent &event)
{
	PopupMenu(toolsMenu, wxPoint(249,25));
}

///////////////////////////////////////////
void MenuPanel::OnHelp(GButtonEvent &event)
{
	PopupMenu(helpMenu, wxPoint(310,25));
}

void MenuPanel::OnMenuNew(wxCommandEvent &event){mainPanel->OnMenuNew(event);}
void MenuPanel::OnMenuOpen(wxCommandEvent &event){mainPanel->OnMenuOpen(event);}
void MenuPanel::OnMenuSave(wxCommandEvent &event){mainPanel->OnMenuSave(event);}
void MenuPanel::OnMenuSaveAs(wxCommandEvent &event){mainPanel->OnMenuSaveAs(event);}
void MenuPanel::OnMenuExit(wxCommandEvent &event){mainPanel->OnMenuExit(event);}
void MenuPanel::OnMenuWindowMode(wxCommandEvent &event){mainPanel->OnMenuWindowMode(event);}
void MenuPanel::OnMenuFullScreen(wxCommandEvent &event){mainPanel->OnMenuFullScreen(event);}
void MenuPanel::OnMenuMinimizeToTray(wxCommandEvent &event){mainPanel->OnMenuMinimizeToTray(event);}
void MenuPanel::OnMenuAddTrigger(wxCommandEvent &event){mainPanel->OnMenuAddTrigger(event);}
void MenuPanel::OnMenuAddMidiCC(wxCommandEvent &event){mainPanel->OnMenuAddMidiCC(event);}
void MenuPanel::OnMenuDeleteTrack(wxCommandEvent &event){mainPanel->OnMenuDeleteTrack(event);}
void MenuPanel::OnMenuSetupWizard(wxCommandEvent &event){mainPanel->OnMenuSetupWizard(event);}
void MenuPanel::OnMenuAudioDevices(wxCommandEvent &event){mainPanel->OnMenuAudioDevices(event);}
void MenuPanel::OnMenuMidiDevices(wxCommandEvent &event){mainPanel->OnMenuMidiDevices(event);}
void MenuPanel::OnMenuGameDevices(wxCommandEvent &event){mainPanel->OnMenuGameDevices(event);}
void MenuPanel::OnMenuStatus(wxCommandEvent &event){mainPanel->OnMenuStatus(event);}
void MenuPanel::OnMenuMidiMonitor(wxCommandEvent &event){mainPanel->OnMenuMidiMonitor(event);}
void MenuPanel::OnMenuPiano(wxCommandEvent &event){mainPanel->OnMenuPiano(event);}
void MenuPanel::OnMenuSequencer(wxCommandEvent &event){mainPanel->OnMenuSequencer(event);}
void MenuPanel::OnMenuSamples(wxCommandEvent &event){mainPanel->OnMenuSamples(event);}
void MenuPanel::OnMenuPlayer(wxCommandEvent &event){mainPanel->OnMenuPlayer(event);}
void MenuPanel::OnMenuDebug(wxCommandEvent &event){mainPanel->OnMenuDebug(event);}
void MenuPanel::OnMenuOptions(wxCommandEvent &event){mainPanel->OnMenuOptions(event);}
void MenuPanel::OnMenuManual(wxCommandEvent &event){mainPanel->OnMenuManual(event);}
void MenuPanel::OnMenuAbout(wxCommandEvent &event){mainPanel->OnMenuAbout(event);}
