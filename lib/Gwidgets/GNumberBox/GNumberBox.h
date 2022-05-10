//// GNumberBox.h /////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef GNUMBERBOX_H
#define GNUMBERBOX_H

#include <wx/panel.h>
#include <wx/dcbuffer.h> 
#include <wx/msgdlg.h>
#include <wx/image.h>
#include <wx/textctrl.h>
#include <wx/valtext.h>

#ifndef LINUX
  #define FDR_NO_MOUSE_CAPTURE 0x0001
#endif

/////////////////////////////////////////
class GNumberBoxEvent: public wxCommandEvent 
{ 
	public: 
		GNumberBoxEvent(wxEventType commandType = wxEVT_NULL, int id = 0 ); 

		virtual wxEvent *Clone() const { return new GNumberBoxEvent(*this); } 

	private: 
	DECLARE_DYNAMIC_CLASS(GNumberBoxEvent) 
}; 

BEGIN_DECLARE_EVENT_TYPES() 
	DECLARE_EVENT_TYPE(wxEVT_COMMAND_GNUMBERBOX, -1) 
END_DECLARE_EVENT_TYPES() 

typedef void (wxEvtHandler::*wxGNumberBoxEventFunction)(GNumberBoxEvent&); 

#define EVT_GNUMBERBOX(id, fn) \
	DECLARE_EVENT_TABLE_ENTRY(wxEVT_COMMAND_GNUMBERBOX, id, -1,  \
	(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)  \
	wxStaticCastEvent(wxGNumberBoxEventFunction, & fn), (wxObject *) NULL ),


/////////////////////////////
class GNumberBox: public wxTextCtrl
{ 
	public: 
	// Constructors 
		GNumberBox(wxWindow *parent, wxWindowID id, const wxString& value, const wxPoint& pos, const wxSize& size); 

		// Destructor 
		virtual ~GNumberBox(); 

		void SetMinMax(int min, int max);
		void Set(int value);
		void SetDefault(int value);
		void OnTextChange(wxCommandEvent &event);

	private: 
		void OnMouse(wxMouseEvent &event); 
		void OnKeyDown(wxKeyEvent &event);
		#ifndef LINUX
		bool UseMouseCapture();
		#endif
		#ifdef WIN32
		void OnMouseCaptureLost(wxMouseCaptureLostEvent &event);
		#endif

		bool dragging;
		wxPoint mousePoint;
		int storedValue;
		int minValue;
		int maxValue;
		int defaultValue;

		DECLARE_EVENT_TABLE() 
};

#endif //GNUMBERBOX_H
