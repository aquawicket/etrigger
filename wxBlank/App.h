//// App.h /////////////////////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////////////////
#ifndef APP_H
#define APP_H

#include <wx/wxprec.h> 
#include "main.h"

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

//////////////////////////
class MyApp : public wxApp
{

public:
    MyApp();
	~MyApp();

    // create our main window here
    virtual bool OnInit();

private:
    DECLARE_NO_COPY_CLASS(MyApp)

};

DECLARE_APP(MyApp)

#endif //APP_H