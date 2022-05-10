//// EtmPlayerDialog.h //////////////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef ETMPLAYERDIALOG_H
#define ETMPLAYERDIALOG_H

#include "wx/glcanvas.h"
#include "../lib/GWidgets/GLImage/GLImage.h"

#include <string>
#include <utility>
#include "../lib/GWidgets/GLFont/glfont2.h"

#include "../Images/load.xpm"
#include "../Images/play.xpm"
#include "../Images/stop.xpm"
#include "../Images/editor.xpm"
#include "../Images/settings.xpm"

using namespace glfont;

// include OpenGL
#ifdef __WXMAC__
#include "OpenGL/glu.h"
#include "OpenGL/gl.h"
#else
#include <windows.h>
#include <GL/glu.h>
#include <GL/gl.h>
#endif

#include "EtmPlayerOptions.h"
#include "EtmEditorDialog2.h"

class GLCanvas;
//class RenderTimer;
class EtmEditorDialog;

////////////////////////////////////////
class EtmPlayerDialog : public wxDialog
{
public:
	EtmPlayerDialog(MainPanel *parent);
	~EtmPlayerDialog();
	void InitVariables();
	void Notify();

	void OnLoad();
	void OnPlay();
	void OnStop();
	void OnEditor();
	void OnSettings();

	void RecieveMessage(std::vector<unsigned char> &message);

	MainPanel *mainPanel;
	EtmFile *etmFile;
	GLCanvas *glCanvas;
	//RenderTimer *renderTimer;
	EtmPlayerOptions *etmPlayerOptions;
	//EtmEditorDialog2 *etmEditorDialog2;
};


//////////////////////////////////
class GLCanvas: public wxGLCanvas
{
public:
    GLCanvas( EtmPlayerDialog *parent, wxWindowID id, wxSize size);
	~GLCanvas();

    void OnPaint(wxPaintEvent& event);
    void OnSize(wxSizeEvent& event);
	void OnEraseBackground(wxEraseEvent& event){}; //Do nothing, to avoid flashing.
    void OnEnterWindow(wxMouseEvent& event);
	void OnMouseReleased(wxMouseEvent& event);
	void OnKeyDown(wxKeyEvent& event);
	void OnKeyUp(wxKeyEvent& event);
	void IdleLoop(wxIdleEvent& event);

	void DrawXYZ();
	void DrawGrid();
	void DrawDividers();
	void DrawMidi();
	void DrawButtons();
	void DrawText();

	void SetDefaultView();
	
	void prepare2DViewport(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y);
    void prepare3DViewport(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y);
	void Render();

	EtmPlayerDialog *etmPlayerDialog;
	EtmFile *etmFile;

	//drawing
	int rows;
	float spacing;
	float speed;
	float latency;

	GLImage *load;
	GLImage *play;
	GLImage *stop;
	GLImage *editor;
	GLImage *settings;
	GLFont  *myfont;

	GLfloat X; // Translate screen to x direction (left or right)
	GLfloat Y; // Translate screen to y direction (up or down)
	GLfloat Z; // Translate screen to z direction (zoom in or out)
	GLfloat rotX; // Rotate screen on x axis 
	GLfloat rotY; // Rotate screen on y axis
	GLfloat rotZ; // Rotate screen on z axis
	GLfloat rotLx; // Translate screen by using the glulookAt function (left or right)
	GLfloat rotLy; // Translate screen by using the glulookAt function (up or down)
	GLfloat rotLz; // Translate screen by using the glulookAt function (zoom in or out)

	//Video Options
	bool lineSmoothing;
	void LineSmoothing();

	DECLARE_EVENT_TABLE()
};

#endif //ETMPLAYERDIALOG_H