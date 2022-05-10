//// Joystick.h /////////////////////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <wx/event.h>
#include <wx/joystick.h> 

#ifdef WIN32
#include "joystickEx.h"
class wxJoystickEx;
#endif

#include "Tracks.h"
#include "Process.h"


typedef struct{
#ifdef WIN32
	wxJoystickEx *wxjoy;
#endif //WIN32
#ifdef MAC
	wxJoystick *wxjoy;
#endif //MAC
	int minX;
	int maxX;
	int minY;
	int maxY;
	int minZ;
	int maxZ;
	int minR;
	int maxR;
	int minU;
	int maxU;
	int minV;
	int maxV;
}JOY;

////////////////////////////////
class Joystick : public wxWindow
{		
public:
	Joystick(MainPanel *parent);
	~Joystick();	

	void OnJoystick(wxJoystickEvent &event);
	wxArrayString GetDevices();
	void SetDevices(wxArrayString in);
	void Reload();
	int GetMinX();
	int GetMinY();
	int GetMinZ();
	int GetMinR();
	int GetMinU();
	int GetMinV();
	void SetMinX(int num);
	void SetMinY(int num);
	void SetMinZ(int num);
	void SetMinR(int num);
	void SetMinU(int num);
	void SetMinV(int num);
	int GetMaxX();
	int GetMaxY();
	int GetMaxZ();
	int GetMaxR();
	int GetMaxU();
	int GetMaxV();
	void SetMaxX(int num);
	void SetMaxY(int num);
	void SetMaxZ(int num);
	void SetMaxR(int num);
	void SetMaxU(int num);
	void SetMaxV(int num);
	void DetectMaxAxes();
	void ResetMaxAxes();

	MainPanel *mainPanel;
	TrackProc *trackProc;

	bool detectMaxAxes;
	int detectMinX;
	int detectMinY;
	int detectMinZ;
	int detectMinR;
	int detectMinU;
	int detectMinV;

	int detectMaxX;
	int detectMaxY;
	int detectMaxZ;
	int detectMaxR;
	int detectMaxU;
	int detectMaxV;

	int pollSpeed;
	wxArrayString selected;
	std::vector<JOY*> joy;

	bool dancePadFlags[10][4];

	DECLARE_EVENT_TABLE();
};

#endif //JOYSTICK_H

