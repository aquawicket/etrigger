//// joystickEx.h /////////////////////////////////////////
//
///////////////////////////////////////////////////////////

#pragma once
#ifndef JOYSTICKEX_H
#define JOYSTICKEX_H

//#ifdef WIN32
#include "wx/event.h" // Declaration of wxJOYSTICK1, wxJoystickEvent

// Axis could be X, Y, Z, U, V, R, POV

#define MAX_AXIS 7
struct joyCapabilities
{
    // Capabilities of joystick
    wxUint16 m_Mid;
    wxUint16 m_Pid;
    wxUint16 m_Xmin;
    wxUint16 m_Xmax;
    wxUint16 m_Ymin;
    wxUint16 m_Ymax;
    wxUint16 m_Zmin;
    wxUint16 m_Zmax;
    wxUint16 m_Rmin;
    wxUint16 m_Rmax;
    wxUint16 m_Umin;
    wxUint16 m_Umax;
    wxUint16 m_Vmin;
    wxUint16 m_Vmax;
    wxUint16 m_NumButtons;
    wxUint16 m_MaxAxes;
    wxUint16 m_NumAxes;
    wxUint16 m_MaxButtons;
    wxUint16 m_PeriodMin;
    wxUint16 m_PeriodMax;
    wxUint16 m_Caps;
};

struct joyData
{
    wxInt16 joyId;
    wxUint16 axe[MAX_AXIS];
    wxUint32 buttons;
};

class wxJoystickExThread;

class wxJoystickEx : public wxObject
{
    public:
        /*
        * Public interface
        */
        wxJoystickEx(int joystick = wxJOYSTICK1);
        virtual ~wxJoystickEx();

        // Attributes
        ////////////////////////////////////////////////////////////////////////////

   //     friend void wxJoystickExThread::Update(wxJoystickEx &joy);
        wxPoint GetPosition(void) const;
        int GetZPosition(void) const;
        int GetButtonState(void) const;
        int GetPOVPosition(void) const;
        int GetPOVCTSPosition(void) const;
        int GetRudderPosition(void) const;
        int GetUPosition(void) const;
        int GetVPosition(void) const;
        int GetMovementThreshold(void) const;
        void SetMovementThreshold(int threshold) ;

        // Capabilities
        ////////////////////////////////////////////////////////////////////////////

        void FindCapabilities(int joyId);

        static int GetNumberJoysticks(void);
        bool IsOk(void) const; // Checks that the joystick is functioning
        int GetManufacturerId(void) const;
        int GetProductId(void) const;
        wxString GetProductName(void) const;
        int GetXMin(void) const;
        int GetYMin(void) const;
        int GetZMin(void) const;
        int GetXMax(void) const;
        int GetYMax(void) const;
        int GetZMax(void) const;
        int GetNumberButtons(void) const;
        int GetNumberAxes(void) const;
        int GetMaxButtons(void) const;
        int GetMaxAxes(void) const;
        int GetPollingMin(void) const;
        int GetPollingMax(void) const;
        int GetRudderMin(void) const;
        int GetRudderMax(void) const;
        int GetUMin(void) const;
        int GetUMax(void) const;
        int GetVMin(void) const;
        int GetVMax(void) const;

        bool HasRudder(void) const;
        bool HasZ(void) const;
        bool HasU(void) const;
        bool HasV(void) const;
        bool HasPOV(void) const;
        bool HasPOV4Dir(void) const;
        bool HasPOVCTS(void) const;

        // Operations
        ////////////////////////////////////////////////////////////////////////

        // pollingFreq = 0 means that movement events are sent when above the threshold.
        // If pollingFreq > 0, events are received every this many milliseconds.
        bool SetCapture(wxWindow* win, int pollingFreq = 0);
        bool ReleaseCapture(void);

    protected:
    private:
        int m_device;
        wxJoystickExThread* m_thread;
        wxWindow* m_catchwin;
        joyCapabilities m_caps;
	public:
        joyData m_data;
    private:
        wxUint32 m_buttonMask;
        wxUint16 m_moveThresh;

        void Update(void);
        bool GetPosExtended(wxJoystickEvent &jwx_event);
        bool GetPosBasic(wxJoystickEvent &jwx_event);

        friend class wxJoystickExThread;
};

//#endif //WIN32
#endif // JOYSTICKEX_H
