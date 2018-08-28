#if !defined(AFX_MYTOOLBAR_H__E9316062_5376_11D1_9DBD_0000B4724F50__INCLUDED_)
#define AFX_MYTOOLBAR_H__E9316062_5376_11D1_9DBD_0000B4724F50__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MyToolBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyToolBar window

class CMyToolBar:public CToolBar
{
// Construction
public:
  CMyToolBar ();
  BOOL Create (CWnd * pParentWnd, DWORD dwStyle, UINT nID);
// Attributes
public:

// Operations
public:

// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CMyToolBar)
  //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~ CMyToolBar ();

  // Generated message map functions
protected:
  //{{AFX_MSG(CMyToolBar)
    afx_msg void OnWindowPosChanging (LPWINDOWPOS lpWndPos);
  //}}AFX_MSG

    DECLARE_MESSAGE_MAP ()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTOOLBAR_H__E9316062_5376_11D1_9DBD_0000B4724F50__INCLUDED_)
