////wxDelayPanel.h/////////////////////////////////////////////////////////////////////////
//
//
/////////////////////////////////////////////////////////////////////////////

#ifndef WXDELAYPANEL_H
#define WXDELAYPANEL_H

/*
#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "wxDelayPanel.cpp"
#endif
*/

#include "wxVstEditor.h"
#include "ADelay.hpp"
//#include "GButton.h"
//#include "../Layout/ok.xpm"
//#include "../Layout/ok-hover.xpm"
//#include "../Layout/ok-click.xpm"

//class wxBoxSizer;

/*
#define ID_PANEL 10005
#define SYMBOL_WXDELAYPANEL_STYLE 0
#define SYMBOL_WXDELAYPANEL_TITLE _("wxDelayPanel")
#define SYMBOL_WXDELAYPANEL_IDNAME ID_PANEL
#define SYMBOL_WXDELAYPANEL_SIZE wxSize(640, 480)
#define SYMBOL_WXDELAYPANEL_POSITION wxPoint(0, 0)
#define ID_DELAY_SLIDER 10000
#define wxID_STATIC_DELAY 10002
#define wxID_STATIC_DELAY_DISPLAY 10007
#define ID_FEEDBACK_SLIDER 10001
#define wxID_STATIC_FEEDBACK 10003
#define wxID_STATIC_FEEDBACK_DISPLAY 10008
#define ID_VOLUME_SLIDER 10004
#define wxID_STATIC_VOLUME 10006
#define wxID_STATIC_VOLUME_DISPLAY 10009
*/

/*
#ifndef wxCLOSE_BOX
#define wxCLOSE_BOX 0x1000
#endif
#ifndef wxFIXED_MINSIZE
#define wxFIXED_MINSIZE 0
#endif
*/

/////////////////////////////////////
class wxDelayPanel: public wxVstPanel
{    
    

public:
    // Create panel without physical windows and set the creating VST editor
    wxDelayPanel( wxVstEditor* );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = 10005, const wxPoint& pos = wxPoint(0,0), const wxSize& size = wxSize(640, 480), long style = 0 );

    /// Creates the controls and sizers
    void CreateControls();
    //void OnChar( wxKeyEvent& event );
    //void OnKeyDown( wxKeyEvent& event );
    //void OnDelaySliderUpdated( wxCommandEvent& event );
    //void OnFeedbackSliderUpdated( wxCommandEvent& event );
    //void OnVolumeSliderUpdated( wxCommandEvent& event );

    //wxBitmap GetBitmapResource( const wxString& name );
    //wxIcon GetIconResource( const wxString& name );

    //static bool ShowToolTips();
    wxBoxSizer* topsizer;
    //wxSlider* delayFader;
    //wxStaticText* delayDisplay;
    //wxSlider* feedbackFader;
    //wxStaticText* feedbackDisplay;
    //wxSlider* volumeFader;
    //wxStaticText* volumeDisplay;

	//virtual void setParameter (long index, float value);
	//virtual float getParameter (long index);

	DECLARE_EVENT_TABLE()
};

#endif // WXDELAYPANEL_H
