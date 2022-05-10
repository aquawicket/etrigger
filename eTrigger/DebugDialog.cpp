///// DebugDialog.cpp //////////////////////////////////////////////////////////
//
//
/////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "DebugDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////
BEGIN_EVENT_TABLE(DebugDialog, wxDialog)
	EVT_BUTTON(100, DebugDialog::OnLoadWavToMem)
	EVT_BUTTON(101, DebugDialog::OnPlayWav)
	EVT_BUTTON(110, DebugDialog::OnStopWav)
	EVT_BUTTON(102, DebugDialog::OnUnloadWav)
	EVT_BUTTON(103, DebugDialog::OnLoadMp3ToMem)
	EVT_BUTTON(104, DebugDialog::OnPlayMp3)
	EVT_BUTTON(111, DebugDialog::OnStopMp3)
	EVT_BUTTON(105, DebugDialog::OnUnloadMp3)
END_EVENT_TABLE() 

///////////////////////////////
DebugDialog::DebugDialog(MainPanel* parent) 
	:wxDialog(NULL, -1, wxT("Debug"), wxDefaultPosition, wxSize(400, 700), wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER )
{
	InitVariables();

	mainPanel = parent;
	
	LoadWavToMem = new wxButton(this, 100, wxT("Load Wav To Memory"), wxPoint(10,10), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	framesToLoad = new wxTextCtrl(this, 106, wxEmptyString, wxPoint(150, 10), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	PlayWav = new wxButton(this, 101, wxT("Play Wav"), wxPoint(10,40), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	startFrame = new wxTextCtrl(this, 107, wxEmptyString, wxPoint(150, 40), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	StopWav = new wxButton(this, 110, wxT("Stop Wav"), wxPoint(10,70), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	UnloadWav = new wxButton(this, 102, wxT("Unload Wav"), wxPoint(10,100), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	
	LoadMp3ToMem = new wxButton(this, 103, wxT("Load Mp3 To Memory"), wxPoint(10,160), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	framesToLoad2 = new wxTextCtrl(this, 108, wxEmptyString, wxPoint(150, 160), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	PlayMp3 = new wxButton(this, 104, wxT("Play Mp3"), wxPoint(10,190), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	startFrame2 = new wxTextCtrl(this, 109, wxEmptyString, wxPoint(150, 190), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	StopMp3 = new wxButton(this, 111, wxT("Stop Mp3"), wxPoint(10,220), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	UnloadMp3 = new wxButton(this, 105, wxT("Unload Mp3"), wxPoint(10,250), wxDefaultSize, 0, wxDefaultValidator, wxT(""));

	wxStandardPaths stdPath;
	wxString execPath = stdPath.GetExecutablePath();
	execPath.Replace(wxT("eTrigger.app/Contents/MacOS/eTrigger"), wxT(""), true);
	wxStaticText *temp = new wxStaticText(this, -1, execPath, wxPoint(10,280), wxDefaultSize, 0, wxT(""));
}

///////////////////////////
DebugDialog::~DebugDialog()
{
	delete LoadWavToMem;
	delete PlayWav;
	delete UnloadWav;
	delete LoadMp3ToMem;
	delete PlayMp3;
	delete UnloadMp3;
}

/////////////////////////////////
void DebugDialog::InitVariables()
{
	mainPanel = NULL;
	LoadWavToMem = NULL;
	PlayWav = NULL;
	UnloadWav = NULL;
	LoadMp3ToMem = NULL;
	PlayMp3 = NULL;
	UnloadMp3 = NULL;
}

///////////////////////////////////////////////////////
void DebugDialog::OnLoadWavToMem(wxCommandEvent &event)
{
	int frames = ConvToInt(framesToLoad->GetValue());
	mainPanel->soundController->LoadFile(wxT("Sound1.wav"), frames);
}

//////////////////////////////////////////////////
void DebugDialog::OnPlayWav(wxCommandEvent &event)
{
	int frame = ConvToInt(startFrame->GetValue());
	mainPanel->soundController->PlaySound(wxT("Sound1.wav"), frame, true);
}

//////////////////////////////////////////////////
void DebugDialog::OnStopWav(wxCommandEvent &event)
{
	mainPanel->soundController->StopSound(wxT("Sound1.wav"));
}

////////////////////////////////////////////////////
void DebugDialog::OnUnloadWav(wxCommandEvent &event)
{
	mainPanel->soundController->UnloadFile(wxT("Sound1.wav"));
}

///////////////////////////////////////////////////////
void DebugDialog::OnLoadMp3ToMem(wxCommandEvent &event)
{
	int frames = ConvToInt(framesToLoad2->GetValue());
	mainPanel->soundController->LoadFile(wxT("Sound1.mp3"), frames);
}

//////////////////////////////////////////////////
void DebugDialog::OnPlayMp3(wxCommandEvent &event)
{
	int frame = ConvToInt(startFrame2->GetValue());
	mainPanel->soundController->PlaySound(wxT("Sound1.mp3"), frame, true);
}

//////////////////////////////////////////////////
void DebugDialog::OnStopMp3(wxCommandEvent &event)
{
	mainPanel->soundController->StopSound(wxT("Sound1.mp3"));
}

////////////////////////////////////////////////////
void DebugDialog::OnUnloadMp3(wxCommandEvent &event)
{
	mainPanel->soundController->UnloadFile(wxT("Sound1.mp3"));
}

//////////////////////////////////////////////////////////
void DebugDialog::OnConvertMp3ToWav(wxCommandEvent &event)
{
#ifdef SNDFILE
	wxString in = wxT("mp3.mp3");
	wxString out = wxT("mp3.wav");

	SNDFILE* sndfile = NULL;
	SF_INFO sfinfo;
	mpg123_handle *mh = NULL;
	unsigned char* buffer = NULL;
	size_t buffer_size = 0;
	size_t done = 0;
	int  channels = 0;
	int encoding = 0;
	long rate = 0;
	int  err  = MPG123_OK;
	off_t samples = 0;
	
	err = mpg123_init();
	
	const char* temp = (const char*)in.mb_str(wxConvUTF8);
	if( err != MPG123_OK || (mh = mpg123_new(NULL, &err)) == NULL
	    /* Let mpg123 work with the file, that excludes MPG123_NEED_MORE messages. */
	    || mpg123_open(mh, temp) != MPG123_OK
	    /* Peek into track and get first output format. */
	    || mpg123_getformat(mh, &rate, &channels, &encoding) != MPG123_OK )
	{
		wxMessageBox(wxString::Format(wxT("Trouble with mpg123: %s\n"),
		         mh==NULL ? mpg123_plain_strerror(err) : mpg123_strerror(mh) ));
		
		mpg123_close(mh);
		mpg123_delete(mh);
		mpg123_exit();

		return;
	}

	if(encoding != MPG123_ENC_SIGNED_16)
	{ /* Signed 16 is the default output format anyways; it would actually by only different if we forced it.
	     So this check is here just for this explanation. */
		
		wxMessageBox(wxString::Format(wxT("Bad encoding 0x%x!"), encoding));

		mpg123_close(mh);
		mpg123_delete(mh);
		mpg123_exit();

		return;
	}
	/* Ensure that this output format will not change (it could, when we allow it). */
	mpg123_format_none(mh);
	mpg123_format(mh, rate, channels, encoding);

	/* Buffer could be almost any size here, mpg123_outblock() is just some recommendation.
	   Important, especially for sndfile writing, is that the size is a multiple of sample size. */
	buffer_size = mpg123_outblock( mh );
	buffer = (unsigned char*)malloc( buffer_size );

	//bzero(&sfinfo, sizeof(sfinfo) );
	sfinfo.samplerate = rate;
	sfinfo.channels = channels;
	sfinfo.format = SF_FORMAT_WAV|SF_FORMAT_PCM_16;
	//wxMessageBox(wxString::Format(wxT("Creating 16bit WAV with %i channels and %liHz."), channels, rate));

	const char* temp2 = (const char*)out.mb_str(wxConvUTF8);
	sndfile = sf_open(temp, SFM_WRITE, &sfinfo);
	if(sndfile == NULL){ 
		
		wxMessageBox(wxT("Cannot open output file!"));

		mpg123_close(mh);
		mpg123_delete(mh);
		mpg123_exit();

		return; 
	}

	do
	{
		err = mpg123_read( mh, buffer, buffer_size, &done );
		sf_write_short( sndfile, (short*)buffer, done/sizeof(short) );
		samples += done/sizeof(short);
		/* We are not in feeder mode, so MPG123_OK, MPG123_ERR and MPG123_NEW_FORMAT are the only possibilities.
		   We do not handle a new format, MPG123_DONE is the end... so abort on anything not MPG123_OK. */
	} while (err==MPG123_OK);

	if(err != MPG123_DONE)
		wxMessageBox(wxString::Format(wxT("Warning: Decoding ended prematurely because: %s\n"),
	         err == MPG123_ERR ? mpg123_strerror(mh) : mpg123_plain_strerror(err) ));

	sf_close( sndfile );

	samples /= channels;
	
	wxMessageBox(wxString::Format(wxT("Samples Written %li"), (long)samples));

	mpg123_close(mh);
	mpg123_delete(mh);
	mpg123_exit();

	wxMessageBox(wxT("Created mp3.wav"));

	return;
#endif
}




//////////////////////////////////////////////////////////////////////////////
#ifdef WIN32
__int64 DebugDialog::GetCPUCount ( unsigned int loword, unsigned int hiword )
{
	// We can use this to get the number of cpu cycles functions take to complete.
		_asm
		{
			_emit 0x0f	// insert rtdsc opcode
			_emit 0x31
			mov hiword , edx
			mov loword , eax
		}		
	return ( (__int64) hiword << 32 ) + loword;
}
#endif //WIN32