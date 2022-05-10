//// MainPanel.cpp ///////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////

#include "MainPanel.h" 

BEGIN_EVENT_TABLE(MainPanel, GObjectPanel)
	EVT_MENU(90, MainPanel::OnNewGImage)
	EVT_MOUSE_EVENTS (MainPanel::OnMouse)
	EVT_GBUTTON (104, MainPanel::OnGButton1)
	EVT_GTOGGLE (105, MainPanel::OnGToggle1)
	EVT_GIMAGESELECTOR (106, MainPanel::OnGImageSelector1)
	EVT_GSLIDER (107, MainPanel::OnGSlider1)
END_EVENT_TABLE()

//////////////////////////////////////
MainPanel::MainPanel(wxWindow* parent)
		  :GObjectPanel(parent)
{ 
	object.push_back(new GAnimate(this, 99, wxPoint(50,5), wxT("test#.png"), 38));
	object.push_back(new GAnimate(this, 100, wxPoint(0,300), wxT("fireBG#.png"), 90));
	object.push_back(new GAnimate(this, 101, wxPoint(500,500), wxT("hulk#.png"), 100));
	object.push_back(new GAnimate(this, 102, wxPoint(100,500), wxT("ken#.png"), 50));
	//object.push_back(new GImage(this, 103, wxPoint(0,0), wxT("gImage1.png")));
	//object.push_back(new GButton(this, 104, wxPoint(10,10), wxT("button2.png"), wxT("button1.png"), wxT("button3.png")));
	//object.push_back(new GToggle(this, 105, wxPoint(10,400), wxT("off.png"), wxT("on.png")));
	//object[5]->SetValue(true);
	//object.push_back(new GImageSelector(this, 106, wxPoint(250, 400), wxT("basketball.png")));
	object.push_back(new GSlider(this, 107, wxPoint(0,0), wxT("sliderBG.png"), wxT("sliderKnob.png")));
	

	mouseXY = new wxStaticText(this, -1, wxT("MouseXY:"), wxPoint(5,700), wxDefaultSize, 0, wxT(""));
	theEvent = new wxStaticText(this, -1, wxT("Event:"), wxPoint(5,720), wxDefaultSize, 0, wxT(""));

	//menu = new wxMenu(0);
	//menu->Append( 90, wxT("New GImage") );

}

MainPanel::~MainPanel()
{ 
	delete mouseXY;
	delete theEvent;
	//delete menu;
}


void MainPanel::OnMouse(wxMouseEvent &event)
{
	/*
	wxPoint xy = event.GetPosition();
	wxString text = wxString::Format("MouseXY: %d %d", xy.x, xy.y );
	mouseXY->SetLabel(text);

	if(event.RightUp()){
		PopupMenu(menu, xy);
	}
	*/
	event.Skip(true);
}

void MainPanel::OnGButton1(GButtonEvent &event)
{
	theEvent->SetLabel("Event: Button 1 clicked");
}

void MainPanel::OnGToggle1(GToggleEvent &event)
{
	if(object[5]->GetValue() == true){
		theEvent->SetLabel("Event: Toggle 1 clicked ON");
		timer->Start((int)object[0]->GetValue(0),false);
	}
	else{
		theEvent->SetLabel("Event: Toggle 1 clicked OFF");
		timer->Stop();
	}
}

void MainPanel::OnGImageSelector1(GImageSelectorEvent &event)
{
	theEvent->SetLabel("Event: GImageSelector1 image changed");
}

void MainPanel::OnGSlider1(GSliderEvent &event)
{
	//theEvent->SetLabel(wxString::Format(wxT("Event: GSlider1 moved to %d"), (int)object[7]->GetValue(0)));
	timer->Start((int)object[4]->GetValue(0),false);
}

void MainPanel::OnNewGImage(wxCommandEvent &event)
{
	object.push_back(new GImage(this, object.size(), wxPoint(525,400), wxT("gImage1.png")));
}