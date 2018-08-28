#include "stdafx.h"
#include "pex32.h"
#include "AboutDlg.h"

BEGIN_MESSAGE_MAP (CAboutDlg, CDialog)
  //{{AFX_MSG_MAP(CAboutDlg)
  //}}AFX_MSG_MAP
ON_BN_CLICKED (ID_LICENSE, &CAboutDlg::OnBnClickedLicense) END_MESSAGE_MAP ()CAboutDlg::CAboutDlg ():CDialog (CAboutDlg::
	 IDD)
{
  //{{AFX_DATA_INIT(CSplashWnd)
  m_version = _T ("V" APPVERSION " (" BUILD ")");
  //}}AFX_DATA_INIT
}

void
CAboutDlg::DoDataExchange (CDataExchange * pDX)
{
  CDialog::DoDataExchange (pDX);
  //{{AFX_DATA_MAP(CAboutDlg)
  DDX_Text (pDX, IDC_VERSION, m_version);
  DDX_Text (pDX, IDC_REGISTERED, m_registered);
  //}}AFX_DATA_MAP
}


BOOL CAboutDlg::OnInitDialog ()
{
  CDialog::OnInitDialog ();
  CWinApp *
    w = AfxGetApp ();
  UpdateData (FALSE);
  return TRUE;			// return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}

void
CAboutDlg::OnBnClickedLicense ()
{
  // TODO: Add your control notification handler code here
}
