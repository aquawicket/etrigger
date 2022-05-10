/// KeyGen.cpp /////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "KeyGen.h"


////////////////////////////////////////
BEGIN_EVENT_TABLE(MyFrame, wxFrame)
	EVT_GBUTTON(100, MyFrame::OnOk)
	EVT_GBUTTON(101, MyFrame::OnCancel)
	EVT_BUTTON(102, MyFrame::OnExtend)
END_EVENT_TABLE() 


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MyFrame::MyFrame() : wxFrame((wxFrame *)NULL, wxID_ANY, wxT("eTrigger KeyGenerator"), wxDefaultPosition, wxSize(400, 300))
{
	CentreOnScreen(wxBOTH);

	ok = new GButton(this, 100, wxPoint(233, 240), ok_xpm, ok_hover_xpm, ok_click_xpm); 
	cancel = new GButton(this, 101, wxPoint(305, 240), cancel_xpm, cancel_hover_xpm, cancel_click_xpm);
	extend = new wxButton(this, 102, wxT("Extend"), wxPoint(10, 240), wxDefaultSize, 0, wxDefaultValidator, wxT(""));

	privateKey = new wxTextCtrl(this, -1, wxT(""), wxPoint(10, 20), wxSize(370, 20), 0, wxDefaultValidator, wxT(""));
	serialNumber = new wxTextCtrl(this, -1, wxT(""), wxPoint(10, 80), wxSize(370, 80), 0, wxDefaultValidator, wxT(""));
}


////////////////////
MyFrame::~MyFrame()
{
	
}

/////////////////////////////////////////////
void MyFrame::OnExtend(wxCommandEvent &event)
{
	//Generate Key Here
	CryptoClass crypt;
	//diskSerialEncoded = privateKey->GetValue();
	diskSerialEncoded = ConvToStdString(privateKey->GetValue());
	diskSerialEncoded.append("15DayExtention");

	//serialNumber->SetValue(crypt.Encrypt(diskSerialEncoded));
	wxString extention = ConvTowxString(crypt.Encrypt(diskSerialEncoded));
	serialNumber->SetValue( extention );
}

///////////////////////////////////////
void MyFrame::OnOk(GButtonEvent &event)
{
	//Generate Key Here
	CryptoClass crypt;
	//diskSerialEncoded = privateKey->GetValue();
	diskSerialEncoded = ConvToStdString(privateKey->GetValue());

	//serialNumber->SetValue(crypt.Encrypt(diskSerialEncoded));
	serialNumber->SetValue( ConvTowxString(crypt.Encrypt(diskSerialEncoded)) );
}

///////////////////////////////////////////
void MyFrame::OnCancel(GButtonEvent &event)
{
	Destroy();
}







/////// Crypto /////////////////////////////////
CryptoClass::CryptoClass()
{
	// Key and IV setup
    ::memset( key, 0x01, CryptoPP::AES::DEFAULT_KEYLENGTH );
    ::memset(  iv, 0x01, CryptoPP::AES::BLOCKSIZE );
}

//////////////////////////////////////////////////
std::string CryptoClass::Encrypt(std::string text)
{
	CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption
        Encryptor( key, sizeof(key), iv );

	std::string EncodedText;
	CryptoPP::StringSource( text, true,
		new CryptoPP::StreamTransformationFilter( Encryptor,  
		    new CryptoPP::Base32Encoder(
				new CryptoPP::StringSink( EncodedText)
			) // Base32Encoder
		) // StreamTransformationFilter
	 );// StringSource

	return EncodedText;
}


//////////////////////////////////////////////////
/*
std::string CryptoClass::Decrypt(std::string text)
{
    // Decryption
    CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption
        Decryptor( key, sizeof(key), iv );

	std::string RecoveredText;
    CryptoPP::StringSource( text, true,
		new CryptoPP::Base32Decoder(
			new CryptoPP::StreamTransformationFilter( Decryptor,
				new CryptoPP::StringSink( RecoveredText )
			) // StreamTransformationFilter
		) // Base32Encoder
	); // StringSource

	return RecoveredText;
}
*/
