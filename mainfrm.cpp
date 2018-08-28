// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "pex32.h"
#include "MyStatusBar.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE (CMainFrame, CPersistentFrame)
  BEGIN_MESSAGE_MAP (CMainFrame, CPersistentFrame)
  //{{AFX_MSG_MAP(CMainFrame)
  ON_WM_CREATE ()ON_COMMAND (WM_TOP, OnTop)
  ON_COMMAND (ID_LEVEL_VIEW, OnLevelView)
  ON_UPDATE_COMMAND_UI (ID_LEVEL_VIEW, OnUpdateLevelView)
  ON_COMMAND (ID_VIEW_TOOLBAR, OnViewToolbar)
  ON_UPDATE_COMMAND_UI (ID_VIEW_TOOLBAR, OnUpdateViewToolbar)
  ON_WM_CLOSE ()ON_COMMAND (ID_AOT, OnAot)
  ON_UPDATE_COMMAND_UI (ID_AOT, OnUpdateAot)
  //}}AFX_MSG_MAP
  ON_MESSAGE (WM_TOP, OnTop) END_MESSAGE_MAP ()
/*
static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};
*/
     static
       UINT
       indicators[] = {
       ID_SEPARATOR,
       IDS_MSGCNT,		// status line indicator
       IDS_UPTIME
     };

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame ()
{
  m_topmost = FALSE;
}

CMainFrame::~CMainFrame ()
{
}

int
CMainFrame::OnCreate (LPCREATESTRUCT lpCreateStruct)
{

  if (CPersistentFrame::OnCreate (lpCreateStruct) == -1)
    return -1;

  if (!m_wndToolBar.
      CreateEx (this, TBSTYLE_FLAT,
		WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY
		| CBRS_HIDE_INPLACE | CBRS_SIZE_DYNAMIC, CRect (0, 0, 0, 0),
		IDR_MAINFRAME) || !m_wndToolBar.LoadToolBar (IDR_MAINFRAME)) {
    TRACE0 ("Failed to create toolbar\n");
    return -1;			// fail to create
  }

  m_wndToolBar.EnableDocking (CBRS_ALIGN_ANY);
  m_wndToolBar.SetWindowText ("Toolbar");

  if (!m_wndStatusBar.Create (this) ||
      !m_wndStatusBar.SetIndicators (indicators,
				     sizeof (indicators) / sizeof (UINT))) {
    TRACE0 ("Failed to create status bar\n");
    return -1;			// fail to create
  }

  EnableDocking (CBRS_ALIGN_ANY);

  if (!CreateLevelBar ())
    return -1;

  DockControlBar (&m_wndToolBar);
  DockControlBar (&m_LevelBar);

/*	
	ASSERT((IDM_AOT & 0xFFF0) == IDM_AOT);
	ASSERT(IDM_AOT < 0xF000);
	m_sysmenu=GetSystemMenu(FALSE);
	m_sysmenu->AppendMenu( MF_SEPARATOR);
	m_sysmenu->AppendMenu( MF_STRING, IDM_AOT, "Always On &Top");
*/
  m_levelvis = (m_LevelBar.GetStyle () & WS_VISIBLE);

  return 0;
}

BOOL CMainFrame::CreateLevelBar (void)
{
  CRect
    rect;
  if (!m_LevelBar.
      CreateEx (this, TBSTYLE_FLAT,
		WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY
		| CBRS_HIDE_INPLACE | CBRS_SIZE_DYNAMIC, CRect (0, 0, 0, 0),
		IDR_LEVELBAR))
    return FALSE;

  if (!m_LevelBar.LoadToolBar (IDR_LEVELBAR))
    return FALSE;

  m_LevelBar.EnableDocking (CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM);
  m_LevelBar.SetWindowText ("Level view");

  m_LevelBar.SetButtonInfo (1, ID_LEVEL0, TBBS_SEPARATOR, 150);
  m_LevelBar.SetButtonInfo (4, ID_LEVEL1, TBBS_SEPARATOR, 150);

  m_LevelBar.GetItemRect (1, &rect);
  rect.left += 3;
  rect.right -= 3;
  rect.top += 5;
  rect.bottom -= 5;
  if (!m_LevelProg1.
      Create (WS_VISIBLE | WS_CHILD, rect, &m_LevelBar, ID_LEVEL0))
    return FALSE;

  m_LevelProg1.SetRange32 (0, 32767);

  m_LevelBar.GetItemRect (4, &rect);
  rect.left += 3;
  rect.right -= 3;
  rect.top += 5;
  rect.bottom -= 5;

  if (!m_LevelProg2.
      Create (WS_VISIBLE | WS_CHILD, rect, &m_LevelBar, ID_LEVEL1))
    return FALSE;

  m_LevelProg2.SetRange32 (0, 32767);

  return TRUE;
}

BOOL CMainFrame::PreCreateWindow (CREATESTRUCT & cs)
{
  // TODO: Modify the Window class or styles here by modifying
  //  the CREATESTRUCT cs
  return CPersistentFrame::PreCreateWindow (cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void
     CMainFrame::AssertValid () const const const
     {
       CPersistentFrame::AssertValid ();
     }

     void CMainFrame::Dump (CDumpContext & dc) const const const
     {
       CPersistentFrame::Dump (dc);
     }

#endif				//_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
     void CMainFrame::OnLevelView ()
{
  m_levelvis = !(m_LevelBar.GetStyle () & WS_VISIBLE);
  TRACE ("OnLevelView");
  ShowControlBar (&m_LevelBar, m_levelvis, FALSE);
}

void
CMainFrame::OnUpdateLevelView (CCmdUI * pCmdUI)
{
  pCmdUI->SetCheck ((m_LevelBar.GetStyle () & WS_VISIBLE) ? 1 : 0);
}

void
CMainFrame::OnViewToolbar ()
{
  ShowControlBar (&m_wndToolBar, (m_wndToolBar.GetStyle () & WS_VISIBLE) == 0,
		  FALSE);

}

void
CMainFrame::OnUpdateViewToolbar (CCmdUI * pCmdUI)
{
  pCmdUI->SetCheck ((m_wndToolBar.GetStyle () & WS_VISIBLE) ? 1 : 0);
}

/*
BOOL CMainFrame::TrayMessage(DWORD dwMessage, UINT CallBackMsg, UINT uID, HICON hIcon, PSTR pszTip)
{
        BOOL res;

	NOTIFYICONDATA tnd;

	tnd.cbSize		= sizeof(NOTIFYICONDATA);
	tnd.hWnd		= m_hWnd;
	tnd.uID			= uID;

	tnd.uFlags		= NIF_MESSAGE|NIF_ICON|NIF_TIP;
	tnd.uCallbackMessage	= CallBackMsg;
	tnd.hIcon		= hIcon;
	if (pszTip)
		lstrcpyn(tnd.szTip, pszTip, sizeof(tnd.szTip));
	else
		tnd.szTip[0] = '\0';

	res = Shell_NotifyIcon(dwMessage, &tnd);

	if (hIcon)
	    DestroyIcon(hIcon);

	return res;
}

void CMainFrame::NotifyDelete(UINT uIndex)
{
	TrayMessage(NIM_DELETE, 0, uIndex, NULL, NULL);
}

void CMainFrame::NotifyAdd(UINT uIndex, UINT CallBackMsg, LPSTR szTip)
{	
	TrayMessage(NIM_ADD, CallBackMsg, uIndex, 
	(HICON)LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(uIndex), IMAGE_ICON, 16, 16, 0),
				szTip);
	//TrayMessage(NIM_ADD, CallBackMsg, uIndex,AfxGetApp()->LoadIcon(uIndex), szTip);
}

*/
