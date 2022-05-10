//// Joystick.cpp ///////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "Joystick.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

////////////////////////////////////
BEGIN_EVENT_TABLE(Joystick, wxWindow)
	EVT_JOYSTICK_EVENTS(Joystick::OnJoystick) 
END_EVENT_TABLE() 

////////////////////////////////
Joystick::Joystick(MainPanel* parent)
{
	mainPanel = parent;
	trackProc = mainPanel->trackProc;

	detectMinX = 65000;
	detectMinY = 65000;
	detectMinZ = 65000;
	detectMinR = 65000;
	detectMinU = 65000;
	detectMinV = 65000;
	detectMaxX = 0;
	detectMaxY = 0;
	detectMaxZ = 0;
	detectMaxR = 0;
	detectMaxU = 0;
	detectMaxV = 0;
	detectMaxAxes = false;

	for(int i=0; i<10; ++i){
		for(int n=0; n<4; ++n){
			dancePadFlags[i][n] = false;
		}
	}
}

/////////////////////
Joystick::~Joystick()
{
	for(unsigned int i=0; i<joy.size(); ++i){
		delete joy[i]->wxjoy;
		delete joy[i];
	}
}

////////////////////////////////////
wxArrayString Joystick::GetDevices()
{
	wxArrayString devices;
	
#ifdef WIN32
	for(int i=0; i<wxJoystickEx::GetNumberJoysticks(); ++i){
		wxJoystickEx *temp = new wxJoystickEx(i);
		if(temp->IsOk()){
			devices.Add(temp->GetProductName(), 1);
		}
		delete temp;
	}
#endif //WIN32
#ifdef MAC
	for(int i=0; i<wxJoystick::GetNumberJoysticks(); ++i){
		wxJoystick *temp = new wxJoystick(i);
		if(temp->IsOk()){
			devices.Add(temp->GetProductName(), 1);
		}
		delete temp;
	}
#endif //MAC
	
	return devices;
}

/////////////////////////////////////////////
void Joystick::SetDevices(wxArrayString in)
{

//#ifdef WIN32
	selected.Clear();

	//Close all open joysticks here
	for(unsigned int k=0; k<joy.size(); ++k){
		joy[k]->wxjoy->ReleaseCapture();
		delete joy[k]->wxjoy;
		delete joy[k];
	}
	joy.clear();

	bool joyFlags[10]; //We don't want to try and load devices that are allready loaded
	for(int f=0; f<10; ++f){joyFlags[f] = false;}

	int n=0;
	for(unsigned int i=0; i<in.GetCount(); ++i)
	{
#ifdef WIN32
		for(int z=0; z<wxJoystickEx::GetNumberJoysticks(); ++z){
			if(joyFlags[z]){continue;} //allready loaded this device
			wxJoystickEx *temp = new wxJoystickEx(z);
#endif //WIN32
#ifdef MAC
		for(int z=0; z<wxJoystick::GetNumberJoysticks(); ++z){
			if(joyFlags[z]){continue;} //allready loaded this device
			wxJoystick *temp = new wxJoystick(z);
#endif MAC
			if(temp->IsOk()){
			
				if(temp->GetProductName() == in.Item(i)){
					joyFlags[z] = true; //mark device loaded
					delete temp;
					joy.push_back(new JOY);
#ifdef WIN32
					joy[n]->wxjoy = new wxJoystickEx(z);
#endif //WIN32
#ifdef MAC
					joy[n]->wxjoy = new wxJoystick(z);
#endif//MAC

					selected.Add(in.Item(i), 1);
					joy[n]->wxjoy->SetCapture(this, pollSpeed);

					//Set min and max variables
					if(joy[n]->wxjoy->GetNumberAxes() > 0){
						joy[n]->minX = joy[n]->wxjoy->GetXMin();
						joy[n]->maxX = joy[n]->wxjoy->GetXMax();
					}
					if(joy[n]->wxjoy->GetNumberAxes() > 1){
						joy[n]->minY = joy[n]->wxjoy->GetYMin();
						joy[n]->maxY = joy[n]->wxjoy->GetYMax();
					}
					if(joy[n]->wxjoy->HasZ()){
						joy[n]->minZ = joy[n]->wxjoy->GetZMin();
						joy[n]->maxZ = joy[n]->wxjoy->GetZMax();
					}
					if(joy[n]->wxjoy->HasRudder()){
						joy[n]->minR = joy[n]->wxjoy->GetRudderMin();
						joy[n]->maxR = joy[n]->wxjoy->GetRudderMax();
					}
					if(joy[n]->wxjoy->HasU()){
						joy[n]->minU = joy[n]->wxjoy->GetUMin();
						joy[n]->maxU = joy[n]->wxjoy->GetUMax();
					}
					if(joy[n]->wxjoy->HasV()){
						joy[n]->minV = joy[n]->wxjoy->GetVMin();
						joy[n]->maxV = joy[n]->wxjoy->GetVMax();
					}

					if(joy[n]->wxjoy->GetProductName() == wxT("DRUM")){
						joy[n]->maxX = 10000;
						joy[n]->maxY = 10000;
						joy[n]->maxZ = 10000;
						joy[n]->maxR = 10000;
						joy[n]->maxU = 10000;
						joy[n]->maxV = 10000;
					}

					/*
					Sleep(1000);
			
					//Display FULL drum info here for debug
					wxMessageBox(wxString::Format(wxT("Device Name: %s\n"
												 "Minimal Polling: %d\n"
												 "Axes: %d   Buttons: %d\n"
												 "HasR: %d   HasV: %d   HasU: %d\n"
												 "HasPOV: %d   HasPOV4Dir: %d   HasPOVCTS(): %d\n"
												 "minX: %d   maxX: %d   X-value: %d\n" 
												 "minY: %d   maxY: %d   Y-value: %d\n" 
												 "minZ: %d   maxZ: %d   Z-value: %d\n" 
												 "minR: %d   maxR: %d   R-value: %d\n" 
												 "minV: %d   maxV: %d   V-value: %d\n" 
												 "minU: %d   maxU: %d   U-value: %d\n"), 
												 joy2[n]->wxjoy->GetProductName(),
												 joy2[n]->wxjoy->GetPollingMin(),
												 joy2[n]->wxjoy->GetNumberAxes(),
												 joy2[n]->wxjoy->GetNumberButtons(),
												 joy2[n]->wxjoy->HasRudder(),
												 joy2[n]->wxjoy->HasV(),
												 joy2[n]->wxjoy->HasU(),
												 joy2[n]->wxjoy->HasPOV(),
												 joy2[n]->wxjoy->HasPOV4Dir(),
												 joy2[n]->wxjoy->HasPOVCTS(),
												 joy2[n]->minX,
												 joy2[n]->maxX,
												 joy2[n]->wxjoy->GetPosition().x,
												 joy2[n]->minY,
												 joy2[n]->maxY,
												 joy2[n]->wxjoy->GetPosition().y,
												 joy2[n]->minZ,
												 joy2[n]->maxZ,
												 joy2[n]->wxjoy->GetZPosition(),
												 joy2[n]->minR,
												 joy2[n]->maxR,
												 joy2[n]->wxjoy->GetRudderPosition(),
												 joy2[n]->minV,
												 joy2[n]->maxV,
												 joy2[n]->wxjoy->GetVPosition(),
												 joy2[n]->minU,
												 joy2[n]->maxU,
												 joy2[n]->wxjoy->GetUPosition()));
					////////////////////////////////////////
					*/

					++n;
					break;
				}	
			}
		}
	}
	//#endif
}

//////////////////////
void Joystick::Reload()
{
	wxArrayString storeSelected = selected;
	int storeMinX = GetMinX();
	int storeMinY = GetMinY();
	int storeMinZ = GetMinZ();
	int storeMinR = GetMinR();
	int storeMinU = GetMinU();
	int storeMinV = GetMinV();

	int storeMaxX = GetMaxX();
	int storeMaxY = GetMaxY();
	int storeMaxZ = GetMaxZ();
	int storeMaxR = GetMaxR();
	int storeMaxU = GetMaxU();
	int storeMaxV = GetMaxV();

	SetDevices(storeSelected);

	SetMinX(storeMinX);
	SetMinY(storeMinY);
	SetMinZ(storeMinZ);
	SetMinR(storeMinR);
	SetMinU(storeMinU);
	SetMinV(storeMinV);

	SetMaxX(storeMaxX);
	SetMaxY(storeMaxY);
	SetMaxZ(storeMaxZ);
	SetMaxR(storeMaxR);
	SetMaxU(storeMaxU);
	SetMaxV(storeMaxV);
}


//////////////////////
int Joystick::GetMinX()
{
	if(joy.size() > 0){
		return joy[0]->minX;
	}
	return 0;
}

//////////////////////
int Joystick::GetMinY()
{
	if(joy.size() > 0){
		return joy[0]->minY;
	}
	return 0;
}

//////////////////////
int Joystick::GetMinZ()
{
	if(joy.size() > 0){
		return joy[0]->minZ;
	}
	return 0;
}

//////////////////////
int Joystick::GetMinR()
{
	if(joy.size() > 0){
		return joy[0]->minR;
	}
	return 0;
}


//////////////////////
int Joystick::GetMinU()
{
	if(joy.size() > 0){
		return joy[0]->minU;
	}
	return 0;
}

//////////////////////
int Joystick::GetMinV()
{
	if(joy.size() > 0){
		return joy[0]->minV;
	}
	return 0;
}

//////////////////////////////
void Joystick::SetMinX(int num)
{
	for(unsigned int n=0; n<joy.size(); ++n){
			joy[n]->minX = num;
	}
}

//////////////////////////////
void Joystick::SetMinY(int num)
{
	for(unsigned int n=0; n<joy.size(); ++n){
			joy[n]->minY = num;
	}
}

//////////////////////////////
void Joystick::SetMinZ(int num)
{
	for(unsigned int n=0; n<joy.size(); ++n){
			joy[n]->minZ = num;
	}
}

//////////////////////////////
void Joystick::SetMinR(int num)
{
	for(unsigned int n=0; n<joy.size(); ++n){
			joy[n]->minR = num;
	}
}

//////////////////////////////
void Joystick::SetMinU(int num)
{
	for(unsigned int n=0; n<joy.size(); ++n){
			joy[n]->minU = num;
	}
}

//////////////////////////////
void Joystick::SetMinV(int num)
{
	for(unsigned int n=0; n<joy.size(); ++n){
			joy[n]->minV = num;
	}
}



//////////////////////
int Joystick::GetMaxX()
{
	if(joy.size() > 0){
		return joy[0]->maxX;
	}
	return 0;
}

//////////////////////
int Joystick::GetMaxY()
{
	if(joy.size() > 0){
		return joy[0]->maxY;
	}
	return 0;
}

//////////////////////
int Joystick::GetMaxZ()
{
	if(joy.size() > 0){
		return joy[0]->maxZ;
	}
	return 0;
}

//////////////////////
int Joystick::GetMaxR()
{
	if(joy.size() > 0){
		return joy[0]->maxR;
	}
	return 0;
}

//////////////////////
int Joystick::GetMaxU()
{
	if(joy.size() > 0){
		return joy[0]->maxU;
	}
	return 0;
}

//////////////////////
int Joystick::GetMaxV()
{
	if(joy.size() > 0){
		return joy[0]->maxV;
	}
	return 0;
}

//////////////////////////////
void Joystick::SetMaxX(int num)
{
	for(unsigned int n=0; n<joy.size(); ++n){
			joy[n]->maxX = num;
	}
}

//////////////////////////////
void Joystick::SetMaxY(int num)
{
	for(unsigned int n=0; n<joy.size(); ++n){
			joy[n]->maxY = num;
	}
}

//////////////////////////////
void Joystick::SetMaxZ(int num)
{
	for(unsigned int n=0; n<joy.size(); ++n){
			joy[n]->maxZ = num;
	}
}

//////////////////////////////
void Joystick::SetMaxR(int num)
{
	for(unsigned int n=0; n<joy.size(); ++n){
			joy[n]->maxR = num;
	}
}

//////////////////////////////
void Joystick::SetMaxU(int num)
{
	for(unsigned int n=0; n<joy.size(); ++n){
			joy[n]->maxU = num;
	}
}

//////////////////////////////
void Joystick::SetMaxV(int num)
{
	for(unsigned int n=0; n<joy.size(); ++n){
			joy[n]->maxV = num;
	}
}

/////////////////////////////
void Joystick::DetectMaxAxes()
{
	detectMaxAxes = true;
}

/////////////////////////////
void Joystick::ResetMaxAxes()
{
	detectMinX = 65000;
	detectMinY = 65000;
	detectMinZ = 65000;
	detectMinR = 65000;
	detectMinU = 65000;
	detectMinV = 65000;

	detectMaxX = 0;
	detectMaxY = 0;
	detectMaxZ = 0;
	detectMaxR = 0;
	detectMaxU = 0;
	detectMaxV = 0;
}

/////////////////////////////////////////////////////
void Joystick::OnJoystick(wxJoystickEvent &event)
{
//#ifdef WIN32
	static wxPoint xy_pos;
    static int z_pos, r_pos, u_pos, v_pos;

	//message[0] = //device #
	//message[1] = //button / axis
	//message[2] = //number;
	std::vector<unsigned char> message(3);

	message[0] = -1;
	for(unsigned int i=0; i<joy.size(); ++i){
#ifdef WIN32
		if(joy[i]->wxjoy->m_data.joyId == event.GetJoystick()){ //FIXME - THESE DON'T ALWAYS MATCH!!  BAD BUG
#endif //WIN32
			message[0] = i;
#ifdef WIN32
		}
#endif //WIN32
	}
	if(message[0] == -1){return;}

	wxString string = joy[message[0]]->wxjoy->GetProductName();

	////// Button Down ///////////
	if(event.ButtonDown(wxJOY_BUTTON_ANY)){
		message[1] = event.GetButtonChange() + 1;
        message[2] = 64; 
	}

	////// Button Up /////////////
	else if(event.ButtonUp(wxJOY_BUTTON_ANY)){
		message[1] = event.GetButtonChange() + 1;
        message[2] = 0; 
	}

	// The axis event must be converted to a 0 - 127 scale.
	// Percent = position * 100 / position max;
	// Velocity = Percent * 127 / 100;
	// OR Velocity = (position * 100 / position Max) * 127 / 100;

	else if (event.IsMove()) {
		
		if (xy_pos.x != joy[message[0]]->wxjoy->GetPosition().x) {
			xy_pos.x = joy[message[0]]->wxjoy->GetPosition().x;
 
			if(detectMaxAxes && xy_pos.x < detectMinX && (mainPanel->optionsDialog != NULL)){
				detectMinX = xy_pos.x;
				mainPanel->optionsDialog->joyMinXBox->SetValue(wxString::Format(wxT("%d"),detectMinX));
			}

			if(detectMaxAxes && xy_pos.x > detectMaxX && (mainPanel->optionsDialog != NULL)){
				detectMaxX = xy_pos.x;
				mainPanel->optionsDialog->joyMaxXBox->SetValue(wxString::Format(wxT("%d"),detectMaxX));
			}

			if(xy_pos.x < joy[message[0]]->minX){ 
				xy_pos.x = joy[message[0]]->minX; 
			}
			if(xy_pos.x > joy[message[0]]->maxX){ 
				xy_pos.x = joy[message[0]]->maxX; 
			}

			message[1] = 'X';
			int percent = (xy_pos.x * 100) / (joy[message[0]]->maxX);
			message[2] = ((percent * 127) / 100);

			if(string == wxT("TWIN PS TO PC CONVERTER")){ //DancePad
				if(message[2] == 0){ //left press
					message[1] = 1;
					message[2] = 64;
					dancePadFlags[message[0]][0] = true;
				}
				if(message[2] == 127){ //right press
					message[1] = 6;
					message[2] = 64; 
					dancePadFlags[message[0]][1] = true;
				}
				if(message[2] == 62){
					message[1] = 1;
					message[2] = 0; 
					if(dancePadFlags[message[0]][0] == true){ //left release
						message[1] = 1;
						dancePadFlags[message[0]][0] = false;
					}
					if(dancePadFlags[message[0]][1] == true){ //right release
						message[1] = 6;
						dancePadFlags[message[0]][1] = false;
					}
				}
			}
		}
		
		else if (xy_pos.y != joy[message[0]]->wxjoy->GetPosition().y) {
			xy_pos.y = joy[message[0]]->wxjoy->GetPosition().y;

			if(detectMaxAxes && xy_pos.y < detectMinY && (mainPanel->optionsDialog != NULL)){
				detectMinY = xy_pos.y;
				mainPanel->optionsDialog->joyMinYBox->SetValue(wxString::Format(wxT("%d"),detectMinY));
			}

			if(detectMaxAxes && xy_pos.y > detectMaxY && (mainPanel->optionsDialog != NULL)){
				detectMaxY = xy_pos.y;
				mainPanel->optionsDialog->joyMaxYBox->SetValue(wxString::Format(wxT("%d"),detectMaxY));
			}

			if(xy_pos.y < joy[message[0]]->minY){ xy_pos.y = joy[message[0]]->minY; }
			if(xy_pos.y > joy[message[0]]->maxY){ xy_pos.y = joy[message[0]]->maxY; }

			message[1] = 'Y';
			int percent = (xy_pos.y * 100) / (joy[message[0]]->maxY);
			message[2] = ((percent * 127) / 100);

			if(string == wxT("TWIN PS TO PC CONVERTER")){ //DancePad
				if(message[2] == 0){ //Up press
					message[1] = 5;
					message[2] = 64; 
					dancePadFlags[message[0]][3] = true;
				}
				if(message[2] == 127){ //Down press
					message[1] = 4;
					message[2] = 64; 
					dancePadFlags[message[0]][4] = true;
				}
				if(message[2] == 62){ 
					message[1] = 5;
					message[2] = 0; 
					if(dancePadFlags[message[0]][3] == true){ //Up release
						message[1] = 5;
						dancePadFlags[message[0]][3] = false;
					}
					if(dancePadFlags[message[0]][4] == true){ //Down release
						message[1] = 4;
						dancePadFlags[message[0]][4] = false;
					}
				}
			}
		}

		else if (r_pos != joy[message[0]]->wxjoy->GetRudderPosition()) {
			r_pos = joy[message[0]]->wxjoy->GetRudderPosition();

			if(detectMaxAxes && r_pos < detectMinR && (mainPanel->optionsDialog != NULL)){
				detectMinR = r_pos;
				mainPanel->optionsDialog->joyMinRBox->SetValue(wxString::Format(wxT("%d"),detectMinR));
			}

			if(detectMaxAxes && r_pos > detectMaxR && (mainPanel->optionsDialog != NULL)){
				detectMaxR = r_pos;
				mainPanel->optionsDialog->joyMaxRBox->SetValue(wxString::Format(wxT("%d"),detectMaxR));
			}

			if(r_pos < joy[message[0]]->minR){ r_pos = joy[message[0]]->minR; }
			if(r_pos > joy[message[0]]->maxR){ r_pos = joy[message[0]]->maxR; }

			message[1] = 'R';
			int percent = (r_pos * 100) / (joy[message[0]]->maxR);
			message[2] = ((percent * 127) / 100);
		}

		else if (u_pos != joy[message[0]]->wxjoy->GetUPosition()) {
			u_pos = joy[message[0]]->wxjoy->GetUPosition();

			if(detectMaxAxes && u_pos < detectMinU && (mainPanel->optionsDialog != NULL)){
				detectMinU = u_pos;
				mainPanel->optionsDialog->joyMinUBox->SetValue(wxString::Format(wxT("%d"),detectMinU));
			}

			if(detectMaxAxes && u_pos > detectMaxU && (mainPanel->optionsDialog != NULL)){
				detectMaxU = u_pos;
				mainPanel->optionsDialog->joyMaxUBox->SetValue(wxString::Format(wxT("%d"),detectMaxU));
			}

			if(u_pos < joy[message[0]]->minU){ u_pos = joy[message[0]]->minU; }
			if(u_pos > joy[message[0]]->maxU){ u_pos = joy[message[0]]->maxU; }

			message[1] = 'U';
			int percent = (u_pos * 100) / (joy[message[0]]->maxU);
			message[2] = ((percent * 127) / 100);
		}

		else if (v_pos != joy[message[0]]->wxjoy->GetVPosition()) {
			v_pos = joy[message[0]]->wxjoy->GetVPosition();

			if(detectMaxAxes && v_pos < detectMinV && (mainPanel->optionsDialog != NULL)){
				detectMinV = v_pos;
				mainPanel->optionsDialog->joyMinVBox->SetValue(wxString::Format(wxT("%d"),detectMinV));
			}

			if(detectMaxAxes && v_pos > detectMaxV && (mainPanel->optionsDialog != NULL)){
				detectMaxV = v_pos;
				mainPanel->optionsDialog->joyMaxVBox->SetValue(wxString::Format(wxT("%d"),detectMaxV));
			}

			if(v_pos < joy[message[0]]->minV){ v_pos = joy[message[0]]->minV; }
			if(v_pos > joy[message[0]]->maxV){ v_pos = joy[message[0]]->maxV; }

			message[1] = 'V';
			int percent = (v_pos * 100) / (joy[message[0]]->maxV);
			message[2] = ((percent * 127) / 100);
		}

		else{
			return; //we got a axis move event, yet everything matched.
		}
		
    }

    else if (event.IsZMove()) {
		if (z_pos != joy[message[0]]->wxjoy->GetZPosition()) {
			z_pos = joy[message[0]]->wxjoy->GetZPosition();

			if(detectMaxAxes && z_pos < detectMinZ && (mainPanel->optionsDialog != NULL)){
				detectMinZ = z_pos;
				mainPanel->optionsDialog->joyMinZBox->SetValue(wxString::Format(wxT("%d"),detectMinZ));
			}

			if(detectMaxAxes && z_pos > detectMaxZ && (mainPanel->optionsDialog != NULL)){
				detectMaxZ = z_pos;
				mainPanel->optionsDialog->joyMaxZBox->SetValue(wxString::Format(wxT("%d"),detectMaxZ));
			}

			if(z_pos < joy[message[0]]->minZ){ z_pos = joy[message[0]]->minZ; }
			if(z_pos > joy[message[0]]->maxZ){ z_pos = joy[message[0]]->maxZ; }

			message[1] = 'Z';		
			int percent = (z_pos * 100) / (joy[message[0]]->maxZ);
		    message[2] = ((percent * 127) / 100);
		}

		else{
			return; //we got a axis move event, yet everything matched.
		}
    }

	else{
		wxMessageBox(wxT("Error: Unknown event Type in JoyProc"));
		return;
	}
	/*
    // if negative positions are possible then shift everything up
    int xmin = wxGetApp().m_minX;
    int xmax = wxGetApp().m_maxX;
    int ymin = wxGetApp().m_minY;
    int ymax = wxGetApp().m_maxY;
    if (xmin < 0) {
        xmax += abs(xmin);
        pt.x += abs(xmin);
    }
    if (ymin < 0) {
        ymax += abs(ymin);
        pt.y += abs(ymin);
    }
	*/

	//OutputDebugString(wxString::Format("%d, %d, %d \n", message[0], message[1], message[2]));
	Process::Send(3, string, NULL, message); // Send to main Processor
//#endif
}
