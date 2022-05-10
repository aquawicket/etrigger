//// Process.h /////////////////////////////////////////////////////////////////////////////
//
//  All signals (Audio, Midi, Joystick, Keyboard, Mouse, Com) are sent here to be 
//  processed. The database will determine output accordingly. Every signal has a 
//  numeric value. Midi starts the signal range with an input value from 0 - 256.
//  other values come in at the 257+ range. 
//  Actual values can be determined in this file.
//
//  Trk must be linked into this class so it can have access to the track database.
//
//  The IdleLoop Function handles multiple zone drums.
//  
//  The only reason this class derives from wxWindow is so we can use the IdleEvent.
//
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef PROCESS_H
#define PROCESS_H

#ifdef VST
#include "eTriggerVST.h"
#endif //VST

#include <vector>
#include <wx/msgdlg.h>
#include "Tracks.h"
#include "Timer.h"
#include "Midi.h"
#include "StatusDialog.h"
#include "MidiMonitor.h"
#include "KeyToString.h"
#include "SequencePlayer.h"
#include "Network.h"
#include "MenuPanel.h"

#ifdef VST
class EtriggerEffect;
#endif //VST

class TrackProc;
class Midi;
class MidiMonitor;
class KeyB;
//class MenuPanel;

typedef struct{
	wxString deviceName;
	wxString inputDetails;
}DeviceInfo;

//For ION iED05 compatability
typedef struct{
	bool drum;
	int track;
	int zone;
}ION;

//////// Process ///////////////
class Process : public wxWindow
{
public:
	Process(wxWindow* parent);
	~Process(){}

	static void Send(int signalType, wxString string, int num, std::vector<unsigned char>& message); //All inputs come here !!!!!!
	static void Output(std::vector<unsigned char> &message);
	static void MultiZoneOutput(int track);
	static bool Retrigger(unsigned char &message);
	static void Crosstalk(std::vector<unsigned char>& message);
	static void PreGain(std::vector<unsigned char>& message);
	static void Volume(std::vector<unsigned char>& message);
	static void Dynamics(std::vector<unsigned char>& message);
	static void Limiter(std::vector<unsigned char>& message);
	static void Compressor(std::vector<unsigned char>& message);
	//static void VelocitySmoothing(std::vector<unsigned char>& message);
	static void AntiMachineGun(std::vector<unsigned char>& message);
	static void CCControlledVelocity(std::vector<unsigned char>& message);
	static void Alteration(std::vector<unsigned char>& message);
	static void MidiCCControlledOutput(std::vector<unsigned char>& message);
	static void VelocityControlledOutput(std::vector<unsigned char>& message);
	static void ZoneControlledOutput(std::vector<unsigned char>& message, int position);
	static void SequenceOutput();
	static void MouseOutput();
	static void PedalDownEvent(std::vector<unsigned char>& message);
	static void VelocityBalance(int position);
	static void PositionSensing(int position);
	static void GetTempo(std::vector<unsigned char>& message);
	static void LinkTrk(TrackProc *mytrack); //The active Trk database must be linked in. 
	static void LinkMidi(Midi *ref);
	static void LinkStatus(StatusDialog *status);
	static void LinkMidiMonitor(MidiMonitor *midmon);
	static void LinkSequencePlayer(SequencePlayer *sp);
	static void LinkMenu(MenuPanel *menu);
#ifdef VST
	static void LinkVST(EtriggerEffect *host);
#endif //VST
	void IdleLoop(wxIdleEvent &event);

#ifdef VST
	static EtriggerEffect *vst;
#endif //VST

	/// SIGNAL DATA
	static bool match;
	static int trackNum;
	static int zoneNum;
	static int trackType;
	//static ION ion[10];
	static bool cancelOutput;
	static int tempo[5];

	static bool active;	
	static TrackProc* trackProc; //Pointer to Trk database
	static Midi* midi; //pointer to midi interface
	static StatusDialog* statusDialog; //pointer to the status dialog window
	static MenuPanel* menuPanel; 
	static MidiMonitor* midiMonitor; //pointer to the status dialog window
	static SequencePlayer* sequencePlayer; //pointer to the SequencePlayer
	static bool Learning;
	static int LearnReply;
	static bool detectingRetrigger;
	static int retriggerTrackNum;
	static int retriggerZoneNum;
	static bool detectingWaitTime;
	static int waitTimeTrackNum;
	static bool confirmWait;
	static DeviceInfo devInfo;
	static int velToPosAvgCycle;
	static int posToVelAvgCycle;

	static Timer timer;
	static double latency;
	
	static std::vector<unsigned char>output;

	DECLARE_EVENT_TABLE()	
};




/////// Learn Event ///////////////////
class LearnEvent: public wxCommandEvent 
{ 
	public: 
		LearnEvent(wxEventType commandType = wxEVT_NULL, int id = 0 ); 

		DeviceInfo GetValue() const { return deviceInfo; } 
		void SetValue(DeviceInfo value) { deviceInfo = value; } 

		virtual wxEvent *Clone() const { return new LearnEvent(*this); } // required for sending with wxPostEvent() 

	private: 
		DeviceInfo deviceInfo; 

	DECLARE_DYNAMIC_CLASS(LearnEvent) 
}; 

BEGIN_DECLARE_EVENT_TYPES() 
	DECLARE_EVENT_TYPE(wxEVT_COMMAND_LEARN, -1) 
END_DECLARE_EVENT_TYPES() 

typedef void (wxEvtHandler::*wxLearnEventFunction)(LearnEvent&); 

#define EVT_LEARN(id, fn) \
	DECLARE_EVENT_TABLE_ENTRY(wxEVT_COMMAND_LEARN, id, -1,  \
	(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)  \
	wxStaticCastEvent(wxLearnEventFunction, & fn), (wxObject *) NULL ),


////// Learn Thread ///////////////
class LearnThread : public wxThread
{
	public:
		LearnThread(wxWindow *parent, int trackType);
		~LearnThread(){};
		void *Entry();

		wxWindow *par;
};

//////////////////////////////
class GTimer: public wxTimer
{
public:

	GTimer();
	void LinkTrackProc(TrackProc *tp);
	void LinkSequencePlayer(SequencePlayer *sp);
	void LinkNetwork(Client *net);
	void Notify();

	SequencePlayer *sequencePlayer;
	TrackProc *trackProc;
	Client *client;
};

#endif //PROCESS_H
