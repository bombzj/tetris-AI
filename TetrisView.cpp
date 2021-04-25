// TetrisView.cpp : implementation of the CTetrisView class
//

#include "stdafx.h"
#include "Tetris.h"

#include "TetrisDoc.h"
#include "TetrisView.h"

#include "Tetrisinput.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTetrisView
extern	CMusicSegment*			g_pSound[MAX_SOUND];
extern	CMusicSegment*			g_pMusic[MAX_MUSIC];

IMPLEMENT_DYNCREATE(CTetrisView, CFormView)

BEGIN_MESSAGE_MAP(CTetrisView, CFormView)
	//{{AFX_MSG_MAP(CTetrisView)
	ON_COMMAND(ID_GAME_NEW, OnGameNew)
	ON_COMMAND(ID_GAME_OPTION, OnGameOption)
	ON_COMMAND(ID_GAME_PAUSE, OnGamePause)
	ON_COMMAND(ID_GAME_CONTROL, OnGameControl)
	ON_COMMAND(ID_GAME_STOP, OnGameStop)
	ON_COMMAND(ID_PLAYER1, OnPlayer1)
	ON_UPDATE_COMMAND_UI(ID_PLAYER1, OnUpdatePlayer1)
	ON_COMMAND(ID_PLAYER2, OnPlayer2)
	ON_UPDATE_COMMAND_UI(ID_PLAYER2, OnUpdatePlayer2)
	ON_WM_MOVE()
	ON_WM_PAINT()
	ON_WM_KILLFOCUS()
	ON_UPDATE_COMMAND_UI(ID_GAME_PAUSE, OnUpdateGamePause)
	ON_UPDATE_COMMAND_UI(ID_GAME_OPTION, OnUpdateGameOption)
	ON_UPDATE_COMMAND_UI(ID_GAME_STOP, OnUpdateGameStop)
	ON_WM_TIMER()
	ON_COMMAND(ID_GAME_PLAYMUSIC, OnGamePlaymusic)
	ON_UPDATE_COMMAND_UI(ID_GAME_PLAYMUSIC, OnUpdateGamePlaymusic)
	ON_COMMAND(ID_GAME_PLAYSOUND, OnGamePlaysound)
	ON_UPDATE_COMMAND_UI(ID_GAME_PLAYSOUND, OnUpdateGamePlaysound)
	ON_COMMAND(ID_COMPUTER, OnComputer)
	ON_UPDATE_COMMAND_UI(ID_COMPUTER, OnUpdateComputer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTetrisView construction/destruction

CTetrisView::CTetrisView()
	: CFormView(CTetrisView::IDD)
{
	//{{AFX_DATA_INIT(CTetrisView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	DefaultKeydef[0][0]=0x1e;
	DefaultKeydef[0][1]=0x20;
	DefaultKeydef[0][2]=0x11;
	DefaultKeydef[0][4]=0x39;
	DefaultKeydef[0][3]=0x1f;
	DefaultKeydef[1][0]=0xcb;
	DefaultKeydef[1][1]=0xcd;
	DefaultKeydef[1][2]=0xc8;
	DefaultKeydef[1][3]=0xcf;
	DefaultKeydef[1][4]=0xd0;
	ReadSettings();
}

CTetrisView::~CTetrisView()
{
	WriteSettings();
	FreeDirectMusic();
	tetris_game.Destroy();
}

void CTetrisView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTetrisView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BOOL CTetrisView::PreCreateWindow(CREATESTRUCT& cs)
{
	//  the CREATESTRUCT cs
	return CFormView::PreCreateWindow(cs);
}

void CTetrisView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
//	ResizeParentToFit();
	SetScrollSizes(MM_TEXT, CSize(0,0));

	srand(time(NULL));

	tetris_game.Create(this);
	SetTimer(ID_GAME_TIMER, 1, NULL);
}


void CTetrisView::ReadSettings()
{
	CWinApp* app=AfxGetApp();
	CString tmp;
	for(int p=0; p<MAX_PLAYER; p++)
		for(DWORD j = 0; j < MAX_KEYDEF; j++ )
		{
			tmp.Format(L"Keydef%d%d", p, j);
			controlsetdlg.Keydef[p][j] = keystatus[p][j].Keydef = app->GetProfileInt(_T("Keydef"), tmp, DefaultKeydef[p][j]);
			
		}
	tetris_game.SetSoundOn(app->GetProfileInt(_T("Config"), _T("playsound"), TRUE));
	tetris_game.SetMusicOn(app->GetProfileInt(_T("Config"), _T("playmusic"), TRUE));
	tetris_game.SetPlayerNumber(app->GetProfileInt(_T("Config"), _T("playernumber"), 1));
	optiondlg.m_othereffect = app->GetProfileInt(_T("Config"), _T("othereffect"), TRUE);
	optiondlg.m_smoothdown = app->GetProfileInt(_T("Config"), _T("smoothdown"), TRUE);
	optiondlg.m_smoothrotate = app->GetProfileInt(_T("Config"), _T("smoothrotate"), TRUE);
	optiondlg.m_leftwindow = app->GetProfileInt(_T("Config"), _T("leftwindow"), FALSE);
	optiondlg.m_ailevel = app->GetProfileInt(_T("Config"), _T("ailevel"), 3);
	optiondlg.m_level = app->GetProfileInt(_T("Config"), _T("level"), 3);
	optiondlg.m_difficulty = app->GetProfileInt(_T("Config"), _T("difficulty"), 0);
	optiondlg.m_shownext = app->GetProfileInt(_T("Config"), _T("shownext"), TRUE);
	optiondlg.m_edit_volumn = app->GetProfileInt(_T("Config"), _T("volumn"), 100);

	tetris_game.SetParam(optiondlg.m_smoothdown, optiondlg.m_smoothrotate,
		optiondlg.m_leftwindow, optiondlg.m_ailevel, optiondlg.m_level, optiondlg.m_difficulty, 
		optiondlg.m_shownext, optiondlg.m_othereffect, optiondlg.m_edit_volumn);
}

void CTetrisView::WriteSettings()
{
	CWinApp* app=AfxGetApp();
	CString tmp;
	for(int p=0; p<MAX_PLAYER; p++)
		for(DWORD j = 0; j < MAX_KEYDEF; j++ )
		{
			tmp.Format(L"Keydef%d%d", p, j);
			app->WriteProfileInt(_T("Keydef"), tmp, keystatus[p][j].Keydef);
		}
	app->WriteProfileInt(_T("Config"), _T("playsound"), tetris_game.IsSoundOn());
	app->WriteProfileInt(_T("Config"), _T("playmusic"), tetris_game.IsMusicOn());
	app->WriteProfileInt(_T("Config"), _T("playernumber"), tetris_game.GetPlayerNumber());
	app->WriteProfileInt(_T("Config"), _T("othereffect"), optiondlg.m_othereffect);
	app->WriteProfileInt(_T("Config"), _T("smoothdown"), optiondlg.m_smoothdown);
	app->WriteProfileInt(_T("Config"), _T("smoothrotate"), optiondlg.m_smoothrotate);
	app->WriteProfileInt(_T("Config"), _T("leftwindow"), optiondlg.m_leftwindow);
	app->WriteProfileInt(_T("Config"), _T("ailevel"), optiondlg.m_ailevel);
	app->WriteProfileInt(_T("Config"), _T("level"), optiondlg.m_level);
	app->WriteProfileInt(_T("Config"), _T("difficulty"), optiondlg.m_difficulty);
	app->WriteProfileInt(_T("Config"), _T("shownext"), optiondlg.m_shownext);
	app->WriteProfileInt(_T("Config"), _T("volumn"), optiondlg.m_edit_volumn);

	tetris_game.SetParam(optiondlg.m_smoothdown, optiondlg.m_smoothrotate,
		optiondlg.m_leftwindow, optiondlg.m_ailevel, optiondlg.m_level, optiondlg.m_difficulty,
		optiondlg.m_shownext, optiondlg.m_othereffect, optiondlg.m_edit_volumn);
}
/////////////////////////////////////////////////////////////////////////////
// CTetrisView diagnostics

#ifdef _DEBUG
void CTetrisView::AssertValid() const
{
	CFormView::AssertValid();
}

void CTetrisView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CTetrisDoc* CTetrisView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTetrisDoc)));
	return (CTetrisDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTetrisView message handlers

void CTetrisView::OnGameNew()
{
	if(tetris_game.IsPlaying())
		tetris_game.StopGame(FALSE);

	InitDirectInput(AfxGetMainWnd()->m_hWnd);
	tetris_game.NewGame();
	LastTime_Game=timeGetTime();
	ResetInputBuffer();
}

void CTetrisView::OnGamePause() 
{
	if(tetris_game.IsPlaying())
	{
		tetris_game.TogglePause();
		if(tetris_game.IsPaused())
		{
			FreeDirectInput();
			ResetInputBuffer();
		}
		else
			InitDirectInput(AfxGetMainWnd()->m_hWnd);
	}
}

void CTetrisView::OnUpdateGamePause(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(tetris_game.IsPaused());
	pCmdUI->Enable(tetris_game.IsPlaying());
}


void CTetrisView::OnGameOption() 
{
	if(optiondlg.DoModal()!=IDOK)
		return;
	WriteSettings();
}
void CTetrisView::OnGameControl() 
{
	if(controlsetdlg.DoModal()!=IDOK)
	{
		for(int p=0; p<MAX_PLAYER; p++)
			for(DWORD j = 0; j < MAX_KEYDEF; j++ )
				controlsetdlg.Keydef[p][j] = keystatus[p][j].Keydef;
		return;
	}
	for(int p=0; p<MAX_PLAYER; p++)
		for(DWORD j = 0; j < MAX_KEYDEF; j++ )
			keystatus[p][j].Keydef = controlsetdlg.Keydef[p][j];
	WriteSettings();
}

void CTetrisView::OnUpdateGameOption(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!tetris_game.IsPlaying());
}

void CTetrisView::OnGameStop() 
{
	tetris_game.StopGame();
	FreeDirectInput();
}

void CTetrisView::OnUpdateGameStop(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(tetris_game.IsPlaying());
}

void CTetrisView::ResetInputBuffer()
{
	for(int p=0;p<2;p++)
		for(int i=0;i<5;i++)
			keystatus[p][i].bKeydown=FALSE;
}

void CTetrisView::OnPlayer1() 
{	tetris_game.SetPlayerNumber(1);	
}
void CTetrisView::OnPlayer2() 
{	tetris_game.SetPlayerNumber(2);	
}
void CTetrisView::OnComputer() 
{	tetris_game.SetPlayerNumber(3);	
}
void CTetrisView::OnUpdatePlayer1(CCmdUI* pCmdUI) 
{	pCmdUI->SetCheck(tetris_game.GetPlayerNumber()==1);
	pCmdUI->Enable(!tetris_game.IsPlaying());
}
void CTetrisView::OnUpdatePlayer2(CCmdUI* pCmdUI) 
{	pCmdUI->SetCheck(tetris_game.GetPlayerNumber()==2);
	pCmdUI->Enable(!tetris_game.IsPlaying());
}
void CTetrisView::OnUpdateComputer(CCmdUI* pCmdUI) 
{	pCmdUI->SetCheck(tetris_game.GetPlayerNumber()==3);
	pCmdUI->Enable(!tetris_game.IsPlaying());
}
void CTetrisView::OnGamePlaymusic() 
{	tetris_game.SetMusicOn(!tetris_game.IsMusicOn());
}
void CTetrisView::OnUpdateGamePlaymusic(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(tetris_game.IsMusicOn()&&g_pMusic[0]!=NULL);	pCmdUI->Enable(g_pMusic[0]!=NULL);
}
void CTetrisView::OnGamePlaysound() 
{	tetris_game.SetSoundOn(!tetris_game.IsSoundOn());
}
void CTetrisView::OnUpdateGamePlaysound(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(tetris_game.IsSoundOn()&&g_pSound[0]!=NULL);	pCmdUI->Enable(g_pSound[0]!=NULL);
}


void CTetrisView::OnMove(int x, int y) 
{
	CFormView::OnMove(x, y);
	tetris_game.UpdateRect();
}

void CTetrisView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	tetris_game.UpdateRect();	

	// Do not call CFormView::OnPaint() for painting messages
}

void CTetrisView::OnKillFocus(CWnd* pNewWnd) 
{
	CFormView::OnKillFocus(pNewWnd);
	tetris_game.PauseGame();
}

void CTetrisView::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent==ID_GAME_TIMER)	
	{

		DWORD curTime=timeGetTime();
		if(tetris_game.IsPaused())
			return;

		DWORD interval=curTime-LastTime_Game;
		if(interval<ANIME_TIME)
			return;
		LastTime_Game+=interval/ANIME_TIME*ANIME_TIME;

		if(tetris_game.IsPlaying())
		{
			/******¶ÁÈ¡directinputµÄ»º³åÇø******/
			DWORD dwElements;
			DIDEVICEOBJECTDATA didod[ DINPUT_BUFFER_SIZE ];
			ReadBufferedData(didod, dwElements);
			if(dwElements<DINPUT_BUFFER_SIZE)
				for(int p=0; p<MAX_PLAYER; p++)
					for(DWORD j = 0; j < MAX_KEYDEF; j++ ) 
					{
						keystatus[p][j].bKeyPress=FALSE;
						for(DWORD i = 0; i < dwElements; i++ ) 
							if(keystatus[p][j].Keydef==didod[i].dwOfs)
							{
								keystatus[p][j].bKeydown = (didod[i].dwData & 0x80) ? TRUE : FALSE;
								if(keystatus[p][j].bKeydown)
								{
									keystatus[p][j].bKeyPress = TRUE;
									keystatus[p][j].DownTime=curTime;
								}
							}
					}
		}
		tetris_game.Animate(keystatus, curTime);

	}
	CFormView::OnTimer(nIDEvent);
}
