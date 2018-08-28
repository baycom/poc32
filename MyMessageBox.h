#if !defined(AFX_MYMESSAGEBOX_H__BF21EB60_CBBA_11D1_B577_0000CB280102__INCLUDED_)
#define AFX_MYMESSAGEBOX_H__BF21EB60_CBBA_11D1_B577_0000CB280102__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MyMessageBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyMessageBox dialog

class CMyMessageBox:public CDialog
{
// Construction
public:
  void MessageBox (CString str);
  void MessageBox (int UIDC);
    CMyMessageBox (CWnd * pParent = NULL);	// standard constructor
  int m_timeout;
// Dialog Data
  //{{AFX_DATA(CMyMessageBox)
  enum
  { IDD = IDD_MYMESSAGEBOX };
  CButton m_button;
  CString m_text;
  //}}AFX_DATA


// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CMyMessageBox)
protected:
    virtual void DoDataExchange (CDataExchange * pDX);	// DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:
    time_t m_startup;
  // Generated message map functions
  //{{AFX_MSG(CMyMessageBox)
  virtual BOOL OnInitDialog ();
  afx_msg void OnTimer (UINT nIDEvent);
  afx_msg void OnClose ();
  //}}AFX_MSG
    DECLARE_MESSAGE_MAP ()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYMESSAGEBOX_H__BF21EB60_CBBA_11D1_B577_0000CB280102__INCLUDED_)
