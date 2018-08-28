// Hardware.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHardware dialog

class CHardware:public CPropertyPage
{
  DECLARE_DYNCREATE (CHardware)
// Construction
public:
  CHardware ();
  ~CHardware ();

// Dialog Data
  //{{AFX_DATA(CHardware)
  enum
  { IDD = IDD_HARDWARE };
  CButton m_sndcrdctrl;
  CButton m_usecomctrl;
  CComboBox m_soundcard;
  int m_int;
  int m_port;
  CString m_syncstr;
  int m_cardnum;
  BOOL m_usesndcrd;
  BOOL m_usecom;
  int m_rxline;
  BOOL m_debug;
  BOOL m_errcor;
  BOOL m_firflt;
  int m_channels;
  //}}AFX_DATA
  CString m_sndstr[8];
  DWORD m_syncword;
// Overrides
  // ClassWizard generate virtual function overrides
  //{{AFX_VIRTUAL(CHardware)
public:
    virtual void OnOK ();
protected:
    virtual void DoDataExchange (CDataExchange * pDX);	// DDX/DDV support
  virtual BOOL OnCommand (WPARAM wParam, LPARAM lParam);
  virtual BOOL OnNotify (WPARAM wParam, LPARAM lParam, LRESULT * pResult);
  //}}AFX_VIRTUAL

// Implementation
protected:
  // Generated message map functions
  //{{AFX_MSG(CHardware)
    virtual BOOL OnInitDialog ();
  //}}AFX_MSG
    DECLARE_MESSAGE_MAP ()

};
