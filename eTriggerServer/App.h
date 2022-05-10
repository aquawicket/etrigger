/// App.h ///////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef APP_H
#define APP_H

#include "wx/wxprec.h"
#include "server.h"

#ifdef __BORLANDC__
#  pragma hdrstop
#endif

// for all others, include the necessary headers
#ifndef WX_PRECOMP
#  include "wx/wx.h"
#endif



///////////////////////////
class MyApp : public wxApp
{
public:
  virtual bool OnInit();

};



#endif //APP_H
