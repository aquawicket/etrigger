////wxDelayMain.cpp/////////////////////////////////////////////////////////////////////////
//
//
/////////////////////////////////////////////////////////////////////////////

#ifdef _MSC_VER
#pragma warning (disable : 4996)
#endif

#include <process.h>

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
  #include "wx/wx.h"
  #include "wx/log.h"
#endif

#ifndef __wxVstEditor__
#include "wxVstEditor.h"
#endif

#ifndef __WXDELAY_H
#include "wxDelay.h"
#endif
bool oome = false;

#if MAC
#pragma export on
#endif


#if WIN32
//////////////////////////////////////////////////////////////////
__declspec(dllexport) void* main (audioMasterCallback audioMaster)
#else
extern "C" AEffect* main_macho (audioMasterCallback audioMaster)
#endif
{
	// Get VST Version
	if (!audioMaster (0, audioMasterVersion, 0, 0, 0, 0))
		return 0;  // old version

	// Create the AudioEffect
	ADelay* effect = new wxDelay (audioMaster);
	if (!effect)
		return 0;
	
	// Check if no problem in constructor of AGain
	if (oome)
	{
		delete effect;
		return 0;
	}
	return effect->getAeffect ();
}

#if MAC
#pragma export off
#endif

///////////////////////////////
class MyDllApp : public wxApp {

public:

	~MyDllApp() {};
	virtual bool OnInit() {	return true; }
	virtual int OnExit() { return 0; }
};

IMPLEMENT_APP_NO_MAIN(MyDllApp)






#if WIN32
#include <windows.h>
/////////////////////////////////////////////////////////////////////////
BOOL WINAPI DllMain (HINSTANCE hInst, DWORD dwReason, LPVOID lpvReserved)
{
    switch(dwReason)
    {
        case DLL_PROCESS_ATTACH:
			// initialize wxWidgets without entering the event loop
			if ( !wxVstEditor::startWxWidgets( hInst ) )
				return FALSE;
			break;

        case DLL_PROCESS_DETACH:
			// uninitilize wxWidgets
			wxVstEditor::stopWxWidgets();
            break;
    } 

	return TRUE;
}
#endif

