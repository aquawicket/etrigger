////wxDelayEditor.cpp////////////////////////////////////////////////////////
//
//
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wxDelayEditor.h"

//////////////////////////////////////////////////
wxDelayEditor::wxDelayEditor (AudioEffect *effect)
 : wxVstEditor (effect) 
{
	// init the size of the plugin, left, top always 0, 0
	rect.right  = rect.left + 640 - 1;
	rect.bottom = rect.top + 480 - 1;
}

////////////////////////////////
wxDelayEditor::~wxDelayEditor ()
{
}

////////////////////////////////////
long wxDelayEditor::open (void *ptr)
{
	// !!! always call this !!!
	wxVstEditor::open (ptr);

	// create the class without physical windows first
	wxDelayPanel* delayPanel = new wxDelayPanel( this );
			
	delayPanel->Create( parent, 10005, wxPoint(0,0), wxSize(640,480), 0  );
	delayPanel->Show( true );

	// set focus to our panel when displayed for the first time
	delayPanel->SetFocus();

	//--init the faders------------------------------------------------
	//delayPanel->setParameter(kDelay, effect->getParameter (kDelay));
	//delayPanel->setParameter(kFeedBack, effect->getParameter (kFeedBack));
	//delayPanel->setParameter(kOut, effect->getParameter (kOut));

	return true;
}

////////////////////////////
void wxDelayEditor::close ()
{
	// !!! always call this !!!
	wxVstEditor::close();
}

