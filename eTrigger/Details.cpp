//// Details.cpp ///////////////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "Details.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////
Details::Details(MainPanel *parent)
{
	mainPanel = parent;
}

//////////////////////////////
wxString Details::GetDetails()
{
	wxString detailData;

	detailData = wxT("USER DETAILS \n");
	detailData += wxT("------------ \n");
	detailData += wxT("ETRIGGER VERSION: ");
	detailData += mainPanel->version;
	
	detailData += wxT("\nSENT: ");
	detailData += ConvTowxString(mainPanel->security->currentTime.GetHour()) += wxT(":");
	detailData += ConvTowxString(mainPanel->security->currentTime.GetMinute()) += wxT(":");
	detailData += ConvTowxString(mainPanel->security->currentTime.GetSecond()) += wxT("  ");
	detailData += ConvTowxString(mainPanel->security->currentTime.GetMonth()+1) += wxT("/");
	detailData += ConvTowxString(mainPanel->security->currentTime.GetDay()) += wxT("/");
	detailData += ConvTowxString(mainPanel->security->currentTime.GetYear()) += wxT("\n");

	detailData += wxT("FIRST RUN TIME: "); 
	detailData += ConvTowxString(mainPanel->security->firstRunTime.GetHour()) += wxT(":");
	detailData += ConvTowxString(mainPanel->security->firstRunTime.GetMinute()) += wxT(":");
	detailData += ConvTowxString(mainPanel->security->firstRunTime.GetSecond()) += wxT("  ");
	detailData += ConvTowxString(mainPanel->security->firstRunTime.GetMonth()+1) += wxT("/");
	detailData += ConvTowxString(mainPanel->security->firstRunTime.GetDay()) += wxT("/");
	detailData += ConvTowxString(mainPanel->security->firstRunTime.GetYear()) += wxT("\n");

	detailData += wxT("LAST RUN TIME: "); 
	detailData += ConvTowxString(mainPanel->security->prevLastRunTime.GetHour()) += wxT(":");
	detailData += ConvTowxString(mainPanel->security->prevLastRunTime.GetMinute()) += wxT(":");
	detailData += ConvTowxString(mainPanel->security->prevLastRunTime.GetSecond()) += wxT("  ");
	detailData += ConvTowxString(mainPanel->security->prevLastRunTime.GetMonth()+1) += wxT("/");
	detailData += ConvTowxString(mainPanel->security->prevLastRunTime.GetDay()) += wxT("/");
	detailData += ConvTowxString(mainPanel->security->prevLastRunTime.GetYear()) += wxT("\n");

	detailData += wxT("\nSYSTEM INFO \n");
	detailData += wxT("----------- \n");
	detailData += wxT("OS: ");
	detailData += ::wxGetOsDescription();

	if(::wxIsPlatform64Bit()){
		detailData += wxT(" 64bit\n");
	}
	else{
		detailData += wxT(" 32bit\n");
	}
	detailData += wxT("COMPUTER ID: ");
	detailData += ConvTowxString(mainPanel->security->diskSerialEncoded);
	detailData += wxT("\nSERIAL: ");
	mainPanel->security->GetSerialNumberFromFile();
	detailData += ConvTowxString(mainPanel->security->serialNumber);
	detailData += wxT("\nREGISTERED: ");
	if(mainPanel->security->IsRegistered()){
		detailData += wxT("True\n");
	}
	else{
		detailData += wxT("False\n");
	}

	detailData += wxT("EMAIL: ");
	detailData += ConvTowxString(mainPanel->security->email);
	detailData += wxT("\n");

	detailData += wxT("\nDevice Info \n");
	detailData += wxT("----------- \n");

	detailData += wxT("AUDIO INPUT DEVICES: \n");
	wxArrayString inAPIs = mainPanel->audio->GetInDeviceAPIs();	
	for(unsigned int i=0; i<inAPIs.GetCount(); ++i){
		detailData += inAPIs.Item(i);
		detailData += wxT(":\n");
		wxArrayString inDevs = mainPanel->audio->GetInDevices(inAPIs.Item(i));
		for(unsigned int i=0; i<inDevs.GetCount(); ++i){
			detailData += wxT("       ");
			detailData += inDevs.Item(i);
			detailData += wxT("\n");
		}
	}

	detailData += wxT("\nAUDIO OUTPUT DEVICES: \n");
	wxArrayString outAPIs = mainPanel->audio->GetOutDeviceAPIs();
	for(unsigned int i=0; i<outAPIs.GetCount(); ++i){
		detailData += outAPIs.Item(i);
		detailData += wxT(":\n");
		wxArrayString outDevs = mainPanel->audio->GetOutDevices(outAPIs.Item(i));
		for(unsigned int i=0; i<outDevs.GetCount(); ++i){
			detailData += wxT("       ");
			detailData += outDevs.Item(i);
			detailData += wxT("\n");
		}
	}

	detailData += wxT("\nSELECTED AUDIO INPUT DEVICES: \n");
	for(unsigned int i=0; i<mainPanel->audio->selectedIn.GetCount(); ++i){
		detailData += mainPanel->audio->selectedIn.Item(i);
		detailData += wxT("\n");
	}

	detailData += wxT("\nSELECTED AUDIO OUTPUT DEVICES: \n");
	for(unsigned int i=0; i<mainPanel->audio->selectedOut.GetCount(); ++i){
		detailData += mainPanel->audio->selectedOut.Item(i);
		detailData += wxT("\n");
	}
	
	detailData += wxT("\nMIDI INPUT DEVICES: \n");
	wxArrayString inDev = mainPanel->midi->GetInDevices();
	for(unsigned int i=0; i<inDev.GetCount(); ++i){
		detailData += inDev.Item(i);
		detailData += wxT("\n");
	}

	detailData += wxT("\nMIDI OUTPUT DEVICES: \n");
	wxArrayString outDev = mainPanel->midi->GetOutDevices();
	for(unsigned int i=0; i<outDev.GetCount(); ++i){
		detailData += outDev.Item(i);
		detailData += wxT("\n");
	}

	detailData += wxT("\nSELECTED MIDI INPUT DEVICES: \n");
	for(unsigned int i=0; i<mainPanel->midi->selectedIn.GetCount(); ++i){
		detailData += mainPanel->midi->selectedIn.Item(i);
		detailData += wxT("\n");
	}

	detailData += wxT("\nSELECTED MIDI OUTPUT DEVICES: \n");
	for(unsigned int i=0; i<mainPanel->midi->selectedOut.GetCount(); ++i){
		detailData += mainPanel->midi->selectedOut.Item(i);
		detailData += wxT("\n");
	}

	detailData += wxT("\nGAME DEVICES: \n");
	wxArrayString gameDevs = mainPanel->joystick->GetDevices();
	for(unsigned int i=0; i<gameDevs.GetCount(); ++i){
		detailData += gameDevs.Item(i);
		detailData += wxT("\n");
	}

	detailData += wxT("\nSELECTED GAME DEVICES: \n");
	for(unsigned int i=0; i<mainPanel->joystick->selected.GetCount(); ++i){
		detailData += mainPanel->joystick->selected.Item(i);
		detailData += wxT("\n");
	}

	detailData += wxT("\nOPTIONS:");
	detailData += wxT("\n   splashScreen = "); detailData += ConvTowxString(mainPanel->splashScreen);
	detailData += wxT("\n   toolTips = "); detailData += ConvTowxString(mainPanel->toolTips);
	detailData += wxT("\n   meters = "); detailData += ConvTowxString(mainPanel->trackProc->enableMeters);
	detailData += wxT("\n   liveMode = "); detailData += ConvTowxString(mainPanel->trackProc->preLoad);
	detailData += wxT("\n   startupFile = "); detailData += mainPanel->initFilename;
	detailData += wxT("\n   mouseSensitivity = "); detailData += ConvTowxString(mainPanel->trackProc->mouseSensitivity);
	detailData += wxT("\n   audioBuffer = "); detailData += ConvTowxString(mainPanel->trackProc->audio->framesPerBuffer);
	detailData += wxT("\n   midiThru = "); detailData += ConvTowxString(mainPanel->trackProc->midiBleed);
  //detailData += wxT("\n   midiInputChannels = "); detailData += /*Todo*/);
	detailData += wxT("\n   retriggerSafty = "); detailData += ConvTowxString(mainPanel->trackProc->retriggerSafty);
	detailData += wxT("\n   retriggerThreshold = "); detailData += ConvTowxString(mainPanel->trackProc->retriggerThreshold);
	detailData += wxT("\n   joystickPollSpeed = "); detailData += ConvTowxString(mainPanel->joystick->pollSpeed);
	detailData += wxT("\n   joyMinX = "); detailData += ConvTowxString(mainPanel->joystick->GetMinX());
	detailData += wxT("\n   joyMinY = "); detailData += ConvTowxString(mainPanel->joystick->GetMinY());
	detailData += wxT("\n   joyMinZ = "); detailData += ConvTowxString(mainPanel->joystick->GetMinZ());
	detailData += wxT("\n   joyMinR = "); detailData += ConvTowxString(mainPanel->joystick->GetMinR());
	detailData += wxT("\n   joyMinU = "); detailData += ConvTowxString(mainPanel->joystick->GetMinU());
	detailData += wxT("\n   joyMinV = "); detailData += ConvTowxString(mainPanel->joystick->GetMinV());
	detailData += wxT("\n   joyMaxX = "); detailData += ConvTowxString(mainPanel->joystick->GetMaxX());
	detailData += wxT("\n   joyMaxY = "); detailData += ConvTowxString(mainPanel->joystick->GetMaxY());
	detailData += wxT("\n   joyMaxZ = "); detailData += ConvTowxString(mainPanel->joystick->GetMaxZ());
	detailData += wxT("\n   joyMaxR = "); detailData += ConvTowxString(mainPanel->joystick->GetMaxR());
	detailData += wxT("\n   joyMaxU = "); detailData += ConvTowxString(mainPanel->joystick->GetMaxU());
	detailData += wxT("\n   joyMaxV = "); detailData += ConvTowxString(mainPanel->joystick->GetMaxV());
	
	return detailData;
}