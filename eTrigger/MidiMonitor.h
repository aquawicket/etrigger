//// MidiMonitor.h //////////////////////////////////////////////////////////////
//
//
/////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef MIDIMONITOR_H
#define MIDIMONITOR_H

#include <wx/dialog.h>
#include <wx/listbox.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/stattext.h>


#include "../lib/Gwidgets/GButton/GButton.h"

#include "../Images/Clear.xpm"

/////// MidiMonitor Event ///////////////////
class MidiMonitorEvent: public wxCommandEvent 
{ 
	public: 
		MidiMonitorEvent(wxEventType commandType = wxEVT_NULL, int id = 0 ); 

		wxString GetValue() const { return eventString; } 
		void SetValue(wxString value) { eventString = value; }

		virtual wxEvent *Clone() const { return new MidiMonitorEvent(*this); } // required for sending with wxPostEvent() 

	private: 
		wxString eventString;

	DECLARE_DYNAMIC_CLASS(MidiMonitoEvent) 
}; 

BEGIN_DECLARE_EVENT_TYPES() 
	DECLARE_EVENT_TYPE(wxEVT_COMMAND_MIDIMONITOR, -1) 
END_DECLARE_EVENT_TYPES() 

typedef void (wxEvtHandler::*wxMidiMonitorEventFunction)(MidiMonitorEvent&); 

#define EVT_MIDIMONITOR(id, fn) \
	DECLARE_EVENT_TABLE_ENTRY(wxEVT_COMMAND_MIDIMONITOR, id, -1,  \
	(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)  \
	wxStaticCastEvent(wxMidiMonitorEventFunction, & fn), (wxObject *) NULL ),



////////////////////////////////////
class MidiMonitor : public wxDialog
{
	public:
		MidiMonitor(wxWindow* parent);
		~MidiMonitor();

		void OnPaint(wxPaintEvent &event);
		void OnClose(wxCloseEvent &event);
		void Input(std::vector<unsigned char>& message);
		void OnClear(GButtonEvent &event);
		void SendDataToFile(wxString outData);
		void OnLogToFile(wxCommandEvent &event);
		void OnMidiMonitorEvent(MidiMonitorEvent &event);

		wxPoint position;
		wxSize size;
		bool shown;
		bool logToFile;
		
		wxBoxSizer *mySizer;
		wxListBox *input;

		wxPanel* bottomPanel;
		GButton* clear;
		wxCheckBox *logToFileBox;

	private:
		DECLARE_EVENT_TABLE() 
};


#endif //MIDIMONITOR_H
