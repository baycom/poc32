// pex32.cpp : Defines the class behaviors for the application.
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
#include "winreg.h"
#include "License.h"
#include "TipDlg.h"

#include  <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL firststart;
/////////////////////////////////////////////////////////////////////////////
// CPex32App

BEGIN_MESSAGE_MAP (CPex32App, CWinApp)
  ON_COMMAND (CG_IDS_TIPOFTHEDAY, ShowTipOfTheDay)
  //{{AFX_MSG_MAP(CPex32App)
  //}}AFX_MSG_MAP
  // Standard file based document commands
  ON_COMMAND (ID_FILE_NEW, CWinApp::OnFileNew)
  ON_COMMAND (ID_FILE_OPEN, CWinApp::OnFileOpen)
  // Standard print setup command
  ON_COMMAND (ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
  END_MESSAGE_MAP ()
/////////////////////////////////////////////////////////////////////////////
// CPex32App construction
  CPex32App::CPex32App ()
{
  firststart = FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPex32App object

CPex32App theApp;

/////////////////////////////////////////////////////////////////////////////
// CPex32App initialization

BOOL CPex32App::InitInstance ()
{
  CString
    str;
  if (OpenMutex (MUTEX_ALL_ACCESS, FALSE, "Pocsag Explorer") == NULL)
    mutex = CreateMutex (NULL, TRUE, "Pocsag Explorer");
  else {
    ::PostMessage (HWND_BROADCAST, WM_COMMAND, WM_TOP, 0);
    return FALSE;
  }
#ifdef _PREVIEW
  {
    time_t
      t = time (NULL);
    struct tm *
      tm = localtime (&t);
    if (tm->tm_year != 97 || tm->tm_mon < 8 || tm->tm_mon > 9) {
      AfxMessageBox ("Sorry Demoversion is no longer valid");
      return FALSE;
    }
  }
#endif
  if (!AfxSocketInit ()) {
    AfxMessageBox (IDS_CANT_LISTEN);
    return FALSE;
  }
  // Standard initialization
  // If you are not using these features and wish to reduce the size
  //  of your final executable, you should remove from the following
  //  the specific initialization routines you do not need.

//  Enable3dControls ();		// Call this when using MFC in a shared DLL

  SetRegistryKey ("Flexnet");
  str = GetProfileString ("Settings", "Version", NULL);
  if (!str.IsEmpty ())
    WriteProfileInt ("poc32-Bar0", "BarDockOk", 1);

  m_pszRegistryKey = NULL;
  SetRegistryKey ("Mediasoft");
  str = GetProfileString ("Settings", "Version", NULL);

  if (str.IsEmpty ()) {
    RegDeleteKey (HKEY_CURRENT_USER, "Software\\FlexNet\\poc32\\poc32-Bar0");
    RegDeleteKey (HKEY_CURRENT_USER, "Software\\FlexNet\\poc32\\poc32-Bar1");
    RegDeleteKey (HKEY_CURRENT_USER, "Software\\FlexNet\\poc32\\poc32-Bar2");
    RegDeleteKey (HKEY_CURRENT_USER, "Software\\FlexNet\\poc32\\poc32-Bar3");
    RegDeleteKey (HKEY_CURRENT_USER,
		  "Software\\FlexNet\\poc32\\poc32-Summary");
  }

  if (GetProfileInt ("poc32-Bar0", "BarDockOk", 0)) {
    AfxMessageBox ("Sorry, freeware testing period is over!");
    return FALSE;
  }

  if (str != APPVERSION) {
    CLicense
      l;
    l.m_licstr.LoadString (IDS_LICSTR1);
    str.LoadString (IDS_LICSTR2);
    l.m_licstr += str;
    if (l.DoModal () == IDCANCEL)
      return FALSE;

    WriteProfileString ("Settings", "Version", APPVERSION);
    firststart = TRUE;
  }
  LoadStdProfileSettings ();	// Load standard INI file options (including MRU)

  // Register the application's document templates.  Document templates
  //  serve as the connection between documents, frame windows and views.

  CSingleDocTemplate *
    pDocTemplate;
  pDocTemplate = new CSingleDocTemplate (IDR_MAINFRAME, RUNTIME_CLASS (CPex32Doc), RUNTIME_CLASS (CMainFrame),	// main SDI frame window
					 RUNTIME_CLASS (CPex32View));
  AddDocTemplate (pDocTemplate);

  // Enable DDE Execute open
  EnableShellOpen ();
  RegisterShellFileTypes (TRUE);

  // Parse command line for standard shell commands, DDE, file open
  CCommandLineInfo
    cmdInfo;
  ParseCommandLine (cmdInfo);

  // Dispatch commands specified on the command line
  if (!ProcessShellCommand (cmdInfo))
    return FALSE;

  // Enable drag/drop open
  m_pMainWnd->DragAcceptFiles ();

  if (!cmdInfo.m_bRunEmbedded) {
    m_pMainWnd->UpdateWindow ();
    if (!m_pMainWnd->IsIconic () && cmdInfo.m_bShowSplash &&
	splash.Create (m_pMainWnd)) {
      // only show splash if not embedded
      splash.ShowWindow (SW_SHOW);
      splash.UpdateWindow ();
      splash.m_start = time (NULL);
    }
  }

  CPrintDialog
  cp (TRUE);
  cp.m_pd.Flags = PD_RETURNDEFAULT;
  cp.GetDefaults ();
  m_hDevMode = cp.m_pd.hDevMode;
  m_hDevNames = cp.m_pd.hDevNames;

  static DEVMODE *
    devmode;
  devmode = (DEVMODE *) GlobalLock (m_hDevMode);
  if (devmode) {
    devmode->dmOrientation = DMORIENT_LANDSCAPE;
    GlobalUnlock (m_hDevMode);
  }

  // CG: This line inserted by 'Tip of the Day' component.
  ShowTipAtStartup ();

  return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPex32App commands

BOOL CPex32App::OnIdle (LONG lCount)
{
  BOOL
    ret = CWinApp::OnIdle (lCount);

  if (splash.m_start && (time (NULL) - splash.m_start) > 5)
    splash.DestroyWindow ();
  else
    ret = TRUE;

  return ret;
}

int
CPex32App::ExitInstance ()
{
  ReleaseMutex (mutex);
  CloseHandle (mutex);
  TRACE ("Exit Instance\n");
  return CWinApp::ExitInstance ();
}

void
CPex32App::ShowTipAtStartup (void)
{
  // CG: This function added by 'Tip of the Day' component.

  CCommandLineInfo cmdInfo;
  ParseCommandLine (cmdInfo);
  if (cmdInfo.m_bShowSplash) {
    CTipDlg dlg;
    if (dlg.m_bStartup)
      dlg.DoModal ();
  }

}

void
CPex32App::ShowTipOfTheDay (void)
{
  // CG: This function added by 'Tip of the Day' component.

  CTipDlg dlg;
  dlg.DoModal ();

}
