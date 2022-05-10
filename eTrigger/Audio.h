////  Audio.h  ////////////////////////////////////////////////////////////////////////
//
//  Audio's job is to interface with audio cards and provide input and output. 
//
///////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef AUDIO_H
#define AUDIO_H

#include <vector>
#include <wx/arrstr.h>
#include <wx/msgdlg.h>

#include "Tracks.h"
#include "Process.h"
#include "SoundController.h"
#include "ReSample.h"

// portaudio
#ifdef PORTAUDIO
#include "../lib-src/portaudio/include/portaudio.h"
#include "../lib-src/portaudio/include/pa_asio.h"
#include "../lib-src/portaudio/src/common/pa_trace.h"
#endif

#include "Timer.h"


class TrackProc;

//#define PA_SAMPLE_TYPE     paFloat32 | paNonInterleaved

//Device class to send to callback
///////////////////////////////////
typedef struct{
#ifdef PORTAUDIO
		PaStreamParameters inDev;
		PaStream *stream;
		const PaDeviceInfo *info;
#endif
		double threshold[100]; //100 channels
		float history[10]; //up to 10 channels
		int framesSincePeak[10]; 

		float history2[5]; //up to 5 channels
		float history3[5]; //up to 5 channels. three history slots
		float thePeak;
		float absolute;
}InDevice;

/// Output ///////////////////////////
typedef struct{
#ifdef PORTAUDIO
		PaStreamParameters outDev;
		PaStream *stream;
		const PaDeviceInfo *info;
#endif
}OutDevice;


///////////
class Audio
{
public:
	Audio(TrackProc *ref);
	~Audio();
	void InitVariables();

	// API handling
	wxArrayString GetInDeviceAPIs();
	void SetInAPI(wxString API);
	wxArrayString GetOutDeviceAPIs();
	void SetOutAPI(wxString API);
	wxString selectedInAPI;
	wxString selectedOutAPI;
	void OpenAsioControlPanel(wxString deviceName);

	// Device handling
	wxArrayString GetInDevices(wxString API);
	int SetInDevice(wxString in, int num);
	void SetInDevices(wxArrayString in);
	wxArrayString GetOutDevices(wxString API);
	int SetOutDevice(wxString in, int num);
	void SetOutDevices(wxArrayString in);

	// Audio Buffer handling
	void SetAudioBuffer(int size);

	// Sample Rate handling
    int GetInSampleRate();
	void SetInSampleRate(int rate);
	int GetOutSampleRate();
	void SetOutSampleRate(int rate);

	void LearnThreshold();
	
	void StopCallback();
	void StartCallback();
	void KillStreams();

#ifdef PORTAUDIO
	static int InCallBack( const void *inputBuffer, void *outputBuffer,
                           unsigned long frameBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData );

	static int OutCallBack( const void *input, void *output, unsigned long frameBuffer,
					        const PaStreamCallbackTimeInfo* paTimeInfo, 
							PaStreamCallbackFlags statusFlags, 
							void *userData );
#endif

	static TrackProc *trackProc;

    wxArrayString selectedIn;
    wxArrayString selectedOut;
	std::vector<InDevice> inDevice;
	std::vector<OutDevice> outDevice;

	//////// PORTAUDIO ////////
#ifdef PORTAUDIO
	PaError err;
#endif
	int inSampleRate;
	static int outSampleRate;
	int framesPerBuffer;

	//Threshold
	static bool learningThreshold;
	static wxDialog *learning;
	static Timer timer;
	static double learnStartTime;
	double latency;	

	static bool paused;
};

#endif //AUDIO_H
