//// Midi.h //////////////////////////////////////////////////////////////////////////
//
//  Midi's job is to interface with Midi Input and Output Devices.
//
//
///////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef MIDI_H
#define MIDI_H

#include <wx/arrstr.h>
#include "Tracks.h"
#include "Process.h"
#include "../lib/RtMidi/RtMidi.h"

class TrackProc;

typedef struct{
	RtMidiIn rtIn;
	int deviceNumber;
	wxString deviceName;
}MIDIIN;

///////////////
class Midi
{
	public:
		Midi(TrackProc *ref);
		~Midi();

		void SetMidiEngine(int engine);
		wxArrayString GetInDevices();
		wxArrayString GetOutDevices();
		void SetInDevice(wxString in, int num);
		void SetInDevices(wxArrayString in);
		void SetOutDevice(wxString out, int num);
		void SetOutDevices(wxArrayString in);
		void StopCallback();
		void StartCallback();
		void SendMessage( std::vector<unsigned char> *message );
		static void callback( double deltatime, std::vector< unsigned char > *message, void *userData );

		TrackProc *trackProc;
		int midiEngine; //1 - RtMidi, 2 - PortMidi
        static bool active;

		std::vector<MIDIIN*> midiin;
		std::vector<RtMidiOut*> midiout;
		wxArrayString selectedIn;
		wxArrayString selectedOut;
};

#endif //MIDI_H

