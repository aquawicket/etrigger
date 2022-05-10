////wxDelay.h/////////////////////////////////////////////////////////////////////////
//
//
/////////////////////////////////////////////////////////////////////////////

#ifndef WXDELAY_H
#define WXDELAY_H

#include "ADelay.hpp"

//////////////////////////////

class wxDelay : public ADelay
{
public:
	wxDelay (audioMasterCallback audioMaster);
	~wxDelay ();

	void setParameter (long index, float value);
	bool keysRequired ();
	bool getEffectName (char* name);
	bool getProductString (char* text);
	long getVendorVersion () { return 1000; }
};




#endif
