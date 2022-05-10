//// StatusDialog.h /////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef STATUSDIALOG_H
#define STATUSDIALOG_H

#include <wx/dialog.h>
#include <wx/listbox.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/stattext.h>
#include <wx/checkbox.h>

#include "../lib/Gwidgets/GButton/GButton.h"

#include "../Images/Clear.xpm"


/////// StatusDialog Event ///////////////////
class StatusDialogEvent: public wxCommandEvent 
{ 
	public: 
		StatusDialogEvent(wxEventType commandType = wxEVT_NULL, int id = 0 ); 

		wxString GetValue() const { return eventString; } 
		void SetValue(wxString value) { eventString = value; }
		void SetInOut(int value) { inOrOut = value; }
		int GetInOut() const { return inOrOut; }

		virtual wxEvent *Clone() const { return new StatusDialogEvent(*this); } // required for sending with wxPostEvent() 

	private: 
		wxString eventString;
		int inOrOut; //1 = in, 2 = out, 0 = err;

	DECLARE_DYNAMIC_CLASS(StatusDialogEvent) 
}; 

BEGIN_DECLARE_EVENT_TYPES() 
	DECLARE_EVENT_TYPE(wxEVT_COMMAND_STATUSDIALOG, -1) 
END_DECLARE_EVENT_TYPES() 

typedef void (wxEvtHandler::*wxStatusDialogEventFunction)(StatusDialogEvent&); 

#define EVT_STATUSDIALOG(id, fn) \
	DECLARE_EVENT_TABLE_ENTRY(wxEVT_COMMAND_STATUSDIALOG, id, -1,  \
	(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)  \
	wxStaticCastEvent(wxStatusDialogEventFunction, & fn), (wxObject *) NULL ),





/////////////////////////////////////
class StatusDialog : public wxDialog
{
	public:
		StatusDialog(wxWindow* parent);
		~StatusDialog();
		void OnClose(wxCloseEvent &event);
		void Input(const wxString &temp);
		void Output(const wxString &temp);
		void OnClear(GButtonEvent &event);
		void OnMouseWheel(wxMouseEvent &event);
		void OnLogToFile(wxCommandEvent &event);
		void OnMove(wxMoveEvent &event);
		void OnSize(wxSizeEvent &event);
		void SendStatusToFile(wxString outStatus);
		void OnStatusDialogEvent(StatusDialogEvent &event);

		wxPoint position;
		wxSize size;
		bool shown;
		bool logToFile;
		
		wxBoxSizer *mySizer;
		
		wxBoxSizer *mySizer2;
		wxPanel* textPanel;
		wxPanel* textPanel2;
		wxStaticText* inputText;
		wxStaticText* outputText;

		wxBoxSizer *mySizer3;
		wxListBox *input;
	    wxListBox *output;

		wxPanel *bottomPanel;
		GButton *clear;
		wxCheckBox *logToFileBox;

	private:
		DECLARE_EVENT_TABLE() 
};

#endif //STATUSDIALOG_H
