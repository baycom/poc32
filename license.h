// License.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLicense dialog

class CLicense:public CDialog
{
// Construction
public:
  CLicense (CWnd * pParent = NULL);	// standard constructor

// Dialog Data
  //{{AFX_DATA(CLicense)
  enum
  { IDD = IDD_LICENSE };
  CString m_licstr;
  //}}AFX_DATA


// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CLicense)
protected:
    virtual void DoDataExchange (CDataExchange * pDX);	// DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  // Generated message map functions
  //{{AFX_MSG(CLicense)
  // NOTE: the ClassWizard will add member functions here
  //}}AFX_MSG
    DECLARE_MESSAGE_MAP ()
};
