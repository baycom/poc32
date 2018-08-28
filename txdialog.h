// TxDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTxDialog dialog

class CTxDialog:public CDialog
{
// Construction
public:
  CTxDialog (CWnd * pParent = NULL);	// standard constructor

// Dialog Data
  //{{AFX_DATA(CTxDialog)
  enum
  { IDD = IDD_TX };
  int m_encode;
  int m_fct;
  CString m_msg;
  int m_bitrate;
  UINT m_adr;
  //}}AFX_DATA


// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CTxDialog)
protected:
    virtual void DoDataExchange (CDataExchange * pDX);	// DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  // Generated message map functions
  //{{AFX_MSG(CTxDialog)
  // NOTE: the ClassWizard will add member functions here
  //}}AFX_MSG
    DECLARE_MESSAGE_MAP ()
};
