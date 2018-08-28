// SmartSocket.cpp : implementation file
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
#include "aliases.h"
#include "Listen.h"
#include "SmartSocket.h"
#include "MyMessageBox.h"
#include "Pex32Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CSmartSocket

CSmartSocket::CSmartSocket ()
{
}

CSmartSocket::CSmartSocket (CPex32Doc * pDoc)
{
  m_pDoc = NULL;
  m_loginerr = 0;
  m_pDoc = pDoc;
  m_LoggedIn = FALSE;
  m_rxcnt = 0;
  m_lastmsg = 0;
}

CSmartSocket::~CSmartSocket ()
{
}

// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP (CSmartSocket, CAsyncSocket)
  //{{AFX_MSG_MAP(CSmartSocket)
  //}}AFX_MSG_MAP
  END_MESSAGE_MAP ()
#endif // 0
/////////////////////////////////////////////////////////////////////////////
// CSmartSocket member functions
     void CSmartSocket::OnReceive (int nErrorCode)
{
  TRACE ("OnReceive called\n");
  char buf[1];
  int i;
  if ((i = Receive (buf, sizeof (buf))) > 0) {
    if (buf[0] == '\n' || buf[0] == '\r') {
      m_RecvBuffer[m_rxcnt] = 0;
      if (i)
	OnLineComplete ();
      m_rxcnt = 0;
    }
    else {
      if (m_rxcnt < (sizeof (m_RecvBuffer) - 1))
	m_RecvBuffer[m_rxcnt++] = buf[0];
      else {
	m_RecvBuffer[m_rxcnt] = 0;
	m_rxcnt = 0;
	OnLineComplete ();
      }
    }
  }
  CAsyncSocket::OnReceive (nErrorCode);
}

static void *
thread_routine (void *p)
{
  CSmartSocket *ss = (CSmartSocket *) p;
  while (1) {
    ss->OnSend (0);
    Sleep (100);
  }
}

void
CSmartSocket::OnStartup ()
{
  CWinApp *w = AfxGetApp ();
  AsyncSelect (FD_READ | FD_CLOSE);
  DWORD i;

  m_thread_handle =
    CreateThread (NULL, 0, (LPTHREAD_START_ROUTINE) thread_routine, this, 0,
		  &i);

    pr ("POC32 " APPVERSION " (" BUILD
	") Remote Access Interface\r\n\r\nPassword: ");

}

void
CSmartSocket::OnClose (int nErrorCode)
{
  TerminateThread (m_thread_handle, 0);
  CloseHandle (m_thread_handle);

  delete this;
  CAsyncSocket::OnClose (nErrorCode);
}

void
CSmartSocket::pr (char *format, ...)
{
  char cbuf[10240];
  va_list argpoint;

  va_start (argpoint, format);
  vsprintf (cbuf, format, argpoint);
  va_end (argpoint);
  Send (cbuf, strlen (cbuf));
}

void
CSmartSocket::OnLineComplete ()
{
  if (!m_LoggedIn) {
    if (!strcmp (m_RecvBuffer, m_pDoc->m_sg.m_opt.m_password)) {
      pr ("\r\nPassword accepted.\r\n");
      m_LoggedIn = TRUE;
    }
    else {
      m_loginerr++;
      Sleep (m_loginerr * 1000);
      pr ("\r\nPassword not accepted.\r\n");
      if (m_loginerr >= 1) {
	pr ("disconnecting.\r\n");
	Close ();
      }
      pr ("\r\nPassword: ");
      return;
    }
  }
  if (!_stricmp (m_RecvBuffer, "help")) {
    pr ("You may use the following commands:\r\n\r\n"
	"quit\r\n\r\nSorry that's all for now...\r\n");
  }

  if (!_stricmp (m_RecvBuffer, "quit"))
    Close ();
}

void
CSmartSocket::OnSend (int nErrorCode)
{
  if (m_LoggedIn) {
    char s[32];
    char t[_MAXMSGLEN * 3];

    while (m_lastmsg < m_pDoc->m_msg.GetSize ()) {
      CMsg & m = m_pDoc->m_msg[m_lastmsg];
      if (m.m_displayed) {
	m_pDoc->datetimestr (s, sizeof (s), m.m_time);
	sprintf (t,
		 "%s\t%-4.4s\t%-5.5s\t%7.7d\t%s\t%d (%-5.5s)\t%s\r\n",
		 s, m_pDoc->m_source[m.m_type >> 4],
		 m_pDoc->m_bitstr[m.m_bitrate], m.m_adr,
		 m_pDoc->m_alias.LookupAlias (m.m_adr), m.m_fct,
		 m_pDoc->m_funcstr[m.m_func], m.m_msg);
	pr (t);
      }
      m_lastmsg++;
    }

    if (m_lastmsg > m_pDoc->m_msg.GetSize ())
      m_lastmsg = 0;
  }
  CAsyncSocket::OnSend (nErrorCode);
}
