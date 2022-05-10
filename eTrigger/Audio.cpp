//// Audio.cpp /////////////////////////////////////////////////
// 
// 
/////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "Audio.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

TrackProc *Audio::trackProc = NULL;
bool Audio::paused = NULL;
Timer Audio::timer;
double Audio::learnStartTime = NULL;
bool Audio::learningThreshold = false;
wxDialog *Audio::learning;
int Audio::outSampleRate = NULL;

////////////////////////////
Audio::Audio(TrackProc *ref)
{
	InitVariables();

	trackProc = ref;
#ifdef PORTAUDIO
	err = Pa_Initialize();
	if( err != paNoError ){
		wxMessageBox(wxString::Format(wxT("An error occured in Initialize(), Error: %d - %s"), err, Pa_GetErrorText(err)),wxT("Error"), wxSTAY_ON_TOP);
		return;
	}
#endif
	return;
}

///////////////
Audio::~Audio()
{
	StopCallback();
	KillStreams();

#ifdef PORTAUDIO
	Pa_Terminate();
#endif
}

///////////////////////////
void Audio::InitVariables()
{
	//selectedIn = NULL;      FIXME cannot null a wxArrayString
	//selectedOut = NULL;      FIXME cannot null a wxArrayString
	inDevice.clear();
	outDevice.clear();
#ifdef PORTAUDIO
	err = NULL;
#endif
	inSampleRate = NULL;
	outSampleRate = NULL;
	framesPerBuffer = NULL;
	latency = NULL;	
}

//////////////////////////////////////
wxArrayString Audio::GetInDeviceAPIs()
{	
	//This function will scan the devices and return the names of the API's
	wxArrayString APIs;

#ifdef PORTAUDIO
	const PaDeviceInfo *pdi;
	const PaHostApiInfo *api;
	int numDevices = Pa_GetDeviceCount();
	for(int id=0; id<numDevices; ++id ) // FIX ME - we need to cycle only through IN devices
    {
		pdi = Pa_GetDeviceInfo( id );
		api = Pa_GetHostApiInfo( pdi->hostApi );

		//need to stop duplicates here
		if(APIs.Index(wxString::FromAscii(api->name), false, false) == wxNOT_FOUND){
			APIs.Add(wxString::FromAscii(api->name),1);
		}
	}
#endif
	
	return APIs;
}

///////////////////////////////////////
wxArrayString Audio::GetOutDeviceAPIs()
{	
	//This function will scan the devices and return the names of the API's
	wxArrayString APIs;

#ifdef PORTAUDIO
	const PaDeviceInfo *pdi;
	const PaHostApiInfo *api;
	int numDevices = Pa_GetDeviceCount();

	for(int id=0; id<numDevices; ++id ) // FIX ME - we need to cycle only through Out devices
    {
		pdi = Pa_GetDeviceInfo( id );
		api = Pa_GetHostApiInfo( pdi->hostApi );

		//need to stop duplicates here
		if(APIs.Index(wxString::FromAscii(api->name), false, false) == wxNOT_FOUND){
			APIs.Add(wxString::FromAscii(api->name),1);
		}
	}
#endif

	return APIs;
}

//////////////////////////////////
void Audio::SetInAPI(wxString API)
{
	if(API == wxT("")){return;}
	wxArrayString APIs;
	APIs = GetInDeviceAPIs();
	for(unsigned int i=0; i<APIs.GetCount(); ++i){
		if(API == APIs.Item(i)){
			selectedInAPI = API;
			return;
		}
	}
	if(selectedInAPI == API){
		wxMessageBox(wxT("Error: atempting to load an audio API that is not available"),wxT("Error"), wxSTAY_ON_TOP);
	}
}

///////////////////////////////////
void Audio::SetOutAPI(wxString API)
{
	if(API == wxT("")){return;}
	wxArrayString APIs;
	APIs = GetOutDeviceAPIs();
	for(unsigned int i=0; i<APIs.GetCount(); ++i){
		if(API == APIs.Item(i)){
			selectedOutAPI = API;
			return;
		}
	}
	if(selectedOutAPI == API){
		wxMessageBox(wxT("Error: atempting to load an audio API that is not available"),wxT("Error"), wxSTAY_ON_TOP);
	}
}

/////////////////////////////////////////////////////
void Audio::OpenAsioControlPanel(wxString deviceName)
{

#ifdef PORTAUDIO
	//We must temporarily close ALL streams before we can view the asio control panel.
	unsigned int numDevices = Pa_GetDeviceCount();
    const PaDeviceInfo *pdi;

	for ( unsigned int d=0; d<numDevices; ++d ) {              
		pdi = Pa_GetDeviceInfo( d );
		if(deviceName == wxString::FromAscii(pdi->name) ){ 

			wxArrayString temp = selectedIn;
			StopCallback();
			KillStreams();
			int error = PaAsio_ShowControlPanel(d, 0);
			if(error != 0){
				wxMessageBox(wxString::Format(wxT("Error opening Asio Control Panel   Code:%d"), error),wxT("Error"), wxSTAY_ON_TOP);
			}

			SetInDevices(temp);
			StartCallback();
		}
	}
#endif
}

///////////////////////////////////////////////
wxArrayString Audio::GetInDevices(wxString API)
{
	wxArrayString InDevs;

#ifdef PORTAUDIO
	int id;
	const PaDeviceInfo *pdi;
	const PaHostApiInfo *api;
	static double standardSampleRates[] = {  8000.0,  9600.0, 11025.0, 12000.0,
                                            16000.0,          22050.0, 24000.0,
                                            32000.0,          44100.0, 48000.0,
                                                              88200.0, 96000.0,
                                               -1.0 }; // Negative terminated list

	int numDevices = Pa_GetDeviceCount();

	for( id=0; id<numDevices; ++id ) // Iterate through all devices
    {
        pdi = Pa_GetDeviceInfo( id );
        
		if(pdi->maxInputChannels > 0){

			api = Pa_GetHostApiInfo( pdi->hostApi );
			if(API == wxString::FromAscii(api->name)){

				//Add the Device to the list if it does not allready exist.
				if(InDevs.Index(wxString::FromAscii(pdi->name), false, false) == wxNOT_FOUND){

					PaStreamParameters temp;
					temp.device = (PaDeviceIndex)id; 
					temp.channelCount = pdi->maxInputChannels;
					temp.sampleFormat = paFloat32 | paNonInterleaved;
					temp.suggestedLatency = Pa_GetDeviceInfo( temp.device )->defaultLowInputLatency;
					temp.hostApiSpecificStreamInfo = NULL;

					if(!Pa_IsFormatSupported( &temp, NULL, inSampleRate )){
						InDevs.Add(wxString::FromAscii(pdi->name),1);
					}
				}
			}
        }
    }
#endif 

	return InDevs;
}

////////////////////////////////////////////
int Audio::SetInDevice(wxString in, int num)
{
#ifdef PORTAUDIO
	//This function opens a stream one at a time.
	unsigned int numDevices = Pa_GetDeviceCount();
	const PaHostApiInfo *api;
    const PaDeviceInfo *pdi;

	for ( unsigned int d=0; d<numDevices; ++d ) {
                
		pdi = Pa_GetDeviceInfo( d );
		if(in == wxString::FromAscii(pdi->name)  && pdi->maxInputChannels > 0){ //if the Device names match....

			api = Pa_GetHostApiInfo( pdi->hostApi );
			if(selectedInAPI == wxString::FromAscii(api->name)){ //if the API names match....
	
				inDevice[num].info = Pa_GetDeviceInfo( d );
				inDevice[num].inDev.device = (PaDeviceIndex)d; 
				inDevice[num].inDev.channelCount = pdi->maxInputChannels;
				inDevice[num].inDev.sampleFormat = paFloat32 | paNonInterleaved;
				inDevice[num].inDev.suggestedLatency = 0; //Pa_GetDeviceInfo( device[num].inDev.device )->defaultLowInputLatency;
			    inDevice[num].inDev.hostApiSpecificStreamInfo = NULL;
				for(int c=0; c<100; ++c){
					inDevice[num].threshold[c] = 0;
				}
     
			    //// Test weather this device setup is supported
				err = Pa_IsFormatSupported( &inDevice[num].inDev, NULL, inSampleRate );
				if( err != paNoError ){
					wxMessageBox(wxString::Format(wxT("The Audio Device does no support this format, Error: %d - %s"), err, Pa_GetErrorText(err)), wxT("Error"), wxSTAY_ON_TOP);
					return -1;
				}

				//// Open The Device in a new Callback stream
				err = Pa_OpenStream  ( &inDevice[num].stream, &inDevice[num].inDev, NULL, inSampleRate, framesPerBuffer, 0, InCallBack, (void*)&inDevice[num] ); 
				if( err != paNoError ){
					wxMessageBox(wxString::Format(wxT("An error occured opening the audio stream, Error: %d - %s"), err, Pa_GetErrorText(err)),wxT("Error"), wxSTAY_ON_TOP);
					return -1;
				}
				else{
					LearnThreshold();
				}
			
				selectedIn.Add(in, 1); //Success. Add it to the active device list.

			return 0;
			}
		}
	}
#endif
	return 0;
}

//////////////////////////////////////////
void Audio::SetInDevices(wxArrayString in)
{
	//This function Opens streams for multiple input devices
	selectedIn.Clear();
	inDevice.clear();
	inDevice.resize(in.GetCount()); 
  
	int d = 0;
	for(unsigned int i=0; i<in.GetCount(); ++i)
	{
		if(SetInDevice(in.Item(i), d) == -1){ 
			inDevice.resize((inDevice.size() - 1)); //if the device fails, remove it from the array.
			d--;
		}
		++d;
	}
}


////////////////////////////////////////////////
wxArrayString Audio::GetOutDevices(wxString API)
{
	wxArrayString OutDevs;
#ifdef PORTAUDIO
	int id;
	const PaDeviceInfo *pdi;
	const PaHostApiInfo *api;
	static double standardSampleRates[] = {  8000.0,  9600.0, 11025.0, 12000.0,
                                            16000.0,          22050.0, 24000.0,
                                            32000.0,          44100.0, 48000.0,
                                                              88200.0, 96000.0,
                                               -1.0 }; // Negative terminated list

	int numDevices = Pa_GetDeviceCount();

	for( id=0; id<numDevices; ++id ) // Iterate through all devices
    {
        pdi = Pa_GetDeviceInfo( id );
        // Try 1 to maxChannels on each device
        //maxChannels = pdi->maxOutputChannels;
        
		if(pdi->maxOutputChannels > 0){

			api = Pa_GetHostApiInfo( pdi->hostApi );
			if(API == wxString::FromAscii(api->name)){

				//Add the Device to the list if it does not allready exist.
				if(OutDevs.Index(wxString::FromAscii(pdi->name), false, false) == wxNOT_FOUND){

					PaStreamParameters temp;
					temp.device = (PaDeviceIndex)id; 
					temp.channelCount = pdi->maxOutputChannels;
					temp.sampleFormat = paFloat32;
					temp.suggestedLatency = Pa_GetDeviceInfo( temp.device )->defaultLowInputLatency;
					temp.hostApiSpecificStreamInfo = NULL;

					if(!Pa_IsFormatSupported( NULL, &temp, outSampleRate )){
						OutDevs.Add(wxString::FromAscii(pdi->name),1);
					}
				}
			}
		}
    }
#endif
	return OutDevs;
}

//////////////////////////////////////////////
int Audio::SetOutDevice(wxString out, int num)
{
#ifdef PORTAUDIO
	//This function opens a stream one at a time.
	unsigned int numDevices = Pa_GetDeviceCount();
	const PaHostApiInfo *api;
    const PaDeviceInfo *pdi;

	for ( unsigned int d=0; d<numDevices; ++d ) {
                
		pdi = Pa_GetDeviceInfo( d );
		if(out == wxString::FromAscii(pdi->name) && pdi->maxOutputChannels > 0){ //if the Device names match....

			api = Pa_GetHostApiInfo( pdi->hostApi );
			if(selectedOutAPI == wxString::FromAscii(api->name)){ //if the API names match....
	
				outDevice[num].info = Pa_GetDeviceInfo( d );
				outDevice[num].outDev.device = (PaDeviceIndex)d; 
				outDevice[num].outDev.channelCount = 2;//pdi->maxOutputChannels;
				outDevice[num].outDev.sampleFormat = paFloat32;
				outDevice[num].outDev.suggestedLatency = 0; //Pa_GetDeviceInfo( device[num].inDev.device )->defaultLowInputLatency;
			    outDevice[num].outDev.hostApiSpecificStreamInfo = NULL;
    
			    //// Test weather this device setup is supported
				err = Pa_IsFormatSupported( NULL, &outDevice[num].outDev, outSampleRate );
				if( err != paNoError ){
					wxMessageBox(wxString::Format(wxT("The Audio Device does not support this format, Error: %d - %s"), err, Pa_GetErrorText(err)), wxT("Error"), wxSTAY_ON_TOP);
					return -1;
				}

				//// Open The Device in a new Callback stream
				err = Pa_OpenStream  ( &outDevice[num].stream, NULL, &outDevice[num].outDev, outSampleRate,
					                   framesPerBuffer, paNoFlag, OutCallBack,
								trackProc->trackPanel->mainPanel->soundController); 
				
				if( err ){
					wxMessageBox(wxString::Format(wxT("An error occured opening the audio stream, Error: %d - %s"), err, Pa_GetErrorText(err)),wxT("Error"), wxSTAY_ON_TOP);
					return -1;
				}

				selectedOut.Add(out, 1); //Success. Add it to the active device list.

			return 0;
			}
		}
	}
#endif
	return 0;
}

////////////////////////////////////////////
void Audio::SetOutDevices(wxArrayString out)
{
	//This function Opens streams for multiple input devices
	selectedOut.Clear();
	outDevice.clear();

	outDevice.resize(out.GetCount()); 
  
	int d = 0;
	for(unsigned int i=0; i<out.GetCount(); ++i)
	{
		if(SetOutDevice(out.Item(i), d) == -1){ 
			outDevice.resize((outDevice.size() - 1)); //if the device fails, remove it from the array.
			d--;
		}
		++d;
	}	
}



////////////////////////////////////
void Audio::SetAudioBuffer(int size)
{
	wxArrayString temp = selectedIn;
	wxArrayString temp2 = selectedOut;
	StopCallback();
	KillStreams();

	framesPerBuffer = size;

	SetInDevices(temp);
	SetOutDevices(temp2);
	StartCallback();
}

////////////////////////////
int Audio::GetInSampleRate()
{
	return inSampleRate;
}

/////////////////////////////////////
void Audio::SetInSampleRate(int rate)
{
	inSampleRate = rate;
}

/////////////////////////////
int Audio::GetOutSampleRate()
{
	return outSampleRate;
}

//////////////////////////////////////
void Audio::SetOutSampleRate(int rate)
{
	outSampleRate = rate;
}

////////////////////////////
void Audio::LearnThreshold()
{
	timer.start();
	learningThreshold = true;
	learnStartTime = timer.getElapsedTimeInMilliSec();
	learning = new wxDialog(NULL, -1, wxT("Detecting Threshold, do not play . . ."), wxDefaultPosition, wxSize(300,25), wxCAPTION | wxSTAY_ON_TOP, wxT(""));
	learning->CenterOnParent(wxBOTH);
	learning->Show();
}

//////////////////////////
void Audio::StopCallback()
{
#ifdef PORTAUDIO
	//Stop all of the streams
	for(unsigned int i=0; i<inDevice.size(); ++i){
		if(Pa_IsStreamActive( inDevice[i].stream )){
			err = Pa_StopStream( inDevice[i].stream );
			if( err != paNoError ){
				wxMessageBox(wxString::Format(wxT("An error occured stopping the Audio Input Callback, Error: %d - %s"), err, Pa_GetErrorText(err)),wxT("Error"), wxSTAY_ON_TOP);
			}
		}
	}

	for(unsigned int i=0; i<outDevice.size(); ++i){
		if(Pa_IsStreamActive( outDevice[i].stream )){
			err = Pa_StopStream( outDevice[i].stream );
			if( err != paNoError ){
				wxMessageBox(wxString::Format(wxT("An error occured stopping the Audio Output Callback, Error: %d - %s"), err, Pa_GetErrorText(err)),wxT("Error"), wxSTAY_ON_TOP);
			}
		}
	}
#endif
}

///////////////////////////
void Audio::StartCallback()
{
#ifdef PORTAUDIO
	//Start all of the streams
	for(unsigned int i=0; i<inDevice.size(); ++i){
		if(!Pa_IsStreamActive( inDevice[i].stream )){
			err = Pa_StartStream( inDevice[i].stream );
			if( err != paNoError ){
				wxMessageBox(wxString::Format(wxT("An error occured starting the Audio Input Callback, Error: %d - %s"), err, Pa_GetErrorText(err)),wxT("Error"), wxSTAY_ON_TOP);
			}
		}
	}

	for(unsigned int i=0; i<outDevice.size(); ++i){
		if(!Pa_IsStreamActive( outDevice[i].stream )){
			err = Pa_StartStream( outDevice[i].stream );
			Pa_Sleep(2000); //TEMPORARY PAUSE
			if( err != paNoError ){
				wxMessageBox(wxString::Format(wxT("An error occured starting the Audio Output Callback, Error: %d - %s"), err, Pa_GetErrorText(err)),wxT("Error"), wxSTAY_ON_TOP);
			}
		}
	}

	trackProc->trackPanel->mainPanel->soundController->CheckSampleRates();
#endif
}

/////////////////////////
void Audio::KillStreams()
{
#ifdef PORTAUDIO
    //Stop all of the streams
	for(unsigned int i=0; i<inDevice.size(); ++i){
		if(Pa_IsStreamActive( inDevice[i].stream )){
			err = Pa_StopStream( inDevice[i].stream );
			if( err != paNoError ){
				wxMessageBox(wxString::Format(wxT("An error occured stopping the Audio Input Callback, Error: %d - %s"), err, Pa_GetErrorText(err)),wxT("Error"), wxSTAY_ON_TOP);
			}
		}

		err = Pa_CloseStream( inDevice[i].stream );
		if( err != paNoError ){
			wxMessageBox(wxString::Format(wxT("An error occured closeing the Audio Input Stream, Error: %d - %s"), err, Pa_GetErrorText(err)),wxT("Error"), wxSTAY_ON_TOP);
		}
	}

	for(unsigned int i=0; i<outDevice.size(); ++i){
		if(Pa_IsStreamActive( outDevice[i].stream )){
			err = Pa_StopStream( outDevice[i].stream );
			if( err != paNoError ){
				wxMessageBox(wxString::Format(wxT("An error occured stopping the Audio Output Callback, Error: %d - %s"), err, Pa_GetErrorText(err)),wxT("Error"), wxSTAY_ON_TOP);
			}
		}

		err = Pa_CloseStream( outDevice[i].stream );
		if( err != paNoError ){
			wxMessageBox(wxString::Format(wxT("An error occured closeing the Audio Output Stream, Error: %d - %s"), err, Pa_GetErrorText(err)),wxT("Error"), wxSTAY_ON_TOP);
		}
	}
#endif

	inDevice.resize(0);
	selectedIn.Clear();

	outDevice.resize(0);
	selectedOut.Clear();
}

#ifdef PORTAUDIO
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Audio::InCallBack( const void *inputBuffer, void *outputBuffer, unsigned long frameBuffer,
					const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData )
{
	if( inputBuffer == NULL ) return paContinue; 

	if(!paused){

		if(learningThreshold && (timer.getElapsedTimeInMilliSec() - learnStartTime) > 3500){
			timer.stop();
			learningThreshold = false;
			learning->Destroy();
		}
	
		InDevice *thisDevice = (InDevice*)userData;  //This holds the device info we need
		int* input = (int*)inputBuffer;
		std::vector<float *>channel(thisDevice->inDev.channelCount);	


		/////////////////////////////////////////////////////
		for(int c=0; c< thisDevice->inDev.channelCount; ++c){ //Cycle through channels

			channel[c] = (float*)input[c]; //seperate channels into a channel[] array

			for (unsigned int f=0; f<frameBuffer; ++f) { //Cycle through frames

				//Let's change the data to absolute value along the way.
				if(channel[c][f] >= 0){ thisDevice->absolute = channel[c][f]; }
				else{ thisDevice->absolute = -channel[c][f]; }

				//If we have data above the threshold, process it.
				if(thisDevice->absolute > thisDevice->threshold[c]){

					//If were above the threshold and learning, increase it.
					if(learningThreshold){
						thisDevice->threshold[c] = thisDevice->threshold[c] + 0.01;
					}

					//We are finding the peak of this wave.
					////////////////////////////////////////////////////////////////////////
					if(thisDevice->absolute >= thisDevice->history[c]){
						thisDevice->history[c] = thisDevice->absolute;
						thisDevice->framesSincePeak[c] = 0;
					}
					else{
						++thisDevice->framesSincePeak[c];
					}
				}//above threshold
				else{
					++thisDevice->framesSincePeak[c];
				}

				if(thisDevice->history[c] > 0 && thisDevice->framesSincePeak[c] > 1000){ //this is a good number to tune.
						
					thisDevice->thePeak = thisDevice->history[c];

					//Set the gains for the track we belong too.
					//FIXME
					for(int t=1; t<(trackProc->tracks+1); ++t){
						for(int z=0; z < trackProc->n[t].zones; ++z){
							if((thisDevice->inDev.device * 1000) + (c + 200000) == trackProc->n[t].inputCode[z]){
								thisDevice->thePeak = (thisDevice->history[c] * ((float)trackProc->n[t].preGain[z] / 100) *((float)trackProc->n[t].masterGain / 100));
							}
						}
					}

					//turn it into a velocity value using peak audio, gain and volume.
					//FIXME
					//We need to make a correct scale using threshold - 1.0 to 1-127 midi
					//Just above threshold (audio) should equal 1 (midi).
					//1.0 (audio) should equal 127 (midi).
					int velocity = ((((thisDevice->thePeak - (thisDevice->threshold[c] * 5)) / (5 - (thisDevice->threshold[c] * 5)) * 100) * 127) / 100);

					if(velocity > 0){
						if(velocity > 127){velocity=127;}
						std::vector<unsigned char> message(3);
     					message[0] = thisDevice->inDev.device;
						message[1] = c;
						message[2] = velocity;
						char* name = ((char*)thisDevice->info->name);
						Process::Send(2, wxString::FromAscii(name), thisDevice->inDev.device, message);
					}

					thisDevice->history[c] = 0;
					thisDevice->framesSincePeak[c] = 0;
				}//trigger
			}// cycling framesBuffer
		}// cycling channels
	}//paused

	return paContinue;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Audio::OutCallBack( const void *input, void *output, unsigned long frameBuffer,
					const PaStreamCallbackTimeInfo* paTimeInfo, PaStreamCallbackFlags statusFlags, void *userData )
{
	float *out = (float *)output; //create a pointer to the output buffer
	for(unsigned int z=0; z<frameBuffer * 2; ++z){ out[z] = 0; } //Clear the output buffer

	SoundController *data = (SoundController *)userData;

	data->RequestAudio(out, frameBuffer, outSampleRate, 2);

	return paContinue;
}
#endif