// MyStatusBar.cpp : implementation file
//

#include "stdafx.h"
#include "pex32.h"
#include "MyStatusBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyStatusBar message handlers

BEGIN_MESSAGE_MAP (CMyStatusBar, CStatusBar)
  //{{AFX_MSG_MAP(CMyStatusBar)
  ON_WM_TIMER ()ON_WM_CREATE ()ON_WM_DESTROY ()
  //}}AFX_MSG_MAP
  END_MESSAGE_MAP ()
/////////////////////////////////////////////////////////////////////////////
// CMyStatusBar
  CMyStatusBar::CMyStatusBar ()
{
}

CMyStatusBar::~CMyStatusBar ()
{
}

void
CMyStatusBar::OnTimer (UINT nIDEvent)
{
  switch (nIDEvent) {
  case 0x1235:
    {
      CString strUpTime;
      CTime timeNow = CTime::GetCurrentTime ();
      // calculate uptime and set the status bar....
      CTimeSpan upTime = timeNow - m_timeStarted;
      UINT uFmt = upTime.GetDays () > 0 ? IDS_UPTIME_DAYS : IDS_UPTIME_DAY;
      strUpTime = upTime.Format (uFmt);
      SetPaneText (2, strUpTime, TRUE);
      break;
    }
  }
  //CStatusBar::OnTimer(nIDEvent);
}

int
CMyStatusBar::OnCreate (LPCREATESTRUCT lpCreateStruct)
{
  if (CStatusBar::OnCreate (lpCreateStruct) == -1)
    return -1;
  m_timeStarted = CTime::GetCurrentTime ();
  SetTimer (0x1235, 30000, NULL);
  return 0;
}

void
CMyStatusBar::OnDestroy ()
{
  KillTimer (0x1235);
  CStatusBar::OnDestroy ();
}
