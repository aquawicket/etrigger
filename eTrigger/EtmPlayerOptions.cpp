//// EtmPlayerOptions.cpp //////////////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "EtmPlayerOptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


BEGIN_EVENT_TABLE(EtmPlayerOptions, wxDialog)
	EVT_BUTTON(101, EtmPlayerOptions::OnOk)
	EVT_BUTTON(102, EtmPlayerOptions::OnCancel)
	EVT_CLOSE(      EtmPlayerOptions::OnClose)
	EVT_COMMAND_SCROLL(100, EtmPlayerOptions::OnSpeed)
	EVT_COMMAND_SCROLL(103, EtmPlayerOptions::OnLatency)
	EVT_CHECKBOX(104, EtmPlayerOptions::OnLineSmoothing)
END_EVENT_TABLE()

///////////////////////////////////////////////////////////
EtmPlayerOptions::EtmPlayerOptions(EtmPlayerDialog *parent)
	:wxDialog(parent, -1, wxT("Player Options"), wxDefaultPosition, wxSize(400,600), wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER, wxT(""))
{
	etmPlayerDialog = parent;


	wxStaticText *speedText = new wxStaticText(this, -1, wxT("Speed"), wxPoint(225, 15), wxDefaultSize, 0, wxT(""));
	speedSlider = new wxSlider(this, 100, etmPlayerDialog->glCanvas->speed * 10000, 25, 150, wxPoint(265,10), wxDefaultSize, wxHORIZONTAL, wxDefaultValidator, wxT(""));

	wxStaticText *latencyText = new wxStaticText(this, -1, wxT("Latency"), wxPoint(225, 45), wxDefaultSize, 0, wxT(""));
	latencySlider = new wxSlider(this, 103, etmPlayerDialog->glCanvas->latency, -100, 100, wxPoint(265,40), wxDefaultSize, wxHORIZONTAL, wxDefaultValidator, wxT(""));
	
	lineSmoothingBox = new wxCheckBox(this, 104, wxT("Line Smoothing"), wxPoint(225, 75), wxDefaultSize, 0, wxDefaultValidator, wxT("")); 

	ok = new wxButton(this, 101, wxT("Ok"), wxPoint(200, 550), wxDefaultSize, 0, wxDefaultValidator, wxT(""));
	cancel = new wxButton(this, 102, wxT("Cancel"), wxPoint(300, 550), wxDefaultSize, 0, wxDefaultValidator, wxT(""));

	VarsToTemp(); //backup settings
	VarsToDlg(); //then put them onto the dialog
}

/////////////////////////////////////
EtmPlayerOptions::~EtmPlayerOptions()
{

}

///////////////////////////////////
void EtmPlayerOptions::VarsToTemp()
{
	speed = etmPlayerDialog->glCanvas->speed;
	latency = etmPlayerDialog->glCanvas->latency;
	lineSmoothing = etmPlayerDialog->glCanvas->lineSmoothing;
}

//////////////////////////////////
void EtmPlayerOptions::VarsToDlg()
{
	speedSlider->SetValue(etmPlayerDialog->glCanvas->speed * 10000);
	latencySlider->SetValue(etmPlayerDialog->glCanvas->latency);
	lineSmoothingBox->SetValue(etmPlayerDialog->glCanvas->lineSmoothing);
}

///////////////////////////////////
void EtmPlayerOptions::TempToVars()
{
	etmPlayerDialog->glCanvas->speed = speed;
	etmPlayerDialog->glCanvas->latency = latency;
	etmPlayerDialog->glCanvas->lineSmoothing = lineSmoothing;
}

//////////////////////////////////
void EtmPlayerOptions::TempToDlg()
{
	speedSlider->SetValue(speed * 10000);
	latencySlider->SetValue(latency);
	lineSmoothingBox->SetValue(lineSmoothing);
}

////////////////////////////////
void EtmPlayerOptions::OnOk(wxCommandEvent &event)
{
	VarsToTemp();
	Hide();
}

////////////////////////////////////
void EtmPlayerOptions::OnCancel(wxCommandEvent &event)
{
	Close();
}

void EtmPlayerOptions::OnClose(wxCloseEvent &event)
{
	TempToVars();
	TempToDlg(); 
	Hide();
}

////////////////////////////////////////////////////
void EtmPlayerOptions::OnSpeed(wxScrollEvent &event)
{
	etmPlayerDialog->glCanvas->speed = (float)speedSlider->GetValue() / 10000;
}

//////////////////////////////////////////////////////
void EtmPlayerOptions::OnLatency(wxScrollEvent &event)
{
	etmPlayerDialog->glCanvas->latency = latencySlider->GetValue();
}

void EtmPlayerOptions::OnLineSmoothing(wxCommandEvent &event)
{
	etmPlayerDialog->glCanvas->lineSmoothing = lineSmoothingBox->GetValue();
}
