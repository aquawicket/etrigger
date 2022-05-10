//// EtmFile.h //////////////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef ETMFILE_H
#define ETMFILE_H

#include <wx/stopwatch.h>
#include "SoundController.h"
#include "DirSearch.h"

typedef struct{
	int midiType; //0 = noteOn, 1 = noteOff, 2 = midiCC
	int drumType; //1 = kick, 2 = snare, 4 = HiHat,   and so on...
	int timestamp;
	int channel;
	int note;
	int velocity;
	int dificulty; //1-10
}MIDIDATA;


//////////////
class EtmFile
{
public:
	EtmFile(SoundController *controller);
	~EtmFile();
	void InitVariables();

	wxArrayString GetEtmFolders();
	void New();
	void Load();
	void Save();
	void Close();
	void Play();
	void Record();
	void Stop();
	void Pause();
	void Resume();
	void SetPosition(int millisecond);
	void FindAudio();
	void ImportAudio();
	void LoadAudio();
	void UnloadAudio();
	void SaveMidi();
	void LoadMidi();
	void GetDrumTypes(); 
	void SetTypeToLine();
	void AddNoteOn(long time, int type, int velocity);
	void AddNoteOff(long time, int type);
	void AddMidiCC(long time, int type, int velocity);
	int GetNextNote();
	int GetLengthInMs();

	vector<MIDIDATA> midiData; //Don't forget about dificulty level.
	vector<int> drumTypes;
	int typeToLine[25]; //which line to put the drum on.

	SoundController *soundController;
	SoundFile *soundFile;

	wxString etmDir;
	wxString etmFile;
    wxString audioFile;

	wxStopWatch *timeStamp; //current timestamp
	unsigned int nextMidiNote; 

	bool playing;
	bool recording;

	wxString songTitle;
	int goodHits;
	int badHits;
	int missedHits;
};
#endif //ETMFILE_H