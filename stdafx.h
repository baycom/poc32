// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#define _CRT_SECURE_NO_DEPRECATE
#define  WINVER  0x0502

#include <afxwin.h>		// MFC core and standard components
#include <afxext.h>		// MFC extensions
#include <afxcview.h>
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>		// MFC support for Windows 95 Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <afxtempl.h>

#include <MMSystem.h>
// CG: The following line was added by the Windows Multimedia component.
#pragma comment(lib, "winmm.lib")
#include <afxsock.h>		// MFC socket extensions
