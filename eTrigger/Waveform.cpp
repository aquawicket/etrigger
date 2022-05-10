//// Waveform.cpp /////////////////////////////////////////////////////////////
// 
//
//////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "Waveform.h" 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

DEFINE_EVENT_TYPE(wxEVT_COMMAND_WAVEFORM) 
IMPLEMENT_DYNAMIC_CLASS(WaveformEvent, wxCommandEvent)  // RTTI
///////////////////////////////////////////////////////////
WaveformEvent::WaveformEvent(wxEventType commandType, int id) 
		: wxCommandEvent(commandType, id) 
{ 
} 




////////////////////////////////////
BEGIN_EVENT_TABLE(Waveform, wxPanel) 
	EVT_PAINT  (Waveform::OnPaint) 
	EVT_MOUSE_EVENTS (Waveform::OnMouse)
END_EVENT_TABLE() 

//////////////////////////////////////////////////////////////
Waveform::Waveform(wxWindow *parent, EtmFile *file, wxPoint pos, wxSize size)
		:wxPanel(parent, wxID_ANY, pos, size, 0, wxT(""))
{
	//soundFile = NULL;
	etmFile = file;
	ratio = .5; //pixels per ms
	cursor = 0; //set the cursor ms.
	scrollAmount = 0; //set the scroll pixel.
}

///////////////////////////////////////////
void Waveform::OnPaint(wxPaintEvent &event) 
{ 
#ifndef MAC
	SetDoubleBuffered(true);
#endif //!MAC
	wxBufferedPaintDC dc(this);
	dc.SetBackground(wxColour(30, 30, 30));
	dc.Clear();

	//draw 0db line
	dc.SetPen(wxColour(0,255,0));
	dc.DrawLine(0, GetSize().y/2, GetSize().x, GetSize().y/2); 

	if(etmFile->soundFile != NULL){
		DrawWave(dc);
	}

	DrawCursor(dc);
} 

///////////////////////////////////////////
void Waveform::OnMouse(wxMouseEvent &event)
{
	if(event.LeftUp()){
		
		//we need to find the ms from the click.
		SetCursor((scrollAmount + event.GetPosition().x) / ratio);

		// Create event 
		WaveformEvent event(wxEVT_COMMAND_WAVEFORM, GetId()); 
		event.SetEventObject(this); 

		// Send it 
		GetEventHandler()->ProcessEvent(event); 
	}
}

/////////////////////////////////
void Waveform::DrawWave(wxDC &dc)
{
	//pixel to ms
	double ms = scrollAmount / ratio;
	double ms2 = (scrollAmount + GetSize().x) / ratio;
	//ms to frame;
	int f = ((ms / 1000) * etmFile->soundFile->samplerate) * etmFile->soundFile->channels;
	int f2 = ((ms2 / 1000) * etmFile->soundFile->samplerate) * etmFile->soundFile->channels;

	//we are currently drawing mono by overlapping the channels
	for(f; f<f2; ++f){

		//duration in ms = soundFile->frames / soundFile->samplerate * 1000;
		//currentTime in ms = f/soundFile->channels / soundFile->samplerate * 1000;

		int x = ((((float)(f/etmFile->soundFile->channels) / (float)etmFile->soundFile->samplerate) * 1000) * ratio) - scrollAmount;
		int y = ((GetSize().y/2) + (etmFile->soundFile->soundData[f] * (float)(GetSize().y/2)) );
		
		dc.DrawPoint(x, y);

		//how do we find out the time we are on in ms
		//use frames and samplerate
	}
}

////////////////////////////////////
void Waveform::DrawCursor(wxDC &dc)
{
	dc.SetPen(wxColour(255,0,0));
	dc.DrawLine((cursor * ratio) - scrollAmount, 0, (cursor * ratio) - scrollAmount, GetSize().y);
}

////////////////////////////////
void Waveform::SetCursor(double ms)
{
	etmFile->SetPosition(ms);
	cursor = etmFile->timeStamp->Time();
	Refresh();
}

////////////////////////////////////
void Waveform::SetScroll(int amount)
{
	scrollAmount = amount;
	Refresh();
}

////////////////////////////////
int Waveform::GetWidthInPixels()
{
	//We must find how wide the sound data is in pixels
	if(etmFile->soundFile != NULL){
		return etmFile->soundFile->frames / etmFile->soundFile->samplerate * 1000 * ratio;
	}
	return 0;
}

////////////////////////////
int Waveform::GetWidthInMs()
{
	if(etmFile->soundFile != NULL){
		return etmFile->soundFile->frames / etmFile->soundFile->samplerate * 1000;
	}
	return 0;
}