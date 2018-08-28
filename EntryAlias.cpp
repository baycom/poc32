// EntryAlias.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "pex32.h"
#include "aliases.h"
#include "EntryAlias.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CEntryAlias 


CEntryAlias::CEntryAlias (CWnd * pParent /*=NULL*/ )
:CDialog (CEntryAlias::IDD, pParent)
{
  //{{AFX_DATA_INIT(CEntryAlias)
  //}}AFX_DATA_INIT
}


void
CEntryAlias::DoDataExchange (CDataExchange * pDX)
{
  CDialog::DoDataExchange (pDX);
  //{{AFX_DATA_MAP(CEntryAlias)
  //}}AFX_DATA_MAP
  DDX_Text (pDX, IDC_ADDRESS, m_a.m_adr);
  DDX_Text (pDX, IDC_ALIAS, m_a.m_alias);
  DDV_MaxChars (pDX, m_a.m_alias, 32);
  DDX_Text (pDX, IDC_PROGRAMNAME2, m_a.m_programname);

}


BEGIN_MESSAGE_MAP (CEntryAlias, CDialog)
  //{{AFX_MSG_MAP(CEntryAlias)
  ON_BN_CLICKED (ID_DELETE, OnDelete) ON_BN_CLICKED (ID_CHOOSE, OnChoose)
  //}}AFX_MSG_MAP
  END_MESSAGE_MAP ()
/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CEntryAlias 
     void CEntryAlias::OnDelete ()
{
  EndDialog (_DELETE_ENTRY);
}

void
CEntryAlias::OnChoose ()
{
  CFileDialog fd (TRUE, "", "", OFN_HIDEREADONLY, "");
  if (fd.DoModal () == IDOK) {
    m_a.m_programname = fd.GetPathName ();
    UpdateData (FALSE);
  }
}
