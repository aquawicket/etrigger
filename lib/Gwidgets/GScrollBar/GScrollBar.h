//// GScrollBar.h //////////////////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef GSCROLLBAR_H
#define GSCROLLBAR_H

#include <wx/window.h>
#include <wx/dcbuffer.h>
#include <wx/msgdlg.h>
#include <wx/image.h>
#include <wx/event.h>

//Include XPM image files
#include "left.xpm"
#include "right.xpm"

#define FDR_NO_MOUSE_CAPTURE 0x0001 

////////////////////////////////////////////
class GScrollBarEvent: public wxCommandEvent 
{
	public: 
		GScrollBarEvent(wxEventType commandType = wxEVT_NULL, int id = 0 ); 

		int GetValue() const { return m_position; } 
		void SetValue(int value) { m_position = value; } 

		virtual wxEvent *Clone() const { return new GScrollBarEvent(*this); } 

	private: 
		int m_position; 

	DECLARE_DYNAMIC_CLASS(GScrollBarEvent) 
};

BEGIN_DECLARE_EVENT_TYPES() 
DECLARE_EVENT_TYPE(wxEVT_COMMAND_GSCROLLBAR, -1) 
END_DECLARE_EVENT_TYPES() 

typedef void (wxEvtHandler::*wxGScrollBarEventFunction)(GScrollBarEvent&); 

#define EVT_GSCROLLBAR(id, fn) \
	DECLARE_EVENT_TABLE_ENTRY(wxEVT_COMMAND_GSCROLLBAR, id, -1,  \
	(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)  \
	wxStaticCastEvent(wxGScrollBarEventFunction, & fn), (wxObject *) NULL ),

////////////////////////////////
class GScrollBar: public wxPanel
{
	public:
		GScrollBar(wxWindow* parent, wxWindow *scrollwindow, wxWindowID id, int direction); //style - 1 = vertical or 2 = horizontal
		~GScrollBar();

		bool Create(wxWindow* parent, wxWindowID id, int direction);
		void Init();
		void SizeBar();
		void ShowScrollBar();
		void HideScrollBar();
		void OnPaint(wxPaintEvent &WXUNUSED(event));
		void OnEraseBackground(wxEraseEvent& WXUNUSED(event));
		void OnMouse(wxMouseEvent &event);
		//void OnMouseCaptureLost(wxMouseCaptureLostEvent &event);
		void DrawBackground(wxDC &dc);
		void DrawSlider(wxDC &dc);
		void DrawArrows(wxDC &dc);
		bool UseMouseCapture();
		void SizeSlider(int framesize, int pagesize);
		void PositionSlider(int pagesize);
		void UpdateScrollBar(int framesize, int pagesize);
		void ScrollWindow();
		void ResetScroll();


		wxWindow *framewin;
		wxWindow *scrollwin;
		unsigned int scrollwinposition;
		wxSize pSize;
		int sliderposition;
		int position;
		bool m_dragging;
		int slidersize;
		int offset;
		int fullPageSize;
		bool active;
	

		wxImage left;
        wxImage right;

		DECLARE_EVENT_TABLE()
};


#endif //GSCROLLBAR_H
