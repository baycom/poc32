// Set.cpp : implementation file
//

#include "stdafx.h"
#include "pex32.h"
#include "Decoder.h"
#include "Encoder.h"
#include "Hardware.h"
#include "Statistic.h"
#include "Set.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSet

IMPLEMENT_DYNAMIC (CSet, CPropertySheet) CSet::CSet (UINT nIDCaption, CWnd * pParentWnd, UINT iSelectPage):CPropertySheet (nIDCaption, pParentWnd,
		iSelectPage)
{
}

CSet::CSet (LPCTSTR pszCaption, CWnd * pParentWnd, UINT iSelectPage):CPropertySheet (pszCaption, pParentWnd,
		iSelectPage)
{
  AddPage (&m_dec);
  AddPage (&m_enc);
  AddPage (&m_hw);
  AddPage (&m_st);
  m_activepage = GetPageIndex (&m_dec);
  TRACE ("Prop COnst\n");
}

CSet::~CSet ()
{
}


BEGIN_MESSAGE_MAP (CSet, CPropertySheet)
  //{{AFX_MSG_MAP(CSet)
  // NOTE - the ClassWizard will add and remove mapping macros here.
  //}}AFX_MSG_MAP
  END_MESSAGE_MAP ()
/////////////////////////////////////////////////////////////////////////////
// CSet message handlers
     int CSet::DoModal ()
{
  SetActivePage (m_activepage);
  return CPropertySheet::DoModal ();
}

BOOL CSet::DestroyWindow ()
{
  m_activepage = GetActiveIndex ();
  return CPropertySheet::DestroyWindow ();
}
