// License.cpp : implementation file
//

#include "stdafx.h"
#include "pex32.h"
#include "License.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLicense dialog


CLicense::CLicense (CWnd * pParent /*=NULL*/ )
:CDialog (CLicense::IDD, pParent)
{
  //{{AFX_DATA_INIT(CLicense)
  m_licstr = _T ("");
  //}}AFX_DATA_INIT
}


void
CLicense::DoDataExchange (CDataExchange * pDX)
{
  CDialog::DoDataExchange (pDX);
  //{{AFX_DATA_MAP(CLicense)
  DDX_Text (pDX, IDC_LICENSE, m_licstr);
  //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP (CLicense, CDialog)
  //{{AFX_MSG_MAP(CLicense)
  // NOTE: the ClassWizard will add message map macros here
  //}}AFX_MSG_MAP
  END_MESSAGE_MAP ()
/////////////////////////////////////////////////////////////////////////////
// CLicense message handlers
