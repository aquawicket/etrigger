//// SequencerDialog.h ////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef SEQUENCERDIALOG_H
#define SEQUENCERDIALOG_H

#include "MainPanel.h"
#include "Midi.h"
#include "EtmFile.h" //for MIDIDATA struct
#include "Timer.h"

class Grid; 
//class PTimer;

//////////////////////////////////////
class SequencerDialog: public wxDialog
{
public:
	SequencerDialog(MainPanel *parent);
	~SequencerDialog();
	void Notify();

	void OnSize(wxSizeEvent &event);
	void OnScroll(wxScrollEvent &event);
	void OnRewind(wxCommandEvent &event);
	void OnBackward(wxCommandEvent &event);
	void OnPlay(wxCommandEvent &event);
	void OnRecord(wxCommandEvent &event);
	void OnStop(wxCommandEvent &event);
	void Stop();
	void OnForward(wxCommandEvent &event);
	void OnSave(wxCommandEvent &event);
	void OnClear(wxCommandEvent &event);
	void UpdateDlg();

    void AddNoteOn(long time, int channel, int note, int velocity);
	void AddNoteOff(long time, int channel, int note);
	void AddMidiCC(long time, int channel, int note, int velocity);
	void SetCursor(int x);
	int GetNextNote();
	void LoadMidiFile();
	void SaveMidiFile();
	void RecieveMessage(std::vector<unsigned char> &message);

	MainPanel *mainPanel;

	unsigned int hScrollPosition;
	wxScrollBar *hScrollBar;

	wxString seqDir;
	wxString seqFile;

	wxButton *rewind;
	wxButton *backward;
	wxButton *playButton;
	wxButton *stop;
	wxButton *recordButton;
	wxButton *forward;

	wxButton *save;
	wxButton *clear;

	Grid *grid;
	bool play;
	bool record;
	wxStopWatch sw;
	unsigned int i;
	//PTimer *time;

	DECLARE_EVENT_TABLE();
};




//////////////////////////
class Grid: public wxPanel
{
public:
	Grid(SequencerDialog *parent);
	void OnPaint(wxPaintEvent &event); 
	void CheckCursor();
	void DrawGrid(wxDC &dc);
	void DrawMidi(wxDC &dc);
	void DrawCursor(wxDC &dc);
	void OnMouse(wxMouseEvent &event);

	int GetHRange();

	SequencerDialog *sequencerDialog;

	int startGap;
	int cursorPosition;
	vector<MIDIDATA> midiData;

	DECLARE_EVENT_TABLE();
};


#endif SEQUENCERDIALOG_H