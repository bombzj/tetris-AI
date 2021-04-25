# Microsoft Developer Studio Project File - Name="Tetris" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Tetris - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Tetris.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Tetris.mak" CFG="Tetris - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Tetris - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Tetris - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Tetris - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 dxguid.lib winmm.lib dinput8.lib dxerr8.lib d3d8.lib d3dx8dt.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Tetris - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 dxguid.lib winmm.lib dinput8.lib dxerr8.lib d3d8.lib d3dx8dt.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Tetris - Win32 Release"
# Name "Tetris - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ControlsetDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\Tetris.rc
# End Source File
# Begin Source File

SOURCE=.\Tetris_AI.cpp
# End Source File
# Begin Source File

SOURCE=.\Tetris_Game.cpp
# End Source File
# Begin Source File

SOURCE=.\TetrisView.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ControlsetDialog.h
# End Source File
# Begin Source File

SOURCE=.\OptionDialog.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Tetris_AI.h
# End Source File
# Begin Source File

SOURCE=.\Tetris_Game.h
# End Source File
# Begin Source File

SOURCE=.\TetrisView.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Group "Midi"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\res\level00.MID
# End Source File
# Begin Source File

SOURCE=.\res\level01.mid
# End Source File
# Begin Source File

SOURCE=.\res\level02.mid
# End Source File
# Begin Source File

SOURCE=.\res\level03.mid
# End Source File
# Begin Source File

SOURCE=.\res\level04.mid
# End Source File
# Begin Source File

SOURCE=.\res\level05.mid
# End Source File
# Begin Source File

SOURCE=.\res\level06.mid
# End Source File
# Begin Source File

SOURCE=.\res\level07.mid
# End Source File
# Begin Source File

SOURCE=.\res\level08.mid
# End Source File
# Begin Source File

SOURCE=.\res\level09.mid
# End Source File
# Begin Source File

SOURCE=.\res\level10.mid
# End Source File
# End Group
# Begin Group "Wave"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\res\Addline.wav
# End Source File
# Begin Source File

SOURCE=.\res\bottom.wav
# End Source File
# Begin Source File

SOURCE=.\res\Delline.wav
# End Source File
# Begin Source File

SOURCE=.\res\gameover.wav
# End Source File
# Begin Source File

SOURCE=.\res\invalid.wav
# End Source File
# Begin Source File

SOURCE=.\res\Levelclear.wav
# End Source File
# Begin Source File

SOURCE=.\res\Levelup.wav
# End Source File
# Begin Source File

SOURCE=.\res\move.wav
# End Source File
# Begin Source File

SOURCE=.\res\rotate.wav
# End Source File
# Begin Source File

SOURCE=.\res\speedup.wav
# End Source File
# End Group
# Begin Group "Bmp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\res\Background.BMP
# End Source File
# Begin Source File

SOURCE=.\res\Block.tga
# End Source File
# Begin Source File

SOURCE=.\res\Changewhite.tga
# End Source File
# Begin Source File

SOURCE=.\res\Crash.tga
# End Source File
# Begin Source File

SOURCE=.\res\Explode.tga
# End Source File
# Begin Source File

SOURCE=.\res\Gameover.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GamePause.tga
# End Source File
# Begin Source File

SOURCE=.\res\Grayblock.tga
# End Source File
# Begin Source File

SOURCE=.\res\Level.tga
# End Source File
# Begin Source File

SOURCE=.\res\nfloor.tga
# End Source File
# Begin Source File

SOURCE=.\res\Score.tga
# End Source File
# Begin Source File

SOURCE=.\res\Subtitle.tga
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\firework.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Tetris.ico
# End Source File
# Begin Source File

SOURCE=.\res\Tetris.rc2
# End Source File
# Begin Source File

SOURCE=.\res\TetrisDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Group "Other"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ShapeFile.h
# End Source File
# Begin Source File

SOURCE=.\TetrisControl.cpp
# End Source File
# Begin Source File

SOURCE=.\TetrisControl.h
# End Source File
# Begin Source File

SOURCE=.\TetrisDraw.cpp
# End Source File
# Begin Source File

SOURCE=.\TetrisDraw.h
# End Source File
# Begin Source File

SOURCE=.\TetrisInput.cpp
# End Source File
# Begin Source File

SOURCE=.\TetrisInput.h
# End Source File
# Begin Source File

SOURCE=.\TetrisMusic.cpp
# End Source File
# Begin Source File

SOURCE=.\TetrisMusic.h
# End Source File
# End Group
# Begin Group "Few Edited"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\d3dapp.cpp
# End Source File
# Begin Source File

SOURCE=.\d3dapp.h
# End Source File
# Begin Source File

SOURCE=.\d3dres.h
# End Source File
# Begin Source File

SOURCE=.\d3dutil.cpp
# End Source File
# Begin Source File

SOURCE=.\d3dutil.h
# End Source File
# Begin Source File

SOURCE=.\dmutil.cpp
# End Source File
# Begin Source File

SOURCE=.\dmutil.h
# End Source File
# Begin Source File

SOURCE=.\dxutil.cpp
# End Source File
# Begin Source File

SOURCE=.\dxutil.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Tetris.cpp
# End Source File
# Begin Source File

SOURCE=.\Tetris.h
# End Source File
# Begin Source File

SOURCE=.\TetrisDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\TetrisDoc.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
