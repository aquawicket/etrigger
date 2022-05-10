//// AdminDialog.h /////////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef ADMINDIALOG_H
#define ADMINDIALOG_H

#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/textdlg.h>
#include <wx/msgdlg.h>
#include <wx/stattext.h>
#include <wx/datetime.h>
#include <wx/utils.h>

#include "MainPanel.h"
#include "Security.h"

#include "../lib/Gwidgets/GHelper/GHelper.h"

class MainPanel;

////////////////////////////////////
class AdminDialog : public wxDialog
{
public:
	AdminDialog(MainPanel *parent);
	~AdminDialog();
	void InitVariables();

	void OnClient(wxCommandEvent& event);
	void OnCrash(wxCommandEvent& event);
	void OnShowDiskSerial(wxCommandEvent& event);

	MainPanel *mainPanel;
	Security *security;
	wxButton *clientButton;
	wxButton *crashButton;
	wxStaticText *diskSerial;
	wxStaticText *diskSerialEncoded;
	wxStaticText *serialNumber;
	wxStaticText *serialPassed;
	wxStaticText *currentTime;
	wxStaticText *firstRunTime;
	wxStaticText *lastRunTime;
	wxStaticText *OSinfo;

	DECLARE_EVENT_TABLE();
};

#endif // ADMINDIALOG_H
