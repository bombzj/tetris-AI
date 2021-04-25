; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=COptionDialog
LastTemplate=generic CWnd
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Tetris.h"
LastPage=0

ClassCount=7
Class1=CTetrisApp
Class2=CTetrisDoc
Class3=CTetrisView
Class4=CMainFrame

ResourceCount=7
Resource1=IDD_ABOUTBOX
Resource2=IDD_OPTION
Class5=CAboutDlg
Resource3=IDD_TETRIS_FORM
Class6=COptionDialog
Resource4=IDD_Tetris_FORM
Class7=CControlsetDialog
Resource5=IDD_CONTROLSET
Resource6=IDR_MAINFRAME
Resource7=IDD_SELECTDEVICE

[CLS:CTetrisApp]
Type=0
HeaderFile=Tetris.h
ImplementationFile=Tetris.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=ID_ONIDLE

[CLS:CTetrisDoc]
Type=0
HeaderFile=TetrisDoc.h
ImplementationFile=TetrisDoc.cpp
Filter=N

[CLS:CTetrisView]
Type=0
HeaderFile=TetrisView.h
ImplementationFile=TetrisView.cpp
Filter=D
BaseClass=CFormView
VirtualFilter=VWC
LastObject=ID_COMPUTER


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=Tetris.cpp
ImplementationFile=Tetris.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_GAME_NEW
Command2=ID_GAME_PAUSE
Command3=ID_GAME_STOP
Command4=ID_PLAYER1
Command5=ID_PLAYER2
Command6=ID_COMPUTER
Command7=ID_APP_EXIT
Command8=ID_GAME_OPTION
Command9=ID_GAME_CONTROL
Command10=ID_GAME_PLAYMUSIC
Command11=ID_GAME_PLAYSOUND
Command12=ID_APP_ABOUT
CommandCount=12

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_PLAYER1
Command2=ID_PLAYER2
Command3=ID_COMPUTER
Command4=ID_GAME_CONTROL
Command5=ID_GAME_PLAYMUSIC
Command6=ID_GAME_OPTION
Command7=ID_GAME_PLAYSOUND
Command8=ID_FORCEWINDOWMODE
Command9=ID_GAME_NEW
Command10=ID_GAME_PAUSE
Command11=ID_GAME_STOP
Command12=ID_GAME_CHANGEDEVICE
Command13=ID_GAME_FULLSCREEN
CommandCount=13

[DLG:IDD_Tetris_FORM]
Type=1
Class=CTetrisView
ControlCount=0

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
Command9=ID_ONIDLE
CommandCount=9

[CLS:COptionDialog]
Type=0
HeaderFile=OptionDialog.h
ImplementationFile=OptionDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=COptionDialog
VirtualFilter=dWC

[DLG:IDD_CONTROLSET]
Type=1
Class=CControlsetDialog
ControlCount=24
Control1=IDC_EDIT_LEFT1,edit,1350633600
Control2=IDC_EDIT_RIGHT1,edit,1350633600
Control3=IDC_EDIT_ROTATE1,edit,1350633600
Control4=IDC_EDIT_BOTTOM1,edit,1350633600
Control5=IDC_EDIT_DOWN1,edit,1350633600
Control6=IDC_EDIT_LEFT2,edit,1350633600
Control7=IDC_EDIT_RIGHT2,edit,1350633600
Control8=IDC_EDIT_ROTATE2,edit,1350633600
Control9=IDC_EDIT_BOTTOM2,edit,1350633600
Control10=IDC_EDIT_DOWN2,edit,1350633600
Control11=IDOK,button,1342242817
Control12=IDCANCEL,button,1342242816
Control13=IDC_STATIC,button,1342177287
Control14=IDC_STATIC,button,1342177287
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352

[CLS:CControlsetDialog]
Type=0
HeaderFile=ControlsetDialog.h
ImplementationFile=ControlsetDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT_ROTATE2
VirtualFilter=dWC

[DLG:IDD_OPTION]
Type=1
Class=COptionDialog
ControlCount=20
Control1=IDC_EDIT_LEVEL,edit,1350633600
Control2=IDC_SPIN_LEVEL,msctls_updown32,1342177334
Control3=IDC_EDIT_DIFICULTY,edit,1350633600
Control4=IDC_SPIN_DIFICULTY,msctls_updown32,1342177334
Control5=IDC_EDIT_AILEVEL,edit,1350633600
Control6=IDC_SPIN_AILEVEL,msctls_updown32,1342177334
Control7=IDC_CHECK_SHOWNEXT,button,1342242819
Control8=IDC_CHECK_SMOOTHDOWN,button,1342242819
Control9=IDC_CHECK_SMOOTHROTATE,button,1342242819
Control10=IDC_OTHEREFFECT,button,1342242819
Control11=IDC_LEFTWINDOW,button,1342242819
Control12=IDC_SLIDER_VOLUMN,msctls_trackbar32,1342242840
Control13=IDC_EDIT_VOLUMN,edit,1350633600
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDOK,button,1342242817
Control18=IDCANCEL,button,1342242816
Control19=IDC_STATIC,button,1342177287
Control20=IDC_LABEL_VOLUMN,static,1342308352

[DLG:IDD_TETRIS_FORM]
Type=1
Class=?
ControlCount=0

[DLG:IDD_SELECTDEVICE]
Type=1
Class=?
ControlCount=14
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308864
Control3=IDC_ADAPTER_COMBO,combobox,1344339971
Control4=IDC_STATIC,static,1342308864
Control5=IDC_DEVICE_COMBO,combobox,1344339971
Control6=IDC_STATIC,button,1342177287
Control7=IDC_WINDOW,button,1342373897
Control8=IDC_FULLSCREEN,button,1342177289
Control9=IDC_FULLSCREENMODES_COMBO,combobox,1344471043
Control10=IDC_STATIC,button,1342177287
Control11=IDC_STATIC,static,1342308864
Control12=IDC_MULTISAMPLE_COMBO,combobox,1344339971
Control13=IDOK,button,1342242817
Control14=IDCANCEL,button,1342242816

