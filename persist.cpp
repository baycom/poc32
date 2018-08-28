#include "stdafx.h"
#include "pex32.h"
#include "persist.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
///////////////////////////////////////////////////////////////
// CPersistentFrame

const CRect
CPersistentFrame::s_rectDefault (10, 10, 500, 400);	// static
const char
  CPersistentFrame::s_profileHeading[] = "Window size";
const char
  CPersistentFrame::s_profileRect[] = "Rect";
const char
  CPersistentFrame::s_profileIcon[] = "icon";
const char
  CPersistentFrame::s_profileMax[] = "max";
const char
  CPersistentFrame::s_AutoHide[] = "AutoHide";

IMPLEMENT_DYNAMIC (CPersistentFrame, CFrameWnd)
BEGIN_MESSAGE_MAP (CPersistentFrame, CFrameWnd)
  //{{AFX_MSG_MAP(CPersistentFrame)
  ON_WM_DESTROY ()ON_COMMAND (ID_HIDE, OnHide)
  ON_UPDATE_COMMAND_UI (ID_HIDE, OnUpdateHide) ON_WM_SIZE ()
  //}}AFX_MSG_MAP
END_MESSAGE_MAP ()
///////////////////////////////////////////////////////////////
  CPersistentFrame::CPersistentFrame ()
{
  m_bFirstTime = TRUE;
  m_bAutoHide = FALSE;
}

///////////////////////////////////////////////////////////////
CPersistentFrame::~CPersistentFrame ()
{
}

///////////////////////////////////////////////////////////////
void
CPersistentFrame::OnDestroy ()
{
  CString strText;
  BOOL bIconic, bMaximized;

  WINDOWPLACEMENT wndpl;
  wndpl.length = sizeof (WINDOWPLACEMENT);
  // gets current window position and
  //  iconized/maximized status
  BOOL bRet = GetWindowPlacement (&wndpl);
  if (wndpl.showCmd == SW_SHOWNORMAL) {
    bIconic = FALSE;
    bMaximized = FALSE;
  }
  else if (wndpl.showCmd == SW_SHOWMAXIMIZED) {
    bIconic = FALSE;
    bMaximized = TRUE;
  }
  else if (wndpl.showCmd == SW_SHOWMINIMIZED) {
    bIconic = TRUE;
    if (wndpl.flags) {
      bMaximized = TRUE;
    }
    else {
      bMaximized = FALSE;
    }
  }

  strText.Format ("%04d %04d %04d %04d",
		  wndpl.rcNormalPosition.left,
		  wndpl.rcNormalPosition.top,
		  wndpl.rcNormalPosition.right,
		  wndpl.rcNormalPosition.bottom);
  AfxGetApp ()->WriteProfileString (s_profileHeading, s_profileRect, strText);
  AfxGetApp ()->WriteProfileInt (s_profileHeading, s_profileIcon, bIconic);
  AfxGetApp ()->WriteProfileInt (s_profileHeading, s_profileMax, bMaximized);

  AfxGetApp ()->WriteProfileInt (s_profileHeading, s_AutoHide, m_bAutoHide);

  SaveBarState (AfxGetApp ()->m_pszProfileName);

  NotifyDelete (IDR_MAINFRAME);

  CFrameWnd::OnDestroy ();
}

///////////////////////////////////////////////////////////////
void
CPersistentFrame::ActivateFrame (int nCmdShow)
{
  CString strText;
  BOOL bIconic, bMaximized;
  UINT flags;
  WINDOWPLACEMENT wndpl;
  CRect rect;
  TRACE ("ActivateFrame\n");
  if (m_bFirstTime) {
    m_bFirstTime = FALSE;
    strText = AfxGetApp ()->GetProfileString (s_profileHeading,
					      s_profileRect);
    if (!strText.IsEmpty ()) {
      rect.left = atoi ((const char *) strText);
      rect.top = atoi ((const char *) strText + 5);
      rect.right = atoi ((const char *) strText + 10);
      rect.bottom = atoi ((const char *) strText + 15);
    }
    else {
      rect = s_rectDefault;
    }

    bIconic = AfxGetApp ()->GetProfileInt (s_profileHeading,
					   s_profileIcon, 0);
    bMaximized = AfxGetApp ()->GetProfileInt (s_profileHeading,
					      s_profileMax, 0);
    m_bAutoHide = AfxGetApp ()->GetProfileInt (s_profileHeading,
					       s_AutoHide, FALSE);

    TRACE ("CPersistentFrame::ActivateFrame--bIconic = %d,", bIconic);
    TRACE (" bMaximized = %d\n", bMaximized);

    if (bIconic) {
      nCmdShow = SW_SHOWMINNOACTIVE;
      if (bMaximized) {
	flags = WPF_RESTORETOMAXIMIZED;
      }
      else {
	flags = WPF_SETMINPOSITION;
      }
    }
    else {
      if (bMaximized) {
	nCmdShow = SW_SHOWMAXIMIZED;
	flags = WPF_RESTORETOMAXIMIZED;
      }
      else {
	nCmdShow = SW_NORMAL;
	flags = WPF_SETMINPOSITION;
      }
    }
    wndpl.length = sizeof (WINDOWPLACEMENT);
    wndpl.showCmd = nCmdShow;
    wndpl.flags = flags;
    wndpl.ptMinPosition = CPoint (0, 0);
    wndpl.ptMaxPosition = CPoint (-::GetSystemMetrics (SM_CXBORDER),
				  -::GetSystemMetrics (SM_CYBORDER));
    wndpl.rcNormalPosition = rect;

    LoadBarState (AfxGetApp ()->m_pszProfileName);
    // sets window's position and iconized/maximized status
    BOOL bRet = SetWindowPlacement (&wndpl);
    CFrameWnd::ActivateFrame (nCmdShow);
    if (m_bAutoHide && bIconic)
      HideWindow ();
  }
}

BOOL
  CPersistentFrame::TrayMessage (DWORD dwMessage, UINT CallBackMsg, UINT uID,
				 HICON hIcon, PSTR pszTip)
{
  BOOL res;

  NOTIFYICONDATA tnd;

  tnd.cbSize = sizeof (NOTIFYICONDATA);
  tnd.hWnd = m_hWnd;
  tnd.uID = uID;
  tnd.uCallbackMessage = CallBackMsg;
  tnd.hIcon = hIcon;

  if (CallBackMsg)
    tnd.uFlags = NIF_MESSAGE;

  if (hIcon)
    tnd.uFlags |= NIF_ICON;

  if (pszTip)
    tnd.uFlags |= NIF_TIP;

  if (pszTip)
    lstrcpyn (tnd.szTip, pszTip, sizeof (tnd.szTip));
  else
    tnd.szTip[0] = '\0';

  res = Shell_NotifyIcon (dwMessage, &tnd);

  if (hIcon)
    DestroyIcon (hIcon);

  return res;
}

void
CPersistentFrame::NotifyDelete (UINT uIndex)
{
  TrayMessage (NIM_DELETE, 0, uIndex, NULL, NULL);
}

void
CPersistentFrame::NotifyAdd (UINT uIndex, UINT CallBackMsg, LPSTR szTip)
{
  TrayMessage (NIM_ADD, CallBackMsg, uIndex,
	       (HICON) LoadImage (AfxGetApp ()->m_hInstance,
				  MAKEINTRESOURCE (uIndex), IMAGE_ICON, 16,
				  16, 0), szTip);
}

void
CPersistentFrame::NotifyModify (UINT uIndex, char *s)
{
  TrayMessage (NIM_MODIFY, 0, uIndex, 0, s);
}

void
CPersistentFrame::HideWindow ()
{
  CString s;
  s.LoadString (IDS_WNDTOP);
  NotifyAdd (IDR_MAINFRAME, WM_TOP, s.GetBuffer (300));
  ShowWindow (SW_HIDE);
  m_hidden = TRUE;
}

void
CPersistentFrame::OnHide ()
{
  m_bAutoHide = !m_bAutoHide;
}

void
CPersistentFrame::OnUpdateHide (CCmdUI * pCmdUI)
{
  pCmdUI->SetCheck (m_bAutoHide);
}

void
CPersistentFrame::OnSize (UINT nType, int cx, int cy)
{
  if ((nType == SIZE_MINIMIZED) && m_bAutoHide)
    HideWindow ();

  CFrameWnd::OnSize (nType, cx, cy);
  //TRACE("OnSize: %d %d %d\n",nType, cx, cy);
}

void
CPersistentFrame::OnTop (void)
{
  TRACE ("on Top \n");
  NotifyDelete (IDR_MAINFRAME);
  ShowWindow (SW_RESTORE);
  SetForegroundWindow ();
  m_hidden = FALSE;
}

LRESULT CPersistentFrame::OnTop (WPARAM wParam, LPARAM lParam)
{
  switch (lParam) {
  case WM_RBUTTONDOWN:
    {
      CMenu
	m;
      CPoint
	p;
      GetCursorPos (&p);
      m.LoadMenu (IDR_CONTEXT);
      m.GetSubMenu (0)->TrackPopupMenu (TPM_LEFTALIGN | TPM_RIGHTBUTTON,
					p.x, p.y, this);
    }
    break;

  case WM_LBUTTONDOWN:
    switch (wParam) {
    case IDR_MAINFRAME:
      OnTop ();
      break;

    default:
      break;
    }
    break;
  }
  return 0;
}

void
CPersistentFrame::OnAot (void)
{
  TRACE ("OnTop\n");
  m_topmost = !m_topmost;
  if (m_topmost)
    SetWindowPos (&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
  else
    SetWindowPos (&wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}

void
CPersistentFrame::OnClose ()
{
  GetSystemMenu (TRUE);
  CFrameWnd::OnClose ();
}

void
CPersistentFrame::OnUpdateAot (CCmdUI * pCmdUI)
{
  pCmdUI->SetCheck (m_topmost);
}
