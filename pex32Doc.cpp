// pex32Doc.cpp : implementation of the CPex32Doc class
//

#include "stdafx.h"
#include "MyStatusBar.h"
#include "MainFrm.h"
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
#include "pocsag.h"
#include "ecctab.h"
#include "Listen.h"
#include "aliases.h"
#include "MyMessageBox.h"
#include "pex32Doc.h"
#include "Winnls.h"

CPex32Doc *pPex32Doc;

/*
 * the coefficients for a symmetric FIR filter
 */
static const char m_filter_coeffs_512[] = { 7, 12, 25, 45, 70, 94, 114, 125 };
static const char m_filter_coeffs_1200[] = { 0, -1, -3, -2, 5, 22, 44, 59 };
static const char m_filter_coeffs_2400[] = { 0, 1, 0, -5, -10, 4, 46, 86 };

/* We need a pocsag_rx structure for every bitrate and channel. It contains all
   local variables for DPLL and data buffers.
*/


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPex32Doc

IMPLEMENT_DYNCREATE (CPex32Doc, CDocument)
  BEGIN_MESSAGE_MAP (CPex32Doc, CDocument)
  //{{AFX_MSG_MAP(CPex32Doc)
  // NOTE - the ClassWizard will add and remove mapping macros here.
  //    DO NOT EDIT what you see in these blocks of generated code!
  //}}AFX_MSG_MAP
  END_MESSAGE_MAP ()
/////////////////////////////////////////////////////////////////////////////
// CPex32Doc construction/destruction
CPex32Doc::CPex32Doc ():m_s (""), m_sg ("")
{
  pPex32Doc = this;

  m_srvstr[QUIX] = QUIXSTR;
  m_srvstr[TMOBIL] = TMOBILSTR;
  m_srvstr[TELMI] = TELMISTR;
  m_srvstr[UNKNOWN] = "?";
  m_srvstr[OWNMSG] = "TXMSG";

  m_bitstr[0] = "2400";
  m_bitstr[1] = "1200";
  m_bitstr[2] = "512";

  m_funcstr[BEEP] = BEEPSTR;
  m_funcstr[NUM] = NUMSTR;
  m_funcstr[ALPHA] = ALPHASTR;

  m_source[0] = "COM";
  m_source[1] = "CH1";
  m_source[2] = "CH2";

  /*
   * initialize variables
   */
  m_timespan = time (NULL);
  /* this is the sampling rate to be used in khz 
   */
  m_srate = 11025;

  /* preset each DPLL decoder structure
   */
  m_rx_512l.dcd = DCD_MOSTNEGATIVE;
  m_rx_512l.rx_sync = 0;
  m_rx_512l.b.p = 0;
  m_rx_512l.channel = 0;
  m_rx_512r = m_rx_1200l = m_rx_2400l = m_rx_512l;

  m_rx_512r.channel = 1;
  m_rx_1200r = m_rx_2400r = m_rx_512r;

  m_rx_512r.b.br = m_rx_512l.b.br = 512;
  m_rx_1200r.b.br = m_rx_1200l.b.br = 1200;
  m_rx_2400r.b.br = m_rx_2400l.b.br = 2400;

  m_rx_512r.ph_update = m_rx_512l.ph_update =
    (0x10000L * 512L + m_srate / 2) / m_srate;
  m_rx_1200r.ph_update = m_rx_1200l.ph_update =
    (0x10000L * 1200L + m_srate / 2) / m_srate;
  m_rx_2400r.ph_update = m_rx_2400l.ph_update =
    (0x10000L * 2400L + m_srate / 2) / m_srate;

  m_invert_rx = FALSE;

  /* absolute hysteresis of the simulated FSK-comparator.
   */
  m_hyst = 1024;

  /* Just used to produce some debug messages (development relicts)
   */
  m_verbose_level = 0;


  /* Basics which can be overidden by property page settings.
     baudrate_mask: bit0 512bit/s  bit1 1200bit/s  bit2 2400bit/s
   */
  m_baudrate_mask = 7;

  /* Use FIR filter? Will only improve decoding results when the sampling
     rate is >= 20khz and AF carries IF parts.
   */
  m_do_filter = TRUE;

  /* Number of bits to correct (maximum is 2) this increases the errors too.
   */
  m_correct_bits = 2;


  /* Preset all file and device handles. 
   */
  m_hCVxD = INVALID_HANDLE_VALUE;
  m_enablesound = FALSE;
  m_WavIn = 0;

  /* Clear buffer pointer array (not really needed)
   */
  memset (m_DataBuf, 0, sizeof (m_DataBuf));


  /* preset character translation table with standard ASCII
   */
  for (int i = 0; i < 256; i++)
    m_transtbl[i].Format ("%c", i);

  m_transtbl[0] = " ";
  m_transtbl[1] = "<SOH>";
  m_transtbl[2] = "<STX>";
  m_transtbl[3] = " ";
  m_transtbl[4] = "<EOT>";
  m_transtbl[5] = "<ENQ>";
  m_transtbl[6] = "<ACK>";
  m_transtbl[7] = "<BEL>";
  m_transtbl[13] = "<CR>";
  m_transtbl[10] = "<LF>";
  m_transtbl[0x5b] = "Ä";
  m_transtbl[0x7b] = "ä";
  m_transtbl[0x5c] = "Ö";
  m_transtbl[0x7c] = "ö";
  m_transtbl[0x5d] = "Ü";
  m_transtbl[0x7d] = "ü";
  m_transtbl[0x1f] = "ß";
  m_transtbl[0x7e] = "ß";

  m_last_saved = time (NULL);
  m_mainfrm = NULL;
  m_pListen = NULL;
  m_mmb = NULL;
  m_shareware = TRUE;
//  STARTUPINFO StartupInfo;
//  GetStartupInfo(&StartupInfo);

//  char drive[FILENAME_MAX];
//  char dir[FILENAME_MAX];
//  _splitpath (StartupInfo.lpTitle, drive, dir, NULL, NULL);
//  sprintf(m_homedir.GetBuffer(FILENAME_MAX*2),"%s%s",drive,dir);
//  m_homedir.ReleaseBuffer();
  m_homedir=GetExeDir();
}

CPex32Doc::~CPex32Doc ()
{
}

CString CPex32Doc::GetExeDir()
{
	char szPath[FILENAME_MAX];
	GetModuleFileName(AfxGetApp()->m_hInstance, szPath, sizeof(szPath));
	
	char *ptr = strrchr(szPath, '\\');
	
	if (ptr)
	{
		ptr[1] = '\0';
	}
	
	ASSERT(strlen(szPath) < sizeof(szPath));
	
	return szPath;
}


/* ---------------------------------------------------------------------- 
   Besides InitHardware you need to call this high level initialization
*/
BOOL CPex32Doc::OnNewDocument ()
{
  if (!CDocument::OnNewDocument ())
    return FALSE;

  m_msg.RemoveAll ();
  SetModifiedFlag (FALSE);
  return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CPex32Doc serialization
/* ---------------------------------------------------------------------- 
   I'm using this to override the standard serialization of CObjects, so I'm
   able to check on data inconsistencies or integrity. The file format is a
   tab-spaced table, which can be easily imported by winword etc..
*/
void
CPex32Doc::Serialize (CArchive & ar)
{
  int i;
  BOOL ok = FALSE;
  CString str;

  m_lastlistname = ar.GetFile ()->GetFileName ();
  CProgressCtrl pg;

  if (m_mainfrm) {
    RECT rect;
    m_mainfrm->m_wndStatusBar.GetItemRect (0, &rect);
    ok =
      pg.Create (WS_VISIBLE,
		 CRect (120, 4, rect.right - rect.left - 120, 16),
		 &m_mainfrm->m_wndStatusBar, 1234);
  }
  TRACE ("Serialize\n");

  if (ar.IsStoring ()) {
    if (ok) {
      pg.SetRange32 (0, m_msg.GetSize ());
		str.LoadString (IDS_STORING);
      m_mainfrm->m_wndStatusBar.SetPaneText (0, str);
      ::SendMessage (m_mainfrm->m_wndStatusBar, WM_PAINT, 0, 0);
    }
    for (i = 0; i < m_msg.GetSize (); i++) {
		if (!(i & 63) && ok) {
			pg.SetPos (i);
		}

      str.Format("%x\t%x\t%x\t%x\t%x\t%x\t%x\t%s\r\n",
		  i,
		 (int)m_msg[i].m_time,
		  m_msg[i].m_type,
		  m_msg[i].m_bitrate,
		  m_msg[i].m_adr,
		  m_msg[i].m_fct, 
		  m_msg[i].m_func, 
		  m_msg[i].m_msg);
		  
      ar.WriteString (str);
    }
  }
  else {
    char *s;
    char *t;

    int i, j = 0;
    BOOL fmterr = FALSE;
    CMsg msg;
    CFile *f = ar.GetFile ();
    if (ok) {
      pg.SetRange32 (0, (short) (f->GetLength () >> 8));
      str.LoadString (IDS_LOADING);
      m_mainfrm->m_wndStatusBar.SetPaneText (0, str);
      ::SendMessage (m_mainfrm->m_wndStatusBar, WM_PAINT, 0, 0);
    }
    TRACE ("Length %d\n", f->GetLength ());
    while (ar.ReadString (str)) {
      j++;
      s = str.GetBuffer (_MAXMSGLEN * 2);
	  int time32;
      sscanf (s, "%x\t%x\t%x\t%x\t%x\t%x\t%x\t",
	      &i,
	      &time32,
	      &msg.m_type,
	      &msg.m_bitrate, &msg.m_adr, &msg.m_fct, &msg.m_func);
	  msg.m_time=time32;
      t = s;
      if ((msg.m_type & 15) > 4) {
	fmterr = TRUE;
	msg.m_type = UNKNOWN;
      }
      if ((msg.m_type >> 4) > 2) {
	fmterr = TRUE;
	msg.m_type = UNKNOWN;
      }
      if (msg.m_bitrate > 2) {
	fmterr = TRUE;
	msg.m_bitrate = 0;
      }
      if (msg.m_fct > 3) {
	fmterr = TRUE;
	msg.m_fct = 0;
      }
      if (msg.m_func > 2) {
	fmterr = TRUE;
	msg.m_func = 0;
      }
      if (fmterr) {
	CString s, t;
	s.LoadString (IDS_FMTERR);
	t.Format (s, j);
	if (AfxMessageBox (t, MB_OKCANCEL) == IDCANCEL)
	  return;

	continue;
      }

      if (!(i & 63) && ok) {
	pg.SetPos ((int) f->GetPosition () >> 8);
	//TRACE("Pos %d\n",f->GetPosition()>>8);
      }
      for (i = 0; i < 7; i++) {
	t = strchr (t, '\t');
	if (t)
	  t++;
	else
	  break;
      }
      if (t)
	msg.m_msg = t;
      else
	msg.m_msg = "";

      //m_msg.Add(msg);
      AddToList (msg);

      str.ReleaseBuffer ();
    }
  }
}

/////////////////////////////////////////////////////////////////////////////
// CPex32Doc diagnostics

#ifdef _DEBUG
void
     CPex32Doc::AssertValid () const const const
     {
       CDocument::AssertValid ();
     }

     void CPex32Doc::Dump (CDumpContext & dc) const const const
     {
       CDocument::Dump (dc);
     }
#endif				//_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPex32Doc commands

/* ---------------------------------------------------------------------- 
   This function adds one message structure to the messagearray
*/
     void CPex32Doc::AddToList (CMsg & m)
{
  m.m_displayed = FALSE;

  if (!m.m_time)
    time (&m.m_time);

  if (m_sg.m_lmn.m_cutinternalist && m_sg.m_lmn.m_cutinternalistnum)
    while (m_msg.GetSize () >= m_sg.m_lmn.m_cutinternalistnum)
      m_msg.RemoveAt (0);
  m_msg.Add (m);
  //TRACE("Add to List");
  SetModifiedFlag ();
}

BOOL CPex32Doc::OnOpenDocument (LPCTSTR lpszPathName)
{
  TRACE ("OpenDocument\n");

  if (m_msg.GetSize () && (AfxMessageBox (IDS_APPENDFILE, MB_YESNO) == IDNO)) {
    OnNewDocument ();
  }

  if (!CDocument::OnOpenDocument (lpszPathName))
    return FALSE;

  return TRUE;
}

/* ---------------------------------------------------------------------- 
   Read preferences from registry or profile.
*/
void
CPex32Doc::GetPrefs (void)
{
  CWinApp *w = AfxGetApp ();

  m_s.m_dec.m_bitrate = w->GetProfileInt ("Settings", "rxbitrate", 3);
  m_s.m_dec.m_skyper = w->GetProfileInt ("Settings", "skyper", 0);
  m_s.m_dec.m_fct[0] = w->GetProfileInt ("Settings", "fct0", 3);
  m_s.m_dec.m_fct[1] = w->GetProfileInt ("Settings", "fct1", 3);
  m_s.m_dec.m_fct[2] = w->GetProfileInt ("Settings", "fct2", 3);
  m_s.m_dec.m_fct[3] = w->GetProfileInt ("Settings", "fct3", 3);

  m_s.m_enc.m_txinv = w->GetProfileInt ("Settings", "txinv", 0);
  m_s.m_enc.m_pttinv = w->GetProfileInt ("Settings", "pttinv", 1);
  m_s.m_enc.m_txdelay = w->GetProfileInt ("Settings", "txdelay", 20);

  m_s.m_hw.m_port = w->GetProfileInt ("Settings", "port", 1);
  m_s.m_hw.m_int = w->GetProfileInt ("Settings", "int", 0);
  m_s.m_hw.m_syncword = w->GetProfileInt ("Settings", "syncword", _SYNC);
  m_s.m_hw.m_cardnum = w->GetProfileInt ("Settings", "cardnum", -1);
  m_s.m_hw.m_usesndcrd = w->GetProfileInt ("Settings", "usesndcrd", 0);
  m_s.m_hw.m_usecom = w->GetProfileInt ("Settings", "usecom", 0);
  m_s.m_hw.m_debug = w->GetProfileInt ("Settings", "debug", 0);
  m_s.m_hw.m_rxline = w->GetProfileInt ("Settings", "rxline", 0);
  m_s.m_hw.m_errcor = w->GetProfileInt ("Settings", "errcor", 0);
  m_s.m_hw.m_firflt = w->GetProfileInt ("Settings", "firflt", 0);
  m_s.m_hw.m_channels = w->GetProfileInt ("Settings", "channels", 0);

  m_txdlg.m_adr = w->GetProfileInt ("Settings", "adr", 1234567);
  m_txdlg.m_encode = w->GetProfileInt ("Settings", "encode", 0);
  m_txdlg.m_bitrate = w->GetProfileInt ("Settings", "txbitrate", 1);
  m_txdlg.m_fct = w->GetProfileInt ("Settings", "fct", 0);
  m_txdlg.m_msg = w->GetProfileString ("Settings", "msg", "0123456789");

  m_tblname = w->GetProfileString ("Settings", "TransTbl", m_homedir+"\\default.tbl");

  m_s.m_type = w->GetProfileInt ("Settings", "type", UNKNOWN);

  m_colwidth[0] = w->GetProfileInt ("Window", "Col0", 90);
  m_colwidth[1] = w->GetProfileInt ("Window", "Col1", 50);
  m_colwidth[2] = w->GetProfileInt ("Window", "Col2", 0);
  m_colwidth[3] = w->GetProfileInt ("Window", "Col3", 40);
  m_colwidth[4] = w->GetProfileInt ("Window", "Col4", 60);
  m_colwidth[5] = w->GetProfileInt ("Window", "Col5", 60);
  m_colwidth[6] = w->GetProfileInt ("Window", "Col6", 60);
  m_colwidth[7] = w->GetProfileInt ("Window", "Col7", 1000);

  m_s.m_hw.m_syncstr.Format ("0x%X", m_s.m_hw.m_syncword);

  memset (&m_lf, 0, sizeof (LOGFONT));
  strcpy (m_lf.lfFaceName,
	  w->GetProfileString ("Window", "FontName", "MS Sans Serif"));
  m_lf.lfHeight = w->GetProfileInt ("Window", "FontHeight", -8);
  m_lf.lfWeight = w->GetProfileInt ("Window", "FontWeight", 400);
  m_lf.lfItalic = w->GetProfileInt ("Window", "FontItalic", 0);
  m_lf.lfCharSet = w->GetProfileInt ("Window", "FontCharSet", 0);

  m_sg.m_flt.m_totop = w->GetProfileInt ("Settings", "totop", 0);
  m_sg.m_flt.m_filterfct = w->GetProfileInt ("Settings", "filterfct", 0);
//      m_sg.m_flt.m_beep       =w->GetProfileInt("Settings","beep",0);
  m_sg.m_flt.m_filter = w->GetProfileString ("Settings", "filter", "");
  m_sg.m_flt.m_programname =
    w->GetProfileString ("Settings", "programname", "");
  m_sg.m_flt.m_startprg = w->GetProfileInt ("Settings", "startprg", 0);

  m_sg.m_lmn.m_autoload = w->GetProfileInt ("Settings", "autoload", 0);
  m_lastlistname = w->GetProfileString ("Settings", "lastlistname", "");
  m_sg.m_lmn.m_autosave = w->GetProfileInt ("Settings", "autosave", 0);
  m_sg.m_lmn.m_autosavenum = w->GetProfileInt ("Settings", "autosavenum", 0);
  m_sg.m_lmn.m_cutinternalist =
    w->GetProfileInt ("Settings", "cutinternalist", 0);
  m_sg.m_lmn.m_cutinternalistnum =
    w->GetProfileInt ("Settings", "cutinternalistnum", 0);
  m_sg.m_lmn.m_cutvislist = w->GetProfileInt ("Settings", "cutvislist", 0);
  m_sg.m_lmn.m_cutvislistnum =
    w->GetProfileInt ("Settings", "cutvislistnum", 0);

  m_sg.m_opt.m_eliminatecalls =
    w->GetProfileInt ("Settings", "eliminatecalls", 0);
  m_sg.m_opt.m_eliminatecalls_timespan =
    w->GetProfileInt ("Settings", "eliminatecalls_timespan", 60);
  m_sg.m_opt.m_jumptolistend =
    w->GetProfileInt ("Settings", "jumptolistend", 1);

  m_sg.m_opt.m_enabletcpip = w->GetProfileInt ("Settings", "enabletcpip", 0);
  m_sg.m_opt.m_tcpipport = w->GetProfileInt ("Settings", "tcpipport", 8000);
  m_sg.m_opt.m_password = w->GetProfileString ("Settings", "password", "");

  SetPrefs ();
}

/* ---------------------------------------------------------------------- 
   Store preferences in regsitry or profile
*/
void
CPex32Doc::SetPrefs (void)
{
  DWORD syncword = 0x1;

  TRACE ("On Set Prefs\n");


  if (m_s.m_hw.m_syncstr.GetLength () > 2)
    if ((m_s.m_hw.m_syncstr[0] == '0')
	&& ((m_s.m_hw.m_syncstr[1] & 0x5f) == 'X'))
      sscanf (m_s.m_hw.m_syncstr, "0x%x", &syncword);
    else
      syncword = atol (m_s.m_hw.m_syncstr);

  if (!syncword || ((unsigned) syncword != crc (syncword >> 11L))) {
    AfxMessageBox (IDS_SYNCERR);
    //m_mmb->MessageBox(IDS_SYNCERR);
  }
  else
    m_s.m_hw.m_syncword = syncword;

  m_s.m_hw.m_syncstr.Format ("0x%X", m_s.m_hw.m_syncword);

  if (!InitHardware ())
    return;

  CWinApp *w = AfxGetApp ();
  w->WriteProfileInt ("Settings", "rxbitrate", m_s.m_dec.m_bitrate);
  w->WriteProfileInt ("Settings", "skyper", m_s.m_dec.m_skyper);
  w->WriteProfileInt ("Settings", "fct0", m_s.m_dec.m_fct[0]);
  w->WriteProfileInt ("Settings", "fct1", m_s.m_dec.m_fct[1]);
  w->WriteProfileInt ("Settings", "fct2", m_s.m_dec.m_fct[2]);
  w->WriteProfileInt ("Settings", "fct3", m_s.m_dec.m_fct[3]);

  w->WriteProfileInt ("Settings", "txinv", m_s.m_enc.m_txinv);
  w->WriteProfileInt ("Settings", "pttinv", m_s.m_enc.m_pttinv);
  w->WriteProfileInt ("Settings", "txdelay", m_s.m_enc.m_txdelay);

  w->WriteProfileInt ("Settings", "port", m_s.m_hw.m_port);
  w->WriteProfileInt ("Settings", "int", m_s.m_hw.m_int);
  w->WriteProfileInt ("Settings", "syncword", m_s.m_hw.m_syncword);
  w->WriteProfileInt ("Settings", "cardnum", m_s.m_hw.m_cardnum);
  w->WriteProfileInt ("Settings", "usesndcrd", m_s.m_hw.m_usesndcrd);
  w->WriteProfileInt ("Settings", "usecom", m_s.m_hw.m_usecom);
  w->WriteProfileInt ("Settings", "debug", m_s.m_hw.m_debug);
  w->WriteProfileInt ("Settings", "rxline", m_s.m_hw.m_rxline);
  w->WriteProfileInt ("Settings", "errcor", m_s.m_hw.m_errcor);
  w->WriteProfileInt ("Settings", "firflt", m_s.m_hw.m_firflt);
  w->WriteProfileInt ("Settings", "channels", m_s.m_hw.m_channels);

  w->WriteProfileInt ("Settings", "adr", m_txdlg.m_adr);
  w->WriteProfileInt ("Settings", "encode", m_txdlg.m_encode);
  w->WriteProfileInt ("Settings", "txbitrate", m_txdlg.m_bitrate);
  w->WriteProfileInt ("Settings", "fct", m_txdlg.m_fct);
  w->WriteProfileString ("Settings", "msg", m_txdlg.m_msg);

  w->WriteProfileInt ("Settings", "type", m_s.m_type);
  w->WriteProfileString ("Settings", "TransTbl", m_tblname);

  w->WriteProfileInt ("Window", "Col0", m_colwidth[0]);
  w->WriteProfileInt ("Window", "Col1", m_colwidth[1]);
  w->WriteProfileInt ("Window", "Col2", m_colwidth[2]);
  w->WriteProfileInt ("Window", "Col3", m_colwidth[3]);
  w->WriteProfileInt ("Window", "Col4", m_colwidth[4]);
  w->WriteProfileInt ("Window", "Col5", m_colwidth[5]);
  w->WriteProfileInt ("Window", "Col6", m_colwidth[6]);
  w->WriteProfileInt ("Window", "Col7", m_colwidth[7]);

  w->WriteProfileString ("Window", "FontName", m_lf.lfFaceName);
  w->WriteProfileInt ("Window", "FontHeight", m_lf.lfHeight);
  w->WriteProfileInt ("Window", "FontWeight", m_lf.lfWeight);
  w->WriteProfileInt ("Window", "FontItalic", m_lf.lfItalic);
  w->WriteProfileInt ("Window", "FontCharSet", m_lf.lfCharSet);

  w->WriteProfileInt ("Settings", "totop", m_sg.m_flt.m_totop);
  w->WriteProfileInt ("Settings", "filterfct", m_sg.m_flt.m_filterfct);
//      w->WriteProfileInt("Settings","beep"     ,m_sg.m_flt.m_beep);
  w->WriteProfileString ("Settings", "filter", m_sg.m_flt.m_filter);
  w->WriteProfileString ("Settings", "programname", m_sg.m_flt.m_programname);
  w->WriteProfileInt ("Settings", "startprg", m_sg.m_flt.m_startprg);

  w->WriteProfileInt ("Settings", "autoload", m_sg.m_lmn.m_autoload);
  w->WriteProfileString ("Settings", "lastlistname", m_lastlistname);
  w->WriteProfileInt ("Settings", "autosave", m_sg.m_lmn.m_autosave);
  w->WriteProfileInt ("Settings", "autosavenum", m_sg.m_lmn.m_autosavenum);
  w->WriteProfileInt ("Settings", "cutinternalist",
		      m_sg.m_lmn.m_cutinternalist);
  w->WriteProfileInt ("Settings", "cutinternalistnum",
		      m_sg.m_lmn.m_cutinternalistnum);
  w->WriteProfileInt ("Settings", "cutvislist", m_sg.m_lmn.m_cutvislist);
  w->WriteProfileInt ("Settings", "cutvislistnum",
		      m_sg.m_lmn.m_cutvislistnum);

  w->WriteProfileInt ("Settings", "eliminatecalls",
		      m_sg.m_opt.m_eliminatecalls);
  w->WriteProfileInt ("Settings", "eliminatecalls_timespan",
		      m_sg.m_opt.m_eliminatecalls_timespan);
  w->WriteProfileInt ("Settings", "jumptolistend",
		      m_sg.m_opt.m_jumptolistend);

  w->WriteProfileInt ("Settings", "enabletcpip", m_sg.m_opt.m_enabletcpip);
  w->WriteProfileInt ("Settings", "tcpipport", m_sg.m_opt.m_tcpipport);
  w->WriteProfileString ("Settings", "password", m_sg.m_opt.m_password);

}

/* ---------------------------------------------------------------------- 
   Use AddBuffer to add buffers for Win Multimedia WavIn Device
   Should always be called after receiving a filled buffer.
*/
void
CPex32Doc::AddBuffer (void)
{
  static WAVEHDR wvhdr[_BUFMAX];
  int i;
  for (i = 0; i < _BUFMAX; i++)
    if (m_Alloctable[i] == FALSE) {
      MMRESULT res;
      wvhdr[i].lpData = m_DataBuf[i];
      wvhdr[i].dwBufferLength = _BUFLEN;
      wvhdr[i].dwFlags = 0;
      wvhdr[i].dwUser = i;
      if ((res =
	   waveInPrepareHeader (m_WavIn, &wvhdr[i],
				sizeof (WAVEHDR))) != MMSYSERR_NOERROR)
	TRACE ("Error: waveInPrepareHeader %d %x %x! \n", res, i,
	       wvhdr[i].lpData);
      else if (waveInAddBuffer (m_WavIn, &wvhdr[i], sizeof (WAVEHDR)) !=
	       MMSYSERR_NOERROR)
	TRACE ("Error: waveInAddBuffer!\n");
      else
	m_Alloctable[i] = TRUE;
      //TRACE("Buffer %d Added\n",i);
    }
}

/* ---------------------------------------------------------------------- 
	This is the main decoder loop!
	OnNewWavData is called whenever there is a WavIn buffer ready (filled)
	We'll pick up this buffer and call the decoder machine. It has to process 
	all data words of this buffer according to the user preferences.
*/
LONG CPex32Doc::OnNewWavData (UINT wParam, LONG lParam)
{
  static BOOL
    rec = FALSE;
  int
    i = ((LPWAVEHDR) lParam)->dwUser;

  waveInUnprepareHeader ((HWAVEIN) wParam, (LPWAVEHDR) lParam,
			 sizeof (WAVEHDR));

  if (m_enablesound && !rec) {
    rec = TRUE;
    demodulator (m_DataBuf[i]);
    m_Alloctable[i] = FALSE;
    AddBuffer ();
    rec = FALSE;
  }
  else {
    m_Alloctable[i] = FALSE;
    m_buferr++;
  }
  return 0;
}

/* ---------------------------------------------------------------------- 
	InitWavIn(TRUE) opens a WavIn Device and sets the sampling parameters for the 
	specified device. It will adapt to the device's capabilities (8 or 16 bit 
	samples). After successfull initializing it will AddBuffers and start sampling.
	InitWavIn(FASLSE) closes a WavIn Device. 
*/
BOOL CPex32Doc::InitWavIn (BOOL state)
{
  static int
    cardnum = -1;
  static int
    channels = 0;

  WAVEINCAPS
    devcaps;
  WAVEFORMATEX
    Form;
  CString
    s;

  m_enablesound = FALSE;
  if (m_s.m_hw.m_cardnum == -1)
    return FALSE;

  if (state) {

    if (m_WavIn) {
      if ((cardnum == m_s.m_hw.m_cardnum) &&
	  (m_s.m_hw.m_channels == channels)) {
	m_enablesound = TRUE;
	return TRUE;
      }

      /*s.LoadString(IDS_WAITSND);
         m_mainfrm->m_wndStatusBar.SetPaneText(0,s);
         ::SendMessage(m_mainfrm->m_wndStatusBar,WM_PAINT,0,0);
       */

      waveInReset (m_WavIn);
      while (waveInClose (m_WavIn) != MMSYSERR_NOERROR);
      Sleep (100);
    }

    cardnum = m_s.m_hw.m_cardnum;
    channels = m_s.m_hw.m_channels;

    if (waveInGetDevCaps (cardnum, &devcaps, sizeof (devcaps)) ==
	MMSYSERR_NOERROR)
      if ((devcaps.dwFormats & (WAVE_FORMAT_1M16 | WAVE_FORMAT_1S16)) !=
	  (WAVE_FORMAT_1M16 | WAVE_FORMAT_1S16))
	m_8bps = TRUE;
      else
	m_8bps = FALSE;

    //m_8bps=TRUE;

    Form.wFormatTag = WAVE_FORMAT_PCM;
    Form.nChannels = 1 + m_s.m_hw.m_channels;
    Form.wBitsPerSample = 16 - m_8bps * 8;
    Form.nSamplesPerSec = m_srate;
    Form.nBlockAlign = Form.nChannels * (Form.wBitsPerSample >> 3);
    Form.nAvgBytesPerSec = Form.nSamplesPerSec * Form.nBlockAlign;
    Form.cbSize = sizeof (WAVEFORMATEX);
    POSITION
      pos = GetFirstViewPosition ();
    CView *
      pFirstView = GetNextView (pos);
    if (waveInOpen
	(&m_WavIn, m_s.m_hw.m_cardnum, &Form, (DWORD) pFirstView->m_hWnd, 0,
	 CALLBACK_WINDOW)) {
      AfxMessageBox (IDS_WAVERR);
      //m_mmb->MessageBox(IDS_WAVERR);
      m_WavIn = 0;
      return FALSE;
    }

    TRACE ("WavInOpen\n");
    AddBuffer ();
    waveInStart (m_WavIn);
    m_enablesound = TRUE;
    return TRUE;
  }
  else if (m_WavIn) {
    waveInReset (m_WavIn);

    while (waveInClose (m_WavIn) != MMSYSERR_NOERROR);
    Sleep (100);

    m_WavIn = 0;
    return TRUE;
  }
  return FALSE;
}

/* ---------------------------------------------------------------------- 
   This routine sets up the POCSAG virtual device driver for the serial port.
   It assigns interrupt, portaddress and operation mode.
*/
BOOL CPex32Doc::InitSerial (void)
{
  WORD
  portlist[] = { 0x3f8, 0x2f8, 0x3e8, 0x2e8 };
  WORD
  irqlist[] = { 3, 4, 5, 7, 9, 10, 11, 12 };
  config_t
    cfg;

  cfg.port = portlist[m_s.m_hw.m_port];
  cfg.irq = irqlist[m_s.m_hw.m_int];
  cfg.correct_bits = m_s.m_hw.m_errcor * 2;

  poc_config (&cfg);

  if (!poc_activate (m_s.m_hw.m_usecom))
    if (m_s.m_hw.m_usecom) {
      AfxMessageBox (IDS_PORTERR);
      //m_mmb->MessageBox(IDS_PORTERR);
      m_s.m_hw.m_usecom = 0;
      return FALSE;
    }
    else
      return TRUE;

  WORD
    baud = bitrate (m_s.m_dec.m_bitrate);

  switch (m_s.m_dec.m_bitrate) {
  case 0:
    m_baudrate_mask = 4;
    break;			// 2400 Bit/s
  case 1:
    m_baudrate_mask = 2;
    break;			// 1200 Bit/s
  case 2:
    m_baudrate_mask = 1;
    break;			//  512 Bit/s
  case 3:
    m_baudrate_mask = 7;
    break;			// Auto
  }
  poc_setmode (baud, m_s.m_enc.m_txdelay,
	       (m_s.m_hw.m_rxline << 2) | (m_s.m_enc.m_pttinv << 1) | m_s.
	       m_enc.m_txinv, m_s.m_hw.m_debug, m_s.m_hw.m_syncword);
  poc_setrx ();
  return TRUE;
}

/* ---------------------------------------------------------------------- 
   This is the main entry for all Initializations. It can be called more than once
   to change settings, parameters etc. at runtime. InitHardware collects all WavIn 
   capable devices with their 'friendly name' in a string array. So the user is
   able to select the desired one.
   When running WinNT it's not possible using the COM-port decoder. In this case it 
   will be switched off.
*/

BOOL CPex32Doc::InitHardware (void)
{
  static BOOL
    done;
  WAVEINCAPS
    devcaps;
  int
    i;

  if (!done) {
    OSVERSIONINFO
      OsVer;
    done = TRUE;

    /* Allocate memory for sampling buffers needed by the multimedia WavIn
       Device.
     */
    for (i = 0; i < _BUFMAX; i++)
      if ((m_DataBuf[i] = (LPSTR) malloc (_BUFLEN)) != NULL)
	m_Alloctable[i] = FALSE;
      else
	m_Alloctable[i] = TRUE;

    /* Collect WavIn Devices
     */
    for (i = 0; (i < (int) waveInGetNumDevs ()) && (i < 8); i++)
      if (waveInGetDevCaps (i, &devcaps, sizeof (devcaps)) ==
	  MMSYSERR_NOERROR) {
	m_s.m_hw.m_sndstr[i] = devcaps.szPname;
      }
      else
	TRACE ("\nNo Wave In Devices found!\n");

    if (i && ((m_s.m_hw.m_cardnum == -1) || (m_s.m_hw.m_cardnum > i)))
      m_s.m_hw.m_cardnum = 0;

    /* We will only open the COM-port driver when running Win95.
     */
    OsVer.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
    GetVersionEx (&OsVer);
    if (OsVer.dwPlatformId != VER_PLATFORM_WIN32_WINDOWS) {
      /*
         AfxMessageBox(IDS_WINNT);

         TRACE("Running Windows NT");
       */
      m_s.m_hw.m_usecom = FALSE;
    }
    else if (!open_device ()) {
      AfxMessageBox (IDS_NOVXD);
      //m_mmb->MessageBox(IDS_NOVXD);
    }
    else if (poc_getversion () != VERSION) {
      AfxMessageBox (IDS_WRONGVXD);
      //m_mmb->MessageBox(IDS_WRONGVXD);
      close_device ();
    }
  }

  /* Now set the decoder parameters according to users desire
   */
  m_do_filter = m_s.m_hw.m_firflt;
  m_correct_bits = 2 * m_s.m_hw.m_errcor;
  InitWavIn (m_s.m_hw.m_usesndcrd);

  /* re-initialize dcd variable to prevent a dcd-signal on a switched off
     channel.
   */
  m_rx_512l.dcd = m_rx_1200l.dcd = m_rx_2400l.dcd =
    m_rx_512r.dcd = m_rx_1200r.dcd = m_rx_2400r.dcd = DCD_MOSTNEGATIVE;
  m_medleftch = m_medrightch = 0;

  /* InitSerial and all other POC device driver functions may be called even
     the driver is not loaded, this will cause no harm.
   */
  return InitSerial ();
}

/* ---------------------------------------------------------------------- 
   Will close all devices and free all allocated buffers 
*/

BOOL CPex32Doc::OnShutdown ()
{
  int
    i;
  TRACE ("Clean Up\n");
  StopListening ();
  /* shut down all WavIn activities
   */
  InitWavIn (FALSE);

  for (i = 0; i < _BUFMAX; i++)
    free (m_DataBuf[i]);

  /* Stop and close COM-Port driver 
   */
  poc_activate (0);
  close_device ();
  m_alias.SaveAliases (m_homedir+"Aliases.txt");
  delete
    m_mmb;
  return TRUE;
}

/* ---------------------------------------------------------------------- 
   Timer routine, called every 100ms.
*/
void
CPex32Doc::OnTimer (UINT nIDEvent)
{
  static BOOL rec = FALSE;
  time_t t = time (NULL);
  if (m_sg.m_lmn.m_autosave && m_sg.m_lmn.m_autosavenum
      && (t - m_last_saved) > (m_sg.m_lmn.m_autosavenum * 60)) {
    if (!m_lastlistname.IsEmpty () && m_mainfrm) {
      PostMessage (m_mainfrm->m_hWnd, WM_COMMAND, ID_FILE_SAVE, 0);
      TRACE ("AutoSave\n");
      m_last_saved = t;
    }
  }
  /* Do COM-port polling if comport decoding is enabled.
   */
  if (!rec) {
    if (m_s.m_hw.m_usecom)
      CyclicUpdate ();

    /* Display the audio level bars.
     */
    if (m_mainfrm && m_mainfrm->m_levelvis) {
      m_mainfrm->m_LevelProg1.SetPos (m_medleftch);
      m_mainfrm->m_LevelProg2.SetPos (m_medrightch);
    }
  }
}

/* --------------------------------------------------------------------------
   Wrapper for POC device driver functions
   ---------------------------------------------------------------------------
*/
int
CPex32Doc::open_device (void)
{
  m_hCVxD = CreateFile ("\\\\.\\POC.VXD", 0, 0, 0,
			CREATE_NEW, FILE_FLAG_DELETE_ON_CLOSE, 0);

  return m_hCVxD != INVALID_HANDLE_VALUE;
}

/* ---------------------------------------------------------------------- */
void
CPex32Doc::close_device (void)
{
  if (m_hCVxD != INVALID_HANDLE_VALUE)
    CloseHandle (m_hCVxD);
  m_hCVxD = INVALID_HANDLE_VALUE;
}

/* ---------------------------------------------------------------------- */
WORD CPex32Doc::poc_getdcd (void)
{
  WORD
    ret = 0;
  if (INVALID_HANDLE_VALUE != m_hCVxD)
    DeviceIoControl (m_hCVxD, api_getdcd, NULL, 0, &ret, sizeof (ret), NULL,
		     NULL);
  return ret;
}

/* ---------------------------------------------------------------------- */
WORD CPex32Doc::poc_getready (void)
{
  WORD
    ret = 1;
  if (INVALID_HANDLE_VALUE != m_hCVxD)
    DeviceIoControl (m_hCVxD, api_getready, NULL, 0, &ret, sizeof (ret), NULL,
		     NULL);
  return ret;
}

/* ---------------------------------------------------------------------- */
WORD CPex32Doc::poc_getptt (void)
{
  WORD
    ret = 0;
  if (INVALID_HANDLE_VALUE != m_hCVxD)
    DeviceIoControl (m_hCVxD, api_getptt, NULL, 0, &ret, sizeof (ret), NULL,
		     NULL);
  return ret;
}

/* ---------------------------------------------------------------------- */
void
CPex32Doc::poc_setrx (void)
{
  if (INVALID_HANDLE_VALUE != m_hCVxD)
    DeviceIoControl (m_hCVxD, api_setrx, NULL, 0, NULL, 0, NULL, NULL);
}

/* ---------------------------------------------------------------------- */
void
CPex32Doc::poc_setmode (WORD baud, WORD txdel, WORD inv, WORD deb,
			DWORD syncword)
{
  pocfg_t cfg;
  cfg.baud = baud;
  cfg.txdel = txdel;
  cfg.inv = inv;
  cfg.deb = deb;
  cfg.syncword = syncword;
  if (INVALID_HANDLE_VALUE != m_hCVxD)
    DeviceIoControl (m_hCVxD, api_setmode, &cfg, sizeof (pocfg_t), NULL, 0,
		     NULL, NULL);
}

/* ---------------------------------------------------------------------- */
void
CPex32Doc::poc_copyrxb (batch_t * buf)
{
  if (INVALID_HANDLE_VALUE != m_hCVxD)
    DeviceIoControl (m_hCVxD, api_copyrxb, NULL, 0, buf, 0, NULL, NULL);
}

/* ---------------------------------------------------------------------- */
WORD CPex32Doc::poc_config (config_t * buf)
{
  WORD
    ret = 1;
  if (m_hCVxD != INVALID_HANDLE_VALUE)
    DeviceIoControl (m_hCVxD, api_config, buf, 0, &ret, sizeof (ret), NULL,
		     NULL);
  return ret;
}

/* ---------------------------------------------------------------------- */
WORD CPex32Doc::poc_startirq (txbatch_t * b)
{
  WORD
    ret = 0;
  if (INVALID_HANDLE_VALUE != m_hCVxD)
    DeviceIoControl (m_hCVxD, api_startirq, b, sizeof (txbatch_t), &ret,
		     sizeof (ret), NULL, NULL);
  return ret;
}

/* ---------------------------------------------------------------------- */
WORD CPex32Doc::poc_getstate (void)
{
  WORD
    ret = 0;
  if (INVALID_HANDLE_VALUE != m_hCVxD)
    DeviceIoControl (m_hCVxD, api_getstate, NULL, 0, &ret, sizeof (ret), NULL,
		     NULL);
  return ret;
}

/* ---------------------------------------------------------------------- */
WORD CPex32Doc::poc_getversion (void)
{
  WORD
    ret = 0;
  if (INVALID_HANDLE_VALUE != m_hCVxD)
    DeviceIoControl (m_hCVxD, api_getversion, NULL, 0, &ret, sizeof (ret),
		     NULL, NULL);
  return ret;
}

/* ---------------------------------------------------------------------- */
WORD CPex32Doc::poc_activate (WORD buf)
{
  WORD
    ret = 1;
  if (INVALID_HANDLE_VALUE != m_hCVxD)
    DeviceIoControl (m_hCVxD, api_activate, &buf, 0, &ret, sizeof (ret), NULL,
		     NULL);
  return ret;
}

/* ---------------------------------------------------------------------- */
WORD CPex32Doc::poc_getpnp (void)
{
  WORD
    ret = 0;
  if (INVALID_HANDLE_VALUE != m_hCVxD)
    DeviceIoControl (m_hCVxD, api_getpnp, NULL, 0, &ret, sizeof (ret), NULL,
		     NULL);
  return ret;
}

/* -----------------------------------------------------------------------------
   Basic POCSAG decoder functions for WavIn device
   -----------------------------------------------------------------------------
*/
#ifdef DEBUG
/*
  In Debug mode this output TRACE messages.
*/
void
CPex32Doc::xprintf (int verb_level, const char *fmt, ...)
{
  static char buffer[1024];
  va_list args;

  va_start (args, fmt);
  if (verb_level <= m_verbose_level) {
    vsprintf (buffer, fmt, args);
    TRACE (buffer);
  }
  va_end (args);
}
#endif
/* ---------------------------------------------------------------------- 
   See if a dcd is recognized in any DPLL of the WavIn Device
*/
BOOL CPex32Doc::poc_getsnddcd (void)
{
  if (m_s.m_hw.m_usesndcrd && m_enablesound)
    return (m_rx_512l.dcd > 0) || (m_rx_1200l.dcd > 0) || (m_rx_2400l.dcd > 0)
      || (m_rx_512r.dcd > 0) || (m_rx_1200r.dcd > 0) || (m_rx_2400r.dcd > 0);
  return FALSE;
}

/* ---------------------------------------------------------------------- 
   Produce even_parity bit of a POCSAG codeword
*/
inline unsigned char
CPex32Doc::even_parity (unsigned long data)
{
  unsigned int temp = data ^ (data >> 16);

  temp = temp ^ (temp >> 8);
  temp = temp ^ (temp >> 4);
  temp = temp ^ (temp >> 2);
  temp = temp ^ (temp >> 1);
  return temp & 1;
}

/* ---------------------------------------------------------------------- 
  Calculate CRC according to POCSAG specification, this is needed
  when generating POCSAG codewords for transmitting.
*/
unsigned long
CPex32Doc::crc (unsigned long data)
{
  unsigned long ret = data << (BCH_N - BCH_K), shreg = ret;
  unsigned long mask = 1L << (BCH_N - 1), coeff = BCH_POLY << (BCH_K - 1);
  int n = BCH_K;

  for (; n > 0; mask >>= 1, coeff >>= 1, n--)
    if (shreg & mask)
      shreg ^= coeff;
  ret ^= shreg;
  ret = (ret << 1) | even_parity (ret);
#ifdef DEBUG
  xprintf (9, "BCH coder: data: %08lx shreg: %08lx ret: %08lx\n",
	   data, shreg, ret);
#endif
  return ret;
}

/* ---------------------------------------------------------------------- 
   Calculate the syndrome vector, which us used to correct up to 2-bit errors.
   The syndrome vector is used to get the number of bits to correct.
*/
unsigned int
CPex32Doc::pocsag_syndrome (unsigned long data)
{
  unsigned long shreg = data >> 1;	/* throw away parity bit */
  unsigned long mask = 1L << (BCH_N - 1), coeff = BCH_POLY << (BCH_K - 1);
  int n = BCH_K;

  for (; n > 0; mask >>= 1, coeff >>= 1, n--)
    if (shreg & mask)
      shreg ^= coeff;
  if (even_parity (data))
    shreg |= (1 << (BCH_N - BCH_K));
#ifdef DEBUG
  xprintf (9, "BCH syndrome: data: %08lx syn: %08lx\n", data, shreg);
#endif
  return shreg;
}

/* ---------------------------------------------------------------------- 
   This routine is used to check a 32 bit POCSAG codeword. It will return
   zero if there was no error or a correctable error. Otherwise it will
   return a value different from 0.
   Note: The number of bits which can be corrected depends on the user defined
   preset m_correct_bits. (which can be max. 2)
*/
unsigned int
CPex32Doc::pocsag_correct (unsigned long *data)
{
  unsigned int syn = pocsag_syndrome (*data);
#ifdef SYNDROME_TABLEN
  unsigned short tab;
  unsigned long corrmask;

  syn &= SYNDROME_MASK;
  tab = syndrome_table[syn];
  if ((tab & SYNTAB_ERRNUMMASK) > m_correct_bits)
    return 1;
  corrmask = (1U << ((tab >> SYNTAB_BITPOS1) & SYNTAB_BITMASK)) ^
    (1U << ((tab >> SYNTAB_BITPOS2) & SYNTAB_BITMASK));
#ifdef DEBUG
  if (syn)
    xprintf (8, "BCH syndrome: data: %08lx syn: %08lx err: %d "
	     "corr: %08lx\n", *data, syn,
	     tab & SYNTAB_ERRNUMMASK, *data ^ corrmask);
#endif
  *data ^= corrmask;
  return 0;
#else /* SYNDROME_TABLEN */
  return !!syn;
#endif /* SYNDROME_TABLEN */
}

/* ---------------------------------------------------------------------- 
   This is an universal decoder, which receives only one bit. It will use
   the pocsag_rx structure to store the state of the decoder machine.
*/
void
CPex32Doc::do_one_rxbit (pocsag_rx_t * rx, unsigned char rxbit)
{
  rx->rx_data <<= 1;		//collect new bit
  if (rxbit ^ m_invert_rx)
    rx->rx_data |= 1;
  else
    rx->rx_data &= ~1;

  rx->rx_bit = (rx->rx_bit + 1) & 31;	//increment bitcounter modulo 32

  if (!rx->rx_sync && rx->b.p)	//if sync is lost start decoding
  {
    TRACE ("Decode Message\n");
    decode_msg (rx);
  }

  if (!rx->rx_sync && ((rx->rx_data == m_s.m_hw.m_syncword)
		       || (rx->rx_data == ~m_s.m_hw.m_syncword))) {
    if (rx->rx_data == ~m_s.m_hw.m_syncword)	//Adapt to polarity of data signal
      m_invert_rx ^= 1;
    rx->rx_word = rx->rx_bit = 0;	//SYNC OK, begin reception
    rx->rx_sync = 2;
    return;
  }

  if (rx->rx_sync && !rx->rx_bit)	//process one dataword
  {
    if (pocsag_correct (&rx->rx_data))	//codeword not ok
      rx->rx_sync--;		//decrease sync counter. 

    rx->rx_word++;		//increment codeword counter
    if (rx->rx_word == 17)	//check for syncword
    {
      if (rx->rx_data != m_s.m_hw.m_syncword)	//if we have no syncword here
	if (rx->rx_sync)
	  rx->rx_sync--;	//decrease sync counter

      rx->rx_word = 0;		//clear rxdata word
      return;			//never store syncwords 
    }

    if (rx->b.p < 2048)
      rx->b.b[rx->b.p++] = rx->rx_data;	//fill databuffer
  }
}

/* ---------------------------------------------------------------------- 
   This is an universal DPLL (Digital Phase Locked Loop) which processes just
   one bit of the data stream. All parameters and states are stored in the
   pocsag_rx structure.
*/
inline void
CPex32Doc::do_one_demodulator (pocsag_rx_t * rx, unsigned char this_sample)
{
  if (this_sample != rx->last_sample) {
    int diff = ((int) rx->phase) - 0x8000 - ((int) rx->ph_update / 2);

    if (diff > ((int) rx->ph_update / 4))
      rx->phase -= rx->ph_update / 2;
    else if (diff < (-(int) rx->ph_update / 4))
      rx->phase += rx->ph_update / 2;

    if (abs (diff) > DCD_TOLERANCE) {
      if (rx->dcd > 0 && (rx->dcd - DCD_NEGCHANGE) <= 0)
	rx->dcd -= DCD_NEGTHRESHOLD;
      else
	rx->dcd -= DCD_NEGCHANGE;
      if (rx->dcd < DCD_MOSTNEGATIVE)
	rx->dcd = DCD_MOSTNEGATIVE;
    }
    else {
      if (rx->dcd < 0 && (rx->dcd + DCD_POSCHANGE) >= 0)
	rx->dcd += DCD_POSTHRESHOLD;
      else
	rx->dcd += DCD_POSCHANGE;
      if (rx->dcd > DCD_MOSTPOSITIVE)
	rx->dcd = DCD_MOSTPOSITIVE;
    }
  }
  rx->last_sample = this_sample;
  rx->phase += rx->ph_update;
  if (rx->phase >= 0x10000)
    do_one_rxbit (rx, this_sample);
  rx->phase &= 0xffff;
}

/* ---------------------------------------------------------------------- 
   Calculate the FIR filter on one sample. Such a filter does not make sense
   if the sampling rate is less than 10Khz. Using higher sampling rates with
   unfiltered baseband audio IF signal parts may disturb decoding. Therefor
   it is recommended using the FIR filter.
*/
inline void
CPex32Doc::do_one_filter (pocsag_rx_t * rx, const char coeffs[], short sample)
{
  int sum;

  memmove (rx->filter + 1, rx->filter, sizeof (rx->filter) - sizeof (short));
  rx->filter[0] = sample;
  sum = ((rx->filter[0] + rx->filter[15]) * coeffs[0] +
	 (rx->filter[1] + rx->filter[14]) * coeffs[1] +
	 (rx->filter[2] + rx->filter[13]) * coeffs[2] +
	 (rx->filter[3] + rx->filter[12]) * coeffs[3] +
	 (rx->filter[4] + rx->filter[11]) * coeffs[4] +
	 (rx->filter[5] + rx->filter[10]) * coeffs[5] +
	 (rx->filter[6] + rx->filter[9]) * coeffs[6] +
	 (rx->filter[7] + rx->filter[8]) * coeffs[7]);
  //do_one_demodulator(rx, sum > 0);
  do_one_demodulator (rx, GetBit (sum, rx->channel));
}

/* ---------------------------------------------------------------------- 
   Transforms one sample to one bit. This function simulates a comparator
   with a userdefined hysteresis.
*/
BOOL CPex32Doc::GetBit (int val, BOOL ch)
{
  static BOOL
    bit[2];
  if (abs (val) >= m_hyst)
    bit[ch] = val >= 0;

  return bit[ch];
}

/* ---------------------------------------------------------------------- 
   This function is called whenever there is a buffer of samples ready for
   beiing processed. 
*/
void
CPex32Doc::demodulator (LPSTR sound_buffer)
{
  short *bp = (short *) sound_buffer;
  unsigned char *cb = (unsigned char *) sound_buffer;
  int len = _BUFLEN / sizeof (short), i;
  static unsigned char bitl, bitr;
  pocsag_rx_t *rx;
  BOOL chr;
  BOOL ch = m_s.m_hw.m_channels;
  BOOL bit;
  int val;

  len <<= m_8bps;

  m_medleftch = 0;
  m_medrightch = 0;

  for (i = 0; i < len; cb++, bp++, i++) {
    /* Transform 8bit samples into 16bit ones, so the FIR filter will
       calculate more exactly.
     */
    if (!m_8bps)
      val = *bp;
    else
      val = ((*cb) << 8) - 32768;

    /* determine which channel should be processed.
     */
    chr = ch && ((i & 1) ^ m_8bps);

    /* Update the audiolevel peak.
     */
    if (chr)
      m_medrightch = max (m_medrightch, abs (val));
    else
      m_medleftch = max (m_medleftch, abs (val));

    /* Decode one bit.
     */
    bit = GetBit (val, chr);

    /* 512Bit/s Decoder 
     */
    if (m_baudrate_mask & 1) {
      if (chr)
	rx = &m_rx_512r;
      else
	rx = &m_rx_512l;

      if (m_do_filter)
	do_one_filter (rx, m_filter_coeffs_512, val);
      else
	do_one_demodulator (rx, bit);
    }
    /* 1200Bit/s Decoder 
     */
    if (m_baudrate_mask & 2) {
      if (chr)
	rx = &m_rx_1200r;
      else
	rx = &m_rx_1200l;

      if (m_do_filter)
	do_one_filter (rx, m_filter_coeffs_1200, val);
      else
	do_one_demodulator (rx, bit);
    }
    /* 2400Bit/s Decoder 
     */
    if (m_baudrate_mask & 4) {
      if (chr)
	rx = &m_rx_2400r;
      else
	rx = &m_rx_2400l;

      if (m_do_filter)
	do_one_filter (rx, m_filter_coeffs_2400, val);
      else
	do_one_demodulator (rx, bit);
    }
  }
#ifdef DEBUG
  xprintf (10, "\n");
  if (m_baudrate_mask & 7) {
    if (m_baudrate_mask & 1)
      xprintf (3, "512: DCD: %c  ", (m_rx_512l.dcd > 0) ? 'D' : '-');
    if (m_baudrate_mask & 2)
      xprintf (3, "1200: DCD: %c  ", (m_rx_1200l.dcd > 0) ? 'D' : '-');
    if (m_baudrate_mask & 4)
      xprintf (3, "2400: DCD: %c  ", (m_rx_2400l.dcd > 0) ? 'D' : '-');
    xprintf (3, "\n");
  }
#endif
}

/* ---------------------------------------------------------------------- 
   High Level Decoder Functions

   Convert a POCSAG dataword as numeric message.
*/
void
CPex32Doc::five2text (unsigned long d, char *msg, BOOL & bad)
{
  static char *chtab = "084 2.6]195-3U7[";
  int i;

  for (i = 0; i < 5; i++)
    switch ((msg[i] = chtab[(d >> (((4 - i) << 2)) & 15)])) {
    case 'U':
    case '-':
    case '[':
    case ']':
    case '.':
      bad = TRUE;
      break;
    }
}

/* ---------------------------------------------------------------------- 
   Decode POCSAG datawords as one numeric message.
*/
int
CPex32Doc::num2text (unsigned long *t, int imax, char *msg, BOOL & bad)
{
  int i;
  BOOL cnt = !bad;

  bad = FALSE;


  for (i = 0; (i < 24) && (i < imax); i++) {
    if (pocsag_correct (&t[i])) {
      if (i && cnt)
	m_msgerr++;
      break;
    }
    if (!(t[i] & 0x80000000))
      break;


    five2text (t[i] >> 11, msg + i * 5, bad);
  }

  msg[i * 5] = 0;

  if (i) {
    if (cnt)
      m_msgrx++;
    return i - 1;
  }
  else
    return 0;
}

/* ---------------------------------------------------------------------- 
   Get bit in an array of unsigned longs
*/
int
CPex32Doc::getbit (unsigned long *s, unsigned bit)
{
  unsigned startframe = bit / 20, startbit = bit - startframe * 20;
  return !!(s[startframe] & (0x40000000L >> startbit));
}

/* ---------------------------------------------------------------------- 
   Basic function to convert a POCSAG dataword into characters
*/
char
CPex32Doc::num2char (unsigned long *s, unsigned ch)
{
  unsigned i;
  char ret = 0;
  for (i = 0; i < 7; i++)
    ret |= getbit (s, ch * 7 + i) * (1 << i);
  return ret;
}

/* ---------------------------------------------------------------------- 
   Decode POCSAG datawords as alpha-message
*/
int
CPex32Doc::str2text (unsigned long *t, int imax, char *out, BOOL mode)
{
  int i, j, len;
  char c = 32, *msg = out;

  for (i = 0; /*(i<42)&& */ (i < imax); i++) {
    if (pocsag_correct (&t[i])) {
      if (i)
	m_msgerr++;
      break;
    }
    if (!(t[i] & 0x80000000))
      break;
  }

  len = i * 20 / 7;

  for (j = 0; j < len; j++)
    msg += sprintf (msg, m_transtbl[(num2char (t, j) - mode) & 0xff]);

  if (i) {
    m_msgrx++;
    return i - 1;
  }
  else
    return 0;
}

/* ---------------------------------------------------------------------- 
   Main function to decode a buffer of raw POCSAG codewords
*/
void
CPex32Doc::decode_msg (pocsag_rx_t * rx)
{
  batch_t buf;
  CMsg m;
  char msg[_MAXMSGLEN];
  BOOL bad = FALSE;
  batch_t *b;
  int fct = -1, func = -1, i;
  DWORD d, e, adr;

  /* If there is no pocsag_rx structure defined decode_msg must have been 
     called by Timer
   */
  if (rx == NULL) {
    /* Get databuffer from poc driver.
     */
    poc_copyrxb (&buf);
    b = &buf;
  }
  else
    b = &rx->b;


  /* process all datawords.
   */
  for (i = 0; i < b->p; i++) {
    switch ((d = b->b[i])) {
      /* If IDLE word, do nothing.
       */
    case _IDLE:
      break;
    default:
      if (!pocsag_correct (&d))
	switch ((d & 0x80000000) >> 31) {
	  /* process address word of POCSAG data
	   */
	case 0:
	  fct = (d >> 11L) & 3;
	  func = m_s.m_dec.m_fct[fct];
	  adr = ((d >> 10) & 0x7ffff8) + ((i & 15) >> 1);

	  /* addresses < 16 are not allowed
	   */
	  if (adr < 16)
	    break;
	  /* preset message structure with source
	     information
	   */
	  m.m_adr = adr;
	  m.m_fct = fct;
	  m.m_func = func;
	  m.m_type = m_s.m_type;
	  m.m_time = 0;

	  /* If from WavIn device determine channel
	   */
	  if (rx)
	    m.m_type |= (rx->channel + 1) << 4;

	  m.m_bitrate = bitrate (b->br);

	  /* process BEEPs (without message)
	   */
	  if (func == BEEP) {
	    m.m_func = BEEP;
	    m.m_msg.Empty ();
	    AddToList (m);
	    m_msgrx++;
	    func = -1;

	  }
	  else			// Begin auto detection of messagetye
	  if ((func == AUTO) && ((i + 1) < b->p)) {
	    e = b->b[i + 1];
	    if (!pocsag_correct (&e))
	      if (!(e & 0x80000000)) {
		m.m_func = BEEP;
		m.m_msg.Empty ();
#ifdef DEBUG
		m.m_msg.Format ("%x %x", d, pocsag_correct (&d));
#endif
		AddToList (m);
		m_msgrx++;
		func = -1;
	      }
	  }
	  break;

	case 1:		//Process data field of POCSAG data
	  switch (func) {
	  case AUTO:		//continue auto detection of messagetype    
	    bad = TRUE;
	    num2text (b->b + i, b->p - i, msg, bad);
	    if (bad || (strlen (msg) > 20)) {
	      m.m_func = ALPHA;
	      goto alpha;
	    }
	    m.m_func = NUM;
	  case NUM:		//Decode numeric messages
	    bad = FALSE;
	    i += num2text (b->b + i, b->p - i, msg, bad);
	    m.m_msg = msg;
	    AddToList (m);
	    func = -1;
	    //fct=-1;
	    break;
	    //Martina Sieber 79369016
	  case ALPHA:		//Decode alpha message
	  alpha:;
	    {
	      BOOL skyper = (adr >= 4500) && (adr <= 4600)
		&& m_s.m_dec.m_skyper;
	      i += str2text (b->b + i, b->p - i, msg, skyper);

	      if (skyper) {
		//if(adr==4512)
		if (msg[0] == 0x30)
		  m.m_msg.Format ("Skyper 0x%02X Board   0x%02X %s",
				  msg[1] & 255, msg[2] & 255, msg + 3);
		else
		  m.m_msg.Format ("Skyper 0x%02X Message 0x%02X %s",
				  msg[0] & 255, msg[1] & 255, msg + 2);
		AddToList (m);
	      }
	      else {
		m.m_msg = msg;
		AddToList (m);
	      }
	      func = -1;
	    }
	    break;
	  }			//switch(fct)
	  break;
	}			//switch((d&0x80000000)>>31)
    }				//switch((d=rxb[i]))
  }				//for(i=0;(i<rxp)&&!kbhit();i++)

  b->p = 0;
  //Send Message to View Framework for updating the list window.
  //PostMessage(WM_COMMAND,WM_UPDATE);
  UpdateAllViews (NULL);
}

/* ---------------------------------------------------------------------- 
   This routine handles the POC device driver polling. It stops polling 
   while POC is transmitting.
*/
void
CPex32Doc::CyclicUpdate (void)
{
  static BOOL state1, state2;

  if (!poc_getstate () && state2)
    ::SendMessage (AfxGetApp ()->m_pMainWnd->m_hWnd, WM_COMMAND, WM_SETPREFS,
		   0);
  else if (poc_getdcd () != state1) {
    state1 = poc_getdcd ();
    if (!state1)
      decode_msg (NULL);
  }
  state2 = poc_getstate ();
}

/* ---------------------------------------------------------------------- 
   Converts a short bitrate into 'friendly' bitrate or reverse
*/
unsigned
CPex32Doc::bitrate (unsigned u)
{
  unsigned ret;
  switch (u) {
  case 0:
    ret = 2400;
    break;
  case 1:
    ret = 1200;
    break;
  case 2:
    ret = 512;
    break;
  case 3:
    ret = 0;
    break;
  case 2400:
    ret = 0;
    break;
  case 1200:
    ret = 1;
    break;
  case 512:
    ret = 2;
    break;
  }
  return ret;
}

/* ---------------------------------------------------------------------- 
   POCSAG TX-routines

   poc_checkdata converts a POCSAG data buffer before transmitting into
   internal poc device driver data structure  tx_batch
*/
int
CPex32Doc::poc_checkdata (unsigned baud, unsigned long *d, int len)
{
  static txbatch_t buf;

  long i, j;


  if (!poc_getready ())
    return 0;

  for (i = 0; i < len; i++)
    buf.b[(i >> 4)][i & 15] = d[i];

  for (j = i; j < (_MAXTXBATCHES << 4); j++)
    buf.b[(j >> 4)][j & 15] = _IDLE;

  buf.baud = baud;

  if (len)
    poc_startirq (&buf);

  return len;
}

/* ---------------------------------------------------------------------- 
   Prefill POCSAG data with IDLE words. All unused positions of a data buffer
   contain IDLE words.
*/
void
CPex32Doc::idlefill (unsigned long *b, unsigned len)
{
  unsigned j;
  for (j = 0; j < len; j++)
    b[j] = _IDLE;
}

/* ---------------------------------------------------------------------- 
   Prepare a data buffer for beep message.
*/
int
CPex32Doc::poc_beep (unsigned baud, unsigned long adr, unsigned function)
{
  unsigned long buffer[16];
  if (adr > 0x1fffffLU)
    return 0;

  idlefill (buffer, sizeof (buffer) >> 2);
  buffer[((adr & 7) << 1)] = crc (((adr >> 1) & 0x1ffffcLU) | (function & 3));

  while (!poc_getready ());

  poc_checkdata (baud, buffer, sizeof (buffer) >> 2);
  return 1;
}

/* ---------------------------------------------------------------------- 
   Convert ASCII numbers into POCSAG numbers (for numeric messages)
*/
unsigned long
CPex32Doc::fivetol (char *s)
{
  static unsigned long chtab[] = { 0, 8, 4, 12, 2, 10, 6, 14, 1, 9 };
  unsigned long ret = 0;
  unsigned i, j;

  for (i = 0; i < 5; i++) {
    j = (4 - i) << 2;
    switch (s[i]) {
    case 0:
    case ' ':
      ret |= 3L << j;
      break;
    case '-':
      ret |= 11L << j;
      break;
    case '[':
      ret |= 15L << j;
      break;
    case ']':
      ret |= 7L << j;
      break;
    case 'U':
      ret |= 13L << j;
      break;
    default:
      if ((s[i] > '0') && (s[i] <= '9'))
	ret |= chtab[s[i] - '0'] << j;
    }
  }

  return crc (ret | 0x100000UL);
}

/* ---------------------------------------------------------------------- 
   Prepare a data buffer for numeric message
*/
int
CPex32Doc::poc_numerik (unsigned baud, unsigned long adr, unsigned function,
			CString & s)
{
  unsigned long buffer[_MAXTXBATCHES << 4];
  unsigned i = 0, j;
  char msg[21];
  memset (msg, 0, sizeof (msg));
  _memccpy (msg, s, 0, sizeof (msg) - 1);

  if (adr > 0x1fffffLU)
    return 0;

  idlefill (buffer, sizeof (buffer) >> 2);
  buffer[(j = ((adr & 7) << 1))] =
    crc (((adr >> 1) & 0x1ffffcLU) | (function & 3));
  j++;
  if (msg[0])
    for (i = 0; i < (((strlen (msg) - 1) / 5) + 1); i++)
      buffer[j + i] = fivetol (msg + i * 5);

  while (!poc_getready ());

  poc_checkdata (baud, buffer, sizeof (buffer) >> 2);
  return 1;
}

/* ---------------------------------------------------------------------- 
   Get one bit of a character string
*/
int
CPex32Doc::getbit (char *s, unsigned bit)
{
  unsigned startbyte = bit / 7, startbit = bit - startbyte * 7;
  return !!(s[startbyte] & (1 << startbit));
}

/* ---------------------------------------------------------------------- 
   Pick some characters and put them into one POCSAG codeword
*/
unsigned long
CPex32Doc::getword (char *s, unsigned word)
{
  unsigned start = word * 20, i;
  unsigned long ret = 0;
  for (i = 0; i < 20; i++)
    ret |= getbit (s, start + i) * (0x80000LU >> i);
  return 0x100000LU | ret;
}

/* ---------------------------------------------------------------------- 
   Every alpha message has to be passed through the characeter translation
   table.
*/
char
CPex32Doc::txtbl (char c)
{
  for (int i = 0; i < 256; i++)
    if ((m_transtbl[i].GetLength () == 1) && m_transtbl[i][0] == c)
      return i;
  return c;
}

/* ---------------------------------------------------------------------- 
   Prepare a databuffer for alpha message
*/
int
CPex32Doc::poc_alphanum (unsigned baud, unsigned long adr, unsigned function,
			 CString & s)
{
  unsigned long buffer[_MAXTXBATCHES << 4];
  int i, j, l;
  char msg[121];

  for (i = 0; (i < s.GetLength ()) && (i < sizeof (msg)); i++)
    msg[i] = txtbl (s.GetAt (i));

  msg[i] = 0;

  l = strlen (msg);

  if (adr > 0x1fffffLU)
    return 0;

  idlefill (buffer, sizeof (buffer) >> 2);
  buffer[(j = ((adr & 7) << 1))] =
    crc (((adr >> 1) & 0x1ffffcLU) | (function & 3));
  j++;

  for (i = 0; i < (l * 7 / 20 + 1); i++)
    buffer[j + i] = crc (getword (msg, i));


  while (!poc_getready ());

  poc_checkdata (baud, buffer, sizeof (buffer) >> 2);
  return 1;
}

/* ---------------------------------------------------------------------- 
   Loads a character translation table from harddisk. This is the only
   possibility to give the user the freedom of using his (or her) own
   characterset. Think of arabic, russian or hebrew letters.
*/
BOOL CPex32Doc::LoadTransTbl (CString filename)
{
  int
    i,
    j = 0;
  char
    s[7],
    line[80],
    c;

  if (filename.IsEmpty ()) {
    FILE *
      f = fopen ("default.tbl", "wt");
    if (f == NULL)
      return FALSE;

    for (i = 0; i < 256; i++) {
      c = m_transtbl[i][0];
      if (c > 0 && isprint (c) && !isspace (c))
	fprintf (f, "0x%02X\t%s\n", i, m_transtbl[i]);
      else
	fprintf (f, "0x%02X\t<0x%02X>\n", i, c & 255);
    }

    fclose (f);
    return TRUE;
  }

  FILE *
    f = fopen (filename, "rt");
  if (f == NULL)
    return FALSE;

  while (!feof (f)) {
    fgets (line, 80, f);
    j++;
    switch (sscanf (line, "0x%x\t%6s", &i, s)) {
    case 2:
      if ((i >= 0) && (i < 256))
	if (!strncmp (s, "<0x", 3) && s[5] == '>') {
	  int
	    k;
	  s[5] = 0;
	  sscanf (s + 3, "%x", &k);
	  m_transtbl[i] = (char) k;
	}
	else
	  m_transtbl[i] = s;
      break;
    case 1:
      if ((i >= 0) && (i < 256))
	m_transtbl[i] = " ";
      break;
    case 0:
      {
	CString
	  s,
	  t;
	s.LoadString (IDS_FMTERR);
	t.Format (s, j);
	if (AfxMessageBox (t, MB_OKCANCEL) == IDCANCEL) {
	  fclose (f);
	  return FALSE;
	}
      }
      break;

    }
  }

  fclose (f);
  return TRUE;
}

BOOL CPex32Doc::OnStartup ()
{
  m_buferr = 0;
  m_msgerr = 0;
  m_msgrx = 0;
  m_mmb = new CMyMessageBox;

  if (!LoadTransTbl (m_tblname)) {
    if (firststart) {
      CString t;
      //s.LoadString(IDS_NOFILE);
      t.Format (IDS_NOFILE, m_tblname);
      //AfxMessageBox(t);
      m_mmb->MessageBox (t);
    }
    LoadTransTbl ("");
  }
  m_alias.LoadAliases (m_homedir+"Aliases.txt");

  if (m_sg.m_lmn.m_autoload && m_mainfrm && !m_lastlistname.IsEmpty ())
    PostMessage (m_mainfrm->m_hWnd, WM_COMMAND, ID_FILE_MRU_FILE1, 0);

  return TRUE;
}


void
CPex32Doc::StopListening (void)
{
  if (m_pListen != NULL) {
    m_pListen->Close ();
    delete m_pListen;
    Sleep (100);
    m_pListen = NULL;
  }
}

BOOL CPex32Doc::StartListening (void)
{
  BOOL
    bOk = FALSE;
  StopListening ();
  m_pListen = new CListenSocket (this);
  if (m_pListen) {
    if (m_pListen->Create (m_sg.m_opt.m_tcpipport, SOCK_STREAM, FD_ACCEPT))
      bOk = m_pListen->Listen ();

    if (!bOk) {
      CString
	strMsg;
      int
	nErr = m_pListen->GetLastError ();
      if (nErr == WSAEADDRINUSE)
	strMsg.Format (IDS_LISTEN_INUSE, m_sg.m_opt.m_tcpipport);
      else
	strMsg.Format (IDS_LISTEN_ERROR, m_sg.m_opt.m_tcpipport);

      AfxMessageBox (strMsg, MB_OK | MB_ICONSTOP);
      m_pListen->Close ();
      delete
	m_pListen;
      m_pListen = NULL;
    }
  }
  else
    AfxMessageBox (IDS_CANT_LISTEN, MB_OK | MB_ICONSTOP);

  return bOk;
}

/* ---------------------------------------------------------------------- 
   Yes we are aware of international date and time formats.
*/
void
CPex32Doc::datetimestr (LPTSTR Buf, int BufSize, time_t & unixtime)
{
  int ret;
  SYSTEMTIME st;
  struct tm *tt;

  tt = localtime (&unixtime);

  st.wYear = tt->tm_year + 1900;
  st.wMonth = tt->tm_mon + 1;
  st.wDayOfWeek = tt->tm_wday;
  st.wDay = tt->tm_mday;
  st.wHour = tt->tm_hour;
  st.wMinute = tt->tm_min;
  st.wSecond = tt->tm_sec;
  st.wMilliseconds = 0;

  ret =::GetDateFormat (LOCALE_USER_DEFAULT, DATE_SHORTDATE, &st, NULL,
			Buf, BufSize);
  strcat (Buf, " ");

  if (ret)
    ::GetTimeFormat (LOCALE_USER_DEFAULT, /*TIME_NOSECONDS*/0, &st, NULL,
		     Buf + ret, BufSize - ret - 1);
}
