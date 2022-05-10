//// GObject.h //////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////

#ifndef GOBJECT_H
#define GOBJECT_H

#include <wx/image.h>
#include <wx/dcbuffer.h>
#include <wx/graphics.h>

/////////////
class GObject
{ 
	public: 
		GObject(); 
		virtual ~GObject(){}
		virtual void Render(wxDC &dc){}
		virtual void Render(wxGraphicsContext &gc){}
		virtual bool HasMouse(wxMouseEvent &event){return NULL;}
		virtual bool OnMouse(wxMouseEvent &event){return NULL;}
		virtual bool GetValue(){return NULL;}
		virtual float GetValue(int num){return NULL;}
		virtual void SetValue(bool truefalse){}
};

#endif //GOBJECT_H