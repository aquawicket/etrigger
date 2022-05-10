//// App.h /////////////////////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef APP_H
#define APP_H

#include "wx/wxprec.h"
#include "KeyGen.h"

#ifdef __BORLANDC__ 
	#pragma hdrstop 
#endif 

#ifndef WX_PRECOMP 
    #include <wx/wx.h>
#endif 

using namespace std;

/////////////////////////////////////////////////////////////////////////////////
class MyApp : public wxApp
{

public:
	MyApp(){};
	~MyApp(){};

    virtual bool OnInit();

private:
    DECLARE_NO_COPY_CLASS(MyApp)
};

DECLARE_APP(MyApp)

#endif //APP_H
