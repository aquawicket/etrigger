//// AudioDialog.cpp //////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "AudioDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

////////////////////////////////////////
BEGIN_EVENT_TABLE(AudioDialog, wxDialog)
	EVT_GBUTTON(203,  AudioDialog::OnOk)
	EVT_GBUTTON(204,  AudioDialog::OnCancel)
	EVT_GBUTTON(207,  AudioDialog::OnInSetup)
	EVT_GBUTTON(211,  AudioDialog::OnOutSetup)
	EVT_COMBOBOX(205, AudioDialog::UpdateDevices) 
	EVT_COMBOBOX(206, AudioDialog::UpdateDevices)
	EVT_COMBOBOX(209, AudioDialog::UpdateDevices) 
	EVT_COMBOBOX(210, AudioDialog::UpdateDevices)
	EVT_LISTBOX(208,  AudioDialog::OnInputSelect)
	EVT_LISTBOX(212,  AudioDialog::OnOutputSelect)
	EVT_CLOSE(        AudioDialog::OnClose) 
	EVT_SET_FOCUS(    AudioDialog::OnSetFocus)
END_EVENT_TABLE() 

////////////////////////////////////
AudioDialog::AudioDialog(Audio *ref)
	:wxDialog(NULL, -1, wxT("Audio Devices"), wxDefaultPosition, wxSize(460, 290), wxDEFAULT_DIALOG_STYLE)
{
	InitVariables();

	audio = ref;

	CentreOnScreen(wxBOTH);

#ifdef WIN32
	SetBackgroundColour(wxColour(90,90,90));
#endif //WIN32
#ifdef MAC
	wxPanel *background = new wxPanel(this, -1, wxPoint(0,0), this->GetSize(), 0, wxT(""));
	background->SetBackgroundColour(wxColour(90,90,90));
#endif //MAC

	wxStaticText *audioInText = new wxStaticText(this, -1, wxT("Audio Input"), wxPoint(20,5), wxDefaultSize, 0, wxT(""));
	wxStaticText *audioOutText = new wxStaticText(this, -1, wxT("Audio Output"), wxPoint(250,5), wxDefaultSize, 0, wxT(""));

	inAPIs = new wxComboBox(this, 205, wxT(""), wxPoint(10,20), wxSize(200,20), audio->GetInDeviceAPIs(), wxCB_READONLY, wxDefaultValidator, wxT(""));
	inAPIs->SetBackgroundColour( wxColor(30,30,30));
	inAPIs->SetForegroundColour( wxColor(200,200,200));

	outAPIs = new wxComboBox(this, 209, wxT(""), wxPoint(240,20), wxSize(200,20), audio->GetOutDeviceAPIs(), wxCB_READONLY, wxDefaultValidator, wxT(""));
	outAPIs->SetBackgroundColour( wxColor(30,30,30));
	outAPIs->SetForegroundColour( wxColor(200,200,200));

	sampleRates.Add(wxT("8000"));
	sampleRates.Add(wxT("9600"));
	sampleRates.Add(wxT("11025"));
	sampleRates.Add(wxT("12000"));
	sampleRates.Add(wxT("16000"));
	sampleRates.Add(wxT("22050"));
	sampleRates.Add(wxT("24000"));
	sampleRates.Add(wxT("32000"));
	sampleRates.Add(wxT("44100"));
	sampleRates.Add(wxT("48000"));
	sampleRates.Add(wxT("88200"));
	sampleRates.Add(wxT("96000"));

	inSampleRate = new wxComboBox(this,206, wxT(""), wxPoint(10, 60), wxSize(100, 20), sampleRates, wxCB_READONLY, wxDefaultValidator, wxT(""));
	inSampleRate->SetBackgroundColour( wxColor(30,30,30));
	inSampleRate->SetForegroundColour( wxColor(200,200,200));
	inSampleRate->SetSelection(8);
	for(unsigned int i=0; i<inSampleRate->GetCount(); ++i){
		if(inSampleRate->GetString(i) == ConvTowxString(audio->GetInSampleRate())){
			inSampleRate->SetSelection(i);
		}
	}
	storedInSampleRate = audio->inSampleRate;

	outSampleRate = new wxComboBox(this,210, wxT(""), wxPoint(240, 60), wxSize(100, 20), sampleRates, wxCB_READONLY, wxDefaultValidator, wxT(""));
	outSampleRate->SetBackgroundColour( wxColor(30,30,30));
	outSampleRate->SetForegroundColour( wxColor(200,200,200));
	outSampleRate->SetSelection(8);
	for(unsigned int i=0; i<outSampleRate->GetCount(); ++i){
		if(outSampleRate->GetString(i) == ConvTowxString(audio->GetOutSampleRate())){
			outSampleRate->SetSelection(i);
		}
	}
	storedOutSampleRate = audio->outSampleRate;

#ifdef WIN32
	asioInSetup = new GButton(this, 207, wxPoint(140, 60), setup_focused_xpm, setup_hover_focused_xpm, setup_click_focused_xpm); asioInSetup->Hide();
	asioOutSetup = new GButton(this, 211, wxPoint(370, 60), setup_focused_xpm, setup_hover_focused_xpm, setup_click_focused_xpm); asioOutSetup->Hide();
#endif

	audioIn = new wxListBox(this, 208, wxPoint(10,100), wxSize(200,120), NULL,NULL, wxLB_MULTIPLE, wxDefaultValidator);
	audioIn->SetBackgroundColour( wxColor(30,30,30));
	audioIn->SetForegroundColour( wxColor(200,200,200)); 

	audioOut = new wxListBox(this, 212, wxPoint(240,100), wxSize(200,120), NULL, NULL,wxLB_MULTIPLE, wxDefaultValidator);
	audioOut->SetBackgroundColour( wxColor(30,30,30));
	audioOut->SetForegroundColour( wxColor(200,200,200)); 

	ok = new GButton(this, 203, wxPoint(298, 230), ok_xpm, ok_hover_xpm, ok_click_xpm); 
	cancel = new GButton(this, 204, wxPoint(370, 230), cancel_xpm, cancel_hover_xpm, cancel_click_xpm);

	//Select the first API, but if one is loaded, open that one.
	inAPIs->SetSelection(0);
	for(unsigned int i=0; i<inAPIs->GetCount(); ++i){
		if(inAPIs->GetString(i) == audio->selectedInAPI){
			inAPIs->SetSelection(i);
		}
	}

	//Select the first API, but if one is loaded, open that one.
	outAPIs->SetSelection(0);
	for(unsigned int i=0; i<outAPIs->GetCount(); ++i){
		if(outAPIs->GetString(i) == audio->selectedOutAPI){
			outAPIs->SetSelection(i);
		}
	}

	//Now that we have our API, lets populate the device list
	wxCommandEvent *temp = new wxCommandEvent();
	UpdateDevices(*temp);
	delete temp;

    //And if we have any loaded devices, select them
	for(unsigned int i=0; i<audio->selectedIn.GetCount(); ++i){
		audioIn->SetStringSelection( audio->selectedIn.Item(i) );
	}

	//And if we have any loaded devices, select them
	for(unsigned int i=0; i<audio->selectedOut.GetCount(); ++i){
		audioOut->SetStringSelection( audio->selectedOut.Item(i) );
	}

	// If only one asio device happens to be selected. lets show setup button
	//if(APIs->GetString(APIs->GetCurrentSelection()) == wxT("ASIO")){
	  if(inAPIs->GetString(inAPIs->GetSelection()) == wxT("ASIO")){
		int d = 0;
		for(unsigned int i=0; i<audioIn->GetCount(); ++i){
				if(audioIn->IsSelected(i)){
					lastSelectedInDevice = audioIn->GetString(i);
					++d;
				}
		}
		if (d==1){
#ifdef WIN32
			asioInSetup->Show();
#endif
		}
	}

	// If only one asio device happens to be selected. lets show setup button
	  if(outAPIs->GetString(outAPIs->GetSelection()) == wxT("ASIO")){
		int d = 0;
		for(unsigned int i=0; i<audioOut->GetCount(); ++i){
				if(audioOut->IsSelected(i)){
					lastSelectedOutDevice = audioOut->GetString(i);
					++d;
				}
		}
		if (d==1){
#ifdef WIN32
			asioOutSetup->Show();	
#endif
		}
	}
}

/////////////////////////////////////////////////
void AudioDialog::OnSetFocus(wxFocusEvent &event)
{
	//wxMessageBox("focus");
}

///////////////////////////
AudioDialog::~AudioDialog()
{
	delete inAPIs;
	delete inSampleRate;
	delete audioIn;
	delete asioInSetup;
    delete outAPIs;
	delete outSampleRate;
	delete audioOut;
	delete asioOutSetup;
	delete ok;
    delete cancel;
}

/////////////////////////////////
void AudioDialog::InitVariables()
{
	audio = NULL;
	//sampleRates = NULL;     FIXME  wxArrayString cannot be null
	inAPIs = NULL;
	inSampleRate = NULL;
	audioIn = NULL;
	lastSelectedInDevice = wxT("");
	storedInSampleRate = NULL;
	asioInSetup = NULL;
    outAPIs = NULL;
	outSampleRate = NULL;
	audioOut = NULL;
	lastSelectedOutDevice = wxT("");
	storedOutSampleRate = NULL;
	asioOutSetup = NULL;
	ok = NULL;
    cancel = NULL;	
}

/////////////////////////////
void AudioDialog::VarsToDlg()
{
	inSampleRate->SetSelection(0);
	for(unsigned int i=0; i<inSampleRate->GetCount(); ++i){
		if(inSampleRate->GetString(i) == ConvTowxString(audio->GetInSampleRate())){
			inSampleRate->SetSelection(i);
		}
	}

	outSampleRate->SetSelection(0);
	for(unsigned int i=0; i<outSampleRate->GetCount(); ++i){
		if(outSampleRate->GetString(i) == ConvTowxString(audio->GetOutSampleRate())){
			outSampleRate->SetSelection(i);
		}
	}

	//Select the first API, but if one is loaded, open that one.
	inAPIs->SetSelection(0);
	for(unsigned int i=0; i<inAPIs->GetCount(); ++i){
		if(inAPIs->GetString(i) == audio->selectedInAPI){
			inAPIs->SetSelection(i);
		}
	}

	//Select the first API, but if one is loaded, open that one.
	outAPIs->SetSelection(0);
	for(unsigned int i=0; i<outAPIs->GetCount(); ++i){
		if(outAPIs->GetString(i) == audio->selectedOutAPI){
			outAPIs->SetSelection(i);
		}
	}

	//Now that we have our API, lets populate the device list
	wxCommandEvent *temp = new wxCommandEvent();
	UpdateDevices(*temp);
	delete temp;

	//And if we have any loaded devices, select them
	for(unsigned int i=0; i<audio->selectedIn.GetCount(); ++i){
		audioIn->SetStringSelection( audio->selectedIn.Item(i) );
	}

	//And if we have any loaded devices, select them
	for(unsigned int i=0; i<audio->selectedOut.GetCount(); ++i){
		audioOut->SetStringSelection( audio->selectedOut.Item(i) );
	}
}

///////////////////////////////////////////
void AudioDialog::OnOk(GButtonEvent &event)
{
	audio->StopCallback(); //must Stop Callbacks before changing audio devices
	audio->KillStreams();

	wxArrayInt inSelections;
	wxArrayString inStrings;

	audio->SetInAPI( inAPIs->GetStringSelection() ); //Set the selected API
	audioIn->GetSelections(inSelections);
	for(unsigned int i=0; i<inSelections.GetCount(); ++i){
		inStrings.Add( audioIn->GetString( (int)inSelections.Item(i) ), 1);
	}
	audio->SetInDevices(inStrings);	//Set the selected Devices


	wxArrayInt outSelections;
	wxArrayString outStrings;

	audio->SetOutAPI( outAPIs->GetStringSelection() ); //Set the selected API
	audioOut->GetSelections(outSelections);
	for(unsigned int i=0; i<outSelections.GetCount(); ++i){
		outStrings.Add( audioOut->GetString( (int)outSelections.Item(i) ), 1);
	}
	audio->SetOutDevices(outStrings);	//Set the selected Devices


	audio->StartCallback(); //Start callbacks after devices are selected

	Hide();
}

////////////////////////////////////////////
void AudioDialog::OnCancel(GButtonEvent &event)
{
	Close();
}

//////////////////////////////////////////////
void AudioDialog::OnClose(wxCloseEvent &event)
{
	audio->inSampleRate = storedInSampleRate;
	audio->outSampleRate = storedOutSampleRate;
	VarsToDlg();

	Hide();
}

///////////////////////////////
void AudioDialog::UpdateSetup()
{
	if(inAPIs->GetString(inAPIs->GetSelection()) == wxT("ASIO")){		
		if(lastSelectedInDevice != wxT("")){
#ifdef WIN32
			asioInSetup->Show();
#endif
			return;
		}
		else{
#ifdef WIN32
			asioInSetup->Hide();
#endif
			return;
		}
	}

	else{
#ifdef WIN32
		asioInSetup->Hide();
#endif
		return;
	}


	if(outAPIs->GetString(outAPIs->GetSelection()) == wxT("ASIO")){		
		if(lastSelectedOutDevice != wxT("")){
#ifdef WIN32
			asioOutSetup->Show();
#endif
			return;
		}
		else{
#ifdef WIN32
			asioOutSetup->Hide();
#endif
			return;
		}
	}

	else{
#ifdef WIN32
		asioOutSetup->Hide();
#endif
		return;
	}

}

////////////////////////////////////////////////
void AudioDialog::OnInSetup(GButtonEvent &event)
{
#ifdef WIN32
	audio->OpenAsioControlPanel(lastSelectedInDevice);
#endif //WIN32
}

/////////////////////////////////////////////////
void AudioDialog::OnOutSetup(GButtonEvent &event)
{
#ifdef WIN32
	audio->OpenAsioControlPanel(lastSelectedOutDevice);
#endif //WIN32
}

//////////////////////////////////////////////////////
void AudioDialog::OnInputSelect(wxCommandEvent &event)
{
	if(inAPIs->GetString(inAPIs->GetSelection()) == wxT("ASIO")){
		
		//was the item we just clicked selected?
		for(unsigned int i=0; i<audioIn->GetCount(); ++i){
			if(audioIn->GetString(i) == event.GetString()){
				if(audioIn->IsSelected(i)){
					//we selected it
					lastSelectedInDevice = event.GetString();
#ifdef WIN32
					asioInSetup->Show();
#endif
					return;
				}
				else{
					//we deselected it
					lastSelectedInDevice = wxT("");
#ifdef WIN32
					asioInSetup->Hide();
#endif
					return;
				}
			}
		}
	}
}

///////////////////////////////////////////////////////
void AudioDialog::OnOutputSelect(wxCommandEvent &event)
{
	if(outAPIs->GetString(outAPIs->GetSelection()) == wxT("ASIO")){
		
		//was the item we just clicked selected?
		for(unsigned int i=0; i<audioOut->GetCount(); ++i){
			if(audioOut->GetString(i) == event.GetString()){
				if(audioOut->IsSelected(i)){
					//we selected it
					lastSelectedOutDevice = event.GetString();
#ifdef WIN32
					asioOutSetup->Show();
#endif
					return;
				}
				else{
					//we deselected it
					lastSelectedOutDevice = wxT("");
#ifdef WIN32
					asioOutSetup->Hide();
#endif
					return;
				}
			}
		}

	}
}

//////////////////////////////////////////////////////
void AudioDialog::UpdateDevices(wxCommandEvent &event)
{
	//clear the device list and populate it acording to the selected API

	wxString temp = inSampleRate->GetValue();
	audio->inSampleRate = ConvToInt(temp);
	wxString temp2 = outSampleRate->GetValue();
	audio->outSampleRate = ConvToInt(temp2);
	audioIn->Clear(); 
	audioIn->InsertItems( audio->GetInDevices( inAPIs->GetStringSelection() ), 0);
	audioOut->Clear(); 
	audioOut->InsertItems( audio->GetOutDevices( outAPIs->GetStringSelection() ), 0);
	lastSelectedOutDevice = wxT("");
#ifdef WIN32
	UpdateSetup();
#endif
	Refresh();
}
