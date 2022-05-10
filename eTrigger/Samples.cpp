//// Samples.cpp //////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "Samples.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/////////////////////////////////////
Samples::Samples(SoundController *sc) 
{
	soundController = sc;
	wxStandardPaths stdPath; 
    wxString fileLocation = stdPath.GetExecutablePath();
	sampleDir = wxFileName(fileLocation).GetPath() += wxT("\\Samples");
}

///////////////////
Samples::~Samples() 
{
}

/////////////////////////////////////////
wxArrayString Samples::GetSampleFolders()
{
	//FIXME
	/*
	//return all of the folders that have a Audio.wav file.
	wxArrayString files, dirs;
	wxSimpleDirTraverser traverser(files, dirs);
	wxDir dir(sampleDir);
	dir.Traverse(traverser);


	sampleFolders.Clear();
	for(unsigned int i=0; i<dirs.Count(); ++i)
	{
		wxString temp = dirs.Item(i);
		if(::wxFileExists(temp += wxT("\\Sample.txt"))){
			sampleFolders.Add(dirs.Item(i), 1);
		}
		
	}
	*/
	return sampleFolders;
}

///////////////////////////////////////
wxArrayString Samples::GetSampleNames()
{
	sampleNames.Clear();

	//cycle throught the sample folders
	for(unsigned int i=0; i<sampleFolders.Count(); ++i){

		wxString temp = sampleFolders.Item(i);
		if(::wxFileExists(temp += wxT("\\Sample.txt"))){
			wxTextFile file(temp);
			file.Open(wxConvAuto());
			wxString temp2 = file.GetFirstLine();
			sampleNames.Add(temp2, 1);
			file.Close();
		}
	}

	return sampleNames;
}

//////////////////////////////////////////////////
wxString Samples::GetFolderFromName(wxString name)
{
	for(unsigned int i=0; i<sampleFolders.Count(); ++i){
		wxString temp = sampleFolders.Item(i);
		if(::wxFileExists(temp += wxT("\\Sample.txt"))){
			wxTextFile file(temp);
			file.Open(wxConvAuto());
			wxString temp2 = file.GetFirstLine();
			file.Close();

			if(temp2 == name){
				return sampleFolders.Item(i);
			}
		}
	}

	return wxT("");
}

////////////////////////////////////////////////////
wxString Samples::GetNameFromFolder(wxString folder)
{
	folder += wxT("\\Sample.txt");
	wxTextFile file(folder);
	file.Open(wxConvAuto());
	wxString temp2 = file.GetFirstLine();
	file.Close();
	return temp2;
}

///////////////////////////////////////////////////////
void Samples::PlaySample(wxString folder, int velocity)
{
	wxString file = folder += wxT("\\Sample");
	file += ConvTowxString(velocity);
	file += wxT(".wav");
	soundController->PlaySound(file, 0, true);
}