// Statistic.cpp : implementation file
//

#include "stdafx.h"
#include "pex32.h"
#include "Encoder.h"
#include "Decoder.h"
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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CPex32Doc *pPex32Doc;
/////////////////////////////////////////////////////////////////////////////
// CStatistic property page

IMPLEMENT_DYNCREATE (CStatistic, CPropertyPage) CStatistic::CStatistic ():CPropertyPage (CStatistic::
	       IDD)
{
  //{{AFX_DATA_INIT(CStatistic)
  m_rxbuferr = _T ("");
  m_msgerr = _T ("");
  m_msgnum = _T ("");
  m_decrate = _T ("");
  //}}AFX_DATA_INIT
}

CStatistic::~CStatistic ()
{
}

void
CStatistic::DoDataExchange (CDataExchange * pDX)
{
  CPropertyPage::DoDataExchange (pDX);
  //{{AFX_DATA_MAP(CStatistic)
  DDX_Text (pDX, IDC_EXBUFERR, m_rxbuferr);
  DDX_Text (pDX, IDC_MSGERR, m_msgerr);
  DDX_Text (pDX, IDC_MSGNUM, m_msgnum);
  DDX_Text (pDX, IDC_DECRATE, m_decrate);
  //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP (CStatistic, CPropertyPage)
  //{{AFX_MSG_MAP(CStatistic)
  //}}AFX_MSG_MAP
  END_MESSAGE_MAP ()
/////////////////////////////////////////////////////////////////////////////
// CStatistic message handlers
     BOOL CStatistic::OnNotify (WPARAM wParam, LPARAM lParam,
				LRESULT * pResult)
{
  TRACE ("OnNotify\n");
  m_rxbuferr.Format ("%d", pPex32Doc->m_buferr);
  m_msgnum.Format ("%d", pPex32Doc->m_msgrx);
  m_msgerr.Format ("%d", pPex32Doc->m_msgerr);
  if (pPex32Doc->m_msgrx)
    m_decrate.Format ("%d%%",
		      100 - (pPex32Doc->m_msgerr * 100 / pPex32Doc->m_msgrx));

  return CPropertyPage::OnNotify (wParam, lParam, pResult);
}
