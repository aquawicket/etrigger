//// Security.h /////////////////////////////////////////////////////////////////////////
//
//
/////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef SECURITY_H
#define SECURITY_H

//Crypto includes
#include "../lib/cryptopp/cryptlib.h"
#include "../lib/cryptopp/aes.h"        // AES
#include "../lib/cryptopp/modes.h"      // CBC_Mode< >
#include "../lib/cryptopp/filters.h"
#include "../lib/cryptopp/base32.h"

#ifdef WIN32 //For hard drive serial number
#include "diskid32.h"  
#endif //WIN32

#ifdef MAC   //For Hard Drive Serial Number
#include <stdio.h> 
#include <CoreFoundation/CoreFoundation.h> 
#include <IOKit/IOKitLib.h> 
#include <IOKit/network/IOEthernetInterface.h> 
#include <IOKit/network/IONetworkInterface.h> 
#include <IOKit/network/IOEthernetController.h>
#endif //MAC

#include <wx/msgdlg.h>
#include <wx/file.h>
#include <wx/datetime.h>

#ifdef WIN32  //For Windows Registry
#include <wx/stdpaths.h>
#include <wx/msw/registry.h>
#endif
#include <wx/buffer.h>

#include "MainPanel.h"
#include "Process.h"

#include "../Images/buy.xpm"
#include "../Images/buy-hover.xpm"
#include "../Images/buy-click.xpm"
#include "../Images/ok.xpm"
#include "../Images/ok-hover.xpm"
#include "../Images/ok-click.xpm"
#include "../Images/cancel.xpm"
#include "../Images/cancel-hover.xpm"
#include "../Images/cancel-click.xpm"

class MainPanel;

class Security
{
public:
	Security(MainPanel *parent);
	~Security(){};
	void DoTimeCheck();
	void GetCurrentDateTime();
	void ImplantFirstAndLastRunTime();
	void ImplantSerialNumber(std::string email, std::string serial);
	bool GetFirstAndLastRunTime();
	void GetSerialNumberFromFile();
	void SetLastRunTime();
	void Encrypt();
	void Decrypt();
	bool IsRegistered();
	bool IsExtended();
	bool IsTrialPeriodUp();
	int GetTrialDaysLeft();

    MainPanel *mainPanel;

	wxString version;
	wxDateTime currentTime;
	wxDateTime firstRunTime;
	wxDateTime lastRunTime;
	wxDateTime prevLastRunTime; //This is to hold the previous LastRunTime since we update lastRunTime on start.
	//char* diskSerial;
	std::string diskSerial;
	std::string diskSerialEncoded;
	std::string email;
	std::string serialNumber;
	std::string serialDecoded;
	int trialDays;
	
#ifdef WIN32
	DiskID disk;
#endif //WIN32
	
};


///////////////////////////////////
class RegisterDlg : public wxDialog
{
public:
	RegisterDlg(MainPanel *parent);
	void OnBuy(GButtonEvent &event);
	void OnOk(GButtonEvent &event);
	void OnCancel(GButtonEvent &event);

	MainPanel *mainPanel;
	GButton *buy;
	GButton *ok;
	GButton *cancel;

	wxTextCtrl *privateKey;
	wxTextCtrl *email;
	wxTextCtrl *serialNumber;

	DECLARE_EVENT_TABLE();
};

#include <string.h>

//#ifdef WIN32
//////////////////
class CryptoClass{

public:
	CryptoClass();
	std::string Encrypt(std::string text);
	std::string Decrypt(std::string text);
	
	byte key[ CryptoPP::AES::DEFAULT_KEYLENGTH ];
    byte  iv[ CryptoPP::AES::BLOCKSIZE ];
};
//#endif //WIN32

#endif //SECURITY_H
