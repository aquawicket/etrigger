//// GSlider.h /////////////////////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef GSLIDER_H
#define GSLIDER_H

#include "GObject.h"
#include <wx/window.h>
#include <wx/panel.h>
#include <wx/dcbuffer.h> 
#include <wx/msgdlg.h>
#include <wx/image.h>
#include <vector>

#define FDR_NO_MOUSE_CAPTURE 0x0001 

//Device class to send to callback
///////////////////////////////////
typedef struct{
	wxImage slider;
	wxImage focused;
	bool hover;
	bool click;
	bool knobFocused;
	int knobPosX;
	int knobPosY; 
	int knobWidth; 
	int knobHeight;
	float currentValue;
	float defaultValue;
	int mouseOffsetY;
}Knobs;

/////////////////////////////////////////
class GSliderEvent: public wxCommandEvent 
{ 

public: 
	GSliderEvent(wxEventType commandType = wxEVT_NULL, int id = 0 ); 

	float GetValue() const { return m_faderValue; } 
	void SetValue(float value) { m_faderValue = value; } 
	int GetKnobNumber() const { return knobNumber; } 
	void SetKnobNumber(int value) { knobNumber = value; } 

	virtual wxEvent *Clone() const { return new GSliderEvent(*this); } 

private: 
	float m_faderValue;
	int knobNumber;

	DECLARE_DYNAMIC_CLASS(GSliderEvent) 
}; 


BEGIN_DECLARE_EVENT_TYPES() 
	DECLARE_EVENT_TYPE(wxEVT_COMMAND_GSLIDER, -1) 
END_DECLARE_EVENT_TYPES() 

typedef void (wxEvtHandler::*wxGSliderEventFunction)(GSliderEvent&); 

#define EVT_GSLIDER(id, fn) \
	DECLARE_EVENT_TABLE_ENTRY(wxEVT_COMMAND_GSLIDER, id, -1,  \
	(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)  \
	wxStaticCastEvent(wxGSliderEventFunction, & fn), (wxObject *) NULL ),


//////////////////////////////
class GSlider : public GObject
{ 
	public: 
		GSlider(wxWindow* parent, int id, const wxPoint& pos, const wxString& sliderBG, const wxString& sliderKnob);
		~GSlider(); 
		void Render(wxDC &dc);
		void Render(wxGraphicsContext &gc);
		bool OnMouse(wxMouseEvent &event);
		bool HasMouse(wxMouseEvent &event);

		void SetRange(float minValue, float maxValue); 
		float GetMin() const; 
		float GetMax() const; 
		float GetValue(int num);
		void SetValue(int num, float value); 
		void SetDefault(int num, float value);
		void CalcGeometry(int num);
		void AddKnob();
		void DeleteKnob();

		int GetWheelStep() const; 
		void SetWheelStep(int step); 

		bool backFocused;

	protected: 

		void Init(); 
		float NormalizeValue(float value) const; 
		//bool UseMouseCapture(); 
		wxCoord ValueToVertPosition(float value); 
		float ValueFromVertPosition(wxCoord position); 
		void DrawBackground(wxDC &dc); 
		void DrawFaders(wxDC &dc); 
		wxString FormatValue(float value) const; 

	private: 
		// Track size 
		int m_trackPosX, 
			m_trackPosY, 
			m_trackWidth, 
			m_trackHeight; 

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
		//int m_mouseOffsetY;
		bool m_draggingFader;
		int activeKnob;

		// value 
		float m_minValue;
		float m_maxValue; 
		float m_currentValue; 

		wxWindow *mainPanel;
		int myId;
		wxPoint position;
		wxPoint drag;
		bool dragging;
		wxImage c_slider;
		wxImage c_back;
		wxImage c_backFocused;
		wxImage c_hover;
		wxImage c_click;
		wxImage c_focused;

		double rotation;
		double xScale;
		double yScale;

		bool hover;
		bool click;
		bool knobFocused;

		/// Multiple Knobs ////////
		std::vector<Knobs> knobs;

		public:
		int knobCount;
		///////////////////////////

		//DECLARE_EVENT_TABLE() 
};

#endif //GSLIDER_H