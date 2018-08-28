// MyToolBar.cpp : implementation file
//

#include "stdafx.h"
#include "wtypes.h"
#include "AFXIMPL.H"
#include "MyToolBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyToolBar

CMyToolBar::CMyToolBar ()
{
  m_cyTopBorder = 5;
  m_cyBottomBorder = 1;
}

CMyToolBar::~CMyToolBar ()
{
}

BOOL CMyToolBar::Create (CWnd * pParentWnd, DWORD dwStyle, UINT nID)
{
  ASSERT_VALID (pParentWnd);	// must have a parent
  ASSERT (!((dwStyle & CBRS_SIZE_FIXED) && (dwStyle & CBRS_SIZE_DYNAMIC)));

  dwStyle |= TBSTYLE_FLAT;

  // save the style
  m_dwStyle = dwStyle;
  if (nID == AFX_IDW_TOOLBAR)
    m_dwStyle |= CBRS_HIDE_INPLACE;

  dwStyle &= (~CBRS_ALL | TBSTYLE_FLAT);	//musste umgebaut werden, damit TBSTYLE_FLAT durchkommt!
  dwStyle |= CCS_NOPARENTALIGN | CCS_NOMOVEY | CCS_NODIVIDER | CCS_NORESIZE;

  // initialize common controls
  VERIFY (AfxDeferRegisterClass (AFX_WNDCOMMCTLS_REG));

  // create the HWND
  CRect
    rect;
  rect.SetRectEmpty ();
  if (!CWnd::Create (TOOLBARCLASSNAME, NULL, dwStyle, rect, pParentWnd, nID))
    return FALSE;

  // Note: Parent must resize itself for control bar to be resized

  return TRUE;
}

void
CMyToolBar::OnWindowPosChanging (LPWINDOWPOS lpwp)
{
  CToolBar::OnWindowPosChanging (lpwp);
  TRACE ("OnWindows....\n");
  if (!(lpwp->flags & SWP_NOMOVE)) {
    CRect rc;
    GetWindowRect (&rc);
    CWnd *pParent = GetParent ();
    pParent->ScreenToClient (&rc);
    pParent->InvalidateRect (&rc);
    PostMessage (WM_NCPAINT);
  }
}


BEGIN_MESSAGE_MAP (CMyToolBar, CToolBar)
  //{{AFX_MSG_MAP(CMyToolBar)
  ON_WM_WINDOWPOSCHANGING ()
  //}}AFX_MSG_MAP
  END_MESSAGE_MAP ()
/////////////////////////////////////////////////////////////////////////////
// CMyToolBar message handlers
