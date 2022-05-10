//// GHelper.h /////////////////////////////////////////////////////////////////////////////
//
//   This is a helper class the can help to do many tasks such as Data Canversions.
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef GHELPER_H
#define GHELPER_H

#include <string>
#include <wx/msgdlg.h>
#include <wx/string.h>
#include <wx/datetime.h>
#include <wx/file.h>
#include <wx/bitmap.h>

using namespace std;

    //// DATA CONVERTERS //////////////
	wxString ConvTowxString(std::string string);
	wxString ConvTowxString(const char* string);
	wxString ConvTowxString(int string);
	wxString ConvTowxString(double string);
	wxString ConvTowxString(bool string);
	std::string ConvToStdString(wxString string);
	int ConvToInt(wxString string);
	double ConvToDouble(wxString string);
	wxImage ConvTowxImage(wxString file);
	wxImage ConvTowxImage(wxString file, const char** xpm);

	//// FILE SYSTEM HELPERS /////////////////////
	void WriteString(wxString &str, wxFile &file);
	wxString ReadString(wxFile &file);

	/// extras //////////////////////////////
	void RemoveWhiteSpaces(std::string &str);

#endif GHELPER_H