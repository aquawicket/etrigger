/// KeyGen.h ///////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef KEYGEN_H
#define KEYGEN_H

#include <wx/frame.h>
#include <wx/textctrl.h>
#include <wx/button.h>

#include "../lib-src/Gwidgets/GButton/GButton.h"
#include "../lib-src/Gwidgets/GHelper/GHelper.h"

#include "../Images/ok.xpm"
#include "../Images/ok-hover.xpm"
#include "../Images/ok-click.xpm"
#include "../Images/cancel.xpm"
#include "../Images/cancel-hover.xpm"
#include "../Images/cancel-click.xpm"

//Crypto includes
#include "../lib-src/cryptopp/cryptlib.h"
#include "../lib-src/cryptopp/aes.h"        // AES
#include "../lib-src/cryptopp/des.h"
#include "../lib-src/cryptopp/modes.h"      // CBC_Mode< >
#include "../lib-src/cryptopp/filters.h"
#include "../lib-src/cryptopp/base32.h"

///////////////////////////////
class MyFrame : public wxFrame
{
public:
	MyFrame();
	~MyFrame();

	void OnExtend(wxCommandEvent &event);
	void OnOk(GButtonEvent &event);
	void OnCancel(GButtonEvent &event);

	wxTextCtrl *privateKey;
	wxTextCtrl *serialNumber;
	GButton *ok;
	GButton *cancel;
	wxButton *extend;

	std::string diskSerialEncoded;
	std::string diskSerialDecoded; //AKA "serial Number"

	DECLARE_EVENT_TABLE();

};

//////////////////
class CryptoClass{

public:
	CryptoClass();
	std::string Encrypt(std::string text);
	//std::string Decrypt(std::string text);
	
	byte key[ CryptoPP::AES::DEFAULT_KEYLENGTH ];
    byte  iv[ CryptoPP::AES::BLOCKSIZE ];

};

#endif //KEYGEN_H