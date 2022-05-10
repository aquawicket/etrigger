///// DebugDialog.h /////////////////////////////////////////////////////////////
//
//  We can pick on classes and data to do some debugging.
//
//
///////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef DEBUGDIALOG_H
#define DEBUGDIALOG_H

#include "MainPanel.h"

#include <stdio.h>

#ifdef MPG123
#include "../lib-src/mpg123/ports/MSVC++/mpg123.h"
#endif

#ifdef SNDFILE
#include "../lib-src/libsndfile/Win32/sndfile.h"
#endif

class MainPanel;

////////////////////////////////////
class DebugDialog : public wxDialog
{
public:
	DebugDialog(MainPanel* parent);
	~DebugDialog();
	void InitVariables();

	void OnLoadWavToMem(wxCommandEvent &event);
	void OnPlayWav(wxCommandEvent &event);
	void OnStopWav(wxCommandEvent &event);
	void OnUnloadWav(wxCommandEvent &event);
	void OnLoadMp3ToMem(wxCommandEvent &event);
	void OnPlayMp3(wxCommandEvent &event);
	void OnStopMp3(wxCommandEvent &event);
	void OnUnloadMp3(wxCommandEvent &event);
	void OnConvertMp3ToWav(wxCommandEvent &event);

	MainPanel *mainPanel;

	wxButton *LoadWavToMem;
	wxTextCtrl *framesToLoad;
	wxButton *PlayWav;
	wxButton *StopWav;
	wxTextCtrl *startFrame;
	wxButton *UnloadWav;

	wxButton *LoadMp3ToMem;
	wxTextCtrl *framesToLoad2;
	wxButton *PlayMp3;
	wxButton *StopMp3;
	wxTextCtrl *startFrame2;
	wxButton *UnloadMp3;
	//wxButton *ConvertMp3ToWav;
	
	#ifdef WIN32
	static __int64 GetCPUCount ( unsigned int loword, unsigned int hiword );
    #endif //WIN32

	DECLARE_EVENT_TABLE();
};

#endif //DEBUGDIALOG_H
