//// GImage.cpp ///////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////

#include "GImage.h"
 
////////////////////////////////////
BEGIN_EVENT_TABLE(GImage, wxPanel) 
	EVT_PAINT  (GImage::OnPaint) 
END_EVENT_TABLE() 

////////////////////////////////////////////////////////////////////////////////////////
GImage::GImage(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxImage& bmp) 
{
	#ifndef LINUX
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	#endif //LINUX
	c_bmp = bmp;
	imageLoaded = true;

	wxPanel::Create(parent, id, pos, wxSize(bmp.GetWidth(), bmp.GetHeight()), 0, wxT(""));
} 

//////////////////////////////////////////////////////////////////////////////////////////
GImage::GImage(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxString& image) 
{ 
	#ifndef LINUX
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	#endif //LINUX
	c_bmp = wxImage(image, wxBITMAP_TYPE_ANY);
	imageLoaded = true;

	wxPanel::Create(parent, id, pos, wxSize(c_bmp.GetWidth(), c_bmp.GetHeight()), 0, wxT(""));
} 

///////////////////////////////////////////////////////////////////////////////////////
GImage::GImage(wxWindow* parent, wxWindowID id, const wxPoint& pos, const char** image) 
{ 
	#ifndef LINUX
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	#endif //LINUX
	c_bmp = image;
	imageLoaded = true;

	wxPanel::Create(parent, id, pos, wxSize(c_bmp.GetWidth(), c_bmp.GetHeight()), 0, wxT(""));
} 

///////////////////////////////////////////////////////////////////
GImage::GImage(wxWindow* parent, wxWindowID id, const wxPoint& pos)
{
	wxPanel::Create(parent, id, pos, wxSize(100, 100), 0, wxT(""));
	imageLoaded = false;
}

////////////////////////////////////////////
void GImage::SetImage(const wxString& image)
{
	c_bmp = wxImage(image, wxBITMAP_TYPE_ANY);
	imageLoaded = true;
	Refresh();
}

/////////////////
GImage::~GImage() 
{ 

} 

///////////////////////////////////////////////////
void GImage::OnPaint(wxPaintEvent &event) 
{ 
	if(imageLoaded){
#ifndef MAC
		//SetDoubleBuffered(false);
#endif //!MAC
		//wxBufferedPaintDC dc(this);
		wxPaintDC dc(this);
		dc.DrawBitmap( c_bmp, 0, 0);
	}
} 
