//// eTriggerVST.h/////////////////////////////////////////////////////////////////////////
//
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef ETRIGGERVST_H
#define ETRIGGERVST_H

#ifdef VST

#include "wx/wxprec.h"

#include "wxVST.h"
#include "Process.h"
#include "MainPanel.h"

#ifdef MAC
#pragma export on
#endif

//////////////////////////////////////////
class EtriggerEffect : public wxVstEffectX
{
public:
	EtriggerEffect(audioMasterCallback audioMaster);
	~EtriggerEffect();

	virtual long processEvents (VstEvents* events);
	virtual void resume ();
	virtual bool getEffectName (char* name);
	virtual bool getProductString (char* text);
	virtual long getVendorVersion () { return 1000; }
	virtual long canDo (char* text);

	bool oome;
};


/////////////////////////////////////////
class EtriggerEditor : public wxVstEditor
{
public:
	EtriggerEditor(AudioEffect *effect);
	~EtriggerEditor();
	long open(void *ptr);
	void close();

	MainPanel* mainPanel;
};

#ifdef WIN32
//////////////////////////////////////////////////////////////////
__declspec(dllexport) void* main (audioMasterCallback audioMaster)
#else
extern "C" AEffect* main_macho (audioMasterCallback audioMaster)
#endif
{
	// Get VST Version
	if (!audioMaster (0, audioMasterVersion, 0, 0, 0, 0)){
		return 0;  // old version
	}

	// Create the AudioEffect
	EtriggerEffect* effect = new EtriggerEffect(audioMaster);
	if (!effect){
		return 0;
	}
	
	// Check if no problem in constructor of EtriggerEffect
	if (effect->oome)
	{
		delete effect;
		return 0;
	}
	return effect->getAeffect ();
}



///////////////////////////////
class MyDllApp : public wxApp {

public:

	~MyDllApp() {};
	virtual bool OnInit() {	return true; }
	virtual int OnExit() { return 0; }
};

IMPLEMENT_APP_NO_MAIN(MyDllApp)




#ifdef WIN32
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


#ifdef MAC
#pragma export off
#endif


#endif //WIN32
#endif //VST
#endif //ETRIGGERVST_H