//// SoundController.h /////////////////////////////////////////////////////////////
// 
//   This class is our SoundLibrary and Controller
//   We can load .wav files to memory.
//   Unload files.
//   Use the SoundController to stream files into the callback at mutiple voices
//
//   *Soon*
//   Resample the files to match the audio output
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef SOUNDCONTROLLER_H
#define SOUNDCONTROLLER_H

//// libsndfile ///////
#include    <stdio.h>
#include    <stdlib.h>

#ifdef SNDFILE
#include "../lib-src/libsndfile/Win32/sndfile.h"
#endif

#ifdef MPG123
#include    <mpg123.h>
#endif

#include "MainPanel.h"
#include "ReSample.h"

#include <vector>
using namespace std;

class MainPanel;
class SoundFile;

/////////////////////
class SoundController
{
public:
	SoundController(MainPanel *panel);
	~SoundController();
	void InitVariables();

	// LOAD/PLAY/UNLOAD
	void RequestAudio(float *out, int frameBuffer, int outSamplerate, int outChannels);
	int LoadFile(wxString file, int frames); //returns -1 on fail and index number on success
	void PrepairRequest(int index);
	void RequestData(int index, float *output, int bufferSize, int bufferPosition, int outSamplerate, int outChannels);
	void CloseRequest(int index);
	void PrepairResample(int index);
	void CloseResample(int index);
	void UnloadFile(wxString file);
	void UnloadAll();
	void PlaySound(wxString file, int frame, bool overlap);
	void StopSound(wxString file);
	void CheckSampleRates();
	void ReSampleSoundFile(int index, int samplerate);

	vector<SoundFile*> soundFile; //Sound File Database

	//play up to 100 voices at a time.
	wxString fileName[100];
	float *soundData[100];
	int frames[100];
	int framesLoaded[100];
	int channels[100];
	int samplerate[100];
	bool trigger[100];
	int position[100];

	//for reading wav and mp3 from file
	bool fileOpen[100];
#ifdef SNDFILE
	SNDFILE *sndFile[100];  //for reading wav
#endif

#ifdef LIBMPG123
	mpg123_handle *mh[100]; //for reading mp3
#endif //LIBMPG123

	//for resampling
	bool resamplerOpen[100];
	ReSample *resampler[100];

	MainPanel *mainPanel;
};



////////////////
class SoundFile 
{
public:
	//int index;
	wxString fileName;
	float *soundData;
	int frames;
	int framesLoaded;
    int samplerate;
    int channels;
    int format;
    int sections;
    int seekable;
};


////// LoadSoundThread ////////////////
class LoadSoundThread : public wxThread
{
	public:
		LoadSoundThread(SoundController *sc, wxString file);
		~LoadSoundThread(){};
		void *Entry();

		SoundController *soundController;
};

#endif //SOUNDCONTROLLER_H