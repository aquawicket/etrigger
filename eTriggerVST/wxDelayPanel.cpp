////wxDelayPanel.cpp/////////////////////////////////////////////////////////////////////////
//
//
/////////////////////////////////////////////////////////////////////////////

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma implementation "wxDelayPanel.h"
#endif

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#include "wxDelayPanel.h"

/////////////////////////////////////////////
BEGIN_EVENT_TABLE( wxDelayPanel, wxVstPanel )
    EVT_CHAR( wxDelayPanel::OnChar )
    EVT_KEY_DOWN( wxDelayPanel::OnKeyDown )
    EVT_SLIDER( ID_DELAY_SLIDER, wxDelayPanel::OnDelaySliderUpdated )
    EVT_SLIDER( ID_FEEDBACK_SLIDER, wxDelayPanel::OnFeedbackSliderUpdated )
    EVT_SLIDER( ID_VOLUME_SLIDER, wxDelayPanel::OnVolumeSliderUpdated )
END_EVENT_TABLE()

/////////////////////////////////////////////////////////////////////////
 wxDelayPanel::wxDelayPanel( wxVstEditor* editor ) : wxVstPanel( editor )
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool wxDelayPanel::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
    topsizer = NULL;
    delayFader = NULL;
    delayDisplay = NULL;
    feedbackFader = NULL;
    feedbackDisplay = NULL;
    volumeFader = NULL;
    volumeDisplay = NULL;

    wxVstPanel::Create( parent, id, pos, size, style );

    CreateControls();
    GetSizer()->Fit(this);
    GetSizer()->SetSizeHints(this);

    return TRUE;
}

///////////////////////////////////
void wxDelayPanel::CreateControls()
{    
	GButton *theButton = new GButton(this, -1, wxPoint(10,10), ok_xpm, ok_hover_xpm, ok_click_xpm);

	wxDialog *newWin = new wxDialog(this, -1, wxT(""), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, wxT(""));
	newWin->Show(true);

    wxDelayPanel* itemVstPanel1 = this;

    topsizer = new wxBoxSizer(wxHORIZONTAL);
    itemVstPanel1->SetSizer(topsizer);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxVERTICAL);
    topsizer->Add(itemBoxSizer3, 1, wxALIGN_CENTER_VERTICAL, 5);

    delayFader = new wxSlider( itemVstPanel1, ID_DELAY_SLIDER, 0, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL|wxSL_INVERSE );
    itemBoxSizer3->Add(delayFader, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticText* itemStaticText5 = new wxStaticText( itemVstPanel1, wxID_STATIC_DELAY, _("Delay"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add(itemStaticText5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxADJUST_MINSIZE, 5);

    delayDisplay = new wxStaticText( itemVstPanel1, wxID_STATIC_DELAY_DISPLAY, _("Delay Display"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE|wxST_NO_AUTORESIZE );
    itemBoxSizer3->Add(delayDisplay, 0, wxALIGN_CENTER_HORIZONTAL|wxTOP|wxBOTTOM|wxADJUST_MINSIZE, 5);

    wxBoxSizer* itemBoxSizer7 = new wxBoxSizer(wxVERTICAL);
    topsizer->Add(itemBoxSizer7, 1, wxALIGN_CENTER_VERTICAL, 5);

    feedbackFader = new wxSlider( itemVstPanel1, ID_FEEDBACK_SLIDER, 0, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL|wxSL_INVERSE );
    itemBoxSizer7->Add(feedbackFader, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticText* itemStaticText9 = new wxStaticText( itemVstPanel1, wxID_STATIC_FEEDBACK, _("Feedback"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer7->Add(itemStaticText9, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxADJUST_MINSIZE, 5);

    feedbackDisplay = new wxStaticText( itemVstPanel1, wxID_STATIC_FEEDBACK_DISPLAY, _("Feedback Display"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE|wxST_NO_AUTORESIZE );
    itemBoxSizer7->Add(feedbackDisplay, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxADJUST_MINSIZE, 5);

    wxBoxSizer* itemBoxSizer11 = new wxBoxSizer(wxVERTICAL);
    topsizer->Add(itemBoxSizer11, 1, wxALIGN_CENTER_VERTICAL, 5);

    volumeFader = new wxSlider( itemVstPanel1, ID_VOLUME_SLIDER, 0, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL|wxSL_INVERSE );
    itemBoxSizer11->Add(volumeFader, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticText* itemStaticText13 = new wxStaticText( itemVstPanel1, wxID_STATIC_VOLUME, _("Volume"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer11->Add(itemStaticText13, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxADJUST_MINSIZE, 5);

    volumeDisplay = new wxStaticText( itemVstPanel1, wxID_STATIC_VOLUME_DISPLAY, _("Volume Display"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE|wxST_NO_AUTORESIZE );
    itemBoxSizer11->Add(volumeDisplay, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxADJUST_MINSIZE, 5);

	topsizer->SetSizeHints( this );
}

/////////////////////////////////
bool wxDelayPanel::ShowToolTips()
{
    return TRUE;
}

////////////////////////////////////////////////////////////////
wxBitmap wxDelayPanel::GetBitmapResource( const wxString& name )
{
    return wxNullBitmap;
}

////////////////////////////////////////////////////////////
wxIcon wxDelayPanel::GetIconResource( const wxString& name )
{
    return wxNullIcon;
}

/////////////////////////////
static double round(double x)
{
	return (int)(x + 0.5);
}

/////////////////////////////////////////////////////////
void wxDelayPanel::setParameter (long index, float value)
{
	switch (index)
	{
	case kDelay:
		delayFader->SetValue( round(value * 100) );
		delayDisplay->SetLabel( wxString::Format( wxT("%.2f"), value ) );
		break;
	case kFeedBack:
		feedbackFader->SetValue( round(value * 100) );
		feedbackDisplay->SetLabel( wxString::Format( wxT("%.0f%%"), value * 100 ) );
		break;
	case kOut:
		volumeFader->SetValue( round(value * 100) );
		volumeDisplay->SetLabel( wxString::Format( wxT("%.0f%%"), value * 100 ) );
		break;
	}
}

/////////////////////////////////////////////
float wxDelayPanel::getParameter (long index)
{
	switch (index)
	{
	case kDelay:
		return (float)delayFader->GetValue() / 100;
		break;
	case kFeedBack:
		return (float)feedbackFader->GetValue() / 100;
		break;
	case kOut:
		return (float)volumeFader->GetValue() / 100;
		break;
	}

	return 0;
}

////////////////////////////////////////////////////////////////
void wxDelayPanel::OnDelaySliderUpdated( wxCommandEvent& event )
{
	getEditor()->parameterChanged( kDelay );
}

///////////////////////////////////////////////////////////////////
void wxDelayPanel::OnFeedbackSliderUpdated( wxCommandEvent& event )
{
	getEditor()->parameterChanged( kFeedBack );
}

/////////////////////////////////////////////////////////////////
void wxDelayPanel::OnVolumeSliderUpdated( wxCommandEvent& event )
{
    getEditor()->parameterChanged( kOut );
}

//////////////////////////////////////////////
void wxDelayPanel::OnChar( wxKeyEvent& event )
{
    event.Skip();
}

/////////////////////////////////////////////////
void wxDelayPanel::OnKeyDown( wxKeyEvent& event )
{
    event.Skip();
}


