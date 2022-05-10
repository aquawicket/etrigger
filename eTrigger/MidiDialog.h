//// MidiDialog.h /////////////////////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef MIDIDIALOG_H
#define MIDIDIALOG_H

#include <wx/dialog.h>
#include <wx/listbox.h>
#include <wx/image.h>
#include "Midi.h"
#include "../lib/Gwidgets/GButton/GButton.h"

#include "../Images/ok.xpm"
#include "../Images/ok-hover.xpm"
#include "../Images/ok-click.xpm"
#include "../Images/cancel.xpm"
#include "../Images/cancel-hover.xpm"
#include "../Images/cancel-click.xpm"

class Midi;

////////////////////////////////
class MidiDialog : public wxDialog
{
public:
	MidiDialog(Midi *ref);
	~MidiDialog();

	void VarsToDlg();
	void OnOk(GButtonEvent &event);
	void OnCancel(GButtonEvent &event);
	void OnClose(wxCloseEvent &event);
	void IsMidiPatchDriverInstalled();

	Midi *midi;
	wxListBox *midiIn;
	wxListBox *midiOut;
	GButton *ok;
	GButton *cancel;

	DECLARE_EVENT_TABLE();
};

/////////////////////////////////////////
class NoMidiDriverDialog: public wxDialog
{
public:
	NoMidiDriverDialog();
	~NoMidiDriverDialog();
	void InitVariables();

	void OnOk(GButtonEvent &event);
	void OnCancel(GButtonEvent &event);	
	void OnHyperlink1(wxHyperlinkEvent &event);
	void OnHyperlink2(wxHyperlinkEvent &event);
	void OnHyperlink3(wxHyperlinkEvent &event);

	GButton *ok;
	GButton *cancel;
	wxHyperlinkCtrl *link1;	
	wxHyperlinkCtrl *link2;	
	wxHyperlinkCtrl *link3;	

	DECLARE_EVENT_TABLE();
};

#endif //MIDIDIALOG_H

