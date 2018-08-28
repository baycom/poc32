// Encoder.cpp : implementation file
//

#include "stdafx.h"
#include "pex32.h"
#include "Encoder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEncoder property page

IMPLEMENT_DYNCREATE (CEncoder, CPropertyPage) CEncoder::CEncoder ():CPropertyPage (CEncoder::
	       IDD)
{
  //{{AFX_DATA_INIT(CEncoder)
  m_txdelay = 0;
  m_pttinv = FALSE;
  m_txinv = FALSE;
  //}}AFX_DATA_INIT
}

CEncoder::~CEncoder ()
{
}

void
CEncoder::DoDataExchange (CDataExchange * pDX)
{
  CPropertyPage::DoDataExchange (pDX);
  //{{AFX_DATA_MAP(CEncoder)
  DDX_Text (pDX, IDC_EDTTXDELAY, m_txdelay);
  DDV_MinMaxUInt (pDX, m_txdelay, 5, 500);
  DDX_Check (pDX, IDC_PTTINV, m_pttinv);
  DDX_Check (pDX, IDC_TXINV, m_txinv);
  //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP (CEncoder, CPropertyPage)
  //{{AFX_MSG_MAP(CEncoder)
  // NOTE: the ClassWizard will add message map macros here
  //}}AFX_MSG_MAP
  END_MESSAGE_MAP ()
/////////////////////////////////////////////////////////////////////////////
// CEncoder message handlers
     BOOL CEncoder::OnCommand (WPARAM wParam, LPARAM lParam)
{
  SetModified (TRUE);
  return CPropertyPage::OnCommand (wParam, lParam);
}
