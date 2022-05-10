////wxDelayEditor.cpp////////////////////////////////////////////////////////
//
//
/////////////////////////////////////////////////////////////////////////////

#include "wx/wxprec.h"

#include "wxDelayEditor.h"

//////////////////////////////////////////////////
wxDelayEditor::wxDelayEditor (AudioEffect *effect)
 : wxVstEditor (effect) 
{
	// init the size of the plugin, left, top always 0, 0
	rect.right  = rect.left + SYMBOL_WXDELAYPANEL_SIZE.GetWidth() - 1;
	rect.bottom = rect.top + SYMBOL_WXDELAYPANEL_SIZE.GetHeight() - 1;
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
			
	delayPanel->Create( parent, ID_PANEL, SYMBOL_WXDELAYPANEL_POSITION,
							SYMBOL_WXDELAYPANEL_SIZE, SYMBOL_WXDELAYPANEL_STYLE );

	delayPanel->Show( true );

	// set focus to our panel when displayed for the first time
	delayPanel->SetFocus();

	//--init the faders------------------------------------------------
	delayPanel->setParameter(kDelay, effect->getParameter (kDelay));
	delayPanel->setParameter(kFeedBack, effect->getParameter (kFeedBack));
	delayPanel->setParameter(kOut, effect->getParameter (kOut));

	return true;
}

////////////////////////////
void wxDelayEditor::close ()
{
	// !!! always call this !!!
	wxVstEditor::close();
}

