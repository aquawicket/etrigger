//// GHelper.cpp ///////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////

#include "GHelper.h"

//////////////////////////////////////////
wxString ConvTowxString(std::string string)
{
	return wxString(string.c_str(), wxConvUTF8);
}

//////////////////////////////////////
wxString ConvTowxString(const char* string)
{
	return wxString(string, wxConvUTF8);
}

///////////////////////////////////
wxString ConvTowxString(int string)
{
	return wxString::Format(wxT("%d"), string);
}


//////////////////////////////////////
wxString ConvTowxString(double string)
{
	return wxString::Format(wxT("%d"), string);
}

////////////////////////////////////
wxString ConvTowxString(bool string)
{
	if(string == true){return wxT("TRUE");}
	return wxT("FALSE");
}

////////////////////////////////////////////
std::string ConvToStdString(wxString string)
{
	return std::string(string.mb_str(wxConvUTF8));
}

//////////////////////////////
int ConvToInt(wxString string)
{
	int temp;
	string.ToLong((long *) &temp);
	return temp;
}

/////////////////////////////////////
double ConvToDouble(wxString string)
{
	double temp;
	if(!string.ToDouble((double *) &temp)){wxMessageBox(wxT("Error in ConvToDouble(wxString)"));}
	return temp;
}

////////////////////////////////////////
wxImage ConvTowxImage(wxString file)
{
	if(wxFile::Exists(file)){ //.BMP
		wxImage image = wxImage(file, wxBITMAP_TYPE_ANY);
		return image;
	}
	return NULL;
}

///////////////////////////////////////////////////////
wxImage ConvTowxImage(wxString file, const char** xpm)
{
	wxImage image;
	if(wxFile::Exists(file)){ //.BMP
		image = wxImage(file, wxBITMAP_TYPE_ANY);
	}
	else{ //XPM
		image = wxImage(xpm);
	}
	return image;
}

//////////////////////////////////////////////
void WriteString (wxString &str, wxFile &file)
{
	int strlength = str.length();
	file.Write(&strlength, sizeof(strlength));
	file.Write(str);
}

/////////////////////////////////
wxString ReadString(wxFile &file)
{
	int strlength;
	file.Read(&strlength, sizeof(strlength));
	char *cha = new char[strlength + 1];
	file.Read(cha, strlength);	cha[strlength] = 0;
	wxString str = ConvTowxString(cha);
	delete[] cha;

	return str;
}

////////////////////////////////////////
void RemoveWhiteSpaces(std::string &str)
{
    std::string temp;
    for (unsigned int i = 0; i < str.length(); i++)
        if (str[i] != ' ') temp += str[i];
    str = temp;
}