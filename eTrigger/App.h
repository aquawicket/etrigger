//// App.h /////////////////////////////////////////////////////////////////////////////
//
//  App's job is to intitiate the program alog with control at base level.
//
////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef APP_H
#define APP_H

#include <wx/wxprec.h>
#include <wx/snglinst.h>
#include <wx/splash.h>

#include "Main.h"
#include "MainFrame.h"
#include "KeyToString.h"

#include "../Images/splashscreen.xpm"

#ifdef WIN32
#include "Err.h"
#endif //WIN32

#ifdef __BORLANDC__ 
	#pragma hdrstop 
#endif 
	
#ifndef WX_PRECOMP 
    #include <wx/wx.h> 
#endif 

#ifdef WIN32
#if !wxUSE_DEBUGREPORT
    #error "This program can't be built without wxUSE_DEBUGREPORT"
#endif // wxUSE_DEBUGREPORT
#endif //WIN32


#if !wxUSE_ON_FATAL_EXCEPTION
    #error "This program can't be built without wxUSE_ON_FATAL_EXCEPTION"
#endif // wxUSE_ON_FATAL_EXCEPTION


///////////////////////////
class MyApp : public wxApp
{
public:

    MyApp();
	~MyApp();
	void InitVariables();

    virtual bool OnInit();
	virtual int OnExit();

	virtual void OnFatalException();
	void LoadMainSettings();
	int FilterEvent(wxEvent& event);

	//Main *main;
	MainFrame *frame;
    
	bool keyState[256]; //the down state for all keys.
	wxString version;
	bool splashScreen;
	bool versionNotes;

	wxSingleInstanceChecker *m_checker;

private:

    DECLARE_NO_COPY_CLASS(MyApp)
};

DECLARE_APP(MyApp)

#endif //APP_H
