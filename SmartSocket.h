#if !defined(AFX_SMARTSOCKET_H__493A5C13_645A_11D1_9DF4_0000CB280107__INCLUDED_)
#define AFX_SMARTSOCKET_H__493A5C13_645A_11D1_9DF4_0000CB280107__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SmartSocket.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSmartSocket command target

class CSmartSocket:public CAsyncSocket
{
// Attributes
public:

// Operations
public:
  CSmartSocket (CPex32Doc * pDoc);
  CSmartSocket ();
  virtual ~ CSmartSocket ();
  CPex32Doc *m_pDoc;
// Overrides
public:
  void OnLineComplete ();
  void pr (char *format, ...);
  void OnStartup (void);
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CSmartSocket)
public:
    virtual void OnReceive (int nErrorCode);
  virtual void OnClose (int nErrorCode);
  virtual void OnSend (int nErrorCode);
  //}}AFX_VIRTUAL

  // Generated message map functions
  //{{AFX_MSG(CSmartSocket)
  // NOTE - the ClassWizard will add and remove member functions here.
  //}}AFX_MSG

// Implementation
protected:
    BOOL m_LoggedIn;
  char m_RecvBuffer[10240];
  int m_rxcnt;
  int m_loginerr;
  int m_lastmsg;
  HANDLE m_thread_handle;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMARTSOCKET_H__493A5C13_645A_11D1_9DF4_0000CB280107__INCLUDED_)
