////wxDelayEditor.h/////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////
#ifndef WXDELAYEDITOR_H
#define WXDELAYEDITOR_H

#include "wxVST.h"
#include "ADelay.hpp"
#include "wxDelayPanel.h"


////////////////////////////////////////
class wxDelayEditor : public wxVstEditor
{
public:
	wxDelayEditor (AudioEffect *effect);
	virtual ~wxDelayEditor ();

public:
	virtual long open (void *ptr);
	virtual void close ();
};

#endif //WXDELAYEDITOR_H
