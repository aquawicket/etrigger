//// EtmEditorDialog2.cpp //////////////////////////////////////////////////////////////
//
// We will have to code our drum types to allow other drum set compatability.
//
// MidiNote to DrumType
// 1 = Kick Drum
// 2 = Hi-Hat Pedal
// 3 = Hi-Hat
// 4 = Snare 1
// and so on.
//
////////////////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "EtmEditorDialog2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//#include "glfont2.h"

/////////////////////////////////////////////////////
EtmEditorDialog2::EtmEditorDialog2(MainPanel *parent)
	:wxDialog(parent, -1, wxT("Editor"), wxDefaultPosition, wxSize(700,600), wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER | wxMAXIMIZE_BOX, wxT(""))
{
	InitVariables();

	mainPanel = parent;
	etmFile = mainPanel->etmFile;

	glCanvas2 = new GLCanvas2(this, -1, GetClientSize());
	glCanvas2->Refresh();
	//renderTimer = new RenderTimer2(glCanvas2);
	//renderTimer->Start(1, false);
}

/////////////////////////////////////
EtmEditorDialog2::~EtmEditorDialog2()
{
	delete glCanvas2;
	//delete renderTimer;
}

//////////////////////////////////////
void EtmEditorDialog2::InitVariables()
{
	mainPanel = NULL;
	etmFile = NULL;
	glCanvas2 = NULL;
	//renderTimer = NULL;
}

/////////////////////////////////////
void EtmEditorDialog2::Notify()
{
	glCanvas2->Refresh();
}

//////////////////////////////
void EtmEditorDialog2::OnLoad()
{
	etmFile->Load();
}

///////////////////////////////
void EtmEditorDialog2::OnPlay()
{
	etmFile->Play();
}

///////////////////////////////
void EtmEditorDialog2::OnStop()
{
	etmFile->Stop();
}

/////////////////////////////////////////////////////////////////////////
void EtmEditorDialog2::RecieveMessage(std::vector<unsigned char> &message)
{
	//Determin the signal type
	//message[0] = channel;
	//message[1] = drumType;
	//message[2] = velocity;

	if(etmFile->recording == true){
		//Note On
		if(message[0] > 143 && message[0] < 160 && message[2] > 0){
			etmFile->AddNoteOn(etmFile->timeStamp->Time(), message[1], message[2]);
		}
		//Note Off
		if(message[0] > 143 && message[0] < 160 && message[2] == 0){
			//etmFile->AddNoteOff(etmTimer->sw.Time(), message[1]);
		}
		//MidiCC
		if(message[0] > 175 && message[0] < 192){
			etmFile->AddMidiCC(etmFile->timeStamp->Time(), message[1], message[2]);
		}
	}
}

///////////////////////////////////////
BEGIN_EVENT_TABLE(GLCanvas2, wxGLCanvas)
    EVT_SIZE             (GLCanvas2::OnSize)
	EVT_SCROLL           (GLCanvas2::OnScroll)
    EVT_PAINT            (GLCanvas2::OnPaint)
    EVT_ERASE_BACKGROUND (GLCanvas2::OnEraseBackground)
    EVT_ENTER_WINDOW     (GLCanvas2::OnEnterWindow)
	EVT_LEFT_DOWN        (GLCanvas2::OnMousePressed)
	EVT_LEFT_UP          (GLCanvas2::OnMouseReleased)
	EVT_KEY_UP           (GLCanvas2::OnKeyUp)
	EVT_KEY_DOWN         (GLCanvas2::OnKeyDown)
	EVT_IDLE             (GLCanvas2::IdleLoop)
	EVT_BUTTON      (100, GLCanvas2::OnPlay)
	EVT_BUTTON      (101, GLCanvas2::OnStop)
	EVT_BUTTON      (102, GLCanvas2::OnRecord)
	EVT_BUTTON      (103, GLCanvas2::OnNew)
	EVT_BUTTON      (104, GLCanvas2::OnSave)
	EVT_BUTTON      (105, GLCanvas2::OnLoad)
	EVT_BUTTON      (106, GLCanvas2::OnImport)
	EVT_BUTTON      (107, GLCanvas2::OnZoomIn)
	EVT_BUTTON      (108, GLCanvas2::OnZoomOut)
END_EVENT_TABLE()

/////////////////////////////////////////////////////////////////
GLCanvas2::GLCanvas2(EtmEditorDialog2 *parent, wxWindowID id, wxSize size)
    : wxGLCanvas(parent, (wxGLCanvas*) NULL, id, wxPoint(0,0), size, wxFULL_REPAINT_ON_RESIZE , wxT(""))
{
	//SetExtraStyle(wxWS_EX_PROCESS_IDLE); //animate in the idle event

	etmEditorDialog2 = parent;
	etmFile = etmEditorDialog2->etmFile;
	
	//Set all images to NULL
	//myfont = NULL;
	
	int buffsize = GetSize().x * GetSize().y;
	waveFormBuffer = new float[buffsize*3];
	waveFormDirty = true;
	rows = 0;
	spacing = 0;
	speed = 0.008f;
	latency = 0;
	lineSmoothing = false;
	ratio = .1; //pixels per ms

	hScrollBar = new wxScrollBar(this, -1, wxPoint(0 ,GetSize().y - 50), wxSize(GetSize().x,16), wxSB_HORIZONTAL, wxDefaultValidator, wxT(""));
	
#ifndef MAC
	hScrollBar->SetThumbSize(GetSize().x);
	hScrollBar->SetRange(GetWidthInPixels());
	hScrollBar->SetPageSize(GetSize().x / 8);
#endif //!MAC
	scrollAmount = 0;

	record = new wxButton(this, 102, wxT("Record"), wxPoint(10,GetSize().y - 25), wxSize(40, 20), 0, wxDefaultValidator, wxT(""));
	play = new wxButton(this, 100, wxT("Play"), wxPoint(50,GetSize().y - 25), wxSize(40, 20), 0, wxDefaultValidator, wxT(""));
	stop = new wxButton(this, 101, wxT("Stop"), wxPoint(90,GetSize().y - 25), wxSize(40, 20), 0, wxDefaultValidator, wxT(""));

	newFile = new wxButton(this, 103, wxT("New"), wxPoint(200,GetSize().y - 25), wxSize(40, 20), 0, wxDefaultValidator, wxT(""));
	save = new wxButton(this, 104, wxT("Save"), wxPoint(240,GetSize().y - 25), wxSize(40, 20), 0, wxDefaultValidator, wxT(""));
	load = new wxButton(this, 105, wxT("Load"), wxPoint(280,GetSize().y - 25), wxSize(40, 20), 0, wxDefaultValidator, wxT(""));

	import = new wxButton(this, 106, wxT("Import Audio"), wxPoint(350,GetSize().y - 25), wxSize(80, 20), 0, wxDefaultValidator, wxT(""));

	zoomIn = new wxButton(this, 107, wxT("+"), wxPoint(450,GetSize().y - 25), wxSize(20, 20), 0, wxDefaultValidator, wxT(""));
	zoomOut = new wxButton(this, 108, wxT("-"), wxPoint(470,GetSize().y - 25), wxSize(20, 20), 0, wxDefaultValidator, wxT(""));

	SetDefaultView();

	selectedNode = -1;
}

///////////////////////
GLCanvas2::~GLCanvas2()
{
	//delete load;
	delete play;
	//delete stop;
	//myfont->Destroy();
	//delete myfont;
	delete waveFormBuffer;
}

/////////////////////////////////////////////////
void GLCanvas2::OnEnterWindow(wxMouseEvent &event)
{
    //SetFocus();
}

///////////////////////////////////////////////////
void GLCanvas2::OnMousePressed(wxMouseEvent& event)
{
	SetFocus();
	selectedNode = -1;
	float temp1 = (float)(((float)(GetSize().y - 50) / 4) * 3);
	float temp2 = temp1 / (float)40;

	for(unsigned int i=0; i<etmFile->midiData.size(); ++i){
		if(event.GetPosition().x > (etmFile->midiData[i].timestamp * ratio) - scrollAmount - 1 &&
		   event.GetPosition().x < (etmFile->midiData[i].timestamp * ratio) - scrollAmount + 6 &&
		   event.GetPosition().y > (etmFile->midiData[i].drumType - 1) * temp2 &&
		   event.GetPosition().y < (etmFile->midiData[i].drumType - 1) * temp2 + temp2){

			selectedNode = i;
		}		
	}
}
///////////////////////////////////////////////////
void GLCanvas2::OnMouseReleased(wxMouseEvent& event)
{
	etmFile->SetPosition((scrollAmount + event.GetPosition().x) / ratio);
	Refresh();
}

/////////////////////////////////////////
void GLCanvas2::OnKeyUp(wxKeyEvent& event)
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

///////////////////////////////////////////
void GLCanvas2::OnKeyDown(wxKeyEvent& event)
{
 
}

///////////////////////////////////////////
void GLCanvas2::OnPaint(wxPaintEvent &event)
{
    Render();
}

//////////////////////////////////////////
void GLCanvas2::OnSize(wxSizeEvent& event)
{
    // this is also necessary to update the context on some platforms
    wxGLCanvas::OnSize(event);

    // set GL viewport (not called by wxGLCanvas2::OnSize on all platforms...)
    int w, h;
    GetClientSize(&w, &h);

	hScrollBar->SetPosition(wxPoint(0, GetSize().y - 50));
	hScrollBar->SetSize(wxSize(GetSize().x,16));
	
#ifndef MAC
	hScrollBar->SetThumbSize(GetSize().x);
	hScrollBar->SetRange(GetWidthInPixels());
#endif //!MAC

	record->SetPosition(wxPoint(10, GetSize().y - 25));
	play->SetPosition(wxPoint(50, GetSize().y - 25));
	stop->SetPosition(wxPoint(90, GetSize().y - 25));

	newFile->SetPosition(wxPoint(200, GetSize().y - 25));
	save->SetPosition(wxPoint(240, GetSize().y - 25));
	load->SetPosition(wxPoint(280, GetSize().y - 25));

	import->SetPosition(wxPoint(350, GetSize().y - 25));

	zoomIn->SetPosition(wxPoint(450, GetSize().y - 25));
	zoomOut->SetPosition(wxPoint(470, GetSize().y - 25));

    SetCurrent();
    glViewport(0, 0, (GLint) w, (GLint) h);

    glMatrixMode (GL_PROJECTION); // Set the Matrix mode
    glLoadIdentity (); 
    gluPerspective(75, (GLfloat) w /(GLfloat) h , 0.10, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt (rotLx, rotLy, 15.0 + rotLz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); 
	waveFormDirty = true;
	Refresh();
}

//////////////////////////////////////////////
void GLCanvas2::OnScroll(wxScrollEvent &event)
{
	scrollAmount = hScrollBar->GetThumbPosition();
	waveFormDirty = true;
	Refresh();
}

////////////////////////////////////////////
void GLCanvas2::IdleLoop(wxIdleEvent &event)
{
	event.Skip(true); //do not propagate this event
	Render();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
void GLCanvas2::prepare2DViewport(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y)
{
    //Inits the OpenGL viewport for drawing in 2D

    glEnable(GL_TEXTURE_2D);   // textures
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	
    glViewport(topleft_x, topleft_y, bottomrigth_x-topleft_x, bottomrigth_y-topleft_y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluOrtho2D(0, GetSize().x, GetSize().y, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void GLCanvas2::prepare3DViewport(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y)
{	
    glViewport (0, 0, GetSize().x, GetSize().y); // Set the viewport
    glMatrixMode (GL_PROJECTION); // Set the Matrix mode
    glLoadIdentity (); 
    gluPerspective(75, GetSize().x / GetSize().y , 0.10, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt (rotLx, rotLy, 15.0 + rotLz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); 
}

///////////////////////////////
void GLCanvas2::LineSmoothing()
{
	if(lineSmoothing){
		glClearColor(0.0, 0.0, 0.0, 0.0); // Clear the color 
		glShadeModel(GL_FLAT); // Set the shading model to GL_FLAT
		glEnable(GL_LINE_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST); // Set Line Antialiasing
	}
	else{
		glDisable(GL_LINE_SMOOTH);
	}
}

////////////////////////////////
void GLCanvas2::SetDefaultView()
{
	X = 0.0f;
	Y = -7.0f;
	Z = 2.0f;
	rotX = -20.0f;
	rotY = 0.0f;
	rotZ = 0.0f;
	rotLx = 0.0f;
	rotLy = 0.0f;
	rotLz = 0.0f;
	waveFormDirty = true;
	Refresh();
}

////////////////////////
void GLCanvas2::Render()
{
    if(!IsShown()) return;
    wxGLCanvas::SetCurrent();

	//Set scroll bar position
	if(etmFile->timeStamp->Time() > GetMsFromPixel(GetSize().x - 5) &&
		etmFile->playing || 
		etmFile->timeStamp->Time() > GetMsFromPixel(GetSize().x - 5) &&
		etmFile->recording){
		scrollAmount = scrollAmount + GetSize().x - 25;
		hScrollBar->SetThumbPosition(scrollAmount);
	}

	//are we at the end of the audio?
	if((etmFile->timeStamp->Time()) > (GetMsFromPixel(GetWidthInPixels()) + 1000) ){
		etmFile->Pause();
		//etmEditorDialog2->renderTimer->Stop();
	}

	//if(myfont == NULL){ myfont = new GLFont(); myfont->Create("arial.glf", 1); }

	wxPaintDC(this);
	LineSmoothing();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	prepare2DViewport(0, 0, GetSize().x, GetSize().y);

	DrawMidiGrid();
	DrawMidi();
	DrawWaveGrid();	
	DrawWave(); 
	DrawCursor();

	//Do it
	glFlush();
	SwapBuffers();
}

//////////////////////////////
void GLCanvas2::DrawMidiGrid()
{
	float temp1 = (float)(((float)(GetSize().y - 50) / 4) * 3);
	float temp2 = temp1 / (float)40;
	glBegin(GL_LINES);
	glColor3f(1.0, 1.0, 1.0);
	for(float i=1; i<41; ++i){
		glVertex2f(0, temp2 * i); glVertex2f(GetSize().x, temp2 * i);
	}
	glEnd();
}

//////////////////////////
void GLCanvas2::DrawMidi()
{
	float temp1 = (float)(((float)(GetSize().y - 50) / 4) * 3);
	float temp2 = temp1 / (float)40;

	for(unsigned int i=0; i<etmFile->midiData.size(); ++i){
		if(etmFile->midiData[i].timestamp > GetMsFromPixel(GetSize().x)){
			return; //no need to draw past end of screen
		}
		if(etmFile->midiData[i].timestamp > GetMsFromPixel(0)){
			if(etmFile->midiData[i].midiType == 0){ //Note-ON
			
				int velocity = (temp1 * etmFile->midiData[i].velocity) / 127;

				//draw velocitys
				/*
				glBegin(GL_LINES);
					glColor3f(0.0, 1.0, 0.0);
					glVertex2f((etmFile->midiData[i].timestamp * ratio) - scrollAmount, velocity); 
					glVertex2f((etmFile->midiData[i].timestamp * ratio) - scrollAmount, temp1);
				glEnd();
				*/

				//draw hit line
				glBegin(GL_LINES);
					glColor3f(0.3f, 0.3f, 0.3f);
					glVertex2f((etmFile->midiData[i].timestamp * ratio) - scrollAmount, 0); 
					glVertex2f((etmFile->midiData[i].timestamp * ratio) - scrollAmount, GetSize().y);
				glEnd();


				//draw note
				glBegin(GL_QUADS);
				if(selectedNode == i){
					glColor3f(1.0, 1.0, 1.0);
				}
				else{
					if(etmFile->midiData[i].drumType == 1){
						glColor3f(1.0,1.0,0.0);  //yellow
					}
					if(etmFile->midiData[i].drumType == 3){
						glColor3f(0.0,0.0,1.0);  //blue
					}
					if(etmFile->midiData[i].drumType == 4){
						glColor3f(1.0,0.0,0.0);  //red
					}
					if(etmFile->midiData[i].drumType == 5){
						glColor3f(0.0,1.0,0.0); //green
					}
					if(etmFile->midiData[i].drumType == 6){
						glColor3f(1.0,0.75,0.0); //orange
					}
					if(etmFile->midiData[i].drumType == 7){
						glColor3f(0.0,0.5,1.0);  //dark blue 
					}
					if(etmFile->midiData[i].drumType == 8){
						glColor3f(0.75,0.0,1.0); //purple 
					}
					if(etmFile->midiData[i].drumType == 9){
						glColor3f(1.0,0.0,1.0);  //pink
					}
					if(etmFile->midiData[i].drumType == 10){
						glColor3f(0.75,0.0,0.0); //dark red
					}
					if(etmFile->midiData[i].drumType == 14){
						glColor3f(0.75,0.0,1.0); //purple
					}
				}
				glVertex2f((etmFile->midiData[i].timestamp * ratio) - scrollAmount, (etmFile->midiData[i].drumType - 1) * temp2);
				glVertex2f((etmFile->midiData[i].timestamp * ratio) - scrollAmount + 5, (etmFile->midiData[i].drumType - 1) * temp2);
				glVertex2f((etmFile->midiData[i].timestamp * ratio) - scrollAmount + 5, ((etmFile->midiData[i].drumType - 1) * temp2) + temp2);
				glVertex2f((etmFile->midiData[i].timestamp * ratio) - scrollAmount, ((etmFile->midiData[i].drumType - 1) * temp2) + temp2);
				glEnd();
				//FIXME  -  we need to draw the note off here.
			}
		}
	}
}

//////////////////////////////
void GLCanvas2::DrawWaveGrid()
{

}

//////////////////////////
void GLCanvas2::DrawWave()
{
	if(etmFile->soundFile != NULL){	

		float waveYSize = (float)(((float)(GetSize().y - 50) / 8));
		//pixel to ms
		double ms = scrollAmount / ratio;
		double ms2 = (scrollAmount + GetSize().x) / ratio;
		//ms to frame;
		int f = ((ms / 1000) * etmFile->soundFile->samplerate) * etmFile->soundFile->channels;
		int f2 = ((ms2 / 1000) * etmFile->soundFile->samplerate) * etmFile->soundFile->channels;

		//for(int c=0; c<etmFile->soundFile->channels; ++c){
	
		/*
		glBegin(GL_LINE_STRIP);
		glColor3f(0.0, 1.0, 0.0);
		int c = 0;
		//for(int c=0; c<etmFile->soundFile->channels; ++c){
			for(int p=0; p<GetSize().x; ++p){

				if((etmFile->soundFile->frames * etmFile->soundFile->channels) < GetFrameFromPixel(p, c)){
					return;
				}

				int x = p;
				int y = ((temp1*7) + (etmFile->soundFile->soundData[GetFrameFromPixel(p, c)] * (float)(temp1)) );

				glVertex2f(x, y);	
			}
		//}
		glEnd();
		*/
	
	
		//}

		if(waveFormDirty){
			//we are currently drawing mono by overlapping the channels
			glBegin(GL_LINE_STRIP);
			glColor3f(0.0, 1.0, 0.0);
			for(f; f<f2; ++f){

				if(f < etmFile->soundFile->frames){
				//duration in ms = soundFile->frames / soundFile->samplerate * 1000;
				//currentTime in ms = f/soundFile->channels / soundFile->samplerate * 1000;

					int x = ((((float)(f/etmFile->soundFile->channels) / (float)etmFile->soundFile->samplerate) * 1000) * ratio) - scrollAmount;
					int y = ((waveYSize*7) + (etmFile->soundFile->soundData[f] * (float)(waveYSize)) );
		
					glVertex2f(x, y);
				}
		
					//how do we find out the time we are on in ms
					//use frames and samplerate
			}
			glEnd();
			//FIXME - We arn't able to save the pixels
			//our OpenGL texture handle
			//new array
			int temp = (GetSize().x * waveYSize * 3);
			char* colorBits = new char[temp];
			//texture creation..
			glGenTextures(1,&texture);
			glBindTexture(GL_TEXTURE_2D,texture);
			glTexImage2D(GL_TEXTURE_2D,0 ,3 , GetSize().x, waveYSize, 0 , GL_RGB, GL_UNSIGNED_BYTE, colorBits);

			delete[] colorBits;

			//save data to texture using glCopyTexImage2D
			glBindTexture(GL_TEXTURE_2D,texture);

			glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 0,0, GetSize().x, waveYSize, 0);


			waveFormDirty = false; //when glReadPixels and glDrawPixels work.. we can enable this.
		}
		else{ //clean
			//FIXME - We arn't able to recall the stored pixels
			glBindTexture(GL_TEXTURE, texture);
			//glDrawPixels(200, 200, GL_COLOR_INDEX, GL_UNSIGNED_BYTE, waveFormBuffer); 
		}
	}
}

////////////////////////////
void GLCanvas2::DrawCursor()
{
	glBegin(GL_LINES);
		glColor3f(1.0, 0.0, 0.0);
		glVertex2f((etmFile->timeStamp->Time() * ratio) - scrollAmount, 0); 
		glVertex2f((etmFile->timeStamp->Time() * ratio) - scrollAmount, GetSize().y - 50);
	glEnd();
}


/////////////////////////////////
int GLCanvas2::GetWidthInPixels()
{
	//We must find how wide the sound data is in pixels
	if(etmFile->soundFile != NULL){
		return etmFile->soundFile->frames / etmFile->soundFile->samplerate * 1000 * ratio;
	}
	return 0;
}

////////////////////////////////////////
int GLCanvas2::GetMsFromPixel(int pixel)
{
	return ((pixel + scrollAmount) / ratio);

	//Ms To Pixel
	//(etmFile->midiData[i].timestamp * ratio) - scrollAmount
}

////////////////////////////////////////////////////////
int GLCanvas2::GetFrameFromPixel(int pixel, int channel)
{
	double ms = ((pixel + scrollAmount) / ratio);
	int frame = ((ms / 1000) * etmFile->soundFile->samplerate) * etmFile->soundFile->channels;
	return frame;
}

///////////////////////////////////////////////
void GLCanvas2::OnRecord(wxCommandEvent &event)
{
	etmFile->Record();
	//etmEditorDialog2->renderTimer->Start(1, false);
}

/////////////////////////////////////////////
void GLCanvas2::OnPlay(wxCommandEvent &event)
{
	etmFile->Resume();
	//etmEditorDialog2->renderTimer->Start(1, false);
}

/////////////////////////////////////////////
void GLCanvas2::OnStop(wxCommandEvent &event)
{
	etmFile->Pause();
	//etmEditorDialog2->renderTimer->Stop();
}

/////////////////////////////////////////////
void GLCanvas2::OnNew(wxCommandEvent &event)
{
	etmFile->New();
	waveFormDirty = true;
	Refresh();
}

/////////////////////////////////////////////
void GLCanvas2::OnSave(wxCommandEvent &event)
{
	etmFile->Save();
	waveFormDirty = true;
	Refresh();
}

/////////////////////////////////////////////
void GLCanvas2::OnLoad(wxCommandEvent &event)
{
	etmFile->Load();
	
#ifndef MAC
	hScrollBar->SetRange(GetWidthInPixels());
#endif //!MAC
	waveFormDirty = true;
	Refresh();
}

///////////////////////////////////////////////
void GLCanvas2::OnImport(wxCommandEvent &event)
{
	etmFile->ImportAudio();
	
#ifndef MAC
	hScrollBar->SetRange(GetWidthInPixels());
#endif //!MAC
	waveFormDirty = true;
	Refresh();
}

///////////////////////////////////////////////
void GLCanvas2::OnZoomIn(wxCommandEvent &event)
{
	ratio = ratio + 0.05;
	if(ratio > 1.0){ratio = 1.0;}
	
#ifndef MAC
	hScrollBar->SetRange(GetWidthInPixels());
#endif //!MAC

	//lets try to keep the cursor on the same spot on the screen
	//scrollAmount = scrollAmount + 500;
	//hScrollBar->SetThumbPosition(scrollAmount);
	waveFormDirty = true;
	Refresh();
}

///////////////////////////////////////////////
void GLCanvas2::OnZoomOut(wxCommandEvent &event)
{
	ratio = ratio - 0.05;
	if(ratio < 0.05){ratio = 0.05;}
	
#ifndef MAC
	hScrollBar->SetRange(GetWidthInPixels());
#endif //!MAC

	//lets try to keep the cursor on the same spot on the screen
	//scrollAmount = scrollAmount - 500;
	//hScrollBar->SetThumbPosition(scrollAmount);
	waveFormDirty = true;
	Refresh();
}