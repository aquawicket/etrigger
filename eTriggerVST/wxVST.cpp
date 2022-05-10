////wxVst.cpp////////////////////////////////////////////////////////////////
//
//
/////////////////////////////////////////////////////////////////////////////

//#include "wx/wxprec.h"

#include "../eTrigger/stdwx.h"
#include "wxVST.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#include "eTriggerVST.h"
#include "wx/msw/private.h" 


///////////////////////////////////////////////
wxVstEditor::wxVstEditor (AudioEffect *pEffect) 
	: AEffEditor (pEffect), panel (0)
{
	rect.left   = 0;
	rect.top    = 0;
	pEffect->setEditor (this);
	systemWindow = 0;
}

////////////////////////////
wxVstEditor::~wxVstEditor () 
{
}

/////////////////////////////////////////////////
long wxVstEditor::onKeyDown (VstKeyCode &keyCode)
{
	// the panel is not getting any windows activation messages so grab focus when we can...
	panel->SetFocus();

	if ( keyCode.virt == VKEY_TAB )
	{
		wxNavigationKeyEvent eventNav;
		int flags;
		if ( keyCode.modifier == MODIFIER_SHIFT )
			flags = wxNavigationKeyEvent::IsBackward;
		else
			flags = wxNavigationKeyEvent::IsForward;
		eventNav.SetFlags(flags);
		eventNav.SetEventObject(panel);
		if ( panel->GetEventHandler()->ProcessEvent(eventNav) )
				return 1;
	}

	return -1;
}

///////////////////////////////////////////////
long wxVstEditor::onKeyUp (VstKeyCode &keyCode)
{
	return -1;
}

///////////////////////////////////////
void wxVstEditor::draw (ERect *ppErect)
{
}

#if MAC
////////////////////////////////////////
long wxVstEditor::mouse (long x, long y)
{
	return 1;
}
#endif

//////////////////////////////////
long wxVstEditor::open (void *ptr)
{
	// add this to update the value the first time
	postUpdate ();

	// create a parent wxWindow from the host provided window
	parent = new wxWindow();
	parent->SetEventHandler(parent);
	parent->SetHWND((HWND) ptr);
	parent->SetId(wxGetWindowId((HWND) ptr));
#ifndef __WXUNIVERSAL__
	parent->AdoptAttributesFromHWND(); 
#endif // __WXUNIVERSAL__

	return AEffEditor::open (ptr);
}

//////////////////////////
void wxVstEditor::close ()
{
	parent->SetHWND(NULL);
	delete parent;
	parent = NULL;
	panel = NULL;

	AEffEditor::close();
}

/////////////////////////
void wxVstEditor::idle ()
{
}

//////////////////////////////////////////
bool wxVstEditor::onWheel (float distance)
{
	return false;
}

///////////////////////////////////////////
long wxVstEditor::getRect (ERect **ppErect)
{
	*ppErect = &rect;
	return true;
}


///////////////////////////////////////////////////////
// wxWidgets specific methods
///////////////////////////////////////////////////////
bool wxVstEditor::startWxWidgets( HINSTANCE hInstance )
{
	// we must have at least one 'command line' parameter so let it be the DLL name
	// argv should be on the heap since it is later referenced and deleted by wxApp
	int argc = 1;
	wxChar ** argv = new wxChar*[2];
	wxChar *name = new wxChar[1024];
	name[0] = 0;
	GetModuleFileName( hInstance, name, 1024 );
	argv[0] = name;
	argv[1] = NULL;

	// start wxWidgets without going into wx main loop
	wxSetInstance( hInstance);
	wxEntryStart(argc, argv);
	if ( !wxTheApp->CallOnInit() )
	{
		wxEntryCleanup();
		return false;
	}

	delete argv;
	delete name;
	return true;
}

/////////////////////////////////
void wxVstEditor::stopWxWidgets()
{
	wxTheApp->OnExit();
	wxEntryCleanup();
}

////////////////////////////////////////////////////////
void wxVstEditor::setParameter (long index, float value)
{
	// called from ADelayEdit
	if ( panel != NULL )
		panel->setParameter(index, effect->getParameter (index));
}

//////////////////////////////////////////////
void wxVstEditor::parameterChanged(long index)
{
	effect->setParameterAutomated (index, panel->getParameter( index ));
}















////////////////////////////////////////
BEGIN_EVENT_TABLE( wxVstPanel, wxPanel )
    EVT_SIZE( wxVstPanel::OnSize )
END_EVENT_TABLE()

/////////////////////////////////////////////
wxVstPanel::wxVstPanel( wxVstEditor* editor )
{
	m_editor = editor;
	m_editor->panel = this;
}

/////////////////////////////////////////////
void wxVstPanel::OnSize( wxSizeEvent& event )
{
	// this code is for handling hosts with bugs in their sizeWindow, canDoSizeWindow, etc.

	// get current host window
	RECT hostRect;
	GetWindowRect((HWND)m_editor->systemWindow, &hostRect);

	// ask host to resize window
	((AudioEffectX*)m_editor->effect)->sizeWindow (event.GetSize().GetWidth(), event.GetSize().GetHeight());

	// get size after resize
	RECT newHostRect;
	GetWindowRect((HWND)m_editor->systemWindow, &newHostRect);

	// if resized then remember this size
	if ( !EqualRect(&hostRect, &newHostRect) )
	{
		// assuming rect left, top is 0,0 !!!
		m_editor->rect.right = event.GetSize().GetWidth() - 1;
		m_editor->rect.bottom = event.GetSize().GetHeight() - 1;
	}
	// if not resized then go to old size
	else
	{
		SetSize( m_editor->rect.right + 1, m_editor->rect.bottom + 1);
	}

	// now do the default stuff
    event.Skip();
}








///////////////////////////////////////////////////////////
wxVstEffectX::wxVstEffectX(audioMasterCallback audioMaster)
			 :AudioEffectX (audioMaster, 16, 3)
{

}

/////////////////////////////
wxVstEffectX::~wxVstEffectX()
{

}

///////////////////////////////////////////////////////////////////////////////
void wxVstEffectX::process (float** inputs, float** outputs, long sampleFrames)
{

}

//////////////////////////////////////////////////////////////////////////////////
void wxVstEffectX::processReplacing (float** inputs, float** outputs, long sampleFrames)
{

}
