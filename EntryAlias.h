#ifndef AFX_ENTRYALIAS_H__607772E1_C988_11D1_8DC2_00A0C96F8AEE__INCLUDED_
#define AFX_ENTRYALIAS_H__607772E1_C988_11D1_8DC2_00A0C96F8AEE__INCLUDED_

// EntryAlias.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CEntryAlias 

class CEntryAlias:public CDialog
{
// Konstruktion
public:
  CEntryAlias (CWnd * pParent = NULL);	// Standardkonstruktor
  CAlias m_a;
// Dialogfelddaten
  //{{AFX_DATA(CEntryAlias)
  enum
  { IDD = IDD_ENTRYPROPERTIES };
  //}}AFX_DATA


// �berschreibungen
  // Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
  //{{AFX_VIRTUAL(CEntryAlias)
public:
protected:
    virtual void DoDataExchange (CDataExchange * pDX);	// DDX/DDV-Unterst�tzung
  //}}AFX_VIRTUAL

// Implementierung
protected:

  // Generierte Nachrichtenzuordnungsfunktionen
  //{{AFX_MSG(CEntryAlias)
    afx_msg void OnDelete ();
  afx_msg void OnChoose ();
  //}}AFX_MSG
    DECLARE_MESSAGE_MAP ()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio f�gt zus�tzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_ENTRYALIAS_H__607772E1_C988_11D1_8DC2_00A0C96F8AEE__INCLUDED_
