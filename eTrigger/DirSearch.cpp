//// DirSearch.cpp //////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "DirSearch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
wxDirTraverseResult wxSimpleDirTraverser::OnFile(const wxString& filename)
{
	if(m_strPattern != wxEmptyString)
	{
		if(::wxMatchWild(m_strPattern, filename, false))
			m_arrayFiles.Add(filename);
	}
	else
	{
		m_arrayFiles.Add(filename);
	}
	return wxDIR_CONTINUE;
}

////////////////////////////////////////////////////////////////////////
wxDirTraverseResult wxSimpleDirTraverser::OnDir(const wxString& dirname)
{
	m_arrayDirs.Add(dirname);
	return wxDIR_CONTINUE;
}