//// EtmPlayerDialog.cpp //////////////////////////////////////////////////////////////////
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
#include "EtmPlayerDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "../lib/Gwidgets/GLFont/glfont2.h"

///////////////////////////////////////////////////
EtmPlayerDialog::EtmPlayerDialog(MainPanel *parent)
	:wxDialog(parent, -1, wxT("Player"), wxDefaultPosition, wxSize(700,600), wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER | wxMAXIMIZE_BOX, wxT(""))
{
	InitVariables();

	mainPanel = parent;
	etmFile = mainPanel->etmFile;

	glCanvas = new GLCanvas(this, -1, GetClientSize());
	//renderTimer = new RenderTimer(glCanvas);
	//renderTimer->Start(1, false);
}

///////////////////////////////////
EtmPlayerDialog::~EtmPlayerDialog()
{
	delete glCanvas;
	//delete renderTimer;
	delete etmPlayerOptions;
}

/////////////////////////////////////
void EtmPlayerDialog::InitVariables()
{
	mainPanel = NULL;
	etmFile = NULL;
	glCanvas = NULL;
	//renderTimer = NULL;
	etmPlayerOptions = NULL;	
}

//////////////////////////////
void EtmPlayerDialog::Notify()
{
	glCanvas->Refresh();
}

//////////////////////////////
void EtmPlayerDialog::OnLoad()
{
	etmFile->Load();
}

//////////////////////////////
void EtmPlayerDialog::OnPlay()
{
	etmFile->Play();
}

//////////////////////////////
void EtmPlayerDialog::OnStop()
{
	etmFile->Stop();
}

////////////////////////////////
void EtmPlayerDialog::OnEditor()
{
	if(mainPanel->etmEditorDialog2 == NULL){
		mainPanel->etmEditorDialog2 = new EtmEditorDialog2(mainPanel);
		mainPanel->etmEditorDialog2->Show();
		mainPanel->etmEditorDialog2->SetFocus();
	}
	else{
		mainPanel->etmEditorDialog2->Show();
		mainPanel->etmEditorDialog2->SetFocus();
	}
}

//////////////////////////////////
void EtmPlayerDialog::OnSettings()
{
	if(etmPlayerOptions == NULL){
		etmPlayerOptions = new EtmPlayerOptions(this);
		etmPlayerOptions->Show();
		etmPlayerOptions->SetFocus();
	}
	else{
		etmPlayerOptions->Show();
		etmPlayerOptions->SetFocus();
	}
}

/////////////////////////////////////////////////////////////////////////
void EtmPlayerDialog::RecieveMessage(std::vector<unsigned char> &message)
{
	//message[1] = drumType

	if(etmFile->playing == true){
		if(message[0] > 143 && message[0] < 160 && message[2] > 0){

			int currentMidi = etmFile->GetNextNote();

			if(currentMidi > 0 && 
				etmFile->midiData[currentMidi-1].drumType == message[1] &&
			    etmFile->timeStamp->Time() - etmFile->midiData[currentMidi-1].timestamp < 100){
					++etmFile->goodHits;
			}

			else if(currentMidi > 0 && 
				etmFile->midiData[currentMidi].drumType == message[1] &&
			    etmFile->midiData[currentMidi].timestamp - etmFile->timeStamp->Time() < 100){
					++etmFile->goodHits;
			}

			else{
					++etmFile->badHits;
			}
		}
	}
}

///////////////////////////////////////
BEGIN_EVENT_TABLE(GLCanvas, wxGLCanvas)
    EVT_SIZE(GLCanvas::OnSize)
    EVT_PAINT(GLCanvas::OnPaint)
    EVT_ERASE_BACKGROUND(GLCanvas::OnEraseBackground)
    EVT_ENTER_WINDOW( GLCanvas::OnEnterWindow )
	EVT_LEFT_UP(GLCanvas::OnMouseReleased)
	EVT_KEY_UP(GLCanvas::OnKeyUp)
	EVT_KEY_DOWN(GLCanvas::OnKeyDown)
	EVT_IDLE     (GLCanvas::IdleLoop)
END_EVENT_TABLE()

/////////////////////////////////////////////////////////////////
GLCanvas::GLCanvas(EtmPlayerDialog *parent, wxWindowID id, wxSize size)
    : wxGLCanvas(parent, (wxGLCanvas*) NULL, id, wxPoint(0,0), size, wxFULL_REPAINT_ON_RESIZE , wxT(""))
{
	//SetExtraStyle(wxWS_EX_PROCESS_IDLE); //animate in the idle event

	etmPlayerDialog = parent;
	etmFile = etmPlayerDialog->etmFile;
	
	//Set all images to NULL
	load = NULL;
	play = NULL;
	stop = NULL;
	editor = NULL;
	settings = NULL;
	myfont = NULL;

	rows = 0;
	spacing = 0;
	speed = 0.008f;
	latency = 0;
	lineSmoothing = true;

	SetDefaultView();
}

/////////////////////
GLCanvas::~GLCanvas()
{
	delete load;
	delete play;
	delete stop;
	delete editor;
	delete settings;
	myfont->Destroy();
	delete myfont;
}

/////////////////////////////////////////////////
void GLCanvas::OnEnterWindow(wxMouseEvent &event)
{
    //SetFocus();
}

///////////////////////////////////////////////////
void GLCanvas::OnMouseReleased(wxMouseEvent& event)
{
	if(event.GetPosition().x > load->x &&
	   event.GetPosition().x < load->x + load->width &&
	   event.GetPosition().y > load->y &&
	   event.GetPosition().y < load->y + load->height){
		etmPlayerDialog->OnLoad();
	}

	if(event.GetPosition().x > play->x &&
	   event.GetPosition().x < play->x + play->width &&
	   event.GetPosition().y > play->y &&
	   event.GetPosition().y < play->y +play->height){
		etmPlayerDialog->OnPlay();
	}

	if(event.GetPosition().x > stop->x &&
	   event.GetPosition().x < stop->x + stop->width &&
	   event.GetPosition().y > stop->y &&
	   event.GetPosition().y < stop->y +stop->height){
		etmPlayerDialog->OnStop();
	}

	if(event.GetPosition().x > editor->x &&
	   event.GetPosition().x < editor->x + editor->width &&
	   event.GetPosition().y > editor->y &&
	   event.GetPosition().y < editor->y + editor->height){
		etmPlayerDialog->OnEditor();
	}

	if(event.GetPosition().x > settings->x &&
	   event.GetPosition().x < settings->x + settings->width &&
	   event.GetPosition().y > settings->y &&
	   event.GetPosition().y < settings->y + settings->height){
		etmPlayerDialog->OnSettings();
	}
}

/////////////////////////////////////////
void GLCanvas::OnKeyUp(wxKeyEvent& event)
{
	switch (event.GetKeyCode()){   // x,X,y,Y,z,Z uses the glRotatef() function
    
		case WXK_LEFT : // Rotate on x axis
		X -= 0.1f;
		break;

		case WXK_RIGHT : // Rotate on x axis (opposite)
		X += 0.1f;
		break;

		case WXK_UP : // Rotate on y axis 
		Y += 0.1f;
		break;

		case WXK_DOWN : // Rotate on y axis (opposite)
		Y -= 0.1f;
		break; 
	}
	Refresh();
}

///////////////////////////////////////////
void GLCanvas::OnKeyDown(wxKeyEvent& event)
{
	switch (event.GetKeyCode()){   // x,X,y,Y,z,Z uses the glRotatef() function

		case WXK_PAGEUP: // Roatae on z axis
		Z -= 0.1f;
		break;

		case WXK_PAGEDOWN:// Roatae on z axis (opposite)
		Z += 0.1f;
		break;

		case 'X': // Rotates screen on x axis 
		rotX -= 0.5f;
		break;

		case 'x': // Opposite way 
		rotX += 0.5f;
		break;

		case 'y': // Rotates screen on y axis
		rotY -= 0.5f;
		break;

		case 'Y': // Opposite way
		rotY += 0.5f; 
		break; 

		case 'z': // Rotates screen on z axis
		rotZ -= 0.5f;
		break;

		case 'Z': // Opposite way
		rotZ += 0.5f;
		break;

		// j,J,k,K,l,L uses the gluLookAt function for navigation
		case 'j':
		rotLx -= 0.2f; 
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt (rotLx, rotLy, 15.0 + rotLz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		break;

		case 'J':
		rotLx += 0.2f;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt (rotLx, rotLy, 15.0 + rotLz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		break; 

		case 'k':
		rotLy -= 0.2f;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt (rotLx, rotLy, 15.0 + rotLz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		break;

		case 'K':
		rotLy += 0.2f;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt (rotLx, rotLy, 15.0 + rotLz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		break;

		case 'l': // It has a special case when the rotLZ becames less than -15 the screen is viewed from the opposite side
		// therefore this if statement below does not allow rotLz be less than -15
		if(rotLz + 14 >= 0)
		rotLz -= 0.2f;           
		glMatrixMode(GL_MODELVIEW);    
		glLoadIdentity();  
		gluLookAt (rotLx, rotLy, 15.0 + rotLz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		break;

		case 'L':
		rotLz += 0.2f;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt (rotLx, rotLy, 15.0 + rotLz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		break;

		case 'b': // Rotates on x axis by -90 degree
		rotX -= 90.0f;
		break;

		case 'B': // Rotates on y axis by 90 degree
		rotX += 90.0f; 
		break;

		case 'n': // Rotates on y axis by -90 degree
		rotY -= 90.0f;
		break;

		case 'N': // Rotates on y axis by 90 degree
		rotY += 90.0f;
		break;

		case 'm': // Rotates on z axis by -90 degree
		rotZ -= 90.0f; 
		break;

		case 'M': // Rotates on z axis by 90 degree
		rotZ += 90.0f;
		break;

		case 'o': // Default, resets the translations vies from starting view
		case 'O': 

		SetDefaultView();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(rotLx, rotLy, 15.0f + rotLz, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);  
		break;
	}
    Refresh();
}

///////////////////////////////////////////
void GLCanvas::OnPaint(wxPaintEvent &event)
{
    Render();
}

/////////////////////////////////////////
void GLCanvas::OnSize(wxSizeEvent& event)
{
    // this is also necessary to update the context on some platforms
    wxGLCanvas::OnSize(event);

    // set GL viewport (not called by wxGLCanvas::OnSize on all platforms...)
    int w, h;
    GetClientSize(&w, &h);

    SetCurrent();
    glViewport(0, 0, (GLint) w, (GLint) h);

    glMatrixMode (GL_PROJECTION); // Set the Matrix mode
    glLoadIdentity (); 
    gluPerspective(75, (GLfloat) w /(GLfloat) h , 0.10, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt (rotLx, rotLy, 15.0 + rotLz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); 
}

///////////////////////////////////////////
void GLCanvas::IdleLoop(wxIdleEvent &event)
{
	event.Skip(true); //do not propagate this event
	Render();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
void GLCanvas::prepare2DViewport(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y)
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
void GLCanvas::prepare3DViewport(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y)
{	
    glViewport (0, 0, GetSize().x, GetSize().y); // Set the viewport
    glMatrixMode (GL_PROJECTION); // Set the Matrix mode
    glLoadIdentity (); 
    gluPerspective(75, GetSize().x / GetSize().y , 0.10, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt (rotLx, rotLy, 15.0 + rotLz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); 
}

//////////////////////////////
void GLCanvas::LineSmoothing()
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

///////////////////////////////
void GLCanvas::SetDefaultView()
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
}

///////////////////////
void GLCanvas::Render()
{
    if(!IsShown()) return;
    wxGLCanvas::SetCurrent();

	//are we at the end of the audio?
	if((etmFile->timeStamp->Time()) > (etmFile->GetLengthInMs() + 1000) ){
		etmFile->Stop();
	}

	if(myfont == NULL){ myfont = new GLFont(); myfont->Create("arial.glf", 1); }
	if(load == NULL){ load = new GLImage(load_xpm); }
	if(play == NULL){ play = new GLImage(play_xpm); }
	if(stop == NULL){ stop = new GLImage(stop_xpm); }
	if(editor == NULL){ editor = new GLImage(editor_xpm); }
	if(settings == NULL){ settings = new GLImage(settings_xpm); }

	wxPaintDC(this);
	LineSmoothing();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	prepare3DViewport(0, 0, GetSize().x, GetSize().y);

	glPushMatrix(); // It is important to push the Matrix before calling glRotatef and glTranslatef
	glRotatef(rotX,1.0,0.0,0.0); // Rotate on x
    glRotatef(rotY,0.0,1.0,0.0); // Rotate on y
    glRotatef(rotZ,0.0,0.0,1.0); // Rotate on z
    glTranslatef(X, Y, Z); // Translates the screen left or right, up or down or zoom in zoom out

	//DrawXYZ();
	DrawGrid();
	DrawDividers();
	DrawMidi();

	glPopMatrix(); // Don't forget to pop the Matrix

	prepare2DViewport(0, 0, GetSize().x, GetSize().y);
	DrawText();
	DrawButtons();
	
	//Do it
	glFlush();
	SwapBuffers();
}

////////////////////////
void GLCanvas::DrawXYZ()
{
    // Draw the positive side of the lines x,y,z
    glBegin(GL_LINES);
    glColor3f (0.0, 1.0, 0.0); // Green for x axis
    glVertex3f(0,0,0);
    glVertex3f(10,0,0);
    glColor3f(1.0,0.0,0.0); // Red for y axis
    glVertex3f(0,0,0);
    glVertex3f(0,10,0);
    glColor3f(0.0,0.0,1.0); // Blue for z axis
    glVertex3f(0,0,0); 
    glVertex3f(0,0,10);
    glEnd();

    // Dotted lines for the negative sides of x,y,z
    glEnable(GL_LINE_STIPPLE); // Enable line stipple to use a dotted pattern for the lines
    glLineStipple(1, 0x0101); // Dotted stipple pattern for the lines
    glBegin(GL_LINES); 
    glColor3f (0.0, 1.0, 0.0); // Green for x axis
    glVertex3f(-10,0,0);
    glVertex3f(0,0,0);
    glColor3f(1.0,0.0,0.0); // Red for y axis
    glVertex3f(0,0,0);
    glVertex3f(0,-10,0);
    glColor3f(0.0,0.0,1.0); // Blue for z axis
    glVertex3f(0,0,0);
    glVertex3f(0,0,-10);
    glEnd();
    glDisable(GL_LINE_STIPPLE); // Disable the line stipple  
}

/////////////////////////
void GLCanvas::DrawGrid()
{
	glBegin(GL_QUADS); //Left line
	glVertex3f(-5.1f,0.0f,0.0f);
	glVertex3f(-5.0f,0.0f,0.0f);
	glVertex3f(-5.0f, 100.0f, 0.0f);
	glVertex3f(-5.1f, 100.0f, 0.0f);
	glEnd();

	glBegin(GL_QUADS); //Right line
	glVertex3f(5.1f,0.0f,0.0f);
	glVertex3f(5.0f,0.0f,0.0f);
	glVertex3f(5.0f, 100.0f, 0.0f);
	glVertex3f(5.1f, 100.0f, 0.0f);
	glEnd();

	glBegin(GL_LINES);  //White Landing line
    glColor3f(1.0,1.0,1.0); 
    glVertex3f(-5,0,0);
    glVertex3f(5,0,0);
    glEnd();
}

/////////////////////////////
void GLCanvas::DrawDividers()
{
	rows = etmFile->drumTypes.size();
	for(unsigned int i=0; i<etmFile->drumTypes.size(); ++i){
		if(etmFile->drumTypes[i] == 1){rows--; break;}
	}

	if(rows > 0){
		spacing = 10 / (float)rows;

		for(int i=0; i<rows; ++i){
			glBegin(GL_LINES);  //Divider Line
			glColor3f(1.0,1.0,1.0); 
			glVertex3f(-5 + (spacing * i),0,0);
			glVertex3f(-5 + (spacing * i),100,0);
			glEnd();
		}
	}

	for(unsigned int i=0; i<etmFile->drumTypes.size(); ++i){
		if(etmFile->drumTypes[i] == 1 || etmFile->drumTypes[i] == 2){ continue; }
		float x1 = -5 + (spacing * (etmFile->typeToLine[etmFile->drumTypes[i]] - 1));
		float x2 = x1 + spacing;

		glBegin(GL_QUADS);
		if(etmFile->drumTypes[i] == 3){
			glColor3f(0.0,0.0,1.0);  //blue
		}
		if(etmFile->drumTypes[i] == 4){
			glColor3f(1.0,0.0,0.0);  //red
		}
		if(etmFile->drumTypes[i] == 5){
			glColor3f(0.0,1.0,0.0); //green
		}
		if(etmFile->drumTypes[i] == 6){
			glColor3f(1.0,0.75,0.0); //orange
		}
		if(etmFile->drumTypes[i] == 7){
			glColor3f(0.0,0.5,1.0);  //dark blue 
		}
		if(etmFile->drumTypes[i] == 8){
			glColor3f(0.75,0.0,1.0); //purple 
		}
		if(etmFile->drumTypes[i] == 9){
			glColor3f(1.0,0.0,1.0);  //pink
		}
		if(etmFile->drumTypes[i] == 10){
			glColor3f(0.75,0.0,0.0); //dark red
		}
		if(etmFile->drumTypes[i] == 14){
			glColor3f(0.75,0.0,1.0); //purple
		}
		glVertex3f(x1,0.1f,0.0f);
		glVertex3f(x2,0.1f,0.0f);
		glVertex3f(x2, -0.1f, 0.0f);
		glVertex3f(x1, -0.1f, 0.0f);
		glEnd();
	}
}

/////////////////////////
void GLCanvas::DrawMidi()
{
	//FIXME - we should only draw the midi within the window.
	for(unsigned int i=0; i < etmFile->midiData.size(); ++i){
		if(etmFile->midiData[i].midiType == 0){
			
			if(etmFile->midiData[i].drumType == 1){ //kick drum
				float y = (((etmFile->midiData[i].timestamp - latency) * speed) - (etmFile->timeStamp->Time() * speed));

				glBegin(GL_QUADS);
				glColor3f(1.0,1.0,0.0); 
				glVertex3f(-5,y+0.1,0);
				glVertex3f(5,y+0.1,0);
				glVertex3f(5, y-0.1, 0);
				glVertex3f(-5, y-0.1, 0);
				glEnd();
			}

			else if(etmFile->midiData[i].drumType == 2){ //Hi-Hat Pedal
				float y = (((etmFile->midiData[i].timestamp - latency) * speed) - (etmFile->timeStamp->Time() * speed));
			}

			else{ //all other drums
				float y = (((etmFile->midiData[i].timestamp - latency) * speed) - (etmFile->timeStamp->Time() * speed));
				float x1 = -5 + (spacing * (etmFile->typeToLine[etmFile->midiData[i].drumType] - 1));
				float x2 = x1 + spacing;
				glBegin(GL_QUADS);
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
				glVertex3f(x1,y+0.1,0);
				glVertex3f(x2,y+0.1,0);
				glVertex3f(x2, y-0.1, 0);
				glVertex3f(x1, y-0.1, 0);
				glEnd();
			}
		}
	}
}

////////////////////////////
void GLCanvas::DrawButtons()
{
	load->Move(0, GetSize().y - load->height);
	load->Render();

	play->Move(load->width, GetSize().y - play->height);
	play->Render();

	stop->Move(load->width + play->width, GetSize().y - stop->height);
	stop->Render();

	editor->Move(load->width + play->width + stop->width, GetSize().y - editor->height);
	editor->Render();

	settings->Move(load->width + play->width + stop->width + editor->width, GetSize().y - settings->height);
	settings->Render();
}

/////////////////////////
void GLCanvas::DrawText()
{
	//Draw a string
	float white[3] = {1.0F, 1.0F, 1.0F};
	
	wxString goodHits = wxT("Good Hits: ");
	wxString badHits = wxT(" Bad Hits: ");
	goodHits += ConvTowxString(etmFile->goodHits);
	badHits += ConvTowxString(etmFile->badHits);

	myfont->Begin();
	myfont->DrawString(ConvToStdString(etmFile->songTitle), 1.0F, 10, 10, white, white);
	myfont->DrawString(ConvToStdString(goodHits), 1.0F, GetSize().x - 120, 10, white, white);
	myfont->DrawString(ConvToStdString(badHits), 1.0F, GetSize().x - 120, 30, white, white);
}