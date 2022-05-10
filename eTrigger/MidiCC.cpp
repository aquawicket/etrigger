//// Midi.cpp ////////////////////////////////////////////////////////////////////
//
//
/////////////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "MidiCC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

////////////////////////////////////
BEGIN_EVENT_TABLE(MidiCC, wxWindow)
	EVT_PAINT  (MidiCC::OnPaint)
	EVT_ERASE_BACKGROUND(MidiCC::OnEraseBackground)
	EVT_GBUTTON(100, MidiCC::OnSetup)
	EVT_MENU(102, MidiCC::OnMenuDeleteTrack)
	EVT_MENU(103, MidiCC::OnMenuAddTrigger)
	EVT_MENU(104, MidiCC::OnMenuAddMidiCC)
	EVT_SET_FOCUS(MidiCC::OnFocus)
	EVT_KILL_FOCUS(MidiCC::OnKillFocus) 
	EVT_MOUSE_EVENTS (MidiCC::OnMouse) 
	EVT_MOUSEWHEEL(MidiCC::OnMouseWheel)
	EVT_GIMAGESELECTOR(105, MidiCC::OnImageChange)
	EVT_GTEXT(107, MidiCC::OnTextChange)
END_EVENT_TABLE() 

///////////////////////////////////////////////////////////////////////////////////////////////////////
MidiCC::MidiCC(TrackPanel *parent, TrackProc *ref, wxPoint pos, int num) 
		: wxWindow(parent, -1, pos, wxSize(1, 1), 0)
{
	trackProc = ref;
	trackNum = num;

	//GHelper will decide to use the image file or the built in xpm.
	image1 = new wxImage( ConvTowxImage(wxT("Data/track.png"), track_xpm) );
	image2 = new wxImage( ConvTowxImage(wxT("Data/track-focused.png"), track_focused_xpm) );

	text = new TextEdit(this, 107, wxPoint(12,30), wxSize(61, 37), wxNO_BORDER | wxTE_CENTRE | wxTE_MULTILINE | wxTE_NO_VSCROLL | wxTE_RICH , trackProc->n[trackNum].name ); 
	text->SetToolTip(wxT("Here you can rename the track."));	

	setup = new GButton(this, 100, wxPoint(6, 80), setup_xpm, setup_hover_xpm, setup_click_xpm, setup_focused_xpm, setup_hover_focused_xpm, setup_click_focused_xpm); 
	setup->focused = false;
	setup->SetToolTip(wxT("Setup this track's input and signal processing."));

	image = new GImageSelector(this, 105, wxPoint(11, 107), wxSize(60,60));
	image->SetImage(trackProc->n[trackNum].image);

	meter = new GMeter(this, -1, wxPoint(36, 215), wxSize(10,250), false);

	focused = false;
	counter = 0;	

	//SetBackgroundColour(wxColour(99,99,99));
	SetSize(82, 510);

	if(trackProc->preLoad){
		midiCCDialog = new MidiCCDialog(this);
	}

	draggingTrack = false;
}

///////////////////
MidiCC::~MidiCC() 
{ 
	delete image1;
	delete image2;
	delete text;

	if(focused && trackProc != NULL){
		focused = false;
		Refresh();
		//trackProc->focused = 0;
		//trackProc->trackPanel->trackMenu->Enable(102, false);
		//trackProc->trackPanel->mainPanel->menuPanel->tracksMenu->Enable(303, false);
	}
	//ClearBackground();

	if(FindWindowByName(wxString::Format(wxT("Track %d Settings"), trackNum))){
		delete midiCCDialog;
	}
}

void MidiCC::OnEraseBackground(wxEraseEvent& event)
{
	
}

////////////////////////////////////////////////////
void MidiCC::OnPaint(wxPaintEvent &event) 
{ 
#ifndef MAC
	SetDoubleBuffered(false);
#endif !MAC
    wxBufferedPaintDC dc(this); 
    DrawBackground(dc);
} 

//////////////////////////////////////
void MidiCC::DrawBackground(wxDC &dc)
{
	if(focused == false){dc.DrawBitmap( *image1, 0, 0); }
	if(focused == true){dc.DrawBitmap( *image2, 0, 0); } 
}

//////////////////////////////////
void MidiCC::SetTrackNum(int num)
{
	if(FindWindowByName(wxString::Format(wxT("Track %d Settings"), trackNum))){
		midiCCDialog->SetTitle(wxString::Format(wxT("Track %d Settings"), num));
	}
	trackNum = num;
}

//////////////////////////////////////////
void MidiCC::OnSetup(GButtonEvent &event)
{
	if(!FindWindowByName(wxString::Format(wxT("Track %d Settings"), trackNum))){
			midiCCDialog = new MidiCCDialog(this);
			midiCCDialog->Show();
			midiCCDialog->SetFocus();
	}
	else{
			midiCCDialog->Show();
			midiCCDialog->SetFocus();
	}
}

//////////////////////////////////////////////////////
void MidiCC::OnMenuDeleteTrack(wxCommandEvent &event)
{
	trackProc->DeleteTrack(trackNum, true);
}

/////////////////////////////////////////////////////
void MidiCC::OnMenuAddTrigger(wxCommandEvent &event)
{
	trackProc->AddTrigger();
}


////////////////////////////////////////////////////
void MidiCC::OnMenuAddMidiCC(wxCommandEvent &event)
{
	trackProc->AddMidiCC();
}


//////////////////////////////////////////
void MidiCC::OnFocus(wxFocusEvent &event)
{	
	focused = true;
	setup->focused = true;
    Refresh();
	trackProc->focused = trackNum;
	trackProc->trackPanel->trackMenu->Enable(102, true);
	trackProc->trackPanel->mainPanel->menuPanel->tracksMenu->Enable(303, true);
}

//////////////////////////////////////////////
void MidiCC::OnKillFocus(wxFocusEvent &event)
{
	focused = false;
	setup->focused = false;
    Refresh();
	trackProc->trackPanel->trackMenu->Enable(102, false);
	trackProc->trackPanel->mainPanel->menuPanel->tracksMenu->Enable(303, false);
}

//////////////////////////////////////////
void MidiCC::OnMouse(wxMouseEvent &event) 
{
	
	if(event.LeftDown()){ 
		dropSpot = trackNum;
		SetFocus();
		mousePoint = event.GetPosition(); 
		//draggingTrack  = true;  //Moving tracks disabled for now.
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
				Move(-41, winPos.y);
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
		PopupMenu(trackProc->trackMenu, wxDefaultPosition);
	}
}

////////////////////////////////////////////
void MidiCC::OnMouseWheel(wxMouseEvent &event)
{	
	//don't let the event trickle down to the parent.
}

///////////////////////////////
bool MidiCC::UseMouseCapture() 
{ 
	if(GetWindowStyle() & FDR_NO_MOUSE_CAPTURE) 
		return false; 
	else{
		return true; 
	} 
} 

///////////////////////////////////////////////////////
void MidiCC::OnImageChange(GImageSelectorEvent &event)
{
	trackProc->n[trackNum].image = image->GetImage();
}

////////////////////////////
void MidiCC::UpdateDialog()
{
	text->SetValue(trackProc->n[trackNum].name);
	image->SetImage(trackProc->n[trackNum].image);
}

/////////////////////////////////////////////
void MidiCC::OnTextChange(GTextEvent &event)
{
	trackProc->n[trackNum].name = text->GetValue();
}