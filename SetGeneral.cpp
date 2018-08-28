// SetGeneral.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "pex32.h"
#include "ListManager.h"
#include "Filter.h"
#include "Options.h"
#include "SetGeneral.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetGeneral

IMPLEMENT_DYNAMIC (CSetGeneral, CPropertySheet) CSetGeneral::CSetGeneral (UINT nIDCaption, CWnd * pParentWnd, UINT iSelectPage):CPropertySheet (nIDCaption, pParentWnd,
		iSelectPage)
{
}

CSetGeneral::CSetGeneral (LPCTSTR pszCaption, CWnd * pParentWnd, UINT iSelectPage):CPropertySheet (pszCaption, pParentWnd,
		iSelectPage)
{
  AddPage (&m_lmn);
  AddPage (&m_flt);
  AddPage (&m_opt);
  m_activepage = GetPageIndex (&m_lmn);
}

CSetGeneral::~CSetGeneral ()
{
}


BEGIN_MESSAGE_MAP (CSetGeneral, CPropertySheet)
  //{{AFX_MSG_MAP(CSetGeneral)
  // HINWEIS - Der Klassen-Assistent fügt hier Zuordnungsmakros ein und entfernt diese.
  //}}AFX_MSG_MAP
  END_MESSAGE_MAP ()
/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CSetGeneral 
     int CSetGeneral::DoModal ()
{
  SetActivePage (m_activepage);
  return CPropertySheet::DoModal ();
}

BOOL CSetGeneral::DestroyWindow ()
{
  m_activepage = GetActiveIndex ();
  return CPropertySheet::DestroyWindow ();
}
