class CPersistentFrame:public CFrameWnd
{				// remembers where it was on the desktop
  DECLARE_DYNAMIC (CPersistentFrame)
public:
  void NotifyDelete (UINT uIndex);
  void NotifyAdd (UINT uIndex, UINT CallBackMsg, LPSTR szTip);
  void NotifyModify (UINT uIndex, char *s);

  BOOL m_bAutoHide;
  void HideWindow ();
private:
  static const CRect s_rectDefault;
  static const char s_profileHeading[];
  static const char s_profileRect[];
  static const char s_profileIcon[];
  static const char s_profileMax[];
  static const char s_AutoHide[];
//    static const char s_profileTool[];
//    static const char s_profileStatus[];

  BOOL m_bFirstTime;
  BOOL m_hidden;

protected:			// create from serialization only
    CPersistentFrame ();
   ~CPersistentFrame ();

  BOOL TrayMessage (DWORD dwMessage, UINT CallBackMsg, UINT uID, HICON hIcon,
		    PSTR pszTip);
  BOOL m_topmost;

  //{{AFX_VIRTUAL(CPersistentFrame)
public:
    virtual void ActivateFrame (int nCmdShow = -1);
  //}}AFX_VIRTUAL

  //{{AFX_MSG(CPersistentFrame)
  afx_msg void OnDestroy ();
  afx_msg void OnTop (void);
  afx_msg void OnHide ();
  afx_msg void OnUpdateHide (CCmdUI * pCmdUI);
  afx_msg void OnSize (UINT nType, int cx, int cy);
  afx_msg void OnClose ();
  afx_msg void OnAot ();
  afx_msg void OnUpdateAot (CCmdUI * pCmdUI);
  //}}AFX_MSG
  afx_msg LRESULT OnTop (WPARAM wParam, LPARAM lParam);

    DECLARE_MESSAGE_MAP ()
};
