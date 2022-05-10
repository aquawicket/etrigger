//// GImage.h /////////////////////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef GIMAGE_H
#define GIMAGE_H

#include <wx/window.h>
#include <wx/panel.h>
#include <wx/image.h>
#include <wx/dcbuffer.h>

////////////////////////////
class GImage: public wxPanel
{ 
	public: 
	// Constructors 
		GImage(wxWindow* parent,
			wxWindowID id,
			const wxPoint& pos,
			const wxImage& image
			); 

		GImage(wxWindow* parent,
			wxWindowID id,
			const wxPoint& pos,
			const wxString& image
			);

		GImage(wxWindow* parent,
			wxWindowID id,
			const wxPoint& pos,
			const char** image
			);

		GImage(wxWindow* parent,
			wxWindowID id,
			const wxPoint& pos
			);

		void SetImage(const wxString& image);

		// Destructor 
		virtual ~GImage(); 

	private: 
		void OnPaint(wxPaintEvent &event); 

		wxImage c_bmp;
		bool imageLoaded;

		private:
		DECLARE_EVENT_TABLE() 
};

#endif //GIMAGE_H
