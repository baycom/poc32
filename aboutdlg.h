/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg:public CDialog
{
public:
  CAboutDlg ();

// Dialog Data
  //{{AFX_DATA(CAboutDlg)
  enum
  { IDD = IDD_ABOUTBOX };
  CString m_version;
  CString m_registered;
  //}}AFX_DATA

  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CAboutDlg)
protected:
    virtual void DoDataExchange (CDataExchange * pDX);	// DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:
  //{{AFX_MSG(CAboutDlg)
    virtual BOOL OnInitDialog ();
  //}}AFX_MSG
    DECLARE_MESSAGE_MAP ()
public:
    afx_msg void OnBnClickedLicense ();
};
