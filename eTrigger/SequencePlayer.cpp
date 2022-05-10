//// SequencePlayer.cpp /////////////////////////////////////////////////////////////////
//
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "SequencePlayer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

Sequence::Sequence(Midi *parent, StatusDialog *sd, wxString fileName, GMeter *meter, bool overlap){

	midi = parent;
	statusDialog = sd;
	filename = fileName;
	gmeter = meter;
	sequenceOverlap = overlap;

	if(!wxFile::Exists(filename)){
		wxMessageBox(wxString::Format(wxT("Sequencer file %s does not exist."), filename));
		return;
	}
	wxFile* file = new wxFile(filename, wxFile::read);
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

	i=0;
}

/////////////////////////////////
Sequence::~Sequence()
{

}

///////////////////////////
void Sequence::Kill()
{
	delete this;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
SequencePlayer::SequencePlayer()
{
	for(int i=0; i<100; i++){
		play[i] = false;
	}
	//midi = parent;
	//statusDialog = sd;
	/*
	gmeter = meter;
	fileName = filename;
	sequenceOverlap = overlap;
	if(!wxFile::Exists(filename)){
		wxMessageBox(wxString::Format(wxT("Sequencer file %s does not exist."), filename));
		return;
	}
	wxFile* file = new wxFile(filename, wxFile::read);
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

	i=0;
	//playbackTimer.AddSequence(*this);  //add meter to the timer event
	*/
}

/////////////////////////////////
SequencePlayer::~SequencePlayer()
{

}

///////////////////////////
/*
void SequencePlayer::Kill()
{
	delete this;
}
*/

//////////////////////////////////
void SequencePlayer::PlaySequence(Midi *parent, StatusDialog *sd, wxString filename, GMeter *meter, bool overlap)
{
	Sequence *temp = new Sequence(parent, sd, filename, meter, overlap);
	for(int i=0; i<100; i++){
		if(play[i] == true && !temp->sequenceOverlap && (sequence[i]->filename == temp->filename)){
			play[i] = false;
			sequence[i]->sw.Pause(); //stop the timer
			sequence[i]->Kill();
		}
		if(play[i] == false){
			sequence[i] = temp;
			sequence[i]->sw.Start(0);
			play[i] = true;
			return;
		}
	}
}

////////////////////////////
void SequencePlayer::Notify()
{
	for(int s=0; s<100; s++){
		if(play[s]){
		
     		if(sequence[s]->i < sequence[s]->midiData.size()){
	    		if(sequence[s]->sw.Time() >= (sequence[s]->midiData[sequence[s]->i].timestamp))
		    	{
			    	std::vector<unsigned char>output(3);
				    output[0] = sequence[s]->midiData[sequence[s]->i].channel;
					output[1] = sequence[s]->midiData[sequence[s]->i].note;
					output[2] = sequence[s]->midiData[sequence[s]->i].velocity;	

					sequence[s]->midi->SendMessage(&output);
					
					if(sequence[s]->gmeter != NULL){
						int percent = (output[2] * 100) / 127;
						GMeterEvent event(wxEVT_COMMAND_GMETER); //ID of where we come from?
						event.SetValue(percent);
						wxPostEvent(sequence[s]->gmeter->GetEventHandler(), event); //event handle of the gui object
					}
					
					//send output status message
					wxString outputStatus;
					if(output[0] > 143 && output[0] < 160 && output[2] > 0){ outputStatus = wxString::Format(wxT("Midi NoteON:  %d  "), (output[0] - 143)); }  
					if(output[0] > 143 && output[0] < 160 && output[2] == 0){ outputStatus = wxString::Format(wxT("Midi NoteOFF:  %d  "), (output[0] - 143)); } 
					if(output[0] > 127 && output[0] < 144){ outputStatus = wxString::Format(wxT("Midi NoteOFF: %d  "), (output[0] - 127)); } 
					if(output[0] > 159 && output[0] < 176){ outputStatus = wxString::Format(wxT("Midi Aftertouch: ch-%d  "), (output[0]-159)); } 
					if(output[0] > 175 && output[0] < 192){ outputStatus = wxString::Format(wxT("Midi CC: %d  "), (output[0] - 175)); } 
					if(output[0] > 191 && output[0] < 208){ outputStatus = wxString::Format(wxT("Midi PC: %d  "), (output[0] - 191)); } 
					outputStatus += wxString::Format(wxT("%d  %d"), output[1], output[2]);
					
					//Send by event
					StatusDialogEvent event(wxEVT_COMMAND_STATUSDIALOG); //ID of where we come from?
					event.SetInOut(2); //Set event flag to output
					event.SetValue(outputStatus);
					wxPostEvent(sequence[s]->statusDialog->GetEventHandler(), event); //event handle of the gui object

					++sequence[s]->i;
				}
			}
			else{
				play[s] = false;
				sequence[s]->sw.Pause(); //stop the timer
				sequence[s]->Kill();
			}
		}
	}
}