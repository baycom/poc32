# Microsoft Developer Studio Generated NMAKE File, Based on pex32.dsp
!IF "$(CFG)" == ""
CFG=pex32 - Win32 Release
!MESSAGE No configuration specified. Defaulting to pex32 - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "pex32 - Win32 Release" && "$(CFG)" != "pex32 - Win32 Debug" &&\
 "$(CFG)" != "pex32 - Win32 EngRelease" && "$(CFG)" !=\
 "pex32 - Win32 EngShareware" && "$(CFG)" != "pex32 - Win32 Shareware"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "pex32.mak" CFG="pex32 - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "pex32 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "pex32 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "pex32 - Win32 EngRelease" (based on "Win32 (x86) Application")
!MESSAGE "pex32 - Win32 EngShareware" (based on "Win32 (x86) Application")
!MESSAGE "pex32 - Win32 Shareware" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "pex32 - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\poc32.exe" "$(OUTDIR)\pex32.bsc" "outfile.txt"

!ELSE 

ALL : "$(OUTDIR)\poc32.exe" "$(OUTDIR)\pex32.bsc" "outfile.txt"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\AboutDlg.obj"
	-@erase "$(INTDIR)\AboutDlg.sbr"
	-@erase "$(INTDIR)\CMsgLst.obj"
	-@erase "$(INTDIR)\CMsgLst.sbr"
	-@erase "$(INTDIR)\Decoder.obj"
	-@erase "$(INTDIR)\Decoder.sbr"
	-@erase "$(INTDIR)\Encoder.obj"
	-@erase "$(INTDIR)\Encoder.sbr"
	-@erase "$(INTDIR)\Hardware.obj"
	-@erase "$(INTDIR)\Hardware.sbr"
	-@erase "$(INTDIR)\License.obj"
	-@erase "$(INTDIR)\License.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\Persist.obj"
	-@erase "$(INTDIR)\Persist.sbr"
	-@erase "$(INTDIR)\pex.res"
	-@erase "$(INTDIR)\pex32.obj"
	-@erase "$(INTDIR)\pex32.pch"
	-@erase "$(INTDIR)\pex32.sbr"
	-@erase "$(INTDIR)\pex32Doc.obj"
	-@erase "$(INTDIR)\pex32Doc.sbr"
	-@erase "$(INTDIR)\pex32View.obj"
	-@erase "$(INTDIR)\pex32View.sbr"
	-@erase "$(INTDIR)\PocInterface.obj"
	-@erase "$(INTDIR)\PocInterface.sbr"
	-@erase "$(INTDIR)\Set.obj"
	-@erase "$(INTDIR)\Set.sbr"
	-@erase "$(INTDIR)\splash.obj"
	-@erase "$(INTDIR)\splash.sbr"
	-@erase "$(INTDIR)\Statistic.obj"
	-@erase "$(INTDIR)\Statistic.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\TipDlg.obj"
	-@erase "$(INTDIR)\TipDlg.sbr"
	-@erase "$(INTDIR)\TxDialog.obj"
	-@erase "$(INTDIR)\TxDialog.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\pex32.bsc"
	-@erase "$(OUTDIR)\poc32.exe"
	-@erase "outfile.txt"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\pex32.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\Release/

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x407 /fo"$(INTDIR)\pex.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/o"$(OUTDIR)\pex32.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\AboutDlg.sbr" \
	"$(INTDIR)\CMsgLst.sbr" \
	"$(INTDIR)\Decoder.sbr" \
	"$(INTDIR)\Encoder.sbr" \
	"$(INTDIR)\Hardware.sbr" \
	"$(INTDIR)\License.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\Persist.sbr" \
	"$(INTDIR)\pex32.sbr" \
	"$(INTDIR)\pex32Doc.sbr" \
	"$(INTDIR)\pex32View.sbr" \
	"$(INTDIR)\PocInterface.sbr" \
	"$(INTDIR)\Set.sbr" \
	"$(INTDIR)\splash.sbr" \
	"$(INTDIR)\Statistic.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\TipDlg.sbr" \
	"$(INTDIR)\TxDialog.sbr"

"$(OUTDIR)\pex32.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\poc32.pdb" /machine:I386 /out:"$(OUTDIR)\poc32.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AboutDlg.obj" \
	"$(INTDIR)\CMsgLst.obj" \
	"$(INTDIR)\Decoder.obj" \
	"$(INTDIR)\Encoder.obj" \
	"$(INTDIR)\Hardware.obj" \
	"$(INTDIR)\License.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Persist.obj" \
	"$(INTDIR)\pex.res" \
	"$(INTDIR)\pex32.obj" \
	"$(INTDIR)\pex32Doc.obj" \
	"$(INTDIR)\pex32View.obj" \
	"$(INTDIR)\PocInterface.obj" \
	"$(INTDIR)\Set.obj" \
	"$(INTDIR)\splash.obj" \
	"$(INTDIR)\Statistic.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TipDlg.obj" \
	"$(INTDIR)\TxDialog.obj"

"$(OUTDIR)\poc32.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\Release
InputPath=.\Release\poc32.exe
SOURCE=$(InputPath)

"outfile.txt"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	del $(OutDir)\*.res

!ELSEIF  "$(CFG)" == "pex32 - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\poc32.exe" "outfile.txt"

!ELSE 

ALL : "$(OUTDIR)\poc32.exe" "outfile.txt"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\AboutDlg.obj"
	-@erase "$(INTDIR)\CMsgLst.obj"
	-@erase "$(INTDIR)\Decoder.obj"
	-@erase "$(INTDIR)\Encoder.obj"
	-@erase "$(INTDIR)\Hardware.obj"
	-@erase "$(INTDIR)\License.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\Persist.obj"
	-@erase "$(INTDIR)\pex.res"
	-@erase "$(INTDIR)\pex32.obj"
	-@erase "$(INTDIR)\pex32.pch"
	-@erase "$(INTDIR)\pex32Doc.obj"
	-@erase "$(INTDIR)\pex32View.obj"
	-@erase "$(INTDIR)\PocInterface.obj"
	-@erase "$(INTDIR)\Set.obj"
	-@erase "$(INTDIR)\splash.obj"
	-@erase "$(INTDIR)\Statistic.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TipDlg.obj"
	-@erase "$(INTDIR)\TxDialog.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\poc32.exe"
	-@erase "$(OUTDIR)\poc32.ilk"
	-@erase "$(OUTDIR)\poc32.pdb"
	-@erase "outfile.txt"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\pex32.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x407 /fo"$(INTDIR)\pex.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/o"$(OUTDIR)\pex32.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\poc32.pdb" /debug /machine:I386 /out:"$(OUTDIR)\poc32.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AboutDlg.obj" \
	"$(INTDIR)\CMsgLst.obj" \
	"$(INTDIR)\Decoder.obj" \
	"$(INTDIR)\Encoder.obj" \
	"$(INTDIR)\Hardware.obj" \
	"$(INTDIR)\License.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Persist.obj" \
	"$(INTDIR)\pex.res" \
	"$(INTDIR)\pex32.obj" \
	"$(INTDIR)\pex32Doc.obj" \
	"$(INTDIR)\pex32View.obj" \
	"$(INTDIR)\PocInterface.obj" \
	"$(INTDIR)\Set.obj" \
	"$(INTDIR)\splash.obj" \
	"$(INTDIR)\Statistic.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TipDlg.obj" \
	"$(INTDIR)\TxDialog.obj"

"$(OUTDIR)\poc32.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\Debug
InputPath=.\Debug\poc32.exe
SOURCE=$(InputPath)

"outfile.txt"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	del $(OutDir)\*.res

!ELSEIF  "$(CFG)" == "pex32 - Win32 EngRelease"

OUTDIR=.\EngRel
INTDIR=.\EngRel
# Begin Custom Macros
OutDir=.\.\EngRel
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\poc32.exe" "outfile.txt"

!ELSE 

ALL : "$(OUTDIR)\poc32.exe" "outfile.txt"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\AboutDlg.obj"
	-@erase "$(INTDIR)\CMsgLst.obj"
	-@erase "$(INTDIR)\Decoder.obj"
	-@erase "$(INTDIR)\Encoder.obj"
	-@erase "$(INTDIR)\Hardware.obj"
	-@erase "$(INTDIR)\License.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\Persist.obj"
	-@erase "$(INTDIR)\pex.res"
	-@erase "$(INTDIR)\pex32.obj"
	-@erase "$(INTDIR)\pex32.pch"
	-@erase "$(INTDIR)\pex32Doc.obj"
	-@erase "$(INTDIR)\pex32View.obj"
	-@erase "$(INTDIR)\PocInterface.obj"
	-@erase "$(INTDIR)\Set.obj"
	-@erase "$(INTDIR)\splash.obj"
	-@erase "$(INTDIR)\Statistic.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TipDlg.obj"
	-@erase "$(INTDIR)\TxDialog.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\poc32.exe"
	-@erase "outfile.txt"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /D "ENG" /Fp"$(INTDIR)\pex32.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\EngRel/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\pex.res" /d "NDEBUG" /d "_AFXDLL" /d "ENG" 
BSC32=bscmake.exe
BSC32_FLAGS=/o"$(OUTDIR)\pex32.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\poc32.pdb" /machine:I386 /out:"$(OUTDIR)\poc32.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AboutDlg.obj" \
	"$(INTDIR)\CMsgLst.obj" \
	"$(INTDIR)\Decoder.obj" \
	"$(INTDIR)\Encoder.obj" \
	"$(INTDIR)\Hardware.obj" \
	"$(INTDIR)\License.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Persist.obj" \
	"$(INTDIR)\pex.res" \
	"$(INTDIR)\pex32.obj" \
	"$(INTDIR)\pex32Doc.obj" \
	"$(INTDIR)\pex32View.obj" \
	"$(INTDIR)\PocInterface.obj" \
	"$(INTDIR)\Set.obj" \
	"$(INTDIR)\splash.obj" \
	"$(INTDIR)\Statistic.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TipDlg.obj" \
	"$(INTDIR)\TxDialog.obj"

"$(OUTDIR)\poc32.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\EngRel
InputPath=.\EngRel\poc32.exe
SOURCE=$(InputPath)

"outfile.txt"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	del $(OutDir)\*.res

!ELSEIF  "$(CFG)" == "pex32 - Win32 EngShareware"

OUTDIR=.\EngShareware
INTDIR=.\EngShareware
# Begin Custom Macros
OutDir=.\.\EngShareware
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\poc32.exe" "outfile.txt"

!ELSE 

ALL : "$(OUTDIR)\poc32.exe" "outfile.txt"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\AboutDlg.obj"
	-@erase "$(INTDIR)\CMsgLst.obj"
	-@erase "$(INTDIR)\Decoder.obj"
	-@erase "$(INTDIR)\Encoder.obj"
	-@erase "$(INTDIR)\Hardware.obj"
	-@erase "$(INTDIR)\License.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\Persist.obj"
	-@erase "$(INTDIR)\pex.res"
	-@erase "$(INTDIR)\pex32.obj"
	-@erase "$(INTDIR)\pex32.pch"
	-@erase "$(INTDIR)\pex32Doc.obj"
	-@erase "$(INTDIR)\pex32View.obj"
	-@erase "$(INTDIR)\PocInterface.obj"
	-@erase "$(INTDIR)\Set.obj"
	-@erase "$(INTDIR)\splash.obj"
	-@erase "$(INTDIR)\Statistic.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TipDlg.obj"
	-@erase "$(INTDIR)\TxDialog.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\poc32.exe"
	-@erase "outfile.txt"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /D "_SHAREWARE" /D "ENG" /Fp"$(INTDIR)\pex32.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\EngShareware/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\pex.res" /d "NDEBUG" /d "_AFXDLL" /d "ENG" 
BSC32=bscmake.exe
BSC32_FLAGS=/o"$(OUTDIR)\pex32.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\poc32.pdb" /machine:I386 /out:"$(OUTDIR)\poc32.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AboutDlg.obj" \
	"$(INTDIR)\CMsgLst.obj" \
	"$(INTDIR)\Decoder.obj" \
	"$(INTDIR)\Encoder.obj" \
	"$(INTDIR)\Hardware.obj" \
	"$(INTDIR)\License.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Persist.obj" \
	"$(INTDIR)\pex.res" \
	"$(INTDIR)\pex32.obj" \
	"$(INTDIR)\pex32Doc.obj" \
	"$(INTDIR)\pex32View.obj" \
	"$(INTDIR)\PocInterface.obj" \
	"$(INTDIR)\Set.obj" \
	"$(INTDIR)\splash.obj" \
	"$(INTDIR)\Statistic.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TipDlg.obj" \
	"$(INTDIR)\TxDialog.obj"

"$(OUTDIR)\poc32.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\EngShareware
InputPath=.\EngShareware\poc32.exe
SOURCE=$(InputPath)

"outfile.txt"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	del $(OutDir)\*.res

!ELSEIF  "$(CFG)" == "pex32 - Win32 Shareware"

OUTDIR=.\Shareware
INTDIR=.\Shareware
# Begin Custom Macros
OutDir=.\.\Shareware
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\poc32.exe" "outfile.txt"

!ELSE 

ALL : "$(OUTDIR)\poc32.exe" "outfile.txt"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\AboutDlg.obj"
	-@erase "$(INTDIR)\CMsgLst.obj"
	-@erase "$(INTDIR)\Decoder.obj"
	-@erase "$(INTDIR)\Encoder.obj"
	-@erase "$(INTDIR)\Hardware.obj"
	-@erase "$(INTDIR)\License.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\Persist.obj"
	-@erase "$(INTDIR)\pex.res"
	-@erase "$(INTDIR)\pex32.obj"
	-@erase "$(INTDIR)\pex32.pch"
	-@erase "$(INTDIR)\pex32Doc.obj"
	-@erase "$(INTDIR)\pex32View.obj"
	-@erase "$(INTDIR)\PocInterface.obj"
	-@erase "$(INTDIR)\Set.obj"
	-@erase "$(INTDIR)\splash.obj"
	-@erase "$(INTDIR)\Statistic.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TipDlg.obj"
	-@erase "$(INTDIR)\TxDialog.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\poc32.exe"
	-@erase "$(OUTDIR)\poc32.map"
	-@erase "outfile.txt"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /D "_SHAREWARE" /Fp"$(INTDIR)\pex32.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Shareware/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x407 /fo"$(INTDIR)\pex.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/o"$(OUTDIR)\pex32.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\poc32.pdb" /map:"$(INTDIR)\poc32.map" /machine:I386\
 /out:"$(OUTDIR)\poc32.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AboutDlg.obj" \
	"$(INTDIR)\CMsgLst.obj" \
	"$(INTDIR)\Decoder.obj" \
	"$(INTDIR)\Encoder.obj" \
	"$(INTDIR)\Hardware.obj" \
	"$(INTDIR)\License.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Persist.obj" \
	"$(INTDIR)\pex.res" \
	"$(INTDIR)\pex32.obj" \
	"$(INTDIR)\pex32Doc.obj" \
	"$(INTDIR)\pex32View.obj" \
	"$(INTDIR)\PocInterface.obj" \
	"$(INTDIR)\Set.obj" \
	"$(INTDIR)\splash.obj" \
	"$(INTDIR)\Statistic.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TipDlg.obj" \
	"$(INTDIR)\TxDialog.obj"

"$(OUTDIR)\poc32.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\Shareware
InputPath=.\Shareware\poc32.exe
SOURCE=$(InputPath)

"outfile.txt"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	del $(OutDir)\*.res

!ENDIF 


!IF "$(CFG)" == "pex32 - Win32 Release" || "$(CFG)" == "pex32 - Win32 Debug" ||\
 "$(CFG)" == "pex32 - Win32 EngRelease" || "$(CFG)" ==\
 "pex32 - Win32 EngShareware" || "$(CFG)" == "pex32 - Win32 Shareware"
SOURCE=.\AboutDlg.cpp

!IF  "$(CFG)" == "pex32 - Win32 Release"

DEP_CPP_ABOUT=\
	".\AboutDlg.h"\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	

"$(INTDIR)\AboutDlg.obj"	"$(INTDIR)\AboutDlg.sbr" : $(SOURCE) $(DEP_CPP_ABOUT)\
 "$(INTDIR)" "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 Debug"

DEP_CPP_ABOUT=\
	".\AboutDlg.h"\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	

"$(INTDIR)\AboutDlg.obj" : $(SOURCE) $(DEP_CPP_ABOUT) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 EngRelease"

DEP_CPP_ABOUT=\
	".\AboutDlg.h"\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	".\stdafx.h"\
	

"$(INTDIR)\AboutDlg.obj" : $(SOURCE) $(DEP_CPP_ABOUT) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 EngShareware"

DEP_CPP_ABOUT=\
	".\AboutDlg.h"\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	

"$(INTDIR)\AboutDlg.obj" : $(SOURCE) $(DEP_CPP_ABOUT) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 Shareware"

DEP_CPP_ABOUT=\
	".\AboutDlg.h"\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	

"$(INTDIR)\AboutDlg.obj" : $(SOURCE) $(DEP_CPP_ABOUT) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ENDIF 

SOURCE=.\CMsgLst.cpp

!IF  "$(CFG)" == "pex32 - Win32 Release"

DEP_CPP_CMSGL=\
	".\CMsgLst.h"\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	

"$(INTDIR)\CMsgLst.obj"	"$(INTDIR)\CMsgLst.sbr" : $(SOURCE) $(DEP_CPP_CMSGL)\
 "$(INTDIR)" "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 Debug"

DEP_CPP_CMSGL=\
	".\CMsgLst.h"\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	

"$(INTDIR)\CMsgLst.obj" : $(SOURCE) $(DEP_CPP_CMSGL) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 EngRelease"

DEP_CPP_CMSGL=\
	".\CMsgLst.h"\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	".\stdafx.h"\
	

"$(INTDIR)\CMsgLst.obj" : $(SOURCE) $(DEP_CPP_CMSGL) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 EngShareware"

DEP_CPP_CMSGL=\
	".\CMsgLst.h"\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	

"$(INTDIR)\CMsgLst.obj" : $(SOURCE) $(DEP_CPP_CMSGL) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 Shareware"

DEP_CPP_CMSGL=\
	".\CMsgLst.h"\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	

"$(INTDIR)\CMsgLst.obj" : $(SOURCE) $(DEP_CPP_CMSGL) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ENDIF 

SOURCE=.\Decoder.cpp

!IF  "$(CFG)" == "pex32 - Win32 Release"

DEP_CPP_DECOD=\
	".\CMsgLst.h"\
	".\Decoder.h"\
	".\Encoder.h"\
	".\Hardware.h"\
	".\MainFrm.h"\
	".\Persist.h"\
	".\Pex32.h"\
	".\pex32Doc.h"\
	".\pex32View.h"\
	".\Pocdrv.h"\
	".\pocinterface.h"\
	".\Set.h"\
	".\splash.h"\
	".\Statistic.h"\
	".\TxDialog.h"\
	

"$(INTDIR)\Decoder.obj"	"$(INTDIR)\Decoder.sbr" : $(SOURCE) $(DEP_CPP_DECOD)\
 "$(INTDIR)" "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 Debug"

DEP_CPP_DECOD=\
	".\CMsgLst.h"\
	".\Decoder.h"\
	".\Encoder.h"\
	".\Hardware.h"\
	".\MainFrm.h"\
	".\Persist.h"\
	".\Pex32.h"\
	".\pex32Doc.h"\
	".\pex32View.h"\
	".\Pocdrv.h"\
	".\pocinterface.h"\
	".\Set.h"\
	".\splash.h"\
	".\Statistic.h"\
	".\TxDialog.h"\
	

"$(INTDIR)\Decoder.obj" : $(SOURCE) $(DEP_CPP_DECOD) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 EngRelease"

DEP_CPP_DECOD=\
	".\CMsgLst.h"\
	".\Decoder.h"\
	".\Encoder.h"\
	".\Hardware.h"\
	".\MainFrm.h"\
	".\Persist.h"\
	".\Pex32.h"\
	".\pex32Doc.h"\
	".\pex32View.h"\
	".\Pocdrv.h"\
	".\pocinterface.h"\
	".\Set.h"\
	".\splash.h"\
	".\Statistic.h"\
	".\stdafx.h"\
	".\TxDialog.h"\
	

"$(INTDIR)\Decoder.obj" : $(SOURCE) $(DEP_CPP_DECOD) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 EngShareware"

DEP_CPP_DECOD=\
	".\CMsgLst.h"\
	".\Decoder.h"\
	".\Encoder.h"\
	".\Hardware.h"\
	".\MainFrm.h"\
	".\Persist.h"\
	".\Pex32.h"\
	".\pex32Doc.h"\
	".\pex32View.h"\
	".\Pocdrv.h"\
	".\pocinterface.h"\
	".\Set.h"\
	".\splash.h"\
	".\Statistic.h"\
	".\TxDialog.h"\
	

"$(INTDIR)\Decoder.obj" : $(SOURCE) $(DEP_CPP_DECOD) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 Shareware"

DEP_CPP_DECOD=\
	".\CMsgLst.h"\
	".\Decoder.h"\
	".\Encoder.h"\
	".\Hardware.h"\
	".\MainFrm.h"\
	".\Persist.h"\
	".\Pex32.h"\
	".\pex32Doc.h"\
	".\pex32View.h"\
	".\Pocdrv.h"\
	".\pocinterface.h"\
	".\Set.h"\
	".\splash.h"\
	".\Statistic.h"\
	".\TxDialog.h"\
	

"$(INTDIR)\Decoder.obj" : $(SOURCE) $(DEP_CPP_DECOD) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ENDIF 

SOURCE=.\Encoder.cpp

!IF  "$(CFG)" == "pex32 - Win32 Release"

DEP_CPP_ENCOD=\
	".\Encoder.h"\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	

"$(INTDIR)\Encoder.obj"	"$(INTDIR)\Encoder.sbr" : $(SOURCE) $(DEP_CPP_ENCOD)\
 "$(INTDIR)" "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 Debug"

DEP_CPP_ENCOD=\
	".\Encoder.h"\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	

"$(INTDIR)\Encoder.obj" : $(SOURCE) $(DEP_CPP_ENCOD) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 EngRelease"

DEP_CPP_ENCOD=\
	".\Encoder.h"\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	".\stdafx.h"\
	

"$(INTDIR)\Encoder.obj" : $(SOURCE) $(DEP_CPP_ENCOD) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 EngShareware"

DEP_CPP_ENCOD=\
	".\Encoder.h"\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	

"$(INTDIR)\Encoder.obj" : $(SOURCE) $(DEP_CPP_ENCOD) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 Shareware"

DEP_CPP_ENCOD=\
	".\Encoder.h"\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	

"$(INTDIR)\Encoder.obj" : $(SOURCE) $(DEP_CPP_ENCOD) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ENDIF 

SOURCE=.\Hardware.cpp

!IF  "$(CFG)" == "pex32 - Win32 Release"

DEP_CPP_HARDW=\
	".\CMsgLst.h"\
	".\Decoder.h"\
	".\Encoder.h"\
	".\Hardware.h"\
	".\MainFrm.h"\
	".\Persist.h"\
	".\Pex32.h"\
	".\pex32Doc.h"\
	".\pex32View.h"\
	".\Pocdrv.h"\
	".\pocinterface.h"\
	".\Set.h"\
	".\splash.h"\
	".\Statistic.h"\
	".\TxDialog.h"\
	

"$(INTDIR)\Hardware.obj"	"$(INTDIR)\Hardware.sbr" : $(SOURCE) $(DEP_CPP_HARDW)\
 "$(INTDIR)" "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 Debug"

DEP_CPP_HARDW=\
	".\CMsgLst.h"\
	".\Decoder.h"\
	".\Encoder.h"\
	".\Hardware.h"\
	".\MainFrm.h"\
	".\Persist.h"\
	".\Pex32.h"\
	".\pex32Doc.h"\
	".\pex32View.h"\
	".\Pocdrv.h"\
	".\pocinterface.h"\
	".\Set.h"\
	".\splash.h"\
	".\Statistic.h"\
	".\TxDialog.h"\
	

"$(INTDIR)\Hardware.obj" : $(SOURCE) $(DEP_CPP_HARDW) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 EngRelease"

DEP_CPP_HARDW=\
	".\CMsgLst.h"\
	".\Decoder.h"\
	".\Encoder.h"\
	".\Hardware.h"\
	".\MainFrm.h"\
	".\Persist.h"\
	".\Pex32.h"\
	".\pex32Doc.h"\
	".\pex32View.h"\
	".\Pocdrv.h"\
	".\pocinterface.h"\
	".\Set.h"\
	".\splash.h"\
	".\Statistic.h"\
	".\stdafx.h"\
	".\TxDialog.h"\
	

"$(INTDIR)\Hardware.obj" : $(SOURCE) $(DEP_CPP_HARDW) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 EngShareware"

DEP_CPP_HARDW=\
	".\CMsgLst.h"\
	".\Decoder.h"\
	".\Encoder.h"\
	".\Hardware.h"\
	".\MainFrm.h"\
	".\Persist.h"\
	".\Pex32.h"\
	".\pex32Doc.h"\
	".\pex32View.h"\
	".\Pocdrv.h"\
	".\pocinterface.h"\
	".\Set.h"\
	".\splash.h"\
	".\Statistic.h"\
	".\TxDialog.h"\
	

"$(INTDIR)\Hardware.obj" : $(SOURCE) $(DEP_CPP_HARDW) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 Shareware"

DEP_CPP_HARDW=\
	".\CMsgLst.h"\
	".\Decoder.h"\
	".\Encoder.h"\
	".\Hardware.h"\
	".\MainFrm.h"\
	".\Persist.h"\
	".\Pex32.h"\
	".\pex32Doc.h"\
	".\pex32View.h"\
	".\Pocdrv.h"\
	".\pocinterface.h"\
	".\Set.h"\
	".\splash.h"\
	".\Statistic.h"\
	".\TxDialog.h"\
	

"$(INTDIR)\Hardware.obj" : $(SOURCE) $(DEP_CPP_HARDW) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ENDIF 

SOURCE=.\License.cpp

!IF  "$(CFG)" == "pex32 - Win32 Release"

DEP_CPP_LICEN=\
	".\License.h"\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	

"$(INTDIR)\License.obj"	"$(INTDIR)\License.sbr" : $(SOURCE) $(DEP_CPP_LICEN)\
 "$(INTDIR)" "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 Debug"

DEP_CPP_LICEN=\
	".\License.h"\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	

"$(INTDIR)\License.obj" : $(SOURCE) $(DEP_CPP_LICEN) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 EngRelease"

DEP_CPP_LICEN=\
	".\License.h"\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	".\stdafx.h"\
	

"$(INTDIR)\License.obj" : $(SOURCE) $(DEP_CPP_LICEN) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 EngShareware"

DEP_CPP_LICEN=\
	".\License.h"\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	

"$(INTDIR)\License.obj" : $(SOURCE) $(DEP_CPP_LICEN) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 Shareware"

DEP_CPP_LICEN=\
	".\License.h"\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	

"$(INTDIR)\License.obj" : $(SOURCE) $(DEP_CPP_LICEN) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ENDIF 

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "pex32 - Win32 Release"

DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\Persist.h"\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	

"$(INTDIR)\MainFrm.obj"	"$(INTDIR)\MainFrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF)\
 "$(INTDIR)" "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 Debug"

DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\Persist.h"\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 EngRelease"

DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\Persist.h"\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	".\stdafx.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 EngShareware"

DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\Persist.h"\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 Shareware"

DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\Persist.h"\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ENDIF 

SOURCE=.\Persist.cpp

!IF  "$(CFG)" == "pex32 - Win32 Release"

DEP_CPP_PERSI=\
	".\Persist.h"\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	

"$(INTDIR)\Persist.obj"	"$(INTDIR)\Persist.sbr" : $(SOURCE) $(DEP_CPP_PERSI)\
 "$(INTDIR)" "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 Debug"

DEP_CPP_PERSI=\
	".\Persist.h"\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	

"$(INTDIR)\Persist.obj" : $(SOURCE) $(DEP_CPP_PERSI) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 EngRelease"

DEP_CPP_PERSI=\
	".\Persist.h"\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	".\stdafx.h"\
	

"$(INTDIR)\Persist.obj" : $(SOURCE) $(DEP_CPP_PERSI) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 EngShareware"

DEP_CPP_PERSI=\
	".\Persist.h"\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	

"$(INTDIR)\Persist.obj" : $(SOURCE) $(DEP_CPP_PERSI) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 Shareware"

DEP_CPP_PERSI=\
	".\Persist.h"\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	

"$(INTDIR)\Persist.obj" : $(SOURCE) $(DEP_CPP_PERSI) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ENDIF 

SOURCE=.\pex.rc

"$(INTDIR)\pex.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\pex32.cpp

!IF  "$(CFG)" == "pex32 - Win32 Release"

DEP_CPP_PEX32=\
	".\CMsgLst.h"\
	".\Decoder.h"\
	".\Encoder.h"\
	".\Hardware.h"\
	".\License.h"\
	".\MainFrm.h"\
	".\Persist.h"\
	".\Pex32.h"\
	".\pex32Doc.h"\
	".\pex32View.h"\
	".\Pocdrv.h"\
	".\pocinterface.h"\
	".\Set.h"\
	".\splash.h"\
	".\Statistic.h"\
	".\TipDlg.h"\
	".\TxDialog.h"\
	

"$(INTDIR)\pex32.obj"	"$(INTDIR)\pex32.sbr" : $(SOURCE) $(DEP_CPP_PEX32)\
 "$(INTDIR)" "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 Debug"

DEP_CPP_PEX32=\
	".\CMsgLst.h"\
	".\Decoder.h"\
	".\Encoder.h"\
	".\Hardware.h"\
	".\License.h"\
	".\MainFrm.h"\
	".\Persist.h"\
	".\Pex32.h"\
	".\pex32Doc.h"\
	".\pex32View.h"\
	".\Pocdrv.h"\
	".\pocinterface.h"\
	".\Set.h"\
	".\splash.h"\
	".\Statistic.h"\
	".\TipDlg.h"\
	".\TxDialog.h"\
	

"$(INTDIR)\pex32.obj" : $(SOURCE) $(DEP_CPP_PEX32) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 EngRelease"

DEP_CPP_PEX32=\
	".\CMsgLst.h"\
	".\Decoder.h"\
	".\Encoder.h"\
	".\Hardware.h"\
	".\License.h"\
	".\MainFrm.h"\
	".\Persist.h"\
	".\Pex32.h"\
	".\pex32Doc.h"\
	".\pex32View.h"\
	".\Pocdrv.h"\
	".\pocinterface.h"\
	".\Set.h"\
	".\splash.h"\
	".\Statistic.h"\
	".\stdafx.h"\
	".\TipDlg.h"\
	".\TxDialog.h"\
	

"$(INTDIR)\pex32.obj" : $(SOURCE) $(DEP_CPP_PEX32) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 EngShareware"

DEP_CPP_PEX32=\
	".\CMsgLst.h"\
	".\Decoder.h"\
	".\Encoder.h"\
	".\Hardware.h"\
	".\License.h"\
	".\MainFrm.h"\
	".\Persist.h"\
	".\Pex32.h"\
	".\pex32Doc.h"\
	".\pex32View.h"\
	".\Pocdrv.h"\
	".\pocinterface.h"\
	".\Set.h"\
	".\splash.h"\
	".\Statistic.h"\
	".\TipDlg.h"\
	".\TxDialog.h"\
	

"$(INTDIR)\pex32.obj" : $(SOURCE) $(DEP_CPP_PEX32) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 Shareware"

DEP_CPP_PEX32=\
	".\CMsgLst.h"\
	".\Decoder.h"\
	".\Encoder.h"\
	".\Hardware.h"\
	".\License.h"\
	".\MainFrm.h"\
	".\Persist.h"\
	".\Pex32.h"\
	".\pex32Doc.h"\
	".\pex32View.h"\
	".\Pocdrv.h"\
	".\pocinterface.h"\
	".\Set.h"\
	".\splash.h"\
	".\Statistic.h"\
	".\TipDlg.h"\
	".\TxDialog.h"\
	

"$(INTDIR)\pex32.obj" : $(SOURCE) $(DEP_CPP_PEX32) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ENDIF 

SOURCE=.\pex32.rc
SOURCE=.\pex32Doc.cpp

!IF  "$(CFG)" == "pex32 - Win32 Release"

DEP_CPP_PEX32D=\
	".\CMsgLst.h"\
	".\Decoder.h"\
	".\Encoder.h"\
	".\Hardware.h"\
	".\MainFrm.h"\
	".\Persist.h"\
	".\Pex32.h"\
	".\pex32Doc.h"\
	".\Pocdrv.h"\
	".\Set.h"\
	".\splash.h"\
	".\Statistic.h"\
	

"$(INTDIR)\pex32Doc.obj"	"$(INTDIR)\pex32Doc.sbr" : $(SOURCE) $(DEP_CPP_PEX32D)\
 "$(INTDIR)" "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 Debug"

DEP_CPP_PEX32D=\
	".\CMsgLst.h"\
	".\Decoder.h"\
	".\Encoder.h"\
	".\Hardware.h"\
	".\MainFrm.h"\
	".\Persist.h"\
	".\Pex32.h"\
	".\pex32Doc.h"\
	".\Pocdrv.h"\
	".\Set.h"\
	".\splash.h"\
	".\Statistic.h"\
	

"$(INTDIR)\pex32Doc.obj" : $(SOURCE) $(DEP_CPP_PEX32D) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 EngRelease"

DEP_CPP_PEX32D=\
	".\CMsgLst.h"\
	".\Decoder.h"\
	".\Encoder.h"\
	".\Hardware.h"\
	".\MainFrm.h"\
	".\Persist.h"\
	".\Pex32.h"\
	".\pex32Doc.h"\
	".\Pocdrv.h"\
	".\Set.h"\
	".\splash.h"\
	".\Statistic.h"\
	".\stdafx.h"\
	

"$(INTDIR)\pex32Doc.obj" : $(SOURCE) $(DEP_CPP_PEX32D) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 EngShareware"

DEP_CPP_PEX32D=\
	".\CMsgLst.h"\
	".\Decoder.h"\
	".\Encoder.h"\
	".\Hardware.h"\
	".\MainFrm.h"\
	".\Persist.h"\
	".\Pex32.h"\
	".\pex32Doc.h"\
	".\Pocdrv.h"\
	".\Set.h"\
	".\splash.h"\
	".\Statistic.h"\
	

"$(INTDIR)\pex32Doc.obj" : $(SOURCE) $(DEP_CPP_PEX32D) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 Shareware"

DEP_CPP_PEX32D=\
	".\CMsgLst.h"\
	".\Decoder.h"\
	".\Encoder.h"\
	".\Hardware.h"\
	".\MainFrm.h"\
	".\Persist.h"\
	".\Pex32.h"\
	".\pex32Doc.h"\
	".\Pocdrv.h"\
	".\Set.h"\
	".\splash.h"\
	".\Statistic.h"\
	

"$(INTDIR)\pex32Doc.obj" : $(SOURCE) $(DEP_CPP_PEX32D) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ENDIF 

SOURCE=.\pex32eng.rc
SOURCE=.\pex32View.cpp

!IF  "$(CFG)" == "pex32 - Win32 Release"

DEP_CPP_PEX32V=\
	".\AboutDlg.h"\
	".\CMsgLst.h"\
	".\Decoder.h"\
	".\Encoder.h"\
	".\Hardware.h"\
	".\License.h"\
	".\MainFrm.h"\
	".\Persist.h"\
	".\Pex32.h"\
	".\pex32Doc.h"\
	".\pex32View.h"\
	".\Pocdrv.h"\
	".\pocinterface.h"\
	".\Set.h"\
	".\splash.h"\
	".\Statistic.h"\
	".\TxDialog.h"\
	

"$(INTDIR)\pex32View.obj"	"$(INTDIR)\pex32View.sbr" : $(SOURCE)\
 $(DEP_CPP_PEX32V) "$(INTDIR)" "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 Debug"

DEP_CPP_PEX32V=\
	".\AboutDlg.h"\
	".\CMsgLst.h"\
	".\Decoder.h"\
	".\Encoder.h"\
	".\Hardware.h"\
	".\License.h"\
	".\MainFrm.h"\
	".\Persist.h"\
	".\Pex32.h"\
	".\pex32Doc.h"\
	".\pex32View.h"\
	".\Pocdrv.h"\
	".\pocinterface.h"\
	".\Set.h"\
	".\splash.h"\
	".\Statistic.h"\
	".\TxDialog.h"\
	

"$(INTDIR)\pex32View.obj" : $(SOURCE) $(DEP_CPP_PEX32V) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 EngRelease"

DEP_CPP_PEX32V=\
	".\AboutDlg.h"\
	".\CMsgLst.h"\
	".\Decoder.h"\
	".\Encoder.h"\
	".\Hardware.h"\
	".\License.h"\
	".\MainFrm.h"\
	".\Persist.h"\
	".\Pex32.h"\
	".\pex32Doc.h"\
	".\pex32View.h"\
	".\Pocdrv.h"\
	".\pocinterface.h"\
	".\Set.h"\
	".\splash.h"\
	".\Statistic.h"\
	".\stdafx.h"\
	".\TxDialog.h"\
	

"$(INTDIR)\pex32View.obj" : $(SOURCE) $(DEP_CPP_PEX32V) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 EngShareware"

DEP_CPP_PEX32V=\
	".\AboutDlg.h"\
	".\CMsgLst.h"\
	".\Decoder.h"\
	".\Encoder.h"\
	".\Hardware.h"\
	".\License.h"\
	".\MainFrm.h"\
	".\Persist.h"\
	".\Pex32.h"\
	".\pex32Doc.h"\
	".\pex32View.h"\
	".\Pocdrv.h"\
	".\pocinterface.h"\
	".\Set.h"\
	".\splash.h"\
	".\Statistic.h"\
	".\TxDialog.h"\
	

"$(INTDIR)\pex32View.obj" : $(SOURCE) $(DEP_CPP_PEX32V) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 Shareware"

DEP_CPP_PEX32V=\
	".\AboutDlg.h"\
	".\CMsgLst.h"\
	".\Decoder.h"\
	".\Encoder.h"\
	".\Hardware.h"\
	".\License.h"\
	".\MainFrm.h"\
	".\Persist.h"\
	".\Pex32.h"\
	".\pex32Doc.h"\
	".\pex32View.h"\
	".\Pocdrv.h"\
	".\pocinterface.h"\
	".\Set.h"\
	".\splash.h"\
	".\Statistic.h"\
	".\TxDialog.h"\
	

"$(INTDIR)\pex32View.obj" : $(SOURCE) $(DEP_CPP_PEX32V) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ENDIF 

SOURCE=.\PocInterface.cpp

!IF  "$(CFG)" == "pex32 - Win32 Release"

DEP_CPP_POCIN=\
	".\CMsgLst.h"\
	".\Decoder.h"\
	".\ecctab.h"\
	".\Encoder.h"\
	".\Hardware.h"\
	".\MainFrm.h"\
	".\Persist.h"\
	".\Pex32.h"\
	".\pex32Doc.h"\
	".\pex32View.h"\
	".\Pocdrv.h"\
	".\pocinterface.h"\
	".\pocsag.h"\
	".\Set.h"\
	".\splash.h"\
	".\Statistic.h"\
	".\TxDialog.h"\
	

"$(INTDIR)\PocInterface.obj"	"$(INTDIR)\PocInterface.sbr" : $(SOURCE)\
 $(DEP_CPP_POCIN) "$(INTDIR)" "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 Debug"

DEP_CPP_POCIN=\
	".\CMsgLst.h"\
	".\Decoder.h"\
	".\ecctab.h"\
	".\Encoder.h"\
	".\Hardware.h"\
	".\MainFrm.h"\
	".\Persist.h"\
	".\Pex32.h"\
	".\pex32Doc.h"\
	".\pex32View.h"\
	".\Pocdrv.h"\
	".\pocinterface.h"\
	".\pocsag.h"\
	".\Set.h"\
	".\splash.h"\
	".\Statistic.h"\
	".\TxDialog.h"\
	

"$(INTDIR)\PocInterface.obj" : $(SOURCE) $(DEP_CPP_POCIN) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 EngRelease"

DEP_CPP_POCIN=\
	".\CMsgLst.h"\
	".\Decoder.h"\
	".\ecctab.h"\
	".\Encoder.h"\
	".\Hardware.h"\
	".\MainFrm.h"\
	".\Persist.h"\
	".\Pex32.h"\
	".\pex32Doc.h"\
	".\pex32View.h"\
	".\Pocdrv.h"\
	".\pocinterface.h"\
	".\pocsag.h"\
	".\Set.h"\
	".\splash.h"\
	".\Statistic.h"\
	".\stdafx.h"\
	".\TxDialog.h"\
	

"$(INTDIR)\PocInterface.obj" : $(SOURCE) $(DEP_CPP_POCIN) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 EngShareware"

DEP_CPP_POCIN=\
	".\CMsgLst.h"\
	".\Decoder.h"\
	".\ecctab.h"\
	".\Encoder.h"\
	".\Hardware.h"\
	".\MainFrm.h"\
	".\Persist.h"\
	".\Pex32.h"\
	".\pex32Doc.h"\
	".\pex32View.h"\
	".\Pocdrv.h"\
	".\pocinterface.h"\
	".\pocsag.h"\
	".\Set.h"\
	".\splash.h"\
	".\Statistic.h"\
	".\TxDialog.h"\
	

"$(INTDIR)\PocInterface.obj" : $(SOURCE) $(DEP_CPP_POCIN) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 Shareware"

DEP_CPP_POCIN=\
	".\CMsgLst.h"\
	".\Decoder.h"\
	".\ecctab.h"\
	".\Encoder.h"\
	".\Hardware.h"\
	".\MainFrm.h"\
	".\Persist.h"\
	".\Pex32.h"\
	".\pex32Doc.h"\
	".\pex32View.h"\
	".\Pocdrv.h"\
	".\pocinterface.h"\
	".\pocsag.h"\
	".\Set.h"\
	".\splash.h"\
	".\Statistic.h"\
	".\TxDialog.h"\
	

"$(INTDIR)\PocInterface.obj" : $(SOURCE) $(DEP_CPP_POCIN) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ENDIF 

SOURCE=.\Set.cpp

!IF  "$(CFG)" == "pex32 - Win32 Release"

DEP_CPP_SET_C=\
	".\Decoder.h"\
	".\Encoder.h"\
	".\Hardware.h"\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\Set.h"\
	".\splash.h"\
	".\Statistic.h"\
	

"$(INTDIR)\Set.obj"	"$(INTDIR)\Set.sbr" : $(SOURCE) $(DEP_CPP_SET_C)\
 "$(INTDIR)" "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 Debug"

DEP_CPP_SET_C=\
	".\Decoder.h"\
	".\Encoder.h"\
	".\Hardware.h"\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\Set.h"\
	".\splash.h"\
	".\Statistic.h"\
	

"$(INTDIR)\Set.obj" : $(SOURCE) $(DEP_CPP_SET_C) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 EngRelease"

DEP_CPP_SET_C=\
	".\Decoder.h"\
	".\Encoder.h"\
	".\Hardware.h"\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\Set.h"\
	".\splash.h"\
	".\Statistic.h"\
	".\stdafx.h"\
	

"$(INTDIR)\Set.obj" : $(SOURCE) $(DEP_CPP_SET_C) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 EngShareware"

DEP_CPP_SET_C=\
	".\Decoder.h"\
	".\Encoder.h"\
	".\Hardware.h"\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\Set.h"\
	".\splash.h"\
	".\Statistic.h"\
	

"$(INTDIR)\Set.obj" : $(SOURCE) $(DEP_CPP_SET_C) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 Shareware"

DEP_CPP_SET_C=\
	".\Decoder.h"\
	".\Encoder.h"\
	".\Hardware.h"\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\Set.h"\
	".\splash.h"\
	".\Statistic.h"\
	

"$(INTDIR)\Set.obj" : $(SOURCE) $(DEP_CPP_SET_C) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ENDIF 

SOURCE=.\splash.cpp

!IF  "$(CFG)" == "pex32 - Win32 Release"

DEP_CPP_SPLAS=\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	

"$(INTDIR)\splash.obj"	"$(INTDIR)\splash.sbr" : $(SOURCE) $(DEP_CPP_SPLAS)\
 "$(INTDIR)" "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 Debug"

DEP_CPP_SPLAS=\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	

"$(INTDIR)\splash.obj" : $(SOURCE) $(DEP_CPP_SPLAS) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 EngRelease"

DEP_CPP_SPLAS=\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	".\stdafx.h"\
	

"$(INTDIR)\splash.obj" : $(SOURCE) $(DEP_CPP_SPLAS) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 EngShareware"

DEP_CPP_SPLAS=\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	

"$(INTDIR)\splash.obj" : $(SOURCE) $(DEP_CPP_SPLAS) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 Shareware"

DEP_CPP_SPLAS=\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	

"$(INTDIR)\splash.obj" : $(SOURCE) $(DEP_CPP_SPLAS) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ENDIF 

SOURCE=.\Statistic.cpp

!IF  "$(CFG)" == "pex32 - Win32 Release"

DEP_CPP_STATI=\
	".\CMsgLst.h"\
	".\Decoder.h"\
	".\Encoder.h"\
	".\Hardware.h"\
	".\MainFrm.h"\
	".\Persist.h"\
	".\Pex32.h"\
	".\pex32Doc.h"\
	".\pex32View.h"\
	".\Pocdrv.h"\
	".\pocinterface.h"\
	".\Set.h"\
	".\splash.h"\
	".\Statistic.h"\
	".\TxDialog.h"\
	

"$(INTDIR)\Statistic.obj"	"$(INTDIR)\Statistic.sbr" : $(SOURCE)\
 $(DEP_CPP_STATI) "$(INTDIR)" "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 Debug"

DEP_CPP_STATI=\
	".\CMsgLst.h"\
	".\Decoder.h"\
	".\Encoder.h"\
	".\Hardware.h"\
	".\MainFrm.h"\
	".\Persist.h"\
	".\Pex32.h"\
	".\pex32Doc.h"\
	".\pex32View.h"\
	".\Pocdrv.h"\
	".\pocinterface.h"\
	".\Set.h"\
	".\splash.h"\
	".\Statistic.h"\
	".\TxDialog.h"\
	

"$(INTDIR)\Statistic.obj" : $(SOURCE) $(DEP_CPP_STATI) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 EngRelease"

DEP_CPP_STATI=\
	".\CMsgLst.h"\
	".\Decoder.h"\
	".\Encoder.h"\
	".\Hardware.h"\
	".\MainFrm.h"\
	".\Persist.h"\
	".\Pex32.h"\
	".\pex32Doc.h"\
	".\pex32View.h"\
	".\Pocdrv.h"\
	".\pocinterface.h"\
	".\Set.h"\
	".\splash.h"\
	".\Statistic.h"\
	".\stdafx.h"\
	".\TxDialog.h"\
	

"$(INTDIR)\Statistic.obj" : $(SOURCE) $(DEP_CPP_STATI) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 EngShareware"

DEP_CPP_STATI=\
	".\CMsgLst.h"\
	".\Decoder.h"\
	".\Encoder.h"\
	".\Hardware.h"\
	".\MainFrm.h"\
	".\Persist.h"\
	".\Pex32.h"\
	".\pex32Doc.h"\
	".\pex32View.h"\
	".\Pocdrv.h"\
	".\pocinterface.h"\
	".\Set.h"\
	".\splash.h"\
	".\Statistic.h"\
	".\TxDialog.h"\
	

"$(INTDIR)\Statistic.obj" : $(SOURCE) $(DEP_CPP_STATI) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 Shareware"

DEP_CPP_STATI=\
	".\CMsgLst.h"\
	".\Decoder.h"\
	".\Encoder.h"\
	".\Hardware.h"\
	".\MainFrm.h"\
	".\Persist.h"\
	".\Pex32.h"\
	".\pex32Doc.h"\
	".\pex32View.h"\
	".\Pocdrv.h"\
	".\pocinterface.h"\
	".\Set.h"\
	".\splash.h"\
	".\Statistic.h"\
	".\TxDialog.h"\
	

"$(INTDIR)\Statistic.obj" : $(SOURCE) $(DEP_CPP_STATI) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "pex32 - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\pex32.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\pex32.pch" : $(SOURCE)\
 $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "pex32 - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\pex32.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\pex32.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "pex32 - Win32 EngRelease"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /D "ENG" /Fp"$(INTDIR)\pex32.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\pex32.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "pex32 - Win32 EngShareware"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /D "_SHAREWARE" /D "ENG" /Fp"$(INTDIR)\pex32.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\pex32.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "pex32 - Win32 Shareware"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /D "_SHAREWARE" /Fp"$(INTDIR)\pex32.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\pex32.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\TipDlg.cpp

!IF  "$(CFG)" == "pex32 - Win32 Release"

DEP_CPP_TIPDL=\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	".\TipDlg.h"\
	

"$(INTDIR)\TipDlg.obj"	"$(INTDIR)\TipDlg.sbr" : $(SOURCE) $(DEP_CPP_TIPDL)\
 "$(INTDIR)" "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 Debug"

DEP_CPP_TIPDL=\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	".\TipDlg.h"\
	

"$(INTDIR)\TipDlg.obj" : $(SOURCE) $(DEP_CPP_TIPDL) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 EngRelease"

DEP_CPP_TIPDL=\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	".\stdafx.h"\
	".\TipDlg.h"\
	

"$(INTDIR)\TipDlg.obj" : $(SOURCE) $(DEP_CPP_TIPDL) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 EngShareware"

DEP_CPP_TIPDL=\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	".\TipDlg.h"\
	

"$(INTDIR)\TipDlg.obj" : $(SOURCE) $(DEP_CPP_TIPDL) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 Shareware"

DEP_CPP_TIPDL=\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	".\TipDlg.h"\
	

"$(INTDIR)\TipDlg.obj" : $(SOURCE) $(DEP_CPP_TIPDL) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ENDIF 

SOURCE=.\TxDialog.cpp

!IF  "$(CFG)" == "pex32 - Win32 Release"

DEP_CPP_TXDIA=\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	".\TxDialog.h"\
	

"$(INTDIR)\TxDialog.obj"	"$(INTDIR)\TxDialog.sbr" : $(SOURCE) $(DEP_CPP_TXDIA)\
 "$(INTDIR)" "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 Debug"

DEP_CPP_TXDIA=\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	".\TxDialog.h"\
	

"$(INTDIR)\TxDialog.obj" : $(SOURCE) $(DEP_CPP_TXDIA) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 EngRelease"

DEP_CPP_TXDIA=\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	".\stdafx.h"\
	".\TxDialog.h"\
	

"$(INTDIR)\TxDialog.obj" : $(SOURCE) $(DEP_CPP_TXDIA) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 EngShareware"

DEP_CPP_TXDIA=\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	".\TxDialog.h"\
	

"$(INTDIR)\TxDialog.obj" : $(SOURCE) $(DEP_CPP_TXDIA) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ELSEIF  "$(CFG)" == "pex32 - Win32 Shareware"

DEP_CPP_TXDIA=\
	".\Pex32.h"\
	".\Pocdrv.h"\
	".\splash.h"\
	".\TxDialog.h"\
	

"$(INTDIR)\TxDialog.obj" : $(SOURCE) $(DEP_CPP_TXDIA) "$(INTDIR)"\
 "$(INTDIR)\pex32.pch"


!ENDIF 


!ENDIF 

