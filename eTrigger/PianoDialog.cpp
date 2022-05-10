//// PianoDialog.cpp //////////////////////////////////////////////////////////////////////////
//
//   A Visual Piano that reacts to input.
//
//   The piano is 5.3 time the size of the small scroller piano.
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "PianoDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////
BEGIN_EVENT_TABLE(PianoDialog, wxDialog)
    EVT_SIZE(PianoDialog::OnSize) 
	EVT_MOVE(PianoDialog::OnMove) 
	EVT_CLOSE(PianoDialog::OnClose)
END_EVENT_TABLE() 

//////////////////////////////
PianoDialog::PianoDialog(MainPanel* parent)
	  :wxDialog(parent, -1, wxT("Piano"), wxDefaultPosition, wxSize(600, 300), 
	   wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER )
{
	//CentreOnScreen(wxBOTH);
	 /*
	#ifdef WIN32
	position = GetScreenPosition();
	#endif
	#ifdef MAC
	position = GetPosition();
	#endif
	size = GetSize();
	shown = IsShown();
	*/

	mainPanel = parent;
	SetMinSize(wxSize(600,300));
	SetMaxSize(wxSize(3137,300));
	SetBackgroundColour(wxColour(30,30,30));
	pianoPic = new Keyboard(this, -1, wxPoint(0,0), piano_xpm);
	pianoSmall = new GImage(this, -1, wxPoint(0,220), pianoSmall_xpm);

	//transparent dragging window
	transWindow = new TranparentWindow(this, -1, pianoSmall->GetScreenPosition(), wxSize(100,40), wxSTAY_ON_TOP );
	transWindow->SetBackgroundColour(wxColour(0,0,100));
	transWindow->SetTransparent(120);
	transWindow->Show();

	pianoSmall->Move( ((GetSize().x - 599) / 2), 220);
	transWindow->SetSize( (GetSize().x / 5.3),40);
	transWindow->Move(pianoSmall->GetScreenPosition().x, pianoSmall->GetScreenPosition().y);

	for(int i=0; i<128; ++i){
		keyDown[i] = NULL;
	}
}

////////////////////////////////////////
void PianoDialog::OnClose(wxCloseEvent &event)
{
	//if(mainPanel->trackProc->preLoad){
	Hide(); 
	transWindow->Hide();
	//}else{Destroy();}
}

//////////////////////////////////////
void PianoDialog::OnSize(wxSizeEvent &event)
{
	pianoSmall->Move( ((GetSize().x - 599) / 2), 220);
	
	transWindow->SetSize( (GetSize().x / 5.3),40);

	// FIXME - The piano should not be allowed to resize past the end of the last key.
	transWindow->Move(GetScreenPosition().x + ((GetSize().x - 599) / 2) + 4 - (pianoPic->GetPosition().x / 5.3),
		              pianoSmall->GetScreenPosition().y);

	/*
	shown = true;
	#ifdef WIN32
	position = GetScreenPosition();
	#endif
	#ifdef MAC
	position = GetPosition();
	#endif
	size = GetSize();
	event.Skip();
	*/
}

//////////////////////////////////////
void PianoDialog::OnMove(wxMoveEvent &event)
{
	pianoSmall->Move( ((GetSize().x - 599) / 2), 220);
	
	transWindow->SetSize( (GetSize().x / 5.3),40);

	transWindow->Move(GetScreenPosition().x + ((GetSize().x - 599) / 2) + 4 - (pianoPic->GetPosition().x / 5.3),
		              pianoSmall->GetScreenPosition().y);

	/*
	shown = true;
	#ifdef WIN32
	position = GetScreenPosition();
	#endif
	#ifdef MAC
	position = GetPosition();
	#endif
	size = GetSize();
	event.Skip();
	*/
}

//////////////////////////////////
void PianoDialog::KeyDown(int num)
{
	int step = 0;
	int pos = 0;

	for(int i=0; i<11; ++i){
		if(num == 0 + step){
			if(keyDown[num] == NULL){
				keyDown[num] = new GImage(this, -1, wxPoint(5 + pianoPic->GetPosition().x + pos,37), keyCDown_xpm);
			}
			else{keyDown[num]->Show();}
		}
		if(num == 1 + step){
			if(keyDown[num] == NULL){
				keyDown[num] = new GImage(this, -1, wxPoint(32 + pianoPic->GetPosition().x + pos,37), blackKeyDown_xpm);
			}
			else{keyDown[num]->Show();}
		}
		if(num == 2 + step){
			if(keyDown[num] == NULL){
				keyDown[num] = new GImage(this, -1, wxPoint(47 + pianoPic->GetPosition().x + pos,37), keyDDown_xpm);
			}
			else{keyDown[num]->Show();}
		}
		if(num == 3 + step){
			if(keyDown[num] == NULL){
				keyDown[num] = new GImage(this, -1, wxPoint(84 + pianoPic->GetPosition().x + pos,37), blackKeyDown_xpm);
			}
			else{keyDown[num]->Show();}
		}
		if(num == 4 + step){
			if(keyDown[num] == NULL){
				keyDown[num] = new GImage(this, -1, wxPoint(89 + pianoPic->GetPosition().x + pos,37), keyEDown_xpm);
			}
			else{keyDown[num]->Show();}
		}
		if(num == 5 + step){
			if(keyDown[num] == NULL){
				keyDown[num] = new GImage(this, -1, wxPoint(131 + pianoPic->GetPosition().x + pos,37), keyFDown_xpm);
			}
			else{keyDown[num]->Show();}
		}
		if(num == 6 + step){
			if(keyDown[num] == NULL){
				keyDown[num] = new GImage(this, -1, wxPoint(157 + pianoPic->GetPosition().x + pos,37), blackKeyDown_xpm);
			}
			else{keyDown[num]->Show();}
		}
		if(num == 7 + step){
			if(keyDown[num] == NULL){
				keyDown[num] = new GImage(this, -1, wxPoint(172 + pianoPic->GetPosition().x + pos,37), keyGDown_xpm);
			}
			else{keyDown[num]->Show();}
		}
		if(num == 8 + step){
			if(keyDown[num] == NULL){
				keyDown[num] = new GImage(this, -1, wxPoint(204 + pianoPic->GetPosition().x + pos,37), blackKeyDown_xpm);
			}
			else{keyDown[num]->Show();}
		}
		if(num == 9 + step){
			if(keyDown[num] == NULL){
				keyDown[num] = new GImage(this, -1, wxPoint(214 + pianoPic->GetPosition().x + pos,37), keyADown_xpm);
			}
			else{keyDown[num]->Show();}
		}
		if(num == 10 + step){
			if(keyDown[num] == NULL){
				keyDown[num] = new GImage(this, -1, wxPoint(251 + pianoPic->GetPosition().x + pos,37), blackKeyDown_xpm);
			}
			else{keyDown[num]->Show();}
		}
		if(num == 11 + step){
			if(keyDown[num] == NULL){
				keyDown[num] = new GImage(this, -1, wxPoint(256 + pianoPic->GetPosition().x + pos,37), keyBDown_xpm);
			}
			else{keyDown[num]->Show();}
		}
		

		step = step + 12;
		pos = pos + 292;
	}
}

void PianoDialog::KeyUp(int num)
{
	if(keyDown[num] != NULL){
		keyDown[num]->Hide();
	}
}

void PianoDialog::AlignKeys()
{
	for(int i=0; i<128; ++i){
		delete keyDown[i];
		keyDown[i] = NULL;
	}
}


void PianoDialog::OutputNote(int num)
{
	std::vector<unsigned char>pianoOutput(3);
	pianoOutput[0] = 9 + 143;
	pianoOutput[1] = num;
	pianoOutput[2] = 64;

	if(mainPanel->midi->midiout.size() > 0){
		for(unsigned int c=0; c < mainPanel->midi->midiout.size(); ++c){
			mainPanel->midi->midiout[c]->sendMessage(&pianoOutput);
		}
	}
}






/////////////////////////////////////////////
BEGIN_EVENT_TABLE(TranparentWindow, wxDialog)
	EVT_MOUSE_EVENTS(TranparentWindow::OnMouse) 
END_EVENT_TABLE() 

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TranparentWindow::TranparentWindow(PianoDialog* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
				  :wxDialog(parent, id, wxT(""), pos, size, style, wxT("") )
{
	pianoDialog = parent;
}

/////////////////////////////////////////
bool TranparentWindow::UseMouseCapture() 
{ 
	if(GetWindowStyle() & FDR_NO_MOUSE_CAPTURE) 
		return false; 
	else{
		return true; 
	} 
} 

///////////////////////////////////////////////////
void TranparentWindow::OnMouse(wxMouseEvent &event) 
{
	if(event.LeftDown()){ 
		mousePoint = event.GetPosition(); 

		dragging  = true; 
		if(UseMouseCapture()) {CaptureMouse();}
	}

	if(event.LeftIsDown()){

	}

	if(event.LeftUp() || (event.Leaving() && !UseMouseCapture())) 
	{ 
		dragging  = false; 
		if(HasCapture()) {ReleaseMouse();}
		pianoDialog->AlignKeys();
		return; 
	} 

	if(event.Dragging()){
		if(dragging){
	
			if(GetPosition().x + event.GetPosition().x - mousePoint.x < pianoDialog->pianoSmall->GetScreenPosition().x){
				Move(pianoDialog->pianoSmall->GetScreenPosition().x, pianoDialog->pianoSmall->GetScreenPosition().y);
				pianoDialog->pianoPic->Move((pianoDialog->pianoSmall->GetScreenPosition().x - GetPosition().x)*5.3, 0);
				pianoDialog->AlignKeys();
			}
			else if(GetPosition().x + event.GetPosition().x - mousePoint.x + GetSize().x > pianoDialog->pianoSmall->GetScreenPosition().x + pianoDialog->pianoSmall->GetSize().x){
				Move(pianoDialog->pianoSmall->GetScreenPosition().x + pianoDialog->pianoSmall->GetSize().x - GetSize().x, pianoDialog->pianoSmall->GetScreenPosition().y);
				pianoDialog->pianoPic->Move((pianoDialog->pianoSmall->GetScreenPosition().x - GetPosition().x)*5.3, 0);
				pianoDialog->AlignKeys();
			}
			else{
				Move(GetPosition().x + event.GetPosition().x - mousePoint.x, pianoDialog->pianoSmall->GetScreenPosition().y);
				pianoDialog->pianoPic->Move((pianoDialog->pianoSmall->GetScreenPosition().x - GetPosition().x)*5.3, 0);
				pianoDialog->AlignKeys();
			}
		}
		else 
			return; 
	}
}





/////////////////////////////////////////////
BEGIN_EVENT_TABLE(Keyboard, GImage)
	EVT_MOUSE_EVENTS(Keyboard::OnMouse) 
END_EVENT_TABLE() 

///////////////////////////////////////////////////////////////////////////////////////////
Keyboard::Keyboard(PianoDialog *parent, wxWindowID id, const wxPoint& pos, const char** image)
         :GImage(parent, id, pos, image)
{
	pianoDialog = parent;
}

///////////////////////////////////////////
void Keyboard::OnMouse(wxMouseEvent &event)
{
	if(event.LeftDown() || event.LeftDClick()){ 
		//find the key

		wxPoint position = event.GetPosition();
		
		if(position.y > 39){
			//OutputDebugString(wxString::Format("X-%d Y-%d\n",position.x, position.y));
			int step = 0;
			int num = 0;

			for(int i=0; i<11; ++i){
				if(position.y > 133){
					if(position.x > 5 + step && position.x < 47 + step){pianoDialog->OutputNote(num); pianoDialog->KeyDown(num);}
					if(position.x > 46 + step && position.x < 89 + step){pianoDialog->OutputNote(num + 2); pianoDialog->KeyDown(num + 2);}
					if(position.x > 88 + step && position.x < 131 + step){pianoDialog->OutputNote(num + 4); pianoDialog->KeyDown(num + 4);}
					if(position.x > 130 + step && position.x < 172 + step){pianoDialog->OutputNote(num + 5); pianoDialog->KeyDown(num + 5);}
					if(position.x > 171 + step && position.x < 214 + step){pianoDialog->OutputNote(num + 7); pianoDialog->KeyDown(num + 7);}
					if(position.x > 213 + step && position.x < 256 + step){pianoDialog->OutputNote(num + 9); pianoDialog->KeyDown(num + 9);}
					if(position.x > 255 + step && position.x < 298 + step){pianoDialog->OutputNote(num + 11); pianoDialog->KeyDown(num + 11);}
				}
				else{
					if(position.x > 5 + step && position.x < 30 + step){pianoDialog->OutputNote(num); pianoDialog->KeyDown(num);}
					if(position.x > 29 + step && position.x < 55 + step){pianoDialog->OutputNote(num + 1); pianoDialog->KeyDown(num + 1);}
					if(position.x > 54 + step && position.x < 81 + step){pianoDialog->OutputNote(num + 2); pianoDialog->KeyDown(num + 2);}
					if(position.x > 80 + step && position.x < 107 + step){pianoDialog->OutputNote(num + 3); pianoDialog->KeyDown(num + 3);}
					if(position.x > 106 + step && position.x < 131 + step){pianoDialog->OutputNote(num + 4); pianoDialog->KeyDown(num + 4);}
					if(position.x > 130 + step && position.x < 155 + step){pianoDialog->OutputNote(num + 5); pianoDialog->KeyDown(num + 5);}
					if(position.x > 154 + step && position.x < 180 + step){pianoDialog->OutputNote(num + 6); pianoDialog->KeyDown(num + 6);}
					if(position.x > 179 + step && position.x < 202 + step){pianoDialog->OutputNote(num + 7); pianoDialog->KeyDown(num + 7);}
					if(position.x > 201 + step && position.x < 227 + step){pianoDialog->OutputNote(num + 8); pianoDialog->KeyDown(num + 8);}
					if(position.x > 226 + step && position.x < 249 + step){pianoDialog->OutputNote(num + 9); pianoDialog->KeyDown(num + 9);}
					if(position.x > 248 + step && position.x < 273 + step){pianoDialog->OutputNote(num + 10); pianoDialog->KeyDown(num + 10);}
					if(position.x > 272 + step && position.x < 298 + step){pianoDialog->OutputNote(num + 11); pianoDialog->KeyDown(num + 11);}
				}

				step = step + 292;
				num = num + 12;
			}

			//C-2  = 6   - 29 (top part)
			//C-2  = 6   - 46 (bottom part)
			
			//C#-2 = 30  - 54 

			//D-2  = 55  - 80 (top part)
			//D-2  = 47  - 88 (bottom part)

			//D#-2 = 81  - 106

			//E-2  = 107 - 130 (top part)
			//E-2  = 89  - 130  (bottom part)

			//F-2  = 131 - 154 (top part)
			//F-2  = 131 - 171 (bottom part)

			//F#-2 = 155 - 179

			//G-2  = 180 - 201 (top part)
			//G-2  = 172 - 213 (bottom part)

			//G#-2 = 202 - 226

			//A-2  = 227 - 248 (top part)
			//A-2  = 214 - 255 (bottom part)

			//A#-2 = 249 - 272

			//B-2  = 273 - 297 (top part) 	
			//B-2  = 256 - 297 (top part)

			//C-1  = 298 - 321 (top part)
			//C-1  = 298 - 338 (bottom part)

		}
	}

	if(event.LeftUp()) 
	{ 
		for(int i=0; i<128; ++i){
			pianoDialog->KeyUp(i);
		}
	} 

}


