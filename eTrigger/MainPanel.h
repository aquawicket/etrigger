//// MainPanel.h /////////////////////////////////////////////////////////////////////////////
//
// Main's job is CENTRAL CONTROL of EVERYTHING :(
//
/////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef MAINPANEL_H
#define MAINPANEL_H

#ifdef VST
#include "../eTriggerVST/wxVST.h"
#include "../eTriggerVST/eTriggerVST.h"

class EtriggerEditor;
class wxVstPanel;
#endif //VST

#include <wx/frame.h>  
#include <wx/dcbuffer.h>
#include <wx/file.h>
#include <wx/filedlg.h>
#include <wx/menu.h>
#include <wx/msgdlg.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/tooltip.h>
#include <wx/zipstrm.h>
#include <wx/hyperlink.h>
#include <wx/panel.h>

#include "../lib/Gwidgets/GScrollBar/GScrollBar.h"
#include "../lib/Gwidgets/GHelper/GHelper.h"

#include "AboutDialog.h"
#include "Audio.h"
#include "AudioDialog.h"
#include "Details.h"
#include "Joystick.h"
#include "JoystickDialog.h"
#include "MidiCC.h"
#include "Midi.h"
#include "MidiDialog.h"
#include "Network.h"
#include "NotesDialog.h"
#include "OptionsDialog.h"
#include "PianoDialog.h"
#include "Security.h"
#include "Samples.h"
#include "SampleDialog.h"
#include "StatusDialog.h"
#include "MidiMonitor.h"
#include "Tracks.h"
#include "MenuPanel.h"
#include "Trigger.h"
#include "Wizard.h"
#include "SequencerDialog.h"
#include "SequencePlayer.h"
#include "Tray.h"
#include "MainFrame.h"
#include "DebugDialog.h"
#include "EtmFile.h"
#include "EtmEditorDialog2.h"
#include "EtmPlayerDialog.h"


class AboutDialog;
class Audio;
class AudioDialog;
class Client;
class DebugDialog;
class Details;
//class EtmEditorDialog;
class EtmPlayerDialog;
class EtmEditorDialog2;
class GScrollBar;
class Joystick;
class JoystickDialog;
class Midi;
class MidiDialog;
class OptionsDialog;
class PianoDialog;
class Security;
class MenuBar;
class MidiMonitor;
class NetTimer;
class TrackPanel;
class TrayIcon;
class SequencerDialog;
class SequencePlayer;
class GTimer;


///////////////////////////////
#ifndef VST
class MainPanel: public wxPanel
{ 
#endif //!VST
	
#ifdef VST
class MainPanel: public wxVstPanel
{ 
#endif //VST

	public: 
		#ifdef VST
		MainPanel( wxVstEditor* );
		bool Create( wxWindow* parent, wxWindowID id = 10005, const wxPoint& pos = wxPoint(0,0), const wxSize& size = wxSize(640, 480), long style = 0 );
		virtual void setParameter (long index, float value);
		virtual float getParameter (long index);
		#endif //VST

		#ifndef VST
		MainPanel(MainFrame* parent, wxString ver, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name);
		#endif //!VST
		
		~MainPanel();
		void InitVariables();
	
		void OnMenuNew(wxCommandEvent &event);
		void OnMenuOpen(wxCommandEvent &event);
		void OnMenuSave(wxCommandEvent &event);
		void OnMenuSaveAs(wxCommandEvent &event);
		void OnMenuExit(wxCommandEvent &event);
		void OnMenuWindowMode(wxCommandEvent &event);
		void OnMenuFullScreen(wxCommandEvent &event);
		void OnMenuAddTrigger(wxCommandEvent &event);
		void OnMenuAddMidiCC(wxCommandEvent &event);
		void OnMenuDeleteTrack(wxCommandEvent &event);
		void OnMenuSetupWizard(wxCommandEvent &event);
		void OnMenuAudioDevices(wxCommandEvent &event);
		void OnMenuMidiDevices(wxCommandEvent &event);
		void OnMenuGameDevices(wxCommandEvent &event);
		void OnMenuStatus(wxCommandEvent &event);
		void OnMenuMidiMonitor(wxCommandEvent &event);
		void OnMenuPiano(wxCommandEvent &event);
		void OnMenuSequencer(wxCommandEvent &event);
		void OnMenuSamples(wxCommandEvent &event);
		void OnMenuPlayer(wxCommandEvent &event);
		void OnMenuDebug(wxCommandEvent &event);
		void OnMenuOptions(wxCommandEvent &event);
		void OnMenuManual(wxCommandEvent &event);
		void OnMenuAbout(wxCommandEvent &event);
		void SaveMainSettings();
		void LoadMainSettings();
		bool SaveVarsToFile(bool saveAs); //FIXME - this function should belong to TrackProc
		void GetVarsFromFile(wxString path, wxString filename); //FIXME - this function should belong to TrackProc
		bool FileIsValid(wxString ver);
		void StoreSaveData(); //FIXME - this function should belong to TrackProc
		bool CheckForSave(); //FIXME - this function should belong to TrackProc
		void OnMouse(wxMouseEvent &event);
		void OnKeyDown(wxKeyEvent &event);
		void OnMinimize();
		void OnMaximize(wxMaximizeEvent& event);
		void OnMenuMinimizeToTray(wxCommandEvent &event);
		void RestoreFromTray();
		void OnClose(wxCloseEvent &event);
		void OnIdle(wxIdleEvent &event);
		void OnSize(wxSizeEvent& event);
		void OnGScrollBar(GScrollBarEvent &event); 
		void UpdateScroll();
		
		#ifdef VST
		EtriggerEditor* par;
		#endif //VST

		#ifndef VST
		MainFrame *par;
		#endif //!VST

		wxBoxSizer *topSizer;
		MenuPanel *menuPanel;
    	TrackPanel *trackPanel;

		GScrollBar *scrollbar;
		
		//Dialog Classes
		DebugDialog *debugDialog;
		AudioDialog *audioDialog;
		MidiDialog *midiDialog;	
		JoystickDialog *joystickDialog;
		StatusDialog *statusDialog;
		MidiMonitor *midiMonitor;
		wxDialog *closeDLG;
		OptionsDialog *optionsDialog;
		AboutDialog *aboutDialog;
		NotesDialog *notesDialog;
		Details *details;
		PianoDialog *pianoDialog;
		SequencerDialog *sequencerDialog;
		EtmFile *etmFile;
		EtmEditorDialog2 *etmEditorDialog2;
		EtmPlayerDialog *etmPlayerDialog;
		WizardDlg *wizardDlg;
		SampleDialog *sampleDialog;

		//Other?
		Client *client;
		NetTimer *netTimer;
		Process *process;
		SequencePlayer *sequencePlayer;

		//Communication Classes
		TrackProc *trackProc;
		Midi *midi;
		Audio *audio;
		SoundController *soundController;
		Samples *samples;
		Joystick *joystick;
		Security *security;

		//GUI Renderer Timer
		GTimer *gTimer;

		//File data
		wxString fileDirectory;
		wxString fileName;
		TrackProc *saveData; //used to store "save check" data

		//Other Variables
		wxString version;
		bool splashScreen;
		int idleMarker;
		bool toolTips;
		bool versionNotes;
		wxString initPath;
		wxString initFilename;

		//Tray Icon
		TrayIcon *trayIcon;
		
		//Event Handler
		DECLARE_EVENT_TABLE();
};

#endif //MAINPANEL_H
