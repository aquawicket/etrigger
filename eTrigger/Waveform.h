//// Waveform.h /////////////////////////////////////////////////////////////
// 
//  Used to draw the waveform of sound data
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef WAVEFORM_H
#define WAVEFORM_H


/////////////////////////////////////////
class WaveformEvent: public wxCommandEvent 
{ 
	public: 
		WaveformEvent(wxEventType commandType = wxEVT_NULL, int id = 0 ); 

		virtual wxEvent *Clone() const { return new WaveformEvent(*this); } 

	private: 
	DECLARE_DYNAMIC_CLASS(WaveformEvent) 
}; 

BEGIN_DECLARE_EVENT_TYPES() 
	DECLARE_EVENT_TYPE(wxEVT_COMMAND_WAVEFORM, -1) 
END_DECLARE_EVENT_TYPES() 

typedef void (wxEvtHandler::*wxWaveformEventFunction)(WaveformEvent&); 

#define EVT_WAVEFORM(id, fn) \
	DECLARE_EVENT_TABLE_ENTRY(wxEVT_COMMAND_WAVEFORM, id, -1,  \
	(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)  \
	wxStaticCastEvent(wxWaveformEventFunction, & fn), (wxObject *) NULL ),


///////////////////////////////
class Waveform : public wxPanel
{
public:
	Waveform(wxWindow *parent, EtmFile *file, wxPoint pos, wxSize size);
	void OnPaint(wxPaintEvent &event);
	void OnMouse(wxMouseEvent &event);
	void DrawWave(wxDC &dc);
	void DrawCursor(wxDC &dc);
	void SetCursor(double ms);
	void SetScroll(int amount);
	int GetWidthInPixels();
	int GetWidthInMs();

	EtmFile *etmFile;
	
	double ratio; //the pixels per frame ratio "horozontal zoom"
	double cursor; //current audio position in ms
	int scrollAmount; //how far the wave data is scrolled over.

	DECLARE_EVENT_TABLE();
};

#endif WAVEFORM_H