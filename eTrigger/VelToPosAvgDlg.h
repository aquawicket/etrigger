//// VelToPosAvgDlg.h /////////////////////////////////////////////////////////////////////////////
//
//   We want to show a multi-zone drum's velocity/position average
//   We can use this data to remove hotspots
//
//
///////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef VELTOPOSAVGDLG_H
#define VELTOPOSAVGDLG_H

#include <wx/dialog.h>
#include <wx/dc.h>
#include <wx/timer.h>

#include "Trigger.h"

#include "../lib/Gwidgets/GCurve/GCurve.h"

//class AvgTimer;
class Trigger;

///////////////////////////////////////
class VelToPosAvgDlg : public wxDialog
{
public:
	VelToPosAvgDlg(Trigger *trig);
	~VelToPosAvgDlg();

	void OnPaint(wxPaintEvent &WXUNUSED(event));
	void DrawGrid(wxDC &dc);
	void DrawAverage(wxDC &dc);
	void Notify();

	Trigger *trigger;

	GCurve *curve;
	//AvgTimer *timer;

	DECLARE_EVENT_TABLE() 
};


#endif //VELTOPOSAVGDLG_H

