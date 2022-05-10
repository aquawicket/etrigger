//// VelocityDialog.cpp /////////////////////////////////////////////////////////////////
//
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "VelocityDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

///////////////////////////////////////
BEGIN_EVENT_TABLE(VelocityDialog, wxDialog)
	EVT_GBUTTON(100, VelocityDialog::OnOk)
	EVT_GBUTTON(101, VelocityDialog::OnCancel)
	EVT_CLOSE(       VelocityDialog::OnClose) 
	EVT_GSLIDER(200, VelocityDialog::OnSlider1)
	EVT_GSLIDER(201, VelocityDialog::OnSlider2)
	EVT_GSLIDER(202, VelocityDialog::OnSlider3)
	EVT_GSLIDER(203, VelocityDialog::OnSlider4)
	EVT_GSLIDER(204, VelocityDialog::OnSlider5)
	EVT_GSLIDER(205, VelocityDialog::OnSlider6)
	EVT_GSLIDER(206, VelocityDialog::OnSlider7)
	EVT_GSLIDER(207, VelocityDialog::OnSlider8)
	EVT_GSLIDER(208, VelocityDialog::OnSlider9)
	EVT_GSLIDER(209, VelocityDialog::OnSlider10)
	EVT_GSLIDER(210, VelocityDialog::OnSlider11)
	EVT_GSLIDER(211, VelocityDialog::OnSlider12)
	EVT_GSLIDER(212, VelocityDialog::OnSlider13)
	EVT_GSLIDER(213, VelocityDialog::OnSlider14)
	EVT_GSLIDER(214, VelocityDialog::OnSlider15)
	EVT_GSLIDER(215, VelocityDialog::OnSlider16)
	EVT_GSLIDER(216, VelocityDialog::OnSlider17)
	EVT_GSLIDER(217, VelocityDialog::OnSlider18)
	EVT_GSLIDER(218, VelocityDialog::OnSlider19)
	EVT_GSLIDER(219, VelocityDialog::OnSlider20)
	EVT_GSLIDER(220, VelocityDialog::OnSlider21)
	EVT_GSLIDER(221, VelocityDialog::OnSlider22)
	EVT_GSLIDER(222, VelocityDialog::OnSlider23)
	EVT_GSLIDER(223, VelocityDialog::OnSlider24)
	EVT_GSLIDER(224, VelocityDialog::OnSlider25)
	EVT_GSLIDER(225, VelocityDialog::OnSlider26)
	EVT_GSLIDER(226, VelocityDialog::OnSlider27)
	EVT_GSLIDER(227, VelocityDialog::OnSlider28)
	EVT_GSLIDER(228, VelocityDialog::OnSlider29)
	EVT_GSLIDER(229, VelocityDialog::OnSlider30)
	EVT_GSLIDER(230, VelocityDialog::OnSlider31)
	EVT_GSLIDER(231, VelocityDialog::OnSlider32)
	EVT_GSLIDER(232, VelocityDialog::OnSlider33)
	EVT_GSLIDER(233, VelocityDialog::OnSlider34)
	EVT_GSLIDER(234, VelocityDialog::OnSlider35)
	EVT_GSLIDER(235, VelocityDialog::OnSlider36)
	EVT_GSLIDER(236, VelocityDialog::OnSlider37)
	EVT_GSLIDER(237, VelocityDialog::OnSlider38)
	EVT_GSLIDER(238, VelocityDialog::OnSlider39)
	EVT_GSLIDER(239, VelocityDialog::OnSlider40)
	EVT_GSLIDER(240, VelocityDialog::OnSlider41)
	EVT_GSLIDER(241, VelocityDialog::OnSlider42)
	EVT_GSLIDER(242, VelocityDialog::OnSlider43)
	EVT_GSLIDER(243, VelocityDialog::OnSlider44)
	EVT_GSLIDER(244, VelocityDialog::OnSlider45)
	EVT_GSLIDER(245, VelocityDialog::OnSlider46)
	EVT_GSLIDER(246, VelocityDialog::OnSlider47)
	EVT_GSLIDER(247, VelocityDialog::OnSlider48)
	EVT_GSLIDER(248, VelocityDialog::OnSlider49)
	EVT_GSLIDER(249, VelocityDialog::OnSlider50)
	EVT_GSLIDER(250, VelocityDialog::OnSlider51)
	EVT_GSLIDER(251, VelocityDialog::OnSlider52)
	EVT_GSLIDER(252, VelocityDialog::OnSlider53)
	EVT_GSLIDER(253, VelocityDialog::OnSlider54)
	EVT_GSLIDER(254, VelocityDialog::OnSlider55)
	EVT_GSLIDER(255, VelocityDialog::OnSlider56)
	EVT_GSLIDER(256, VelocityDialog::OnSlider57)
	EVT_GSLIDER(257, VelocityDialog::OnSlider58)
	EVT_GSLIDER(258, VelocityDialog::OnSlider59)
	EVT_GSLIDER(259, VelocityDialog::OnSlider60)
	EVT_GSLIDER(260, VelocityDialog::OnSlider61)
	EVT_GSLIDER(261, VelocityDialog::OnSlider62)
	EVT_GSLIDER(262, VelocityDialog::OnSlider63)
	EVT_GSLIDER(263, VelocityDialog::OnSlider64)
	EVT_GSLIDER(264, VelocityDialog::OnSlider65)
	EVT_GSLIDER(265, VelocityDialog::OnSlider66)
	EVT_GSLIDER(266, VelocityDialog::OnSlider67)
	EVT_GSLIDER(267, VelocityDialog::OnSlider68)
	EVT_GSLIDER(268, VelocityDialog::OnSlider69)
	EVT_GSLIDER(269, VelocityDialog::OnSlider70)
	EVT_GSLIDER(270, VelocityDialog::OnSlider71)
	EVT_GSLIDER(271, VelocityDialog::OnSlider72)
	EVT_GSLIDER(272, VelocityDialog::OnSlider73)
	EVT_GSLIDER(273, VelocityDialog::OnSlider74)
	EVT_GSLIDER(274, VelocityDialog::OnSlider75)
	EVT_GSLIDER(275, VelocityDialog::OnSlider76)
	EVT_GSLIDER(276, VelocityDialog::OnSlider77)
	EVT_GSLIDER(277, VelocityDialog::OnSlider78)
	EVT_GSLIDER(278, VelocityDialog::OnSlider79)
	EVT_GSLIDER(279, VelocityDialog::OnSlider80)
	EVT_GSLIDER(280, VelocityDialog::OnSlider81)
	EVT_GSLIDER(281, VelocityDialog::OnSlider82)
	EVT_GSLIDER(282, VelocityDialog::OnSlider83)
	EVT_GSLIDER(283, VelocityDialog::OnSlider84)
	EVT_GSLIDER(284, VelocityDialog::OnSlider85)
	EVT_GSLIDER(285, VelocityDialog::OnSlider86)
	EVT_GSLIDER(286, VelocityDialog::OnSlider87)
	EVT_GSLIDER(287, VelocityDialog::OnSlider88)
	EVT_GSLIDER(288, VelocityDialog::OnSlider89)
	EVT_GSLIDER(289, VelocityDialog::OnSlider90)
	EVT_GSLIDER(290, VelocityDialog::OnSlider91)
	EVT_GSLIDER(291, VelocityDialog::OnSlider92)
	EVT_GSLIDER(292, VelocityDialog::OnSlider93)
	EVT_GSLIDER(293, VelocityDialog::OnSlider94)
	EVT_GSLIDER(294, VelocityDialog::OnSlider95)
	EVT_GSLIDER(295, VelocityDialog::OnSlider96)
	EVT_GSLIDER(296, VelocityDialog::OnSlider97)
	EVT_GSLIDER(297, VelocityDialog::OnSlider98)
	EVT_GSLIDER(298, VelocityDialog::OnSlider99)
	EVT_GSLIDER(299, VelocityDialog::OnSlider100)
	EVT_GSLIDER(300, VelocityDialog::OnSlider101)
	EVT_GSLIDER(301, VelocityDialog::OnSlider102)
	EVT_GSLIDER(302, VelocityDialog::OnSlider103)
	EVT_GSLIDER(303, VelocityDialog::OnSlider104)
	EVT_GSLIDER(304, VelocityDialog::OnSlider105)
	EVT_GSLIDER(305, VelocityDialog::OnSlider106)
	EVT_GSLIDER(306, VelocityDialog::OnSlider107)
	EVT_GSLIDER(307, VelocityDialog::OnSlider108)
	EVT_GSLIDER(308, VelocityDialog::OnSlider109)
	EVT_GSLIDER(309, VelocityDialog::OnSlider110)
	EVT_GSLIDER(310, VelocityDialog::OnSlider111)
	EVT_GSLIDER(311, VelocityDialog::OnSlider112)
	EVT_GSLIDER(312, VelocityDialog::OnSlider113)
	EVT_GSLIDER(313, VelocityDialog::OnSlider114)
	EVT_GSLIDER(314, VelocityDialog::OnSlider115)
	EVT_GSLIDER(315, VelocityDialog::OnSlider116)
	EVT_GSLIDER(316, VelocityDialog::OnSlider117)
	EVT_GSLIDER(317, VelocityDialog::OnSlider118)
	EVT_GSLIDER(318, VelocityDialog::OnSlider119)
	EVT_GSLIDER(319, VelocityDialog::OnSlider120)
	EVT_GSLIDER(320, VelocityDialog::OnSlider121)
	EVT_GSLIDER(321, VelocityDialog::OnSlider122)
	EVT_GSLIDER(322, VelocityDialog::OnSlider123)
	EVT_GSLIDER(323, VelocityDialog::OnSlider124)
	EVT_GSLIDER(324, VelocityDialog::OnSlider125)
	EVT_GSLIDER(325, VelocityDialog::OnSlider126)
	EVT_GSLIDER(326, VelocityDialog::OnSlider127)
END_EVENT_TABLE() 

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VelocityDialog::VelocityDialog(TriggerDialog *parent)
			   :wxDialog(parent, -1, wxT("Full Velocity Control"), wxDefaultPosition, wxSize(800, 340), wxDEFAULT_DIALOG_STYLE)
{
	triggerDialog = parent;
	CentreOnScreen(wxBOTH);
	
#ifdef WIN32 ///////////////////////////////
	SetBackgroundColour(wxColour(90,90,90));
#endif //WIN32 /////////////////////////////
#ifdef MAC ////////////////////////////////////////////////////////////////////////////////
	wxPanel *background = new wxPanel(this, -1, wxPoint(0,0), this->GetSize(), 0, wxT(""));
	background->SetBackgroundColour(wxColour(90,90,90));
#endif //MAC //////////////////////////////////////////////////////////////////////////////

	for(int i=0; i<127; ++i){
		slider[i] = new GSlider(this, 200+i, wxPoint(i*6 + 13, 10), wxNO_BORDER , wxT(""), velSlider_xpm, velSlider_xpm, velKnob_xpm,
		                        velKnob_xpm, velKnob_xpm, velKnob_xpm);
		slider[i]->SetRange(1, 127); 
		slider[i]->SetValue(0, i+1);
		slider[i]->SetDefault(0, i+1);
	}

	ok = new GButton(this, 100, wxPoint(564,280), ok_xpm, ok_hover_xpm, ok_click_xpm); 
	cancel = new GButton(this, 101, wxPoint(635,280), cancel_xpm, cancel_hover_xpm, cancel_click_xpm);

	VarsToTemp(); //backup settings
	VarsToDlg(); //then put them onto the dialog
}

//////////////////////////////////////////////
void VelocityDialog::OnOk(GButtonEvent &event)
{
	Destroy();
}

//////////////////////////////////////////////////
void VelocityDialog::OnCancel(GButtonEvent &event)
{
	Close();
}

/////////////////////////////////////////////////
void VelocityDialog::OnClose(wxCloseEvent &event)
{
	TempToVars();
	Destroy();
}

/////////////////////////////////
void VelocityDialog::VarsToTemp()
{
	for(int i=0; i<127; ++i){
		dynamics[i] = triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][i];
	}
}

////////////////////////////////
void VelocityDialog::VarsToDlg()
{
	for(int i=0; i<127; ++i){
		slider[i]->SetValue(0, triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][i]);
	}
}

/////////////////////////////////
void VelocityDialog::TempToVars()
{
	for(int i=0; i<127; ++i){
		triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][i] = dynamics[i];
	}
}

////////////////////////////////
void VelocityDialog::TempToDlg()
{
	for(int i=0; i<127; ++i){
		slider[i]->SetValue(0, dynamics[i]);
	}
}


void VelocityDialog::OnSlider1(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][0] = event.GetValue();}
void VelocityDialog::OnSlider2(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][1] = event.GetValue();}
void VelocityDialog::OnSlider3(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][2] = event.GetValue();}
void VelocityDialog::OnSlider4(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][3] = event.GetValue();}
void VelocityDialog::OnSlider5(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][4] = event.GetValue();}
void VelocityDialog::OnSlider6(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][5] = event.GetValue();}
void VelocityDialog::OnSlider7(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][6] = event.GetValue();}
void VelocityDialog::OnSlider8(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][7] = event.GetValue();}
void VelocityDialog::OnSlider9(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][8] = event.GetValue();}
void VelocityDialog::OnSlider10(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][9] = event.GetValue();}
void VelocityDialog::OnSlider11(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][10] = event.GetValue();}
void VelocityDialog::OnSlider12(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][11] = event.GetValue();}
void VelocityDialog::OnSlider13(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][12] = event.GetValue();}
void VelocityDialog::OnSlider14(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][13] = event.GetValue();}
void VelocityDialog::OnSlider15(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][14] = event.GetValue();}
void VelocityDialog::OnSlider16(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][15] = event.GetValue();}
void VelocityDialog::OnSlider17(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][16] = event.GetValue();}
void VelocityDialog::OnSlider18(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][17] = event.GetValue();}
void VelocityDialog::OnSlider19(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][18] = event.GetValue();}
void VelocityDialog::OnSlider20(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][19] = event.GetValue();}
void VelocityDialog::OnSlider21(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][20] = event.GetValue();}
void VelocityDialog::OnSlider22(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][21] = event.GetValue();}
void VelocityDialog::OnSlider23(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][22] = event.GetValue();}
void VelocityDialog::OnSlider24(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][23] = event.GetValue();}
void VelocityDialog::OnSlider25(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][24] = event.GetValue();}
void VelocityDialog::OnSlider26(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][25] = event.GetValue();}
void VelocityDialog::OnSlider27(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][26] = event.GetValue();}
void VelocityDialog::OnSlider28(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][27] = event.GetValue();}
void VelocityDialog::OnSlider29(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][28] = event.GetValue();}
void VelocityDialog::OnSlider30(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][29] = event.GetValue();}
void VelocityDialog::OnSlider31(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][30] = event.GetValue();}
void VelocityDialog::OnSlider32(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][31] = event.GetValue();}
void VelocityDialog::OnSlider33(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][32] = event.GetValue();}
void VelocityDialog::OnSlider34(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][33] = event.GetValue();}
void VelocityDialog::OnSlider35(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][34] = event.GetValue();}
void VelocityDialog::OnSlider36(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][35] = event.GetValue();}
void VelocityDialog::OnSlider37(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][36] = event.GetValue();}
void VelocityDialog::OnSlider38(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][37] = event.GetValue();}
void VelocityDialog::OnSlider39(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][38] = event.GetValue();}
void VelocityDialog::OnSlider40(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][39] = event.GetValue();}
void VelocityDialog::OnSlider41(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][40] = event.GetValue();}
void VelocityDialog::OnSlider42(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][41] = event.GetValue();}
void VelocityDialog::OnSlider43(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][42] = event.GetValue();}
void VelocityDialog::OnSlider44(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][43] = event.GetValue();}
void VelocityDialog::OnSlider45(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][44] = event.GetValue();}
void VelocityDialog::OnSlider46(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][45] = event.GetValue();}
void VelocityDialog::OnSlider47(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][46] = event.GetValue();}
void VelocityDialog::OnSlider48(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][47] = event.GetValue();}
void VelocityDialog::OnSlider49(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][48] = event.GetValue();}
void VelocityDialog::OnSlider50(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][49] = event.GetValue();}
void VelocityDialog::OnSlider51(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][50] = event.GetValue();}
void VelocityDialog::OnSlider52(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][51] = event.GetValue();}
void VelocityDialog::OnSlider53(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][52] = event.GetValue();}
void VelocityDialog::OnSlider54(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][53] = event.GetValue();}
void VelocityDialog::OnSlider55(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][54] = event.GetValue();}
void VelocityDialog::OnSlider56(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][55] = event.GetValue();}
void VelocityDialog::OnSlider57(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][56] = event.GetValue();}
void VelocityDialog::OnSlider58(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][57] = event.GetValue();}
void VelocityDialog::OnSlider59(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][58] = event.GetValue();}
void VelocityDialog::OnSlider60(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][59] = event.GetValue();}
void VelocityDialog::OnSlider61(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][60] = event.GetValue();}
void VelocityDialog::OnSlider62(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][61] = event.GetValue();}
void VelocityDialog::OnSlider63(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][62] = event.GetValue();}
void VelocityDialog::OnSlider64(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][63] = event.GetValue();}
void VelocityDialog::OnSlider65(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][64] = event.GetValue();}
void VelocityDialog::OnSlider66(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][65] = event.GetValue();}
void VelocityDialog::OnSlider67(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][66] = event.GetValue();}
void VelocityDialog::OnSlider68(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][67] = event.GetValue();}
void VelocityDialog::OnSlider69(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][68] = event.GetValue();}
void VelocityDialog::OnSlider70(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][69] = event.GetValue();}
void VelocityDialog::OnSlider71(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][70] = event.GetValue();}
void VelocityDialog::OnSlider72(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][71] = event.GetValue();}
void VelocityDialog::OnSlider73(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][72] = event.GetValue();}
void VelocityDialog::OnSlider74(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][73] = event.GetValue();}
void VelocityDialog::OnSlider75(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][74] = event.GetValue();}
void VelocityDialog::OnSlider76(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][75] = event.GetValue();}
void VelocityDialog::OnSlider77(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][76] = event.GetValue();}
void VelocityDialog::OnSlider78(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][77] = event.GetValue();}
void VelocityDialog::OnSlider79(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][78] = event.GetValue();}
void VelocityDialog::OnSlider80(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][79] = event.GetValue();}
void VelocityDialog::OnSlider81(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][80] = event.GetValue();}
void VelocityDialog::OnSlider82(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][81] = event.GetValue();}
void VelocityDialog::OnSlider83(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][82] = event.GetValue();}
void VelocityDialog::OnSlider84(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][83] = event.GetValue();}
void VelocityDialog::OnSlider85(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][84] = event.GetValue();}
void VelocityDialog::OnSlider86(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][85] = event.GetValue();}
void VelocityDialog::OnSlider87(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][86] = event.GetValue();}
void VelocityDialog::OnSlider88(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][87] = event.GetValue();}
void VelocityDialog::OnSlider89(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][88] = event.GetValue();}
void VelocityDialog::OnSlider90(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][89] = event.GetValue();}
void VelocityDialog::OnSlider91(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][90] = event.GetValue();}
void VelocityDialog::OnSlider92(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][91] = event.GetValue();}
void VelocityDialog::OnSlider93(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][92] = event.GetValue();}
void VelocityDialog::OnSlider94(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][93] = event.GetValue();}
void VelocityDialog::OnSlider95(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][94] = event.GetValue();}
void VelocityDialog::OnSlider96(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][95] = event.GetValue();}
void VelocityDialog::OnSlider97(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][96] = event.GetValue();}
void VelocityDialog::OnSlider98(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][97] = event.GetValue();}
void VelocityDialog::OnSlider99(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][98] = event.GetValue();}
void VelocityDialog::OnSlider100(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][99] = event.GetValue();}
void VelocityDialog::OnSlider101(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][100] = event.GetValue();}
void VelocityDialog::OnSlider102(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][101] = event.GetValue();}
void VelocityDialog::OnSlider103(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][102] = event.GetValue();}
void VelocityDialog::OnSlider104(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][103] = event.GetValue();}
void VelocityDialog::OnSlider105(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][104] = event.GetValue();}
void VelocityDialog::OnSlider106(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][105] = event.GetValue();}
void VelocityDialog::OnSlider107(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][106] = event.GetValue();}
void VelocityDialog::OnSlider108(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][107] = event.GetValue();}
void VelocityDialog::OnSlider109(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][108] = event.GetValue();}
void VelocityDialog::OnSlider110(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][109] = event.GetValue();}
void VelocityDialog::OnSlider111(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][110] = event.GetValue();}
void VelocityDialog::OnSlider112(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][111] = event.GetValue();}
void VelocityDialog::OnSlider113(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][112] = event.GetValue();}
void VelocityDialog::OnSlider114(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][113] = event.GetValue();}
void VelocityDialog::OnSlider115(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][114] = event.GetValue();}
void VelocityDialog::OnSlider116(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][115] = event.GetValue();}
void VelocityDialog::OnSlider117(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][116] = event.GetValue();}
void VelocityDialog::OnSlider118(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][117] = event.GetValue();}
void VelocityDialog::OnSlider119(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][118] = event.GetValue();}
void VelocityDialog::OnSlider120(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][119] = event.GetValue();}
void VelocityDialog::OnSlider121(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][120] = event.GetValue();}
void VelocityDialog::OnSlider122(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][121] = event.GetValue();}
void VelocityDialog::OnSlider123(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][122] = event.GetValue();}
void VelocityDialog::OnSlider124(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][123] = event.GetValue();}
void VelocityDialog::OnSlider125(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][124] = event.GetValue();}
void VelocityDialog::OnSlider126(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][125] = event.GetValue();}
void VelocityDialog::OnSlider127(GSliderEvent &event)
{triggerDialog->trigger->trackProc->n[triggerDialog->trigger->trackNum].dynamics[triggerDialog->currentZone][126] = event.GetValue();}
