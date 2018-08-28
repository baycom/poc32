#if !defined(AFX_MYSTATUSBAR_H__0565C233_2C5B_11D1_9D72_0000B4724F50__INCLUDED_)
#define AFX_MYSTATUSBAR_H__0565C233_2C5B_11D1_9D72_0000B4724F50__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MyStatusBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyStatusBar window

class CMyStatusBar:public CStatusBar
{
// Construction
public:
  CMyStatusBar ();
  CTime m_timeStarted;
// Attributes
public:

// Operations
public:

// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CMyStatusBar)
  //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~ CMyStatusBar ();

  // Generated message map functions
protected:
  //{{AFX_MSG(CMyStatusBar)
    afx_msg void OnTimer (UINT nIDEvent);
  afx_msg int OnCreate (LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnDestroy ();
  //}}AFX_MSG

    DECLARE_MESSAGE_MAP ()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSTATUSBAR_H__0565C233_2C5B_11D1_9D72_0000B4724F50__INCLUDED_)
