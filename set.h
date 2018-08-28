// Set.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSet

class CSet:public CPropertySheet
{
  DECLARE_DYNAMIC (CSet)
// Construction
public:
  CSet (UINT nIDCaption, CWnd * pParentWnd = NULL, UINT iSelectPage = 0);
  CSet (LPCTSTR pszCaption, CWnd * pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
  CDecoder m_dec;
  CEncoder m_enc;
  CHardware m_hw;
  CStatistic m_st;
  DWORD m_type;
  int m_activepage;

// Operations
public:

// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CSet)
public:
    virtual int DoModal ();
  virtual BOOL DestroyWindow ();
  //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~ CSet ();

  // Generated message map functions
protected:
  //{{AFX_MSG(CSet)
  // NOTE - the ClassWizard will add and remove member functions here.
  //}}AFX_MSG
    DECLARE_MESSAGE_MAP ()
};

/////////////////////////////////////////////////////////////////////////////
