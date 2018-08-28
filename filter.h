#ifndef AFX_FILTER_H__8AAC3310_C979_11D1_8DC1_00A0C96F8AEE__INCLUDED_
#define AFX_FILTER_H__8AAC3310_C979_11D1_8DC1_00A0C96F8AEE__INCLUDED_

// Filter.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CFilter 

class CFilter:public CPropertyPage
{
  DECLARE_DYNCREATE (CFilter)
// Konstruktion
public:
  CFilter ();
  ~CFilter ();

// Dialogfelddaten
  //{{AFX_DATA(CFilter)
  enum
  { IDD = IDD_FILTER };
  CString m_filter;
  int m_filterfct;
  CString m_programname;
  BOOL m_startprg;
  BOOL m_totop;
  //}}AFX_DATA


// Überschreibungen
  // Der Klassen-Assistent generiert virtuelle Funktionsüberschreibungen
  //{{AFX_VIRTUAL(CFilter)
protected:
    virtual void DoDataExchange (CDataExchange * pDX);	// DDX/DDV-Unterstützung
  virtual BOOL OnCommand (WPARAM wParam, LPARAM lParam);
  //}}AFX_VIRTUAL

// Implementierung
protected:
  // Generierte Nachrichtenzuordnungsfunktionen
  //{{AFX_MSG(CFilter)
    afx_msg void OnChooseprogram ();
  afx_msg void OnLoadFilter ();
  afx_msg void OnSaveFilter ();
  //}}AFX_MSG
    DECLARE_MESSAGE_MAP ()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_FILTER_H__8AAC3310_C979_11D1_8DC1_00A0C96F8AEE__INCLUDED_
