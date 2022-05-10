//// GScrollBar.cpp ///////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////

#include "GScrollBar.h"

DEFINE_EVENT_TYPE(wxEVT_COMMAND_GSCROLLBAR) 

IMPLEMENT_DYNAMIC_CLASS(GScrollBarEvent, wxCommandEvent) 

/////////////////////////////////////////////////////////////////
GScrollBarEvent::GScrollBarEvent(wxEventType commandType, int id) 
		        : wxCommandEvent(commandType, id) 
{ 
} 

///////////////////////////////////////
BEGIN_EVENT_TABLE(GScrollBar, wxWindow) 
	EVT_PAINT  (GScrollBar::OnPaint)
	EVT_MOUSE_EVENTS (GScrollBar::OnMouse) 
	//EVT_MOUSE_CAPTURE_LOST (GScrollBar::OnMouseCaptureLost)
	//EVT_ERASE_BACKGROUND (GScrollBar::OnEraseBackground) 
END_EVENT_TABLE() 

//////////////////////////////////////////////////////////////////////////////////////////////
GScrollBar::GScrollBar(wxWindow* parent, wxWindow *scrollwindow, wxWindowID id, int direction)
{ 
	Init();
    framewin = parent;
	scrollwin = scrollwindow;
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	(void)Create(parent, id, direction); 
} 

/////////////////////////
GScrollBar::~GScrollBar()
{
}

/////////////////////// 
void GScrollBar::Init() 
{ 
	position = 0;
	sliderposition = 15;
	scrollwinposition = 0;

	//left.LoadFile(wxT("left.bmp"), wxBITMAP_TYPE_ANY);
	//right.LoadFile(wxT("right.bmp"), wxBITMAP_TYPE_ANY);

	const wxImage &temp = left_xpm;//wxImage(left_xpm);
	const wxImage &temp2 = right_xpm;//wxImage(right_xpm);
	left = temp;
	right = temp2;
} 

///////////////////////////////////////////////////////////////////////
bool GScrollBar::Create(wxWindow* parent, wxWindowID id, int direction) 
{ 
	
    pSize = framewin->GetSize();	
    wxString name = wxT("scrollbar");

	if(!wxPanel::Create(parent, id, wxPoint(0, pSize.y - 15), wxSize(pSize.x, 15), wxNO_BORDER, name)) 
		return false; 

	SetBackgroundColour(wxColour(0,0,0));
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	return true; 
} 

//////////////////////////
void GScrollBar::SizeBar()
{
	wxSize temp = framewin->GetSize();
	SetSize(0, temp.y - 15, temp.x, 15);

	Refresh();
}

////////////////////////////////
void GScrollBar::ShowScrollBar()
{
	Show();
	Refresh();
	active = true;
}

////////////////////////////////
void GScrollBar::HideScrollBar()
{
	Hide();
	Refresh();
	active = false;
}

///////////////////////////////////////////////////////
void GScrollBar::OnPaint(wxPaintEvent &WXUNUSED(event)) 
{ 
	if(active){
#ifndef MAC
	SetDoubleBuffered(false);
#endif //!MAC
    wxBufferedPaintDC dc(this);

    DrawBackground(dc); 
    DrawSlider(dc);
	DrawArrows(dc);
	
	}
} 

/////////////////////////////////////////
void GScrollBar::DrawBackground(wxDC &dc)
{
	dc.SetBrush(wxColour(0,0,0)); 
	wxSize temp;
    temp = GetSize();
	dc.DrawRectangle(15, 0, temp.x-30, 15);
}

/////////////////////////////////////
void GScrollBar::DrawSlider(wxDC &dc)
{
	dc.SetBrush(wxColour(50,50,50)); 
	dc.DrawRectangle(sliderposition, 0, slidersize, 15);
}

/////////////////////////////////////
void GScrollBar::DrawArrows(wxDC &dc)
{
	dc.DrawBitmap( left, 0, 0);

	wxSize tempSize;
    tempSize = GetClientSize();
	dc.DrawBitmap( right, tempSize.x-15, 0);
}

/////////////////////////////////////////////////////////////////
void GScrollBar::OnEraseBackground(wxEraseEvent& WXUNUSED(event)) 
{
}

/////////////////////////////////////////////
void GScrollBar::OnMouse(wxMouseEvent &event) 
{ 
	if(slidersize > GetSize().x - 31){
		event.Skip(true);
		return;
	}

	wxClientDC dc(this); 
	PrepareDC(dc); 

	wxPoint pos = event.GetPosition(); 
	long x = dc.DeviceToLogicalX(pos.x); 
	long y = dc.DeviceToLogicalY(pos.y); 

	// Send click event
	if(event.LeftDown()) 
		{ 
			//slider bar
			if (x > sliderposition && x < (sliderposition + slidersize)){
				offset = x - sliderposition;
	        	m_dragging = true;
				if(UseMouseCapture()) CaptureMouse();
     			Refresh();
	     		return;
			}

			//left arrow
			if (x < 16){
				// Create and event 
				sliderposition = sliderposition - 10;
				if(sliderposition < 15){sliderposition = 15;}
					wxSize temp;
					temp = GetSize();
				if(sliderposition > (temp.x - slidersize - 15)){sliderposition = (temp.x - slidersize - 15);}
				Refresh();
				//DrawBackground(dc);
			    //DrawSlider(dc);
				wxSize temp3 = framewin->GetSize();
    			int percent = ((sliderposition - 15)* 100) / ((temp.x - 30)- slidersize); 
				position = ((percent * (fullPageSize - (temp3.x - 30))) / 100);

				ScrollWindow();

				GScrollBarEvent event(wxEVT_COMMAND_GSCROLLBAR, GetId()); 
				event.SetEventObject(this); 

				// Give it some contents 
				event.SetValue(position); 

				// Send it 
				GetEventHandler()->ProcessEvent(event); 
			}

			//right arrow
			wxSize temp;
            temp = GetSize();
			if (x > temp.x - 15){
				// Create and event 
				sliderposition = sliderposition + 10;
				if(sliderposition < 15){sliderposition = 15;}
				wxSize temp; 
				temp = GetSize();
				if(sliderposition > (temp.x - slidersize - 15)){sliderposition = (temp.x - slidersize - 15);}
				Refresh();
				//DrawBackground(dc);
			    //DrawSlider(dc);
				pSize = framewin->GetSize();
    			int percent = ((sliderposition - 15)* 100) / ((temp.x - 30)- slidersize); 
				position = ((percent * (fullPageSize - (pSize.x - 30))) / 100);

				ScrollWindow();

				GScrollBarEvent event(wxEVT_COMMAND_GSCROLLBAR, GetId()); 
				event.SetEventObject(this); 

				// Give it some contents 
				event.SetValue(position); 

				// Send it 
				GetEventHandler()->ProcessEvent(event); 
			}
		} 

	if(event.LeftUp() || (event.Leaving() && !UseMouseCapture())) 
	{
		m_dragging = false;
		if(HasCapture()) {
				ReleaseMouse();  
		}
	    return;
	}

	if(m_dragging)
	{
		if(event.Dragging()) 
		{
			
			sliderposition = x - offset;
			if(sliderposition < 15){sliderposition = 15;}
			wxSize temp = GetSize();
			if(sliderposition > (temp.x - slidersize - 15)){sliderposition = (temp.x - slidersize - 15);}
			
			Refresh();
			//DrawBackground(dc);
			//DrawSlider(dc);
			
            //ok we got the slider position. Now precent wise, how many pixels should the positon be?
			//what pecrcent of (temp.x - slidersize) is sliderposition?
			int percent = ((sliderposition - 15)* 100) / ((temp.x - 30)- slidersize); 
			position = ((percent * (fullPageSize - (temp.x ))) / 100);

			ScrollWindow();
			// Create and event 
			GScrollBarEvent event(wxEVT_COMMAND_GSCROLLBAR, GetId()); 
			event.SetEventObject(this); 

			// Give it some contents 
			event.SetValue(position); 


			// Send it 
			GetEventHandler()->ProcessEvent(event); 

		}

		return;
	}

	event.Skip(true);
} 

//////////////////////////////////
bool GScrollBar::UseMouseCapture() 
{ 
	if(GetWindowStyle() & FDR_NO_MOUSE_CAPTURE) 
		return false; 
	else{
		//this->SetFocus(); //this makes the mouse wheel work.. but created track focus issues. 
		return true; 
	} 
} 

///////////////////////////////////////////////////////////////////
/*
void GScrollBar::OnMouseCaptureLost(wxMouseCaptureLostEvent &event)
{

}
*/

////////////////////////////////////////////////////////
void GScrollBar::SizeSlider(int pagesize, int framesize)
{
	wxSize temp = GetSize();
	int percent = 0;
	if(pagesize > (framesize - 30)){
		percent = ((framesize - 30) * 100) / pagesize;  
	}
	else{
		percent = 100;
	}
    slidersize =  ( (percent * (temp.x)) / 100);
	if(slidersize < 20){slidersize = 20;}  //don't let the slider get too small.
	if(slidersize > temp.x - 30){slidersize = (temp.x - 30);}

	Refresh();	
}

/////////////////////////////////////////////
void GScrollBar::PositionSlider(int pagesize)
{
	wxSize temp = GetSize();
	int percent = 0;
	if(pagesize > position){
		percent = (position * 100) / pagesize;
	}
	else{
		percent = 0;
	}

	sliderposition =  ((percent * (temp.x) ) / 100) + 15;
}

/////////////////////////////////////////////////////////////
void GScrollBar::UpdateScrollBar(int framesize, int pagesize)
{
	fullPageSize = pagesize;

	wxSize temp = GetSize(); //<- we loose this when temp.x > pagesize for some reason :( !!!!!!!!!!!!
	//OutputDebugString(wxString::Format("temp.x = %d  pagesize = %d \n", temp.x, pagesize) );
	/*
	if(framesize > pagesize){	
		HideScrollBar();
		active = false;
	}
	else{
	*/
		ShowScrollBar();
		active = true;
	//}

	if(active){
	SizeBar();
	SizeSlider(pagesize, framesize);
	PositionSlider(pagesize);
	scrollwinposition = (0-position);

	/// Check to see if we need to scroll the window right with the resize
	/////   FIX ME  ////////////////////
	if(sliderposition >= (temp.x - slidersize - 15)){
		
		//scroll the window right to compinsate
		if(position > 0){
		wxSize temp = framewin->GetSize();
	    scrollwin->ScrollWindow(  temp.x - pSize.x, 0, NULL ); 
		position = position - (temp.x - pSize.x);
		scrollwinposition = (0-position);
		}
		else {
			position = 0;
			scrollwin->ScrollWindow(  0-(scrollwinposition+position), 0, NULL ); 
			scrollwinposition = (0-position);
		}
		sliderposition = (temp.x - slidersize - 15);
	}

	if(sliderposition < 15){sliderposition = 15;}
	
	pSize = framewin->GetSize();
	}
}

///////////////////////////////
void GScrollBar::ScrollWindow()
{
	scrollwin->ScrollWindow(  0-(scrollwinposition+position), 0, NULL ); 
	scrollwinposition = (0-position);
	
}

//////////////////////////////
void GScrollBar::ResetScroll()
{
	position = 0;
	ScrollWindow();
}
