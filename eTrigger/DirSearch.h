//// DirSearch.h /////////////////////////////////////////////////
//
//   Class for searching through directories and files
//
///////////////////////////////////////////////////////////////

#pragma once
#ifndef DIRSEARCH_H
#define DIRSEARCH_H

#include <wx/dir.h>

///////////////////////////////////////////////////
class wxSimpleDirTraverser : public wxDirTraverser
{
public:
	wxSimpleDirTraverser(wxArrayString &files, wxArrayString &dirs,
		wxString strPattern = wxEmptyString)
	  : m_arrayFiles(files)
	  , m_arrayDirs(dirs)
	  , m_strPattern(strPattern)
	{ }

	virtual wxDirTraverseResult OnFile(const wxString& filename);
	virtual wxDirTraverseResult OnDir(const wxString& dirname);

private:
	wxString m_strPattern;
	wxArrayString &m_arrayFiles;
	wxArrayString &m_arrayDirs;
};


#endif DIRSEARCH_H