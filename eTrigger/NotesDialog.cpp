//// NotesDialog.cpp /////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "NotesDialog.h"

////////////////////////////////////////
BEGIN_EVENT_TABLE(NotesDialog, wxDialog)
	EVT_CHECKBOX(100,NotesDialog::OnStartUpBox) 
END_EVENT_TABLE()

///////////////////////////////////////////
NotesDialog::NotesDialog(MainPanel *parent) 
         : wxDialog(NULL, -1, wxT("eTrigger Version Notes"), wxDefaultPosition, wxSize(500, 510), wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER/* | wxSTAY_ON_TOP*/, wxT(""))
{
	mainPanel = parent;

	#ifdef WIN32
	SetIcon(wxICON(APPICON));
	#endif //WIN32

	mySizer = new wxBoxSizer(wxVERTICAL);
	text = new wxListBox(this, -1, wxPoint(5,10), wxSize(480, 440), 0, NULL, 0, wxDefaultValidator, wxT(""));

	bottomPanel = new wxPanel(this, -1, wxPoint(0,0), wxSize(500,50), 0, wxT(""));
	onStartUp = new wxCheckBox(bottomPanel, 100, wxT("Show Version Notes On Startup"), wxPoint(10, 10), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	onStartUp->SetValue(mainPanel->versionNotes);
	SetNotes();

	mySizer->Add(text, 1, wxEXPAND, 0);
	mySizer->Add(bottomPanel, 0, wxEXPAND, 0);
	mySizer->SetItemMinSize(bottomPanel, 500, 40);
	SetSizer( mySizer );
}

/////////////////////////////////////////////////////
void NotesDialog::OnStartUpBox(wxCommandEvent &event)
{
	mainPanel->versionNotes = onStartUp->GetValue();
}

////////////////////////////
void NotesDialog::SetNotes()
{	
	text->InsertItems(1, &wxString(wxT("* PLEASE REPORT ANY BUGS OR CRASHES.")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("")), text->GetCount());
	
	text->InsertItems(1, &wxString(wxT("eTrigger 0.520")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("---------------------")), text->GetCount());
    text->InsertItems(1, &wxString(wxT("Multiple instances are now allowed, but with caution.")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("")), text->GetCount());

	text->InsertItems(1, &wxString(wxT("eTrigger 0.517")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("---------------------")), text->GetCount());
    text->InsertItems(1, &wxString(wxT("Windows version trial period reset for all users.")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("Mac version is now compatable with intel and ppc machines.")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("Mac version trial period reset for all users.")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("")), text->GetCount());

	text->InsertItems(1, &wxString(wxT("eTrigger 0.515")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("---------------------")), text->GetCount());
    text->InsertItems(1, &wxString(wxT("Fixed bug in Midi Monitor.")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("")), text->GetCount());

	text->InsertItems(1, &wxString(wxT("eTrigger 0.513")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("---------------------")), text->GetCount());
    text->InsertItems(1, &wxString(wxT("Fixed bug in track meters.")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("")), text->GetCount());

	text->InsertItems(1, &wxString(wxT("eTrigger 0.511")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("---------------------")), text->GetCount());
    text->InsertItems(1, &wxString(wxT("Many code changes to increase speed and stability.")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("Fixed learning signal bug.")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("Fixed a few multi-threading bugs.")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("Added overlap setting to Sequence Output.")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("")), text->GetCount());
	
	text->InsertItems(1, &wxString(wxT("eTrigger 0.438")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("---------------------")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("Fixed INT_DIVIDE_BY_ZERO bug")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("")), text->GetCount());

	text->InsertItems(1, &wxString(wxT("eTrigger 0.437")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("---------------------")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("Fixed crash while setting up tracks")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("Fixed the main window scrollbar")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("Fixed Updater, should work from now on")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("Uninstaller will no longer remove user created files.")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("Fixed some small bugs")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("")), text->GetCount());

	text->InsertItems(1, &wxString(wxT("eTrigger 0.436")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("---------------------")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("Added sequence output ability to trigger tracks. (BETA)")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("Fixed some small bugs")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("")), text->GetCount());

	text->InsertItems(1, &wxString(wxT("eTrigger 0.435")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("---------------------")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("Removed number indicator under meters, caused to many crashes.")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("Worked out sample rate conversion. Needed in upcomming features.")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("Added mp3 decoder. Neede in upcomming features.")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("Worked more on the Sound Output Controller. Needed in upcomming features.")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("Worked more on trainer/game mode. Needed in upcomming features.")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("Fixed a few small bugs.")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("")), text->GetCount());
	
	text->InsertItems(1, &wxString(wxT("eTrigger 0.434")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("---------------------")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("* Fixed 2 bugs that cause crashes in multi-zone triggers.")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("* Fixed a few small bugs and more code cleanup.")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("")), text->GetCount());
	
	text->InsertItems(1, &wxString(wxT("eTrigger 0.433b")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("---------------------")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("* Made TONS of code changes and cleanups all throughout eTrigger.")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("* Added drum type selection to tracks. Required for upcomming feature.")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("* Learning retrigger and multizone waittime now end automatically when windows closes.")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("* eTrigger now uses the OpenGL library for an upcomming feature.")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("* Fixed error report sender.")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("* Fixed common crashing bug when playing multi-zone triggers.")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("* Removed Error in Process::Retrigger popup.")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("* Added latency reports to status window.")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("* Arror keys now work on knobs.")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("* Optimized some of the programm loop in eTrigger for better performance.")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("* Removed some cpu intensive code in the output stage for better performance.")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("* Fixed track data variable code, should fix a few random bugs and crashes.")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("")), text->GetCount());

	text->InsertItems(1, &wxString(wxT("eTrigger 0.432b")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("---------------------")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("* Kit's and data files will now be compatable with new versions.")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("* Updater will only ask to update to newest release.")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("")), text->GetCount());

	text->InsertItems(1, &wxString(wxT("eTrigger 0.431b")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("---------------------")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("* Added Center On Screen to the tray icon to restore lost eTrigger window.")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("* MultiZone WaitTime now has and auto-detect feature.")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("* Note Off signals are now enabled by default.")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("* Joysticks with the same name will now work correctly .")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("* Fixed DancePad Up and Left buttons to their own button number .")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("* DancePad button releases now triggers the correct direction.")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("* Added Average monitor to MultiZone panel. Used to monitor hot spots in the future.")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("* Added Velocity Balance to MultiZone panel, NO EFFECT YET.")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("* Fixed trigger track limiters in dynamics panel.")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("")), text->GetCount());
	text->InsertItems(1, &wxString(wxT("")), text->GetCount());
}
