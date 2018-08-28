// Filter.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "pex32.h"
#include "Filter.h"
#include "io.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Eigenschaftenseite CFilter 

IMPLEMENT_DYNCREATE (CFilter, CPropertyPage) CFilter::CFilter ():CPropertyPage (CFilter::
	       IDD)
{
  //{{AFX_DATA_INIT(CFilter)
  m_filter = _T ("");
  m_filterfct = -1;
  m_programname = _T ("");
  m_startprg = FALSE;
  m_totop = FALSE;
  //}}AFX_DATA_INIT
}

CFilter::~CFilter ()
{
}

void
CFilter::DoDataExchange (CDataExchange * pDX)
{
  CPropertyPage::DoDataExchange (pDX);
  //{{AFX_DATA_MAP(CFilter)
  DDX_Text (pDX, IDC_FILTER, m_filter);
  DDX_CBIndex (pDX, IDC_FILTERFCT, m_filterfct);
  DDX_Text (pDX, IDC_PROGRAMNAME, m_programname);
  DDX_Check (pDX, IDC_STARTPRG, m_startprg);
  DDX_Check (pDX, IDC_TOTOP, m_totop);
  //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP (CFilter, CPropertyPage)
  //{{AFX_MSG_MAP(CFilter)
  ON_BN_CLICKED (IDC_CHOOSEPROGRAM, OnChooseprogram)
  ON_BN_CLICKED (ID_LOADFILTER, OnLoadFilter)
  ON_BN_CLICKED (ID_SAVEFILTER, OnSaveFilter)
  //}}AFX_MSG_MAP
  END_MESSAGE_MAP ()
/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CFilter 
     afx_msg void CFilter::OnLoadFilter ()
{
  CFileDialog fd (TRUE, "txt", "*.txt", OFN_HIDEREADONLY, "Filter (*.txt)");
  if (fd.DoModal () == IDOK) {
    FILE *f = fopen (fd.GetPathName (), "rb");
    if (f) {
      int len = _filelength (_fileno (f));
      m_filter.Empty ();
      fread (m_filter.GetBuffer (len), len, 1, f);
      fclose (f);
      m_filter.ReleaseBuffer ();
      UpdateData (FALSE);
    }
  }

}

afx_msg void
CFilter::OnSaveFilter ()
{
  CFileDialog fd (FALSE, "txt", "*.txt",
		  OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "Filter (*.txt)");
  if (fd.DoModal () == IDOK) {
    FILE *f = fopen (fd.GetPathName (), "wt");
    UpdateData (TRUE);
    if (f) {
      fwrite (m_filter, m_filter.GetLength (), 1, f);
      fclose (f);
    }
  }
}
void
CFilter::OnChooseprogram ()
{
  CFileDialog fd (TRUE, "", "", OFN_HIDEREADONLY, "");
  if (fd.DoModal () == IDOK) {
    m_programname = fd.GetPathName ();
    UpdateData (FALSE);
  }
}


BOOL CFilter::OnCommand (WPARAM wParam, LPARAM lParam)
{
  SetModified (TRUE);
  return CPropertyPage::OnCommand (wParam, lParam);
}
