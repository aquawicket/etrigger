//// EtmPlayerOptions.h ///////////////////////////////
//
//
///////////////////////////////////////////////////////

#pragma once
#ifndef ETMPLAYEROPTIONS_H
#define ETMPLAYEROPTIONS_H

#include "EtmPlayerDialog.h"

class EtmPlayerDialog;

////////////////////////////////////////
class EtmPlayerOptions : public wxDialog
{
public:
	EtmPlayerOptions(EtmPlayerDialog *parent);
	~EtmPlayerOptions();
	void OnOk(wxCommandEvent &event);
	void OnCancel(wxCommandEvent &event);
	void OnClose(wxCloseEvent &event);
	void VarsToTemp();
	void VarsToDlg();
	void TempToVars();
	void TempToDlg();

	void OnSpeed(wxScrollEvent &event);
	void OnLatency(wxScrollEvent &event);
	void OnLineSmoothing(wxCommandEvent &event);

	EtmPlayerDialog *etmPlayerDialog;

	wxSlider *speedSlider;
	wxSlider *latencySlider;
	wxCheckBox *lineSmoothingBox;
	wxButton *ok;
	wxButton *cancel;

	//Temp Variables
	float speed;
	int latency;
	bool lineSmoothing;

	DECLARE_EVENT_TABLE()
};


#endif //ETMPLAYEROPTIONS_H