//// wxVstEditor.h /////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////

#ifdef _MSC_VER
#pragma warning (disable : 4996)
#endif

#ifndef __wxVstEditor__
#define __wxVstEditor__

#ifndef __AEffEditor__
#include "AEffEditor.hpp"
#endif

class wxVstPanel;

/////////////////////////////////////
class wxVstEditor : public AEffEditor
{
public :

	wxVstEditor (AudioEffect *pEffect);
	virtual ~wxVstEditor ();

	virtual void setParameter (long index, float value); 
	virtual long getRect (ERect **ppRect);
	virtual long open (void *ptr);
	virtual void close ();
	virtual void idle ();
	virtual void draw (ERect *pRect);

	#if VST_2_1_EXTENSIONS
	virtual long onKeyDown (VstKeyCode &keyCode);
	virtual long onKeyUp (VstKeyCode &keyCode);
	#endif

	#if MAC
	virtual long mouse (long x, long y);
	#endif

	// get the effect attached to this editor
	AudioEffect *getEffect () { return effect; }

	virtual bool onWheel (float distance);

//------ wxWidgets specific members------

	// call one time only to start wxWidgets without entering wx main loop
	// return true if success or false if failed to init wx or the main wxApp
	// will call wxApp->OnInit()
	static bool startWxWidgets( HINSTANCE hInstance );

	// call one time only to stop wxWidgets
	// will call wxApp->OnExit()
	static void stopWxWidgets();

	wxVstPanel *getPanel () { return panel; }

	// called by the panel to inform that a parameter was changed by the GUI
	virtual void parameterChanged(long index);

protected:
	ERect   rect;

	// host window converted into wxWindow from provided systemWindow
	wxWindow *parent;

	// the GUI panel
	wxVstPanel *panel;

	friend class wxVstPanel;
};

/////////////////////////////////
class wxVstPanel : public wxPanel
{
	DECLARE_EVENT_TABLE()

public:

	// make panel and editor know each other
	wxVstPanel( wxVstEditor* editor );
	wxVstEditor* getEditor() { return m_editor; }

	virtual void setParameter (long index, float value) {};
	virtual float getParameter (long index) { return 0; }

    // try to resize host to same size or revert to old size
    void OnSize( wxSizeEvent& event );

protected:
	wxVstEditor* m_editor;
};

#endif
