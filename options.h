#ifndef AFX_OPTIONS_H__8AAC3311_C979_11D1_8DC1_00A0C96F8AEE__INCLUDED_
#define AFX_OPTIONS_H__8AAC3311_C979_11D1_8DC1_00A0C96F8AEE__INCLUDED_

// Options.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld COptions 

class COptions:public CPropertyPage
{
  DECLARE_DYNCREATE (COptions)
// Konstruktion
public:
  COptions ();
  ~COptions ();

// Dialogfelddaten
  //{{AFX_DATA(COptions)
  enum
  { IDD = IDD_GENERAL };
  CSpinButtonCtrl m_spi1;
  BOOL m_jumptolistend;
  int m_eliminatecalls;
  int m_eliminatecalls_timespan;
  BOOL m_enabletcpip;
  CString m_password;
  int m_tcpipport;
  //}}AFX_DATA


// Überschreibungen
  // Der Klassen-Assistent generiert virtuelle Funktionsüberschreibungen
  //{{AFX_VIRTUAL(COptions)
protected:
    virtual void DoDataExchange (CDataExchange * pDX);	// DDX/DDV-Unterstützung
  virtual BOOL OnCommand (WPARAM wParam, LPARAM lParam);
  //}}AFX_VIRTUAL

// Implementierung
protected:
  // Generierte Nachrichtenzuordnungsfunktionen
  //{{AFX_MSG(COptions)
  // HINWEIS: Der Klassen-Assistent fügt hier Member-Funktionen ein
  //}}AFX_MSG
    DECLARE_MESSAGE_MAP ()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_OPTIONS_H__8AAC3311_C979_11D1_8DC1_00A0C96F8AEE__INCLUDED_
