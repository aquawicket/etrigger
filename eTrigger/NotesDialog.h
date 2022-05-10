//// NotesDialog.h /////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef NOTESDIALOG_H
#define NOTESDIALOG_H

#include <wx/dialog.h>
#include "MainPanel.h"

/////////////////////////////////
class NotesDialog : public wxDialog
{
public:
	NotesDialog(MainPanel *parent);

	void OnStartUpBox(wxCommandEvent &event);

	MainPanel *mainPanel;

	wxBoxSizer *mySizer;
	wxListBox *text;
	wxCheckBox *onStartUp;
	wxPanel* bottomPanel;
	void SetNotes();

	DECLARE_EVENT_TABLE();

};

#endif //NOTESDIALOG_H
