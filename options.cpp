// Options.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "pex32.h"
#include "Options.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Eigenschaftenseite COptions 

IMPLEMENT_DYNCREATE (COptions, CPropertyPage) COptions::COptions ():CPropertyPage (COptions::
	       IDD)
{
  //{{AFX_DATA_INIT(COptions)
  m_jumptolistend = FALSE;
  m_eliminatecalls = -1;
  m_eliminatecalls_timespan = 0;
  m_enabletcpip = FALSE;
  m_password = _T ("");
  m_tcpipport = 0;
  //}}AFX_DATA_INIT
}

COptions::~COptions ()
{
}

void
COptions::DoDataExchange (CDataExchange * pDX)
{
  CPropertyPage::DoDataExchange (pDX);
  //{{AFX_DATA_MAP(COptions)
  DDX_Control (pDX, IDC_SPIN1, m_spi1);
  DDX_Check (pDX, IDC_AUTOSCROLL, m_jumptolistend);
  DDX_CBIndex (pDX, IDC_ELIMINATECALLS, m_eliminatecalls);
  DDX_Text (pDX, IDC_TIMESPAN, m_eliminatecalls_timespan);
  DDX_Check (pDX, IDC_TCPIP, m_enabletcpip);
  DDX_Text (pDX, IDC_PASSWORD, m_password);
  DDX_Text (pDX, IDC_PORT, m_tcpipport);
  DDV_MinMaxInt (pDX, m_tcpipport, 0, 65535);
  //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP (COptions, CPropertyPage)
  //{{AFX_MSG_MAP(COptions)
  // HINWEIS: Der Klassen-Assistent fügt hier Zuordnungsmakros für Nachrichten ein
  //}}AFX_MSG_MAP
  END_MESSAGE_MAP ()
/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten COptions 
     BOOL COptions::OnCommand (WPARAM wParam, LPARAM lParam)
{
  SetModified (TRUE);
  return CPropertyPage::OnCommand (wParam, lParam);
}
