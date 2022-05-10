//// AudioDialog.h /////////////////////////////////////////////////////////////////////
//
//  AudioDialog's job is to work with selecting and deselecting audio devices for Audio 
//  to use.
//
////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef AUDIODIALOG_H
#define AUDIODIALOG_H

#include <wx/dialog.h>
#include <wx/listbox.h>
#include <wx/image.h>
#include <wx/combobox.h>

#include "Audio.h"
#include "../lib/Gwidgets/GButton/GButton.h"

#include "../Images/setup-focused.xpm"
#include "../Images/setup-hover-focused.xpm"
#include "../Images/setup-click-focused.xpm"
#include "../Images/ok.xpm"
#include "../Images/ok-hover.xpm"
#include "../Images/ok-click.xpm"
#include "../Images/cancel.xpm"
#include "../Images/cancel-hover.xpm"
#include "../Images/cancel-click.xpm"

class Audio;

////////////////////////////////////
class AudioDialog : public wxDialog
{
public:
	AudioDialog(Audio *ref);
	~AudioDialog();
	void InitVariables();

	void OnSetFocus(wxFocusEvent &event);
	void VarsToDlg();
	void OnInSetup(GButtonEvent &event);
	void OnOutSetup(GButtonEvent &event);
	void UpdateSetup();
	void OnInputSelect(wxCommandEvent &event);
	void OnOutputSelect(wxCommandEvent &event);
	void UpdateDevices(wxCommandEvent &event);
	void OnOk(GButtonEvent &event);
	void OnCancel(GButtonEvent &event);
	void OnClose(wxCloseEvent &event);
		
	Audio *audio;
	wxArrayString sampleRates;
	wxComboBox *inAPIs;
	wxComboBox* inSampleRate;
	wxListBox *audioIn;
	wxString lastSelectedInDevice;
	double storedInSampleRate;

	GButton *asioInSetup;	
    wxComboBox *outAPIs;
	wxComboBox *outSampleRate;
	wxListBox *audioOut;
	wxString lastSelectedOutDevice;
	double storedOutSampleRate;
	GButton *asioOutSetup;	
	GButton *ok;
    GButton *cancel;	

	DECLARE_EVENT_TABLE();
};
#endif //AUDIODIALOG_H
