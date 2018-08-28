// splash.cpp : implementation file
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1995 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.
#include "stdafx.h"
#include "pex32.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSplashWnd dialog
BEGIN_MESSAGE_MAP (CSplashWnd, CDialog)
  //{{AFX_MSG_MAP(CSplashWnd)
  // NOTE - the ClassWizard will add and remove mapping macros here.
  //}}AFX_MSG_MAP
  END_MESSAGE_MAP ()
     void CSplashWnd::DoDataExchange (CDataExchange * pDX)
{
  CDialog::DoDataExchange (pDX);
  //{{AFX_DATA_MAP(CSplashWnd)
  DDX_Text (pDX, IDC_VERSION, m_version);
  //}}AFX_DATA_MAP
  TRACE ("Do Data Exchange");
}


BOOL CSplashWnd::Create (CWnd * pParent)
{
  //{{AFX_DATA_INIT(CSplashWnd)
  m_version = _T ("");
  //}}AFX_DATA_INIT

  if (!CDialog::Create (CSplashWnd::IDD, pParent)) {
    TRACE0 ("Warning: creation of CSplashWnd dialog failed\n");
    return FALSE;
  }
  return TRUE;
}

BOOL CSplashWnd::OnInitDialog ()
{
  m_version = _T ("V" APPVERSION " (" BUILD ")");
  CDialog::OnInitDialog ();
  CenterWindow ();
  return TRUE;			// return TRUE  unless you set the focus to a control
}

/////////////////////////////////////////////////////////////////////////////
// CSplashWnd message handlers
