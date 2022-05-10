//// SequencerDialog.cpp ///////////////////////////////////////////////////////////////////////
//
//  Once this class can open .mid files, it should be good to use.
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "SequencerDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

////////////////////////////////////////////
BEGIN_EVENT_TABLE(SequencerDialog, wxDialog)
	EVT_SIZE      (SequencerDialog::OnSize)
	EVT_SCROLL    (SequencerDialog::OnScroll)
	EVT_BUTTON    (106, SequencerDialog::OnBackward)
	EVT_BUTTON    (102, SequencerDialog::OnPlay)
	EVT_BUTTON    (103, SequencerDialog::OnStop)
	EVT_BUTTON    (104, SequencerDialog::OnRecord)
	EVT_BUTTON    (105, SequencerDialog::OnRewind)
	EVT_BUTTON    (107, SequencerDialog::OnForward)
	EVT_BUTTON    (108, SequencerDialog::OnSave)
	EVT_BUTTON    (109, SequencerDialog::OnClear)
END_EVENT_TABLE()

///////////////////////////////////////////////////
SequencerDialog::SequencerDialog(MainPanel *parent)
      : wxDialog(parent, -1, wxT("Sequencer"), wxDefaultPosition, wxSize(700, 500), wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER | wxMAXIMIZE_BOX)
{
	mainPanel = parent;

	wxStandardPaths stdPath; 
    wxString fileLocation = stdPath.GetExecutablePath();
#ifdef MAC
	fileLocation.Replace(wxT("/eTrigger.app/Contents/MacOS/eTrigger"), wxT(""), true);
	fileLocation += wxT("/Sequencer/");
	seqDir = fileLocation;
#endif //MAC
#ifdef WIN32
	seqDir = wxFileName(fileLocation).GetPath() += wxT("\\Sequencer\\");
#endif //WIN32

	CentreOnScreen(wxBOTH);

#ifdef WIN32 ///////////////////////////////
	SetBackgroundColour(wxColour(90,90,90));
#endif //WIN32 /////////////////////////////
#ifdef MAC ////////////////////////////////////////////////////////////////////////////////
	wxPanel *background = new wxPanel(this, -1, wxPoint(0,0), this->GetSize(), 0, wxT(""));
	background->SetBackgroundColour(wxColour(90,90,90));
#endif //MAC //////////////////////////////////////////////////////////////////////////////

	grid = new Grid(this);

	hScrollPosition = 0;
	hScrollBar = new wxScrollBar(this, 101, wxPoint(60 , 410), wxSize(630,20), wxSB_HORIZONTAL, wxDefaultValidator, wxT(""));

	rewind = new wxButton(this, 105, wxT("|<"), wxPoint(0,0), wxSize(40, 30), 0, wxDefaultValidator, wxT(""));
	backward = new wxButton(this, 106, wxT("<<"), wxPoint(0,0), wxSize(40, 30), 0, wxDefaultValidator, wxT(""));
	playButton = new wxButton(this, 102, wxT("Play"), wxPoint(0,0), wxSize(40, 30), 0, wxDefaultValidator, wxT(""));
	stop = new wxButton(this, 103, wxT("Stop"), wxPoint(0, 0), wxSize(40, 30), 0, wxDefaultValidator, wxT(""));
	recordButton = new wxButton(this, 104, wxT("Record"), wxPoint(0, 0), wxSize(40, 30), 0, wxDefaultValidator, wxT(""));
	forward = new wxButton(this, 107, wxT(">>"), wxPoint(0,0), wxSize(40, 30), 0, wxDefaultValidator, wxT(""));
	save = new wxButton(this, 108, wxT("Save"), wxPoint(0,0), wxSize(40,30), 0, wxDefaultValidator, wxT(""));
	clear = new wxButton(this, 109, wxT("Clear"), wxPoint(0,0), wxSize(40,30), 0, wxDefaultValidator, wxT(""));

	UpdateDlg();

	//time = new PTimer(this);
}

///////////////////////////////////
SequencerDialog::~SequencerDialog()
{
	//delete time;
}

//////////////////////////////
void SequencerDialog::Notify()
{
	if(play){
		grid->cursorPosition = sw.Time();
		std::vector<unsigned char>output(3);

		if(grid->cursorPosition < (grid->GetHRange() + 300) && i < grid->midiData.size()){
			if(grid->cursorPosition >= (grid->midiData[i].timestamp))
			{
				output[0] = grid->midiData[i].channel;
				output[1] = grid->midiData[i].note;
				output[2] = grid->midiData[i].velocity;	

				mainPanel->trackProc->midi->SendMessage(&output);	

				++i;
			}
			grid->CheckCursor();
			grid->Refresh();
		}
		else{
			play = false;
			sw.Pause(); //stop the timer
			Stop(); //Stop Notify();
			grid->cursorPosition = 0;
			i=0;
		}
	}

	if(record){
		grid->cursorPosition = sw.Time();
		grid->CheckCursor();
		grid->Refresh();
	}
}

////////////////////////////////////////////////
void SequencerDialog::OnSize(wxSizeEvent &event)
{
	UpdateDlg();
}

////////////////////////////////////////////////////
void SequencerDialog::OnScroll(wxScrollEvent &event)
{
	hScrollPosition = hScrollBar->GetThumbPosition();
	UpdateDlg();
}

/////////////////////////////////////////////////////
void SequencerDialog::OnRewind(wxCommandEvent &event)
{
	Stop();
	hScrollBar->SetThumbPosition(0);
	hScrollPosition = 0;
	grid->cursorPosition = 0;
	i = 0;
	UpdateDlg();
}

///////////////////////////////////////////////////////
void SequencerDialog::OnBackward(wxCommandEvent &event)
{
	Stop();

	grid->cursorPosition = grid->cursorPosition - 200;
	if(grid->cursorPosition < 0){
		grid->cursorPosition = 0;
		hScrollPosition = 0;
		hScrollBar->SetThumbPosition(0);
	}

	i = GetNextNote();
	grid->CheckCursor();
	UpdateDlg();
}

///////////////////////////////////////////////////
void SequencerDialog::OnPlay(wxCommandEvent &event)
{
	play = true;
	record = false;
	sw.Start(grid->cursorPosition);
}

///////////////////////////////////////////////////
void SequencerDialog::OnStop(wxCommandEvent &event)
{
	//Stop();
	UpdateDlg();
}

////////////////////////////
void SequencerDialog::Stop()
{
	play = false;
	record = false;
	sw.Pause();
	//Stop();
	i = GetNextNote();
}
/////////////////////////////////////////////////////
void SequencerDialog::OnRecord(wxCommandEvent &event)
{
	play = false;
	record = true;
	//Start(1, false);
	sw.Start(0);
	sw.Pause();
}

//////////////////////////////////////////////////////
void SequencerDialog::OnForward(wxCommandEvent &event)
{
	Stop();

	grid->cursorPosition = grid->cursorPosition + 200;

	i = GetNextNote();
	grid->CheckCursor();
	UpdateDlg();
}
///////////////////////////////////////////////////
void SequencerDialog::OnSave(wxCommandEvent &event)
{
	int response;
	wxFileDialog *fileDlg = new wxFileDialog(NULL, wxString(wxT("Save eTrigger Sequence")), seqDir, seqFile, 
		                                    wxString(wxT("eTrigger Sequence (*.seq)|*.seq")), wxFD_SAVE | wxFD_OVERWRITE_PROMPT, wxDefaultPosition);
	response = fileDlg->ShowModal();
	if(response == wxID_OK){
		seqFile = fileDlg->GetFilename();
		SaveMidiFile();
	}
	delete fileDlg;
}

////////////////////////////////////////////////////
void SequencerDialog::OnClear(wxCommandEvent &event)
{
	grid->midiData.clear();
	Refresh();
}

/////////////////////////////////
void SequencerDialog::UpdateDlg()
{
	grid->SetSize(this->GetSize().x - 85, this->GetSize().y - 100);
	
	hScrollBar->SetPosition(wxPoint(grid->GetPosition().x, grid->GetSize().y + 11));
	hScrollBar->SetSize(grid->GetSize().x, 15);

	//We want to set the range according to the first and last midi time stamps.
#ifndef MAC
	hScrollBar->SetThumbSize(grid->GetSize().x - 100);
	hScrollBar->SetRange(grid->GetHRange());
#endif //!MAC

	rewind->SetPosition(wxPoint(grid->GetPosition().x, grid->GetSize().y + 30));
	backward->SetPosition(wxPoint(grid->GetPosition().x + 50, grid->GetSize().y + 30));
	playButton->SetPosition(wxPoint(grid->GetPosition().x + 100, grid->GetSize().y + 30));
	stop->SetPosition(wxPoint(grid->GetPosition().x + 150, grid->GetSize().y + 30));
	recordButton->SetPosition(wxPoint(grid->GetPosition().x + 200, grid->GetSize().y + 30));
	forward->SetPosition(wxPoint(grid->GetPosition().x + 250, grid->GetSize().y + 30));
	save->SetPosition(wxPoint(grid->GetPosition().x + 350, grid->GetSize().y + 30));
	clear->SetPosition(wxPoint(grid->GetPosition().x + 400, grid->GetSize().y + 30));

	grid->Refresh();
}

///////////////////////////////////////////////////////////////////////////////
void SequencerDialog::AddNoteOn(long time, int channel, int note, int velocity)
{
	MIDIDATA temp;
	temp.midiType = 0; //note on
	temp.drumType = 0;
	temp.dificulty = 0;
	temp.timestamp = time;
	temp.velocity = velocity;

	temp.note = note;
	temp.channel = channel;
	
	if(grid->midiData.size() == 0){grid->midiData.push_back(temp); return;}
	
	//Insert into the right slot according to timestamp.
	unsigned int i = 0;
	while(i < grid->midiData.size()){
		if(time > grid->midiData[i].timestamp){
			++i;
		}
		else{
			break;
		}
	}

	grid->midiData.insert( grid->midiData.begin() + i, temp );
}

//////////////////////////////////////////////////////////////////
void SequencerDialog::AddNoteOff(long time, int channel, int note)
{
	MIDIDATA temp;
	temp.midiType = 1; //noteOff
	temp.drumType = 0;
	temp.dificulty = 0;
	temp.timestamp = time;
	temp.velocity = 0;

	temp.note = note;
	temp.channel = channel;
	
	if(grid->midiData.size() == 0){grid->midiData.push_back(temp); return;}
	
	//Insert into the right slot according to timestamp.
	unsigned int i = 0;
	while(i < grid->midiData.size()){
		if(time > grid->midiData[i].timestamp){
			++i;
		}
		else{
			break;
		}
	}

	grid->midiData.insert( grid->midiData.begin() + i, temp );
}

///////////////////////////////////////////////////////////////////////////////
void SequencerDialog::AddMidiCC(long time, int channel, int note, int velocity)
{
	MIDIDATA temp;
	temp.midiType = 2; //MidiCC
	temp.drumType = 0;
	temp.dificulty = 0;
	temp.timestamp = time;
	temp.velocity = velocity;

	temp.note = note;
	temp.channel = channel;
	
	if(grid->midiData.size() == 0){grid->midiData.push_back(temp); return;}
	
	//Insert into the right slot according to timestamp.
	unsigned int i = 0;
	while(i < grid->midiData.size()){
		if(time > grid->midiData[i].timestamp){
			++i;
		}
		else{
			break;
		}
	}

	grid->midiData.insert( grid->midiData.begin() + i, temp );
}

//////////////////////////////////////
void SequencerDialog::SetCursor(int x)
{
	Stop();
	grid->cursorPosition = x + hScrollPosition;
	i = GetNextNote();

	UpdateDlg();	
}

//////////////////////////////////
int SequencerDialog::GetNextNote()
{
	// Find the next i from the position
	unsigned int i=0;
	while( i < grid->midiData.size() && grid->cursorPosition > grid->midiData[i].timestamp){
		++i;
	}
	return i;
}
/////////////////////////////////////////////////
void SequencerDialog::LoadMidiFile()
{
	wxString temp = seqDir;
	wxFile* file = new wxFile(temp += seqFile, wxFile::read);
	if(file->IsOpened()){
		if(!file->Eof()){

			grid->midiData.clear();
			int vectorSize;
			file->Read(&vectorSize, sizeof(vectorSize));
			for(int z=0; z<vectorSize; ++z){
				MIDIDATA temp;
				file->Read(&temp, sizeof(temp));
				grid->midiData.push_back(temp);
			}
		}
	}
	file->Close();
	delete file;
}

////////////////////////////////////
void SequencerDialog::SaveMidiFile()
{
	wxString temp = seqDir;
	wxFile*	file = new wxFile(temp += seqFile, wxFile::write);
	if(file->IsOpened()){
		int vectorSize = grid->midiData.size();
		file->Write(&vectorSize, sizeof(vectorSize));	
		for(int z=0; z<vectorSize; ++z){
			file->Write(&grid->midiData[z], sizeof(grid->midiData[z]));
		}
	}
	file->Close();
	delete file;
}

/////////////////////////////////////////////////////////////////////////
void SequencerDialog::RecieveMessage(std::vector<unsigned char> &message)
{
	//Determin the signal type
	//message[0] = channel;
	//message[1] = note;
	//message[2] = velocity;
	//OutputDebugString(Conv(message[0]) += wxString(" ") += Conv(message[1]) += wxString(" ") += Conv(message[2]) += wxString("\n"));

	if(sw.Time() == 0){
		sw.Start(0);
	}

	//Note On
	if(message[0] > 143 && message[0] < 160 && message[2] > 0){
		AddNoteOn(grid->cursorPosition, message[0], message[1], message[2]);
	}
    //Note Off
    if(message[0] > 143 && message[0] < 160 && message[2] == 0){
		AddNoteOff(grid->cursorPosition, message[0], message[1]);
	}
	//MidiCC
	if(message[0] > 175 && message[0] < 192){
		AddMidiCC(grid->cursorPosition, message[0], message[1], message[2]);
	}
}

////////////////////////////////
BEGIN_EVENT_TABLE(Grid, wxPanel)
	EVT_PAINT  (Grid::OnPaint) 
	EVT_MOUSE_EVENTS (Grid::OnMouse)
END_EVENT_TABLE()

///////////////////////////////////
Grid::Grid(SequencerDialog *parent)
     :wxPanel(parent, 100, wxPoint(60,10), wxSize(630, 400), 0, wxT(""))
{
	sequencerDialog = (SequencerDialog*)parent;
	SetBackgroundColour(wxColour(30,30,30));

	cursorPosition = 0;
}

///////////////////////////////////////
void Grid::OnPaint(wxPaintEvent &event) 
{ 
#ifndef MAC
	SetDoubleBuffered(true);
#endif //!MAC
	wxBufferedPaintDC dc(this); 

	dc.SetBackground(wxColour(30, 30, 30)); 
	dc.Clear();
	dc.SetBrush(wxBrush(wxColour(255,255,255), wxSOLID)); 

	DrawGrid(dc);
	DrawMidi(dc);
	DrawCursor(dc);
	//dc.Blit(0, 0, GetSize().x, GetSize().y,
} 

////////////////////////
void Grid::CheckCursor()
{
	if((cursorPosition - sequencerDialog->hScrollPosition) != (GetSize().x  / 2)){
		if(cursorPosition - (GetSize().x  / 2) > 0){
			//adjust the hScrollBar to get the cursor to the middle
			sequencerDialog->hScrollPosition = cursorPosition - (GetSize().x  / 2);
			sequencerDialog->hScrollBar->SetThumbPosition(cursorPosition - (GetSize().x  / 2));
		}
	}
}

////////////////////////////////////////////
void Grid::OnMouse(wxMouseEvent &event)
{
	if(event.LeftDown()){
		sequencerDialog->SetCursor(event.GetPosition().x);
	}
}

/////////////////////////////
void Grid::DrawGrid(wxDC &dc)
{
	//first we need to draw 126 horizonal lines
	//So it's the height of the grid / 127

	dc.SetPen(wxColour(50,50,50));

	float temp = (float)GetSize().y / (float)127;
	for(float i=1; i<127; ++i){
		dc.DrawLine(0, temp * i, GetSize().x, temp * i);
	}
}

/////////////////////////////
void Grid::DrawMidi(wxDC &dc)
{
	//first we need to draw 126 horizonal lines
	//So it's the height of the grid / 127

	//find the first element and set all time stamps reletive to it.
	float temp = (float)GetSize().y / (float)127;

	for(unsigned int i=0; i<midiData.size(); ++i){
		if(midiData[i].midiType == 0){
			
			int velocity = GetSize().y - midiData[i].velocity * temp - temp;


		    //draw velocity
			dc.SetPen(wxColour(0,255,0));
			dc.DrawLine(midiData[i].timestamp - sequencerDialog->hScrollPosition, velocity, midiData[i].timestamp - sequencerDialog->hScrollPosition, GetSize().y);
			
			//draw note
			dc.SetPen(wxColour(255,255,255));
			dc.DrawRectangle(midiData[i].timestamp - sequencerDialog->hScrollPosition, temp * midiData[i].note - temp, 5, temp);
		
			//FIXME  -  we need to draw the note off here.
		}
	}
}

///////////////////////////////
void Grid::DrawCursor(wxDC &dc)
{
	dc.SetPen(wxColour(255,0,0));
	dc.DrawLine(cursorPosition - sequencerDialog->hScrollPosition, 0, cursorPosition - sequencerDialog->hScrollPosition, GetSize().y);
}

/////////////////////
int Grid::GetHRange()
{
	if(midiData.size() > 0){
		return  midiData[midiData.size()-1].timestamp - midiData[0].timestamp;
	}
	else{
		return 0;
	}
}