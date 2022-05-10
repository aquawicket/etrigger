//// EtmEditorDialog2.h ////////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef ETMPLAYERDIALOG2_H
#define ETMPLAYERDIALOG2_H

#include "wx/glcanvas.h"
#include "../lib/GWidgets/GLImage/GLImage.h"

#include <string>
#include <utility>
#include "../lib/GWidgets/GLFont/glfont2.h"

#include "../Images/load.xpm"
#include "../Images/play.xpm"
#include "../Images/stop.xpm"

using namespace glfont;

// include OpenGL
#ifdef MAC
#include "OpenGL/glu.h"
#include "OpenGL/gl.h"
#else
#include <windows.h>
#include <GL/glu.h>
#include <GL/gl.h>
#endif

class GLCanvas2;
//class RenderTimer2;

////////////////////////////////////////
class EtmEditorDialog2 : public wxDialog
{
public:
	EtmEditorDialog2(MainPanel *parent);
	~EtmEditorDialog2();
	void InitVariables();
	void Notify();

	void OnLoad();
	void OnPlay();
	void OnStop();

	void RecieveMessage(std::vector<unsigned char> &message);

	MainPanel *mainPanel;
	EtmFile *etmFile;
	GLCanvas2 *glCanvas2;
	//RenderTimer2 *renderTimer;
};


///////////////////////////////////
class GLCanvas2: public wxGLCanvas
{
public:
    GLCanvas2( EtmEditorDialog2 *parent, wxWindowID id, wxSize size);
	~GLCanvas2();

    void OnPaint(wxPaintEvent& event);
    void OnSize(wxSizeEvent& event);
	void OnEraseBackground(wxEraseEvent& event){}; //Do nothing, to avoid flashing.
    void OnEnterWindow(wxMouseEvent& event);
	void OnMousePressed(wxMouseEvent& event);
	void OnMouseReleased(wxMouseEvent& event);
	void OnKeyDown(wxKeyEvent& event);
	void OnKeyUp(wxKeyEvent& event);
	void IdleLoop(wxIdleEvent& event);
	void OnScroll(wxScrollEvent &event);
	void RecieveMessage(std::vector<unsigned char> &message);

	void DrawMidiGrid();
	void DrawMidi();
	void DrawWaveGrid();
	void DrawWave();
	void DrawCursor();

	void SetDefaultView();
	
	void prepare2DViewport(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y);
    void prepare3DViewport(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y);
	void Render();

	EtmEditorDialog2 *etmEditorDialog2;
	EtmFile *etmFile;

	//drawing
	int rows;
	float spacing;
	float speed;
	float latency;

	GLvoid *waveFormBuffer;
	bool waveFormDirty;
	//unsigned int texture;
	GLuint texture;

	//GLFont  *myfont;

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

	double ratio;

	int scrollAmount;
	wxScrollBar *hScrollBar;
	int GetWidthInPixels();
	int GetMsFromPixel(int pixel);
	int GetFrameFromPixel(int pixel, int channel);

	void OnRecord(wxCommandEvent &event);
	void OnPlay(wxCommandEvent &event);
	void OnStop(wxCommandEvent &event);
	void OnNew(wxCommandEvent &event);
	void OnSave(wxCommandEvent &event);
	void OnLoad(wxCommandEvent &event);
	void OnImport(wxCommandEvent &event);
	void OnZoomIn(wxCommandEvent &event);
	void OnZoomOut(wxCommandEvent &event);

	wxButton *record;
	wxButton *play;
	wxButton *stop;
	wxButton *newFile;
	wxButton *save;
	wxButton *load;
	wxButton *import;
	wxButton *zoomIn;
	wxButton *zoomOut;

	int selectedNode;

	DECLARE_EVENT_TABLE()
};

#endif //ETMPLAYERDIALOG_H