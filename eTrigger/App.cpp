//// App.cpp ////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "App.h" 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_APP(MyApp); 

//////////////
MyApp::MyApp()
{
#ifndef _DEBUG
	wxHandleFatalExceptions(); //We want to catch exceptions
#endif //_DEBUG
}

///////////////
MyApp::~MyApp()
{
	//delete m_checker;
}

///////////////////////////
void MyApp::InitVariables()
{
	frame = NULL;
	for(int i=0; i<256; ++i){keyState[i] = NULL;}
	version = wxT("");
	splashScreen = NULL;
	m_checker = NULL;
}

////////////////////
bool MyApp::OnInit()
{ 
	/// eTRIGGER VERSION ///
	version = wxT("0.669");

	wxInitAllImageHandlers();
	
	//// Is another instance running ////////////
	/*
	m_checker = new wxSingleInstanceChecker(GetAppName());
	if(m_checker->IsAnotherRunning()){
		wxLogError(wxT("Another eTrigger instance is already running, aborting."));
		return false;
    }
	*/
	// Somtimes eTrigger gets stuck and the user has to restart.
	// So lets let eTrigger run as many times as needed..  who cares...


	if (!wxApp::OnInit()) return false;

	LoadMainSettings();

	//main = new Main(); 
	frame = new MainFrame(0L, wxT("eTrigger"), wxHSCROLL, version); 
		
	SetTopWindow(frame); 
	frame->SetIcon(wxICON(eTriggerServerIcon)); // <<< SetIcon just dosn't seem to want to work.
	frame->Show(true);
	frame->Refresh();

	for(int i=0; i<256; ++i){keyState[i] = false;} //zero out the key states
	
	////// Splashscreen //////////////
	if(splashScreen){
		wxSplashScreen *splash = new wxSplashScreen(wxImage(splashscreen_xpm), wxSPLASH_CENTRE_ON_SCREEN|wxSPLASH_TIMEOUT,
		                                   		    2500, NULL, -1, wxDefaultPosition, wxDefaultSize,
			                                        wxSIMPLE_BORDER/*|wxSTAY_ON_TOP*/);
	}
		
	return true;
}

///////////////////
int MyApp::OnExit()
{
    return 0;
}

//////////////////////////////
void MyApp::OnFatalException()
{
#ifdef WIN32
	ERR *error = new ERR;
	error->GenerateReport(wxDebugReport::Context_Exception, frame->mainPanel);
#endif //WIN32
}


//////////////////////////////////////
int MyApp::FilterEvent(wxEvent& event)
{
	// MASTER EVENT CLASS. All event are filtered through here.
	if(event.GetEventType()==wxEVT_KEY_DOWN){

		std::vector<unsigned char> message(3);
		message[0] = ((wxKeyEvent&)event).GetKeyCode();

		if(!keyState[message[0]]){
			keyState[message[0]] = true;
			message[1] = 1;
			message[2] = 64;
			Process::Send(4, wxT("Device: Keyboard"), NULL, message);
		}
	}

	if(event.GetEventType()==wxEVT_KEY_UP){
		std::vector<unsigned char> message(3);
		message[0] = ((wxKeyEvent&)event).GetKeyCode(); 

		if(keyState[message[0]]){
			keyState[message[0]] = false;
			message[1] = 0;
			message[2] = 0;
			Process::Send(4, wxT("Device: Keyboard"), NULL, message);
		}
	}

	if(event.GetEventType()==wxEVT_MOUSEWHEEL){
		std::vector<unsigned char> message(1);
		if(((wxMouseEvent&)event).GetWheelRotation() > 0){
			message[0] = 1;
		}
		if(((wxMouseEvent&)event).GetWheelRotation() < 0){
			message[0] = 0;
		}

		Process::Send(5, wxT("Device: Mouse"), NULL, message);
	}

	return -1; //let it pass through
}


////////////////////////////////
void MyApp::LoadMainSettings()
{
	//Lets check the file to se if we need a splash screen.
	//Does the file exists?
	if(wxFile::Exists(wxT("ETR.dat"))){
		wxFile *file = new wxFile(wxT("ETR.dat"), wxFile::read);
		if(file->IsOpened()){

			//If the file has data, let's load the settings
			if(!file->Eof()){

				/// HEADER ////////////////////////////////////////////////
				wxString header = ReadString(*file);

				//Check to make sure this file is valid. 
				wxString head = (wxString(wxT("ETR ")) += version);
				if(header == head){

					/// FRAME SIZE AND POSITION //////////////////////////////
					file->Read(&splashScreen, sizeof(splashScreen));

				}
				else{
					splashScreen = true;
					versionNotes = true;
				}
			}
			else{
				splashScreen = true;
				versionNotes = true;
			}
			file->Close();
		}
		delete file;
	}
	else{
		splashScreen = true;
		versionNotes = true;
	}
}
