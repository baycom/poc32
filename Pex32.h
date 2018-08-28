// pex32.h : main header file for the PEX32 application
//

#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "splash.h"
#include "pocdrv.h"

//#define IDM_AOT 0x10

#define WM_TOP WM_USER+284
#define WM_UPDATE WM_USER+285
#define WM_SETPREFS WM_USER+286

#define _MYTIMER 4711

#ifdef _SHAREWARE
#define BUILD "SHAREWARE"
#else
#define BUILD "FREEWARE"
#endif
#define APPVERSION "2.17"

#define _DELETE_ENTRY 3

#define _FLT_NOTACT 0
#define _FLT_ACCEPT 1
#define _FLT_REJECT 2

extern BOOL firststart;

/////////////////////////////////////////////////////////////////////////////
// CPex32App:
// See pex32.cpp for the implementation of this class
//
class CPex32App:public CWinApp
{
public:
  CPex32App ();
  CSplashWnd splash;
  HANDLE mutex;
// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CPex32App)
public:
    virtual BOOL InitInstance ();
  virtual BOOL OnIdle (LONG lCount);
  virtual int ExitInstance ();
  //}}AFX_VIRTUAL

// Implementation

  //{{AFX_MSG(CPex32App)
  //}}AFX_MSG
    DECLARE_MESSAGE_MAP ()
private:
  void ShowTipAtStartup (void);
private:
  void ShowTipOfTheDay (void);
};


/////////////////////////////////////////////////////////////////////////////
