# Microsoft Developer Studio Project File - Name="pex32" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=pex32 - Win32 Release
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "pex32.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "pex32.mak" CFG="pex32 - Win32 Release"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "pex32 - Win32 Release" (basierend auf  "Win32 (x86) Application")
!MESSAGE "pex32 - Win32 Debug" (basierend auf  "Win32 (x86) Application")
!MESSAGE "pex32 - Win32 EngRelease" (basierend auf  "Win32 (x86) Application")
!MESSAGE "pex32 - Win32 EngShareware" (basierend auf  "Win32 (x86) Application")
!MESSAGE "pex32 - Win32 Shareware" (basierend auf  "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "pex32 - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Target_Dir ""
F90=df.exe
# ADD BASE F90 /include:".\Release/"
# ADD F90 /include:".\Release/"
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# SUBTRACT BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:".\Release\poc32.exe"
# Begin Custom Build
OutDir=.\Release
InputPath=.\Release\poc32.exe
SOURCE="$(InputPath)"

"outfile.txt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	del $(OutDir)\*.res

# End Custom Build

!ELSEIF  "$(CFG)" == "pex32 - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Target_Dir ""
F90=df.exe
# ADD BASE F90 /include:".\Debug/"
# ADD F90 /include:".\Debug/"
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# SUBTRACT BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:".\Debug\poc32.exe"
# SUBTRACT LINK32 /map
# Begin Custom Build
OutDir=.\Debug
InputPath=.\Debug\poc32.exe
SOURCE="$(InputPath)"

"outfile.txt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	del $(OutDir)\*.res

# End Custom Build

!ELSEIF  "$(CFG)" == "pex32 - Win32 EngRelease"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\pex32__0"
# PROP BASE Intermediate_Dir ".\pex32__0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\EngRel"
# PROP Intermediate_Dir ".\EngRel"
# PROP Target_Dir ""
F90=df.exe
# ADD BASE F90 /include:".\pex32__0/"
# ADD F90 /include:".\EngRel/"
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "SHAREWARE" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "ENG" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL" /d "ENG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# SUBTRACT BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386 /out:"Release/poc32.exe"
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:".\EngRel\poc32.exe"
# Begin Custom Build
OutDir=.\EngRel
InputPath=.\EngRel\poc32.exe
SOURCE="$(InputPath)"

"outfile.txt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	del $(OutDir)\*.res

# End Custom Build

!ELSEIF  "$(CFG)" == "pex32 - Win32 EngShareware"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\pex32___"
# PROP BASE Intermediate_Dir ".\pex32___"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\EngShareware"
# PROP Intermediate_Dir ".\EngShareware"
# PROP Target_Dir ""
F90=df.exe
# ADD BASE F90 /include:".\pex32___/"
# ADD F90 /include:".\EngShareware/"
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_SHAREWARE" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_SHAREWARE" /D "ENG" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL" /d "ENG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "ENG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# SUBTRACT BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386 /out:"EngRel/poc32.exe"
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:".\EngShareware\poc32.exe"
# Begin Custom Build
OutDir=.\EngShareware
InputPath=.\EngShareware\poc32.exe
SOURCE="$(InputPath)"

"outfile.txt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	del $(OutDir)\*.res

# End Custom Build

!ELSEIF  "$(CFG)" == "pex32 - Win32 Shareware"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\pex32__0"
# PROP BASE Intermediate_Dir ".\pex32__0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Shareware"
# PROP Intermediate_Dir ".\Shareware"
# PROP Target_Dir ""
F90=df.exe
# ADD BASE F90 /include:".\pex32__0/"
# ADD F90 /include:".\Shareware/"
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "SHAREWARE" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_SHAREWARE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# SUBTRACT BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386 /out:"Release/poc32.exe"
# ADD LINK32 /nologo /subsystem:windows /map /machine:I386 /out:".\Shareware\poc32.exe"
# Begin Custom Build
OutDir=.\Shareware
InputPath=.\Shareware\poc32.exe
SOURCE="$(InputPath)"

"outfile.txt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	del $(OutDir)\*.res

# End Custom Build

!ENDIF 

# Begin Target

# Name "pex32 - Win32 Release"
# Name "pex32 - Win32 Debug"
# Name "pex32 - Win32 EngRelease"
# Name "pex32 - Win32 EngShareware"
# Name "pex32 - Win32 Shareware"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\AboutDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\aliases.cpp
# End Source File
# Begin Source File

SOURCE=.\CMsgLst.cpp
# End Source File
# Begin Source File

SOURCE=.\Decoder.cpp
# End Source File
# Begin Source File

SOURCE=.\Encoder.cpp
# End Source File
# Begin Source File

SOURCE=.\EntryAlias.cpp
# End Source File
# Begin Source File

SOURCE=.\Filter.cpp
# End Source File
# Begin Source File

SOURCE=.\Hardware.cpp
# End Source File
# Begin Source File

SOURCE=.\License.cpp
# End Source File
# Begin Source File

SOURCE=.\listen.cpp
# End Source File
# Begin Source File

SOURCE=.\ListManager.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\mbgrep.cpp
# End Source File
# Begin Source File

SOURCE=.\MyMessageBox.cpp
# End Source File
# Begin Source File

SOURCE=.\MyStatusBar.cpp
# End Source File
# Begin Source File

SOURCE=.\Options.cpp
# End Source File
# Begin Source File

SOURCE=.\Persist.cpp
# End Source File
# Begin Source File

SOURCE=.\pex.rc
# End Source File
# Begin Source File

SOURCE=.\pex32.cpp
# End Source File
# Begin Source File

SOURCE=.\pex32Doc.cpp
# End Source File
# Begin Source File

SOURCE=.\pex32View.cpp
# End Source File
# Begin Source File

SOURCE=.\ReadMe.Txt
# End Source File
# Begin Source File

SOURCE=.\register.cpp
# End Source File
# Begin Source File

SOURCE=.\Set.cpp
# End Source File
# Begin Source File

SOURCE=.\SetGeneral.cpp
# End Source File
# Begin Source File

SOURCE=.\SmartSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\splash.cpp
# End Source File
# Begin Source File

SOURCE=.\Statistic.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TipDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TxDialog.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\AboutDlg.h
# End Source File
# Begin Source File

SOURCE=.\aliases.h
# End Source File
# Begin Source File

SOURCE=.\CMsgLst.h
# End Source File
# Begin Source File

SOURCE=.\Decoder.h
# End Source File
# Begin Source File

SOURCE=.\ecctab.h
# End Source File
# Begin Source File

SOURCE=.\Encoder.h
# End Source File
# Begin Source File

SOURCE=.\EntryAlias.h
# End Source File
# Begin Source File

SOURCE=.\Filter.h
# End Source File
# Begin Source File

SOURCE=.\Hardware.h
# End Source File
# Begin Source File

SOURCE=.\License.h
# End Source File
# Begin Source File

SOURCE=.\listen.h
# End Source File
# Begin Source File

SOURCE=.\ListManager.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\mbgrep.h
# End Source File
# Begin Source File

SOURCE=.\MyMessageBox.h
# End Source File
# Begin Source File

SOURCE=.\MyStatusBar.h
# End Source File
# Begin Source File

SOURCE=.\MyToolBar.h
# End Source File
# Begin Source File

SOURCE=.\Options.h
# End Source File
# Begin Source File

SOURCE=.\Persist.h
# End Source File
# Begin Source File

SOURCE=.\Pex32.h
# End Source File
# Begin Source File

SOURCE=.\pex32Doc.h
# End Source File
# Begin Source File

SOURCE=.\pex32View.h
# End Source File
# Begin Source File

SOURCE=.\Pocdrv.h
# End Source File
# Begin Source File

SOURCE=.\pocinterface.h
# End Source File
# Begin Source File

SOURCE=.\pocsag.h
# End Source File
# Begin Source File

SOURCE=.\register.h
# End Source File
# Begin Source File

SOURCE=.\Set.h
# End Source File
# Begin Source File

SOURCE=.\SetGeneral.h
# End Source File
# Begin Source File

SOURCE=.\SmartSocket.h
# End Source File
# Begin Source File

SOURCE=.\splash.h
# End Source File
# Begin Source File

SOURCE=.\Statistic.h
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# Begin Source File

SOURCE=.\TipDlg.h
# End Source File
# Begin Source File

SOURCE=.\TxDialog.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap49.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\deti.bmp
# End Source File
# Begin Source File

SOURCE=.\res\deti1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Eurologo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\eyes.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00003.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00004.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_main.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_ownm.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_pex3.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_quix.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_telm.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_tmob.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_unkn.ico
# End Source File
# Begin Source File

SOURCE=.\res\InfoAdvisor_4400.bmp
# End Source File
# Begin Source File

SOURCE=.\res\litebulb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mainfram.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pex32.ico
# End Source File
# Begin Source File

SOURCE=.\res\pex32Doc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# End Group
# End Target
# End Project
