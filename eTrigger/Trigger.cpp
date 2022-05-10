//// Trigger.cpp ////////////////////////////////////////////////////////////////////
//
//
/////////////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "Trigger.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

////////////////////////////////////
BEGIN_EVENT_TABLE(Trigger, wxWindow)
	//EVT_PAINT  (Trigger::OnPaint)
	//EVT_ERASE_BACKGROUND(Trigger::OnEraseBackground)
	EVT_GBUTTON(100, Trigger::OnSetup)
	EVT_MENU(102, Trigger::OnMenuDeleteTrack)
	EVT_MENU(103, Trigger::OnMenuAddTrigger)
	EVT_MENU(104, Trigger::OnMenuAddMidiCC)
	EVT_SET_FOCUS(Trigger::OnFocus)
	EVT_KILL_FOCUS(Trigger::OnKillFocus) 
	EVT_GSLIDER(105, Trigger::OnSlider)
	EVT_MOUSE_EVENTS (Trigger::OnMouse) 
	EVT_MOUSEWHEEL(Trigger::OnMouseWheel)
	EVT_GIMAGESELECTOR(106, Trigger::OnImageChange)
	EVT_GTEXT(107, Trigger::OnTextChange)
END_EVENT_TABLE() 

///////////////////////////////////////////////////////////////////////////////////////////////////////
Trigger::Trigger(TrackPanel *parent, TrackProc *ref, wxPoint pos, int num) 
		: wxWindow(parent, -1, pos, wxSize(1,1), 0)
{
	trackProc = ref;
	trackNum = num;

	//GHelper will decide to use the image file or the built in xpm.
	//image1 = new wxImage( ConvTowxImage(wxT("Data/track.png"), track_xpm) );
	//image2 = new wxImage( ConvTowxImage(wxT("Data/track-focused.png"), track_focused_xpm) );
	background = new GImage(this, -1, wxPoint(0,0), wxT("Data/track.png"));

	text = new TextEdit(background, 107, wxPoint(12,30), wxSize(61, 37), wxNO_BORDER | wxTE_CENTRE | wxTE_MULTILINE | wxTE_NO_VSCROLL | wxTE_RICH , trackProc->n[trackNum].name ); 
	text->SetToolTip(wxT("Here you can rename the track."));

	setup = new GButton(background, 100, wxPoint(6, 80), 
		setup_xpm, 
		setup_hover_xpm, 
		setup_click_xpm, 
		setup_focused_xpm, 
		setup_hover_focused_xpm, 
		setup_click_focused_xpm); 
	setup->focused = false;\
	setup->SetToolTip(wxT("Setup this track's input and signal processing."));

	image = new GImageSelector(background, 106, wxPoint(11, 107), wxSize(60,60)); 
	image->SetImage(trackProc->n[trackNum].image);

	meter = new GMeter(background, -1, wxPoint(60, 215), wxSize(10,250), true);

	slider = new GSlider(background, 105, wxPoint(6, 176), wxNO_BORDER | wxTRANSPARENT_WINDOW , wxT(""), 
		ConvTowxImage(wxT("Data/slider.png"), slider_xpm), 
		ConvTowxImage(wxT("Data/slider-focused.bmp"), slider_focused_xpm), 
		ConvTowxImage(wxT("Data/knob.bmp"), knob_xpm), 
		ConvTowxImage(wxT("Data/knob.bmp"), knob_xpm), 
		ConvTowxImage(wxT("Data/knob.bmp"), knob_xpm), 
		ConvTowxImage(wxT("Data/knob-focused.bmp"), knob_focused_xpm));
	slider->SetRange(0, 200); 
	slider->SetValue(0, trackProc->n[trackNum].masterGain);
	slider->SetDefault(0, 100);

	focused = false;
	counter = 0;	

	//SetBackgroundColour(wxColour(99,99,99));
	SetSize(82, 510);

	if(trackProc->preLoad){
		triggerDialog = new TriggerDialog(this);
	}

	draggingTrack = false;
}

///////////////////
Trigger::~Trigger() 
{ 
	//delete image1;
	//delete image2;
	
	delete text;

	if(focused){
		focused = false;
		slider->backFocused = false;
#ifndef MAC
		image->backFocused = false;
#endif //!MAC
		Refresh();
		//trackProc.focused = 0;
		//trackProc.trackPanel->trackMenu->Enable(102, false);
		//trackProc.trackPanel->mainPanel->menuPanel->tracksMenu->Enable(303, false);
	}
	//ClearBackground(); //no good for MAC

	if(FindWindowByName(wxString::Format(wxT("Track %d Settings"), trackNum))){
		delete triggerDialog;
	}
	delete background;
}

void Trigger::OnEraseBackground(wxEraseEvent& event)
{
	
}

////////////////////////////////////////////////////
void Trigger::OnPaint(wxPaintEvent &WXUNUSED(event)) 
{ 
#ifndef MAC
	//SetDoubleBuffered(false);
#endif //!MAC
	//wxBufferedPaintDC dc(this); 
	wxPaintDC dc(this);
	DrawBackground(dc);
} 

//////////////////////////////////////
void Trigger::DrawBackground(wxDC &dc)
{
	//if(focused == false){dc.DrawBitmap( *image1, 0, 0, true); }
	//if(focused == true){dc.DrawBitmap( *image2, 0, 0, true); } 
}

//////////////////////////////////
void Trigger::SetTrackNum(int num)
{
	if(FindWindowByName(wxString::Format(wxT("Track %d Settings"), trackNum))){
		triggerDialog->SetTitle(wxString::Format(wxT("Track %d Settings"), num));
	}
	trackNum = num;
}

//////////////////////////////////////////
void Trigger::OnSetup(GButtonEvent &event)
{
	if(!FindWindowByName(wxString::Format(wxT("Track %d Settings"), trackNum))){
			triggerDialog = new TriggerDialog(this);
			triggerDialog->Show();
			triggerDialog->SetFocus();
	}
	else{
			triggerDialog->Show();
			triggerDialog->SetFocus();
	}
}

//////////////////////////////////////////////////////
void Trigger::OnMenuDeleteTrack(wxCommandEvent &event)
{
	trackProc->DeleteTrack(trackNum, true);
}

/////////////////////////////////////////////////////
void Trigger::OnMenuAddTrigger(wxCommandEvent &event)
{
	trackProc->AddTrigger();
}

////////////////////////////////////////////////////
void Trigger::OnMenuAddMidiCC(wxCommandEvent &event)
{
	trackProc->AddMidiCC();
}

//////////////////////////////////////////
void Trigger::OnFocus(wxFocusEvent &event)
{	
	focused = true;
	setup->focused = true;
	slider->backFocused = true;
#ifndef MAC
	image->backFocused = true;
#endif //!MAC
	Refresh();
	trackProc->focused = trackNum;
	trackProc->trackPanel->trackMenu->Enable(102, true);
	trackProc->trackPanel->mainPanel->menuPanel->tracksMenu->Enable(303, true);
}

//////////////////////////////////////////////
void Trigger::OnKillFocus(wxFocusEvent &event)
{
	focused = false;
	setup->focused = false;
	slider->backFocused = false;
#ifndef MAC
	image->backFocused = false;
#endif //!MAC
	Refresh();
	trackProc->trackPanel->trackMenu->Enable(102, false);
	trackProc->trackPanel->mainPanel->menuPanel->tracksMenu->Enable(303, false);
}

///////////////////////////////////////////
void Trigger::OnSlider(GSliderEvent &event) 
{ 
	//Master volume
	trackProc->n[trackNum].masterGain = (int)event.GetValue();
	trackProc->n[trackNum].masterVolume = (((int)event.GetValue() * 127) / 100);
}

//////////////////////////////////////////
void Trigger::OnMouse(wxMouseEvent &event) 
{
	
	if(event.LeftDown()){ 
		dropSpot = trackNum;
		SetFocus();
		mousePoint = event.GetPosition(); 
		//draggingTrack = true;   //Moving tracks disabled for now.
		trackPoint = GetPosition(); //remember original position
		if(UseMouseCapture()) {CaptureMouse();}
	}

	//if(event.LeftIsDown()){

	//}

	if(event.LeftUp() || (event.Leaving() && !UseMouseCapture())) 
	{
		if(trackNum != dropSpot){
			trackProc->MoveTrack(trackNum, dropSpot);
		}
		else{
			Move(trackPoint);
		}
		
		draggingTrack  = false; 

		if(HasCapture()) {ReleaseMouse();}
		return; 
	}

	if(event.Dragging()){
		if(draggingTrack){
			wxPoint temp = event.GetPosition();
			wxPoint winPos = GetPosition();
			
			if(winPos.x + temp.x - mousePoint.x < -41){
				Move(-41, winPos.y + 0);
			}
			else{
				Move(winPos.x + temp.x - mousePoint.x, winPos.y + 0);
			}

			if(trackProc->DetectLanding(trackNum, winPos.x + temp.x - mousePoint.x)){	dropSpot = trackProc->DetectLanding(trackNum, winPos.x + temp.x - mousePoint.x); }
		}
		else
			return;
	}

	if(event.RightDown() && !draggingTrack){
		SetFocus();
	}

	if(event.RightUp() && !draggingTrack){
		PopupMenu(trackProc->trackMenu, wxDefaultPosition); //FIXME crashes app on linux when deleting a track.
	}
}

////////////////////////////////////////////
void Trigger::OnMouseWheel(wxMouseEvent &event)
{	
	//don't let the event trickle down to the parent.
}

///////////////////////////////
bool Trigger::UseMouseCapture() 
{ 
	if(GetWindowStyle() & FDR_NO_MOUSE_CAPTURE) 
		return false;
	else{
		return true;
	} 
} 

///////////////////////////////////////////////////////
void Trigger::OnImageChange(GImageSelectorEvent &event)
{
	trackProc->n[trackNum].image = image->GetImage();
}

////////////////////////////
void Trigger::UpdateDialog()
{
	text->SetValue(trackProc->n[trackNum].name);
	image->SetImage(trackProc->n[trackNum].image);
	slider->SetValue(0, trackProc->n[trackNum].masterGain);
}

/////////////////////////////////////////////
void Trigger::OnTextChange(GTextEvent &event)
{
	trackProc->n[trackNum].name = text->GetValue();
}