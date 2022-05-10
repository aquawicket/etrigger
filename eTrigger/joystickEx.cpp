/////////////////////////////////////////////////////////////////////////////
// Name:        wxJoystickEx
// Purpose:     Joystick Extended class, interface for a joystick with up to
// 6 axis, and 32 buttons.
// Author:
// Modified by:
// Created:
// RCS-ID:      $Id$
// Copyright:   (c) Guilhem Lavaux
// Licence:

/////////////////////////////////////////////////////////////////////////////

/*
 * Windows Multimedia
 * About Joysticks
 *
 * The joystick is an ancillary input device for applications that provide
 * alternatives to using the keyboard and mouse. The joystick provides
 * positional information within a coordinate system that has absolute
 * maximum and minimum values in each axis of movement.
 *
 * Joystick services are loaded when the operating system is started. The
 * joystick services can simultaneously monitor two joysticks, each with
 * two- or three-axis movement. Each joystick can have up to four buttons.
 * You can use the joystick functions to determine the capabilities of the
 * joysticks and joystick driver. Also, you can process a joystick's positional
 *  and button information by querying the joystick directly or by capturing
 * the joystick and processing messages from it. The latter method is simpler
 * because your application does not have to manually query the joystick or
 * track the time to generate queries at regular intervals.
 */
// For compilers that support precompilation, includes "wx.h".
#include "stdwx.h"
#include "wx/wxprec.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#if wxUSE_JOYSTICK
#ifdef WIN32
#ifndef WX_PRECOMP
// Include your minimal set of headers here, or wx.h
    #include "wx/event.h" // this include wxThread
    #include "wx/string.h"
    #include "wx/window.h"
#endif

// ... now your other include files ...
#ifdef WIN32
#include "wx/msw/private.h"
#endif //WIN32


#if !defined(__GNUWIN32_OLD__) || defined(__CYGWIN10__)
#ifdef WIN32
    #include <mmsystem.h>
#endif //WIN32
#endif

// Why doesn't BC++ have joyGetPosEx?
#if !defined(__WIN32__) || defined(__BORLANDC__)
#define NO_JOYGETPOSEX
#endif

#ifndef __WINE__
    // Needed for the product Name functions.
#ifdef WIN32
    #include "wx/msw/registry.h"
    #include <regstr.h>
#endif //WIN32
#endif

#include "joystickEx.h"

// Minimum and maximum values for polling, given in milliseconds.
#define MIN_POLLING 10
#define MAX_POLLLING 1000
#define MAX_BUTTONS 32
#define MAX_JOYSTICKID 15

enum {
    wxJS_AXIS_X = 0,
    wxJS_AXIS_Y,
    wxJS_AXIS_Z,
    wxJS_AXIS_RUDDER,
    wxJS_AXIS_U,
    wxJS_AXIS_V,
    wxJS_AXIS_POV,

    wxJS_AXIS_MAX = 32767,
    wxJS_AXIS_MIN = -32767
};


////////////////////////////////////////////////////////////////////////////
// Background thread for reading the joystick device
////////////////////////////////////////////////////////////////////////////

class wxJoystickExThread : public wxThread
{
public:
    wxJoystickExThread(wxJoystickEx* pJoy);
    void* Entry();

private:
    int       m_polling;
    wxJoystickEx* m_joy;

    // Allow wxJoystickEx to change the m_polling.
    friend class wxJoystickEx;
};

wxJoystickExThread::wxJoystickExThread(wxJoystickEx* pJoy)
    : m_polling(0)
{
    m_joy = pJoy;
}

void* wxJoystickExThread::Entry()
{
    while (true)
    {
        if (TestDestroy())
            break;

        // Update the joystick values
        m_joy->Update();

        // Put the thread to sleep
        Sleep(m_polling);
    }

    return NULL;
}

////////////////////////////////////////////////////////////////////////////

wxJoystickEx::wxJoystickEx(int joystick)
    : m_device(-1),
      m_thread(NULL),
      m_catchwin(NULL),
      m_buttonMask(0),
      m_moveThresh(0)
{
    JOYINFO joyInfo;
    unsigned int i, maxsticks = 2;

    if ((maxsticks = joyGetNumDevs()) == 0)
	    // There is no system driver for joystick in the OS.
	    // return ERR_NODRIVER;
	    return;

    // Parse input values
    if (joystick > MAX_JOYSTICKID) return;

    // Init data members
    wxZeroMemory(m_data);
    wxZeroMemory(m_caps);

    for( i = 0; i < maxsticks; ++i ) {
        // Look for attached device
        // i = 0 --> JOYSTICKID1
        // i = 1 --> JOYSTICKID2
        if( joyGetPos(i, &joyInfo) == JOYERR_NOERROR ) {
            if( !joystick ) {
                // Found the one we want,
                // store actual OS id
                m_data.joyId = i;
                m_device = i;
                // Find the capabilities for this joystick
                FindCapabilities(i);
                // and return
                break;
            }
            joystick --;
        }
    }

    // If found the one we want... create the thread.
    if (m_device != -1) {
        m_thread = new wxJoystickExThread(this);
        m_thread->Create();
        m_thread->Run();
    }
}

wxJoystickEx::~wxJoystickEx()
{
    ReleaseCapture();
    if (m_thread)
        m_thread->Delete();  // It's detached so it will delete itself
}

void wxJoystickEx::FindCapabilities(int joyId)
{
    JOYCAPS joyCaps;
    wxUint16 i;

    wxZeroMemory(joyCaps);
    // Get the capabilities
    if (joyGetDevCaps(joyId, &joyCaps, sizeof(JOYCAPS)) == JOYERR_NOERROR) {
        m_caps.m_Mid = joyCaps.wMid;
        m_caps.m_Pid = joyCaps.wPid;
        m_caps.m_Xmin = joyCaps.wXmin;
		m_caps.m_Xmax = joyCaps.wXmax;
        m_caps.m_Ymin = joyCaps.wYmin;
		m_caps.m_Ymax = joyCaps.wYmax;
        m_caps.m_Zmin = joyCaps.wZmin;
		m_caps.m_Zmax = joyCaps.wZmax;
		m_caps.m_Rmin = joyCaps.wRmin;        
		m_caps.m_Rmax = joyCaps.wRmax;
		m_caps.m_Umin = joyCaps.wUmin;
		m_caps.m_Umax = joyCaps.wUmax;
		m_caps.m_Vmin = joyCaps.wVmin;
		m_caps.m_Vmax = joyCaps.wVmax;
        m_caps.m_NumButtons = joyCaps.wNumButtons;
        m_caps.m_NumAxes= joyCaps.wNumAxes;
        m_caps.m_MaxButtons = joyCaps.wMaxButtons;
        m_caps.m_MaxAxes= joyCaps.wMaxAxes;
        m_caps.m_Caps = joyCaps.wCaps;
        m_caps.m_PeriodMin = MIN_POLLING;
        m_caps.m_PeriodMax = MAX_POLLLING;
    }

    // Check values
    if (m_caps.m_NumButtons > MAX_BUTTONS)
        m_caps.m_NumButtons = 0;
    if (m_caps.m_NumAxes > MAX_AXIS)
        m_caps.m_NumAxes = 0;

    for (i = 0; i < m_caps.m_NumButtons; ++i) {
	    m_buttonMask |= (1 << i);
    }
}

////////////////////////////////////////////////////////////////////////////
// State
////////////////////////////////////////////////////////////////////////////
bool wxJoystickEx::GetPosExtended(wxJoystickEvent &jwx_event)
{
    bool new_event = false;
    // use the Extended position
    JOYINFOEX joyInfo;

    // For good measure.
    wxZeroMemory(joyInfo);
    joyInfo.dwSize = sizeof(JOYINFOEX);
    // Note: With game pad, it takes no more time to return all
    // information from the joystick than it does to get only
    // the button states or axis.
    joyInfo.dwFlags = JOY_RETURNALL;

    // JoyGetPosEx will fill in the joyinfoex struct with all the
    // joystick information.
    if (joyGetPosEx(m_data.joyId, &joyInfo) == JOYERR_NOERROR) {
			// Event Joy Move, make it exclusive
			if (m_data.axe[wxJS_AXIS_X] != static_cast<wxUint16>(joyInfo.dwXpos)) {
			    m_data.axe[wxJS_AXIS_X] = static_cast<wxUint16>(joyInfo.dwXpos);
				jwx_event.SetEventType(wxEVT_JOY_MOVE);
				new_event = true;
			} else if (m_data.axe[wxJS_AXIS_Y] != static_cast<wxUint16>(joyInfo.dwYpos)) {
				m_data.axe[wxJS_AXIS_Y] = static_cast<wxUint16>(joyInfo.dwYpos);
				jwx_event.SetEventType(wxEVT_JOY_MOVE);
				new_event = true;
			} else if ( HasZ() && (m_data.axe[wxJS_AXIS_Z] != static_cast<wxUint16>(joyInfo.dwZpos))) {
				m_data.axe[wxJS_AXIS_Z] = static_cast<wxUint16>(joyInfo.dwZpos);
				jwx_event.SetEventType(wxEVT_JOY_ZMOVE);
				new_event = true;
			} else if (m_data.axe[wxJS_AXIS_RUDDER] != static_cast<wxUint16>(joyInfo.dwRpos)) {
				m_data.axe[wxJS_AXIS_RUDDER] = static_cast<wxUint16>(joyInfo.dwRpos);
				jwx_event.SetEventType(wxEVT_JOY_MOVE);
				new_event = true;
			} else if ( HasU() && (m_data.axe[wxJS_AXIS_U] != static_cast<wxUint16>(joyInfo.dwUpos))) {
				m_data.axe[wxJS_AXIS_U] = static_cast<wxUint16>(joyInfo.dwUpos);
				jwx_event.SetEventType(wxEVT_JOY_MOVE);
				new_event = true;
			} else if ( HasV() && (m_data.axe[wxJS_AXIS_V] != static_cast<wxUint16>(joyInfo.dwVpos))) {
				m_data.axe[wxJS_AXIS_V] = static_cast<wxUint16>(joyInfo.dwVpos);
				jwx_event.SetEventType(wxEVT_JOY_MOVE);
				new_event = true;
			} else if ( HasPOV() && ( m_data.axe[wxJS_AXIS_POV] != static_cast<wxUint16>(joyInfo.dwPOV))) {
			    // dwPOS
			    // Current position of the point-of-view control.
			    // Values for this member are in the range 0 through 35,900.
			    // These values represent the angle, in degrees, of each view
			    // multiplied by 100.
			    if ((joyInfo.dwPOV >= 0) && ( joyInfo.dwPOV <= 35900)) {
                    m_data.axe[wxJS_AXIS_POV] = static_cast<wxUint16>(joyInfo.dwPOV);
                    jwx_event.SetEventType(wxEVT_JOY_MOVE);
                    new_event = true;
                }
			}

			if ( (m_data.buttons & m_buttonMask) != (static_cast<wxUint32>(joyInfo.dwButtons) & m_buttonMask)) {
				wxUint16 i = 0;
				wxUint32 button = 0, joyButton = 0;

				// An button has change
				for ( i = 0; i < (m_caps.m_NumButtons); ++i) {
					button = (m_data.buttons & (1 << i));
					joyButton = (static_cast<wxUint32>(joyInfo.dwButtons) & (1 << i));
					if ( button != joyButton) {
						if (joyButton) {
							m_data.buttons |= (1 << i);
							jwx_event.SetEventType(wxEVT_JOY_BUTTON_DOWN);
						} else {
							m_data.buttons &= ~(1 << i);
							jwx_event.SetEventType(wxEVT_JOY_BUTTON_UP);
						}
						break;
					}
				}
				jwx_event.SetButtonChange(i);
				new_event = true;
			}
        }
        return new_event;
}

bool wxJoystickEx::GetPosBasic(wxJoystickEvent &jwx_event)
{
    bool new_event = false;

    // Joystick with 3 Axis
    JOYINFO joyInfo;

    wxZeroMemory(joyInfo);

    if (joyGetPos(m_data.joyId, &joyInfo) == JOYERR_NOERROR) {
        // Event Joy Move
        if (m_data.axe[wxJS_AXIS_X] != static_cast<wxUint16>(joyInfo.wXpos)) {
            m_data.axe[wxJS_AXIS_X] = static_cast<wxUint16>(joyInfo.wXpos);
            jwx_event.SetEventType(wxEVT_JOY_MOVE);
			new_event = true;
        } else if (m_data.axe[wxJS_AXIS_Y] != static_cast<wxUint16>(joyInfo.wYpos)) {
			m_data.axe[wxJS_AXIS_Y] = static_cast<wxUint16>(joyInfo.wYpos);
			jwx_event.SetEventType(wxEVT_JOY_MOVE);
			new_event = true;
		} else if (m_data.axe[wxJS_AXIS_Z] != static_cast<wxUint16>(joyInfo.wZpos)) {
			m_data.axe[wxJS_AXIS_Z] = static_cast<wxUint16>(joyInfo.wZpos);
			jwx_event.SetEventType(wxEVT_JOY_ZMOVE);
			new_event = true;
		}

        // Do not limit only to 4 buttons
		if ( (m_data.buttons & m_buttonMask) != (static_cast<wxUint32>(joyInfo.wButtons & m_buttonMask))) {
			wxUint16 i = 0, button = 0, joyButton = 0;

			// An button has change
			for ( i = 0; i < (m_caps.m_NumButtons); ++i) {
                button = (m_data.buttons & (1 << i));
				joyButton = (static_cast<wxUint16>(joyInfo.wButtons) & (1 << i));
				if ( button != joyButton) {
					if (joyButton) {
						m_data.buttons |= (1 << i);
						jwx_event.SetEventType(wxEVT_JOY_BUTTON_DOWN);
					} else {
						m_data.buttons &= ~(1 << i);
						jwx_event.SetEventType(wxEVT_JOY_BUTTON_UP);
					}
					break;
				}
			}
			jwx_event.SetButtonChange(i);
			new_event = true;
        }
    }
    return new_event;
}

void wxJoystickEx::Update(void)
{
    bool new_event = false;
    wxJoystickEvent jwx_event;

    if (HasRudder()) {
#ifndef NO_JOYGETPOSEX

        new_event = GetPosExtended(jwx_event);

#else

        new_event = GetPosBasic(jwx_exent);

#endif
    } else {

        new_event = GetPosBasic(jwx_event);
	}

	if (new_event) {
	    wxDateTime now = wxDateTime::Now();
	    wxPoint pos(m_data.axe[wxJS_AXIS_X], m_data.axe[wxJS_AXIS_Y]);

		jwx_event.SetTimestamp(now.GetMillisecond());
		jwx_event.SetJoystick(m_data.joyId);
		jwx_event.SetButtonState(m_data.buttons);
		jwx_event.SetPosition(pos);
		jwx_event.SetZPosition(m_data.axe[wxJS_AXIS_Z]);
		jwx_event.SetEventObject(m_catchwin);

		if (m_catchwin){
		    //FIXME     AddPendingEvent is a protected member
			//m_catchwin->AddPendingEvent(jwx_event);
		}
	}
}

wxPoint wxJoystickEx::GetPosition() const
{
    wxPoint pos(m_data.axe[wxJS_AXIS_X], m_data.axe[wxJS_AXIS_Y]);
    return pos;
}

int wxJoystickEx::GetZPosition() const
{
    return m_data.axe[wxJS_AXIS_Z];
}

int wxJoystickEx::GetButtonState() const
{
    return m_data.buttons;
}

int wxJoystickEx::GetPOVPosition() const
{
    // Returns the point-of-view position, expressed in continuous,
    // one-hundredth of a degree units, but limited to return
    // 0, 9000, 18000 or 27000. Returns -1 on error.
    return ((m_data.axe[wxJS_AXIS_POV] % 9000) * 9000);
}

int wxJoystickEx::GetPOVCTSPosition() const
{
    // Returns the point-of-view position, expressed in continuous,
    // one-hundredth of a degree units. Returns -1 on error.
    return m_data.axe[wxJS_AXIS_POV];
}

int wxJoystickEx::GetRudderPosition() const
{
        return m_data.axe[wxJS_AXIS_RUDDER];
}

int wxJoystickEx::GetUPosition() const
{
        return m_data.axe[wxJS_AXIS_U];
}

int wxJoystickEx::GetVPosition() const
{
        return m_data.axe[wxJS_AXIS_V];
}

int wxJoystickEx::GetMovementThreshold() const
{
    /*
    The movement threshold is the distance the joystick must be moved before
    a joystick position-change message (MM_JOY1MOVE, MM_JOY1ZMOVE,
    MM_JOY2MOVE, or MM_JOY2ZMOVE) is sent to a window that has captured the
    device. The threshold is initially zero.
    */

    unsigned int thresh = 0;
    MMRESULT res = joyGetThreshold(m_data.joyId, &thresh);
    if (res == JOYERR_NOERROR )
    {
        return static_cast<int>(thresh);
    }
    return 0;
}

void wxJoystickEx::SetMovementThreshold(int threshold)
{
    joySetThreshold(m_data.joyId, static_cast<UINT>(threshold));
}

////////////////////////////////////////////////////////////////////////////
// Capabilities
////////////////////////////////////////////////////////////////////////////

bool wxJoystickEx::IsOk() const
{
    return (m_device != -1);
}

/**
    johan@linkdata.se 2002-08-20:
    Now returns the number of connected, functioning
    joysticks, as intended.
*/
int wxJoystickEx::GetNumberJoysticks(void)
{
    JOYINFO joyInfo;
    int i, maxsticks, actualsticks;

    maxsticks = joyGetNumDevs();
    actualsticks = 0;
    for( i=0; i<maxsticks; ++i )
    {
        if( joyGetPos( i, &joyInfo ) == JOYERR_NOERROR )
        {
            ++actualsticks;
        }
    }
    return actualsticks;
}

int wxJoystickEx::GetManufacturerId() const
{
    return m_caps.m_Mid;
}

int wxJoystickEx::GetProductId() const
{
    return m_caps.m_Pid;
}

wxString wxJoystickEx::GetProductName() const
{
    wxString str;
#ifndef __WINE__
    JOYCAPS joyCaps;
    if (joyGetDevCaps(m_data.joyId, &joyCaps, sizeof(joyCaps)) != JOYERR_NOERROR)
        return wxEmptyString;

    wxRegKey key1(wxString::Format(wxT("HKEY_LOCAL_MACHINE\\%s\\%s\\%s"),
                   REGSTR_PATH_JOYCONFIG, joyCaps.szRegKey, REGSTR_KEY_JOYCURR));

    key1.QueryValue(wxString::Format(wxT("Joystick%d%s"),
                                     m_data.joyId + 1, REGSTR_VAL_JOYOEMNAME),
                    str);

    wxRegKey key2(wxString::Format(wxT("HKEY_LOCAL_MACHINE\\%s\\%s"),
                                        REGSTR_PATH_JOYOEM, str.c_str()));
    key2.QueryValue(REGSTR_VAL_JOYOEMNAME, str);
#endif
    return str;
}

int wxJoystickEx::GetXMin() const
{
    return m_caps.m_Xmin;
}

int wxJoystickEx::GetYMin() const
{
    return m_caps.m_Ymin;
}

int wxJoystickEx::GetZMin() const
{
    return m_caps.m_Zmin;
}

int wxJoystickEx::GetXMax() const
{
    return m_caps.m_Xmax;
}

int wxJoystickEx::GetYMax() const
{
    return m_caps.m_Ymax;
}

int wxJoystickEx::GetZMax() const
{
    return m_caps.m_Zmax;
}

int wxJoystickEx::GetNumberButtons() const
{
    return m_caps.m_NumButtons;
}

int wxJoystickEx::GetNumberAxes() const
{
    return m_caps.m_NumAxes;
}

int wxJoystickEx::GetMaxButtons() const
{
    return m_caps.m_MaxButtons;
}

int wxJoystickEx::GetMaxAxes() const
{
    return m_caps.m_MaxAxes;
}

int wxJoystickEx::GetPollingMin() const
{
    return m_caps.m_PeriodMin;
}

int wxJoystickEx::GetPollingMax() const
{
    return m_caps.m_PeriodMax;
}

int wxJoystickEx::GetRudderMin() const
{
    return m_caps.m_Rmin;
}

int wxJoystickEx::GetRudderMax() const
{
    return m_caps.m_Rmax;
}

int wxJoystickEx::GetUMin() const
{
    return m_caps.m_Umin;
}

int wxJoystickEx::GetUMax() const
{
    return m_caps.m_Umax;
}

int wxJoystickEx::GetVMin() const
{
    return m_caps.m_Vmin;
}

int wxJoystickEx::GetVMax() const
{
    return m_caps.m_Vmax;
}

bool wxJoystickEx::HasRudder() const
{
    return ((m_caps.m_Caps & JOYCAPS_HASR) == JOYCAPS_HASR);
}

bool wxJoystickEx::HasZ() const
{
    return ((m_caps.m_Caps & JOYCAPS_HASZ) == JOYCAPS_HASZ);
}

bool wxJoystickEx::HasU() const
{
    return ((m_caps.m_Caps & JOYCAPS_HASU) == JOYCAPS_HASU);
}

bool wxJoystickEx::HasV() const
{
    return ((m_caps.m_Caps & JOYCAPS_HASV) == JOYCAPS_HASV);
}

bool wxJoystickEx::HasPOV() const
{
    return ((m_caps.m_Caps & JOYCAPS_HASPOV) == JOYCAPS_HASPOV);
}

bool wxJoystickEx::HasPOV4Dir() const
{
    return ((m_caps.m_Caps & JOYCAPS_POV4DIR) == JOYCAPS_POV4DIR);
}

bool wxJoystickEx::HasPOVCTS() const
{
    return ((m_caps.m_Caps & JOYCAPS_POVCTS) == JOYCAPS_POVCTS);
}

////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////

bool wxJoystickEx::SetCapture(wxWindow* win, int pollingFreq)
{
    m_catchwin = win;
    if (m_thread)
    {
        if ((pollingFreq >= m_caps.m_PeriodMin) && (pollingFreq <= m_caps.m_PeriodMax))
            m_thread->m_polling = pollingFreq;
        if (pollingFreq == 0) {
            m_moveThresh = GetMovementThreshold();
            SetMovementThreshold(0);
        }
        return true;
    }
    return false;
}

bool wxJoystickEx::ReleaseCapture()
{
    m_catchwin = NULL;
    if (m_thread)
    {
        m_thread->m_polling = 0;
        SetMovementThreshold(m_moveThresh);
        return true;
    }
    return false;
}

#endif //WIN32
#endif  // wxUSE_JOYSTICK
