#ifndef AFX_SETGENERAL_H__8AAC3314_C979_11D1_8DC1_00A0C96F8AEE__INCLUDED_
#define AFX_SETGENERAL_H__8AAC3314_C979_11D1_8DC1_00A0C96F8AEE__INCLUDED_

// SetGeneral.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// CSetGeneral

class CSetGeneral:public CPropertySheet
{
  DECLARE_DYNAMIC (CSetGeneral)
// Konstruktion
public:
  CSetGeneral (UINT nIDCaption, CWnd * pParentWnd = NULL, UINT iSelectPage =
	       0);
  CSetGeneral (LPCTSTR pszCaption, CWnd * pParentWnd =
	       NULL, UINT iSelectPage = 0);

// Attribute
public:

  CListManager m_lmn;
  CFilter m_flt;
  COptions m_opt;
  int m_activepage;

// Operationen
public:

// Überschreibungen
  // Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
  //{{AFX_VIRTUAL(CSetGeneral)
public:
    virtual int DoModal ();
  virtual BOOL DestroyWindow ();
  //}}AFX_VIRTUAL

// Implementierung
public:
    virtual ~ CSetGeneral ();

  // Generierte Nachrichtenzuordnungsfunktionen
protected:
  //{{AFX_MSG(CSetGeneral)
  // HINWEIS - Der Klassen-Assistent fügt hier Member-Funktionen ein und entfernt diese.
  //}}AFX_MSG
    DECLARE_MESSAGE_MAP ()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_SETGENERAL_H__8AAC3314_C979_11D1_8DC1_00A0C96F8AEE__INCLUDED_
