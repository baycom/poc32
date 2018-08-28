// Decoder.cpp : implementation file
//

#include "stdafx.h"
#include "pex32.h"
#include "Decoder.h"
#include "Encoder.h"
#include "Hardware.h"
#include "Statistic.h"
#include "Set.h"
#include "Filter.h"
#include "ListManager.h"
#include "Options.h"
#include "SetGeneral.h"
#include "MyStatusBar.h"
#include "MainFrm.h"
#include "Listen.h"
#include "aliases.h"
#include "MyMessageBox.h"
#include "Pex32Doc.h"
//#include "Pex32View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDecoder property page
extern CPex32Doc *pPex32Doc;

IMPLEMENT_DYNCREATE (CDecoder, CPropertyPage) CDecoder::CDecoder ():CPropertyPage (CDecoder::
	       IDD)
{
  //{{AFX_DATA_INIT(CDecoder)
  m_bitrate = -1;
  m_skyper = FALSE;
  //}}AFX_DATA_INIT
}

CDecoder::~CDecoder ()
{
}

void
CDecoder::DoDataExchange (CDataExchange * pDX)
{
  CPropertyPage::DoDataExchange (pDX);
  DDX_CBIndex (pDX, IDC_FCT0, m_fct[0]);
  DDX_CBIndex (pDX, IDC_FCT1, m_fct[1]);
  DDX_CBIndex (pDX, IDC_FCT2, m_fct[2]);
  DDX_CBIndex (pDX, IDC_FCT3, m_fct[3]);
  //{{AFX_DATA_MAP(CDecoder)
  DDX_Control (pDX, IDC_CHARSET, m_chartbl);
  DDX_CBIndex (pDX, IDC_COMBO_BITRATE, m_bitrate);
  DDX_Check (pDX, IDC_SKYPER, m_skyper);
  //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP (CDecoder, CPropertyPage)
  //{{AFX_MSG_MAP(CDecoder)
  ON_BN_CLICKED (IDC_CHARSET, OnCharset)
  //}}AFX_MSG_MAP
  END_MESSAGE_MAP ()
/////////////////////////////////////////////////////////////////////////////
// CDecoder message handlers
     BOOL CDecoder::OnApply ()
{
  ::SendMessage (AfxGetApp ()->m_pMainWnd->m_hWnd, WM_COMMAND, WM_SETPREFS,
		 0);
  return CPropertyPage::OnApply ();
}

BOOL CDecoder::OnCommand (WPARAM wParam, LPARAM lParam)
{
  SetModified (TRUE);
  return CPropertyPage::OnCommand (wParam, lParam);
}

void
CDecoder::OnCharset ()
{
  char fname[FILENAME_MAX], *t;

  strcpy (fname, pPex32Doc->m_tblname);

  if ((t = strchr (fname, '.')) != NULL)
    t[0] = 0;

  CString s;
  s.LoadString (IDS_TBLFILE);

  //CFileDialog fd( TRUE, "tbl",fname,OFN_HIDEREADONLY,s);
  CFileDialog fd (TRUE, "tbl", "*.tbl", OFN_HIDEREADONLY, s);

  if (fd.DoModal () == IDOK)
    if (!pPex32Doc->LoadTransTbl (fd.GetPathName ())) {
      CString s, t;
      s.LoadString (IDS_NOFILE);
      t.Format (s, pPex32Doc->m_tblname);
      AfxMessageBox (t);
    }
    else {
      char fname[FILENAME_MAX];
      pPex32Doc->m_tblname = fd.GetPathName ();
      _splitpath (pPex32Doc->m_tblname, NULL, NULL, fname, NULL);
      m_chartbl.SetWindowText (fname);
    }
}

BOOL CDecoder::OnInitDialog ()
{
  CPropertyPage::OnInitDialog ();
  char
    fname[FILENAME_MAX];

  _splitpath (pPex32Doc->m_tblname, NULL, NULL, fname, NULL);

  m_chartbl.SetWindowText (fname);

  return TRUE;			// return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}
