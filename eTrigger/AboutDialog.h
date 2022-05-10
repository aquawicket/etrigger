//// AboutDialog.h /////////////////////////////////////////////////////////////////////////////
//
//  About's job is to show details about the software. Version, Web site, Extra Info, etc.
//
////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <wx/dialog.h>
#include <wx/hyperlink.h>

#include "../lib/Gwidgets/GButton/GButton.h"
#include "../lib/Gwidgets/GImage/GImage.h"

#include "MainPanel.h"
#include "Tracks.h"
#include "KeyToString.h"
#include "AdminDialog.h"

#include "../Images/register.xpm"
#include "../Images/register-hover.xpm"
#include "../Images/register-click.xpm"
#include "../Images/sendReport.xpm"
#include "../Images/sendReport-hover.xpm"
#include "../Images/sendReport-click.xpm"
#include "../Images/ok.xpm"
#include "../Images/ok-hover.xpm"
#include "../Images/ok-click.xpm"
#include "../Images/cancel.xpm"
#include "../Images/cancel-hover.xpm"
#include "../Images/cancel-click.xpm"
#include "../Images/logoSmall.xpm"

class TrackProc;
class Logo;

/////////////////////////////
class AboutDialog: public wxDialog
{
public:
	AboutDialog(MainPanel *parent);
	~AboutDialog();
	void InitVariables();

	void OnOk(GButtonEvent &event);
	void OnCancel(GButtonEvent &event);	
	void OnRegister(GButtonEvent &event);
	void OnSendDetailReport(GButtonEvent &event);

	MainPanel *mainPanel;
	Security *security;
	TrackProc *trackProc;
	Logo *logo;
	GButton *registerButton;
	GButton *sendDetailReport;
	GButton *ok;
	GButton *cancel;
	wxHyperlinkCtrl *website;	

	DECLARE_EVENT_TABLE();
};

//////////////////////////
class Logo: public GImage
{
public:
	Logo(AboutDialog* parent, wxWindowID id, const wxPoint& pos, const char** image);
	void OnKeyDown(wxKeyEvent &event);
	void KeyHistory(char key);

	char keyHistory[20];

	AboutDialog *aboutDialog;
	AdminDialog *adminDialog;

	DECLARE_EVENT_TABLE();
};

#endif //ABOUTDIALOG_H
