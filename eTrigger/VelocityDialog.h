//// VelocityDialog.h /////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef VELOCITYDIALOG_H
#define VELOCITYDIALOG_H

#include <wx/dialog.h>

#include "../lib/Gwidgets/GButton/GButton.h"
#include "../lib/Gwidgets/GSlider/GSlider.h"

#include "TriggerDialog.h"

#include "../Images/velSlider.xpm"
#include "../Images/velKnob.xpm"
#include "../Images/ok.xpm"
#include "../Images/ok-hover.xpm"
#include "../Images/ok-click.xpm"
#include "../Images/cancel.xpm"
#include "../Images/cancel-hover.xpm"
#include "../Images/cancel-click.xpm"

class TriggerDialog;

class VelocityDialog : public wxDialog
{
public:
	VelocityDialog(TriggerDialog* parent);

	void OnOk(GButtonEvent &event);
	void OnCancel(GButtonEvent &event);
	void OnClose(wxCloseEvent &event);
	void VarsToTemp();
	void VarsToDlg();
	void TempToVars();
	void TempToDlg();

	void OnSlider1(GSliderEvent &event);
	void OnSlider2(GSliderEvent &event);
	void OnSlider3(GSliderEvent &event);
	void OnSlider4(GSliderEvent &event);
	void OnSlider5(GSliderEvent &event);
	void OnSlider6(GSliderEvent &event);
	void OnSlider7(GSliderEvent &event);
	void OnSlider8(GSliderEvent &event);
	void OnSlider9(GSliderEvent &event);
	void OnSlider10(GSliderEvent &event);
	void OnSlider11(GSliderEvent &event);
	void OnSlider12(GSliderEvent &event);
	void OnSlider13(GSliderEvent &event);
	void OnSlider14(GSliderEvent &event);
	void OnSlider15(GSliderEvent &event);
	void OnSlider16(GSliderEvent &event);
	void OnSlider17(GSliderEvent &event);
	void OnSlider18(GSliderEvent &event);
	void OnSlider19(GSliderEvent &event);
	void OnSlider20(GSliderEvent &event);
    void OnSlider21(GSliderEvent &event);
    void OnSlider22(GSliderEvent &event);
    void OnSlider23(GSliderEvent &event);
    void OnSlider24(GSliderEvent &event);
    void OnSlider25(GSliderEvent &event);
    void OnSlider26(GSliderEvent &event);
    void OnSlider27(GSliderEvent &event);
    void OnSlider28(GSliderEvent &event);
    void OnSlider29(GSliderEvent &event);
    void OnSlider30(GSliderEvent &event);
    void OnSlider31(GSliderEvent &event);
    void OnSlider32(GSliderEvent &event);
    void OnSlider33(GSliderEvent &event);
    void OnSlider34(GSliderEvent &event);
    void OnSlider35(GSliderEvent &event);
    void OnSlider36(GSliderEvent &event);
    void OnSlider37(GSliderEvent &event);
    void OnSlider38(GSliderEvent &event);
    void OnSlider39(GSliderEvent &event);
    void OnSlider40(GSliderEvent &event);
    void OnSlider41(GSliderEvent &event);
    void OnSlider42(GSliderEvent &event);
    void OnSlider43(GSliderEvent &event);
    void OnSlider44(GSliderEvent &event);
    void OnSlider45(GSliderEvent &event);
    void OnSlider46(GSliderEvent &event);
    void OnSlider47(GSliderEvent &event);
    void OnSlider48(GSliderEvent &event);
    void OnSlider49(GSliderEvent &event);
    void OnSlider50(GSliderEvent &event);
    void OnSlider51(GSliderEvent &event);
    void OnSlider52(GSliderEvent &event);
    void OnSlider53(GSliderEvent &event);
    void OnSlider54(GSliderEvent &event);
    void OnSlider55(GSliderEvent &event);
    void OnSlider56(GSliderEvent &event);
    void OnSlider57(GSliderEvent &event);
    void OnSlider58(GSliderEvent &event);
    void OnSlider59(GSliderEvent &event);
    void OnSlider60(GSliderEvent &event);
    void OnSlider61(GSliderEvent &event);
    void OnSlider62(GSliderEvent &event);
    void OnSlider63(GSliderEvent &event);
    void OnSlider64(GSliderEvent &event);
    void OnSlider65(GSliderEvent &event);
    void OnSlider66(GSliderEvent &event);
    void OnSlider67(GSliderEvent &event);
    void OnSlider68(GSliderEvent &event);
    void OnSlider69(GSliderEvent &event);
    void OnSlider70(GSliderEvent &event);
    void OnSlider71(GSliderEvent &event);
    void OnSlider72(GSliderEvent &event);
    void OnSlider73(GSliderEvent &event);
    void OnSlider74(GSliderEvent &event);
    void OnSlider75(GSliderEvent &event);
    void OnSlider76(GSliderEvent &event);
    void OnSlider77(GSliderEvent &event);
    void OnSlider78(GSliderEvent &event);
    void OnSlider79(GSliderEvent &event);
    void OnSlider80(GSliderEvent &event);
    void OnSlider81(GSliderEvent &event);
    void OnSlider82(GSliderEvent &event);
    void OnSlider83(GSliderEvent &event);
    void OnSlider84(GSliderEvent &event);
    void OnSlider85(GSliderEvent &event);
    void OnSlider86(GSliderEvent &event);
    void OnSlider87(GSliderEvent &event);
    void OnSlider88(GSliderEvent &event);
    void OnSlider89(GSliderEvent &event);
    void OnSlider90(GSliderEvent &event);
    void OnSlider91(GSliderEvent &event);
    void OnSlider92(GSliderEvent &event);
    void OnSlider93(GSliderEvent &event);
    void OnSlider94(GSliderEvent &event);
    void OnSlider95(GSliderEvent &event);
    void OnSlider96(GSliderEvent &event);
    void OnSlider97(GSliderEvent &event);
    void OnSlider98(GSliderEvent &event);
    void OnSlider99(GSliderEvent &event);
    void OnSlider100(GSliderEvent &event);
    void OnSlider101(GSliderEvent &event);
    void OnSlider102(GSliderEvent &event);
    void OnSlider103(GSliderEvent &event);
    void OnSlider104(GSliderEvent &event);
    void OnSlider105(GSliderEvent &event);
    void OnSlider106(GSliderEvent &event);
    void OnSlider107(GSliderEvent &event);
    void OnSlider108(GSliderEvent &event);
    void OnSlider109(GSliderEvent &event);
    void OnSlider110(GSliderEvent &event);
    void OnSlider111(GSliderEvent &event);
    void OnSlider112(GSliderEvent &event);
    void OnSlider113(GSliderEvent &event);
    void OnSlider114(GSliderEvent &event);
    void OnSlider115(GSliderEvent &event);
    void OnSlider116(GSliderEvent &event);
    void OnSlider117(GSliderEvent &event);
    void OnSlider118(GSliderEvent &event);
    void OnSlider119(GSliderEvent &event);
    void OnSlider120(GSliderEvent &event);
    void OnSlider121(GSliderEvent &event);
    void OnSlider122(GSliderEvent &event);
    void OnSlider123(GSliderEvent &event);
    void OnSlider124(GSliderEvent &event);
    void OnSlider125(GSliderEvent &event);
    void OnSlider126(GSliderEvent &event);
    void OnSlider127(GSliderEvent &event);

	TriggerDialog *triggerDialog;

	int dynamics[127];

	GButton *ok;
	GButton *cancel;

	GSlider *slider[127];

private:
	DECLARE_EVENT_TABLE() 

};


#endif //VELOCITYDIALOG_H

