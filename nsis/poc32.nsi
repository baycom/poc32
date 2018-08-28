!define MYPRODUCT "BayCom POC32"
!define MYVERSION "2.17"
!define VER_MAJOR 2
!define VER_MINOR 17

OutFile "poc32-i386-win32-${VER_MAJOR}${VER_MINOR}-freeware.exe"

XPStyle on

;--------------------------------

Page license
Page components
Page directory
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles

; First is default
LoadLanguageFile "${NSISDIR}\Contrib\Language files\English.nlf"
LoadLanguageFile "${NSISDIR}\Contrib\Language files\Dutch.nlf"
LoadLanguageFile "${NSISDIR}\Contrib\Language files\French.nlf"
LoadLanguageFile "${NSISDIR}\Contrib\Language files\German.nlf"
LoadLanguageFile "${NSISDIR}\Contrib\Language files\Korean.nlf"
LoadLanguageFile "${NSISDIR}\Contrib\Language files\Russian.nlf"
LoadLanguageFile "${NSISDIR}\Contrib\Language files\Spanish.nlf"
LoadLanguageFile "${NSISDIR}\Contrib\Language files\Swedish.nlf"
LoadLanguageFile "${NSISDIR}\Contrib\Language files\TradChinese.nlf"
LoadLanguageFile "${NSISDIR}\Contrib\Language files\SimpChinese.nlf"
LoadLanguageFile "${NSISDIR}\Contrib\Language files\Slovak.nlf"

LicenseData "license.txt"

Name "${MYPRODUCT} ${MYVERSION}"
Function .onInit

	;Language selection dialog

	Push ""
	Push ${LANG_ENGLISH}
	Push English
	Push ${LANG_DUTCH}
	Push Dutch
	Push ${LANG_FRENCH}
	Push French
	Push ${LANG_GERMAN}
	Push German
	Push ${LANG_KOREAN}
	Push Korean
	Push ${LANG_RUSSIAN}
	Push Russian
	Push ${LANG_SPANISH}
	Push Spanish
	Push ${LANG_SWEDISH}
	Push Swedish
	Push ${LANG_TRADCHINESE}
	Push "Traditional Chinese"
	Push ${LANG_SIMPCHINESE}
	Push "Simplified Chinese"
	Push ${LANG_SLOVAK}
	Push Slovak
	Push A ; A means auto count languages
	       ; for the auto count to work the first empty push (Push "") must remain
	LangDLL::LangDialog "Installer Language" "Please select the language of the installer"

	Pop $LANGUAGE
	StrCmp $LANGUAGE "cancel" 0 +2
		Abort
FunctionEnd

InstallDir "$PROGRAMFILES\BayCom\POC32"
InstallDirRegKey HKEY_LOCAL_MACHINE "SOFTWARE\BayCom\POC32" ""

Section "Executables and DLLs (Required)" default
SectionIn RO
SetOutPath "$INSTDIR"

; add files / whatever that need to be installed here.
WriteRegStr HKEY_LOCAL_MACHINE "SOFTWARE\BayCom\POC32" "" "$INSTDIR"
WriteRegStr HKEY_LOCAL_MACHINE "Software\BayCom\POC32" "Installer Language" "$LANGUAGE"
WriteRegStr HKEY_LOCAL_MACHINE "Software\Microsoft\Windows\CurrentVersion\Uninstall\POC32" "DisplayName" "POC32 (remove only)"
WriteRegStr HKEY_LOCAL_MACHINE "Software\Microsoft\Windows\CurrentVersion\Uninstall\POC32" "UninstallString" '"$INSTDIR\uninst.exe"'


; write out uninstaller
WriteUninstaller "$INSTDIR\uninst.exe"

File "..\Release\poc32.exe" 
File "..\text\aliases.txt"
File "..\text\default.tbl" 
File "..\text\hebrew.tbl"
File "..\text\default.tbl" 
File "..\text\poc32de.pdf"
File "..\text\tipsde.txt"
File "..\text\tipseng.txt"


SetOutPath "$INSTDIR"

;Create Shortcuts
SetShellVarContext all
CreateDirectory "$SMPROGRAMS\POC32"
CreateShortCut "$SMPROGRAMS\POC32\Uninstall.lnk" "$INSTDIR\uninst.exe" "" "$INSTDIR\uninst.exe" 0
CreateShortCut "$SMPROGRAMS\POC32\POC32.lnk" "$INSTDIR\poc32.exe" "" "$INSTDIR\poc32.exe" 0
CreateShortCut "$SMPROGRAMS\POC32\POC32 Documentation (German).lnk" "$INSTDIR\poc32de.pdf" "" "$INSTDIR\poc32de.pdf" 0
SectionEnd ; end of default section

Section "Desktop Menu Shortcut" desktop
CreateShortCut "$DESKTOP\POC32.lnk" "$INSTDIR\poc32.exe" "" "$INSTDIR\poc32.exe" 0
SectionEnd

Section "Quick Launch Menu Shortcut" quicklaunch
SetShellVarContext current
CreateShortCut "$QUICKLAUNCH\POC32.lnk" "$INSTDIR\poc32.exe" "" "$INSTDIR\poc32.exe" 0
SectionEnd
 
Section "-post"
SetShellVarContext all

ExecShell open '$SMPROGRAMS\POC32'
#ExecShell open '$INSTDIR'

Sleep 500
BringToFront

SectionEnd

Function un.onInit

  ;Get language from registry
  ReadRegStr $LANGUAGE HKEY_LOCAL_MACHINE "Software\BayCom\POC32" "Installer Language"
  
FunctionEnd

Section Uninstall

;Remove all files
Delete $INSTDIR\*

; add delete commands to delete whatever files/registry keys/etc you installed here.
Delete "$INSTDIR\uninst.exe"
DeleteRegKey HKEY_LOCAL_MACHINE "SOFTWARE\BayCom\POC32"
DeleteRegKey HKEY_LOCAL_MACHINE "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\POC32"

;Remove Shortcuts from Menu
SetShellVarContext all
Delete "$SMPROGRAMS\POC32\*.*"
Delete "$DESKTOP\POC32.lnk"
RMDir "$SMPROGRAMS\POC32"

SetShellVarContext current
Delete "$QUICKLAUNCH\POC32.lnk"

RMDir "$INSTDIR"
SectionEnd ; end of uninstall section

; eof
