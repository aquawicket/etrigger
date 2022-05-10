//// EtmFile.cpp //////////////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "EtmFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////
EtmFile::EtmFile(SoundController *controller)
{
	InitVariables();

	soundController = controller;

	wxStandardPaths stdPath; 
    wxString fileLocation = stdPath.GetExecutablePath();
	etmDir = wxFileName(fileLocation).GetPath() += wxT("\\Player\\");

	timeStamp = new wxStopWatch();
	timeStamp->Pause();
}

///////////////////
EtmFile::~EtmFile()
{
	delete timeStamp;
}

/////////////////////////////
void EtmFile::InitVariables()
{
	midiData.clear(); 
	drumTypes.clear();
	for(int i=0; i<25; ++i){typeToLine[i] = NULL;}
	soundController = NULL;
	soundFile = NULL;
	etmDir = wxT("");
	etmFile = wxT("");
	audioFile = wxT("");
	timeStamp = NULL;
	nextMidiNote = NULL; 
	playing = NULL; 
	recording = NULL; 
	songTitle = wxT("");
	goodHits = NULL; 
	badHits = NULL; 
	missedHits = NULL; 
}

///////////////////
void EtmFile::New()
{
	Close();
	int response;

	wxFileDialog *fileDlg = new wxFileDialog(NULL, wxString(wxT("New eTrigger Media")), etmDir, etmFile, 
		                                    wxString(wxT("eTrigger Media (*.etm)|*.etm")), wxFD_SAVE | wxFD_OVERWRITE_PROMPT, wxDefaultPosition);

	response = fileDlg->ShowModal();

	if(response == wxID_OK){
		etmFile = fileDlg->GetFilename();
		SaveMidi();
		FindAudio();
		LoadAudio();
	}

	delete fileDlg;
}

////////////////////
void EtmFile::Load()
{
	Stop();

	int response;
	wxFileDialog *fileDlg = new wxFileDialog(NULL, wxString(wxT("Load eTrigger Media")), etmDir, wxString(wxT("")), 
		                                    wxString(wxT("eTrigger Media (*.etm)|*.etm")), wxFD_OPEN | wxFD_FILE_MUST_EXIST, wxDefaultPosition);
	response = fileDlg->ShowModal();

	if(response == wxID_OK){
		etmFile = fileDlg->GetFilename();
		LoadMidi();
		FindAudio();
		LoadAudio();
	}

	delete fileDlg;
}

////////////////////
void EtmFile::Save()
{
	Stop();

	if(soundFile == NULL){
		wxMessageBox(wxT("Please Import an audio file first"));
		return;
	}

	if(etmFile != wxT("")){
		SaveMidi();
		FindAudio();
		LoadAudio();
		wxMessageBox(wxString::Format(wxT("SAVED - %s"), etmFile));
	}

	/*
	int response;
	wxFileDialog *fileDlg = new wxFileDialog(NULL, wxString(wxT("Save eTrigger Media")), etmDir, etmFile, 
		                                    wxString(wxT("eTrigger Media (*.etm)|*.etm")), wxSAVE | wxOVERWRITE_PROMPT, wxDefaultPosition);
	response = fileDlg->ShowModal();
	if(response == wxID_OK){
		etmFile = fileDlg->GetFilename();
		SaveMidi();
		FindAudio();
		LoadAudio();
	}
	delete fileDlg;
	*/
}

/////////////////////
void EtmFile::Close()
{
	Stop();
	etmFile = wxT("");
	midiData.clear();
	songTitle = wxT("");
	UnloadAudio();
}

////////////////////
void EtmFile::Play()
{
	Stop();

	if(etmFile == wxT("")){
		wxMessageBox(wxT("Please load or create an etm file."));
		return;
	}

	if(soundFile != NULL){
		goodHits = 0;
		badHits = 0;
		missedHits = 0;

		playing = true;
		recording = false;
		timeStamp->Start(timeStamp->Time());
		
		int frame = ( (timeStamp->Time() / 1000) * (soundFile->samplerate * soundFile->channels) );
		wxString temp = etmDir;
		soundController->PlaySound(temp += audioFile, frame, false);
	}
	else{
		wxMessageBox(wxT("Please Import an audio file first"));
		return;
	}
}

//////////////////////
void EtmFile::Record()
{
	//Stop();

	if(etmFile == wxT("")){
		wxMessageBox(wxT("Please load or create an etm file."));
		return;
	}

	if(soundFile != NULL){
		playing = false;
		recording = true;
		timeStamp->Start(timeStamp->Time());
	
		int frame = ( (timeStamp->Time() / 1000) * (soundFile->samplerate * soundFile->channels) );
		wxString temp = etmDir;
		soundController->PlaySound(temp += audioFile, frame, false);
	}
	else{
		wxMessageBox(wxT("Please Import an audio file first"));
		return;
	}
}

////////////////////
void EtmFile::Stop()
{
	wxString temp = etmDir;
	soundController->StopSound(temp += audioFile);

	playing = false;
	recording = false;
	timeStamp->Pause();
	SetPosition(0);
}

/////////////////////
void EtmFile::Pause()
{
	wxString temp = etmDir;
	soundController->StopSound(temp += audioFile);

	playing = false;
	recording = false;
	timeStamp->Pause();
}
//////////////////////
void EtmFile::Resume()
{
	if(etmFile == wxT("")){
		wxMessageBox(wxT("Please load or create an etm file."));
		return;
	}

	if(soundFile != NULL){
		goodHits = 0;
		badHits = 0;
		missedHits = 0;

		playing = true;
		recording = false;
		timeStamp->Start(timeStamp->Time());
		
		int frame = ( (timeStamp->Time() / 1000) * (soundFile->samplerate * soundFile->channels) );
		wxString temp = etmDir;
		soundController->PlaySound(temp += audioFile, frame, false);
	}
	else{
		wxMessageBox(wxT("Please Import an audio file first"));
		return;
	}
}
//////////////////////////////////////////
void EtmFile::SetPosition(int millisecond)
{
	if(millisecond < 0){millisecond = 0;}
	timeStamp->Start(millisecond);
	timeStamp->Pause();
	nextMidiNote = GetNextNote();
}

/////////////////////////
void EtmFile::FindAudio()
{
	//we take the etmFile name and try to find it's audio file.
	wxString temp = etmDir;
	wxString audio = etmFile;
	audio.Replace(wxT(".etm"), wxT(".wav"));

	if(wxFile::Exists(temp += audio)){
		audioFile = audio;
		return;
	}

	temp = etmDir;
	audio.Replace(wxT(".wav"), wxT(".mp3"));
	if(wxFile::Exists(temp += audio)){
		audioFile = audio;
		return;
	}

	audioFile = wxT("");
}

///////////////////////////
void EtmFile::ImportAudio()
{
	int response;
	wxFileDialog *fileDlg = new wxFileDialog(NULL, wxString(wxT("Import Audio")), wxT(""), wxString(wxT("")), 
		                                    wxString(wxT("Audio files (*.wav;*.mp3)|*.wav;*.mp3|WAVE files (*.wav)|*.wav|MP3 files (*.mp3)|*.mp3")), wxFD_OPEN | wxFD_FILE_MUST_EXIST, wxDefaultPosition);
	response = fileDlg->ShowModal();

	if(response == wxID_OK){
		wxString fileDirectory = fileDlg->GetDirectory();
		wxString fileName = fileDlg->GetFilename();
		
		wxString audio = etmFile;
		wxString extention = fileDlg->GetFilename().AfterLast('.');
		audio.Replace(wxT("etm"), extention);

		if(etmFile == wxT("")){
			wxMessageBox(wxT("Please Create or Load an etm file first"));
			delete fileDlg;
			return;
		}

		wxString temp = etmDir;
		if(wxFile::Exists(temp += audio)){
			//FIXME: we need an overwrite confrimmation here
		}
			
		fileDirectory += wxT("\\");
		::wxCopyFile(fileDirectory += fileName, temp, true);
		FindAudio();
		LoadAudio();
	}

	delete fileDlg;
}

/////////////////////////
void EtmFile::LoadAudio()
{
	if(audioFile != wxT("")){
		wxString temp = etmDir;
		int index = soundController->LoadFile(temp += audioFile, -1);
		if(index != -1){
			soundFile = soundController->soundFile[index];
		}
	}
}

///////////////////////////
void EtmFile::UnloadAudio()
{
	wxString temp = etmDir;
	soundController->UnloadFile(temp += audioFile);
	soundFile = NULL;
}

////////////////////////
void EtmFile::SaveMidi()
{
	wxString temp = etmDir;
	wxFile*	file = new wxFile(temp += etmFile, wxFile::write);
	if(file->IsOpened()){
		int vectorSize = midiData.size();
		file->Write(&vectorSize, sizeof(vectorSize));	
		for(int z=0; z<vectorSize; ++z){
			file->Write(&midiData[z], sizeof(midiData[z]));
		}
	}
	file->Close();
	delete file;

	GetDrumTypes();
	SetTypeToLine();
}

////////////////////////
void EtmFile::LoadMidi()
{
	wxString temp = etmDir;
	wxFile* file = new wxFile(temp += etmFile, wxFile::read);
	if(file->IsOpened()){
		if(!file->Eof()){

			midiData.clear();
			int vectorSize;
			file->Read(&vectorSize, sizeof(vectorSize));
			for(int z=0; z<vectorSize; ++z){
				MIDIDATA temp;
				file->Read(&temp, sizeof(temp));
				midiData.push_back(temp);
			}
		}
	}
	file->Close();
	delete file;

	GetDrumTypes();
	SetTypeToLine();
}






////////////////////////////
void EtmFile::GetDrumTypes()
{
	drumTypes.clear();
	bool exists = false;

	for(unsigned int i=0; i<midiData.size(); ++i){
		exists = false;
		for(unsigned int d=0; d<drumTypes.size(); ++d){
			if(midiData[i].drumType == drumTypes[d]){
				exists = true;
			}
		}
		if(!exists){
			drumTypes.push_back(midiData[i].drumType);
		}
	}
}

//////////////////////////////
void EtmFile::SetTypeToLine()
{
	typeToLine[0] = 0; //default / no drum type
	typeToLine[1] = 0; //Kick Drum
	typeToLine[2] = 0; //Hi-Hat Pedal

	int line = 1;
	for(int l=3; l<25; ++l){ //All Other Drums
		typeToLine[l] = 0;
		for(unsigned int t=0; t < drumTypes.size(); ++t){
			if(drumTypes[t] == l){ //the drum exists in the midi data.
				typeToLine[l] = line;
				++line;
				break;
			}
		}
	}
}

//////////////////////////
int EtmFile::GetNextNote()
{
	if(midiData.size() == 0){return 0;}

	// Find the next i from the position
	unsigned int nextMidiNote=0;
	while( nextMidiNote < midiData.size()-1 && timeStamp->Time() > midiData[nextMidiNote].timestamp){
		++nextMidiNote;
	}
	return nextMidiNote;
}

////////////////////////////
int EtmFile::GetLengthInMs()
{
	if(soundFile != NULL){
		return (soundFile->frames / soundFile->samplerate) * 1000;
	}
	else{
		return 0;
	}
}

////////////////////////////////////////////////////////////////////////
void EtmFile::AddNoteOn(long time, int type, int velocity)
{
	MIDIDATA temp;
	temp.midiType = 0;
	temp.drumType = type;
	temp.dificulty = 0;
	temp.timestamp = time;
	temp.velocity = velocity;

	temp.note = 0;
	temp.channel = 0;
	
	if(midiData.size() == 0){midiData.push_back(temp); return;}
	
	//Insert into the right slot according to timestamp.
	unsigned int i = 0;
	while(i < midiData.size()){
		if(time > midiData[i].timestamp){
			++i;
		}
		else{
			break;
		}
	}

	midiData.insert( midiData.begin() + i, temp );
}

///////////////////////////////////////////////
void EtmFile::AddNoteOff(long time, int type)
{
	MIDIDATA temp;
	temp.midiType = 1;
	temp.drumType = type;
	temp.dificulty = 0;
	temp.timestamp = time;
	temp.velocity = 0;

	temp.note = 0;
	temp.channel = 0;
	
	if(midiData.size() == 0){midiData.push_back(temp); return;}
	
	//Insert into the right slot according to timestamp.
	unsigned int i = 0;
	while(i < midiData.size()){
		if(time > midiData[i].timestamp){
			++i;
		}
		else{
			break;
		}
	}

	midiData.insert( midiData.begin() + i, temp );
}

////////////////////////////////////////////////////////////////////////
void EtmFile::AddMidiCC(long time, int type, int velocity)
{
	MIDIDATA temp;
	temp.midiType = 2;
	temp.drumType = type;
	temp.dificulty = 0;
	temp.timestamp = time;
	temp.velocity = velocity;

	temp.note = 0;
	temp.channel = 0;
	
	if(midiData.size() == 0){midiData.push_back(temp); return;}
	
	//Insert into the right slot according to timestamp.
	unsigned int i = 0;
	while(i < midiData.size()){
		if(time > midiData[i].timestamp){
			++i;
		}
		else{
			break;
		}
	}

	midiData.insert( midiData.begin() + i, temp );
}