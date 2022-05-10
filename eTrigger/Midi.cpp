//// Midi.cpp ///////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "Midi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

bool Midi::active = false;

/////////////////////////////////////////
Midi::Midi(TrackProc *ref)
{
	trackProc = ref;
}

/////////////////////
Midi::~Midi()
{
	StopCallback();

	for(unsigned int i=0; i<midiin.size(); ++i){
		midiin[i]->rtIn.closePort();
		delete midiin[i];
	}

	for(unsigned int i=0; i<midiout.size(); ++i){
		
#ifdef MAC
		if(i<(midiout.size() -1)){
			delete midiout[i];
			continue;
		}
		//else{ midiout[i]->closePort(); }
#endif //MAC#
#ifdef WIN32
		midiout[i]->closePort();
#endif //WIN32
		
		delete midiout[i];
	}
}

////////////////////////////////////
void Midi::SetMidiEngine(int engine)
{
	//TODO
}

//////////////////////////////////////
wxArrayString Midi::GetInDevices()
{
	active = false;
	wxArrayString InDev;

	RtMidiIn *temp = 0;
	try{
		temp = new RtMidiIn();
	}
	catch (RtError &error) {
		std::string temp2 = error.getMessage();
		wxMessageBox(ConvTowxString(temp2));
	}

	unsigned int nPorts = temp->getPortCount();

	std::string portName;
	for ( unsigned int i=0; i<nPorts; ++i ) {
		try {
			portName = temp->getPortName(i);
		}
		catch (RtError &error) {
			error.printMessage();
		}
		if(portName != "eTrigger"){
			InDev.Add(ConvTowxString(portName));
		}
	}

	delete temp;
	active = true;
	return InDev;
}

///////////////////////////////////////
wxArrayString Midi::GetOutDevices()
{
	wxArrayString OutDev;
	//RtMidiOut *temp = new RtMidiOut;

	RtMidiOut *temp = 0;
	try{
		temp = new RtMidiOut();
	}
	catch (RtError &error) {
		std::string temp2 = error.getMessage();
		wxMessageBox(ConvTowxString(temp2));
	}

	unsigned int nPorts = temp->getPortCount();

	std::string portName;
	for ( unsigned int i=0; i<nPorts; ++i ) {
		try {
			portName = temp->getPortName(i);
		}
		catch (RtError &error) {
			error.printMessage();
		}
		OutDev.Add(ConvTowxString(portName));
	}
	
	delete temp;
	return OutDev;	
}

////////////////////////////////////////////////
void Midi::SetInDevice(wxString in, int num)
{
	unsigned int nPorts = midiin[num]->rtIn.getPortCount();
	std::string portName;

	for ( unsigned int i=0; i<nPorts; ++i ) {

		portName = midiin[num]->rtIn.getPortName(i);
		if(in == ConvTowxString(portName) ){
			midiin[num]->rtIn.openPort( i );
            midiin[num]->rtIn.ignoreTypes( false, false, false );
			midiin[num]->deviceName = in;
			midiin[num]->deviceNumber = num;
			selectedIn.Add(in, 1);
			return;
		}
	}
}

//////////////////////////////////////////////////
void Midi::SetOutDevice(wxString out, int num)
{
	if(out == wxT("eTrigger")){
	   midiout[num]->openVirtualPort( std::string( "eTrigger" ) );
	   return;
	}
	   
	unsigned int nPorts = midiout[num]->getPortCount();
	std::string portName;

	unsigned int i;
	for ( i=0; i<nPorts; ++i ) {

		portName = midiout[num]->getPortName(i);
		if(out == ConvTowxString(portName) ){
			midiout[num]->openPort( i );
			selectedOut.Add(out, 1);
			return;
		}
	}
}

/////////////////////////////////////////////
void Midi::SetInDevices(wxArrayString in)
{
	selectedIn.Clear();

	for(unsigned int b=0; b<midiin.size(); ++b){
		midiin[b]->rtIn.closePort();
		delete midiin[b];
	}

	midiin.clear();
	midiin.resize(in.GetCount()); 

	for(unsigned int i=0; i<in.GetCount(); ++i)
	{
		midiin[i] = new MIDIIN();
		SetInDevice(in.Item(i), i);
	}
}

///////////////////////////////////////////////
void Midi::SetOutDevices(wxArrayString out)
{
	selectedOut.Clear();

	for(unsigned int b=0; b<midiout.size(); ++b){
		
#ifdef MAC
		if(b<(midiout.size() -1)){
		   delete midiout[b];
		   continue;
		}
		//else{ midiout[b]->closePort(); }
#endif //MAC
#ifdef WIN32
	       midiout[b]->closePort();
#endif //WIN32
		   delete midiout[b];
	}

	midiout.clear();
	midiout.resize(out.GetCount()); 

	unsigned int i;
	for(i=0; i<out.GetCount(); ++i)
	{
		midiout[i] = new RtMidiOut();
		SetOutDevice(out.Item(i), i);
	}
#ifndef WIN32
	midiout.push_back(new RtMidiOut());
	SetOutDevice(wxT("eTrigger"), i);
#endif //!WIN32
}

/////////////////////////////////////////////////////////////////
void Midi::SendMessage( std::vector<unsigned char> *message )
{
	if(midiout.size() > 0){  
		for(unsigned int i=0; i < midiout.size(); ++i){ //FIXME allow MAC to send on virtual output
			midiout[i]->sendMessage(message);
		}
	}	
}

/////////////////////////////
void Midi::StopCallback()
{
	active = false;
	for(unsigned int i=0; i<midiin.size(); ++i){
		midiin[i]->rtIn.cancelCallback();
	}
}

//////////////////////////
void Midi::StartCallback()
{
	active = true;
	//Start all of the devices
	for(unsigned int i=0; i<midiin.size(); ++i){

		//I would like to pass the Port Number to userDate instead of NULL.
		midiin[i]->rtIn.setCallback( &Midi::callback, (void*)midiin[i]);//start the callback event

		std::vector<unsigned char> message;
	    midiin[i]->rtIn.getMessage(&message); //clear the buffer
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////
void Midi::callback( double deltatime, std::vector< unsigned char > *message, void *userData )
{
	if(active){
		MIDIIN *midiIn = (MIDIIN*)userData;

		wxString deviceName = midiIn->deviceName; 
		int deviceNum = midiIn->deviceNumber;

		Process::Send(1,  deviceName, deviceNum, *message);
	}
}
