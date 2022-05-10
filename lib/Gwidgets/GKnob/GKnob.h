//// GKnob.h /////////////////////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef GKNOB_H
#define GKNOB_H

#include <wx/window.h>
#include <wx/panel.h>
#include <wx/dcbuffer.h> 
#include <wx/msgdlg.h>
#include <wx/image.h>

#define FDR_NO_MOUSE_CAPTURE 0x0001

///////////////////////////////////////
class GKnobEvent: public wxCommandEvent 
{ 
	public: 
		GKnobEvent(wxEventType commandType = wxEVT_NULL, int id = 0 ); 

		// Accessors 
		float GetValue() const { return m_faderValue; } 
		void SetValue(float value) { m_faderValue = value; } 

		// required for sending with wxPostEvent() 
		virtual wxEvent *Clone() const { return new GKnobEvent(*this); } 

	
	private: 
		float m_faderValue; 

	DECLARE_DYNAMIC_CLASS(GKnobEvent) 
}; 

BEGIN_DECLARE_EVENT_TYPES() 
	DECLARE_EVENT_TYPE(wxEVT_COMMAND_GKNOB, -1) 
END_DECLARE_EVENT_TYPES() 

typedef void (wxEvtHandler::*wxGKnobEventFunction)(GKnobEvent&); 

#define EVT_GKNOB(id, fn) \
	DECLARE_EVENT_TABLE_ENTRY(wxEVT_COMMAND_GKNOB, id, -1,  \
	(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)  \
	wxStaticCastEvent(wxGKnobEventFunction, & fn), (wxObject *) NULL ),


///////////////////////////
class GKnob: public wxPanel
{ 
	public: 
	// Constructors 
		GKnob(); 
		GKnob(wxWindow* parent,
			wxWindowID id,// = wxID_ANY, 
			const wxPoint& pos,// = wxDefaultPosition, 
			long style,// = 0, 
			const wxString& name,// = wxPanelNameStr,
			const wxImage& back,
			const wxImage& knob); 

		GKnob(wxWindow* parent,
			wxWindowID id,// = wxID_ANY, 
			const wxPoint& pos,// = wxDefaultPosition, 
			long style,// = 0, 
			const wxString& name,// = wxPanelNameStr,
			const wxString& back,
			const wxString& knob); 

		GKnob(wxWindow* parent,
			wxWindowID id,// = wxID_ANY, 
			const wxPoint& pos,// = wxDefaultPosition, 
			long style,// = 0, 
			const wxString& name,// = wxPanelNameStr,
			const char** back,
			const char** knob); 

		// Destructor 
		virtual ~GKnob(); 

		// Creator 
		bool Create(wxWindow* parent,// = (wxWindow*) NULL, 
			wxWindowID id,// = wxID_ANY, 
			const wxPoint& pos,// = wxDefaultPosition, 
			long style,// = 0, 
			const wxString& name,// = wxPanelNameStr
			const wxImage& back,
			const wxImage& knob); 

		bool Create(wxWindow* parent,// = (wxWindow*) NULL, 
			wxWindowID id,// = wxID_ANY, 
			const wxPoint& pos,// = wxDefaultPosition, 
			long style,// = 0, 
			const wxString& name,// = wxPanelNameStr
			const wxString& back,
			const wxString& knob);

		bool Create(wxWindow* parent,// = (wxWindow*) NULL, 
			wxWindowID id,// = wxID_ANY, 
			const wxPoint& pos,// = wxDefaultPosition, 
			long style,// = 0, 
			const wxString& name,// = wxPanelNameStr
			const char** back,
			const char** knob); 

		// Accessors 
		virtual float GetValue() const; 
		virtual void SetValue(float value); 
		virtual void ResetStoredValue();

		virtual void SetRange(float minValue, float maxValue); 
		virtual float GetMin() const; 
		virtual float GetMax() const; 

		bool focused;

	protected: 
		// Common part of all constructors 
		void Init(); 

		// Normalize the value to fit in the range 
		float NormalizeValue(float value) const; 

		// Style accessors 
		bool UseMouseCapture(); 

		// Scale calculation 
		float ValueFromVertPosition(wxCoord position); 

		// Calculate size and position of everything 
		void CalcGeometry(); 

		// Control painting 
		void DrawBackground(wxDC &dc); 
		void DrawKnob(wxDC &dc); 

		wxString FormatValue(float value) const; 

		// Event handling 
		void OnSize(wxSizeEvent &event); 
		void OnEraseBackground(wxEraseEvent &event);
		void OnPaint(wxPaintEvent &event); 
		void OnMouse(wxMouseEvent &event); 
		void OnKeyDown(wxKeyEvent &event);

	private: 
		// Background Size 
		int m_BackPosX, 
			m_BackPosY, 
			m_BackWidth, 
			m_BackHeight; 

		// Knob size 
		int m_knobPosX, 
			m_knobPosY, 
			m_knobWidth, 
			m_knobHeight; 

		int m_tickPosY, 
			m_tickPosX, 
			m_tickWidth, 
			m_tickHeight; 

		// Mouse logic 
		int m_mouseOffsetY, 
			m_wheelRotation, 
			m_wheelStep; 
		bool m_draggingKnob, 
			m_wheelKnobMove; 

		// value 
		float m_minValue, 
			m_maxValue, 
			m_currentValue, 
		    storedValue,
		    gainValue;

		wxImage c_knob;
		wxImage c_back;

		DECLARE_EVENT_TABLE() 
};

#endif //GKNOB_H
