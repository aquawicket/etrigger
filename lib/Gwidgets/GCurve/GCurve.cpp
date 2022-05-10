//// GCurve.cpp ///////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////

#include "GCurve.h" 

wxColour GetColorAverage( wxColour color1, wxColour color2, float weight);
void DrawWuLine( wxDC *pDC, short X0, short Y0, short X1, short Y1 );

DEFINE_EVENT_TYPE(wxEVT_COMMAND_GCURVE) 

IMPLEMENT_DYNAMIC_CLASS(GCurveEvent, wxCommandEvent) 

///////////////////////////////////////////////////////////
GCurveEvent::GCurveEvent(wxEventType commandType, int id) 
		     : wxCommandEvent(commandType, id) 
{ 
} 


////////////////////////////////////
BEGIN_EVENT_TABLE(GCurve, wxPanel) 
	EVT_PAINT  (GCurve::OnPaint) 
	EVT_ERASE_BACKGROUND(GCurve::OnEraseBackground) 
	EVT_MOUSE_EVENTS (GCurve::OnMouse) 
END_EVENT_TABLE() 

///////////////////////////////////////////////////////////////////
GCurve::GCurve(wxWindow *parent, wxWindowID id, const wxPoint& pos)
       :wxPanel(parent, id, pos, wxSize(250,200), 0, wxT(""))
{
	SetBackgroundColour(wxColour(0,0,0));

	draggingNode  = false;

	lowLimiter = 0;
	highLimiter = 127;
	lowCompressor = 0;
	highCompressor = 127;
	lowPercent = 100;
	highPercent = 100;
}

////////////////////////////////////////////////////
void GCurve::OnPaint(wxPaintEvent &event) 
{
#ifndef MAC
	SetDoubleBuffered(false);
#endif //!MAC
	wxBufferedPaintDC dc(this); 
	
	dc.SetBackground(wxColour(0, 0, 0)); 
	dc.SetBackgroundMode(wxSOLID);
	dc.Clear();
	dc.SetBrush(*wxTRANSPARENT_BRUSH); 

	DrawGrid(dc);
	DrawCurve(dc);
	DrawPoints(dc);
} 

/////////////////////////////////////////////////////
void GCurve::OnEraseBackground( wxEraseEvent& event )
{

}

//////////////////////////////////////////
void GCurve::OnMouse(wxMouseEvent &event) 
{ 
	//how do we determine if the mouse in on the line?
	
	//Method 1:  Find Y in the line
	//We can provide the x coordinate of the mouse, take that coordinate,
	//and find the Y coordinate the coorisponds in the line. 

	//I.E.  Line = (0,100,0,100)
	// x = 50, so y = 50
	if(event.LeftDClick()){
		int mouseX = event.GetPosition().x;
		int mouseY = event.GetPosition().y;
	
		for(unsigned int i=0; i<points.size()-1; ++i){
			
			int LineX;
			int LineY;

			if(points[i+1].y != points[i].y){
				LineY = (((points[i+1].y - points[i].y) * (mouseX - points[i].x)) / (points[i+1].x - points[i].x)) + points[i].y;
				LineX = (((points[i+1].x - points[i].x) * (mouseY - points[i].y)) / (points[i+1].y - points[i].y)) + points[i].x;
			}
			else{
				//We crash if we try to use points[i+1].y != points[i].y when it equals 0;
				//???????
			}

			if(LineY < mouseY +4 && LineY > mouseY -4 ||
			   LineX < mouseX +4 && LineX > mouseX -4){

				   if(mouseX < points[i+1].x+4 && mouseX > points[i].x-4){

				    AddPoint(event.GetPosition());
					GridToVelocities();
					Refresh();

					GCurveEvent event(wxEVT_COMMAND_GCURVE, GetId()); 
					event.SetEventObject(this); 
					GetEventHandler()->ProcessEvent(event);

					return;
				}
			}
		}
	}

	if(event.RightDClick()){
		int mouseX = event.GetPosition().x;
		int mouseY = event.GetPosition().y;
		for(unsigned int i=1; i<points.size()-1; ++i){
			if(mouseX < points[i].x+4 && mouseX > points[i].x-4 &&
				mouseY < points[i].y+4 && mouseY > points[i].y-4){

					//Delete the node
					DeletePoint(i);
					GridToVelocities();
					Refresh();

					GCurveEvent event(wxEVT_COMMAND_GCURVE, GetId()); 
					event.SetEventObject(this); 
					GetEventHandler()->ProcessEvent(event);
			}
		}
	}

	if(event.LeftDown()){
		int mouseX = event.GetPosition().x;
		int mouseY = event.GetPosition().y;
		for(unsigned int i=1; i<points.size()-1; ++i){
			if(mouseX < points[i].x+4 && mouseX > points[i].x-4 &&
				mouseY < points[i].y+4 && mouseY > points[i].y-4){
					draggingNode = true;
					currentNode = i;
					if(UseMouseCapture()) {CaptureMouse();}
			}
		}
	}

	if(event.LeftUp() || (event.Leaving() && !UseMouseCapture())){ 
		draggingNode  = false; 

		
		if(HasCapture()){
			ReleaseMouse(); 
		}
		
	}

	if(draggingNode){
		if(event.Dragging()) {
			if(event.GetPosition().x > points[currentNode-1].x &&
			   event.GetPosition().x < points[currentNode+1].x){	
				points[currentNode].x = event.GetPosition().x;
				Refresh();
				GridToVelocities();

				GCurveEvent event(wxEVT_COMMAND_GCURVE, GetId()); 
				event.SetEventObject(this); 
				GetEventHandler()->ProcessEvent(event);
			}
			if(event.GetPosition().y > 0 &&
			   event.GetPosition().y < GetSize().y){
				points[currentNode].y = event.GetPosition().y;
				Refresh();
				GridToVelocities();

				GCurveEvent event(wxEVT_COMMAND_GCURVE, GetId()); 
				event.SetEventObject(this); 
				GetEventHandler()->ProcessEvent(event);
			}
		}
		else{ 
			return;
		}
	}


}

///////////////////////////////
bool GCurve::UseMouseCapture() 
{ 
	if(GetWindowStyle() & FDR_NO_MOUSE_CAPTURE) 
		return false; 
	else{
		return true; 
	} 
}

///////////////////////////////
void GCurve::DrawGrid(wxDC &dc)
{
	//highCompressor
	dc.SetPen(wxColour(0,0,200));
	dc.SetBrush(wxBrush(wxColour(0,0,200), wxSOLID));
	dc.DrawRectangle(0, 0, GetSize().x, GetSize().y - ( ( (double)GetSize().y / (double)127 ) * highCompressor) );

    //lowCompressor
	dc.DrawRectangle(0, GetSize().y - ( ( (double)GetSize().y / (double)127 ) * lowCompressor), GetSize().x, GetSize().y);

	//highPercent
	dc.SetPen(wxColour(128,0,255));
	dc.SetBrush(wxBrush(wxColour(128,0,255), wxSOLID));
	dc.DrawRectangle(0, 
					 (GetSize().y - ( ( (double)GetSize().y / (double)127 ) * highCompressor)) - 
					 (((double)GetSize().y / (double)127 ) * (((127 - highCompressor) * (100 - highPercent)) / 100)),
					 GetSize().x, 
					 (((double)GetSize().y / (double)127 ) * (((127 - highCompressor) * (100 - highPercent)) / 100)));
	
	//lowPercent
	dc.DrawRectangle(0, 
		             GetSize().y - ( ( (double)GetSize().y / (double)127 ) * lowCompressor), 
					 GetSize().x, 
					 (((double)GetSize().y / (double)127 ) * ((lowCompressor * (100 - lowPercent)) / 100)));
	
	//Draw minimum percent lines
	dc.DrawRectangle(0, 
					 GetSize().y - ( ( (double)GetSize().y / (double)127 ) * highCompressor) - 4,
					 GetSize().x, 
					 4);

	dc.DrawRectangle(0, 
					 GetSize().y - ( ( (double)GetSize().y / (double)127 ) * lowCompressor),
					 GetSize().x, 
					 4);

	//highLimiter
	dc.SetPen(wxColour(200,0,0));
	dc.SetBrush(wxBrush(wxColour(200,0,0), wxSOLID));
	dc.DrawRectangle(0, 0, GetSize().x, GetSize().y - ( ( (double)GetSize().y / (double)127 ) * highLimiter) );

    //lowLimiter
	dc.DrawRectangle(0, GetSize().y - ( ( (double)GetSize().y / (double)127 ) * lowLimiter), GetSize().x, GetSize().y);

	//Draw Grid
	dc.SetPen(wxColour(50,50,50));
	for(int i=1; i<32; ++i){
		dc.DrawLine((double)((double)GetSize().x / (double)32) * i, 0, (double)((double)GetSize().x / (double)32) * i, GetSize().y);
		dc.DrawLine(0, (double)((double)GetSize().y / (double)32) * i, GetSize().x, (double)((double)GetSize().y / (double)32) * i);
	}
}

////////////////////////////////
void GCurve::DrawCurve(wxDC &dc)
{
	if(points.size() > 0){
		dc.SetPen(wxPen(wxColour(200,200,200), 1, wxSOLID));
		for(unsigned int i=0; i<points.size()-1; ++i){
			dc.DrawLine(points[i].x, points[i].y, points[i+1].x, points[i+1].y);
			//DrawWuLine( &dc, points[i].x, points[i].y, points[i+1].x, points[i+1].y);
		}
	}
}

/////////////////////////////////
void GCurve::DrawPoints(wxDC &dc)
{
	dc.SetBrush(wxBrush(wxColour(0,200,0), wxSOLID));
	if(points.size() > 0){
		for(unsigned int i=1; i<points.size()-1; ++i){
			dc.DrawCircle(points[i].x, points[i].y, 3);
		}
	}
}

////////////////////////////////////
void GCurve::AddPoint(wxPoint point)
{
	std::vector<wxPoint>::iterator theIterator = points.begin();
	
	if(points.size() == 0){
		points.insert(theIterator, point);
		return;
	}

	
	for(unsigned int i=0; i<points.size()-1; ++i){
		theIterator++;
		if(point.x > points[i].x && point.x < points[i+1].x){		
			points.insert(theIterator, point);
			return;
		}	
	}
}

////////////////////////////////////
void GCurve::DeletePoint(int num)
{
	std::vector<wxPoint>::iterator theIterator = points.begin();

	for(int i=0; i<num; ++i){
		++theIterator;
	}
		
	points.erase(theIterator);
}

///////////////////////////////
void GCurve::GridToVelocities()
{
	//Here we take the curve and break it down into 127 layers across the grid.
	//FIXME - We eventually want to make the scale controllable by the class user.

	//First we must divide the width of the grid into 127.
	int point = 0;
	for(int i=1; i<128; ++i){ //128
		    int X = ((double)((double)GetSize().x / (double)127) * i);

			//Now that we know which pixes to check, we can get the y position of each line.
			if(X <= points[point+1].x){
				//then we are in range of this line 
			}
			else {
				point++;
			}

			//Now let's extract the Y axis frum the current line and post it to the velocities[].
			if((points[point+1].x - points[point].x) == 0){ //this is to stop potential INT_DIVIDE_BY_ZERO exceptions
				velocities[i-1] = ((( ((points[point+1].y - points[point].y) * (X - points[point].x)) ) + points[point].y) / ((double)GetSize().y / (double)127));
			}
			else{
				velocities[i-1] = ((( ((points[point+1].y - points[point].y) * (X - points[point].x)) / (points[point+1].x - points[point].x)) + points[point].y) / ((double)GetSize().y / (double)127));
			}
			velocities[i-1] = 127 - velocities[i-1];

			//Now lets respect the Compressors
			//We must also take in to account compress percents if we want that.
			if(velocities[i-1] < lowCompressor){
				velocities[i-1] = ((((lowCompressor - velocities[i-1]) * lowPercent) / 100) + velocities[i-1]);
			}
			if(velocities[i-1] > highCompressor){
				//FIXME - we need to come up with the right equasion to take percent into account.
				velocities[i-1] = ((((highCompressor - velocities[i-1]) * highPercent) / 100) + velocities[i-1]);
			}
	}
}

///////////////////////////////
void GCurve::VelocitiesToGrid()
{
	//This will be tricky
	//We need to take the velocities and plot out the grid.
}

///////////////////////////////////
void GCurve::SetLowLimiter(int num)
{
	lowLimiter = num;
	Refresh();
}

////////////////////////////////////
void GCurve::SetHighLimiter(int num)
{
	highLimiter = num;
	Refresh();
}

//////////////////////////////////////
void GCurve::SetLowCompressor(int num)
{
	lowCompressor = num;
	if(points.size() > 0){
		GridToVelocities();
	}
	Refresh();
}

///////////////////////////////////////
void GCurve::SetHighCompressor(int num)
{
	highCompressor = num;
	if(points.size() > 0){
		GridToVelocities();
	}
	Refresh();
}

//////////////////////////////////////
void GCurve::SetLowPercent(int num)
{
	lowPercent = num;
	if(points.size() > 0){
		GridToVelocities();
	}
	Refresh();
}

//////////////////////////////////////
void GCurve::SetHighPercent(int num)
{
	highPercent = num;
	if(points.size() > 0){
		GridToVelocities();
	}
	Refresh();
}







