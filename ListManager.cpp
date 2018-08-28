// ListManager.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "pex32.h"
#include "ListManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Eigenschaftenseite CListManager 

IMPLEMENT_DYNCREATE (CListManager, CPropertyPage) CListManager::CListManager ():CPropertyPage (CListManager::
	       IDD)
{
  //{{AFX_DATA_INIT(CListManager)
  m_autosave = FALSE;
  m_autosavenum = 0;
  m_cutinternalist = FALSE;
  m_cutvislist = FALSE;
  m_cutvislistnum = 0;
  m_autoload = FALSE;
  m_cutinternalistnum = 0;
  //}}AFX_DATA_INIT
}

CListManager::~CListManager ()
{
}

void
CListManager::DoDataExchange (CDataExchange * pDX)
{
  CPropertyPage::DoDataExchange (pDX);
  //{{AFX_DATA_MAP(CListManager)
  DDX_Control (pDX, IDC_SPIN3, m_spin3);
  DDX_Control (pDX, IDC_SPIN2, m_spin2);
  DDX_Control (pDX, IDC_SPIN1, m_spin1);
  DDX_Check (pDX, IDC_AUTOSAVE, m_autosave);
  DDX_Text (pDX, IDC_AUTOSAVENUM, m_autosavenum);
  DDX_Check (pDX, IDC_CUTINTERNALIST, m_cutinternalist);
  DDX_Check (pDX, IDC_CUTVISLIST, m_cutvislist);
  DDX_Text (pDX, IDC_CUTVISLISTNUM, m_cutvislistnum);
  DDX_Check (pDX, IDC_LOADLASTLIST, m_autoload);
  DDX_Text (pDX, IDC_CUTINTERNALISTNUM, m_cutinternalistnum);
  //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP (CListManager, CPropertyPage)
  //{{AFX_MSG_MAP(CListManager)
  //}}AFX_MSG_MAP
  END_MESSAGE_MAP ()
/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CListManager 
     BOOL CListManager::OnInitDialog ()
{
  CPropertyPage::OnInitDialog ();

  m_spin1.SetRange32 (0, 1000000);
  m_spin2.SetRange32 (0, 1000000);
  m_spin2.SetRange32 (0, 1000);


  return TRUE;			// return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CListManager::OnCommand (WPARAM wParam, LPARAM lParam)
{
  SetModified (TRUE);
  return CPropertyPage::OnCommand (wParam, lParam);
}

BOOL CListManager::OnApply ()
{
  ::SendMessage (AfxGetApp ()->m_pMainWnd->m_hWnd, WM_COMMAND, WM_SETPREFS,
		 0);
  return CPropertyPage::OnApply ();
}
