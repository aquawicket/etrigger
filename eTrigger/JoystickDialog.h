//// JoystickDialog.h /////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef JOYSTICKDIALOG_H
#define JOYSTICKDIALOG_H

#include <wx/dialog.h>
#include <wx/listbox.h>
#include <wx/image.h>
#include "Joystick.h"
#include "../lib/Gwidgets/GButton/GButton.h"

#include "../Images/ok.xpm"
#include "../Images/ok-hover.xpm"
#include "../Images/ok-click.xpm"
#include "../Images/cancel.xpm"
#include "../Images/cancel-hover.xpm"
#include "../Images/cancel-click.xpm"

class Joystick;

///////////////////////////////////////
class JoystickDialog : public wxDialog
{
public:
	JoystickDialog(Joystick *ref);

	void VarsToDlg();
	void OnOk(GButtonEvent &event);
	void OnCancel(GButtonEvent &event);
	void OnClose(wxCloseEvent &event);

	Joystick *joystick;

	wxListBox *joys;
	GButton *ok;
	GButton *cancel;

	DECLARE_EVENT_TABLE();
};

#endif //JOYSTICKDIALOG_H

