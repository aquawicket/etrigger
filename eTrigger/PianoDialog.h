//// PianoDialog.h /////////////////////////////////////////////////////////////////////////////
//
//   A Visual Piano that reacts to input.
//
/////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef PIANODIALOG_H
#define PIANODIALOG_H

#include <wx/dialog.h>
#include <wx/image.h>
#include "MainPanel.h"
#include "../lib/Gwidgets/GImage/GImage.h"

// XPM Images
#include "../Images/piano.xpm"
#include "../Images/pianoSmall.xpm"
#include "../Images/blackKeyDown.xpm"
#include "../Images/keyCDown.xpm"
#include "../Images/keyDDown.xpm"
#include "../Images/keyEDown.xpm"
#include "../Images/keyFDown.xpm"
#include "../Images/keyGDown.xpm"
#include "../Images/keyADown.xpm"
#include "../Images/keyBDown.xpm"

#define FDR_NO_MOUSE_CAPTURE 0x0001 

class PianoDialog;

////////////////////////////////////////
class TranparentWindow : public wxDialog
{
public:
	TranparentWindow(PianoDialog* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style);
	void OnMouse(wxMouseEvent &event);
	bool UseMouseCapture();

	PianoDialog *pianoDialog;

	bool dragging;
	wxPoint mousePoint;

private:
	DECLARE_EVENT_TABLE()
};



//////////////////////////////
class Keyboard : public GImage
{
public:
	Keyboard(PianoDialog *parent, wxWindowID id, const wxPoint& pos, const char** image);
	void OnMouse(wxMouseEvent &event);

	PianoDialog *pianoDialog;

private:
	DECLARE_EVENT_TABLE() 
};




//////////////////////////////
class PianoDialog : public wxDialog
{
public:
	PianoDialog(MainPanel* parent);
	void OnClose(wxCloseEvent &event);
	void OnMove(wxMoveEvent &event);
	void OnSize(wxSizeEvent &event);
	void KeyDown(int num);
	void KeyUp(int num);
	void AlignKeys();
	void OutputNote(int num);

	wxPoint position;
	wxSize size;
	bool shown;

	MainPanel *mainPanel;
	Keyboard *pianoPic;
	GImage *pianoSmall;

	GImage *keyDown[128];

	TranparentWindow *transWindow;

private:
	DECLARE_EVENT_TABLE() 
};



#endif //PIANODIALOG_H

