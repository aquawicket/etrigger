////wxDelay.cpp//////////////////////////////////////////////////////////////
//
// 
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wxDelay.h"
#include "wxDelayEditor.h"

#include <string.h>

extern bool oome;

//////////////////////////////////////////////////
wxDelay::wxDelay (audioMasterCallback audioMaster)
 : ADelay (audioMaster)
{
	setUniqueID ('WXDL');
	editor = new wxDelayEditor (this);
	if (!editor)
		oome = true;
}

////////////////////
wxDelay::~wxDelay ()
{
	// the editor gets deleted by the
	// AudioEffect base class
}

////////////////////////////////////////////////////
void wxDelay::setParameter (long index, float value)
{
	ADelay::setParameter (index, value);

	if (editor)
		((wxVstEditor*)editor)->setParameter (index, value);
}

/////////////////////////////
bool wxDelay::keysRequired ()
{
	return ( editor != NULL );
}

////////////////////////////////////////
bool wxDelay::getEffectName (char* name)
{
	strcpy (name, "wxDelay");
	return true;
}

///////////////////////////////////////////
bool wxDelay::getProductString (char* text)
{
	strcpy (text, "wxDelay");
	return true;
}

