//// eTriggerVST.cpp//////////////////////////////////////////////////////////
//
// 
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "eTriggerVST.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifdef VST

#include <string.h>

///////////////////////////////////////////////////////////////
EtriggerEffect::EtriggerEffect(audioMasterCallback audioMaster)
               :wxVstEffectX(audioMaster)
{
	oome = false;
	isSynth();
	setUniqueID('ETRI');
	editor = new EtriggerEditor(this);
	if(!editor){
		oome = true;
	}

	Process::LinkVST(this);
}

/////////////////////////////////
EtriggerEffect::~EtriggerEffect()
{
	// the editor gets deleted by the AudioEffect base class
}

//////////////////////////////////////////////////
long EtriggerEffect::processEvents (VstEvents* ev)
{
	for (long i = 0; i < ev->numEvents; i++)
	{
		if ((ev->events[i])->type != kVstMidiType)
			continue;
		VstMidiEvent* event = (VstMidiEvent*)ev->events[i];
		char* midiData = event->midiData;
		long status = midiData[0];
		long note = midiData[1] & 0x7f;
		long velocity = midiData[2] & 0x7f;

		std::vector<unsigned char> message(3);
		message[0] = status;
		message[1] = note;
		message[2] = velocity;
		Process::Send(1, wxT("HOST"), 1, message);

		event++;
	}
	return 1;	// want more
}

//////////////////////////////
void EtriggerEffect::resume ()
{
	wantEvents ();
}

//////////////////////////////////////////////
bool EtriggerEffect::getEffectName(char* name)
{
	strcpy (name, "eTrigger");
	return true;
}

/////////////////////////////////////////////////
bool EtriggerEffect::getProductString(char* text)
{
	strcpy (text, "aquawicket");
	return true;
}

///////////////////////////////////
long EtriggerEffect::canDo (char* text)
{
	if (!strcmp (text, "receiveVstEvents"))
		return 1;
	if (!strcmp (text, "receiveVstMidiEvent"))
		return 1;
	if (!strcmp (text, "sendVstEvents"))
		return 1;
	if (!strcmp (text, "sendVstMidiEvent"))
		return 1;
	if (!strcmp (text, "midiProgramNames"))
		return 1;
	return -1;	// explicitly can't do; 0 => don't know
}









///////////////////////////////////////////////////
EtriggerEditor::EtriggerEditor(AudioEffect *effect)
               :wxVstEditor (effect) 
{
	// init the size of the plugin, left, top always 0, 0
	rect.right  = rect.left + 800 - 1;
	rect.bottom = rect.top + 600 - 1;
}

/////////////////////////////////
EtriggerEditor::~EtriggerEditor()
{
}

////////////////////////////////////
long EtriggerEditor::open(void *ptr)
{
	wxVstEditor::open (ptr);

	// create the class without physical windows first
	mainPanel = new MainPanel( this );

	mainPanel->Create( parent, 10005, wxPoint(0,0), wxSize(800,600), 0 );
	
	mainPanel->Show( true );

	// set focus to our panel when displayed for the first time
	mainPanel->SetFocus();

	//--init the faders------------------------------------------------
	//delayPanel->setParameter(kDelay, effect->getParameter (kDelay));
	//delayPanel->setParameter(kFeedBack, effect->getParameter (kFeedBack));
	//delayPanel->setParameter(kOut, effect->getParameter (kOut));

	return true;
}

////////////////////////////
void EtriggerEditor::close()
{
	wxVstEditor::close();
}

#endif VST