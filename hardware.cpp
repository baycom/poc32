// Hardware.cpp : implementation file
//

#include "stdafx.h"
#include "pex32.h"
#include "Decoder.h"
#include "Encoder.h"
#include "Hardware.h"
#include "Statistic.h"
#include "Set.h"
#include "Filter.h"
#include "ListManager.h"
#include "Options.h"
#include "SetGeneral.h"
#include "MyStatusBar.h"
#include "MainFrm.h"
#include "Listen.h"
#include "aliases.h"
#include "MyMessageBox.h"
#include "Pex32Doc.h"
//#include "Pex32View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHardware property page
extern CPex32Doc *pPex32Doc;
IMPLEMENT_DYNCREATE (CHardware, CPropertyPage) CHardware::CHardware ():CPropertyPage (CHardware::
	       IDD)
{
  //{{AFX_DATA_INIT(CHardware)
  m_int = -1;
  m_port = -1;
  m_syncstr = _T ("");
  m_cardnum = -1;
  m_usesndcrd = FALSE;
  m_usecom = FALSE;
  m_rxline = -1;
  m_debug = FALSE;
  m_errcor = FALSE;
  m_firflt = FALSE;
  m_channels = -1;
  //}}AFX_DATA_INIT
}

CHardware::~CHardware ()
{
}

void
CHardware::DoDataExchange (CDataExchange * pDX)
{
  CPropertyPage::DoDataExchange (pDX);
  //{{AFX_DATA_MAP(CHardware)
  DDX_Control (pDX, IDC_USESNDCRD, m_sndcrdctrl);
  DDX_Control (pDX, IDC_USECOM, m_usecomctrl);
  DDX_Control (pDX, IDC_SOUNDCARD, m_soundcard);
  DDX_CBIndex (pDX, IDC_INT, m_int);
  DDX_CBIndex (pDX, IDC_PORT, m_port);
  DDX_Text (pDX, IDC_SYNCWORD, m_syncstr);
  DDV_MaxChars (pDX, m_syncstr, 10);
  DDX_CBIndex (pDX, IDC_SOUNDCARD, m_cardnum);
  DDX_Check (pDX, IDC_USESNDCRD, m_usesndcrd);
  DDX_Check (pDX, IDC_USECOM, m_usecom);
  DDX_CBIndex (pDX, IDC_RXLINE, m_rxline);
  DDX_Check (pDX, IDC_DEBUG2, m_debug);
  DDX_Check (pDX, IDC_CORR, m_errcor);
  DDX_Check (pDX, IDC_FIRFLT, m_firflt);
  DDX_CBIndex (pDX, IDC_CHANNELS, m_channels);
  //}}AFX_DATA_MAP

}


BEGIN_MESSAGE_MAP (CHardware, CPropertyPage)
  //{{AFX_MSG_MAP(CHardware)
  //}}AFX_MSG_MAP
  END_MESSAGE_MAP ()
/////////////////////////////////////////////////////////////////////////////
// CHardware message handlers
     BOOL CHardware::OnInitDialog ()
{
  CPropertyPage::OnInitDialog ();

  if (pPex32Doc->m_hCVxD == INVALID_HANDLE_VALUE)
    SetWindowLong (m_usecomctrl.m_hWnd, GWL_STYLE,
		   GetWindowLong (m_usecomctrl.m_hWnd,
				  GWL_STYLE) | WS_DISABLED);

  if (m_sndstr[0].IsEmpty ())
    SetWindowLong (m_sndcrdctrl.m_hWnd, GWL_STYLE,
		   GetWindowLong (m_sndcrdctrl.m_hWnd,
				  GWL_STYLE) | WS_DISABLED);

  m_soundcard.InitStorage (8, 1024);
  for (int i = 0; i < 8; i++)
    if (!m_sndstr[i].IsEmpty ())
      m_soundcard.InsertString (i, m_sndstr[i]);
    else
      break;
  UpdateData (FALSE);
  return TRUE;			// return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}

void
CHardware::OnOK ()
{
  TRACE ("OnOk\n");
  CPropertyPage::OnOK ();
  ::SendMessage (AfxGetApp ()->m_pMainWnd->m_hWnd, WM_COMMAND, WM_SETPREFS,
		 0);
}

BOOL CHardware::OnCommand (WPARAM wParam, LPARAM lParam)
{
  SetModified (TRUE);
  return CPropertyPage::OnCommand (wParam, lParam);
}

BOOL CHardware::OnNotify (WPARAM wParam, LPARAM lParam, LRESULT * pResult)
{
  //TRACE("Notify %x",wParam);
  if (wParam)
    SetModified (TRUE);
  return CPropertyPage::OnNotify (wParam, lParam, pResult);
}
