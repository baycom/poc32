// Statistic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStatistic dialog

class CStatistic:public CPropertyPage
{
  DECLARE_DYNCREATE (CStatistic)
// Construction
public:
  CStatistic ();
  ~CStatistic ();

// Dialog Data
  //{{AFX_DATA(CStatistic)
  enum
  { IDD = IDD_STATISTIC };
  CString m_rxbuferr;
  CString m_msgerr;
  CString m_msgnum;
  CString m_decrate;
  //}}AFX_DATA


// Overrides
  // ClassWizard generate virtual function overrides
  //{{AFX_VIRTUAL(CStatistic)
protected:
    virtual void DoDataExchange (CDataExchange * pDX);	// DDX/DDV support
  virtual BOOL OnNotify (WPARAM wParam, LPARAM lParam, LRESULT * pResult);
  //}}AFX_VIRTUAL

// Implementation
protected:
  // Generated message map functions
  //{{AFX_MSG(CStatistic)
  //}}AFX_MSG
    DECLARE_MESSAGE_MAP ()

};
