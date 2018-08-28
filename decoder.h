// Decoder.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDecoder dialog

class CDecoder:public CPropertyPage
{
  DECLARE_DYNCREATE (CDecoder)
// Construction
public:
  CDecoder ();
  ~CDecoder ();

// Dialog Data
  int m_fct[4];
  //{{AFX_DATA(CDecoder)
  enum
  { IDD = IDD_DECODER };
  CButton m_chartbl;
  int m_bitrate;
  BOOL m_skyper;
  //}}AFX_DATA


// Overrides
  // ClassWizard generate virtual function overrides
  //{{AFX_VIRTUAL(CDecoder)
public:
    virtual BOOL OnApply ();
protected:
    virtual void DoDataExchange (CDataExchange * pDX);	// DDX/DDV support
  virtual BOOL OnCommand (WPARAM wParam, LPARAM lParam);
  //}}AFX_VIRTUAL

// Implementation
protected:
  // Generated message map functions
  //{{AFX_MSG(CDecoder)
    afx_msg void OnCharset ();
  virtual BOOL OnInitDialog ();
  //}}AFX_MSG
    DECLARE_MESSAGE_MAP ()

};
