# Microsoft Developer Studio Project File - Name="i1k_D3D9Shader" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=i1k_D3D9Shader - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "i1k_D3D9Shader.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "i1k_D3D9Shader.mak" CFG="i1k_D3D9Shader - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "i1k_D3D9Shader - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "i1k_D3D9Shader - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "i1k_D3D9Shader - Win32 Release"

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
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winmm.lib d3d9.lib d3dx9.lib dsound.lib /nologo /entry:"entrypoint" /subsystem:windows /pdb:none /machine:I386 /nodefaultlib /out:"exe/luxo4k_vc6.exe" /CRINKLER /VERBOSE:FUNCTIONS /VERBOSE:IMPORTS /VERBOSE:LABELS /HASHTRIES:300 /COMPMODE:SLOW /ORDERTRIES:4000

!ELSEIF  "$(CFG)" == "i1k_D3D9Shader - Win32 Debug"

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
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winmm.lib opengl32.lib glu32.lib comdlg32.lib d3dx9.lib /nologo /subsystem:windows /map /debug /machine:I386 /out:"exe/4verts_deb.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "i1k_D3D9Shader - Win32 Release"
# Name "i1k_D3D9Shader - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\src\config.h
# End Source File
# Begin Source File

SOURCE=.\src\fp.h
# End Source File
# Begin Source File

SOURCE=.\src\intro.cpp
# End Source File
# Begin Source File

SOURCE=.\src\intro.h
# End Source File
# Begin Source File

SOURCE=.\src\main_deb.cpp

!IF  "$(CFG)" == "i1k_D3D9Shader - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "i1k_D3D9Shader - Win32 Debug"

!ENDIF

# End Source File
# Begin Source File

SOURCE=.\src\main_rel.cpp

!IF  "$(CFG)" == "i1k_D3D9Shader - Win32 Release"

!ELSEIF  "$(CFG)" == "i1k_D3D9Shader - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF

# End Source File
# End Group
# End Target
# End Project
