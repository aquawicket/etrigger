//// Tracks.h /////////////////////////////////////////////////////////////////////////////
//This class keeps track of all of the tracks and their variables. 
//i.e what kinda of track, number of zones, position on the screen, input, ouput. etc

//We are allocating enough room for 100 tracks. 
//We would dynamically allocate except, outside classes point to this class.
//So when the number variable is resized, memory address change and the classes
//pointing to it's data now point to the wrong memory location.

//Updates can be made to redirect all of the outside pointers to point to the 
//correct updated address, but this can be a very involved process and many risks
//can come about. 

//In the future, if number can be made dynamic, and can be resized while pointing to 
//the same memory locations, it will be a gain in using less memory at runtime.
//
////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef TRACKS_H
#define TRACKS_H

#include <wx/menu.h>
#include <wx/gdicmn.h>
#include "MainPanel.h"
#include "Audio.h"
#include "Midi.h"
#include "Trigger.h"
#include "MidiCC.h"

#include "../Images/logo.xpm"

class MainPanel;
class Trigger;
class MidiCC;
class Audio;
class Midi;

///////////////////////////////////
class TrackPanel: public wxPanel
{ 
	public: 
		TrackPanel(MainPanel* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name);
		~TrackPanel(); 
		void InitVariables();

		void OnPaint(wxPaintEvent& event); 
		void OnMouse(wxMouseEvent &event);
		void OnMenuAddTrigger(wxCommandEvent &event);
	    void OnMenuAddMidiCC(wxCommandEvent &event);
	    void OnMenuDeleteTrack(wxCommandEvent &event);

		MainPanel *mainPanel;
		wxMenu *trackMenu;
		wxImage *logo;

		int position;
		
	DECLARE_EVENT_TABLE();
};

////////////////
class TrackData
{
	public:
		TrackData();
		//~TrackData();
		void InitVariables();

		int midiType;  //1=trigger, 2=midicc
		int drumType;  //1=kick, 2=snare, and so on...
		wxPoint pos; //x,y position in the parent window
		Trigger *trigger;
		MidiCC *midicc;

		/////////////////////////////////////////////
		// Track Database
		/////////////////////////////////////////////

		//Input
		wxString name; //name at the top of the track
		wxString image; //image selected on the track
		int trackNum; //current track number
		int zones; //number of zones the tracks is

		wxString deviceName[3];
		wxString inputDetails[3];
		int inputCode[3]; //input type and number
		int audioThreshold[3]; //threshold for audio input
		
		//Process
		int multiZoneWaitTime; //how long to wait for multiple zones
		int preVolume[3]; //individual volume for each zone
		int preGain[3]; //individual Gain for each zone (AUDIO)
		int retrigger[3];
		int crosstalk[3];
		int highCompressor[3];
		int highPercent[3];
		int lowCompressor[3];
		int lowPercent[3];
		int highLimiter[3];
		int lowLimiter[3];
		double lastHitTime[3];
		int lastOutputVelocity[3];
		int lastRetriggerVelocity[3];
		bool ccReverse;
		bool noteOff[3];
		bool lastWasNoteOff[3];
        
		std::vector< wxPoint > pointsZone1;
		std::vector< wxPoint > pointsZone2;
		std::vector< wxPoint > pointsZone3;
		int dynamics[3][127];
		double antiMachineGun[3][127];
		int antiMachineGunTime[3];

		bool midiCCControlledVelocity[3];
		int midiCCControlledVelocityNote[3];

		bool basicOutput[3];
				
		bool alternateOutput[3];
		bool alternateRandom[3];
		bool alternateCheckBox[3][100];
		int alternateNotes[3][100];
		int alternateReset[3];
		int alternateMarker[3];
		int alternateOffMarker[3];
		double lastAlternateHitTime[3];
		int alternateLastOn[3];

		bool midiCCControlledOutput[3];
		int midiCCControlledInputNote[3];
		bool midiCCControlledCheckBox[3][100];
		int midiCCControlledNotes[3][100];
		int midiCCControlledSliders[3][100];
		int midiCCControlledLastOn[3];

		bool velocityControlledOutput[3];
		bool velocityControlledCheckBox[3][100];
		int velocityControlledNotes[3][100];
		int velocityControlledSliders[3][100];
		int velocityControlledLastOn[3];

		bool zoneControlledOutput;
		bool zoneControlledCheckBox[100];
		int zoneControlledNotes[100];
		int zoneControlledSliders[100];
		int zoneControlledLastOn;
		
		bool sequenceOutput[3];
		wxString sequenceFile[3];
		bool sequenceOverlap[3];

		bool mouseOutput[3];
		int mouseX[3];
		int mouseY[3];

		bool pedalDownEvent;
		int pedalDownThreshold;
		int storedHighVelocity;
		double highTime;
		int pedalVolume;
		int pedalNote;
		int pedalSpeedIntensity;
		bool pedalDownFlag;

		//Output
		int masterGain; //overall volume adjustment for all zones of an audio track
		int masterVolume; //overall volume adjustment for all zones of a track
		int outputChannel[3]; //output midi channel for each zone  "Status Code"
		int outputNote[3]; //output midi note for each zone
		int outputVelocity[3]; //Used to store mouse wheel velocities.
		int storedVelocity[3]; //Used to store MultiZone velocities.
		bool waitForPiezo; //This is a flag to wait for extra zone velocities on MultiZone tracks.
		double firstPiezoHitTime; //Timestamp of the first piezo hit time on MultiZone tracks.

		int priority[3]; //priority control for up to 3 zones
		int gravity[3]; //Gravitational pull on the position produces on a multi-zone drum.
		int velocityBalance; //Controlls the hotspot of the multi-zone drum.
		char velToPosAvg[127][1000]; //[velocity][position-history] "history of each velocity's position"
		char posToVelAvg[127][1000];	//[position][velocity-history] "history of each position's velocity"
		bool hasRim;
		bool enableCC; 
		int ccOutputChannel;
		int ccOutputNote;
		int ccOutputHighCompressor;
		int ccOutputLowCompressor;

		//TODO:
		//////SoundFolder Output/////
		wxString sampleFolder[3];
};

////////////////
class TrackProc
{
	public:
		TrackProc(TrackPanel *parent);
		~TrackProc();
		void InitVariables();

		void AddTrigger(/*bool InitDefault*/);
		void AddMidiCC(/*bool InitDefault*/);
		void DeleteTrack(int i, bool confirm);
		void DeleteAllTracks();
		void MoveTrack(int num, int to);
		void LinkMidi(Midi *ref);
		void LinkAudio(Audio *ref);
		int DetectLanding(int track, int pos);
		void SetPreLoad(bool pl);

		TrackPanel *trackPanel;
		Audio *audio;
		Midi *midi;
		wxMenu *trackMenu;

		TrackData n[100];

		int tracks;
		int focused;
		bool enableMeters;
		bool preLoad;
		int mouseSensitivity;
		bool midiBleed; //Let unassigned midi bleed through?
		bool midiChannel[16]; //midi channels.
		int retriggerSafty;
		int retriggerThreshold;
		int flamAdjustment;
		int rollAdjustment;
};

#endif //TRACKS_H
