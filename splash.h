// splash.h : header file
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

/////////////////////////////////////////////////////////////////////////////
// CSplash dialog

class CSplashWnd:public CDialog
{
// Construction
public:
  BOOL Create (CWnd * pParent);
  time_t m_start;
// Dialog Data
  //{{AFX_DATA(CSplashWnd)
  enum
  { IDD = IDD_SPLASH };
  CString m_version;
  //}}AFX_DATA

// Implementation
protected:
  // Generated message map functions
  //{{AFX_MSG(CSplashWnd)
    virtual BOOL OnInitDialog ();
  virtual void DoDataExchange (CDataExchange * pDX);	// DDX/DDV support
  //}}AFX_MSG
    DECLARE_MESSAGE_MAP ()
};
