//// MidiForm.cpp /////////////////////////////////////////////////////////////
// 
//
//////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "MidiForm.h" 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


DEFINE_EVENT_TYPE(wxEVT_COMMAND_MIDIFORM) 
IMPLEMENT_DYNAMIC_CLASS(MidiformEvent, wxCommandEvent)  // RTTI
/////////////////////////////////////////////////////////////
MidiformEvent::MidiformEvent(wxEventType commandType, int id) 
		: wxCommandEvent(commandType, id) 
{ 
} 




////////////////////////////////////
BEGIN_EVENT_TABLE(Midiform, wxPanel) 
	EVT_PAINT  (Midiform::OnPaint) 
	EVT_MOUSE_EVENTS (Midiform::OnMouse)
	EVT_KEY_DOWN     (Midiform::OnKey)
END_EVENT_TABLE() 

/////////////////////////////////////////////////////////////////////////////
Midiform::Midiform(wxWindow *parent, EtmFile *file, wxPoint pos, wxSize size)
		:wxPanel(parent, wxID_ANY, pos, size, wxWANTS_CHARS, wxT(""))
{
	etmFile = file;
	ratio = .5; //pixels per ms
	cursor = 0; //set the cursor ms.
	scrollAmount = 0; //set the scroll pixel.
	selectedNode = -1;
}

///////////////////////////////////////////
void Midiform::OnPaint(wxPaintEvent &event) 
{ 
#ifndef MAC
	SetDoubleBuffered(true);
#endif //!MAC
	wxBufferedPaintDC dc(this);
	dc.SetBackground(wxColour(30, 30, 30));
	dc.Clear();

	DrawGrid(dc);
	DrawMidi(dc);
	DrawCursor(dc);
} 

///////////////////////////////////////////
void Midiform::OnMouse(wxMouseEvent &event)
{
	if(event.LeftDown()){
		SetFocus();
		selectedNode = -1;
		float temp = (float)GetSize().y / (float)40;

		for(unsigned int i=0; i<etmFile->midiData.size(); ++i){
			if(event.GetPosition().x > (etmFile->midiData[i].timestamp * ratio) - scrollAmount - 1 &&
				event.GetPosition().x < (etmFile->midiData[i].timestamp * ratio) - scrollAmount + 6 &&
				event.GetPosition().y > (temp * etmFile->midiData[i].drumType - temp - 3) &&
				event.GetPosition().y < (temp * etmFile->midiData[i].drumType) + 2 &&
				etmFile->midiData[i].midiType == 0){
				selectedNode = i;
			}
		}
	}

	if(event.LeftUp()){
		
		//we need to find the ms from the click.
		SetCursor((scrollAmount + event.GetPosition().x) / ratio);

		// Create event 
		MidiformEvent event(wxEVT_COMMAND_MIDIFORM, GetId()); 
		event.SetEventObject(this); 

		// Send it 
		GetEventHandler()->ProcessEvent(event); 
	}
}

///////////////////////////////////////
void Midiform::OnKey(wxKeyEvent &event)
{
	if(selectedNode != -1){
		if(event.GetKeyCode() == WXK_LEFT){
			etmFile->midiData[selectedNode].timestamp--;
		}
		if(event.GetKeyCode() == WXK_RIGHT){
			etmFile->midiData[selectedNode].timestamp++;
		}
		if(event.GetKeyCode() == WXK_DELETE ||
		   event.GetKeyCode() == WXK_BACK){
		   etmFile->midiData.erase (etmFile->midiData.begin() + selectedNode);
		   selectedNode = -1;
		}
		Refresh();
	}
}

/////////////////////////////////
void Midiform::DrawGrid(wxDC &dc)
{
	dc.SetPen(wxColour(50,50,50));

	float temp = (float)GetSize().y / (float)40;
	for(float i=1; i<40; ++i){
		dc.DrawLine(0, temp * i, GetSize().x, temp * i);
	}
}

/////////////////////////////////
void Midiform::DrawMidi(wxDC &dc)
{
	float temp = (float)GetSize().y / (float)40;

	for(unsigned int i=0; i<etmFile->midiData.size(); ++i){
		if(etmFile->midiData[i].midiType == 0){ //Note-ON
			
			int velocity = GetSize().y - etmFile->midiData[i].velocity * temp - temp;


		    //draw velocity
			dc.SetPen(wxColour(0,255,0));
			dc.DrawLine((etmFile->midiData[i].timestamp * ratio) - scrollAmount, velocity, (etmFile->midiData[i].timestamp * ratio) - scrollAmount, GetSize().y);
			
			//draw note
			if(selectedNode == i){
				dc.SetPen(wxColour(0,0,255));
			}
			else{
				dc.SetPen(wxColour(255,255,255));
			}
			dc.DrawRectangle((etmFile->midiData[i].timestamp * ratio) - scrollAmount, temp * etmFile->midiData[i].drumType - temp, 5, temp);
		
			//FIXME  -  we need to draw the note off here.
		}
	}
}

///////////////////////////////////
void Midiform::DrawCursor(wxDC &dc)
{
	dc.SetPen(wxColour(255,0,0));
	dc.DrawLine((cursor * ratio) - scrollAmount, 0, (cursor * ratio) - scrollAmount, GetSize().y);
}

/////////////////////////
void Midiform::LoadMidi()
{

}

///////////////////////////////////
void Midiform::SetCursor(double ms)
{
	etmFile->SetPosition(ms);
	cursor = etmFile->timeStamp->Time();
	Refresh();
}

////////////////////////////////////
void Midiform::SetScroll(int amount)
{
	scrollAmount = amount;
	Refresh();
}

////////////////////////////////
int Midiform::GetWidthInPixels()
{
	//We must find how wide the sound data is in pixels

	//ms duration * ration
	return 0;
}

