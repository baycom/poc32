// TxDialog.cpp : implementation file
//

#include "stdafx.h"
#include "pex32.h"
#include "TxDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTxDialog dialog


CTxDialog::CTxDialog (CWnd * pParent /*=NULL*/ )
:CDialog (CTxDialog::IDD, pParent)
{
  //{{AFX_DATA_INIT(CTxDialog)
  m_encode = -1;
  m_fct = -1;
  m_msg = _T ("");
  m_bitrate = -1;
  m_adr = 0;
  //}}AFX_DATA_INIT
}


void
CTxDialog::DoDataExchange (CDataExchange * pDX)
{
  CDialog::DoDataExchange (pDX);
  //{{AFX_DATA_MAP(CTxDialog)
  DDX_CBIndex (pDX, IDC_ENCODE, m_encode);
  DDX_CBIndex (pDX, IDC_FCT, m_fct);
  DDX_Text (pDX, IDC_MSG, m_msg);
  DDV_MaxChars (pDX, m_msg, 256);
  DDX_CBIndex (pDX, IDC_BITRATE, m_bitrate);
  DDX_Text (pDX, IDC_ADR, m_adr);
  DDV_MinMaxUInt (pDX, m_adr, 0, 2097151);
  //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP (CTxDialog, CDialog)
  //{{AFX_MSG_MAP(CTxDialog)
  // NOTE: the ClassWizard will add message map macros here
  //}}AFX_MSG_MAP
  END_MESSAGE_MAP ()
/////////////////////////////////////////////////////////////////////////////
// CTxDialog message handlers
