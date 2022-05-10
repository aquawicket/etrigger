//// GMeter.cpp ///////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////

#include "GMeter.h" 

///////// Gmeter Event ////////////////
DEFINE_EVENT_TYPE(wxEVT_COMMAND_GMETER) 
IMPLEMENT_DYNAMIC_CLASS(GMeterEvent, wxCommandEvent) 

/////////////////////////////////////////////////////////////////////////////////////////
GMeterEvent::GMeterEvent(wxEventType commandType, int id) : wxCommandEvent(commandType, id) 
{ 
} 


///////////////////////////////////
BEGIN_EVENT_TABLE(GMeter, wxPanel) 
	EVT_MOUSE_EVENTS (GMeter::OnMouse)
	EVT_PAINT (GMeter::OnPaint)
	EVT_ERASE_BACKGROUND(GMeter::OnEraseBackground)
	EVT_GMETER(-1, GMeter::OnGMeterEvent)
END_EVENT_TABLE() 

///////////////////////////////////////////////////////////////////////////////////////////////////
GMeter::GMeter(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, bool falloff)
{ 
	// SETTINGS
	SPEED1 = 2;
	SPEED2 = 100;
	PEAK = 1;
	SPACING = 5;
	
	mySize = size;

	updateFlag = false;

	(void)Create(parent, id, pos, size); 
} 

/////////////////
GMeter::~GMeter() 
{ 
	delete memDC;
} 

////////////////////////////////////////////////////////////////////////////////////////////////////////
bool GMeter::Create(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size) 
{ 
	if(!wxPanel::Create(parent, id, pos, size, wxNO_BORDER, wxT(""))) 
		return false; 

	memDC = new wxMemoryDC();
	SetBackgroundColour(wxColour(0,0,0));
	updateFlag = false;
	Refresh();

	return true; 
} 

///////////////////////////////////////////////////
void GMeter::OnEraseBackground(wxEraseEvent& event)
{

}

////////////////////////////////////////////////////
void GMeter::OnPaint(wxPaintEvent &WXUNUSED(event)) 
{
#ifndef MAC
	SetDoubleBuffered(false);
#endif //!MAC
	
	wxBufferedPaintDC dc(this); 

	if(updateFlag){
		dc.Blit(0, 0, mySize.x, mySize.y, memDC, 0, 0);
		updateFlag = false;
	}
	else{
		dc.SetBackground(wxColour(0, 0, 0)); 
		dc.SetBackgroundMode(wxSOLID); 
		dc.Clear(); 
		dc.SetBrush(*wxTRANSPARENT_BRUSH); 
	}
}

/////////////////////////
void GMeter::Hit(int val)
{
	wxImage temp = wxImage(mySize.x, mySize.y, false);
	memDC->SelectObject(wxBitmap(temp));
	memDC->SetBackground(wxColour(0, 0, 0)); 
	memDC->SetBackgroundMode(wxSOLID); 
	memDC->Clear();

	sw.Start();
	falloff = (val * mySize.y) / 100;

	falltemp = falloff;
	peakfall = falloff;
	value = val;

	int position = (mySize.y * value) / 100;
	int b = SPACING -1;

	for(int i=0; i<position; ++i){

		int percent = ((i * 100) / mySize.y);
		int color1 = (255 * percent) / 100 * 2;
		if(percent > 50){color1 = 255;}
		int color2 = 255 - ((255 * percent) / 100 * 2);
		if(percent < 51){color2 = 255;}
		
		if(i != b || i == position-1){
			memDC->SetPen(wxColour(color1,color2,0));
			memDC->DrawLine(0, mySize.y -1 -i, mySize.x, mySize.y -1 -i);
		}	
		else{b=b+SPACING;}
		
		if(i == position-1){peakcolor = wxColour(color1, color2, 0);} //store the peak color
	}
	
	updateFlag = true;
	Refresh();
}

/////////////////////////////////////////
void GMeter::OnMouse(wxMouseEvent &event) 
{ 
	if(event.RightUp())
	{
		//FIXME
		//GetParent()->ProcessEvent(event); //Let event bleed through to the parent.
	}
}

/// TEST //////////////
bool GMeter::Notify(){
	
	if(falloff > 0){  //process falloff animations			
		temp = sw.Time();
		
		if(falltemp > 0){
			memDC->SetPen(wxColour(0, 0, 0));
			memDC->SetBrush(wxColour(0, 0, 0));
			memDC->DrawRectangle(0, mySize.y +PEAK -falloff, mySize.x, temp / SPEED1);
			updateFlag = true;
			Refresh();	
            falltemp =  falloff - (temp  / SPEED1);	
			return 1;
		}

		else if(peakfall > -SPEED2 && PEAK){
			memDC->SetPen(wxColour(0, 0, 0));
			memDC->DrawLine(0, mySize.y -peakfall, mySize.x, mySize.y -peakfall);
			peakfall = peakfall - (temp / SPEED2);
			memDC->SetPen(peakcolor);
			memDC->DrawLine(0, mySize.y -peakfall, mySize.x, mySize.y -peakfall);
			updateFlag = true;
			Refresh();
			return 1;
		}

		else{
			falloff = 0;
			sw.Pause();
			return 0;
		}
	}
	return 0;
}

//////////////////////////////////////////////
void GMeter::OnGMeterEvent(GMeterEvent &event)
{
	Hit(event.GetValue());
}