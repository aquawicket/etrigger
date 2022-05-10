//// App.cpp ////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

#include "App.h" 

IMPLEMENT_APP(MyApp); 

//////////////
MyApp::MyApp()
{
}

///////////////
MyApp::~MyApp()
{
}

////////////////////
bool MyApp::OnInit()
{ 
	    if ( !wxApp::OnInit() ) return false;
	
		MyFrame* frame = new MyFrame(0L, wxT("Blank wxWidgets App")); 
		frame->Show();

		SetTopWindow(frame); 
		frame->Centre(wxBOTH);
		frame->Refresh();		      
		return true;
}