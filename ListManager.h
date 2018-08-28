#ifndef AFX_LISTMANAGER_H__03697BF3_C962_11D1_8DC1_00A0C96F8AEE__INCLUDED_
#define AFX_LISTMANAGER_H__03697BF3_C962_11D1_8DC1_00A0C96F8AEE__INCLUDED_

// ListManager.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CListManager 

class CListManager:public CPropertyPage
{
  DECLARE_DYNCREATE (CListManager)
// Konstruktion
public:
  CListManager ();
  ~CListManager ();

// Dialogfelddaten
  //{{AFX_DATA(CListManager)
  enum
  { IDD = IDD_LISTMANAGER };
  CSpinButtonCtrl m_spin3;
  CSpinButtonCtrl m_spin2;
  CSpinButtonCtrl m_spin1;
  BOOL m_autosave;
  int m_autosavenum;
  BOOL m_cutinternalist;
  BOOL m_cutvislist;
  int m_cutvislistnum;
  BOOL m_autoload;
  int m_cutinternalistnum;
  //}}AFX_DATA


// Überschreibungen
  // Der Klassen-Assistent generiert virtuelle Funktionsüberschreibungen
  //{{AFX_VIRTUAL(CListManager)
public:
    virtual BOOL OnApply ();
protected:
    virtual void DoDataExchange (CDataExchange * pDX);	// DDX/DDV-Unterstützung
  virtual BOOL OnCommand (WPARAM wParam, LPARAM lParam);
  //}}AFX_VIRTUAL

// Implementierung
protected:
  // Generierte Nachrichtenzuordnungsfunktionen
  //{{AFX_MSG(CListManager)
    virtual BOOL OnInitDialog ();
  //}}AFX_MSG
    DECLARE_MESSAGE_MAP ()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_LISTMANAGER_H__03697BF3_C962_11D1_8DC1_00A0C96F8AEE__INCLUDED_
