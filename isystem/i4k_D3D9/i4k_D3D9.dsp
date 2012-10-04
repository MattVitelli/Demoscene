# Microsoft Developer Studio Project File - Name="e_demo04" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=e_demo04 - Win32 Video
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "e_demo04.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "e_demo04.mak" CFG="e_demo04 - Win32 Video"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "e_demo04 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "e_demo04 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "e_demo04 - Win32 Video" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "e_demo04 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "bin/Release"
# PROP Intermediate_Dir "bin/Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /G6 /Gr /Zp1 /W3 /Ox /Oa /Oi /Os /Oy- /Gf /I "../" /D "WINDOWS" /D "A32BITS" /D "SIMD" /D "NDEBUG" /FD /QIfist /Gs /c
# SUBTRACT CPP /WX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winmm.lib d3d9.lib d3dx9.lib dsound.lib /nologo /entry:"entrypoint" /subsystem:windows /pdb:none /machine:I386 /nodefaultlib /out:"exe/4verts.exe" /CRINKLER /VERBOSE:FUNCTIONS /VERBOSE:IMPORTS /VERBOSE:LABELS /HASHTRIES:300 /COMPMODE:SLOW /ORDERTRIES:4000 /SAFEIMPORT

!ELSEIF  "$(CFG)" == "e_demo04 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "bin/Debug"
# PROP Intermediate_Dir "bin/Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /ML /W3 /WX /Zi /Od /Op /I "../" /D "_DEBUG" /D "WINDOWS" /D "DEBUG" /D "SIMD" /D "A32BITS" /FR /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winmm.lib opengl32.lib glu32.lib comdlg32.lib d3dx9.lib /nologo /subsystem:windows /map /debug /machine:I386 /out:"exe/4verts_deb.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "e_demo04 - Win32 Video"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "e_demo04___Win32_Video"
# PROP BASE Intermediate_Dir "e_demo04___Win32_Video"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "bin/Video"
# PROP Intermediate_Dir "bin/Video"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /ML /W3 /WX /GX /ZI /Od /Op /I "../" /D "_DEBUG" /D "WINDOWS" /D "DEBUG" /D "SIMD" /D "A32BITS" /FR /FD /GZ /c
# ADD CPP /nologo /ML /W3 /WX /GX /ZI /Od /Op /I "../" /D "_DEBUG" /D "WINDOWS" /D "DEBUG" /D "SIMD" /D "A32BITS" /FR /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winmm.lib opengl32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"exe/4verts_deb.exe" /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winmm.lib opengl32.lib glu32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"exe/4verts_vid.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "e_demo04 - Win32 Release"
# Name "e_demo04 - Win32 Debug"
# Name "e_demo04 - Win32 Video"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "sys"

# PROP Default_Filter ""
# Begin Group "_windows"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\sys\_windows\main_deb.cpp

!IF  "$(CFG)" == "e_demo04 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "e_demo04 - Win32 Debug"

!ELSEIF  "$(CFG)" == "e_demo04 - Win32 Video"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\sys\_windows\main_rel.cpp

!IF  "$(CFG)" == "e_demo04 - Win32 Release"

!ELSEIF  "$(CFG)" == "e_demo04 - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "e_demo04 - Win32 Video"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\sys\_windows\main_video.cpp

!IF  "$(CFG)" == "e_demo04 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "e_demo04 - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "e_demo04 - Win32 Video"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\sys\_windows\raster.cpp

!IF  "$(CFG)" == "e_demo04 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "e_demo04 - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "e_demo04 - Win32 Video"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\sys\_windows\raster.h

!IF  "$(CFG)" == "e_demo04 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "e_demo04 - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "e_demo04 - Win32 Video"

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\src\sys\mlibc.cpp
# End Source File
# Begin Source File

SOURCE=.\src\sys\mlibc.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\src\animation.cpp
# End Source File
# Begin Source File

SOURCE=.\src\animation.h
# End Source File
# Begin Source File

SOURCE=.\src\intro.cpp
# End Source File
# Begin Source File

SOURCE=.\src\intro.h
# End Source File
# Begin Source File

SOURCE=.\src\maths.cpp
# End Source File
# Begin Source File

SOURCE=.\src\maths.h
# End Source File
# Begin Source File

SOURCE=.\src\mesh.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mesh.h
# End Source File
# Begin Source File

SOURCE=.\src\meshData.h
# End Source File
# Begin Source File

SOURCE=.\src\mzk.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mzk.h
# End Source File
# End Group
# End Target
# End Project
