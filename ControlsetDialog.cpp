// ControlsetDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Tetris.h"
#include "ControlsetDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CControlsetDialog dialog
/*********定义键盘上每个键的名称**********/
wchar_t KeyDefString[KEYBOARD_NUMBER][KEYBOARD_STRINGLENGTH]={L"",
/*#define DIK_ESCAPE          0x01*/	L"Escape",
/*#define DIK_1               0x02*/	L"1",
/*#define DIK_2               0x03*/	L"2",
/*#define DIK_3               0x04*/	L"3",
/*#define DIK_4               0x05*/	L"4",
/*#define DIK_5               0x06*/	L"5",
/*#define DIK_6               0x07*/	L"6",
/*#define DIK_7               0x08*/	L"7",
/*#define DIK_8               0x09*/	L"8",
/*#define DIK_9               0x0A*/	L"9",
/*#define DIK_0               0x0B*/	L"0",
/*#define DIK_MINUS           0x0C*/	L"-",
/*#define DIK_EQUALS          0x0D*/	L"=",
/*#define DIK_BACK            0x0E*/	L"backspace",
/*#define DIK_TAB             0x0F*/	L"Table",
/*#define DIK_Q               0x10*/	L"Q",
/*#define DIK_W               0x11*/	L"W",
/*#define DIK_E               0x12*/	L"E",
/*#define DIK_R               0x13*/	L"R",
/*#define DIK_T               0x14*/	L"T",
/*#define DIK_Y               0x15*/	L"Y",
/*#define DIK_U               0x16*/	L"U",
/*#define DIK_I               0x17*/	L"I",
/*#define DIK_O               0x18*/	L"O",
/*#define DIK_P               0x19*/	L"P",
/*#define DIK_LBRACKET        0x1A*/	L"[",
/*#define DIK_RBRACKET        0x1B*/	L"]",
/*#define DIK_RETURN          0x1C*/	L"Enter",
/*#define DIK_LCONTROL        0x1D*/	L"Left Control",
/*#define DIK_A               0x1E*/	L"A",
/*#define DIK_S               0x1F*/	L"S",
/*#define DIK_D               0x20*/	L"D",
/*#define DIK_F               0x21*/	L"F",
/*#define DIK_G               0x22*/	L"G",
/*#define DIK_H               0x23*/	L"H",
/*#define DIK_J               0x24*/	L"J",
/*#define DIK_K               0x25*/	L"K",
/*#define DIK_L               0x26*/	L"L",
/*#define DIK_SEMICOLON       0x27*/	L"Semicolon",
/*#define DIK_APOSTROPHE      0x28*/	L"Apostrophe",
/*#define DIK_GRAVE           0x29*/	L"accent grave",
/*#define DIK_LSHIFT          0x2A*/	L"Left Shift",
/*#define DIK_BACKSLASH       0x2B*/	L"Back Slash",
/*#define DIK_Z               0x2C*/	L"Z",
/*#define DIK_X               0x2D*/	L"X",
/*#define DIK_C               0x2E*/	L"C",
/*#define DIK_V               0x2F*/	L"V",
/*#define DIK_B               0x30*/	L"B",
/*#define DIK_N               0x31*/	L"N",
/*#define DIK_M               0x32*/	L"M",
/*#define DIK_COMMA           0x33*/	L",",
/*#define DIK_PERIOD          0x34*/	L".",
/*#define DIK_SLASH           0x35*/	L"/",
/*#define DIK_RSHIFT          0x36*/	L"Right Shift",
/*#define DIK_MULTIPLY        0x37*/	L"*",
/*#define DIK_LMENU           0x38*/	L"left Alt",
/*#define DIK_SPACE           0x39*/	L"Space Bar",
/*#define DIK_CAPITAL         0x3A*/	L"Capital",
/*#define DIK_F1              0x3B*/	L"F1",
/*#define DIK_F2              0x3C*/	L"F2",
/*#define DIK_F3              0x3D*/	L"F3",
/*#define DIK_F4              0x3E*/	L"F4",
/*#define DIK_F5              0x3F*/	L"F5",
/*#define DIK_F6              0x40*/	L"F6",
/*#define DIK_F7              0x41*/	L"F7",
/*#define DIK_F8              0x42*/	L"F8",
/*#define DIK_F9              0x43*/	L"F9",
/*#define DIK_F10             0x44*/	L"F10",
/*#define DIK_NUMLOCK         0x45*/	L"Number Lock",
/*#define DIK_SCROLL          0x46*/	L"Scroll Lock",
/*#define DIK_NUMPAD7         0x47*/	L"NumPad 7",
/*#define DIK_NUMPAD8         0x48*/	L"NumPad 8",
/*#define DIK_NUMPAD9         0x49*/	L"NumPad 9",
/*#define DIK_SUBTRACT        0x4A*/	L"Substract",
/*#define DIK_NUMPAD4         0x4B*/	L"NumPad 4",
/*#define DIK_NUMPAD5         0x4C*/	L"NumPad 5",
/*#define DIK_NUMPAD6         0x4D*/	L"NumPad 6",
/*#define DIK_ADD             0x4E*/	L"Add",
/*#define DIK_NUMPAD1         0x4F*/	L"NumPad 1",
/*#define DIK_NUMPAD2         0x50*/	L"NumPad 2",
/*#define DIK_NUMPAD3         0x51*/	L"NumPad 3",
/*#define DIK_NUMPAD0         0x52*/	L"NumPad 0",
/*#define DIK_DECIMAL         0x53*/	L"NumPad .", L"", L"",
/*#define DIK_OEM_102         0x56*/	L"",
/*#define DIK_F11             0x57*/	L"F11",
/*#define DIK_F12             0x58*/	L"F12", L"", L"", L"", L"", L"", L"", L"", L"", L"", L"", L"",
/*#define DIK_F13             0x64*/	L"",
/*#define DIK_F14             0x65*/	L"",
/*#define DIK_F15             0x66*/	L"", L"", L"", L"", L"", L"", L"", L"", L"", L"",
/*#define DIK_KANA            0x70*/	L"", L"", L"",
/*#define DIK_ABNT_C1         0x73*/	L"", L"", L"", L"", L"", L"",
/*#define DIK_CONVERT         0x79*/	L"", L"",
/*#define DIK_NOCONVERT       0x7B*/	L"", L"",
/*#define DIK_YEN             0x7D*/	L"",
/*#define DIK_ABNT_C2         0x7E*/	L"Numpad . on Brazilian keyboard", L"", L"", L"", L"", L"", L"", L"", L"", L"", L"", L"", L"", L"", L"",
/*#define DIK_NUMPADEQUALS    0x8D*/	L"", L"", L"",
/*#define DIK_PREVTRACK       0x90*/	L"",
/*#define DIK_AT              0x91*/	L"",
/*#define DIK_COLON           0x92*/	L"",
/*#define DIK_UNDERLINE       0x93*/	L"",
/*#define DIK_KANJI           0x94*/	L"",
/*#define DIK_STOP            0x95*/	L"",
/*#define DIK_AX              0x96*/	L"",
/*#define DIK_UNLABELED       0x97*/	L"", L"",
/*#define DIK_NEXTTRACK       0x99*/	L"Next Track", L"", L"",
/*#define DIK_NUMPADENTER     0x9C*/	L"Enter on numeric keypad",
/*#define DIK_RCONTROL        0x9D*/	L"Right Control", L"", L"",
/*#define DIK_MUTE            0xA0*/	L"Mute",
/*#define DIK_CALCULATOR      0xA1*/	L"Calculator",
/*#define DIK_PLAYPAUSE       0xA2*/	L"Play / Pause", L"",
/*#define DIK_MEDIASTOP       0xA4*/	L"Media Stop", L"", L"", L"", L"", L"", L"", L"", L"", L"",
/*#define DIK_VOLUMEDOWN      0xAE*/	L"Volume -", L"",
/*#define DIK_VOLUMEUP        0xB0*/	L"Volume +", L"",
/*#define DIK_WEBHOME         0xB2*/	L"Web home",
/*#define DIK_NUMPADCOMMA     0xB3*/	L"", L"",
/*#define DIK_DIVIDE          0xB5*/	L"NumPad /", L"",
/*#define DIK_SYSRQ           0xB7*/	L"SysRQ",
/*#define DIK_RMENU           0xB8*/	L"right Alt", L"", L"", L"", L"", L"", L"", L"", L"", L"", L"", L"", L"",
/*#define DIK_PAUSE           0xC5*/	L"Pause", L"",
/*#define DIK_HOME            0xC7*/	L"Home",
/*#define DIK_UP              0xC8*/	L"UpArrow",
/*#define DIK_PRIOR           0xC9*/	L"PgUp", L"",
/*#define DIK_LEFT            0xCB*/	L"LeftArrow", L"",
/*#define DIK_RIGHT           0xCD*/	L"RightArrow", L"",
/*#define DIK_END             0xCF*/	L"End",
/*#define DIK_DOWN            0xD0*/	L"DownArrow",
/*#define DIK_NEXT            0xD1*/	L"PgDn",
/*#define DIK_INSERT          0xD2*/	L"Insert",
/*#define DIK_DELETE          0xD3*/	L"Delete", L"", L"", L"", L"", L"", L"", L"",
/*#define DIK_LWIN            0xDB*/	L"Left Winkey",
/*#define DIK_RWIN            0xDC*/	L"Right Winkey",
/*#define DIK_APPS            0xDD*/	L"AppMenu key",
/*#define DIK_POWER           0xDE*/	L"System Power",
/*#define DIK_SLEEP           0xDF*/	L"System Sleep", L"", L"", L"",
/*#define DIK_WAKE            0xE3*/	L"System Wake", L"",
/*#define DIK_WEBSEARCH       0xE5*/	L"Web Search",
/*#define DIK_WEBFAVORITES    0xE6*/	L"Web Favorites",
/*#define DIK_WEBREFRESH      0xE7*/	L"Web Refresh",
/*#define DIK_WEBSTOP         0xE8*/	L"Web Stop",
/*#define DIK_WEBFORWARD      0xE9*/	L"Web Forward",
/*#define DIK_WEBBACK         0xEA*/	L"Web Back",
/*#define DIK_MYCOMPUTER      0xEB*/	L"My Computer",
/*#define DIK_MAIL            0xEC*/	L"Mail",
/*#define DIK_MEDIASELECT     0xED*/	L"Media Select",
};

CControlsetDialog::CControlsetDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CControlsetDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CControlsetDialog)
	//}}AFX_DATA_INIT
}


void CControlsetDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CControlsetDialog)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CControlsetDialog, CDialog)
	//{{AFX_MSG_MAP(CControlsetDialog)
	ON_EN_SETFOCUS(IDC_EDIT_LEFT1, OnSetfocusEditLeft1)
	ON_EN_SETFOCUS(IDC_EDIT_RIGHT1, OnSetfocusEditRight1)
	ON_EN_SETFOCUS(IDC_EDIT_ROTATE1, OnSetfocusEditRotate1)
	ON_EN_SETFOCUS(IDC_EDIT_BOTTOM1, OnSetfocusEditBottom1)
	ON_EN_SETFOCUS(IDC_EDIT_DOWN1, OnSetfocusEditDown1)
	ON_EN_SETFOCUS(IDC_EDIT_LEFT2, OnSetfocusEditLeft2)
	ON_EN_SETFOCUS(IDC_EDIT_RIGHT2, OnSetfocusEditRight2)
	ON_EN_SETFOCUS(IDC_EDIT_ROTATE2, OnSetfocusEditRotate2)
	ON_EN_SETFOCUS(IDC_EDIT_BOTTOM2, OnSetfocusEditBottom2)
	ON_EN_SETFOCUS(IDC_EDIT_DOWN2, OnSetfocusEditDown2)
	ON_WM_TIMER()
	ON_EN_KILLFOCUS(IDC_EDIT_BOTTOM1, OnKillfocusEditBottom1)
	ON_EN_KILLFOCUS(IDC_EDIT_BOTTOM2, OnKillfocusEditBottom2)
	ON_EN_KILLFOCUS(IDC_EDIT_DOWN1, OnKillfocusEditDown1)
	ON_EN_KILLFOCUS(IDC_EDIT_DOWN2, OnKillfocusEditDown2)
	ON_EN_KILLFOCUS(IDC_EDIT_LEFT1, OnKillfocusEditLeft1)
	ON_EN_KILLFOCUS(IDC_EDIT_LEFT2, OnKillfocusEditLeft2)
	ON_EN_KILLFOCUS(IDC_EDIT_RIGHT1, OnKillfocusEditRight1)
	ON_EN_KILLFOCUS(IDC_EDIT_RIGHT2, OnKillfocusEditRight2)
	ON_EN_KILLFOCUS(IDC_EDIT_ROTATE1, OnKillfocusEditRotate1)
	ON_EN_KILLFOCUS(IDC_EDIT_ROTATE2, OnKillfocusEditRotate2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CControlsetDialog message handlers

BOOL CControlsetDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	playercontrol=-1;

	GetDlgItem(IDC_EDIT_LEFT1)->SetWindowText(	KeyDefString[Keydef[0][KeyDef_Left]]);
	GetDlgItem(IDC_EDIT_LEFT2)->SetWindowText(	KeyDefString[Keydef[1][KeyDef_Left]]);
	GetDlgItem(IDC_EDIT_RIGHT1)->SetWindowText(	KeyDefString[Keydef[0][KeyDef_Right]]);
	GetDlgItem(IDC_EDIT_RIGHT2)->SetWindowText(	KeyDefString[Keydef[1][KeyDef_Right]]);
	GetDlgItem(IDC_EDIT_ROTATE1)->SetWindowText(KeyDefString[Keydef[0][KeyDef_Rotate]]);
	GetDlgItem(IDC_EDIT_ROTATE2)->SetWindowText(KeyDefString[Keydef[1][KeyDef_Rotate]]);
	GetDlgItem(IDC_EDIT_BOTTOM1)->SetWindowText(KeyDefString[Keydef[0][KeyDef_Bottom]]);
	GetDlgItem(IDC_EDIT_BOTTOM2)->SetWindowText(KeyDefString[Keydef[1][KeyDef_Bottom]]);
	GetDlgItem(IDC_EDIT_DOWN1)->SetWindowText(	KeyDefString[Keydef[0][KeyDef_Down]]);
	GetDlgItem(IDC_EDIT_DOWN2)->SetWindowText(	KeyDefString[Keydef[1][KeyDef_Down]]);

	InitDirectInput(m_hWnd);
	SetTimer(1000, 50, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CControlsetDialog::OnCancel()
{
	KillTimer(1000);
	FreeDirectInput();
	CDialog::OnCancel();
}

void CControlsetDialog::OnOK() 
{
	KillTimer(1000);
	FreeDirectInput();
	UpdateData();	
	CDialog::OnOK();
}

void CControlsetDialog::OnTimer(UINT nIDEvent)
{	//每间隔一定时间读取键盘缓冲，如果有输入则保存到keydef数组
	if(playercontrol!=-1)
	{
		DWORD dwElements;
		DIDEVICEOBJECTDATA didod[ DINPUT_BUFFER_SIZE ];
		ReadBufferedData(didod, dwElements);
		if(dwElements<DINPUT_BUFFER_SIZE)
			for(DWORD i=0;i<dwElements;i++)
				if((didod[i].dwData & 0x80) && didod[i].dwOfs!=0x0f)
				{
					Keydef[playercontrol][nkeydef]=didod[i].dwOfs;
					GetDlgItem(ControlID)->SetWindowText(KeyDefString[didod[i].dwOfs]);
					NextDlgCtrl();
					if(playercontrol==-1)
						break;
				}
	}
	CDialog::OnTimer(nIDEvent);
}
//当不同的edit control得到焦点的时候改变playercontrol和nkeydef、controlid的值
void CControlsetDialog::OnSetfocusEditLeft1() 
{	playercontrol=0;	nkeydef=0;	ControlID=IDC_EDIT_LEFT1;	}
void CControlsetDialog::OnSetfocusEditRight1() 
{	playercontrol=0;	nkeydef=1;	ControlID=IDC_EDIT_RIGHT1;	}
void CControlsetDialog::OnSetfocusEditRotate1() 
{	playercontrol=0;	nkeydef=2;	ControlID=IDC_EDIT_ROTATE1;	}
void CControlsetDialog::OnSetfocusEditBottom1() 
{	playercontrol=0;	nkeydef=3;	ControlID=IDC_EDIT_BOTTOM1;	}
void CControlsetDialog::OnSetfocusEditDown1() 
{	playercontrol=0;	nkeydef=4;	ControlID=IDC_EDIT_DOWN1;	}
void CControlsetDialog::OnSetfocusEditLeft2() 
{	playercontrol=1;	nkeydef=0;	ControlID=IDC_EDIT_LEFT2;	}
void CControlsetDialog::OnSetfocusEditRight2() 
{	playercontrol=1;	nkeydef=1;	ControlID=IDC_EDIT_RIGHT2;	}
void CControlsetDialog::OnSetfocusEditRotate2() 
{	playercontrol=1;	nkeydef=2;	ControlID=IDC_EDIT_ROTATE2;	}
void CControlsetDialog::OnSetfocusEditBottom2() 
{	playercontrol=1;	nkeydef=3;	ControlID=IDC_EDIT_BOTTOM2;	}
void CControlsetDialog::OnSetfocusEditDown2() 
{	playercontrol=1;	nkeydef=4;	ControlID=IDC_EDIT_DOWN2;	}

void CControlsetDialog::OnKillfocusEditBottom1() {	playercontrol=-1;}
void CControlsetDialog::OnKillfocusEditBottom2() {	playercontrol=-1;}
void CControlsetDialog::OnKillfocusEditDown1() {	playercontrol=-1;}
void CControlsetDialog::OnKillfocusEditDown2() {	playercontrol=-1;}
void CControlsetDialog::OnKillfocusEditLeft1() {	playercontrol=-1;}
void CControlsetDialog::OnKillfocusEditLeft2() {	playercontrol=-1;}
void CControlsetDialog::OnKillfocusEditRight1() {	playercontrol=-1;}
void CControlsetDialog::OnKillfocusEditRight2() {	playercontrol=-1;}
void CControlsetDialog::OnKillfocusEditRotate1() {	playercontrol=-1;}
void CControlsetDialog::OnKillfocusEditRotate2() {	playercontrol=-1;}
