//// SoundController.cpp /////////////////////////////////////////////
//
//
/////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "SoundController.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


////////////SoundController///////////////////////
SoundController::SoundController(MainPanel *panel)
{
	mainPanel = panel;
	InitVariables();
}

///////////////////////////////////
SoundController::~SoundController()
{
	UnloadAll();
}

/////////////////////////////////////
void SoundController::InitVariables()
{
	soundFile.clear();

	for(int i=0; i<100; ++i){
		fileName[i] = wxT("");
		soundData[i] = NULL;
		frames[i] = NULL;
		framesLoaded[i] = NULL;
		channels[i] = NULL;
		trigger[i] = NULL;
		position[i] = NULL;
		fileOpen[i] = NULL;
#ifdef SNDFILE
		sndFile[i] = NULL;
#endif
#ifdef MPG123
		mh[i] = NULL;
#endif
		resamplerOpen[i] = NULL;
		resampler[i] = NULL;
	}
}

////////////////////////////////////////////////////////
int SoundController::LoadFile(wxString file, int frames)
{
	UnloadFile(file); //Unload if loaded

	//If not, does it exist?
	if(!wxFile::Exists(file)){ 
		wxMessageBox(wxString(wxT("Cannot locate file: ")) += file);
		return -1; 
	}

///// LOAD WAVE //////////////////////////
#ifdef SNDFILE
	if(file.Contains(wxT(".wav"))){
		SNDFILE *sndFile;
		SF_INFO sfInfo;

		const char* temp = (const char*)file.mb_str(wxConvUTF8);
		sndFile = sf_open(temp, SFM_READ, &sfInfo);    

		sf_seek(sndFile, 0, SEEK_SET); //lets start at the beginning.

		soundFile.push_back(new SoundFile); //FIXME: memory leaks only on bad exit
            //use STL so it can clean itself up?
		    //bad programming :(

		soundFile[soundFile.size()-1]->fileName = file;
		soundFile[soundFile.size()-1]->frames = sfInfo.frames;
		soundFile[soundFile.size()-1]->channels = sfInfo.channels;
		soundFile[soundFile.size()-1]->samplerate = sfInfo.samplerate;
		soundFile[soundFile.size()-1]->format = sfInfo.format;      //what exactly is this?
		soundFile[soundFile.size()-1]->sections = sfInfo.sections;  //and what is this?
		soundFile[soundFile.size()-1]->seekable = sfInfo.seekable;  //and what is this?

		if(frames == -1){
			soundFile[soundFile.size()-1]->framesLoaded = soundFile[soundFile.size()-1]->frames;
		}
		else{
			soundFile[soundFile.size()-1]->framesLoaded = frames;
		}
		
		soundFile[soundFile.size()-1]->soundData = new float[soundFile[soundFile.size()-1]->framesLoaded * sfInfo.channels]; //FIXME: memory leaks sometimes
		sf_readf_float(sndFile, soundFile[soundFile.size()-1]->soundData, soundFile[soundFile.size()-1]->framesLoaded);

		int err = sf_close (sndFile);
		if(err){
			wxMessageBox(wxT("Error in sf_close"));
		}

		//ReSampleSoundFile(soundFile.size()-1, mainPanel->audio->outSampleRate);
		return soundFile.size()-1;
	}
#endif
	
	////// LOAD MP3 ////////////////////////////////
#ifdef MPG123
	if(file.Contains(wxT(".mp3"))){
		
		wxString in = file;
		mpg123_handle *mh = NULL;
		size_t done = 0;
		int channels = 0;
		int encoding = 0;
		long rate = 0;
		int  err  = MPG123_OK;
		off_t samples = 0;
	
		err = mpg123_init();
		const char* temp = (const char*)in.mb_str(wxConvUTF8);
		if( err != MPG123_OK || (mh = mpg123_new(NULL, &err)) == NULL
			|| mpg123_open(mh, temp) != MPG123_OK
			|| mpg123_getformat(mh, &rate, &channels, &encoding) != MPG123_OK ){
			
				wxMessageBox(wxString::Format(wxT("Trouble with mpg123: %s\n"),
		         mh==NULL ? mpg123_plain_strerror(err) : mpg123_strerror(mh) ));
		
			mpg123_close(mh);
			mpg123_delete(mh);
			mpg123_exit();
			return -1;
		}

		if(encoding != MPG123_ENC_SIGNED_16){
			wxMessageBox(wxString::Format(wxT("Bad encoding 0x%x!"), encoding));

			mpg123_close(mh);
			mpg123_delete(mh);
			mpg123_exit();
			return -1;
		}

		mpg123_seek(mh, 0, SEEK_END); //goto the end of the file
		int totalFrames = mpg123_tell(mh) * channels; //get the total number of samples
		
		soundFile.push_back(new SoundFile); //FIXME: memory leaks sometimes
		soundFile[soundFile.size()-1]->fileName = file;
		soundFile[soundFile.size()-1]->frames = (totalFrames / 2);
		soundFile[soundFile.size()-1]->samplerate = rate;
		soundFile[soundFile.size()-1]->channels = channels;
		soundFile[soundFile.size()-1]->format = SF_FORMAT_FLOAT;      //what exactly is this?
		soundFile[soundFile.size()-1]->sections = 0;  //and what is this?
		soundFile[soundFile.size()-1]->seekable = 0;  //and what is this?
		
		if(frames == -1){
			soundFile[soundFile.size()-1]->framesLoaded = soundFile[soundFile.size()-1]->frames;
		}
		else{
			soundFile[soundFile.size()-1]->framesLoaded = frames;
		}
		
		soundFile[soundFile.size()-1]->soundData = new float[soundFile[soundFile.size()-1]->framesLoaded * channels]; //FIXME: memory leaks sometimes

		mpg123_seek(mh, 0, SEEK_SET); //goto the beginning of the file
		////// Read and decode audio data /////
		
		short *mpg123Buffer = new short[soundFile[soundFile.size()-1]->framesLoaded * channels];
		err = mpg123_read( mh, (unsigned char*)mpg123Buffer, soundFile[soundFile.size()-1]->framesLoaded * channels * sizeof(short), &done );
			
		for (unsigned int i=0; i<done/sizeof(short); ++i) {
			soundFile[soundFile.size()-1]->soundData[samples+i] = (float)mpg123Buffer[i] / 32768;
		}

		samples += done/sizeof(short);
		
		delete mpg123Buffer;
		mpg123_close(mh);
		mpg123_delete(mh);
		mpg123_exit();

		//ReSampleSoundFile(soundFile.size()-1, mainPanel->audio->outSampleRate);
		return soundFile.size()-1;
	}
#endif

	return -1;
}

///////////////////////////////////////////////
void SoundController::UnloadFile(wxString file)
{
	//stop playback
	for(unsigned int n=0; n<100; ++n){
		if(file == fileName[n]){
			CloseRequest(n);
			trigger[n] = false;
		}
	}

	for(unsigned int i=0; i<soundFile.size(); ++i){
		if(soundFile[i]->fileName == file){
			delete[] soundFile[i]->soundData;
			delete soundFile[i];
			soundFile.erase(soundFile.begin()+i);
		}
	}
}

/////////////////////////////////
void SoundController::UnloadAll()
{
	//stop all playback
	for(unsigned int n=0; n<100; ++n){
		CloseRequest(n);
		CloseResample(n);
		trigger[n] = false;
	}

	for(unsigned int i=0; i<soundFile.size(); ++i){
		delete[] soundFile[i]->soundData;
		delete soundFile[i];
		soundFile.erase(soundFile.begin()+i);
	}
}


///////////////////////////////////////////////////////////////////////
void SoundController::PlaySound(wxString file, int frame, bool overlap)
{
	int index = -1;
	for(unsigned int i=0; i<soundFile.size(); ++i){
		if(soundFile[i]->fileName == file){
			index = i;
		}
	}

	if(index == -1){
		index = LoadFile(file, 0); //just load info to memory, not audio data.
	}

	if(index == -1){return;}
		
	if(!overlap){StopSound(file);}

	//find the first available spot in the SoundController
	int s=0;
	while(trigger[s] == true){ s++; }

	fileName[s] = soundFile[index]->fileName;
	soundData[s] = soundFile[index]->soundData;
	frames[s] = soundFile[index]->frames;
	framesLoaded[s] = soundFile[index]->framesLoaded;
	channels[s] = soundFile[index]->channels;
	samplerate[s] = soundFile[index]->samplerate;
	position[s] = frame;
	trigger[s] = true;
	return;
}

//////////////////////////////////////////////
void SoundController::StopSound(wxString file)
{
	for(unsigned int s=0; s<100; ++s){
		if(fileName[s] == file){
			position[s] = 0;
			trigger[s] = false;	
			CloseResample(s);
			CloseRequest(s);
		}
	}
}

///////////////////////////////////////////////
void SoundController::PrepairRequest(int index)
{
	//Here we wanna open the file for reading if it's NOT allready open.
	//Then we wanna seek to the current position
	//TODO - more error protection here.

	if(!fileOpen[index]){
#ifdef SNDFILE
		if(fileName[index].Contains(wxT(".wav"))){
			const char* temp = (const char*)fileName[index].mb_str(wxConvUTF8);
			SF_INFO sfInfo;
			sndFile[index] = sf_open(temp, SFM_READ, &sfInfo);
			sf_seek(sndFile[index], (position[index] / channels[index]), SEEK_SET); //lets start from position.
			fileOpen[index] = true;
		}
#endif //SNDFILE

#ifdef MPG123
		if(fileName[index].Contains(wxT(".mp3"))){
			int chans = 0;
			int encoding = 0;
			long rate = 0;
			int  err  = MPG123_OK;
	
			err = mpg123_init();
			const char* temp = (const char*)fileName[index].mb_str(wxConvUTF8);
			if( err != MPG123_OK || (mh[index] = mpg123_new(NULL, &err)) == NULL
				|| mpg123_open(mh[index], temp) != MPG123_OK
				|| mpg123_getformat(mh[index], &rate, &chans, &encoding) != MPG123_OK ){
			
				wxMessageBox(wxString::Format(wxT("Trouble with mpg123: %s\n"),
		         mh[index]==NULL ? mpg123_plain_strerror(err) : mpg123_strerror(mh[index]) ));
		
				mpg123_close(mh[index]);
				mpg123_delete(mh[index]);
				mpg123_exit();
				return;
			}

			if(encoding != MPG123_ENC_SIGNED_16){
				wxMessageBox(wxString::Format(wxT("Bad encoding 0x%x!"), encoding));

				mpg123_close(mh[index]);
				mpg123_delete(mh[index]);
				mpg123_exit();
				return;
			}

			mpg123_seek(mh[index], (position[index] / channels[index]), SEEK_SET); //goto the current position
			fileOpen[index] = true;
		}
#endif
	}
}

/////////////////////////////////////////////
void SoundController::CloseRequest(int index)
{
	//Here we wanna close the file we are reading if it's open.
	//TODO  - more error protection here.

	if(fileOpen[index]){
#ifdef SNDFILE
		if(fileName[index].Contains(wxT(".wav"))){
			int err = sf_close (sndFile[index]);
			if(err){wxMessageBox(wxT("Error in sf_close"));}
			fileOpen[index] = false;
		}
#endif 

#ifdef MPG123
		if(fileName[index].Contains(wxT(".mp3"))){
			mpg123_close(mh[index]);
			mpg123_delete(mh[index]);
			mpg123_exit();
			fileOpen[index] = false;
		}
#endif
	}
}

////////////////////////////////////////////////
void SoundController::PrepairResample(int index)
{
	if(!resamplerOpen[index]){
		//
		resampler[index] = new ReSample(channels[index], ((1.0 * mainPanel->audio->outSampleRate) / samplerate[index]));
		resamplerOpen[index] = true;
	}
}

////////////////////////////////////////////////
void SoundController::CloseResample(int index)
{
	if(resamplerOpen[index]){
		//
#ifdef SAMPLERATE
		resampler[index]->src_state = src_delete(resampler[index]->src_state);
#endif
		delete resampler[index];
		resampler[index] = NULL;
		resamplerOpen[index] = false;
	}
}

////////////////////////////////////////
void SoundController::CheckSampleRates()
{
	for(unsigned int i=0; i<soundFile.size(); ++i){
		if(soundFile[i]->samplerate != mainPanel->audio->outSampleRate){
			wxString fileName = soundFile[i]->fileName;
			int frames = soundFile[i]->framesLoaded;
			UnloadFile(fileName);
			LoadFile(fileName, frames);
		}
	}
}

//////////////////////////////////////////////////////////////////
void SoundController::ReSampleSoundFile(int index, int samplerate)
{
#ifdef SNDFILE
	if(soundFile[index]->samplerate != samplerate){
		soundFile.push_back(new SoundFile); //FIXME: memory leaks sometimes

		soundFile[soundFile.size()-1]->fileName = soundFile[index]->fileName;
		soundFile[soundFile.size()-1]->frames = soundFile[index]->frames * ((1.0 * samplerate) / soundFile[index]->samplerate);
		soundFile[soundFile.size()-1]->framesLoaded = soundFile[index]->framesLoaded * ((1.0 * samplerate) / soundFile[index]->samplerate);
		soundFile[soundFile.size()-1]->channels = soundFile[index]->channels;
		soundFile[soundFile.size()-1]->samplerate = samplerate;
		soundFile[soundFile.size()-1]->format = soundFile[index]->format;      //what exactly is this?
		soundFile[soundFile.size()-1]->sections = soundFile[index]->sections;  //and what is this?
		soundFile[soundFile.size()-1]->seekable = soundFile[index]->seekable;  //and what is this?

		//soundFile[soundFile.size()-1]->soundData = new float[soundFile[soundFile.size()-1]->framesLoaded * soundFile[soundFile.size()-1]->channels];
		float *temp = new float[soundFile[soundFile.size()-1]->framesLoaded * soundFile[soundFile.size()-1]->channels * 2];

		int startSample = 0;
		/*
		ReSample resampler;
		int framesGenerated = resampler.libsamplerate(((1.0 * samplerate) / soundFile[index]->samplerate), soundFile[index]->soundData, soundFile[index]->channels,
			                    startSample, soundFile[index]->framesLoaded, temp, soundFile[soundFile.size()-1]->framesLoaded * 2);
		*/

		//soundFile[soundFile.size()-1]->framesLoaded = framesGenerated;
		//soundFile[soundFile.size()-1]->soundData = new float[framesGenerated * soundFile[index]->channels];

		/*
		for(int i=0; i< (framesGenerated * soundFile[index]->channels); ++i){
			soundFile[soundFile.size()-1]->soundData[i] = temp[i];
		}
		*/
		delete temp;
		

		delete[] soundFile[index]->soundData;
		delete soundFile[index];
		soundFile.erase(soundFile.begin()+index);
	}
#endif
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundController::RequestData(int index, float *output, int bufferSize, int bufferPosition, int outSamplerate, int outChannels)
{
	///////// WAV FILE ///////////////////////
#ifdef SNDFILE
	if(fileName[index].Contains(wxT(".wav"))){

			float *tempOut = new float[(bufferSize * outChannels) - bufferPosition];
			sf_readf_float(sndFile[index], tempOut, (((bufferSize * outChannels)- bufferPosition) / channels[index]) );

			for(int i=bufferPosition; i < (bufferSize * outChannels); ++i){
				output[i] += tempOut[i-bufferPosition];
				++position[index];
				if(position[index] >= (frames[index] * channels[index])){
					i = (bufferSize * outChannels);
				}
			}

			delete tempOut;
	}
#endif

#ifdef MPG123
	///////// MP3 FILE ///////////////////////
	if(fileName[index].Contains(wxT(".mp3"))){
		
		short *mpg123Buffer = new short[bufferSize - bufferPosition];
		size_t done = 0;
		mpg123_read( mh[index], (unsigned char*)mpg123Buffer, (bufferSize - bufferPosition) * sizeof(short), &done );
			
		for(int i=bufferPosition; i < bufferSize; ++i){
			output[i] += ((float)mpg123Buffer[i-bufferPosition] / 32768);
			++position[index];
			if(position[index] >= (frames[index] * channels[index])){i = bufferSize;}
		}

		delete mpg123Buffer;
	}
#endif
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void SoundController::RequestAudio(float *out, int frameBuffer, int outSamplerate, int outChannels)
{
	for(unsigned int v=0; v<100; ++v){ //check all voices

		if(trigger[v]){
			for(int i=0; i<frameBuffer*outChannels; ++i){ //mix the temp buffer into the output buffer.
				
				if(position[v] < (frames[v] * channels[v]) && trigger[v]){
					
					//Play whatever is loaded in memory	
					if(position[v] < (framesLoaded[v] * channels[v])){
							PrepairResample(v);
#ifdef RESAMPLE
							int output =  resampler[v]->libresample(((1.0 * outSamplerate) / samplerate[v]), soundData[v], channels[v],
								position[v], framesLoaded[v], out, frameBuffer);

							i = output * outChannels;
#endif RESAMPLE
					}
					
					//Play the rest From file
					else{
						PrepairResample(v);
						PrepairRequest(v);
						RequestData(v, out, frameBuffer, i, outSamplerate, outChannels);
						i = frameBuffer * outChannels; //we are done filling the frames for this trigger
					}
				}

				else{
					CloseResample(v);
					CloseRequest(v);
					position[v] = 0;
					trigger[v] = false; //we reached the end, turn the trigger off.
					i = frameBuffer * outChannels; //we are done with this loop
				}
			}//frameBuffer
		}//triggers
	}//voices
}

//////// Learn Thread //////////////////////////////////////////////
LoadSoundThread::LoadSoundThread(SoundController *sc, wxString file) 
				: wxThread()
{
	soundController = sc;
	Create();
	Run();
}

//////////////////////////////
void *LoadSoundThread::Entry()
{
	return 0;
}