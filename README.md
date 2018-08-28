POC32 Implementation Guide 

Version    : 1.0.19
Date       : March, 1997
Platform   : Win32 (Windows 95 or Windows NT/I386)
Language   : Microsoft Visual C++ V4.X and MFC extensions
Description: POC32 is a POCSAG protocol en-/decoder software

------------------------------------------------------------------------------

Welcome to the wonderful world of Microsoft's idea of C++. 

POC32 is developed using the MFC (Microsoft Foundation Classes), which make your
programs look like an original microsoft application.


Class Overview:

CAboutDlg                          Standard about dialog.
CBigIcon                           Splash screen big-icon creator.
CDecoder                           Property page containing all decoder settings.
CEncoder                           Property page containing all encoder settings.
CHardware						   Property page containing all hardware settings.
CLicense                           Startup screen displaying license agreement.
CMainFrame                         Handles all major messages from the system and 
                                   MFC framework.
CMsg                               Class containing a message structure. All messages 
                                   are stored in a MFC CArray.
CPeristentFrame                    Taken from 'InsideVisual C++' to store window size
                                   and position in profile or registry.
CPex32App                          Standard main MFC application frame. 
CPex32View                         Contains all major window message handlers and 
                                   provides a list view in report style with all
								   standard functions (including sorting, finding and
								   printing all entries).
CPocInterface                      All basic POCSAG en-/decoder functions. This class
                                   controls the POC.VXD and is able using any WavIn
								   Device for decoding. Minor modifications would be
								   neccessary changing it into a DLL.
CSet                               Sets up the main property page. All usersettings are
								   stored here or in embedded classes.
CSplashWnd                         Standard splash screen class.
CStatistic                         Property page displaying current decoder statistics.
CTipDlg                            Standard tip of day dialog.
CTxDialog                          Transmit POCSAG-packet-dialog.
pocsag_rx						   Structure saving all important decoder states. For
                                   every channel and bitrate an instance of this 
								   structure exists.
