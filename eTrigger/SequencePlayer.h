//// SequencePlayer.h /////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////

#pragma once
#ifndef SEQUENCEPLAYER_H
#define SEQUENCEPLAYER_H

#include <wx/timer.h>
#include "Timer.h"
#include "EtmFile.h"
#include "../lib/Gwidgets/GMeter/GMeter.h"

//class PlaybackTimer;
class Sequence
{
public:
	Sequence(Midi *parent, StatusDialog *sd, wxString fileName, GMeter *meter, bool overlap);
	~Sequence();
	void Kill();

	Midi *midi;
	StatusDialog *statusDialog;
	vector<MIDIDATA> midiData;
	wxString filename;
	GMeter *gmeter;
	bool sequenceOverlap;
	unsigned int i;
	bool play;
	wxStopWatch sw;
};

class SequencePlayer
{
public:
	SequencePlayer();
	~SequencePlayer();
	//void Kill();
	void PlaySequence(Midi *parent, StatusDialog *sd, wxString filename, GMeter *meter, bool overlap);
	void Notify();

	//Midi *midi;
	//StatusDialog *statusDialog;
	

	Sequence *sequence[100];

	//vector<MIDIDATA> midiData;
	//GMeter *gmeter;
	//wxString fileName;
	//bool sequenceOverlap;
	//unsigned int i;
	bool play[100];
};


#endif //SEQUENCEPLAYER_H