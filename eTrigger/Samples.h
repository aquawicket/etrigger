//// Samples.h /////////////////////////////////////////////////
//
//   Samples will be located in a directory.
//
///////////////////////////////////////////////////////////////

#pragma once
#ifndef SAMPLES_H
#define SAMPLES_H

#include <wx/textfile.h>
#include "DirSearch.h"

class Samples
{
	public:
		Samples(SoundController *sc);
		~Samples();
		wxArrayString GetSampleFolders();
		wxArrayString GetSampleNames();
		wxString GetFolderFromName(wxString name);
		wxString GetNameFromFolder(wxString folder);
		void PlaySample(wxString folder, int velocity);

		SoundController *soundController;
		wxString sampleDir;
		wxArrayString sampleFolders;
		wxArrayString sampleNames;
};
    

#endif SAMPLES_H