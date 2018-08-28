// pex32View.h : interface of the CPex32View class
//
/////////////////////////////////////////////////////////////////////////////

class CPex32View:public CListView
{
  enum
  { LINESPERPAGE = 52, LEFTBORDER = 100 };
protected:			// create from serialization only
    CPex32View ();
    DECLARE_DYNCREATE (CPex32View)
  CListCtrl *m_pList;
  CImageList m_imageList;
  CFindReplaceDialog *m_fdlg;
  CString m_findstr;
  CMsgList *m_msg;
  CMyMessageBox *m_mmb;

  int m_SortItem;
  int m_SortDir;
  int m_LastItem;
  int m_start;
  int m_nPage;
  int m_maxcols;

  BOOL m_stopped;
  CPex32Doc *m_pDoc;

// Attributes
public:
    CPex32Doc * GetDocument ();
// Operations
public:

// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CPex32View)
public:
    virtual void OnDraw (CDC * pDC);	// overridden to draw this view
  virtual BOOL PreCreateWindow (CREATESTRUCT & cs);
protected:
    virtual void OnInitialUpdate ();	// called first time after construct
  virtual BOOL OnPreparePrinting (CPrintInfo * pInfo);
  virtual void OnUpdate (CView * pSender, LPARAM lHint, CObject * pHint);
  virtual void OnPrint (CDC * pDC, CPrintInfo * pInfo);
  //}}AFX_VIRTUAL
// Implementation
public:
    virtual ~ CPex32View ();
#ifdef _DEBUG
  virtual void AssertValid () const;
  virtual void Dump (CDumpContext & dc) const;
#endif

protected:
  void PrintPageHeader (CDC * pDC);
  void PrintPageFooter (CDC * pDC);
  void set_type (void);
  int get_dec_state (void);
  int match_wildcard (CString str1, CString str2);
  void datetimestr (LPTSTR Buf, int BufSize, time_t & unixtime);

// Generated message map functions
protected:
  //{{AFX_MSG(CPex32View)
    afx_msg void OnSettings ();
  afx_msg void OnUpdateDcd (CCmdUI * pCmdUI);
  afx_msg void OnColumnclick (NMHDR * pNMHDR, LRESULT * pResult);
  afx_msg void OnTx ();
  afx_msg void OnUpdateTx (CCmdUI * pCmdUI);
  afx_msg void OnQuix ();
  afx_msg void OnTelmi ();
  afx_msg void OnTmobil ();
  afx_msg void OnUpdateQuix (CCmdUI * pCmdUI);
  afx_msg void OnUpdateTelmi (CCmdUI * pCmdUI);
  afx_msg void OnUpdateTmobil (CCmdUI * pCmdUI);
  afx_msg void On1200 ();
  afx_msg void OnUpdate1200 (CCmdUI * pCmdUI);
  afx_msg void On2400 ();
  afx_msg void OnUpdate2400 (CCmdUI * pCmdUI);
  afx_msg void On512 ();
  afx_msg void OnUpdate512 (CCmdUI * pCmdUI);
  afx_msg void OnFind ();
  afx_msg void OnEditCopy ();
  afx_msg void OnAutobaud ();
  afx_msg void OnUpdateAutobaud (CCmdUI * pCmdUI);
  afx_msg void OnUpdate (void);
  afx_msg void OnAutomsg ();
  afx_msg void OnUpdateAutomsg (CCmdUI * pCmdUI);
  afx_msg void OnStop ();
  afx_msg void OnUpdateStop (CCmdUI * pCmdUI);
  afx_msg void OnContextMenu (CWnd * pWnd, CPoint point);
  afx_msg void OnChoosefont ();
  afx_msg void OnGowww ();
  afx_msg void OnFeedback ();
  afx_msg void OnAppAbout ();
  afx_msg void OnLicense ();
  afx_msg void SetPrefs (void);
  afx_msg void OnUpdateLevel0 (CCmdUI * pCmdUI);
  afx_msg void OnUpdateLevel1 (CCmdUI * pCmdUI);
  afx_msg void OnTimer (UINT nIDEvent);
  afx_msg LONG OnNewWavData (UINT wParam, LONG lParam);
  afx_msg void OnDestroy ();
  afx_msg void OnDblclk (NMHDR * pNMHDR, LRESULT * pResult);
  afx_msg void OnOptionsProperties ();
  afx_msg void OnKeyDown (UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg void OnEntryProperties ();
  afx_msg void OnRegister ();
  afx_msg void OnSponsor ();
  afx_msg void OnDeleteEntry ();
  afx_msg void OnUpdateall ();
  //}}AFX_MSG
  afx_msg LRESULT OnFindReplace (WPARAM wParam, LPARAM lParam);
    DECLARE_MESSAGE_MAP ()
};
static UINT NEAR WM_FINDREPLACE = RegisterWindowMessage (FINDMSGSTRING);
#ifndef _DEBUG			// debug version in pex32View.cpp
inline CPex32Doc *
CPex32View::GetDocument ()
{
  return (CPex32Doc *) m_pDocument;
}
#endif

/////////////////////////////////////////////////////////////////////////////
