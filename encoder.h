// Encoder.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEncoder dialog

class CEncoder:public CPropertyPage
{
  DECLARE_DYNCREATE (CEncoder)
// Construction
public:
  CEncoder ();
  ~CEncoder ();

// Dialog Data
  //{{AFX_DATA(CEncoder)
  enum
  { IDD = IDD_ENCODER };
  UINT m_txdelay;
  BOOL m_pttinv;
  BOOL m_txinv;
  //}}AFX_DATA


// Overrides
  // ClassWizard generate virtual function overrides
  //{{AFX_VIRTUAL(CEncoder)
protected:
    virtual void DoDataExchange (CDataExchange * pDX);	// DDX/DDV support
  virtual BOOL OnCommand (WPARAM wParam, LPARAM lParam);
  //}}AFX_VIRTUAL

// Implementation
protected:
  // Generated message map functions
  //{{AFX_MSG(CEncoder)
  // NOTE: the ClassWizard will add member functions here
  //}}AFX_MSG
    DECLARE_MESSAGE_MAP ()

};
