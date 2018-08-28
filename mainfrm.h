// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////
#include "persist.h"
#include "MyToolbar.h"

class CMainFrame:public CPersistentFrame
{
protected:			// create from serialization only
  CMainFrame ();
  DECLARE_DYNCREATE (CMainFrame)
  BOOL CreateLevelBar (void);
  //CMenu* m_sysmenu;

  /*
     BOOL TrayMessage(DWORD dwMessage, UINT CallBackMsg, UINT uID, HICON hIcon, PSTR pszTip);
     void NotifyDelete(UINT uIndex);
     void NotifyAdd(UINT uIndex, UINT CallBackMsg, LPSTR szTip);
   */

// Attributes
public:
    BOOL m_levelvis;
// Operations
public:

// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CMainFrame)
public:
    virtual BOOL PreCreateWindow (CREATESTRUCT & cs);
  //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~ CMainFrame ();
#ifdef _DEBUG
  virtual void AssertValid () const;
  virtual void Dump (CDumpContext & dc) const;
#endif

public:			// control bar embedded members
    CMyStatusBar m_wndStatusBar;
  CToolBar m_wndToolBar, m_LevelBar;
  CProgressCtrl m_LevelProg1, m_LevelProg2;
// Generated message map functions
protected:
  //{{AFX_MSG(CMainFrame)
    afx_msg int OnCreate (LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnLevelView ();
  afx_msg void OnUpdateLevelView (CCmdUI * pCmdUI);
  afx_msg void OnViewToolbar ();
  afx_msg void OnUpdateViewToolbar (CCmdUI * pCmdUI);
  //}}AFX_MSG
    DECLARE_MESSAGE_MAP ()
};

/////////////////////////////////////////////////////////////////////////////
