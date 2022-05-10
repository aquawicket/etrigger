//// TriggerDialog.cpp ////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "VelToPosAvgDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

///////////////////////////////////////////
BEGIN_EVENT_TABLE(VelToPosAvgDlg, wxDialog) 
	EVT_PAINT  (VelToPosAvgDlg::OnPaint) 
END_EVENT_TABLE() 

/////////////////////////////////////////////
VelToPosAvgDlg::VelToPosAvgDlg(Trigger *trig)
			   :wxDialog(trig, -1, wxT("Velocity / Position Average"), wxDefaultPosition, wxSize(500, 300), wxDEFAULT_DIALOG_STYLE)
{
	trigger = trig;

	CentreOnScreen(wxBOTH);
	SetBackgroundColour(wxColour(255,255,255));

	curve = new GCurve(this, 100, wxPoint(160,20));
	curve->points.push_back( wxPoint(0, 200) );
	curve->points.push_back( wxPoint(250, 0) );

	//timer = new AvgTimer(this);
}

/////////////////////////////////
VelToPosAvgDlg::~VelToPosAvgDlg()
{
	//timer->Stop();
	//delete timer;
	Destroy();
}

///////////////////////////////////////////////////////////
void VelToPosAvgDlg::OnPaint(wxPaintEvent &WXUNUSED(event)) 
{ 
#ifndef MAC
	SetDoubleBuffered(false);
#endif //!MAC
	wxBufferedPaintDC dc(this); 
	dc.Clear();
	DrawGrid(dc);
	DrawAverage(dc);
}

///////////////////////////////////////
void VelToPosAvgDlg::DrawGrid(wxDC &dc)
{
	dc.SetPen(wxColour(0,0,0));
	dc.SetBrush(wxBrush(wxColour(0,0,0), wxSOLID));
	dc.DrawLine(20, 20, 20, 147);
	dc.DrawLine(20, 147, 147, 147);
}

//////////////////////////////////////////
void VelToPosAvgDlg::DrawAverage(wxDC &dc)
{
	//the grid is a simple 127 x 127 grid to place our dots.
	//note: eventually we may want to expand this.

	//Lets get the average velocity for each position.
	//But's lets include all 1000 of the history to get the average for each position.

	//Lets draw the average.

	//draw by position 0 to 127.
	//find the average velocity for each position.
	//find the average position for each velocity. 
	int average = 0;
	for(int n=0; n<127; ++n){ //go through each position (0-127)
		int vCount = 0;
		int vTotal = 0;
		int pCount = 0;
		int pTotal = 0;
		for(int h=0; h<999; ++h){ //go through all 1000 velocity histories. 
			int v = trigger->trackProc->n[trigger->trackNum].velToPosAvg[n][h];
			int p = trigger->trackProc->n[trigger->trackNum].posToVelAvg[n][h];
				//x now equals that number. 
	
				//find the average of p with h x 1000.   don't inclue the 0'
			    
			    //add all 1000 together divided by 1000

				//Draw each dot from (0-127 x 0-127) on the grid.	
				if(v != 0){
					vCount++;
					vTotal += v;
				}

				if(p != 0){
					pCount++;
					pTotal += p;
				}
		}

		if(vCount != 0){
			average = vTotal / vCount;
			//FIXME - have to convert position  and average to the grid size
			curve->AddPoint(wxPoint((n * curve->GetSize().x) / 127  , (average * curve->GetSize().y) / 127));
			curve->GridToVelocities();
			curve->Refresh();
			//lets place the dot that = the average on the grid.
			dc.SetPen(wxColour(200,0,0));
			dc.SetBrush(wxBrush(wxColour(200,0,0), wxSOLID));
			dc.DrawLine(21+n, 19+average, 22+n, 20+average);
		}

		if(pCount != 0){
			average = pTotal / pCount;
			//curve->AddPoint(wxPoint(n, average));
			//curve->GridToVelocities();
			//curve->Refresh();
			//lets place the dot that = the average on the grid.
			dc.SetPen(wxColour(0,0,200));
			dc.SetBrush(wxBrush(wxColour(0,0,200), wxSOLID));
			dc.DrawLine(21+n, 19+average, 22+n, 20+average);
		}
	}
}

/////////////////////////////
void VelToPosAvgDlg::Notify()
{
	Refresh();
}