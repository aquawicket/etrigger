//// Process.cpp ///////////////////////////////////////////////////////////
//
// All signals (Audio, Midi, Joystick, Keyboard, Mouse, Com) are sent here.
//
// Input Codes
// -----------
// input       device   channel    value 
// type          #        #          #
//   0          00        00        000
//1=Midi       00-99     01-16    000-999
//2=Audio      00-99      00      000-999
//3=Joystick   00-99      00      000-999
//4=Keyboard   00-99      00      000-999
//5=Mouse      00-99      00      000-999
//6=ComPort    00-99      00      000-999
//
// i.e. 30200011  <--- Joystick 2, button 11
//  or. 10104062  <--- Midi, device 1, channel 4, note 62
//
//
////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "Process.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifdef VST
EtriggerEffect* Process::vst = NULL;
#endif //VST

TrackProc* Process::trackProc = NULL;
Midi* Process::midi = NULL;
StatusDialog* Process::statusDialog = NULL;
MidiMonitor* Process::midiMonitor = NULL;
SequencePlayer* Process::sequencePlayer = NULL;
MenuPanel* Process::menuPanel = NULL;
bool Process::active = false;
bool Process::Learning = false;
int Process::LearnReply = 0;
bool Process::confirmWait = false;
bool Process::match = false;
int Process::trackNum = 0;
int Process::zoneNum = 0;
int Process::trackType = 0;
bool Process::cancelOutput = false;
bool Process::detectingRetrigger = false;
int Process::retriggerTrackNum = 0;
int Process::retriggerZoneNum = 0;
bool Process::detectingWaitTime = false;
int Process::waitTimeTrackNum = 0;
DeviceInfo Process::devInfo;
Timer Process::timer;
double Process::latency;
int Process::velToPosAvgCycle = 0;
int Process::posToVelAvgCycle = 0;
//ION Process::ion[10];
std::vector<unsigned char> Process::output(3);
int Process::tempo[5];

////////////////////////////////////
BEGIN_EVENT_TABLE(Process, wxWindow)
	EVT_IDLE     (Process::IdleLoop)
END_EVENT_TABLE()

/////////////////////////////////////////////////////////
Process::Process(wxWindow* parent): wxWindow(parent, -1)
{ 
	this->Hide(); //deriving from wxWindow and hiding is only neccessary to get the IdleLoop() event
	SetExtraStyle(wxWS_EX_PROCESS_IDLE); 
	timer.start();  //Start the master timer
}

/////////////////////////////////////////
void Process::LinkTrk(TrackProc *mytrack) //this must be called first with the active Trk database.
{
	trackProc = mytrack; //pointer to Trk database.
}

//////////////////////////////////////
void Process::LinkMidi(Midi *ref)
{
	midi = ref;
}

///////////////////////////////////////////
#ifdef VST
void Process::LinkVST(EtriggerEffect *host)
{
	vst = host;
}
#endif //VST

///////////////////////////////////////////
void Process::LinkStatus(StatusDialog *status)
{
	statusDialog = status;
}

///////////////////////////////////////////
void Process::LinkMenu(MenuPanel *menu)
{
	menuPanel = menu;
}

//////////////////////////////////////////////////
void Process::LinkMidiMonitor(MidiMonitor *midmon)
{
	midiMonitor = midmon;
}

//////////////////////////////////////////////////
void Process::LinkSequencePlayer(SequencePlayer *sp)
{
	sequencePlayer = sp;
}


//This is where we handle Multi-Zone input. We will hold the information here untill all of the 
//required data has arrived or until a certain amount of time has passed.
//////////////////////////////////////////
void Process::IdleLoop(wxIdleEvent &event)
{
	//The job of this loop is to push the stored data of a MultiZone track to processing
	//if time is up. 

	event.Skip(true);			//do not propagate this event

	for(int i=1; i<(trackProc->tracks+1); ++i){
		if(trackProc->n[i].waitForPiezo == true){  
		
			if (waitTimeTrackNum != i //not learning this wait time
				&& timer.getElapsedTimeInMilliSec() - trackProc->n[i].firstPiezoHitTime >= trackProc->n[i].multiZoneWaitTime){
				
				event.RequestMore(false);
				MultiZoneOutput(i);
			}

			event.RequestMore(true);
		}

	}
}






///////////////////////////////////////////////////////////////////////////////////////
//                        !!! ALL SIGNALS ARE SENT HERE !!!                          //
///////////////////////////////////////////////////////////////////////////////////////
void Process::Send(int signalType, wxString string, int num, std::vector<unsigned char>& message)
{
	latency = timer.getElapsedTimeInMilliSec();

	if(!active){return;}
	//This function collects input signals. From here the signal will be evaluated
	//and output signal data will be created and passed on. 

	///////////////////////////////// MIDI /////////////////////////////////
	////////////////////////////////////////////////////////////////////////	
	if(signalType == 1){
		//string     = device name
		//num        = device number
		//message[0] = midi channel
		//message[1] = midi note
		//message[2] = velocity

		/////////////////////// MIDI NOTE-ON SIGNAL ////////////////////////////
		if(message[0] > 143 && message[0] < 160 && message[2] > 0){ //is it a Note-On signal  

			if(!trackProc->midiChannel[message[0]-143]){ return ;} //don't listen to channels that arn't selected.
					
			if(Learning == true && trackType == 1){
				devInfo.deviceName = string;
				devInfo.inputDetails = wxString::Format(wxT("Midi Hit:  Channel-%d, Note-%d"), (message[0]-143), message[1]);
				LearnReply = (num * 100000) + ((message[0]-143) * 1000) + (message[1] + 10000000);
				return;
			}

			match = false; //used for midi Bleed.
			for(trackNum=1; trackNum < (trackProc->tracks+1); ++trackNum){ //cycle through all the tracks
				if(trackProc->n[trackNum].midiType == 1){ //If it's a Trigger track, let's check it
					for(zoneNum=0; zoneNum<trackProc->n[trackNum].zones; ++zoneNum){ //Check all zones

						if(((num * 100000) + ((message[0]-143) * 1000) + (message[1] + 10000000)) == trackProc->n[trackNum].inputCode[zoneNum]){ //check for the match
							
							match = true;
							
							if(!Retrigger(message[2])){

								//Check for Multi Zone
								if(trackProc->n[trackNum].zones > 1){

									//Store the Velocity Information
									trackProc->n[trackNum].storedVelocity[zoneNum] = message[2];

									//Does this complete the zones?
									bool go = true;
									for(int z=0; z<trackProc->n[trackNum].zones; ++z){ //Check all zones
										if(trackProc->n[trackNum].storedVelocity[z] == 0){go = false;}
									}
									if(go){
										MultiZoneOutput(trackNum);
									}
									else{
										if(trackProc->n[trackNum].firstPiezoHitTime == 0){
											trackProc->n[trackNum].firstPiezoHitTime = timer.getElapsedTimeInMilliSec();
										}
										trackProc->n[trackNum].waitForPiezo = true;
										//The Idle Loop is active for this track.
									}
								}

								else{  //if it's just a single zone, send it.

									output[0] = trackProc->n[trackNum].outputChannel[zoneNum] + 143;
									output[1] = trackProc->n[trackNum].outputNote[zoneNum];
									output[2] = message[2];
									CCControlledVelocity(output);
									PreGain(output);
									Limiter(output);
									Dynamics(output);
									Volume(output);
									AntiMachineGun(output);
									Alteration(output);
									MidiCCControlledOutput(output);
									VelocityControlledOutput(output);
									SequenceOutput();
									MouseOutput();
									Output(output);
									trackProc->n[trackNum].lastWasNoteOff[zoneNum] = false;
								}
							}
						}
					}
				}
			}
			if(!match && trackProc->midiBleed){	
				trackNum = 0;
				zoneNum = 0;
				Output(message); 
			}

			//Send direct
			//statusDialog->Input(wxString::Format(wxT("Midi Note-ON: ch-%d note-%d vel-%d"), (message[0]-143), message[1], message[2]));

			//Send by event
			if(statusDialog->IsShown()){
				StatusDialogEvent event(wxEVT_COMMAND_STATUSDIALOG, trackProc->trackPanel->mainPanel->process->GetId()); //ID of where we come from?
				event.SetInOut(1); //set event flag to input
				event.SetValue(wxString::Format(wxT("Midi Note-ON: ch-%d note-%d vel-%d"), (message[0]-143), message[1], message[2]));
				wxPostEvent(statusDialog->GetEventHandler(), event); //event handler of the gui object
			}
		}

		/////////////////////// MIDI NOTE-OFF SIGNAL ////////////////////////////
		if(message[0] > 143 && message[0] < 160 && message[2] == 0){ //is it a Note-Off signal 

			if(!trackProc->midiChannel[message[0]-143]){ return ;} //don't listen to channels that arn't selected.

			match = false; //used for midi Bleed.
			for(trackNum=1; trackNum<trackProc->tracks+1; ++trackNum){ //cycle through all the tracks
				if(trackProc->n[trackNum].midiType == 1){ //If it's a Trigger track, let's check it
					for(zoneNum=0; zoneNum<trackProc->n[trackNum].zones; ++zoneNum){ //Check all zones
						if(((num * 100000) + ((message[0]-143) * 1000) + (message[1] + 10000000)) == trackProc->n[trackNum].inputCode[zoneNum]){ //check for the match
						
							match = true;

							if(trackProc->n[trackNum].noteOff[zoneNum] && !trackProc->n[trackNum].lastWasNoteOff[zoneNum]){
								output[0] = trackProc->n[trackNum].outputChannel[zoneNum] + 143;
								output[1] = trackProc->n[trackNum].outputNote[zoneNum];
								output[2] = 0;
								Alteration(output);
								MidiCCControlledOutput(output);
							    VelocityControlledOutput(output);
								MouseOutput();
								Output(output);
								trackProc->n[trackNum].lastWasNoteOff[zoneNum] = true;
							}
						}
					}
				}
			}
			if(!match && trackProc->midiBleed){	
				trackNum = 0;
				zoneNum = 0;
				Output(message); 
			}
			//statusDialog->Input(wxString::Format(wxT("Midi Note-OFF: ch-%d note-%d vel-%d"), (message[0]-143), message[1], message[2]));
			//Send by event
			if(statusDialog->IsShown()){
				StatusDialogEvent event(wxEVT_COMMAND_STATUSDIALOG, trackProc->trackPanel->mainPanel->process->GetId()); //ID of where we come from?
				event.SetInOut(1); //set event flag to input
				event.SetValue(wxString::Format(wxT("Midi Note-OFF: ch-%d note-%d vel-%d"), (message[0]-143), message[1], message[2]));
				wxPostEvent(statusDialog->GetEventHandler(), event); //event handler of the gui object
			}
		}

		/////////////////////// MIDI NOTE-OFF SIGNAL ////////////////////////////
		if(message[0] > 127 && message[0] < 144){

			if(!trackProc->midiChannel[message[0]-127]){ return ;} //don't listen to channels that arn't selected.

			match = false; //used for midi Bleed.
			for(trackNum=1; trackNum<trackProc->tracks+1; ++trackNum){ //cycle through all the tracks
				if(trackProc->n[trackNum].midiType == 1){ //If it's a Trigger track, let's check it
					for(zoneNum=0; zoneNum<trackProc->n[trackNum].zones; ++zoneNum){ //Check all zones
						if(((num * 100000) + ((message[0]-127)* 1000) + (message[1] + 10000000)) == trackProc->n[trackNum].inputCode[zoneNum]){ //check for the match
						
							match = true;

							if(trackProc->n[trackNum].noteOff[zoneNum] && !trackProc->n[trackNum].lastWasNoteOff[zoneNum]){
								output[0] = trackProc->n[trackNum].outputChannel[zoneNum] + 127;
								output[1] = trackProc->n[trackNum].outputNote[zoneNum];
								output[2] = 0;
								Alteration(output);
								MidiCCControlledOutput(output);
							    VelocityControlledOutput(output);
								MouseOutput();
								Output(output);
								trackProc->n[trackNum].lastWasNoteOff[zoneNum] = true;
							}
						}
					}
				}
			}
			if(!match && trackProc->midiBleed){
				trackNum = 0;
				zoneNum = 0;
				Output(message); 
			}
			//statusDialog->Input(wxString::Format(wxT("Midi Note-OFF: ch-%d note-%d vel-%d"), (message[0]-127), message[1], message[2]));
			//Send by event
			if(statusDialog->IsShown()){
				StatusDialogEvent event(wxEVT_COMMAND_STATUSDIALOG, trackProc->trackPanel->mainPanel->process->GetId()); //ID of where we come from?
				event.SetInOut(1); //set event flag to input
				event.SetValue(wxString::Format(wxT("Midi Note-OFF: ch-%d note-%d vel-%d"), (message[0]-127), message[1], message[2]));
				wxPostEvent(statusDialog->GetEventHandler(), event); //event handler of the gui object
			}
		}

        /////////////////////// MIDI AFTERTOUCH SIGNAL ////////////////////////////
		if(message[0] > 159 && message[0] < 176){

			if(!trackProc->midiChannel[message[0]-159]){ return ;} //don't listen to channels that arn't selected.

			match = false; //used for midi Bleed.
			if(!match && trackProc->midiBleed){
				trackNum = 0;
				zoneNum = 0;
				Output(message); 
			}
			//statusDialog->Input(wxString::Format(wxT("Midi Aftertouch: ch-%d note-%d vel-%d"), (message[0]-159), message[1], message[2]));
			//Send by event
			if(statusDialog->IsShown()){
				StatusDialogEvent event(wxEVT_COMMAND_STATUSDIALOG, trackProc->trackPanel->mainPanel->process->GetId()); //ID of where we come from?
				event.SetInOut(1); //set event flag to input
				event.SetValue(wxString::Format(wxT("Midi Aftertouch: ch-%d note-%d vel-%d"), (message[0]-159), message[1], message[2]));
				wxPostEvent(statusDialog->GetEventHandler(), event); //event handler of the gui object
			}
		}


		//////////////////////// MIDI-CC SIGNAL ////////////////////////////
		if(message[0] > 175 && message[0] < 192){

			if(!trackProc->midiChannel[message[0]-175]){ return ;} //don't listen to channels that arn't selected.

			// The MPS-400 drum module sends choke data in Midi CC format. 
			//185 99 50
            //185 98 32
            //185  6 24
            //185 99 50
            //185 98 32
            //185  6 26
			// Let's work em in here sometime.

			if(Learning == true && trackType == 2){
				devInfo.deviceName = string;
				devInfo.inputDetails = wxString::Format(wxT("Midi CC: Channel-%d Note-%d"), (message[0]-175), message[1]);
				LearnReply = (num * 100000) + ((message[0]-175) * 1000) + (message[1] + 10000000);
			}

			match = false; //used for midi Bleed.
			for(trackNum=1; trackNum < (trackProc->tracks+1); ++trackNum){ //cycle through all the tracks
				if(trackProc->n[trackNum].midiType == 2){ //If it's a MidiCC track, let's check it
					if(((num * 100000) + ((message[0]-175) * 1000) + (message[1] + 10000000)) == trackProc->n[trackNum].inputCode[0]){ //check for the match
						
						match = true;
						zoneNum = 0;

						output[0] = trackProc->n[trackNum].outputChannel[0]  + 175;
						output[1] = trackProc->n[trackNum].outputNote[0];

						if(!trackProc->n[trackNum].ccReverse){
							output[2] = message[2];
						}
						else{
							output[2] = 127 - message[2];
						}
						
						Compressor(output);

						if(output[2] != trackProc->n[trackNum].lastOutputVelocity[0]){
							trackProc->n[trackNum].lastOutputVelocity[0] = output[2]; 
							PedalDownEvent(output);
							Output(output);
						}
					}
				}
			}
			if(!match && trackProc->midiBleed){	
				trackNum = 0;
				zoneNum = 0;
				Output(message); 
			}
			//statusDialog->Input(wxString::Format(wxT("Midi CC: ch-%d note-%d vel-%d"), (message[0]-175), message[1], message[2]));
			//Send by event
			if(statusDialog->IsShown()){
				StatusDialogEvent event(wxEVT_COMMAND_STATUSDIALOG, trackProc->trackPanel->mainPanel->process->GetId()); //ID of where we come from?
				event.SetInOut(1); //set event flag to input
				event.SetValue(wxString::Format(wxT("Midi CC: ch-%d note-%d vel-%d"), (message[0]-175), message[1], message[2]));
				wxPostEvent(statusDialog->GetEventHandler(), event); //event handler of the gui object
			}
		}
		
		/*
		/////////////////////// MIDI PC SIGNAL ////////////////////////////
		if(message[0] > 191 && message[0] < 208){
			
			// The MPS-400 drum module sends 201 XX commands before it sends note on signals in internal midi format.
			// the XX changes as the user changes kits on the module. Let's ignore these for now and see if the
			// note-ON/OFF signals get through ok.

			//if(string != wxT("Device: MPS-400")){

			if(!trackProc->midiChannel[message[0]-191]){ return ;} //don't listen to channels that arn't selected.

				match = false; //used for midi Bleed.
				if(!match && trackProc->midiBleed){	
					trackNum = 0;
					zoneNum = 0;
					Output(message); 
				}
				statusDialog->Input(wxString::Format(wxT("Midi PC: ch-%d note-%d"), (message[0]-191), message[1]));
			}
		}
		*/

		//midiMonitor->Input(message);
		if(midiMonitor->IsShown()){
			wxString temp;
			for(unsigned int i=0; i<message.size(); ++i){
				temp += wxString::Format(wxT("%d "), message[i]);
			}
			MidiMonitorEvent event(wxEVT_COMMAND_MIDIMONITOR, trackProc->trackPanel->mainPanel->process->GetId()); //ID of where we come from?
			event.SetValue(temp);
			wxPostEvent(midiMonitor->GetEventHandler(), event); //event handler of the gui object
		}
			return;
	}


	///////////////////////////////// AUDIO /////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	if(signalType == 2){
		
		//string     = device name
		//num        = device number
		//message[0] = device number
		//message[1] = channel number
		//message[2] = velocity

		/////////////////////// AUDIO TRIGGER SIGNAL ////////////////////////////
		if(message[2] > 0){ //is it a Note-On signal 

			//// LEARNING ////////////////
			if(Learning == true && trackType == 1){
	
				int overwrite = wxYES;
				for(trackNum=1; trackNum < (trackProc->tracks+1); ++trackNum){ //cycle through all the tracks
					for(zoneNum=0; zoneNum<trackProc->n[trackNum].zones; ++zoneNum){ //Check all zones
						
						if((message[0] * 100000) + (message[1] + 20000000) == trackProc->n[trackNum].inputCode[zoneNum]){
							confirmWait = true;
							overwrite = wxMessageBox(wxT("This device channel is allready set to another track, switch it to this track?"), wxT("Channel in use"), wxYES_NO | wxSTAY_ON_TOP);
							if(overwrite == wxYES){trackProc->n[trackNum].inputCode[zoneNum] = 0;} //reset any track that uses this inputCode.
						}
					}
				}
                
				if(overwrite == wxYES){
					wxString temp = string;
					devInfo.deviceName = wxString(wxT("Device: ")) += temp;
					devInfo.inputDetails = wxString::Format(wxT("Audio IN Channel: %d"),message[1]+1);
					LearnReply = (message[0] * 100000) + (message[1] + 20000000);
					//Learning = false;
				}
				confirmWait = false;
			}
			///////////////////////////////////////

			for(trackNum=1; trackNum < (trackProc->tracks+1); ++trackNum){ //cycle through all the tracks
				if(trackProc->n[trackNum].midiType == 1){ //If it's a trigger track, let's check it
					for(zoneNum=0; zoneNum<trackProc->n[trackNum].zones; ++zoneNum){ //Check all zones
						if((message[0] * 100000) + (message[1] + 20000000) == trackProc->n[trackNum].inputCode[zoneNum]){ //check for the match
													
							if(!Retrigger(message[2])){

								//Check for Multi Zone
								if(trackProc->n[trackNum].zones > 1){

									//Store the Velocity Information
									trackProc->n[trackNum].storedVelocity[zoneNum] = message[2];

									//Does this complete the zones?
									bool go = true;
									for(int z=0; z<trackProc->n[trackNum].zones; ++z){ //Check all zones
										if(trackProc->n[trackNum].storedVelocity[z] == 0){go = false;}
									}
									if(go){
										MultiZoneOutput(trackNum);
									}
									else{
										if(trackProc->n[trackNum].firstPiezoHitTime == 0){
											trackProc->n[trackNum].firstPiezoHitTime = timer.getElapsedTimeInMilliSec();
										}
									    trackProc->n[trackNum].waitForPiezo = true;
										//The Idle Loop is active for this track.
									}
								}

								else{  //if it's just a single zone, send it.

									//std::vector<unsigned char>output(3);
									output[0] = trackProc->n[trackNum].outputChannel[zoneNum] + 143;
									output[1] = trackProc->n[trackNum].outputNote[zoneNum];
									output[2] = message[2];
									CCControlledVelocity(output);
									Limiter(output);
									Dynamics(output);
									AntiMachineGun(output);
									Alteration(output);
									MidiCCControlledOutput(output);
							        VelocityControlledOutput(output);
									SequenceOutput();
									MouseOutput();
									Output(output);

									if(trackProc->n[trackNum].noteOff[zoneNum]){
										output[0] = trackProc->n[trackNum].outputChannel[zoneNum] + 127;
										output[1] = trackProc->n[trackNum].outputNote[zoneNum];
										output[2] = 0;
										Alteration(output);
										MidiCCControlledOutput(output);
							            VelocityControlledOutput(output);
										Output(output);
									}
								}
							}
						}
					}				
				}
			}	
			//too much latency to put at top
			//statusDialog->Input(wxString::Format(wxT("%s: ch-%d: vel-%d"), string.c_str(), message[1]+1, message[2]));
			//Send by event
			if(statusDialog->IsShown()){
				StatusDialogEvent event(wxEVT_COMMAND_STATUSDIALOG, trackProc->trackPanel->mainPanel->process->GetId()); //ID of where we come from?
				event.SetInOut(1); //set event flag to input
				event.SetValue(wxString::Format(wxT("%s: ch-%d: vel-%d"), string.c_str(), message[1]+1, message[2]));
				wxPostEvent(statusDialog->GetEventHandler(), event); //event handler of the gui object
			}
				return;
		}
		wxMessageBox(wxT("Error: Audio Proc is attempting to send 0 velocities"),wxT(""), wxSTAY_ON_TOP);
	}



	///////////////////////////////// JOYSTICK /////////////////////////////
	////////////////////////////////////////////////////////////////////////
	if(signalType == 3){
		//string     = device name
		//message[0] = device #
		//message[1] = button / axis #
		//message[2] = down = 64, up = 0, vel = 0-127
		
		/////////////////////// JOYSTICK BUTTON DOWN SIGNAL ////////////////////////////
		if(message[1] > 0 && message[1] < 33 && message[2] == 64){ //is it a Note-On signal  
						
			if(Learning == true){
				if(string == wxT("DRUM") && message[1] > 6){ //ION IED05
					devInfo.deviceName = string;
					devInfo.inputDetails = wxString::Format(wxT("Button: %d"), message[1]);
					LearnReply = (message[0] * 100000) + (message[1] + 30000000);
				}   
				else{
					devInfo.deviceName = string;
					devInfo.inputDetails = wxString::Format(wxT("Button: %d"), message[1]);
					LearnReply = (message[0] * 1000) + (message[1] + 300000);
				}
				
			}
			
			for(trackNum=1; trackNum < (trackProc->tracks+1); ++trackNum){ //cycle through all the tracks
				if(trackProc->n[trackNum].midiType == 1){ //If it's a Trigger track, let's check it
					for(zoneNum=0; zoneNum<trackProc->n[trackNum].zones; ++zoneNum){ //Check all zones
						if((message[0] * 100000) + (message[1] + 30000000) == trackProc->n[trackNum].inputCode[zoneNum]){ //check for the match
							
							if(!Retrigger(message[2])){

								//Check for Multi Zone
								if(trackProc->n[trackNum].zones > 1){

									//Store the Velocity Information
									trackProc->n[trackNum].storedVelocity[zoneNum] = 64;

									//Does this complete the zones?
									bool go = true;
									for(int z=0; z<trackProc->n[trackNum].zones; ++z){ //Check all zones
										if(trackProc->n[trackNum].storedVelocity[z] == 0){go = false;}
									}
									if(go){
										MultiZoneOutput(trackNum);
									}
									else{
										if(trackProc->n[trackNum].firstPiezoHitTime == 0){
											trackProc->n[trackNum].firstPiezoHitTime = timer.getElapsedTimeInMilliSec();
										}
										trackProc->n[trackNum].waitForPiezo = true;
										//The Idle Loop is active for this track.
									}
								}

								else{  //if it's just a single zone, send it.
										output[0] = trackProc->n[trackNum].outputChannel[zoneNum] + 143;;
										output[1] = trackProc->n[trackNum].outputNote[zoneNum];
										output[2] = 64;
										CCControlledVelocity(output);
										PreGain(output);
										Limiter(output);
									    Dynamics(output);
										Volume(output);
										AntiMachineGun(output);
										Alteration(output);
										MidiCCControlledOutput(output);
							            VelocityControlledOutput(output);
										SequenceOutput();
										MouseOutput();
										Output(output);
										trackProc->n[trackNum].lastWasNoteOff[zoneNum] = false;
								}
							}
						}
					}
				}

				if(trackProc->n[trackNum].midiType == 2){ //If it's a MidiCC track, let's check it
					if((message[0] * 100000) + (message[1] + 30000000) == trackProc->n[trackNum].inputCode[0]){ //check for the match
						
						zoneNum = 0;

						//std::vector<unsigned char>output(3);
						output[0] = trackProc->n[trackNum].outputChannel[zoneNum] + 175;
						output[1] = trackProc->n[trackNum].outputNote[zoneNum];

						if(!trackProc->n[trackNum].ccReverse){ output[2] = 127;	}
						else{ output[2] = 0; }
						
						PedalDownEvent(output);
						Compressor(output);
						Output(output);
					}
				}
			}
			//statusDialog->Input(wxString::Format(wxT("%s: Button Down: but-%d"), string.c_str(), message[1]));
			//Send by event
			if(statusDialog->IsShown()){
				StatusDialogEvent event(wxEVT_COMMAND_STATUSDIALOG, trackProc->trackPanel->mainPanel->process->GetId()); //ID of where we come from?
				event.SetInOut(1); //set event flag to input
				event.SetValue(wxString::Format(wxT("%s: Button Down: but-%d"), string.c_str(), message[1]));
				wxPostEvent(statusDialog->GetEventHandler(), event); //event handler of the gui object
			}
				return;
		}

		/////////////////////// JOYSTICK BUTTON UP SIGNAL ////////////////////////////
		if(message[1] > 0 && message[1] < 33 && message[2] == 0){ //is it a Note-Off signal  

			for(trackNum=1; trackNum < (trackProc->tracks+1); ++trackNum){ //cycle through all the tracks
				if(trackProc->n[trackNum].midiType == 1){ //If it's a Trigger track, let's check it
					for(zoneNum=0; zoneNum<trackProc->n[trackNum].zones; ++zoneNum){ //Check all zones
						if((message[0] * 100000) + (message[1] + 30000000) == trackProc->n[trackNum].inputCode[zoneNum]){ //check for the match

							if(trackProc->n[trackNum].noteOff[zoneNum]&& !trackProc->n[trackNum].lastWasNoteOff[zoneNum]){
								output[0] = trackProc->n[trackNum].outputChannel[zoneNum] + 127;
								output[1] = trackProc->n[trackNum].outputNote[zoneNum];
								output[2] = 0;
								Alteration(output);
								MidiCCControlledOutput(output);
							    VelocityControlledOutput(output);
								Output(output);
								trackProc->n[trackNum].lastWasNoteOff[zoneNum] = true;
							}
						}
					}
				}

				if(trackProc->n[trackNum].midiType == 2){ //If it's a MidiCC track, let's check it
					if((message[0] * 100000) + (message[1] + 30000000) == trackProc->n[trackNum].inputCode[0]){ //check for the match
						
						zoneNum = 0;

						output[0] = trackProc->n[trackNum].outputChannel[zoneNum] + 175;
						output[1] = trackProc->n[trackNum].outputNote[zoneNum];

						if(!trackProc->n[trackNum].ccReverse){ output[2] = 0;	}
						else{ output[2] = 127; }
						
						PedalDownEvent(output);
						Compressor(output);
						Output(output);
					}
				}
			}
			//statusDialog->Input(wxString::Format(wxT("%s: Button Up: but-%d"), string.c_str(), message[1]));
			//Send by event
			if(statusDialog->IsShown()){
				StatusDialogEvent event(wxEVT_COMMAND_STATUSDIALOG, trackProc->trackPanel->mainPanel->process->GetId()); //ID of where we come from?
				event.SetInOut(1); //set event flag to input
				event.SetValue(wxString::Format(wxT("%s: Button Up: but-%d"), string.c_str(), message[1]));
				wxPostEvent(statusDialog->GetEventHandler(), event); //event handler of the gui object
			}
				return;
		}

		/////////////////////// JOYSTICK AXIS SIGNAL ////////////////////////////
		if(message[1] == 'X' || message[1] == 'Y' || message[1] == 'Z' || message[1] == 'R' || message[1] == 'U' || message[1] == 'V'){ 
			
			if(Learning == true){
					devInfo.deviceName = string;
					devInfo.inputDetails = wxString::Format(wxT("Joy Axis: %c"), message[1]);
					LearnReply = (message[0] * 100000) + (message[1] + 30000000);
			}

			for(trackNum=1; trackNum < (trackProc->tracks+1); ++trackNum){ //cycle through all the tracks
				if(trackProc->n[trackNum].midiType == 2){ //If it's a MidiCC track, let's check it
					for(zoneNum=0; zoneNum<trackProc->n[trackNum].zones; ++zoneNum){ //Check all zones
						if((message[0] * 100000) + (message[1] + 30000000) == trackProc->n[trackNum].inputCode[zoneNum]){ //check for the match
						
							output[0] = trackProc->n[trackNum].outputChannel[zoneNum] + 175;
							output[1] = trackProc->n[trackNum].outputNote[zoneNum];

							if(!trackProc->n[trackNum].ccReverse){
								output[2] = message[2];
							}
							else{
								output[2] = 127 - message[2];
							}
						
							PedalDownEvent(output);
							Compressor(output);
							Output(output);
						}
					}
				}

				if(trackProc->n[trackNum].midiType == 1){ //If it's a Trigger track, let's check it
					for(zoneNum=0; zoneNum<trackProc->n[trackNum].zones; ++zoneNum){ //Check all zones
						if((message[0] * 100000) + (message[1] + 30000000) == trackProc->n[trackNum].inputCode[zoneNum]){ //check for the match
														
							if(message[2] > 0){		
								if(!Retrigger(message[2])){
									output[0] = trackProc->n[trackNum].outputChannel[zoneNum] + 143;
									output[1] = trackProc->n[trackNum].outputNote[zoneNum];
									output[2] = message[2];
									CCControlledVelocity(output);
									PreGain(output);
									Limiter(output);
									Dynamics(output);
									Volume(output);
									AntiMachineGun(output);
									Alteration(output);
									MidiCCControlledOutput(output);
							        VelocityControlledOutput(output);
									SequenceOutput();
									MouseOutput();
									Output(output);
									trackProc->n[trackNum].lastWasNoteOff[zoneNum] = false;
								}
							}
							
							else if(trackProc->n[trackNum].noteOff[zoneNum] && !trackProc->n[trackNum].lastWasNoteOff[zoneNum]){
								output[0] = trackProc->n[trackNum].outputChannel[zoneNum] + 127;
								output[1] = trackProc->n[trackNum].outputNote[zoneNum];
								output[2] = 0;
								Alteration(output);
								MidiCCControlledOutput(output);
							    VelocityControlledOutput(output);
								Output(output);
								trackProc->n[trackNum].lastWasNoteOff[zoneNum] = true;
							}
						}	
					}
				}
			}

			//statusDialog->Input(wxString::Format(wxT("%s: Axis %c: %d"), string.c_str(), message[1], message[2]));
			//Send by event
			if(statusDialog->IsShown()){
				StatusDialogEvent event(wxEVT_COMMAND_STATUSDIALOG, trackProc->trackPanel->mainPanel->process->GetId()); //ID of where we come from?
				event.SetInOut(1); //set event flag to input
				event.SetValue(wxString::Format(wxT("%s: Axis %c: %d"), string.c_str(), message[1], message[2]));
				wxPostEvent(statusDialog->GetEventHandler(), event); //event handler of the gui object
			}
				return;
		}
		wxMessageBox(wxString::Format(wxT("Error: Recieved an Unknown Signal Type from JoyProc %d %d %d"), message[0], message[1], message[2]),wxT(""), wxSTAY_ON_TOP);
	}



	///////////////////////////////// KEYBOARD /////////////////////////////
	////////////////////////////////////////////////////////////////////////
	if(signalType == 4){

		//string     = "Device: Keyboard"
		//message[0] = Key Code 
		//message[1] = 1=down, 0=up
		//message[2] = velocity

		/////////////////////// KEYBOARD DOWN SIGNAL ////////////////////////////
		if(message[1] == 1){			
			
			if(Learning == true){
				devInfo.deviceName = string;
				devInfo.inputDetails = wxString(wxT("Key: ")) += KeyB::KeyToString(message[0]);
				LearnReply = (message[0] + 40000000);
			}
			
			for(trackNum=1; trackNum < (trackProc->tracks+1); ++trackNum){ //cycle through all the tracks
				if(trackProc->n[trackNum].midiType == 1){ //If it's a Trigger track, let's check it
					for(zoneNum=0; zoneNum<trackProc->n[trackNum].zones; ++zoneNum){ //Check all zones
						if((message[0] + 40000000) == trackProc->n[trackNum].inputCode[zoneNum]){ //check for the match
						
							if(!Retrigger(message[2])){	
							
								//Check for Multi Zone
								if(trackProc->n[trackNum].zones > 1){

									//Store the Velocity Information
									trackProc->n[trackNum].storedVelocity[zoneNum] = 64 + trackProc->n[trackNum].preVolume[zoneNum];
									if(trackProc->n[trackNum].storedVelocity[zoneNum] < 1){
										trackProc->n[trackNum].storedVelocity[zoneNum] = 1;
									}
									if(trackProc->n[trackNum].storedVelocity[zoneNum] > 127){
										trackProc->n[trackNum].storedVelocity[zoneNum] = 127;
									}

									//Does this complete the zones?
									bool go = true;
									for(int z=0; z<trackProc->n[trackNum].zones; ++z){ //Check all zones
										if(trackProc->n[trackNum].storedVelocity[z] == 0){go = false;}
									}
									if(go){
										MultiZoneOutput(trackNum);
									}
									else{
										if(trackProc->n[trackNum].firstPiezoHitTime == 0){
											trackProc->n[trackNum].firstPiezoHitTime = timer.getElapsedTimeInMilliSec();
										}
										trackProc->n[trackNum].waitForPiezo = true;
										//The Idle Loop is active for this track.
									}
								}

								else{  //if it's just a single zone, send it.
							
									//std::vector<unsigned char>output(3);
									output[0] = trackProc->n[trackNum].outputChannel[zoneNum] + 143;
									output[1] = trackProc->n[trackNum].outputNote[zoneNum];
									output[2] = 64;

									CCControlledVelocity(output);
									PreGain(output);
									Limiter(output);
									Dynamics(output);
									Volume(output);
									AntiMachineGun(output);
									Alteration(output);
									MidiCCControlledOutput(output);
							        VelocityControlledOutput(output);
									SequenceOutput();
									MouseOutput();
									Output(output);
									trackProc->n[trackNum].lastWasNoteOff[zoneNum] = false;
								}
							}
						}
					}
				}

				if(trackProc->n[trackNum].midiType == 2){ //If it's a MidiCC track, let's check it
					if((message[0] + 40000000) == trackProc->n[trackNum].inputCode[0]){ //check for the match
						
						zoneNum = 0;

						//std::vector<unsigned char>output(3);
						output[0] = trackProc->n[trackNum].outputChannel[zoneNum] + 175;
						output[1] = trackProc->n[trackNum].outputNote[zoneNum];

						if(!trackProc->n[trackNum].ccReverse){ output[2] = 127;	}
						else{ output[2] = 0; }
						
						PedalDownEvent(output);
						Compressor(output);
						Output(output);
					}
				}
			}
			//statusDialog->Input(wxString::Format(wxT("Keyboard Down: key-%d"), message[0]));
			//Send by event
			if(statusDialog->IsShown()){
				StatusDialogEvent event(wxEVT_COMMAND_STATUSDIALOG, trackProc->trackPanel->mainPanel->process->GetId()); //ID of where we come from?
				event.SetInOut(1); //set event flag to input
				event.SetValue(wxString::Format(wxT("Keyboard Down: key-%d"), message[0]));
				wxPostEvent(statusDialog->GetEventHandler(), event); //event handler of the gui object
			}
				return;
		}

		/////////////////////// KEYBOARD UP SIGNAL ////////////////////////////
		if(message[1] == 0){
			
			for(trackNum=1; trackNum < (trackProc->tracks+1); ++trackNum){ //cycle through all the tracks
				if(trackProc->n[trackNum].midiType == 1){ //If it's a Trigger track, let's check it
					for(zoneNum=0; zoneNum<trackProc->n[trackNum].zones; ++zoneNum){ //Check all zones
						if((message[0] + 40000000) == trackProc->n[trackNum].inputCode[zoneNum]){ //check for the match
							
							if(trackProc->n[trackNum].noteOff[zoneNum] && !trackProc->n[trackNum].lastWasNoteOff[zoneNum]){
								output[0] = trackProc->n[trackNum].outputChannel[zoneNum] + 127;
								output[1] = trackProc->n[trackNum].outputNote[zoneNum];
								output[2] = 0;
								Alteration(output);
								MidiCCControlledOutput(output);
							    VelocityControlledOutput(output);
								Output(output);
								trackProc->n[trackNum].lastWasNoteOff[zoneNum] = true;
							}
						}
					}
				}

				if(trackProc->n[trackNum].midiType == 2){ //If it's a MidiCC track, let's check it
					if((message[0] + 40000000) == trackProc->n[trackNum].inputCode[0]){ //check for the match
						
						zoneNum = 0;

						//std::vector<unsigned char>output(3);
						output[0] = trackProc->n[trackNum].outputChannel[zoneNum] + 175;
						output[1] = trackProc->n[trackNum].outputNote[zoneNum];

						if(!trackProc->n[trackNum].ccReverse){ output[2] = 0; }
						else{ output[2] = 127; }
						
						PedalDownEvent(output);
						Compressor(output);
						Output(output);
					}
				}
			}
			//statusDialog->Input(wxString::Format(wxT("Keyboard Up: key-%d"), message[0]));
			//Send by event
			if(statusDialog->IsShown()){
				StatusDialogEvent event(wxEVT_COMMAND_STATUSDIALOG, trackProc->trackPanel->mainPanel->process->GetId()); //ID of where we come from?
				event.SetInOut(1); //set event flag to input
				event.SetValue(wxString::Format(wxT("Keyboard Up: key-%d"), message[0]));
				wxPostEvent(statusDialog->GetEventHandler(), event); //event handler of the gui object
			}
				return;
		}
		wxMessageBox(wxT("Error: Recieved an Unknown Signal Type From Keyboard"),wxT(""), wxSTAY_ON_TOP);
	}



	///////////////////////////////// MOUSE ////////////////////////////////
	////////////////////////////////////////////////////////////////////////
	if(signalType == 5){
		//string     = "Device: Mouse"
		//message[0] = Wheel Direction           1=UP  0=DOWN

		/////////////////////// MOUSE WHEEL UP SIGNAL ////////////////////////////
		if(message[0] == 1){
			
			if(Learning == true && trackType == 2){
				devInfo.deviceName = string;
				devInfo.inputDetails = wxT("Wheel");
				LearnReply = (50000000);
			}

			for(trackNum=1; trackNum < (trackProc->tracks+1); ++trackNum){ //cycle through all the tracks
				if(trackProc->n[trackNum].midiType == 2){ //If it's a Trigger track, let's check it
				  	if((50000000) == trackProc->n[trackNum].inputCode[0]){ //check for the match
							
							zoneNum = 0;

							output[0] = trackProc->n[trackNum].outputChannel[zoneNum] + 175;
							output[1] = trackProc->n[trackNum].outputNote[zoneNum];

							if(!trackProc->n[trackNum].ccReverse){
								trackProc->n[trackNum].outputVelocity[zoneNum] = trackProc->n[trackNum].outputVelocity[zoneNum] + trackProc->mouseSensitivity;
							}
							else{
								trackProc->n[trackNum].outputVelocity[zoneNum] = trackProc->n[trackNum].outputVelocity[zoneNum] - trackProc->mouseSensitivity;
							}
							output[2] = trackProc->n[trackNum].outputVelocity[zoneNum];

							if(trackProc->n[trackNum].outputVelocity[zoneNum] < 0){output[2] = 0; trackProc->n[trackNum].outputVelocity[zoneNum] = 0;}
							if(trackProc->n[trackNum].outputVelocity[zoneNum] > 127){output[2] = 127; trackProc->n[trackNum].outputVelocity[zoneNum] = 127;}
							
							Compressor(output);
							trackProc->n[trackNum].outputVelocity[zoneNum] = output[2];

							if(output[2] != trackProc->n[trackNum].lastOutputVelocity[zoneNum]){
								trackProc->n[trackNum].lastOutputVelocity[zoneNum] = output[2]; 
								PedalDownEvent(output);
								Output(output);
							}
					}
				}
			}
			//statusDialog->Input(wxString::Format(wxT("Mouse Wheel Up")));
			//Send by event
			if(statusDialog->IsShown()){
				StatusDialogEvent event(wxEVT_COMMAND_STATUSDIALOG, trackProc->trackPanel->mainPanel->process->GetId()); //ID of where we come from?
				event.SetInOut(1); //set event flag to input
				event.SetValue(wxString::Format(wxT("Mouse Wheel Up")));
				wxPostEvent(statusDialog->GetEventHandler(), event); //event handler of the gui object
			}
				return;
		}

		/////////////////////// MOUSE WHEEL DOWN SIGNAL ////////////////////////////
		if(message[0] == 0){
			
			if(Learning == true && trackType == 2){
				devInfo.deviceName = string;
				LearnReply = (50000000);
			}

			for(trackNum=1; trackNum < (trackProc->tracks+1); ++trackNum){ //cycle through all the tracks
				if(trackProc->n[trackNum].midiType == 2){ //If it's a Trigger track, let's check it
				  	if((50000000) == trackProc->n[trackNum].inputCode[0]){ //check for the match
							
							output[0] = trackProc->n[trackNum].outputChannel[0] + 175;
							output[1] = trackProc->n[trackNum].outputNote[0];
		
							if(!trackProc->n[trackNum].ccReverse){
								trackProc->n[trackNum].outputVelocity[0] = trackProc->n[trackNum].outputVelocity[0] - trackProc->mouseSensitivity;
							}
							else{
								trackProc->n[trackNum].outputVelocity[0] = trackProc->n[trackNum].outputVelocity[0] + trackProc->mouseSensitivity;
							}
							output[2] = trackProc->n[trackNum].outputVelocity[0];
	
							if(trackProc->n[trackNum].outputVelocity[0] < 0){output[2] = 0; trackProc->n[trackNum].outputVelocity[0] = 0;}
							if(trackProc->n[trackNum].outputVelocity[0] > 127){output[2] = 127; trackProc->n[trackNum].outputVelocity[0] = 127;}
							
							Compressor(output);
							trackProc->n[trackNum].outputVelocity[0] = output[2];
							
							if(output[2] != trackProc->n[trackNum].lastOutputVelocity[0]){
								trackProc->n[trackNum].lastOutputVelocity[0] = output[2]; 
								PedalDownEvent(output);
								Output(output);
							}
					}
				}
			}
			//statusDialog->Input(wxString::Format(wxT("Mouse Wheel Down")));
			//Send by event
			if(statusDialog->IsShown()){
				StatusDialogEvent event(wxEVT_COMMAND_STATUSDIALOG, trackProc->trackPanel->mainPanel->process->GetId()); //ID of where we come from?
				event.SetInOut(1); //set event flag to input
				event.SetValue(wxString::Format(wxT("Mouse Wheel Down")));
				wxPostEvent(statusDialog->GetEventHandler(), event); //event handler of the gui object
			}
				return;
		}
		wxMessageBox(wxString::Format(wxT("Error: Recieved an Unknown Signal type from Mouse %d"), message[0]),wxT(""), wxSTAY_ON_TOP);
	}

	///////////////////////////////// COM PORT /////////////////////////////
	////////////////////////////////////////////////////////////////////////
	if(signalType == 6){

		// Serial Port Communication will require a serial port library
		// there is one for wxWidgets called wxCtb that currently supports windows and linux,
		// however there is talk of getting wxCTB to work on OSX :)

		/////////////////////// COM PORT SIGNAL ///////////////////////////
		if(Learning == true){
				devInfo.deviceName = string;
				LearnReply = (60000000);
		}
		//statusDialog->Input(wxString::Format(wxT("COM Port Signal")));
		//Send by event
		if(statusDialog->IsShown()){
			StatusDialogEvent event(wxEVT_COMMAND_STATUSDIALOG, trackProc->trackPanel->mainPanel->process->GetId()); //ID of where we come from?
			event.SetInOut(1); //set event flag to input
			event.SetValue(wxString::Format(wxT("COM Port Signal")));
			wxPostEvent(statusDialog->GetEventHandler(), event); //event handler of the gui object
		}
			return;
	}

	//If we got here, we have an unknown signal error
	wxMessageBox(wxT("Error in Process::Send, unknown signal type"),wxT(""), wxSTAY_ON_TOP);
}

/////////////////////////////////////////////////////////
bool Process::Retrigger(unsigned char &message)
{
	//////////////   DIRECT MIDI PROCESSING  (play mode) //////////////
	//IF the time between the hits is greater then the retrigger lvl...   all is good. 
	if(!detectingRetrigger && ((int)(timer.getElapsedTimeInMilliSec() - trackProc->n[trackNum].lastHitTime[zoneNum])) > (trackProc->n[trackNum].retrigger[zoneNum] + trackProc->retriggerSafty)){
		trackProc->n[trackNum].lastHitTime[zoneNum] = timer.getElapsedTimeInMilliSec();
		trackProc->n[trackNum].lastOutputVelocity[zoneNum] = message;
		trackProc->n[trackNum].lastRetriggerVelocity[zoneNum] = 0;
		return false;
	}
	
	//retrigger detected...
	if(!detectingRetrigger && ((int)(timer.getElapsedTimeInMilliSec() - trackProc->n[trackNum].lastHitTime[zoneNum])) <= (trackProc->n[trackNum].retrigger[zoneNum] + trackProc->retriggerSafty)){
		
		//FLAM DETECTION
		//If the Current Velocity > LastOutputVelocity..    then let it through, it could be a flam.
		if( message > (trackProc->n[trackNum].lastOutputVelocity[zoneNum] + trackProc->flamAdjustment) ){
			trackProc->n[trackNum].lastHitTime[zoneNum] = timer.getElapsedTimeInMilliSec();
			trackProc->n[trackNum].lastOutputVelocity[zoneNum] = message;
			trackProc->n[trackNum].lastRetriggerVelocity[zoneNum] = 0;
			return false; 
		}
		
		//ROLL DETECTION
		//If the Current Velocity > LastRetriggerVelocity..    then let it through, it could be a roll.
		if( trackProc->n[trackNum].lastRetriggerVelocity[zoneNum] && message > (trackProc->n[trackNum].lastRetriggerVelocity[zoneNum] + trackProc->rollAdjustment) ){
			trackProc->n[trackNum].lastHitTime[zoneNum] = timer.getElapsedTimeInMilliSec();
			trackProc->n[trackNum].lastOutputVelocity[zoneNum] = message;
			trackProc->n[trackNum].lastRetriggerVelocity[zoneNum] = 0;
			return false; 
		}

		trackProc->n[trackNum].lastRetriggerVelocity[zoneNum] = message;
		return true;
	}

	////////////////  FOR RETRIGGER WINDOW PREOCESSING (retrigger detection mode) //////////////////////
	//check for new retrigger if retrigger window is open	
	if(detectingRetrigger 
	   && ((int)(timer.getElapsedTimeInMilliSec() - trackProc->n[trackNum].lastHitTime[zoneNum])) > (trackProc->n[trackNum].retrigger[zoneNum])
	   && ((int)(timer.getElapsedTimeInMilliSec() - trackProc->n[trackNum].lastHitTime[zoneNum])) < trackProc->retriggerThreshold 
	   && trackNum == retriggerTrackNum && zoneNum == retriggerZoneNum){

	   trackProc->n[trackNum].retrigger[zoneNum] = ((int)(timer.getElapsedTimeInMilliSec() - trackProc->n[trackNum].lastHitTime[zoneNum]));
	   trackProc->n[trackNum].trigger->triggerDialog->retriggerBox->SetValue(wxString::Format(wxT("%d"),trackProc->n[trackNum].retrigger[zoneNum]));

	   return false;
	}

	//if the time is higher than the retrigger threshold..   no retrigger detected	
	if(detectingRetrigger
		&& ((int)(timer.getElapsedTimeInMilliSec() - trackProc->n[trackNum].lastHitTime[zoneNum])) >= trackProc->retriggerThreshold
		&& trackNum == retriggerTrackNum && zoneNum == retriggerZoneNum){

		trackProc->n[trackNum].lastHitTime[zoneNum] = timer.getElapsedTimeInMilliSec();

		return false;
	}
    
	//known retrigger detected
	if(detectingRetrigger
		&& ((int)(timer.getElapsedTimeInMilliSec() - trackProc->n[trackNum].lastHitTime[zoneNum])) <= (trackProc->n[trackNum].retrigger[zoneNum])
		&& trackNum == retriggerTrackNum && zoneNum == retriggerZoneNum){

		return true;
	}

	if(trackNum != retriggerTrackNum || zoneNum != retriggerZoneNum){
		return false;
	}


	//FIXME - This needs to goto an ErrorLog.txt
	//wxMessageBox(wxT("Error in Process::Retrigger()"));

	return true;
}

/////////////////////////////////////////////////////////
void Process::Crosstalk(std::vector<unsigned char>& message)
{
	//TODO
}

/////////////////////////////////////////////////////////
void Process::PreGain(std::vector<unsigned char>& message)
{
	int temp = message[2];
	temp = temp + trackProc->n[trackNum].preVolume[zoneNum];
	if(temp < 1){temp = 1;}
	if(temp > 127){temp = 127;}
	message[2] = temp;
	//OutputDebugString( wxString::Format( wxT("PreGain:%d  "), message[2]) );
}

///////////////////////////////////////////////////////////////////////
void Process::CCControlledVelocity(std::vector<unsigned char>& message)
{
	if(trackProc->n[trackNum].midiCCControlledVelocity[zoneNum]){
		for(int i=1; i<trackProc->tracks+1; ++i){
			if(trackProc->n[i].midiType == 2 && trackProc->n[trackNum].midiCCControlledVelocityNote[zoneNum] == trackProc->n[i].outputNote[0]){
				message[2] = trackProc->n[i].outputVelocity[0];
			}
		}
	}
}

///////////////////////////////////////////////////////////
void Process::Dynamics(std::vector<unsigned char>& message)
{
	//This is use on triger tracks, and the compressors are built in.
	//Refer to TriggerDialog.cpp to see how it gets is Dynamic values
	if(message[2] > 0){
		message[2] = trackProc->n[trackNum].dynamics[zoneNum][message[2]-1];
	}
	//OutputDebugString( wxString::Format( wxT("Dynamics:%d  "), message[2]) );
}

/////////////////////////////////////////////////////////
void Process::Volume(std::vector<unsigned char>& message)
{
	int temp = message[2];
	temp = int(temp + trackProc->n[trackNum].masterVolume - 127); //Then do the Master Volume	
	if(temp < 1){temp = 1;}
	if(temp > 127){temp = 127;}
	message[2] = temp;	
	//OutputDebugString( wxString::Format( wxT("Volume:%d  "), message[2]) );
}

/////////////////////////////////////////////////////////
void Process::Limiter(std::vector<unsigned char>& message)
{
	if(message[2] > trackProc->n[trackNum].highLimiter[zoneNum]){cancelOutput = true;}
	if(message[2] < trackProc->n[trackNum].lowLimiter[zoneNum]){cancelOutput = true;}
}

/////////////////////////////////////////////////////////
void Process::Compressor(std::vector<unsigned char>& message)
{
	//This is used for MidiCC tracks.
	//We don't have to use it on Trigger tracks, as the compressors are build into trigger Dynamics.
	if(message[2] > trackProc->n[trackNum].highCompressor[zoneNum]){message[2] = trackProc->n[trackNum].highCompressor[zoneNum];}
	if(message[2] < trackProc->n[trackNum].lowCompressor[zoneNum]){message[2] = trackProc->n[trackNum].lowCompressor[zoneNum];}
}

///////////////////////////////////////////////////////////////
void Process::AntiMachineGun(std::vector<unsigned char>& message)
{
	//The idea here is to disallow the same velocity to be played again over a certain period of time.
	//I.E. velocity's are only allowed to repeat every 500ms. If we get a repeat signal, we should look
	//for the closest velocity that is allowed, or has been 500ms since it's last hit. 
    
	//Also, this should come after Volume and respect the Compressor.

	//Example:
	//Signal recieved with velocity 64
	//Has it been over 500ms since 64 for this drum?

	int step = 1;
	bool up = true;
	while(timer.getElapsedTimeInMilliSec() - trackProc->n[trackNum].antiMachineGun[zoneNum][message[2]] < trackProc->n[trackNum].antiMachineGunTime[zoneNum])
	{
		if(up){message[2] = message[2] + step; step++; up = false;}
		else{message[2] = message[2] - step; step++; up = true;}
	}

	trackProc->n[trackNum].antiMachineGun[zoneNum][message[2]] = timer.getElapsedTimeInMilliSec();

	//Honor the limiters
	if(message[2] > trackProc->n[trackNum].highLimiter[zoneNum]){
		message[2] = trackProc->n[trackNum].highLimiter[zoneNum];
	}
	if(message[2] < trackProc->n[trackNum].lowLimiter[zoneNum]){
		message[2] = trackProc->n[trackNum].lowLimiter[zoneNum];
	}

	//Honor the Compressors
	//If we build these values into variables, we can make this process faster
	//since the calculations won't be done durring the live processing.
	if(message[2] > ((((trackProc->n[trackNum].highCompressor[zoneNum]-127)
					* trackProc->n[trackNum].highPercent[zoneNum]) / 100) + 127))
	{
		message[2] = ((((trackProc->n[trackNum].highCompressor[zoneNum]-127)
					* trackProc->n[trackNum].highPercent[zoneNum]) / 100) + 127);
	}
	if(message[2] < ((trackProc->n[trackNum].lowCompressor[zoneNum]
	                 * trackProc->n[trackNum].lowPercent[zoneNum]) / 100))
	{
		message[2] = trackProc->n[trackNum].lowCompressor[zoneNum];
	}

	//OutputDebugString( wxString::Format( wxT("AntiMachineGun:%d\n"), step-1) );
	//
	//If no, search for the closest velocity and check again?
	//When yes, make the timestamp for the velociity and pass it through. 

	//This should be an array variable for each zone as they would have their own samples.
	//We may do a trackProc->n[trackNum].antiMachineGun[zoneNum][127] to timestamp each velocity.
}

///////////////////////////////////////////////////////////////
void Process::Alteration(std::vector<unsigned char>& message)
{
	//Here we ultimatly decide which note to play.
	//We should ba able to put in as many alternating note as we want. But lets start with 100.
	
	//Alternating notes works by playing the notes in the list in a sequence.
	//I.E.  If we choose 5 alternating notes... 1,2,3,4 and 5,
	//The first drum hit will generate a 1, the second generates a 2 and so on.
	//After the last note is played, 5, it resets back to 1 and starts over.
	//Reset time will automatically reset
	//back to the beginning if the drum is not hit for the choosen period of time.
	//I.E. with reset time set to 10 seconds, we play the drum 3 times fast generating
	//1,2 and 3. If we wait 10 seconds, the next note generated will be 1 as the list started over.
	//However, if we only wait 9 seconds, the next note will generate as 4 and continue on.

	if(trackProc->n[trackNum].alternateOutput[zoneNum]){ //if the zone output is set to alternation . . .

		if(message[2] != 0){ //note on
			if(trackProc->n[trackNum].alternateRandom[zoneNum]){ //Randomize
				int temp = 0;
				//FIXME - using a loop to count the alternating notes is slow
				//Need a new variable that holds the count instead of looping here.
				while(trackProc->n[trackNum].alternateCheckBox[zoneNum][temp] != 0){
					++temp;
				}
				int num = rand() % temp + 1;
				message[1] = trackProc->n[trackNum].alternateNotes[zoneNum][num-1];
			}
			else{ //Not Randomize
				if( ((int)timer.getElapsedTimeInMilliSec() - trackProc->n[trackNum].lastAlternateHitTime[zoneNum]) > trackProc->n[trackNum].alternateReset[zoneNum]){
					trackProc->n[trackNum].alternateMarker[zoneNum] = 0;
					trackProc->n[trackNum].alternateOffMarker[zoneNum] = 0;
				}

				message[1] = trackProc->n[trackNum].alternateNotes[zoneNum][trackProc->n[trackNum].alternateMarker[zoneNum]];
				if(trackProc->n[trackNum].alternateCheckBox[zoneNum][trackProc->n[trackNum].alternateMarker[zoneNum]+1] != 0){
					trackProc->n[trackNum].alternateMarker[zoneNum]++;
				}
				else{
					trackProc->n[trackNum].alternateMarker[zoneNum] = 0;
				}

				trackProc->n[trackNum].lastAlternateHitTime[zoneNum] = timer.getElapsedTimeInMilliSec();
				
			}
			trackProc->n[trackNum].alternateLastOn[zoneNum] = message[1]; //remember this
		}

		else{ //note off
			message[1] = trackProc->n[trackNum].alternateLastOn[zoneNum];
		}
	}
}

/////////////////////////////////////////////////////////////////////////
void Process::MidiCCControlledOutput(std::vector<unsigned char>& message)
{
	//Ok. remember, if it's a note off signal, it needs to match up to the last 
	//not on signal, like in alternation.

	if(trackProc->n[trackNum].midiCCControlledOutput[zoneNum]){ //if the zone output is set to Midi CC Controlled . . .
		if(message[2] != 0){ //note on

			bool match = false;
			for(int i=1; i < (trackProc->tracks+1); ++i){ //cycle through all the tracks
				if((trackProc->n[i].midiType == 2) && (trackProc->n[i].outputNote[0] == trackProc->n[trackNum].midiCCControlledInputNote[zoneNum])){
					
					match = true;
					unsigned char temp = trackProc->n[i].lastOutputVelocity[0];
					message[1] = trackProc->n[trackNum].midiCCControlledNotes[zoneNum][0];
					for (int n=0; n<10; ++n){
						if(trackProc->n[trackNum].midiCCControlledCheckBox[zoneNum][n+1] &&
							temp >= trackProc->n[trackNum].midiCCControlledSliders[zoneNum][n]){
							message[1] = trackProc->n[trackNum].midiCCControlledNotes[zoneNum][n+1];
						}
					}

					trackProc->n[trackNum].midiCCControlledLastOn[zoneNum] = message[1]; //remember this
				}
			}

			if(!match){
				wxString temp = wxString::Format(wxT("Please create a MidiCC track to controll this output with MidiCC Note %d"),trackProc->n[trackNum].midiCCControlledInputNote[zoneNum]);
				wxMessageBox(temp);
			}
		}
		else{ //note off
			message[1] = trackProc->n[trackNum].midiCCControlledLastOn[zoneNum];
		}
	}
}

///////////////////////////////////////////////////////////////////////////
void Process::VelocityControlledOutput(std::vector<unsigned char>& message)
{
	//Ok. remember, if it's a note off signal, it needs to match up to the last 
	//note on signal, like in alternation.

	if(trackProc->n[trackNum].velocityControlledOutput[zoneNum]){ //if the zone output is set to Velocity Controlled . . .
		if(message[2] != 0){ //note on

			    unsigned char temp = message[2];
				message[1] = trackProc->n[trackNum].velocityControlledNotes[zoneNum][0];
				for (int n=0; n<10; ++n){
					if(trackProc->n[trackNum].velocityControlledCheckBox[zoneNum][n+1] &&
						temp >= trackProc->n[trackNum].velocityControlledSliders[zoneNum][n]){
						message[1] = trackProc->n[trackNum].velocityControlledNotes[zoneNum][n+1];
					}
				}

			trackProc->n[trackNum].velocityControlledLastOn[zoneNum] = message[1];  //remember this
		}
		else{ //note off
			message[1] = trackProc->n[trackNum].velocityControlledLastOn[zoneNum];
		}
	}
}

/////////////////////////////////////////////////////////////////////////
void Process::ZoneControlledOutput(std::vector<unsigned char>& message, int position)
{
	//Ok. remember, if it's a note off signal, it needs to match up to the last 
	//not on signal, like in alternation.

	if(trackProc->n[trackNum].zoneControlledOutput){ //if the zone output is set to Zone Controlled . . .
		if(message[2] != 0){ //note on

					message[1] = trackProc->n[trackNum].zoneControlledNotes[0];
					for (int n=0; n<10; ++n){
						if(trackProc->n[trackNum].zoneControlledCheckBox[n+1] &&
							position >= trackProc->n[trackNum].zoneControlledSliders[n]){
							message[1] = trackProc->n[trackNum].zoneControlledNotes[n+1];
						}
					}

					trackProc->n[trackNum].zoneControlledLastOn = message[1]; //remember this
		}
		else{ //note off
			message[1] = trackProc->n[trackNum].zoneControlledLastOn;
		}
	}
}

/////////////////////////////////////////////////////////////////
void Process::SequenceOutput()
{
	if(trackProc->n[trackNum].sequenceOutput[zoneNum] && cancelOutput == false){
		if(trackProc->enableMeters){
			sequencePlayer->PlaySequence(trackProc->midi, statusDialog, trackProc->n[trackNum].sequenceFile[zoneNum], trackProc->n[trackNum].trigger->meter, trackProc->n[trackNum].sequenceOverlap[zoneNum]);
		}
		else{
			sequencePlayer->PlaySequence(trackProc->midi, statusDialog, trackProc->n[trackNum].sequenceFile[zoneNum],  NULL, trackProc->n[trackNum].sequenceOverlap[zoneNum]);
		}
		cancelOutput = true;
	}
}

///////////////////////////
void Process::MouseOutput()
{
	if(trackProc->n[trackNum].mouseOutput[zoneNum] && cancelOutput == false){
			//move mouse
			int x = trackProc->n[trackNum].mouseX[zoneNum];
			int y = trackProc->n[trackNum].mouseY[zoneNum];
			double fScreenWidth    = ::GetSystemMetrics( SM_CXSCREEN )-1; 
			double fScreenHeight  = ::GetSystemMetrics( SM_CYSCREEN )-1; 
			double fx = x*(65535.0f/fScreenWidth);
			double fy = y*(65535.0f/fScreenHeight);
			INPUT  Input={0};
			Input.type      = INPUT_MOUSE;
			Input.mi.dwFlags  = MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE;
			Input.mi.dx = fx;
			Input.mi.dy = fy;
			::SendInput(1,&Input,sizeof(INPUT));

			// left mouse down 
			Input.type      = INPUT_MOUSE;
			Input.mi.dwFlags  = MOUSEEVENTF_LEFTDOWN;
			::SendInput(1,&Input,sizeof(INPUT));

			// left mouse up
			::ZeroMemory(&Input,sizeof(INPUT));
			Input.type      = INPUT_MOUSE;
			Input.mi.dwFlags  = MOUSEEVENTF_LEFTUP;
			::SendInput(1,&Input,sizeof(INPUT));
			
		}
}

/////////////////////////////////////////////////////////////////
void Process::PedalDownEvent(std::vector<unsigned char>& message)
{
	if(trackProc->n[trackNum].pedalDownEvent){
		
		//are we at or past the pedal down threshold?
		if(message[2] <= trackProc->n[trackNum].pedalDownThreshold && trackProc->n[trackNum].pedalDownFlag){
			
			//Here we must determine the speed
			double Speed = timer.getElapsedTimeInMilliSec() - trackProc->n[trackNum].highTime;
			
			
			if(Speed > trackProc->n[trackNum].pedalSpeedIntensity){Speed = trackProc->n[trackNum].pedalSpeedIntensity;} //keep it to 0 - 100 percent range
			int percent = (Speed * 100) / trackProc->n[trackNum].pedalSpeedIntensity; //thats the percent to play of 127
			int velocity = 127 -(((percent * 126) / 100) + (127 - trackProc->n[trackNum].pedalVolume));

			if(velocity < 1){velocity = 1;}
			if(velocity > 127){velocity = 127;}
			
			std::vector<unsigned char>pedalOutput(3);
			pedalOutput[0] = trackProc->n[trackNum].outputChannel[zoneNum] + 143;
			pedalOutput[1] = trackProc->n[trackNum].pedalNote;
			pedalOutput[2] = velocity;
			Output(pedalOutput);

			trackProc->n[trackNum].storedHighVelocity = 0;
			trackProc->n[trackNum].pedalDownFlag = false;
		}

		if(message[2] > trackProc->n[trackNum].pedalDownThreshold){
			trackProc->n[trackNum].pedalDownFlag = true;
		}

		//Are we at a high?
		if(message[2] > trackProc->n[trackNum].storedHighVelocity){
			trackProc->n[trackNum].storedHighVelocity = message[2];
		}


		if(message[2] < trackProc->n[trackNum].storedHighVelocity){
			trackProc->n[trackNum].highTime = (int)timer.getElapsedTimeInMilliSec();
		}
	}
}


/////////////////////////////////////////////////////////
void Process::MultiZoneOutput(int track)
{
	//Here we take velocity information stored for multiple zones and process it down
	//to one output signal.
	//We may get signals from the Idle Loop that are incomplete (zones velocities missing).
	//It's still our job to create the apropriate output signal weather all zone 
	//velocities are stored or not.
	trackNum = track;

	//This is where we will check the MultiZone wait time if we are learning it.
	if(detectingWaitTime && waitTimeTrackNum == trackNum && timer.getElapsedTimeInMilliSec() - trackProc->n[trackNum].firstPiezoHitTime > trackProc->n[trackNum].multiZoneWaitTime
	   && timer.getElapsedTimeInMilliSec() - trackProc->n[trackNum].firstPiezoHitTime < 100){
		trackProc->n[trackNum].multiZoneWaitTime = timer.getElapsedTimeInMilliSec() - trackProc->n[trackNum].firstPiezoHitTime + 1;
		trackProc->n[trackNum].trigger->triggerDialog->multiZoneWaitTimeBox->SetValue(wxString::Format(wxT("%d"),trackProc->n[trackNum].multiZoneWaitTime));
	}

	trackProc->n[trackNum].firstPiezoHitTime = 0;
	trackProc->n[trackNum].waitForPiezo = false;

	///////////////  Priority Control ////////////////////////////
	int PriorityVelocity[3];
	for(int i=0; i<3; ++i){
		PriorityVelocity[i] = trackProc->n[trackNum].storedVelocity[i] + trackProc->n[trackNum].priority[i];
	}

	//// Find the loudest piezo acording to priority ///////////////
	int loudest = 0;
	for(int p=0; p<trackProc->n[trackNum].zones; ++p){ //Check all zones
		if(PriorityVelocity[p] > loudest){
			loudest = PriorityVelocity[p];
			zoneNum = p;
		}
	}

	////////////////  Position Sensing   ///////////////////////

	//// Position Gravity ////////////////////////////
	int PositionGravity[3];
	for(int i=0; i<3; ++i){
		PositionGravity[i] = trackProc->n[trackNum].storedVelocity[i] + trackProc->n[trackNum].gravity[i];
	}
	
	int Precent = 0;
	int Position1 = 0;
	int Position2 = 0;

	// Algorythm 1 - Last piezo is rim
	if(trackProc->n[trackNum].hasRim){
		if(trackProc->n[trackNum].zones == 2){
			if(PositionGravity[0] == PositionGravity[1]){
				Position1 = 127;
			}
			if(PositionGravity[0] > PositionGravity[1]){
				Precent = (PositionGravity[1] * 100) / PositionGravity[0];
				Position1 = ((127 * Precent) / 100);
			}
			if(PositionGravity[0] < PositionGravity[1]){
				Position1 = 127;
				//we may want to cancel position output here.
			}
		}
		if(trackProc->n[trackNum].zones == 3){
			//Get first position
			if(PositionGravity[0] == PositionGravity[1]){
				Position1 = 64;
			}
			if(PositionGravity[0] > PositionGravity[1]){
				Precent = (PositionGravity[1] * 100) / PositionGravity[0];
				Position1 = ((127 * Precent) / 100) / 2;
			}
			if(PositionGravity[0] < PositionGravity[1]){
				Precent = (PositionGravity[0] * 100) / PositionGravity[1];
				Position1 = 127 - ((127 * Precent) / 100) / 2;
			}
			//Get Second Position
			if(PositionGravity[1] == PositionGravity[2]){
				Position2 = 127;
			}
			if(PositionGravity[1] > PositionGravity[2]){
				Precent = (PositionGravity[2] * 100) / PositionGravity[1];
				Position2 = ((127 * Precent) / 100);
			}
			if(PositionGravity[1] < PositionGravity[2]){
				Position2 = 127;
				//we may want to cancel position output here.
			}

		}
	}
	// Algorythm 2 - No rim
	else{
		if(trackProc->n[trackNum].zones == 2){
			if(PositionGravity[0] == PositionGravity[1]){
				Position1 = 64;
			}
			if(PositionGravity[0] > PositionGravity[1]){
				Precent = (PositionGravity[1] * 100) / PositionGravity[0];
				Position1 = ((127 * Precent) / 100) / 2;
			}
			if(PositionGravity[0] < PositionGravity[1]){
				Precent = (PositionGravity[0] * 100) / PositionGravity[1];
				Position1 = 127 - ((127 * Precent) / 100) / 2;
			}
		}
		if(trackProc->n[trackNum].zones == 3){
			// Get the first position
			if(PositionGravity[0] == PositionGravity[1]){
				Position1 = 64;
			}
			if(PositionGravity[0] > PositionGravity[1]){
				Precent = (PositionGravity[1] * 100) / PositionGravity[0];
				Position1 = ((127 * Precent) / 100) / 2;
			}
			if(PositionGravity[0] < PositionGravity[1]){
				Precent = (PositionGravity[0] * 100) / PositionGravity[1];
				Position1 = 127 - ((127 * Precent) / 100) / 2;
			}
			// Get the second position
			if(PositionGravity[1] == PositionGravity[2]){
				Position2 = 64;
			}
			if(PositionGravity[1] > PositionGravity[2]){
				Precent = (PositionGravity[2] * 100) / PositionGravity[1];
				Position2 = ((127 * Precent) / 100) / 2;
			}
			if(PositionGravity[1] < PositionGravity[2]){
				Precent = (PositionGravity[1] * 100) / PositionGravity[2];
				Position2 = 127 - ((127 * Precent) / 100) / 2;
			}
		}
	}

	if(Position1 < 0){Position1 = 0;}
	if(Position1 > 127){Position1 = 127;}
	if(Position2 < 0){Position2 = 0;}
	if(Position2 > 127){Position2 = 127;}

	//Get the average of all positions
	int finalPosition = 0;
	if(trackProc->n[trackNum].zones == 3){
		finalPosition = (Position1 + Position2) / 2;
	}
	else{
		finalPosition = Position1;
	}
	
	//OutputDebugString(wxString::Format("Final = %d\n", finalPosition));

	//////// OUTPUT /////////////////////////////////////////////////////////

	//std::vector<unsigned char>output(3);
	output[0] = trackProc->n[trackNum].outputChannel[zoneNum] + 143;
	output[1] = trackProc->n[trackNum].outputNote[zoneNum];
	output[2] = trackProc->n[trackNum].storedVelocity[zoneNum];

	VelocityBalance(finalPosition);
	PositionSensing(finalPosition);
	CCControlledVelocity(output);
	Dynamics(output);
	Volume(output);
	Limiter(output);
	AntiMachineGun(output);
	Alteration(output);
	MidiCCControlledOutput(output);
	VelocityControlledOutput(output);
	ZoneControlledOutput(output, finalPosition);
	Output(output);

	//be sure to reset the stored data
	for(int p=0; p<trackProc->n[trackNum].zones; ++p){ //Check all zones
		trackProc->n[trackNum].storedVelocity[p] = 0;
	}

}

///////////////////////////////////////////
void Process::VelocityBalance(int position)
{
	//This is where we take the Velocity, Position and the velocityBalance slider
	//and determin what to change to velocity to.  This is intended to remove the
	//"Hot Spot" in multi-zone drum triggers

	//Are variables are . . .
	//trackProc->n[trackNum].velocityBalance;
	//trackProc->n[trackNum].storedVelocity[zoneNum];
	//position;

	//Lets record the Velocity and Position to the drums VelToPosAvg catalog.
	//We will use varToPosAvgCycle to cycle in the new hit value position.
	//Since we only want to keep an average, we can just a history of 1000 velocities per position
	
	trackProc->n[trackNum].velToPosAvg[trackProc->n[trackNum].storedVelocity[zoneNum]][velToPosAvgCycle] = position;
	trackProc->n[trackNum].posToVelAvg[position][posToVelAvgCycle] = trackProc->n[trackNum].storedVelocity[zoneNum];
	if(velToPosAvgCycle == 999){
		velToPosAvgCycle = 0;
	}
	else{
		velToPosAvgCycle++;
	}

	if(posToVelAvgCycle == 999){
		posToVelAvgCycle = 0;
	}
	else{
		posToVelAvgCycle++;
	}
}

///////////////////////////////////////////
void Process::PositionSensing(int position)
{
	if(trackProc->n[trackNum].enableCC){
		std::vector<unsigned char>message(3);
		message[0] = trackProc->n[trackNum].ccOutputChannel + 175;
		message[1] = trackProc->n[trackNum].ccOutputNote;
		message[2] = position;

		//Obey the limiters
		if(message[2] < trackProc->n[trackNum].ccOutputLowCompressor){
			message[2] = trackProc->n[trackNum].ccOutputLowCompressor;
		}
		if(message[2] > trackProc->n[trackNum].ccOutputHighCompressor){
			message[2] = trackProc->n[trackNum].ccOutputHighCompressor;
		}

		//OUTPUT
		trackProc->midi->SendMessage(&message);

		//send output status message
		wxString outputStatus;
		outputStatus = wxString::Format(wxT("Midi CC: %d  "), (message[0] - 175));
		outputStatus += wxString::Format(wxT("%d  %d"), message[1], message[2]);
		
		//Send by event
		if(statusDialog->IsShown()){
			StatusDialogEvent event(wxEVT_COMMAND_STATUSDIALOG, trackProc->trackPanel->mainPanel->process->GetId()); //ID of where we come from?
			event.SetInOut(2); //Set event flag to output
			event.SetValue(outputStatus);
			wxPostEvent(statusDialog->GetEventHandler(), event); //event handler of the gui object
		}
	}
}

///////////////////////////////////////////////////////////
void Process::GetTempo(std::vector<unsigned char>& message)
{
	//Get the average tempo

	if(message[0] < 143 && message[0] > 160 || message[2] == 0){
		return;
	}

	if(timer.getElapsedTimeInMilliSec() - tempo[4] < 500){
		return;
	}

	for(int i=0; i<5; i++){
		tempo[i] = tempo[i+1];
	}
	tempo[5] = (int)timer.getElapsedTimeInMilliSec();
	

	int average = ((tempo[5] - tempo[4]) +
		(tempo[4] - tempo[3]) +
		(tempo[3] - tempo[2]) +
		(tempo[2] - tempo[1]) +
		(tempo[1] - tempo[0])) / 5;

	int bpm = 60000 / average;

	menuPanel->tempo->SetLabel(wxString::Format("%d BPM", bpm));
}
/////////////////////////////////////////////////////////
void Process::Output(std::vector<unsigned char>& message)
{
	if(cancelOutput){cancelOutput = false; return;}
	
	//Average the tempo
	GetTempo(message);
	//Play to MIDI out
	trackProc->midi->SendMessage(&message);

#ifdef VST
	VstMidiEvent *v = new VstMidiEvent();
	v->type = 1;
	v->midiData[0] = message[0];
	v->midiData[1] = message[1];
	v->midiData[2] = message[2];
	v->deltaFrames = 0;

	VstEvents *ve = new VstEvents();
	ve->numEvents = 1;
	ve->events[0] = (VstEvent *)v;
	vst->sendVstEventsToHost(ve);
	delete v;
	delete ve;
#endif //VST

	//Play sample
	/*
	if(!fromIdleLoop && trackProc->n[trackNum].sampleFolder[zoneNum] != wxT("") && message[2] > 0){			
		trackProc->trackPanel->mainPanel->samples->PlaySample(trackProc->n[trackNum].sampleFolder[zoneNum], message[2]);
	}
	*/

	//Record to sequencer
	if(trackProc->trackPanel->mainPanel->sequencerDialog != NULL){
		if(trackProc->trackPanel->mainPanel->sequencerDialog->record){
			trackProc->trackPanel->mainPanel->sequencerDialog->RecieveMessage(message);
		}
	}

	//Play to Player
	if(trackProc->trackPanel->mainPanel->etmPlayerDialog != NULL){
		if( trackProc->trackPanel->mainPanel->etmFile->playing){
			message[1] = trackProc->n[trackNum].drumType;
			trackProc->trackPanel->mainPanel->etmPlayerDialog->RecieveMessage(message);
		}
		//Record to EtmEditor
		if(trackProc->trackPanel->mainPanel->etmEditorDialog2 != NULL){
			if(trackProc->trackPanel->mainPanel->etmFile->recording){
				message[1] = trackProc->n[trackNum].drumType;
				trackProc->trackPanel->mainPanel->etmEditorDialog2->RecieveMessage(message);
			}
		}
	}

	double endLatency = timer.getElapsedTimeInMilliSec() - latency;
	int percent = (message[2] * 100) / 127;

	//Visual Track Meters
		if(trackProc->n[trackNum].midiType == 1 && message[2] > 0 && message[2] < 128){ //Trigger Track
			if(trackProc->enableMeters){
				GMeterEvent event(wxEVT_COMMAND_GMETER, trackProc->trackPanel->mainPanel->process->GetId()); //ID of where we come from?
				event.SetValue(percent);
				wxPostEvent(trackProc->n[trackNum].trigger->meter->GetEventHandler(), event); //event handle of the gui object
			}
		}
		if(trackProc->n[trackNum].midiType == 2){ //MidiCC Track
			if(trackProc->enableMeters){
				GMeterEvent event(wxEVT_COMMAND_GMETER, trackProc->trackPanel->mainPanel->process->GetId()); //ID of where we come from?
				event.SetValue(percent);
				wxPostEvent(trackProc->n[trackNum].midicc->meter->GetEventHandler(), event); //event handle of the gui object
			}
		}

	//send output status message
	if(statusDialog->IsShown()){
		wxString outputStatus;
		if(message[0] > 143 && message[0] < 160 && message[2] > 0){ outputStatus = wxString::Format(wxT("Midi NoteON:  %d  "), (message[0] - 143)); }  
		if(message[0] > 143 && message[0] < 160 && message[2] == 0){ outputStatus = wxString::Format(wxT("Midi NoteOFF:  %d  "), (message[0] - 143)); } 
		if(message[0] > 127 && message[0] < 144){ outputStatus = wxString::Format(wxT("Midi NoteOFF: %d  "), (message[0] - 127)); } 
		if(message[0] > 159 && message[0] < 176){ outputStatus = wxString::Format(wxT("Midi Aftertouch: ch-%d  "), (message[0]-159)); } 
		if(message[0] > 175 && message[0] < 192){ outputStatus = wxString::Format(wxT("Midi CC: %d  "), (message[0] - 175)); } 
		if(message[0] > 191 && message[0] < 208){ outputStatus = wxString::Format(wxT("Midi PC: %d  "), (message[0] - 191)); } 
		outputStatus += wxString::Format(wxT("%d  %d"), message[1], message[2]);
		outputStatus += wxString::Format(wxT("       Latency: %fms"), endLatency);

		//Send by event
		StatusDialogEvent event(wxEVT_COMMAND_STATUSDIALOG, trackProc->trackPanel->mainPanel->process->GetId()); //ID of where we come from?
		event.SetInOut(2); //Set event flag to output
		event.SetValue(outputStatus);
		wxPostEvent(statusDialog->GetEventHandler(), event); //event handle of the gui object
	}
}




///////// Learn Event ////////////////
DEFINE_EVENT_TYPE(wxEVT_COMMAND_LEARN) 
IMPLEMENT_DYNAMIC_CLASS(LearnEvent, wxCommandEvent) 

/////////////////////////////////////////////////////////////////////////////////////////
LearnEvent::LearnEvent(wxEventType commandType, int id) : wxCommandEvent(commandType, id) 
{ 
} 

//////// Learn Thread ////////////////////////////////////////////////
LearnThread::LearnThread(wxWindow *parent, int trackType) : wxThread()
{
	par = parent;
	Process::trackType = trackType;
	Create();
	Run();
}

//////////////////////////
void *LearnThread::Entry()
{
	Process::Learning = true;
	Process::LearnReply = 0;
	Process::devInfo.inputDetails = wxT("");
	Process::devInfo.deviceName = wxT("");
	long currentTime = ::wxGetLocalTime();

	while( (::wxGetLocalTime() - currentTime < 5) && (Process::LearnReply == 0) 
		   || Process::confirmWait && (Process::LearnReply == 0) ){ //give the LearnReply variable time to fill
	}

	// Create and event 
	if(Process::Learning == true){
		LearnEvent event(wxEVT_COMMAND_LEARN, GetId()); 
		wxPostEvent(par->GetEventHandler(), event);
	}

	Process::Learning = false;
	return 0;
}



////////////////////////////
GTimer::GTimer() : wxTimer()
{
	sequencePlayer = NULL;
	trackProc = NULL;
	Start(1,false);
}

/////////////////////
void GTimer::Notify()
{
	if(sequencePlayer){
		sequencePlayer->Notify();
	}
	if(trackProc){
		for(int i=1; i<(trackProc->tracks+1); ++i){
			if(trackProc->n[i].trigger){
				trackProc->n[i].trigger->meter->Notify();
			}
		}
	}
	if(client && (GetInterval() > 60000)){  //only every minute
		client->Notify();
		Start(1,false); //restart the timer
	}

}

//////////////////////////////////////////////////
void GTimer::LinkTrackProc(TrackProc *tp)
{
	trackProc = tp;
}

//////////////////////////////////////////////////
void GTimer::LinkSequencePlayer(SequencePlayer *sp)
{
	sequencePlayer = sp;
}

//////////////////////////////////////////////////
void GTimer::LinkNetwork(Client *net)
{
	client = net;
}