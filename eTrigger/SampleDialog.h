//// SampleDialog.h /////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////

#pragma once
#ifndef SAMPLEDIALOG_H
#define SAMPLEDIALOG_H

#include "../lib/Gwidgets/GImage/GImage.h"
#include "TriggerDialog.h"

class MainPanel;
class TriggerDialog;

//////////////////////////////////////////////////////////
class SampleDialog : public wxDialog
{
	public:
		SampleDialog(TriggerDialog* parent);
		~SampleDialog();
		void SetActiveSample(wxString folder);
		void UpdateDialog();
		void PopulateSamples();
		void OnSampleSelection(wxCommandEvent &event);
		void OnImport(wxCommandEvent &event);

		TriggerDialog *triggerDialog;
		MainPanel *mainPanel;

		wxListBox *samples;
		wxStaticText *sampleFolder;
		GImage *image;
		wxButton *import;

		DECLARE_EVENT_TABLE()
};

#endif SAMPLEDIALOG_H
