//// Details.h /////////////////////////////////////////////////////////////////////////
//
//  Details job is to put together all of the information such as Operating system,
//  devices open, etc. It can then be sent to error reports and detail reports etc.
//
////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef DETAILS_H
#define DETAILS_H

#include "MainPanel.h"
class MainPanel;

//////////////
class Details
{
public:
	Details(MainPanel *parent);
	wxString GetDetails();

	MainPanel *mainPanel;
};

#endif  //DETAILS_H

