//// MidiForm.h //////////////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef MIDIFORM_H
#define MIDIFORM_H

/////////////////////////////////////////
class MidiformEvent: public wxCommandEvent 
{ 
	public: 
		MidiformEvent(wxEventType commandType = wxEVT_NULL, int id = 0 ); 

		virtual wxEvent *Clone() const { return new MidiformEvent(*this); } 

	private: 
	DECLARE_DYNAMIC_CLASS(MidiformEvent) 
}; 

BEGIN_DECLARE_EVENT_TYPES() 
	DECLARE_EVENT_TYPE(wxEVT_COMMAND_MIDIFORM, -1) 
END_DECLARE_EVENT_TYPES() 

typedef void (wxEvtHandler::*wxMidiformEventFunction)(MidiformEvent&); 

#define EVT_MIDIFORM(id, fn) \
	DECLARE_EVENT_TABLE_ENTRY(wxEVT_COMMAND_MIDIFORM, id, -1,  \
	(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)  \
	wxStaticCastEvent(wxMidiformEventFunction, & fn), (wxObject *) NULL ),


///////////////////////////////
class Midiform : public wxPanel
{
public:
	Midiform(wxWindow *parent, EtmFile *file, wxPoint pos, wxSize size);
	void OnPaint(wxPaintEvent &event);
	void OnMouse(wxMouseEvent &event);
	void OnKey(wxKeyEvent &event);
	void LoadMidi();
	void DrawGrid(wxDC &dc);
	void DrawMidi(wxDC &dc);
	void DrawCursor(wxDC &dc);
	void SetCursor(double ms);
	void SetScroll(int amount);
	int GetWidthInPixels();

	EtmFile *etmFile;

	double ratio; //the pixels per frame ratio "horozontal zoom"
	double cursor; //current audio position in ms
	int scrollAmount; //how far the wave data is scrolled over.
	int selectedNode;

	DECLARE_EVENT_TABLE();
};

#endif //MIDIFORM_H