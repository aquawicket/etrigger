//// Err.h //////////////////////////////////////////////////////////////////////////////
//
//  Err's job is to catch error's and asserts and show details about these errors. 
//  Along with capabilty to send reports to the user, and the eTriggerServer.
//
/////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef ERR_H
#define ERR_H

#include <wx/button.h>
#include <wx/datetime.h>
#include <wx/dcclient.h>
#include <wx/debugrpt.h>
#include <wx/ffile.h>
#include <wx/filename.h>
#include <wx/frame.h>
#include <wx/icon.h>
#include <wx/log.h>
#include <wx/menu.h>
#include <wx/msgdlg.h>
#include <wx/socket.h> 

#include "../lib/Gwidgets/GButton/GButton.h"
#include "mainPanel.h"

#include "../Images/cancel.xpm"
#include "../Images/error.xpm"
#include "../Images/ok.xpm"

//////////////////////////////////
class ERRdialog : public wxDialog
{
public:
	ERRdialog(wxDebugReport::Context &ctx, MainPanel *parent);
	~ERRdialog(){}

	void OnOk(GButtonEvent &event);
	void OnCancel(GButtonEvent &event);

	MainPanel *mainPanel;
	GImage *image;
	wxTextCtrl *description;
	GButton *ok;
	GButton *cancel;
	wxStaticText* status; 
	wxDebugReport::Context *data;
	wxDebugReport *report;
	wxString *ReportData;

	DECLARE_EVENT_TABLE(); 
};


//////////////////////////////////////
BEGIN_EVENT_TABLE(ERRdialog, wxDialog)
	EVT_GBUTTON(100, ERRdialog::OnOk)
	EVT_GBUTTON(101, ERRdialog::OnCancel)
END_EVENT_TABLE() 


/////////////////////////////////////////////////////////////////////////////////////////////////
ERRdialog::ERRdialog(wxDebugReport::Context &ctx, MainPanel *parent) 
          : wxDialog(NULL, -1, wxT("Send Error Report"), wxDefaultPosition, wxSize(396, 450), 0, wxT("Send Error Report"))
{
	mainPanel = parent;
	image = new GImage(this, -1, wxPoint(10,10), error_xpm);
	wxStaticText *temp = new wxStaticText(this, -1, wxString("Please describe what you did before eTrigger crashed."), wxPoint(10, 275), wxSize(376, 20), wxALIGN_CENTRE, wxString(""));
	description = new wxTextCtrl(this, -1, wxT(""), wxPoint(10, 295), wxSize(376, 80), 0, wxDefaultValidator, wxT(""));
	status = new wxStaticText(this, -1, wxString("Click OK to send an error report."), wxPoint(10, 395), wxSize(376, 20), wxALIGN_CENTRE, wxString(""));
	ok = new GButton(this, 100, wxPoint(130, 415), ok_xpm);
	cancel = new GButton(this, 101, wxPoint(210, 415), cancel_xpm);
	
	 
	data = &ctx;

	report = new wxDebugReport;
	ReportData = new wxString();
                                                  
    // add all standard files: currently this means just a minidump and an
    // XML file with system info and stack trace
    report->AddAll(ctx);

    // you can also call report->AddFile(...) with your own log files, files
    // created using wxRegKey::Export() and so on, here we just add a test
    // file containing the date of the crash

	wxFFile file;
	file.Open(report->GetDirectory() + _T("/") + report->GetReportName() + _T(".xml"), _T("r"));
    if ( file.IsOpened() )
    {
		file.ReadAll(ReportData, wxConvAuto());
        file.Close();
    }
}

/////////////////////////////////////////
void ERRdialog::OnOk(GButtonEvent &event)
{ 
	//We can provide much more data in the error report by pulling values from variables
	//throughout the rest of the program

	wxString tempstring = wxT("\n\n");
	tempstring += mainPanel->details->GetDetails();

	tempstring += wxT("\n\nError Description:\n");
	tempstring += description->GetValue();
	*ReportData += tempstring;

	status->SetLabel("Connected...\n");

	if(	mainPanel->client->SendErrorReport(ReportData) ){
		status->SetLabel("Sending Error Report Failed.\n");		
	}
	else{
		status->SetLabel("Sent Error Report Successfully.\n");
	}

	
	::wxSleep(3);

	Close();
}

/////////////////////////////////////////////
void ERRdialog::OnCancel(GButtonEvent &event)
{
	Close();
}

          
////////////////////////////////////////////////////////
class ERR
{
public:
	
	ERR(){}
	ERR(wxString error){wxMessageBox(error, wxT(""), wxSTAY_ON_TOP);}
	~ERR(){}
	void GenerateReport(wxDebugReport::Context ctx, MainPanel *parent);
};

////////////////////////////////////////////////////
void ERR::GenerateReport(wxDebugReport::Context ctx, MainPanel *parent)
{
	ERRdialog *ED = new ERRdialog(ctx, parent);
	ED->ShowModal();
}

#endif //ERR_H