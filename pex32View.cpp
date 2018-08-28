// pex32View.cpp : implementation of the CPex32View class
//

#include "stdafx.h"
#include "pex32.h"
#include "MyStatusBar.h"
#include "MainFrm.h"
#include "Decoder.h"
#include "Encoder.h"
#include "Hardware.h"
#include "Statistic.h"
#include "Set.h"
#include "Filter.h"
#include "ListManager.h"
#include "Options.h"
#include "SetGeneral.h"
#include "Listen.h"
#include "aliases.h"
#include "MyMessageBox.h"
#include "Pex32Doc.h"
#include "Pex32View.h"
#include "AboutDlg.h"
#include "License.h"
#include "EntryAlias.h"
#include "mbgrep.h"

#include <time.h>
#include <string.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPex32View

IMPLEMENT_DYNCREATE (CPex32View, CListView)
  BEGIN_MESSAGE_MAP (CPex32View, CListView)
  //{{AFX_MSG_MAP(CPex32View)
  ON_COMMAND (ID_SETTINGS, OnSettings)
  ON_UPDATE_COMMAND_UI (ID_DCD, OnUpdateDcd)
  ON_NOTIFY_REFLECT (LVN_COLUMNCLICK, OnColumnclick)
  ON_COMMAND (ID_TX, OnTx)
  ON_UPDATE_COMMAND_UI (ID_TX, OnUpdateTx)
  ON_COMMAND (ID_QUIX, OnQuix)
  ON_COMMAND (ID_TELMI, OnTelmi)
  ON_COMMAND (ID_TMOBIL, OnTmobil)
  ON_UPDATE_COMMAND_UI (ID_QUIX, OnUpdateQuix)
  ON_UPDATE_COMMAND_UI (ID_TELMI, OnUpdateTelmi)
  ON_UPDATE_COMMAND_UI (ID_TMOBIL, OnUpdateTmobil)
  ON_COMMAND (ID_1200, On1200)
  ON_UPDATE_COMMAND_UI (ID_1200, OnUpdate1200)
  ON_COMMAND (ID_2400, On2400)
  ON_UPDATE_COMMAND_UI (ID_2400, OnUpdate2400)
  ON_COMMAND (ID_512, On512)
  ON_UPDATE_COMMAND_UI (ID_512, OnUpdate512)
  ON_COMMAND (ID_FIND, OnFind)
  ON_COMMAND (ID_EDIT_COPY, OnEditCopy)
  ON_COMMAND (ID_AUTOBAUD, OnAutobaud)
  ON_UPDATE_COMMAND_UI (ID_AUTOBAUD, OnUpdateAutobaud)
  ON_COMMAND (WM_UPDATE, OnUpdate)
  ON_COMMAND (ID_AUTOMSG, OnAutomsg)
  ON_UPDATE_COMMAND_UI (ID_AUTOMSG, OnUpdateAutomsg)
  ON_COMMAND (ID_STOP, OnStop)
  ON_UPDATE_COMMAND_UI (ID_STOP, OnUpdateStop)
  ON_WM_CONTEXTMENU ()ON_COMMAND (ID_CHOOSEFONT, OnChoosefont)
  ON_COMMAND (ID_GOWWW, OnGowww)
  ON_COMMAND (ID_FEEDBACK, OnFeedback)
  ON_COMMAND (ID_APP_ABOUT, OnAppAbout)
  ON_COMMAND (ID_LICENSE, OnLicense)
  ON_COMMAND (WM_SETPREFS, SetPrefs)
  ON_UPDATE_COMMAND_UI (ID_LEVEL0, OnUpdateLevel0)
  ON_UPDATE_COMMAND_UI (ID_LEVEL1, OnUpdateLevel1)
  ON_WM_TIMER ()ON_MESSAGE (MM_WIM_DATA, OnNewWavData)
  ON_WM_DESTROY ()ON_NOTIFY_REFLECT (NM_DBLCLK, OnDblclk)
  ON_COMMAND (ID_OPTIONS_PROPERTIES, OnOptionsProperties)
  ON_WM_KEYDOWN ()ON_COMMAND (ID_ENTRYPROPERTIES, OnEntryProperties)
  ON_COMMAND (ID_REGISTER, OnRegister)
  ON_COMMAND (ID_EUROPOINT, OnSponsor)
  ON_COMMAND (ID_DELETECMD, OnDeleteEntry)
  ON_COMMAND (ID_UPDATEALL, OnUpdateall)
  //}}AFX_MSG_MAP
  // Standard printing commands
  ON_COMMAND (ID_FILE_PRINT, CListView::OnFilePrint)
  ON_COMMAND (ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
  ON_COMMAND (ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
  ON_REGISTERED_MESSAGE (WM_FINDREPLACE, OnFindReplace) END_MESSAGE_MAP ()
/////////////////////////////////////////////////////////////////////////////
// CPex32View construction/destruction
  CPex32View::CPex32View ()
{
  m_pList = NULL;
  m_SortDir = 1;
  m_LastItem = 0;
  m_stopped = FALSE;
  m_maxcols = 0;
  m_mmb = NULL;
}

CPex32View::~CPex32View ()
{
}

void
CPex32View::SetPrefs (void)
{
  m_pDoc->SetPrefs ();
}

BOOL CPex32View::PreCreateWindow (CREATESTRUCT & cs)
{
  // TODO: Modify the Window class or styles here by modifying
  //  the CREATESTRUCT cs

  return CListView::PreCreateWindow (cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPex32View drawing

void
CPex32View::OnDraw (CDC * pDC)
{
  CPex32Doc *pDoc = GetDocument ();
  ASSERT_VALID (pDoc);
}

/////////////////////////////////////////////////////////////////////////////
// CPex32View diagnostics

#ifdef _DEBUG
void
     CPex32View::AssertValid () const const const
     {
       CListView::AssertValid ();
     }

     void CPex32View::Dump (CDumpContext & dc) const const const
     {
       CListView::Dump (dc);
     }

     CPex32Doc *CPex32View::GetDocument ()	// non-debug version is inline
{
  ASSERT (m_pDocument->IsKindOf (RUNTIME_CLASS (CPex32Doc)));
  return (CPex32Doc *) m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPex32View message handlers
/* ---------------------------------------------------------------------- 
   Is called everytime the user selects File/New (or on startup)
   I'm using this to initialize the decoder functions and to setup
   some display parameters.
*/
void
CPex32View::OnInitialUpdate ()
{
  CString str;

  TRACE ("OnInitialUpdate\n");

  /* Call this only once.
   */
  if (m_pList == NULL) {
    /* Create some easy to access class pointers. Yes it's lazy and not c++ 
       like.
     */
    m_pDoc = GetDocument ();
    m_msg = &m_pDoc->m_msg;
    m_pList = &GetListCtrl ();
    m_pDoc->m_mainfrm = (CMainFrame *) AfxGetApp ()->m_pMainWnd;
    m_pDoc->GetPrefs ();
    m_pDoc->OnStartup ();
    if (m_pDoc->m_sg.m_opt.m_enabletcpip) {
      m_pDoc->StartListening ();
    }
    m_mmb = new CMyMessageBox;

    if (m_pDoc->m_sg.m_flt.m_filterfct) {
      m_mmb->MessageBox (IDS_FLTACT);
      //AfxMessageBox(IDS_FLTACT);
    }

    /* Setup ListView in reportstyle.
     */
    m_imageList.Create (16, 16, 0, 0, 5);	// 32, 32 for large icons
    m_imageList.Add (AfxGetApp ()->LoadIcon (IDR_QUIX));
    m_imageList.Add (AfxGetApp ()->LoadIcon (IDR_TMOBIL));
    m_imageList.Add (AfxGetApp ()->LoadIcon (IDR_TELMI));
    m_imageList.Add (AfxGetApp ()->LoadIcon (IDR_UNKNOWN));
    m_imageList.Add (AfxGetApp ()->LoadIcon (IDR_OWNMSG));

    m_pDoc->m_f.CreateFontIndirect (&m_pDoc->m_lf);
    SetFont (&m_pDoc->m_f, TRUE);

    m_pList->SetImageList (&m_imageList, LVSIL_SMALL);
    //str.LoadString(IDS_NUMBER);
    //m_pList->InsertColumn( m_maxcols,str,LVCFMT_RIGHT,m_pDoc->m_colwidth[m_maxcols++]);
    str.LoadString (IDS_TIME);
    m_pList->InsertColumn (m_maxcols, str, LVCFMT_LEFT,
			   m_pDoc->m_colwidth[m_maxcols++]);
    str.LoadString (IDS_SOURCE);
    m_pList->InsertColumn (m_maxcols, str, LVCFMT_LEFT,
			   m_pDoc->m_colwidth[m_maxcols++]);
    str.LoadString (IDS_TYPE);
    m_pList->InsertColumn (m_maxcols, str, LVCFMT_LEFT,
			   m_pDoc->m_colwidth[m_maxcols++]);
    str.LoadString (IDS_BITRATE);
    m_pList->InsertColumn (m_maxcols, str, LVCFMT_RIGHT,
			   m_pDoc->m_colwidth[m_maxcols++]);
    str.LoadString (IDS_ADDRESS);
    m_pList->InsertColumn (m_maxcols, str, LVCFMT_RIGHT,
			   m_pDoc->m_colwidth[m_maxcols++]);
    str.LoadString (IDS_ALIAS);
    m_pList->InsertColumn (m_maxcols, str, LVCFMT_LEFT,
			   m_pDoc->m_colwidth[m_maxcols++]);
    str.LoadString (IDS_FUNC);
    m_pList->InsertColumn (m_maxcols, str, LVCFMT_LEFT,
			   m_pDoc->m_colwidth[m_maxcols++]);
    str.LoadString (IDS_MSG);
    m_pList->InsertColumn (m_maxcols, str, LVCFMT_LEFT,
			   m_pDoc->m_colwidth[m_maxcols++]);

    m_pList->SetBkColor (RGB (128, 128, 128));
    m_pList->SetTextColor (RGB (0, 0, 0));

    SetWindowLong (m_hWnd, GWL_STYLE,
		   LVS_REPORT | GetWindowLong (m_hWnd, GWL_STYLE));
    if (firststart)
      OnSettings ();
    /* This timer handles only the COM-Port device driver polls and displays
       the audiolevel bars.
     */
    SetTimer (_MYTIMER, 100, NULL);
  }
  /* Clear ListView.
   */
  m_LastItem = 0;
  m_pList->DeleteAllItems ();
  OnUpdate (NULL, 0, NULL);
  CListView::OnInitialUpdate ();
}

/* ---------------------------------------------------------------------- 
   format decoder functionbit mapping into one byte.
*/
int
CPex32View::get_dec_state (void)
{
  return m_pDoc->m_s.m_dec.m_fct[0] | (m_pDoc->m_s.m_dec.
				       m_fct[1] << 2) | (m_pDoc->m_s.m_dec.
							 m_fct[2] << 4) |
    (m_pDoc->m_s.m_dec.m_fct[3] << 6);
}

/* ---------------------------------------------------------------------- 
   Call property page.
*/
void
CPex32View::OnSettings (void)
{
  m_pDoc->m_s.DoModal ();
}

void
CPex32View::OnOptionsProperties ()
{
  int f, g, h;
  CString s;
  s.LoadString (IDS_PROPTITLEGENERAL);
  m_pDoc->m_sg.SetTitle (s);

  s = m_pDoc->m_sg.m_flt.m_filter;
  f = m_pDoc->m_sg.m_flt.m_filterfct;
  g = m_pDoc->m_sg.m_opt.m_eliminatecalls;
  h = m_pDoc->m_sg.m_opt.m_eliminatecalls_timespan;

  if (m_pDoc->m_sg.DoModal () == IDOK)
    if ((s != m_pDoc->m_sg.m_flt.m_filter)
	|| (f != m_pDoc->m_sg.m_flt.m_filterfct)
	|| (g != m_pDoc->m_sg.m_opt.m_eliminatecalls)
	|| (h != m_pDoc->m_sg.m_opt.m_eliminatecalls_timespan)) {
      /* if filters have changed redisplay ListView.
       */
      OnUpdateall ();
    }
}

void
CPex32View::OnUpdateDcd (CCmdUI * pCmdUI)
{
  static BOOL laststate;

  BOOL dcd = m_pDoc->poc_getdcd () || m_pDoc->poc_getsnddcd ();
  pCmdUI->Enable (dcd);
/*
	if(dcd!=laststate)
	{	
		CString s;
		if(dcd)
			s.LoadString(IDS_DORX);
		else
			s.LoadString(AFX_IDS_IDLEMESSAGE);

		m_mainfrm->m_wndStatusBar.SetPaneText(0,s);
		laststate=dcd;
	}
*/
}

/* ---------------------------------------------------------------------- 
   Compare function for ListView (Windows Explorer-like)
*/
int CALLBACK
pfnCompare (LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
  CPex32View *clw = (CPex32View *) lParamSort;
  CMsgList & m_msg = clw->m_pDoc->m_msg;
  int ret = 0;

  switch (clw->m_SortItem) {
  case 0:
    if (lParam1 > lParam2)
      ret = 1;
    else if (lParam1 < lParam2)
      ret = -1;
    break;
    /*
       case 1:      if(m_msg[lParam1].m_time>m_msg[lParam2].m_time)
       ret=1;
       else
       if(m_msg[lParam1].m_time<m_msg[lParam2].m_time)
       ret=-1;
       break;
     */
  case 1:
    if ((m_msg[lParam1].m_type >> 4) > (m_msg[lParam2].m_type >> 4))
      ret = 1;
    else if ((m_msg[lParam1].m_type >> 4) < (m_msg[lParam2].m_type >> 4))
      ret = -1;
    break;
  case 2:
    if ((m_msg[lParam1].m_type & 15) > (m_msg[lParam2].m_type & 15))
      ret = 1;
    else if ((m_msg[lParam1].m_type & 15) < (m_msg[lParam2].m_type & 15))
      ret = -1;
    break;
  case 3:
    if (m_msg[lParam1].m_bitrate < m_msg[lParam2].m_bitrate)
      ret = 1;
    else if (m_msg[lParam1].m_bitrate > m_msg[lParam2].m_bitrate)
      ret = -1;
    break;
  case 4:
    if (m_msg[lParam1].m_adr > m_msg[lParam2].m_adr)
      ret = 1;
    else if (m_msg[lParam1].m_adr < m_msg[lParam2].m_adr)
      ret = -1;
    break;
  case 5:
    ret =
      _stricmp (clw->m_pDoc->m_alias.LookupAlias (m_msg[lParam1].m_adr),
		clw->m_pDoc->m_alias.LookupAlias (m_msg[lParam2].m_adr));
    break;
  case 6:
    if (m_msg[lParam1].m_fct > m_msg[lParam2].m_fct)
      ret = 1;
    else if (m_msg[lParam1].m_fct < m_msg[lParam2].m_fct)
      ret = -1;
    break;
  case 7:
    ret = _stricmp (m_msg[lParam1].m_msg, m_msg[lParam2].m_msg);
    break;
  }

  if (!clw->m_SortDir)
    ret *= -1;
  //TRACE("SortDir %d %d\n",ret,clw->m_SortDir);
  return ret;
}

/* ---------------------------------------------------------------------- 
   Sort List Items on column click (Windows Explorer-like)
*/
void
CPex32View::OnColumnclick (NMHDR * pNMHDR, LRESULT * pResult)
{
  static int OldSort;

  NM_LISTVIEW *pNMListView = (NM_LISTVIEW *) pNMHDR;
  //TRACE("Pressed  %ld %ld\n",pNMListView->iItem,pNMListView->iSubItem);
  m_SortItem = pNMListView->iSubItem;

  if (m_SortItem != OldSort) {
    m_SortDir = 1;
    OldSort = m_SortItem;
  }
  else {
    m_SortDir = 0;
    OldSort = -1;
  }

  m_pList->SortItems (pfnCompare, (LRESULT) this);
  *pResult = 0;
}

/* ---------------------------------------------------------------------- 
   Display Transmission dialog.
*/
void
CPex32View::OnTx ()
{
  if (m_pDoc->m_s.m_hw.m_usecom == FALSE)
    return;
  if (m_pList->GetSelectedCount () == 1) {
    LV_ITEM item;
    memset (&item, 0, sizeof (LV_ITEM));
    item.mask = LVIF_STATE;
    item.stateMask = LVIS_SELECTED;

    for (int i = 0; i < m_msg->GetSize (); i++) {
      item.iItem = i;
      m_pList->GetItem (&item);
      if (item.state == LVIS_SELECTED) {
	CMsgList & m_msg = m_pDoc->m_msg;
	i = m_pList->GetItemData (i);
	m_pDoc->m_txdlg.m_adr = m_msg[i].m_adr;
	m_pDoc->m_txdlg.m_bitrate = m_msg[i].m_bitrate;
	m_pDoc->m_txdlg.m_fct = m_msg[i].m_fct;
	m_pDoc->m_txdlg.m_encode = m_msg[i].m_func;
	m_pDoc->m_txdlg.m_msg = m_msg[i].m_msg;
	break;
      }
    }

  }

  if (m_pDoc->m_txdlg.DoModal () == IDOK) {
    WORD baud = m_pDoc->bitrate (m_pDoc->m_txdlg.m_bitrate);
    CMsg m;
    switch (m_pDoc->m_txdlg.m_encode) {
    case BEEP:
      m_pDoc->poc_beep (baud, m_pDoc->m_txdlg.m_adr, m_pDoc->m_txdlg.m_fct);
      break;
    case NUM:
      m_pDoc->poc_numerik (baud, m_pDoc->m_txdlg.m_adr,
			   m_pDoc->m_txdlg.m_fct, m_pDoc->m_txdlg.m_msg);
      break;
    case ALPHA:
      m_pDoc->poc_alphanum (baud, m_pDoc->m_txdlg.m_adr,
			    m_pDoc->m_txdlg.m_fct, m_pDoc->m_txdlg.m_msg);
      break;
    }
    m.m_adr = m_pDoc->m_txdlg.m_adr;
    m.m_fct = m_pDoc->m_txdlg.m_fct;
    m.m_func = m_pDoc->m_txdlg.m_encode;
    m.m_type = OWNMSG;
    m.m_bitrate = m_pDoc->m_txdlg.m_bitrate;
    m.m_msg = m_pDoc->m_txdlg.m_msg;
    m_pDoc->AddToList (m);
    OnUpdate ();
  }
}

/* ---------------------------------------------------------------------- 
   Preset functionbit mapping for german paging services.
*/
void
CPex32View::set_type (void)
{
  switch (m_pDoc->m_s.m_type) {
  case UNKNOWN:
    m_pDoc->m_s.m_dec.m_fct[0] = AUTO;
    m_pDoc->m_s.m_dec.m_fct[1] = AUTO;
    m_pDoc->m_s.m_dec.m_fct[2] = AUTO;
    m_pDoc->m_s.m_dec.m_fct[3] = AUTO;
    break;
  case TMOBIL:
    m_pDoc->m_s.m_dec.m_fct[0] = NUM;
    m_pDoc->m_s.m_dec.m_fct[1] = BEEP;
    m_pDoc->m_s.m_dec.m_fct[2] = ALPHA;
    m_pDoc->m_s.m_dec.m_fct[3] = ALPHA;
    m_pDoc->m_s.m_dec.m_skyper = TRUE;
    break;
  case QUIX:
    m_pDoc->m_s.m_dec.m_fct[0] = NUM;
    m_pDoc->m_s.m_dec.m_fct[1] = ALPHA;
    m_pDoc->m_s.m_dec.m_fct[2] = NUM;
    m_pDoc->m_s.m_dec.m_fct[3] = ALPHA;
    m_pDoc->m_s.m_dec.m_skyper = FALSE;
    break;
  case TELMI:
    m_pDoc->m_s.m_dec.m_fct[0] = ALPHA;
    m_pDoc->m_s.m_dec.m_fct[1] = NUM;
    m_pDoc->m_s.m_dec.m_fct[2] = ALPHA;
    m_pDoc->m_s.m_dec.m_fct[3] = ALPHA;
    m_pDoc->m_s.m_dec.m_skyper = FALSE;
    break;
  }
}

void
CPex32View::OnUpdateTx (CCmdUI * pCmdUI)
{
  //int state=;
  //pCmdUI->SetCheck(!state);
  pCmdUI->Enable (m_pDoc->m_s.m_hw.m_usecom);
  //m_pDoc->m_mainfrm->m_wndToolBar.GetToolBarCtrl( ).SetState(pCmdUI->m_nID,TBSTATE_PRESSED);//state && m_pDoc->m_s.m_hw.m_usecom);
  if (m_pDoc->m_s.m_hw.m_usecom)
    m_pDoc->m_mainfrm->m_wndToolBar.GetToolBarCtrl ().PressButton (pCmdUI->
								   m_nID,
								   m_pDoc->
								   poc_getstate
								   ());
}

void
CPex32View::OnAutomsg ()
{
  m_pDoc->m_s.m_type = UNKNOWN;
  set_type ();
  SetPrefs ();
}

void
CPex32View::OnQuix ()
{
  m_pDoc->m_s.m_type = QUIX;
  set_type ();
  SetPrefs ();
  TRACE ("Quix %X\n", get_dec_state ());
}

void
CPex32View::OnTelmi ()
{
  m_pDoc->m_s.m_type = TELMI;
  set_type ();
  SetPrefs ();
  TRACE ("TelMi %X\n", get_dec_state ());
}

void
CPex32View::OnTmobil ()
{
  m_pDoc->m_s.m_type = TMOBIL;
  set_type ();
  SetPrefs ();
  TRACE ("TMOBIL %X\n", get_dec_state ());
}

void
CPex32View::OnUpdateAutomsg (CCmdUI * pCmdUI)
{
  //pCmdUI->SetCheck(get_dec_state()==0xff);
  m_pDoc->m_mainfrm->m_wndToolBar.GetToolBarCtrl ().PressButton (pCmdUI->
								 m_nID,
								 get_dec_state
								 () == 0xff);
}

void
CPex32View::OnUpdateQuix (CCmdUI * pCmdUI)
{
  //pCmdUI->SetCheck(get_dec_state()==0x99);
  m_pDoc->m_mainfrm->m_wndToolBar.GetToolBarCtrl ().PressButton (pCmdUI->
								 m_nID,
								 get_dec_state
								 () == 0x99);
}

void
CPex32View::OnUpdateTelmi (CCmdUI * pCmdUI)
{
  //pCmdUI->SetCheck(get_dec_state()==0xA6);
  m_pDoc->m_mainfrm->m_wndToolBar.GetToolBarCtrl ().PressButton (pCmdUI->
								 m_nID,
								 get_dec_state
								 () == 0xA6);
}

void
CPex32View::OnUpdateTmobil (CCmdUI * pCmdUI)
{
  //pCmdUI->SetCheck(get_dec_state()==0xA1);
  m_pDoc->m_mainfrm->m_wndToolBar.GetToolBarCtrl ().PressButton (pCmdUI->
								 m_nID,
								 get_dec_state
								 () == 0xA1);
}

void
CPex32View::On512 ()
{
  m_pDoc->m_s.m_dec.m_bitrate = 2;
  m_pDoc->m_baudrate_mask = 1;
  SetPrefs ();
}

void
CPex32View::On1200 ()
{
  m_pDoc->m_s.m_dec.m_bitrate = 1;
  m_pDoc->m_baudrate_mask = 2;
  SetPrefs ();
}

void
CPex32View::On2400 ()
{
  m_pDoc->m_s.m_dec.m_bitrate = 0;
  m_pDoc->m_baudrate_mask = 4;
  SetPrefs ();
}

void
CPex32View::OnUpdate512 (CCmdUI * pCmdUI)
{
  //pCmdUI->SetCheck(m_pDoc->m_s.m_dec.m_bitrate==2);     
  m_pDoc->m_mainfrm->m_wndToolBar.GetToolBarCtrl ().PressButton (pCmdUI->
								 m_nID,
								 m_pDoc->m_s.
								 m_dec.
								 m_bitrate ==
								 2);
}

void
CPex32View::OnUpdate1200 (CCmdUI * pCmdUI)
{
  //pCmdUI->SetCheck( m_pDoc->m_s.m_dec.m_bitrate==1 );
  m_pDoc->m_mainfrm->m_wndToolBar.GetToolBarCtrl ().PressButton (pCmdUI->
								 m_nID,
								 m_pDoc->m_s.
								 m_dec.
								 m_bitrate ==
								 1);
}

void
CPex32View::OnUpdate2400 (CCmdUI * pCmdUI)
{
  //pCmdUI->SetCheck(m_pDoc->m_s.m_dec.m_bitrate==0);     
  m_pDoc->m_mainfrm->m_wndToolBar.GetToolBarCtrl ().PressButton (pCmdUI->
								 m_nID,
								 m_pDoc->m_s.
								 m_dec.
								 m_bitrate ==
								 0);
}

void
CPex32View::OnAutobaud ()
{
  m_pDoc->m_s.m_dec.m_bitrate = 3;
  m_pDoc->m_baudrate_mask = 7;
  SetPrefs ();
}

void
CPex32View::OnUpdateAutobaud (CCmdUI * pCmdUI)
{
  //pCmdUI->SetCheck(m_pDoc->m_s.m_dec.m_bitrate==3);     
  m_pDoc->m_mainfrm->m_wndToolBar.GetToolBarCtrl ().PressButton (pCmdUI->
								 m_nID,
								 m_pDoc->m_s.
								 m_dec.
								 m_bitrate ==
								 3);
}

void
CPex32View::OnStop ()
{
  m_stopped = !m_stopped;
  if (!m_stopped)
    OnUpdate ();
}

void
CPex32View::OnUpdateStop (CCmdUI * pCmdUI)
{
  //pCmdUI->SetCheck(m_stopped);  
  m_pDoc->m_mainfrm->m_wndToolBar.GetToolBarCtrl ().PressButton (pCmdUI->
								 m_nID,
								 m_stopped);
}

void
CPex32View::OnFind ()
{
  static BOOL first_time = TRUE;
  m_start = 0;
  m_fdlg = new CFindReplaceDialog;
  m_fdlg->Create (TRUE, m_findstr, NULL,
		  FR_HIDEUPDOWN | FR_HIDEMATCHCASE | FR_HIDEWHOLEWORD, this);
}

LRESULT CPex32View::OnFindReplace (WPARAM wParam, LPARAM lParam)
{
  char
    str[300];
  LV_ITEM
    Item;
  int
    found = 0, i, j = m_pList->GetItemCount (), k;

  if (m_fdlg->IsTerminating ())
    return 0;

  m_findstr = m_fdlg->GetFindString ();

  m_findstr.MakeLower ();

  for (i = m_start; i < j; i++) {
    for (k = 0; k < 8; k++) {
      memset (&Item, 0, sizeof (Item));
      Item.mask = LVIF_TEXT;
      Item.iItem = i;
      Item.iSubItem = k;
      Item.pszText = str;
      Item.cchTextMax = sizeof (str);
      if (m_pList->GetItem (&Item)) {
	_strlwr (str);
	if (strstr (str, m_findstr)) {
	  while (!m_pList->EnsureVisible (i, FALSE)
		 && m_pList->GetCountPerPage ()) {
	    found = m_pList->GetTopIndex ();

	    if (found > i)
	      m_pList->Scroll (CSize (0, -10 * m_pList->GetCountPerPage ()));
	    else
	      m_pList->Scroll (CSize (0, 10 * m_pList->GetCountPerPage ()));

	    m_pList->UpdateWindow ();
	  }
	  int
	    lastfound = -1;
	  while ((found = m_pList->GetTopIndex ()) != i) {
	    if (found == lastfound)
	      break;
	    if (found > i)
	      m_pList->Scroll (CSize (0, -10));
	    else
	      m_pList->Scroll (CSize (0, 10));
	    lastfound = found;
	  }
	  Item.mask = LVIF_STATE;
	  Item.iSubItem = 0;
	  Item.state = LVIS_SELECTED | LVIS_FOCUSED;
	  Item.stateMask = LVIS_SELECTED | LVIS_FOCUSED;
	  m_pList->SetItem (&Item);
	  found = 1;

	  m_start = i + 1;
	  i = j;
	  break;
	}
      }
    }
  }
  if (!found) {
    AfxMessageBox (IDS_NOMATCHES, MB_ICONSTOP);
    m_start = 0;
  }
  return 0;
}

/*
	This function compares two strings, which may contain wildcards.
*/
int
CPex32View::match_wildcard (CString str1, CString str2)
{
  int i, match = TRUE;

  for (i = 0; (i < str1.GetLength ()) && (i < str2.GetLength ()); i++) {
    if (str2[i] == '*')
      break;
    if ((str1[i] != str2[i]) && (str2[i] != '?')) {
      match = FALSE;
      break;
    }
  }
  return match;
}

void
CPex32View::OnUpdate (CView * pSender, LPARAM lHint, CObject * pHint)
{
  OnUpdate ();
}

/* ---------------------------------------------------------------------- 
   Call this function whenever you want to have the display updated according
   to new messages in the database. If any filters are applied they are processed
   right here. It's important to do it here and not in the database. So later
   filterchanges take effect on all data stored in the base.
*/
void
CPex32View::OnUpdate (void)
{
  int i, j, itemcnt = m_pList->GetItemCount ();
  char *sep = ",;:\t\n\r", *tok;
  char *s[8];
  BOOL ok, prtok, add = FALSE;
  CString flt[8];
  CString str;
  CProgressCtrl pg;
  RECT rect;
  BOOL executed = FALSE;
  BOOL match = FALSE;
  CRegEx RegEx;

  if (m_stopped)
    return;

  if (m_pDoc->m_mainfrm) {
    m_pDoc->m_mainfrm->m_wndStatusBar.GetItemRect (0, &rect);
    ok =
      pg.Create (WS_VISIBLE,
		 CRect (100, 4, rect.right - rect.left - 100, 16),
		 &m_pDoc->m_mainfrm->m_wndStatusBar, 1234);
    pg.SetRange32 (m_LastItem, m_msg->GetSize ());
    str.LoadString (IDS_UPDLIST);
    m_pDoc->m_mainfrm->m_wndStatusBar.SetPaneText (0, str);
    ::SendMessage (m_pDoc->m_mainfrm->m_wndStatusBar, WM_PAINT, 0, 0);
  }
  if (m_LastItem)
    m_pList->SetItemCount (m_msg->GetSize ());

  //TRACE("OnUpdate Size %d\n",m_msg->GetSize());

  for (i = m_LastItem; i < m_msg->GetSize (); i++) {
    //CMsg m=(*m_msg)[i];
    CMsg & m = (*m_msg)[i];
    if (!(i & 63) && ok)
      pg.SetPos (i);
    str.Format ("%07d\t%d\t\"%s\"", m.m_adr, m.m_fct, m.m_msg);

    if ((m_pDoc->m_sg.m_flt.m_totop || m_pDoc->m_sg.m_flt.m_filterfct) &&
	!m_pDoc->m_sg.m_flt.m_filter.IsEmpty ()) {
      switch (m_pDoc->m_sg.m_flt.m_filterfct) {
      case _FLT_NOTACT:
      case _FLT_ACCEPT:
	prtok = FALSE;
	break;
      case _FLT_REJECT:
	prtok = TRUE;
	break;
      }

      //TRACE("Filter %d\n",m_s.m_dec.m_filterfct);
      //stradr.Format("%07d",m.m_adr);

      flt[0].Format ("%07d\n", m.m_adr);
      flt[1] = m.m_msg + "\n";
      flt[2].Format ("%d (%s)\n", m.m_fct, m_pDoc->m_funcstr[m.m_func]);
      flt[3].Format ("%s\n", m_pDoc->m_alias.LookupAlias (m.m_adr));

      s[0] = flt[0].GetBuffer (8);
      s[1] = flt[1].GetBuffer (_MAXMSGLEN);
      s[2] = flt[2].GetBuffer (16);
      s[3] = flt[3].GetBuffer (_MAXMSGLEN);

      CString filter = m_pDoc->m_sg.m_flt.m_filter;
      if ((tok =
	   strtok (filter.GetBuffer (filter.GetLength ()), sep)) == NULL)
	prtok = TRUE;

      match = FALSE;

      while (tok != NULL) {
	for (j = 0; j < 4; j++)
	  match |= RegEx.regex_match (tok, s[j]);

	if (match)
	  switch (m_pDoc->m_sg.m_flt.m_filterfct) {
	  case _FLT_NOTACT:
	  case _FLT_ACCEPT:
	    prtok |= TRUE;
	    TRACE ("juhu\n");
	    break;
	  case _FLT_REJECT:
	    prtok = FALSE;
	    break;
	  }

	tok = strtok (NULL, sep);
      }

      filter.ReleaseBuffer ();

      for (j = 0; j < 4; j++)
	flt[j].ReleaseBuffer ();

      if (prtok && m_pDoc->m_mainfrm && m_pDoc->m_sg.m_flt.m_totop)
	//::PostMessage(m_pDoc->m_mainfrm->m_hWnd,WM_COMMAND,WM_TOP,0);
	m_pDoc->m_mainfrm->SetForegroundWindow ();

      if (!executed && prtok && m_pDoc->m_sg.m_flt.m_startprg) {
	if ((int)
	    ShellExecute (m_hWnd, "play",
			  m_pDoc->m_sg.m_flt.m_programname, str, NULL,
			  SW_SHOW) <= 32)
	  ShellExecute (m_hWnd, NULL, m_pDoc->m_sg.m_flt.m_programname,
			str, NULL, SW_SHOW);
//	executed = TRUE;
      }

      if (!m_pDoc->m_sg.m_flt.m_filterfct && m_pDoc->m_sg.m_flt.m_totop)
	prtok = TRUE;
    }
    else
      prtok = TRUE;

    if (prtok && itemcnt && m_pDoc->m_sg.m_opt.m_eliminatecalls
	&& m_pDoc->m_sg.m_opt.m_eliminatecalls_timespan) {
      int ndx = itemcnt;
      do {
	ndx--;
	CMsg & msg = (*m_msg)[m_pList->GetItemData (ndx)];
	if ((m.m_time - msg.m_time) >
	    m_pDoc->m_sg.m_opt.m_eliminatecalls_timespan)
	  break;

	if (m_pDoc->m_sg.m_opt.m_eliminatecalls == 2)
	  if (msg.m_adr != m.m_adr)
	    continue;

	if (!msg.m_msg.Compare (m.m_msg)) {
	  prtok = FALSE;
	  break;
	}

      }
      while (ndx);
    }

    if (prtok) {
      m.m_displayed = TRUE;
      m_pDoc->m_alias.LookupAlias (m.m_adr);
      if (!executed && !m_pDoc->m_alias.m_a.m_alias.IsEmpty () &&
	  !m_pDoc->m_alias.m_a.m_programname.IsEmpty ()) {
	if ((int)
	    ShellExecute (m_hWnd, "play",
			  m_pDoc->m_alias.m_a.m_programname, str, NULL,
			  SW_SHOW) <= 32)
	  ShellExecute (m_hWnd, NULL, m_pDoc->m_alias.m_a.m_programname,
			str, NULL, SW_SHOW);
	//executed = TRUE;
      }

      if (m_pDoc->m_sg.m_lmn.m_cutvislist
	  && m_pDoc->m_sg.m_lmn.m_cutvislistnum)
	while (m_pList->GetItemCount () >= m_pDoc->m_sg.m_lmn.m_cutvislistnum) {
	  m_pList->DeleteItem (0);
	  itemcnt--;
	}

      int col = 0;
      str.Format ("%ld", itemcnt);
      //m_pList->InsertItem(LVIF_IMAGE|LVIF_TEXT|LVIF_PARAM,i, str,0 ,0, m.m_type&15,i);
      m_pList->InsertItem (LVIF_IMAGE | LVIF_PARAM, itemcnt, str, 0, 0,
			   m.m_type & 15, i);
      m_pDoc->datetimestr (str.GetBuffer (32), 32, m.m_time);
      m_pList->SetItemText (itemcnt, col++, str);
      str.ReleaseBuffer ();
      m_pList->SetItemText (itemcnt, col++, m_pDoc->m_source[m.m_type >> 4]);
      m_pList->SetItemText (itemcnt, col++, m_pDoc->m_srvstr[m.m_type & 15]);
      m_pList->SetItemText (itemcnt, col++, m_pDoc->m_bitstr[m.m_bitrate]);
      str.Format ("%07d", m.m_adr);
      m_pList->SetItemText (itemcnt, col++, str);
      m_pList->SetItemText (itemcnt, col++, m_pDoc->m_alias.m_a.m_alias);
      str.Format ("%d (%s)", m.m_fct, m_pDoc->m_funcstr[m.m_func]);
      m_pList->SetItemText (itemcnt, col++, str);
      m_pList->SetItemText (itemcnt, col++, m.m_msg);
      itemcnt++;
      add = TRUE;
    }
    else
      m.m_displayed = FALSE;

  }

  if (add) {
    m_LastItem = i;
    if (m_pDoc->m_sg.m_opt.m_jumptolistend)
      while (!m_pList->EnsureVisible (itemcnt - 1, FALSE))
	m_pList->Scroll (CSize (0, 5));
  }

  if (m_pDoc->m_mainfrm) {
    str.LoadString (AFX_IDS_IDLEMESSAGE);
    m_pDoc->m_mainfrm->m_wndStatusBar.SetPaneText (0, str);

    flt[0].LoadString (IDS_MSGS);
    str.Format ("%s %d/%d", flt[0], itemcnt, m_msg->GetSize ());
    m_pDoc->m_mainfrm->m_wndStatusBar.SetPaneText (1, str, TRUE);
    m_pDoc->m_mainfrm->NotifyModify (IDR_MAINFRAME, str.GetBuffer (256));
    str.ReleaseBuffer ();

    ::SendMessage (m_pDoc->m_mainfrm->m_wndStatusBar, WM_PAINT, 0, 0);
  }
}

/////////////////////////////////////////////////////////////////////////////
// CPex32View printing

BOOL CPex32View::OnPreparePrinting (CPrintInfo * pInfo)
{
  pInfo->SetMaxPage ((m_pList->GetItemCount () / LINESPERPAGE) + 1);
  TRACE ("OnPreparePrinting\n");
  return DoPreparePrinting (pInfo);
}

void
CPex32View::PrintPageHeader (CDC * pDC)
{
  CString s, str[6];
  CPoint point (LEFTBORDER, 0);
  str[0].LoadString (IDS_MONPRT);
  pDC->TextOut (point.x, point.y, str[0]);
  point += CSize (0, -620);
  str[0].LoadString (IDS_TIME);
  str[1].LoadString (IDS_BITRATE);
  str[2].LoadString (IDS_ADDRESS);
  str[3].LoadString (IDS_ALIAS);
  str[4].LoadString (IDS_FUNC);
  str[5].LoadString (IDS_MSG);

  s.Format ("%-14.14s %-5.5s %-7.7s %-9.9s %-9.9s %s",
	    str[0], str[1], str[2], str[3], str[4], str[5]);
  pDC->TextOut (point.x, point.y, s);
}

void
CPex32View::PrintPageFooter (CDC * pDC)
{
  CString str, s;

  CPoint point (LEFTBORDER, -11000);
  CPex32Doc *pDoc = GetDocument ();
  s.LoadString (IDS_MONPRTFILE);
  str.Format (s, (LPCSTR) pDoc->GetTitle ());
  pDC->TextOut (point.x, point.y, str);
  s.LoadString (IDS_MONPRTPAGE);
  str.Format (s, m_nPage);
  CSize size = pDC->GetTextExtent (str);
  point.x += 11520 - size.cx;
  pDC->TextOut (point.x, point.y, str);
}

void
CPex32View::OnPrint (CDC * pDC, CPrintInfo * pInfo)
{
  int i, nStart, nEnd, nHeight, ic = m_pList->GetItemCount ();
  CString str, s;
  CPoint point (LEFTBORDER, -640);
  CFont font;
  TEXTMETRIC tm;

  pDC->SetMapMode (MM_TWIPS);
  CPex32Doc *pDoc = GetDocument ();
  m_nPage = pInfo->m_nCurPage;	// for PrintPageFooter’s benefit

  nStart = (m_nPage - 1) * LINESPERPAGE;
  nEnd = nStart + LINESPERPAGE;

  font.CreateFont (- /*280 */ 170, 0, 0, 0, 400, FALSE, FALSE,
		   0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		   CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		   DEFAULT_PITCH | FF_MODERN, "Courier New");
  CFont *pOldFont = (CFont *) (pDC->SelectObject (&font));

  PrintPageHeader (pDC);
  pDC->GetTextMetrics (&tm);
  nHeight = tm.tmHeight + tm.tmExternalLeading;

  for (i = nStart; i < nEnd; i++) {
    if (i >= ic)
      break;
    CMsg m = (*m_msg)[m_pList->GetItemData (i)];
    m_pDoc->datetimestr (s.GetBuffer (32), 32, m.m_time);
    str.Format ("%s %5.5s %7.7d %-9.9s %d (%-5.5s) %s",
		s,
		m_pDoc->m_bitstr[m.m_bitrate],
		m.m_adr,
		m_pDoc->m_alias.LookupAlias (m.m_adr),
		m.m_fct, m_pDoc->m_funcstr[m.m_func], m.m_msg);
    s.ReleaseBuffer ();
    point.y -= nHeight;
    pDC->TextOut (point.x, point.y, str);
  }
  PrintPageFooter (pDC);
  pDC->SelectObject (pOldFont);
}

/* ---------------------------------------------------------------------- 
   Low cost version of copy to clipboard. Could have done it in C++, but
   for text-only objects it makes no difference.
*/
void
CPex32View::OnEditCopy ()
{
  CString str, s;
  LV_ITEM item;
  HGLOBAL ClpMem = NULL;
  char *ClpStr;
  int pos = 0, newmem = 1024;
  BOOL all = FALSE;
  BOOL ok;
  CProgressCtrl pg;

  if (m_pList->GetItemCount () == 0) {
    AfxMessageBox (IDS_NOITEMS);
    return;
  }

  if (m_pList->GetSelectedCount () == 0) {
    if (AfxMessageBox (IDS_NOSEL, MB_OKCANCEL) == IDOK)
      all = TRUE;
    else
      return;
  }

  if (!OpenClipboard ()) {
    AfxMessageBox (IDS_NOCLIPBRD);
    return;
  }

  EmptyClipboard ();
  {
    if (m_pDoc->m_mainfrm) {
      RECT rect;
      m_pDoc->m_mainfrm->m_wndStatusBar.GetItemRect (0, &rect);
      ok =
	pg.Create (WS_VISIBLE,
		   CRect (100, 4, rect.right - rect.left - 100, 16),
		   &m_pDoc->m_mainfrm->m_wndStatusBar, 1234);
      pg.SetRange32 (m_LastItem, m_msg->GetSize ());
    }
  }
  memset (&item, 0, sizeof (LV_ITEM));
  item.mask = LVIF_STATE;
  item.stateMask = LVIS_SELECTED;

  for (int i = 0; i < m_pList->GetItemCount (); i++) {
    if (!(i & 63) && ok)
      pg.SetPos (i);

    item.iItem = i;
    m_pList->GetItem (&item);
    if ((item.state == LVIS_SELECTED) || all) {
      if (ClpMem == NULL) {
	ClpMem =
	  GlobalAlloc (GMEM_MOVEABLE | GMEM_DDESHARE | GMEM_ZEROINIT, 1024);
	ClpStr = (char *) GlobalLock (ClpMem);
      }

      if (ClpMem != NULL) {
	CMsg m = (*m_msg)[m_pList->GetItemData (i)];
	m_pDoc->datetimestr (s.GetBuffer (32), 32, m.m_time);
	str.
	  Format ("%s\t%-4.4s\t%-5.5s\t%7.7d\t%s\t%d (%-5.5s)\t%s\r\n",
		  s, m_pDoc->m_source[m.m_type >> 4],
		  m_pDoc->m_bitstr[m.m_bitrate], m.m_adr,
		  m_pDoc->m_alias.LookupAlias (m.m_adr), m.m_fct,
		  m_pDoc->m_funcstr[m.m_func], m.m_msg);
	s.ReleaseBuffer ();
	if ((int) (strlen (ClpStr) + strlen (str)) >= newmem) {
	  HGLOBAL ret;
	  GlobalUnlock (ClpMem);
	  if ((ret =
	       GlobalReAlloc (ClpMem, 1024 + newmem,
			      GMEM_MOVEABLE | GMEM_ZEROINIT)) != NULL) {
	    newmem += 1024;
	    ClpMem = ret;
	    ClpStr = (char *) GlobalLock (ClpMem);
	    pos += sprintf (ClpStr + pos, "%s", str);

	  }
	  else
	    TRACE ("GlobalReAlloc Failed\n");
	}
	else
	  pos += sprintf (ClpStr + pos, "%s", str);
      }
    }
  }

  if (ClpMem != NULL) {
    GlobalUnlock (ClpMem);
    if (::SetClipboardData (CF_TEXT, ClpMem) == NULL) {
      AfxMessageBox (IDS_NOCLPCPY);
      CloseClipboard ();
      return;
    }
  }
  CloseClipboard ();
}

/* ---------------------------------------------------------------------- 
   Display ContextMenu... some people say they need it.
*/
void
CPex32View::OnContextMenu (CWnd * pWnd, CPoint point)
{
  CMenu m;
  m.LoadMenu (IDR_CONTEXT);
  if (!m_pDoc->m_s.m_hw.m_usecom)
    m.EnableMenuItem (ID_TX, MF_GRAYED);

  m.GetSubMenu (0)->TrackPopupMenu (TPM_LEFTALIGN | TPM_RIGHTBUTTON,
				    point.x, point.y, this);
}

/* ---------------------------------------------------------------------- 
   Display Font Selection Box.
*/
void
CPex32View::OnChoosefont ()
{
  GetFont ()->GetLogFont (&m_pDoc->m_lf);
  CFontDialog fd (&m_pDoc->m_lf, CF_SCREENFONTS);
  if (fd.DoModal () == IDOK) {
    CString str;
    int col = 0;
    m_pDoc->m_f.Detach ();
    m_pDoc->m_f.CreateFontIndirect (fd.m_cf.lpLogFont);
    SetFont (&m_pDoc->m_f, TRUE);

    int x = abs (fd.m_cf.lpLogFont->lfHeight);
    time_t t = time (NULL);
    m_pDoc->datetimestr (str.GetBuffer (32), 32, t);
    str.ReleaseBuffer ();
    m_pList->SetColumnWidth (col++, x * str.GetLength ());
    m_pList->SetColumnWidth (col++, x * 6);
    m_pList->SetColumnWidth (col++, x * 7);
    m_pList->SetColumnWidth (col++, x * 5);
    m_pList->SetColumnWidth (col++, x * 7);
    m_pList->SetColumnWidth (col++, x * 7);
    m_pList->SetColumnWidth (col++, x * 7);
    m_pList->SetColumnWidth (col++, x * 300);
  }
}

/* ---------------------------------------------------------------------- 
   Store font and ColumnWidths in registry or profile
*/
void
CPex32View::OnDestroy ()
{
  TRACE ("Destroy Window");
  delete m_mmb;
  KillTimer (_MYTIMER);

  GetFont ()->GetLogFont (&m_pDoc->m_lf);
  for (int i = 0; i < m_maxcols; i++)
    m_pDoc->m_colwidth[i] = m_pList->GetColumnWidth (i);
  SetPrefs ();
  m_pDoc->OnShutdown ();
  m_pDoc->m_mainfrm = NULL;
  CListView::OnDestroy ();
}

/* ---------------------------------------------------------------------- 
   Be hip and let the people surf your site.
*/
void
CPex32View::OnGowww ()
{
  if (((int)
       ShellExecute (m_hWnd, "open", "http://www.baycom.de/download/poc32",
		     NULL, NULL, SW_SHOW) <= 32)
      && ((int)
	  ShellExecute (m_hWnd, NULL, "iexplore.exe",
			"-h http://www.baycom.de/download/poc32", NULL,
			SW_SHOW) <= 32))

    AfxMessageBox (IDS_NODEFASSOC);
}

/* ---------------------------------------------------------------------- 
   Be stupid and let the people write you.
*/
void
CPex32View::OnFeedback ()
{
  CWinApp *w = AfxGetApp ();

  CString mailto;
  mailto.
    Format ("mailto:poc32@baycom.de?subject=POC32 Feedback V" APPVERSION);

  if (((int) ShellExecute (m_hWnd, "open", mailto, NULL, NULL, SW_SHOW) <=
       32))
    AfxMessageBox (IDS_NODEFASSOC);
}

afx_msg void
CPex32View::OnRegister ()
{
  TRACE ("OnRegister\n");
  m_pDoc->m_shareware = FALSE;
  AfxMessageBox (IDS_REGISTERED);
}

afx_msg void
CPex32View::OnSponsor ()
{
  if (((int)
       ShellExecute (m_hWnd, "open", "http://www.baycom.de/products/poc32",
		     NULL, NULL, SW_SHOW) <= 32)
      && ((int)
	  ShellExecute (m_hWnd, NULL, "iexplore.exe",
			"-h http://www.baycom.de/products/poc32", NULL,
			SW_SHOW) <= 32))
    AfxMessageBox (IDS_NODEFASSOC);
}

/* ---------------------------------------------------------------------- 
   Do a little self performance.
*/
void
CPex32View::OnAppAbout ()
{
  CAboutDlg aboutDlg;
  aboutDlg.DoModal ();
}

void
CPex32View::OnLicense ()
{
  TRACE ("OnLicense\n");
  CLicense l;
  CString str;
  l.m_licstr.LoadString (IDS_LICSTR1);
  str.LoadString (IDS_LICSTR2);
  l.m_licstr += str;
  if (l.DoModal () == IDCANCEL) {
    RegDeleteKey (HKEY_CURRENT_USER, "Software\\Mediasoft\\poc32\\Settings");
    m_pDoc->m_mainfrm->PostMessage (WM_CLOSE);
  }
}

/* ---------------------------------------------------------------------- 
   Show DCD from WavIn device for left channel
*/
void
CPex32View::OnUpdateLevel0 (CCmdUI * pCmdUI)
{
  pCmdUI->Enable ((m_pDoc->m_rx_512l.dcd > 0) || (m_pDoc->m_rx_1200l.dcd > 0)
		  || (m_pDoc->m_rx_2400l.dcd > 0));
}

/* ---------------------------------------------------------------------- 
   Show DCD from WavIn device for right channel
*/
void
CPex32View::OnUpdateLevel1 (CCmdUI * pCmdUI)
{
  pCmdUI->Enable ((m_pDoc->m_rx_512r.dcd > 0) || (m_pDoc->m_rx_1200r.dcd > 0)
		  || (m_pDoc->m_rx_2400r.dcd > 0));
}

afx_msg LONG
CPex32View::OnNewWavData (UINT wParam, LONG lParam)
{
  return m_pDoc->OnNewWavData (wParam, lParam);
}

void
CPex32View::OnTimer (UINT nIDEvent)
{
  if (nIDEvent == _MYTIMER)
    m_pDoc->OnTimer (nIDEvent);
  else
    CListView::OnTimer (nIDEvent);
}

void
CPex32View::OnDblclk (NMHDR * pNMHDR, LRESULT * pResult)
{
  TRACE ("OnDblclk \n");
  OnEntryProperties ();
  *pResult = 0;
}

void
CPex32View::OnEntryProperties ()
{
  int nSelected = m_pList->GetSelectedCount ();

  // only proceed if one item selected....
  //if ( nSelected == 1 )
  {
    // find the selected item....
    int ndx = 0;
    int nItems = m_pList->GetItemCount ();

    while (ndx < nItems) {
      if (m_pList->GetItemState (ndx, LVIS_SELECTED) == LVIS_SELECTED) {
	int idx = m_pList->GetItemData (ndx);
	TRACE ("Selected idx%d\n", idx);
	CEntryAlias ea;
	m_pDoc->m_alias.LookupAlias ((*m_msg)[idx].m_adr);
	ea.m_a = m_pDoc->m_alias.m_a;
	switch (ea.DoModal ()) {
	case _DELETE_ENTRY:
	  m_pDoc->m_alias.DelAlias (ea.m_a.m_adr);
	  break;

	case IDOK:
	  m_pDoc->m_alias.DelAlias (ea.m_a.m_adr);
	  m_pDoc->m_alias.AddAlias (ea.m_a);
	  break;

	case IDCANCEL:
	  return;
	  break;
	}
	m_pList->SetItemText (ndx, 5,
			      m_pDoc->m_alias.LookupAlias (ea.m_a.m_adr));
	m_pList->Update (ndx);
      }
      ndx++;
    }
  }
  return;
}

void
CPex32View::OnKeyDown (UINT nChar, UINT nRepCnt, UINT nFlags)
{
  TRACE ("KeyDown: %d %d %d\n", nChar, nRepCnt, nFlags);
  switch (nChar) {
  case 13:
    OnEntryProperties ();
    break;
  case 46:
    OnDeleteEntry ();
    break;
  }
  CListView::OnKeyDown (nChar, nRepCnt, nFlags);
}

afx_msg void
CPex32View::OnDeleteEntry ()
{
  int nSelected = m_pList->GetSelectedCount ();

  // only proceed if one item selected....
  if (nSelected) {
    if (AfxMessageBox (IDS_DELETE, MB_OKCANCEL) == IDCANCEL)
      return;

    // find the selected item....
    int ndx = 0;
    int nItems = m_pList->GetItemCount ();

    while (ndx < nItems) {
      if (m_pList->GetItemState (ndx, LVIS_SELECTED) == LVIS_SELECTED) {
	//int idx=m_pList->GetItemData(ndx);
	//m_pDoc->m_msg.RemoveAt(idx);
	m_pList->DeleteItem (ndx);
	nItems--;
      }
      else
	ndx++;
    }

    m_LastItem = 0;
    //m_pList->DeleteAllItems();
    OnUpdate (NULL, 0, NULL);

  }
  return;
}


void
CPex32View::OnUpdateall ()
{
  m_LastItem = 0;
  m_pList->DeleteAllItems ();
  OnUpdate (NULL, 0, NULL);
}
