//// GObjectPanel.cpp //////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////

#include "GObjectPanel.h"

BEGIN_EVENT_TABLE(GObjectPanel, wxPanel)
	EVT_PAINT  (GObjectPanel::OnPaint)
	EVT_MOUSE_EVENTS (GObjectPanel::OnMouse)
END_EVENT_TABLE()

int USEGRAPHICSCONTEXT = 0;

////////////////////////////////////////////
GObjectPanel::GObjectPanel(wxWindow* parent)
	:wxPanel(parent, -1, wxPoint(0,0), wxSize(parent->GetSize().x,parent->GetSize().y), wxBORDER_NONE, wxT("GObjectPanel"))
{ 
	wxInitAllImageHandlers();
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	SetDoubleBuffered(true);

	timer = new GTimer(this);
} 

/////////////////////////////
GObjectPanel::~GObjectPanel()
{
	timer->Stop();
	delete timer;
	for (unsigned int i = 0; i < object.size(); ++i) { 
		delete object[i]; 
	} 
	object.clear();

}

///////////////////////////////////////////////
void GObjectPanel::OnPaint(wxPaintEvent &event)
{ 
	//wxAutoBufferedPaintDC dc(this);  //25% cpu 
	//wxBufferedPaintDC dc(this);   //24% cpu

	//dc->Clear();
	if(1 == 1){
		wxAutoBufferedPaintDC dc(this);
		dc.Clear();
		if(USEGRAPHICSCONTEXT){
			wxGraphicsContext *gc = wxGraphicsContext::Create( dc );
			for(unsigned int i=0; i<object.size(); ++i){
				object[i]->Render(*gc);
			}
			delete gc;
		}
		else{
			for(unsigned int i=0; i<object.size(); ++i){
				object[i]->Render(dc);
			}
		}
	}

	
   
}

///////////////////////////////////////////////
void GObjectPanel::OnMouse(wxMouseEvent &event)
{
	for(int i=object.size()-1; i>-1; --i){
		if(object[i]->OnMouse(event)){return;}
	}
}


////////////////////////////////////////////
GTimer::GTimer(wxWindow *parent) : wxTimer()
{
	gObjectPanel = (GObjectPanel*)parent;
	Start(40,false);
}

/////////////////////
void GTimer::Notify()
{
	gObjectPanel->Refresh();
}