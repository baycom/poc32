// MyMessageBox.cpp : implementation file
//

#include "stdafx.h"
#include "pex32.h"
#include "MyMessageBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyMessageBox dialog


CMyMessageBox::CMyMessageBox (CWnd * pParent /*=NULL*/ )
:CDialog (CMyMessageBox::IDD, pParent)
{
  //{{AFX_DATA_INIT(CMyMessageBox)
  m_text = _T ("");
  //}}AFX_DATA_INIT
  m_timeout = 10;
}


void
CMyMessageBox::DoDataExchange (CDataExchange * pDX)
{
  CDialog::DoDataExchange (pDX);
  //{{AFX_DATA_MAP(CMyMessageBox)
  DDX_Control (pDX, IDOK, m_button);
  DDX_Text (pDX, IDC_EDIT1, m_text);
  //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP (CMyMessageBox, CDialog)
  //{{AFX_MSG_MAP(CMyMessageBox)
  ON_WM_TIMER ()ON_WM_CLOSE ()
  //}}AFX_MSG_MAP
  END_MESSAGE_MAP ()
/////////////////////////////////////////////////////////////////////////////
// CMyMessageBox message handlers
     BOOL CMyMessageBox::OnInitDialog ()
{
  CDialog::OnInitDialog ();
  m_startup = time (NULL);
  SetTimer (0x1236, 1000, NULL);
  return TRUE;			// return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}

void
CMyMessageBox::OnTimer (UINT nIDEvent)
{
  if (nIDEvent == 0x1236) {
    time_t t = time (NULL);
    time_t elapse = t - m_startup;
    if (elapse >= m_timeout)
      SendMessage (WM_CLOSE);
    CString str;
    str.Format ("OK %d", m_timeout - elapse);
    m_button.SetWindowText (str);
    return;
  }

  CDialog::OnTimer (nIDEvent);
}

void
CMyMessageBox::OnClose ()
{
  KillTimer (0x1236);
  CDialog::OnClose ();
}


void
CMyMessageBox::MessageBox (int UIDC)
{
  m_text.LoadString (UIDC);
  MessageBox (m_text);
}

void
CMyMessageBox::MessageBox (CString str)
{
  m_text = str;
  Create (IDD_MYMESSAGEBOX);
  CenterWindow ();
  SetWindowPos (&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
  ShowWindow (SW_SHOW);
}
