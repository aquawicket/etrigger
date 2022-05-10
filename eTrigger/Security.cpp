//// Security.cpp ///////////////////////////////////////////////////////////////////////
//
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "Security.h"

#include "../lib/Gwidgets/GHelper/GHelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/////////////////////////////////////
Security::Security(MainPanel *parent)
{
	mainPanel = parent;
	version = mainPanel->version;
	trialDays = 30;

	GetCurrentDateTime(); //fills all time holders
	wxString temp = wxT("Unknown E-mail");
	email = ConvToStdString(temp);
	
#ifdef WIN32
	diskSerial = disk.getHardDriveSerial();
	
	////// Remove blank spaces
	RemoveWhiteSpaces(diskSerial);
	/*
	int i=0; // 'Copy to' index to string
	int j=0; // 'Copy from' index to string
	while((*(diskSerial+i) = *(diskSerial+j++)) != '\0') // Loop while character
		if(*(diskSerial+i) != ' ') // Increment i as long as
			i++; // character is not a blank
	*/
#endif //WIN32
	
#ifdef MAC
	long Name; 
	long returnValue_len; 
	char returnValue[32000]; 
		
	CFDataRef dataref; 
	const UInt8* pdata; 
	CFIndex index; 
	char buffer[ 256 ]; 
	int fLoop; 
	io_iterator_t io_itr; 
	kern_return_t krt; mach_port_t mpt; 
	char szSerialNum[ 256 ] = { 0 }; 
	strcpy(szSerialNum, "SerialNumberNotFound"); 
		
	krt = IOMasterPort( MACH_PORT_NULL, &mpt ); 
	if ( krt == KERN_SUCCESS ) { 
			
		CFMutableDictionaryRef dictref = IOServiceMatching("IOPlatformExpertDevice" ); 
		if ( dictref ){ 
			krt = IOServiceGetMatchingServices( mpt, dictref, &io_itr ); 
				if ( ( KERN_SUCCESS == krt ) && io_itr ) { 
					io_object_t iot; 
					
					fLoop = 0; 
					do { 
						iot = IOIteratorNext( io_itr ); 
						if ( iot ) { 
							dataref = (CFDataRef)(IORegistryEntryCreateCFProperty( iot, CFSTR("serial-number" ), kCFAllocatorDefault, 0 ) ); 
							if ( NULL != dataref ) { 
								fLoop = 1; 
								
								pdata = CFDataGetBytePtr( dataref ); 
								index = CFDataGetLength( dataref ); 
								
								memcpy( buffer, pdata, index ); 
								
								sprintf( szSerialNum, "%s%s", buffer+13, buffer ); 
								
								CFRelease( dataref ); 
							} 
						} 
					} while ( ( NULL != iot ) && ( 0 == fLoop ) ); 
					IOObjectRelease( iot ); 
				} 
				IOObjectRelease( io_itr ); 
			} 
		} 
		strcpy(returnValue,szSerialNum); 
		returnValue_len=strlen(szSerialNum); 
		diskSerial = returnValue;
	
    if(ConvTowxString(returnValue) == wxT("SerialNumberNotFound")){
		GetFirstAndLastRunTime();
		wxString Serial = ConvTowxString(firstRunTime.GetHour());
		Serial += ConvTowxString(firstRunTime.GetSecond());
		Serial += ConvTowxString(firstRunTime.GetMonth());
		Serial += ConvTowxString(firstRunTime.GetDay());
		Serial += ConvTowxString(firstRunTime.GetYear());		
		//(const char*)diskSerial = Serial.mb_str();
		diskSerial = ConvToStdString(Serial);
		//wxMessageBox(ConvTowxString(diskSerial));
	}
	
#endif //MAC
}

////////////////////////////
void Security::DoTimeCheck()
{
	if(GetFirstAndLastRunTime()){ //ok we were able to pull info lets use it
		//Check for clock tampering
		if(currentTime < firstRunTime || currentTime < lastRunTime){
			wxMessageBox(wxT("It appears the clock has been moved back, please set the clock to the correct time."));
		}
		if(lastRunTime < firstRunTime){
			//wxMessageBox(wxT("Somehow lastRunTime happened before firstRunTime"));
		}

	}
	else{ //This must be the users first run time
		currentTime = wxDateTime::Now();
		firstRunTime = wxDateTime::Now();
		lastRunTime = wxDateTime::Now();
		//wxMessageBox("eTrigger thinks this is the first run");
	}
}

///////////////////////////////////
void Security::GetCurrentDateTime()
{
	currentTime = wxDateTime::Now();
	firstRunTime = wxDateTime::Now();
	lastRunTime = wxDateTime::Now();
}

///////////////////////////////
void Security::SetLastRunTime()
{
	lastRunTime = wxDateTime::Now();
}

///////////////////////////////////////////
void Security::ImplantFirstAndLastRunTime()
{
	/// Implant the hidden file
	wxString configPath;
	wxStandardPaths temp;
#ifdef WIN32
	configPath = temp.GetConfigDir();
	wxString temp2;
	temp2 = configPath.BeforeLast('\\');
    temp2 += wxString(wxT("\\"));
	temp2 += wxString(wxT("r9b0861hb5.ilp"));
#endif //WIN32
#ifdef MAC
	configPath = temp.GetUserConfigDir();
	wxString temp2;
	temp2 = configPath;
	temp2 += wxString(wxT("/Library/Preferences/r9b0861hb6.ilp")); //We need a better location than this
	wxString temp3;
	temp3 = configPath;
	temp3 += wxString(wxT("/Library/Preferences/hrr386.sys")); //We need a better location than this
	
	wxFile* save2 = new wxFile(temp3, wxFile::write);
	if(save2->IsOpened()){
		/// Security ////////////////////////////////////////////////////////
		save2->Write(&firstRunTime, sizeof(firstRunTime));
		save2->Write(&lastRunTime, sizeof(lastRunTime));
	}
	save2->Close();
	delete save2;
#endif //MAC

	wxFile* save = new wxFile(temp2, wxFile::write);
		if(save->IsOpened()){
			/// Security ////////////////////////////////////////////////////////
			save->Write(&firstRunTime, sizeof(firstRunTime));
			save->Write(&lastRunTime, sizeof(lastRunTime));
		}
	save->Close();
	delete save;

#ifdef WIN32
	/// Implant the registry
	wxRegKey *pRegKey = new wxRegKey("HKEY_LOCAL_MACHINE\\Software\\Tlnk2d");
	if( !pRegKey->Exists() ){  pRegKey->Create(); }

	long temp3 = firstRunTime.GetTicks();
	long temp4 = lastRunTime.GetTicks();
	pRegKey->SetValue("etrdscp", temp3);
	pRegKey->SetValue("etrdscd", temp4);

	delete pRegKey;
#endif //WIN32
}

/////////////////////////////////////////////////////////////////////////
void Security::ImplantSerialNumber(std::string email, std::string serial)
{
	/// Implant in serial number file
	wxFile* file = new wxFile(wxT("serial.dat"), wxFile::write);
	if(file->IsOpened()){
		int strlength = serial.length();
		file->Write(&strlength, sizeof(strlength));
		file->Write(ConvTowxString(serial));

		strlength = email.length();
		file->Write(&strlength, sizeof(strlength));
		file->Write(ConvTowxString(email));
	}
	file->Close();
	delete file;
}

///////////////////////////////////////
bool Security::GetFirstAndLastRunTime()
{
	//Check EVERYWHERE for first run time. 
	//returns True if data was found accordingly
	bool status = false;
	
	//First lets check the ETR.dat file
	////////////////////////////////////////////////////////////////
	if(wxFile::Exists(wxT("ETR.dat"))){
		wxFile *open = new wxFile(wxT("ETR.dat"), wxFile::read);
		if(open->IsOpened()){

			
			//If the file has data, let's load the settings
			if(!open->Eof()){

				/// HEADER //////
				int strlength;
				open->Read(&strlength, sizeof(strlength));
				char *cha = new char[strlength + 1];
				open->Read(cha, strlength);	cha[strlength] = 0;
				wxString header = ConvTowxString(cha);
				delete[] cha;

				//Check to make sure this file is valid. 
				wxString head = (wxString(wxT("ETR ")) += version);
				if(header == head){

					// Splash Screen ///////////////////////////////////////
					open->Read(&mainPanel->splashScreen, sizeof(mainPanel->splashScreen));

					/// Security ////////////////////////////////////////////////////////
					open->Read(&firstRunTime, sizeof(firstRunTime));
					open->Read(&lastRunTime, sizeof(lastRunTime));
					prevLastRunTime = lastRunTime;
					status = true;
				}

			}
			
			open->Close();
		}
		delete open;
	}

	///Check second hidden file location
	////////////////////////////////////////////////////////////
	wxString configPath;
	wxStandardPaths temp;
#ifdef WIN32
	configPath = temp.GetConfigDir();
	wxString temp2;
	temp2 = configPath.BeforeLast('\\');
    temp2 += wxString(wxT("\\"));
	temp2 += wxString(wxT("r9b0861hb5.ilp"));
#endif WIN32
#ifdef MAC
	configPath = temp.GetUserConfigDir();
	wxString temp2;
	temp2 = configPath;
	temp2 += wxString(wxT("/Library/Preferences/r9b0861hb6.ilp")); //We need a better location than this
	wxString temp3;
	temp3 = configPath;
	temp3 += wxString(wxT("/Library/Preferences/hrr386.sys")); //We need a better location than this
	
	wxFile* save2 = new wxFile(temp3, wxFile::write);
	if(save2->IsOpened()){
		/// Security ////////////////////////////////////////////////////////
		save2->Write(&firstRunTime, sizeof(firstRunTime));
		save2->Write(&lastRunTime, sizeof(lastRunTime));
	}
	save2->Close();
	delete save2;
#endif //MAC
	
	if(wxFile::Exists(temp2)){
		wxFile* open2 = new wxFile(temp2, wxFile::read);
			if(open2->IsOpened()){
				open2->Read(&firstRunTime, sizeof(firstRunTime));
				open2->Read(&lastRunTime, sizeof(lastRunTime));
				prevLastRunTime = lastRunTime;
				status = true;
			}
		open2->Close();
		delete open2;
	}	

	//// Check registry
	/////////////////////////////////////////////////////////
#ifdef WIN32
	wxRegKey *pRegKey = new wxRegKey("HKEY_LOCAL_MACHINE\\Software\\Tlnk2d");

	if( pRegKey->Exists() ){ 
		
		long temp3;
		long temp4;

		pRegKey->QueryValue("etrdscp", &temp3);
		pRegKey->QueryValue("etrdscd", &temp4);

		wxDateTime temp5 = wxDateTime((time_t)temp3);
		wxDateTime temp6 = wxDateTime((time_t)temp4);
		firstRunTime = temp5;
		lastRunTime = temp6;
		prevLastRunTime = lastRunTime;

		status = true;
	}

	delete pRegKey;
#endif //WIN32

	//Check eTrigger Server
	/////////////////////////////////////////

	return status; 
	///////////////////////////////////////////////////////////////
}

////////////////////////////////////////
void Security::GetSerialNumberFromFile()
{
	///Check application data file
	////////////////////////////////////////////////////////////
	if(wxFile::Exists(wxT("serial.dat"))){
		wxFile* file = new wxFile(wxT("serial.dat"), wxFile::read);
			if(file->IsOpened()){
				int strlength;
				file->Read(&strlength, sizeof(strlength));
				char *cha = new char[strlength + 1];
				file->Read(cha, strlength);	cha[strlength] = 0;
				wxString str = ConvTowxString(cha);
				delete[] cha;
				serialNumber = ConvToStdString(str);

				strlength;
				file->Read(&strlength, sizeof(strlength));
				char *cha2 = new char[strlength + 1];
				file->Read(cha2, strlength);	cha2[strlength] = 0;
				wxString str2 = ConvTowxString(cha2);
				delete[] cha2;

				email = ConvToStdString(str2);

				if(email.find('@', false) == -1){
					email = "Unknown E-mail";
				}
			}
		file->Close();
		delete file;
	}	
}

////////////////////////
void Security::Encrypt()
{
	//Lets Encrypt the users Hard Drive serial number.
	//The only purpose in this is that we don't make it obvious that the user is
	//sending their Hard Drive Serial number as their Computer ID.

	CryptoClass crypt;
	diskSerialEncoded = crypt.Encrypt(diskSerial);
}

////////////////////////
void Security::Decrypt()
{
	CryptoClass crypt;
	
	if(serialNumber.length() >= 52){ //serial MUST be at least 52 characters and even
		serialDecoded  = crypt.Decrypt(serialNumber);  //FIXME - crashes if wrong size!!!
	}	
}

/////////////////////////////
bool Security::IsRegistered()
{
	Encrypt();
	Decrypt();
	if(serialDecoded == diskSerialEncoded){
		return true;
	}
	return false;
}

///////////////////////////
bool Security::IsExtended()
{
	Encrypt();
	Decrypt();

	wxString serialext = ConvTowxString(serialDecoded);
	wxString extention = ConvTowxString(diskSerialEncoded.append("15DayExtention"));
	if(serialext == extention){
		trialDays = 45;
		return true;
	}
	return false;
}

////////////////////////////////
bool Security::IsTrialPeriodUp()
{
	GetSerialNumberFromFile();
	IsExtended();

	if(((currentTime.GetDayOfYear() - firstRunTime.GetDayOfYear())
		+ (((currentTime.GetYear() - firstRunTime.GetYear()) * 365))) > trialDays && !IsRegistered()){
		
		Process::active = false;
		mainPanel->Hide();
		wxMessageDialog temp(mainPanel, wxT("Trial Period Expired. Would you like to register eTrigger now?"), wxT("eTrigger Trial Period Expired"), wxYES_NO | wxSTAY_ON_TOP, wxDefaultPosition);
		int response = temp.ShowModal();
		if(response == wxID_YES){ 
			RegisterDlg *registerDlg = new RegisterDlg(mainPanel);
			registerDlg->ShowModal();
		}
		if(response == wxID_NO){
			#ifndef VST
			mainPanel->Close();
			return false;
			#endif //VST
		}

		//mainPanel->Show(true);
		//Process::active = true;
		//return true;
	}

	return false;
}

////////////////////////////////
int Security::GetTrialDaysLeft()
{
	return trialDays - (currentTime.GetDayOfYear() - firstRunTime.GetDayOfYear())
		             - (((currentTime.GetYear() - firstRunTime.GetYear()) * 365));
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
				new CryptoPP::StringSink( EncodedText )
			) // Base32Encoder
		) // StreamTransformationFilter
	); // StringSource

	return EncodedText;
}

//////////////////////////////////////////////////
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







////////////////////////////////////////
BEGIN_EVENT_TABLE(RegisterDlg, wxDialog)
	EVT_GBUTTON(202, RegisterDlg::OnBuy)
	EVT_GBUTTON(203, RegisterDlg::OnOk)
	EVT_GBUTTON(204, RegisterDlg::OnCancel)
END_EVENT_TABLE() 

/////// Register Dialog ////////////////////
RegisterDlg::RegisterDlg(MainPanel *parent)
		 : wxDialog(NULL, -1, wxT("Register eTrigger"), wxDefaultPosition, wxSize(500, 230), wxCAPTION/* | wxSTAY_ON_TOP*/)
{
	mainPanel = parent;
	CentreOnScreen(wxBOTH);
	SetBackgroundColour(wxColour(90,90,90));

	wxStaticText *registrationKey = new wxStaticText(this, -1, wxT("Registration Key"), wxPoint(11,13), wxDefaultSize, 0, wxT(""));
	privateKey = new wxTextCtrl(this, -1, wxT(""), wxPoint(10,30), wxSize(480, 20), 0, wxDefaultValidator, wxT(""));
	mainPanel->security->Encrypt();
	
	#ifndef LINUX	
	privateKey->SetValue(ConvTowxString(mainPanel->security->diskSerialEncoded));
    #endif //LINUX

	wxStaticText *emailText = new wxStaticText(this, -1, wxT("E-Mail Address"), wxPoint(11,63), wxDefaultSize, 0, wxT(""));
	email = new wxTextCtrl(this, -1, wxT(""), wxPoint(10, 80), wxSize(480, 20), 0, wxDefaultValidator, wxT(""));

	wxStaticText *serial = new wxStaticText(this, -1, wxT("Serial Key"), wxPoint(11,103), wxDefaultSize, 0, wxT(""));
	serialNumber = new wxTextCtrl(this, -1, wxT(""), wxPoint(10, 120), wxSize(480, 40), 0, wxDefaultValidator, wxT(""));

	buy = new GButton(this, 202, wxPoint(50, 170), buy_xpm, buy_hover_xpm, buy_click_xpm);
	ok = new GButton(this, 203, wxPoint(233, 170), ok_xpm, ok_hover_xpm, ok_click_xpm); 
	cancel = new GButton(this, 204, wxPoint(305, 170), cancel_xpm, cancel_hover_xpm, cancel_click_xpm);
}

////////////////////////////////////////////
void RegisterDlg::OnBuy(GButtonEvent &event)
{
	::wxLaunchDefaultBrowser(wxT("http://www.etrigger.net/buy.html"), 0);
}

///////////////////////////////////////////
void RegisterDlg::OnOk(GButtonEvent &event)
{
#ifndef LINUX
	wxString temp = serialNumber->GetValue();
	mainPanel->security->serialNumber = std::string(temp.mb_str(wxConvUTF8));
	
	wxString temp2 = email->GetValue();
	mainPanel->security->email = std::string(temp2.mb_str(wxConvUTF8));
#endif //LINUX

	//Make sure we have a valid e-mail address
    //check e-mail for a @ character and a . caracter.
	//////////////////////////////
	bool validEmail = false;
	int loc = mainPanel->security->email.find( "@", 0 );
     if( loc != string::npos ) {
		 if(loc > 1){
			loc = mainPanel->security->email.find( ".", 0 );
			if( loc != string::npos && mainPanel->security->email.size() > ((unsigned int)loc + 1)) {
				validEmail = true;
			} 
			else {
				validEmail = false;
			}
		 }
     } 
	 else {
		validEmail = false;
		
     }

	 if(!validEmail){
		 wxMessageBox(wxT("The e-mail address you entered is invalid"),wxT(""), wxSTAY_ON_TOP | wxOK);		 
       return;
	 }
	 //////////////////////////////////
	if(mainPanel->security->IsRegistered()){
		wxMessageBox(wxT("Thank you for registering eTrigger"),wxT(""), wxSTAY_ON_TOP | wxOK);
		mainPanel->security->ImplantSerialNumber(mainPanel->security->email, mainPanel->security->serialNumber);
		Destroy();
		mainPanel->Show();
	}
	else if(mainPanel->security->IsExtended()){
		wxMessageBox(wxT("Your Trial period has been extended 15 days.")); //FIXME crashed MAC
		mainPanel->security->ImplantSerialNumber(mainPanel->security->email, mainPanel->security->serialNumber);
		Destroy();
		mainPanel->Show();
	}
	else{
		wxMessageBox(wxT("The serial number you entered is incorrect.")); //FIXME crashes MAC
		Destroy();
#ifndef VST
		mainPanel->Close();
#endif
	}
}

///////////////////////////////////////////////
void RegisterDlg::OnCancel(GButtonEvent &event)
{
	if(mainPanel->security->IsRegistered()){
		Destroy();
		//mainPanel->Show();
	}
	else{
		Destroy();
		#ifndef VST
			mainPanel->par->Destroy();
		#endif
	}
}
