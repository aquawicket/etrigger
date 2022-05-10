//// GCurve.h /////////////////////////////////////////////////////////////////////////////
//
//   The GCurve class is a grid class that supports a flexable line.
//   Double clicking adds a node while double-right clicking removes the node.
//   Using the curve created, you can create a scaled curve.
//   Now we can convert input into output desired acording to the grid line.
//
//   This class is also currently desigened on a 0-127 scale for Midi data.
//   Hence there is a Limiter and Compressor added on the same scale.
//
//   Bugs: 
//		* Double clicking on a completley horizontal line will not add a node.
//
//   Todo:
//		* Add the abilty to actually add CURVE to the line across the grid.
//      * Make the scales of the grid, the limiter, and compressor more versital to work 
//        in more situations other than a 0-127 scale such as midi data.
//      * Add antialiasing to the line drawings.
//		
//    
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef GCURVE_H
#define GCURVE_H

#ifdef WIN
#include <windows.h>
#endif //win
#include <wx/panel.h>
#include <wx/dcbuffer.h> 
#include <wx/msgdlg.h>
#include <wx/image.h>
#include <vector>

#define FDR_NO_MOUSE_CAPTURE 0x0001 

/////////////////////////////////////////
class GCurveEvent: public wxCommandEvent 
{ 

public: 
	GCurveEvent(wxEventType commandType = wxEVT_NULL, int id = 0 ); 

	virtual wxEvent *Clone() const { return new GCurveEvent(*this); } 

	DECLARE_DYNAMIC_CLASS(GCurveEvent) 
}; 


BEGIN_DECLARE_EVENT_TYPES() 
	DECLARE_EVENT_TYPE(wxEVT_COMMAND_GCURVE, -1) 
END_DECLARE_EVENT_TYPES() 

typedef void (wxEvtHandler::*wxGCurveEventFunction)(GCurveEvent&); 

#define EVT_GCURVE(id, fn) \
	DECLARE_EVENT_TABLE_ENTRY(wxEVT_COMMAND_GCURVE, id, -1,  \
	(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)  \
	wxStaticCastEvent(wxGCurveEventFunction, & fn), (wxObject *) NULL ),



/////////////////////////////
class GCurve: public wxPanel
{ 
	public: 
		GCurve(wxWindow *parent, wxWindowID id, const wxPoint& pos);
		void OnPaint(wxPaintEvent &event);
		void OnEraseBackground( wxEraseEvent& event ); 
		void OnMouse(wxMouseEvent &event);
		void DrawGrid(wxDC &dc);
		void DrawCurve(wxDC &dc);
		void DrawPoints(wxDC &dc);
		void AddPoint(wxPoint point);
		void DeletePoint(int num);
		bool UseMouseCapture();
		void GridToVelocities();
		void VelocitiesToGrid();
		void SetLowLimiter(int num);
		void SetHighLimiter(int num);
		void SetLowCompressor(int num);
		void SetHighCompressor(int num);
		void SetLowPercent(int num);
		void SetHighPercent(int num);

		std::vector< wxPoint > points;
		int velocities[127];
		bool draggingNode;
		int currentNode;
		int lowLimiter;
		int highLimiter;
		int lowCompressor;
		int highCompressor;
		int lowPercent;
		int highPercent;

		DECLARE_EVENT_TABLE() 
};


#endif //GCURVE_H
