//// GImageSelector.h /////////////////////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef GIMAGESELECTOR_H
#define GIMAGESELECTOR_H

#include <wx/window.h>
#include <wx/panel.h>
#include <wx/image.h>
#include <wx/dcbuffer.h>
#include <wx/filedlg.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/msgdlg.h>


////////////////////////////////////////////////
class GImageSelectorEvent: public wxCommandEvent 
{ 
	public: 
		GImageSelectorEvent(wxEventType commandType = wxEVT_NULL, int id = 0 ); 

		virtual wxEvent *Clone() const { return new GImageSelectorEvent(*this); } 

	private: 
	DECLARE_DYNAMIC_CLASS(GImageSelectorEvent) 
}; 

BEGIN_DECLARE_EVENT_TYPES() 
	DECLARE_EVENT_TYPE(wxEVT_COMMAND_GIMAGESELECTOR, -1) 
END_DECLARE_EVENT_TYPES() 

typedef void (wxEvtHandler::*wxGImageSelectorEventFunction)(GImageSelectorEvent&); 

#define EVT_GIMAGESELECTOR(id, fn) \
	DECLARE_EVENT_TABLE_ENTRY(wxEVT_COMMAND_GIMAGESELECTOR, id, -1,  \
	(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)  \
	wxStaticCastEvent(wxGImageSelectorEventFunction, & fn), (wxObject *) NULL ),



////////////////////////////////////
class GImageSelector: public wxPanel
{ 
	public: 
		GImageSelector(wxWindow* parent,
			wxWindowID id,
			const wxPoint& pos,
			const wxSize &size
			); 

		virtual ~GImageSelector(); 
		void OnPaint(wxPaintEvent &event); 
		void OnMouse(wxMouseEvent &event);
		void OnEraseBackground(wxEraseEvent &event);
		void SetImage(wxString &file);
		void UpdateImage();
		wxString GetImage();

		bool backFocused;

		wxImage image;
		wxString filePath;		

		private:
		DECLARE_EVENT_TABLE() 
};

#endif //GIMAGESELECTOR_H
