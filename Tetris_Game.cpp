// CTetris_Game.cpp: implementation of the CTetris_Game class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Tetris.h"
#include "Tetris_Game.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern	CMusicManager*          g_pMusicManager;
extern	IDirectMusicAudioPath*  g_p3DAudiopath;
extern	CMusicSegment*			g_pSound[MAX_SOUND];
extern	CMusicSegment*			g_pMusic[MAX_MUSIC];

#define BLOCK_WIDTH	24
#define BLOCK_TYPE	8
#define SCORE_DIGIT	8

#define EFFECT_NOT_START	-1
#define EFFECT_START		0
#define EACH_PLAYER(p) for(p=0; p<MAX_PLAYER; p++)	if(m_bWindowRendering[p])

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
POINT PlayerRect[2]={38,20,482,20};
POINT NextBlockRect[2]={299,43,365,102};
POINT ScoreRect[2]={456, 399, 477, 458};
POINT NFloorRect[2]={38, 514, 482, 514};
POINT LevelRect={352, 246};
POINT SubtitleRect[2]={48,-40,492,-40};

struct// fPoint
{
	float x,y;
}
BaseShapeCenter[SHAPES_NUMBER]={
		1.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f, 
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.5f, 0.5f,
		1.0f, 1.0f,
};
POINT NextBlockTopLeft[SHAPES_NUMBER]={
		0,				BLOCK_WIDTH/2,
		-BLOCK_WIDTH/2, 0,
		-BLOCK_WIDTH/2, 0,
		-BLOCK_WIDTH/2, 0,
		-BLOCK_WIDTH/2, 0,
		-BLOCK_WIDTH/2, 0,
		0,				0,
		-BLOCK_WIDTH/2, BLOCK_WIDTH/2,
};

int scorelevel[4]={100, 250, 400, 600};

CTetris_Game::CTetris_Game()
{
	int i, j;
	m_Texture_Block = NULL;
	m_Texture_Background = NULL;
	m_Texture_Score = NULL;
	m_Texture_Level = NULL;
	m_Texture_NFloor = NULL;
	m_Texture_GrayBlock = NULL;
	m_Texture_GamePaused = NULL;
	m_Texture_Subtitle = NULL;
	m_Texture_Changewhite = NULL;
	m_Texture_Explode = NULL;
	m_Texture_Crash = NULL;

	for(i=0;i<MAX_SOUND;i++)		g_pSound[i]	= NULL;
	for(i=0;i<MAX_MUSIC;i++)		g_pMusic[i]	= NULL;

	//m_bUseDepthBuffer           = TRUE;
	CTetrisControl::InitBasicShapes();
	CTetrisControl::InitScoreLevel(scorelevel);
	// TODO: ?
	//m_hWnd = 0;
	TimerInterval[0]=BASELEVEL_INTERVAL;
	for(i=1;i<=MAX_LEVEL;i++)
		TimerInterval[i]=int(TimerInterval[i-1]/LEVEL_DIFFERENCE);

	//set all texture tile position (tu tv etc.)
	for(i=0;i<BLOCK_TYPE;i++)
		for(j=0;j<BLOCK_FRAME;j++)
			SetTextureRect(BlockRect[i][j], (float)i/BLOCK_TYPE, (float)j/BLOCK_FRAME, (float)(i+1)/BLOCK_TYPE, (float)(j+1)/BLOCK_FRAME, BLOCK_WIDTH, BLOCK_WIDTH);

	for(i=0;i<BLOCK_TYPE;i++)
		for(j=0;j<CHANGEWHITE_FRAME;j++)
			SetTextureRect(ChangewhiteRect[i][j], (float)i/BLOCK_TYPE, (float)j/CHANGEWHITE_FRAME, (float)(i+1)/BLOCK_TYPE, (float)(j+1)/CHANGEWHITE_FRAME, BLOCK_WIDTH, BLOCK_WIDTH);

	for(i=0;i<SCORE_NUMBER;i++)
		SetTextureRect(ScoreNumberRect[i], (float)i/SCORE_NUMBER, 0, (float)(i+1)/SCORE_NUMBER, 1.0f, SCORE_WIDTH, SCORE_HEIGHT);

	for(i=0;i<LEVEL_NUMBER;i++)
		SetTextureRect(LevelNumberRect[i], (float)i/LEVEL_NUMBER, 0, (float)(i+1)/LEVEL_NUMBER, 1.0f, LEVEL_WIDTH, LEVEL_HEIGHT);

	for(i=0;i<NFLOOR_TYPE;i++)
		for(j=0;j<NFLOOR_FRAME;j++)
			SetTextureRect(NFloorTypeRect[i][j], (float)i/NFLOOR_TYPE, (float)j/NFLOOR_FRAME, (float)(i+1)/NFLOOR_TYPE, (float)(j+1)/NFLOOR_FRAME, NFLOOR_WIDTH, NFLOOR_WIDTH);

	for(i=0;i<SUBTITLE_NUMBER;i++)
		SetTextureRect(SubtitleTypeRect[i], 0, (float)i/SUBTITLE_NUMBER, 1.0f, (float)(i+1)/SUBTITLE_NUMBER, SUBTITLE_WIDTH, SUBTITLE_HEIGHT);

	for(i=0;i<CRASH_FRAME;i++)
		SetTextureRect(CrashRect[i], 0, (float)i/CRASH_FRAME, 1.0f, (float)(i+1)/CRASH_FRAME, CRASH_WIDTH, CRASH_HEIGHT);

	for(i=0;i<EXPLODE_FRAME;i++)
	{
		for(j=0;j<EXPLODE_TYPE;j++)
		{
			SetTextureRect(ExplodeRect[j*EXPLODE_DIRECTION+0][i], (float)j/EXPLODE_TYPE, (float)i/EXPLODE_FRAME, (float)(j+1)/EXPLODE_TYPE, (float)(i+1)/EXPLODE_FRAME, EXPLODE_WIDTH, EXPLODE_HEIGHT);
			SetTextureRect(ExplodeRect[j*EXPLODE_DIRECTION+1][i], (float)(j+1)/EXPLODE_TYPE, (float)i/EXPLODE_FRAME, (float)j/EXPLODE_TYPE, (float)(i+1)/EXPLODE_FRAME, EXPLODE_WIDTH, EXPLODE_HEIGHT);
			SetTextureRect(ExplodeRect[j*EXPLODE_DIRECTION+2][i], (float)j/EXPLODE_TYPE, (float)(i+1)/EXPLODE_FRAME, (float)(j+1)/EXPLODE_TYPE, (float)i/EXPLODE_FRAME, EXPLODE_WIDTH, EXPLODE_HEIGHT);
			SetTextureRect(ExplodeRect[j*EXPLODE_DIRECTION+3][i], (float)(j+1)/EXPLODE_TYPE, (float)(i+1)/EXPLODE_FRAME, (float)j/EXPLODE_TYPE, (float)i/EXPLODE_FRAME, EXPLODE_WIDTH, EXPLODE_HEIGHT);
			SetTextureRect(ExplodeRect[j*EXPLODE_DIRECTION+4][i], (float)j/EXPLODE_TYPE, (float)i/EXPLODE_FRAME, (float)(j+1)/EXPLODE_TYPE, (float)(i+1)/EXPLODE_FRAME, EXPLODE_WIDTH, EXPLODE_HEIGHT, FALSE);
			SetTextureRect(ExplodeRect[j*EXPLODE_DIRECTION+5][i], (float)(j+1)/EXPLODE_TYPE, (float)i/EXPLODE_FRAME, (float)j/EXPLODE_TYPE, (float)(i+1)/EXPLODE_FRAME, EXPLODE_WIDTH, EXPLODE_HEIGHT, FALSE);
			SetTextureRect(ExplodeRect[j*EXPLODE_DIRECTION+6][i], (float)j/EXPLODE_TYPE, (float)(i+1)/EXPLODE_FRAME, (float)(j+1)/EXPLODE_TYPE, (float)i/EXPLODE_FRAME, EXPLODE_WIDTH, EXPLODE_HEIGHT, FALSE);
			SetTextureRect(ExplodeRect[j*EXPLODE_DIRECTION+7][i], (float)(j+1)/EXPLODE_TYPE, (float)(i+1)/EXPLODE_FRAME, (float)j/EXPLODE_TYPE, (float)i/EXPLODE_FRAME, EXPLODE_WIDTH, EXPLODE_HEIGHT, FALSE);
		}
	}
	SetallOffset(ExplodeCenterOffset+EXPLODE_DIRECTION*0, 33, 15);
	SetallOffset(ExplodeCenterOffset+EXPLODE_DIRECTION*1, 24, 24);
	SetallOffset(ExplodeCenterOffset+EXPLODE_DIRECTION*2, 30, 24);
	SetallOffset(ExplodeCenterOffset+EXPLODE_DIRECTION*3, 36, 24);
	//不同颜色块的爆炸颜色
	BlockColor[0].r=255;	BlockColor[0].g=0;		BlockColor[0].b=0;
	BlockColor[1].r=250;	BlockColor[1].g=187;	BlockColor[1].b=0;
	BlockColor[2].r=255;	BlockColor[2].g=35;		BlockColor[2].b=200;
	BlockColor[3].r=0;		BlockColor[3].g=70;		BlockColor[3].b=255;
	BlockColor[4].r=0;		BlockColor[4].g=255;	BlockColor[4].b=70;
	BlockColor[5].r=150;	BlockColor[5].g=250;	BlockColor[5].b=100;
	BlockColor[6].r=30;		BlockColor[6].g=255;	BlockColor[6].b=255;
	BlockColor[7].r=100;	BlockColor[7].g=0;		BlockColor[7].b=200;

	for(i=0;i<MAX_SUBTITLE;i++)
		Subtitle[i].subcount=0;

}

void CTetris_Game::SetallOffset(SIZE *size, int cx, int cy)
{
	const int offset=BLOCK_WIDTH/2;
	int cx2 = EXPLODE_WIDTH-cx, cy2 = EXPLODE_HEIGHT-cy;
	(size+0)->cx=offset-cx,		(size+0)->cy=offset-cy;
	(size+1)->cx=offset-cx2,	(size+1)->cy=offset-cy;
	(size+2)->cx=offset-cx,		(size+2)->cy=offset-offset-cy;
	(size+3)->cx=offset-cx2,	(size+3)->cy=offset-offset-cy;
	(size+4)->cy=offset-cx,		(size+4)->cx=offset-cy;
	(size+5)->cy=offset-cx2,	(size+5)->cx=offset-cy;
	(size+6)->cy=offset-cx,		(size+6)->cx=offset-offset-cy;
	(size+7)->cy=offset-cx2,	(size+7)->cx=offset-offset-cy;
}

CTetris_Game::~CTetris_Game()
{
}

HRESULT CALLBACK OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
	void* pUserContext)
{
	CTetris_Game* tg = (CTetris_Game*)pUserContext;
	//tg->m_pd3dDevice = pd3dDevice;
	//tg->InitDeviceObjects();
	//tg->RestoreDeviceObjects();
	return S_OK;
}
HRESULT CALLBACK OnResetDevice(IDirect3DDevice9* pd3dDevice,
	const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	CTetris_Game* tg = (CTetris_Game*)pUserContext;
	tg->m_pd3dDevice = pd3dDevice;
	tg->InitDeviceObjects();
	tg->RestoreDeviceObjects();
	return S_OK;
}
void CALLBACK OnDestroyDevice(void* pUserContext)
{
}
void CALLBACK OnLostDevice(void* pUserContext)
{
	CTetris_Game* tg = (CTetris_Game*)pUserContext;
	tg->DeleteDeviceObjects();
}
HRESULT CTetris_Game::Create(CWnd *wnd)
{
	//HRESULT hr;
	//m_hWnd=wnd->m_hWnd;

	/*		Migration from dx8sdk steps
		remove d3dapp.cpp with CD3DApplication and related code lines
		change SetVertexShader to SetFVF
		add dxsdk include/lib dirs to project setting and move windows sdk kit to above (prior to dxsdk)
		change to unicode and added a lot of wchar_t
		change ZI to Zi in c++/general/debug information format
		LPDIRECT3DTEXTURE8 -> LPDIRECT3DTEXTURE9
		D3DMATERIAL8 -> D3DMATERIAL9
		add device creation codes below
		use dxguid.lib from dxsdk9 (totally different from the one in newest sdk) for directmusic, rename it to dxguid2.lib for link
	*/
	DXUTSetCallbackD3D9DeviceCreated(OnCreateDevice, this);		// side effect: force d3d9
	DXUTSetCallbackD3D9DeviceLost(OnLostDevice, this);
	DXUTSetCallbackD3D9DeviceDestroyed(OnDestroyDevice, this);
	DXUTSetCallbackD3D9DeviceReset(OnResetDevice, this);
	DXUTInit();
	DXUTSetWindow(wnd->m_hWnd, wnd->m_hWnd, wnd->m_hWnd, false);

	DXUTCreateDevice();

	InitDirectMusic(AfxGetMainWnd()->m_hWnd);
	if(g_p3DAudiopath)
		g_p3DAudiopath->SetVolume(m_volumn, 0);
	StopGame();
	return S_OK;
}

void CTetris_Game::SetParam(BOOL smoothdown, BOOL smoothrotate, BOOL leftwindow, int ailevel, int level, 
							int difficulty, BOOL shownext, BOOL othereffect, int volumn)
{
	m_smoothdown = smoothdown;
	m_smoothrotate = smoothrotate;
	m_leftwindow = leftwindow;
	m_AILevel = ailevel;
	m_Level = level;
	m_difficulty = difficulty;
	m_shownext = shownext;
	m_othereffect=othereffect;
	m_volumn = (volumn-100)*20;	//-9600~~0

	if(g_p3DAudiopath)
		g_p3DAudiopath->SetVolume(m_volumn, 0);
}

HRESULT CTetris_Game::Display()
{
	int p, i, j;

/*******绘制整个区域*******/
	Blt3D(0, 0, m_Texture_Background, BG_WIDTH, BG_HEIGHT);
	for(p=0;p<MAX_PLAYER;p++)	if(m_bWindowRendering[p])
	{
		CShape &tmp=TetrisEngine[p].GetCurShape();
		CShape &tmp2=TetrisEngine[p].GetNextShape();
		if(TetrisEngine[p].IsGameOver()&&m_AddFloor[p]==EFFECT_NOT_START)
		{
			/***********绘制GameOver游戏区域**********/
			for(i=0;i<HORIZONTAL_BLOCKS_NUMBER;i++)//
				for(j=0;j<VERTICAL_BLOCKS_NUMBER;j++)
					if(TetrisEngine[p].GetBlock(i, j).m_nStatus==HAVE_BLOCK)
					{
						if(m_GameOver_Counter[p]<(20-j)*CHANGEGRAY_FRAME)
							Blt3D( PlayerRect[p].x+i*BLOCK_WIDTH, PlayerRect[p].y+j*BLOCK_WIDTH, 
								m_Texture_Block, BlockRect[TetrisEngine[p].GetBlock(i, j).m_nColor]+AnimeFrame/BLOCK_CPF%BLOCK_FRAME);
						else
							Blt3D( PlayerRect[p].x+i*BLOCK_WIDTH, PlayerRect[p].y+j*BLOCK_WIDTH, 
								m_Texture_GrayBlock, BLOCK_WIDTH, BLOCK_WIDTH);
					}
			m_GameOver_Counter[p]++;
		}
		else
		{
			CShape &tmp=TetrisEngine[p].GetCurShape();
			CShape &tmp2=TetrisEngine[p].GetNextShape();
			/***********绘制正在消去（爆炸）的行**********/
			if(m_Explode[p]!=EFFECT_NOT_START)
			{
				byte downfloor[VERTICAL_BLOCKS_NUMBER]={0};//计算需要下降的层数
				for(i=0;i<4;i++)
					if(TetrisEngine[p].GetCramedFloor(i)!=-1)
						for(j=0;j<TetrisEngine[p].GetCramedFloor(i);j++)
							downfloor[j]++;
				for(j=0;j<VERTICAL_BLOCKS_NUMBER;j++)
				{
					if(TetrisEngine[p].GetCurBlocksInFloor(VERTICAL_BLOCKS_NUMBER-1-j)<HORIZONTAL_BLOCKS_NUMBER)
					{
						for(i=0;i<HORIZONTAL_BLOCKS_NUMBER;i++)//
							if(TetrisEngine[p].GetBlock(i, j).m_nStatus==HAVE_BLOCK)
							{
								int downpixel=0;
								int downline=m_Explode[p]-DELLINE_DOWN_TIME;
								if(downline>0)//其他层开始往下掉
								{
									if(downline/DELLINE_DOWN_FRAME>=downfloor[j])
										downpixel=downfloor[j]*BLOCK_WIDTH;
									else
										downpixel=downline*BLOCK_WIDTH/DELLINE_DOWN_FRAME;
								}

								Blt3D( PlayerRect[p].x+i*BLOCK_WIDTH, PlayerRect[p].y+j*BLOCK_WIDTH + downpixel, 
									m_Texture_Block, BlockRect[TetrisEngine[p].GetBlock(i, j).m_nColor]+AnimeFrame/BLOCK_CPF%BLOCK_FRAME);
							}
					}
					else
					{
						if(m_Explode[p]<CHANGEWHITE_FRAME)
						{
							for(i=0;i<HORIZONTAL_BLOCKS_NUMBER;i++)
								Blt3D( PlayerRect[p].x+i*BLOCK_WIDTH, PlayerRect[p].y+j*BLOCK_WIDTH, 
									m_Texture_Changewhite, ChangewhiteRect[TetrisEngine[p].GetBlock(i, j).m_nColor]+m_Explode[p]);
						}
						else if(m_Explode[p]<CHANGEWHITE_FRAME+CRASH_FRAME)
							Blt3D( PlayerRect[p].x, PlayerRect[p].y+j*BLOCK_WIDTH, 
								m_Texture_Crash, CrashRect+m_Explode[p]-CHANGEWHITE_FRAME);
						else
						{
							for(i=0;i<HORIZONTAL_BLOCKS_NUMBER;i++)
							{
								int ncolor=TetrisEngine[p].GetBlock(i, j).m_nColor;
								SetColor(ncolor);
								byte nexplode=TetrisEngine[p].GetBlock(i, j).m_nStyle;
								Blt3D( PlayerRect[p].x+i*BLOCK_WIDTH+ExplodeCenterOffset[nexplode].cx, PlayerRect[p].y+j*BLOCK_WIDTH+ExplodeCenterOffset[nexplode].cy, 
									m_Texture_Explode, ExplodeRect[nexplode]+m_Explode[p]-CHANGEWHITE_FRAME-CRASH_FRAME);
							}
							UnSetColor();
						}
					}

				}

			}
			/***********绘制正在增长的行**********/
			else if (m_AddFloor[p]!=EFFECT_NOT_START)
			{
				m_GameOver_Counter[p] = 0;
				float curAddFloor=m_nAddingFloor[p]-(float)m_AddFloor[p]/ADDFLOOR_FRAME;
				for(i=0;i<HORIZONTAL_BLOCKS_NUMBER;i++)
				{
					for(j=0;j<VERTICAL_BLOCKS_NUMBER-int(curAddFloor)-1;j++)
						if(TetrisEngine[p].GetBlock(i, j).m_nStatus==HAVE_BLOCK)
						{
							Blt3D( PlayerRect[p].x+i*BLOCK_WIDTH, PlayerRect[p].y+j*BLOCK_WIDTH + int(BLOCK_WIDTH * curAddFloor), 
								m_Texture_Block, BlockRect[TetrisEngine[p].GetBlock(i, j).m_nColor]+AnimeFrame/BLOCK_CPF%BLOCK_FRAME);
						}
					
					if(TetrisEngine[p].GetBlock(i, j).m_nStatus==HAVE_BLOCK)
					{
						RECT3D rect=BlockRect[TetrisEngine[p].GetBlock(i, j).m_nColor][AnimeFrame/BLOCK_CPF%BLOCK_FRAME];
						float ftmp=1+int(curAddFloor)-curAddFloor;
						rect.height=int(ftmp*BLOCK_WIDTH);
						rect.point[3].tv=rect.point[1].tv=rect.point[0].tv+ftmp/BLOCK_FRAME;
						Blt3D( PlayerRect[p].x+i*BLOCK_WIDTH, PlayerRect[p].y+j*BLOCK_WIDTH + int(BLOCK_WIDTH * curAddFloor), 
							m_Texture_Block, &rect);
					}
				}
			}
			else
			{
				/***********绘制游戏区域**********/
				for(i=0;i<HORIZONTAL_BLOCKS_NUMBER;i++)//
					for(j=0;j<VERTICAL_BLOCKS_NUMBER;j++)
						if(TetrisEngine[p].GetBlock(i, j).m_nStatus==HAVE_BLOCK)
					{
						Blt3D( PlayerRect[p].x+i*BLOCK_WIDTH, PlayerRect[p].y+j*BLOCK_WIDTH, 
							m_Texture_Block, BlockRect[TetrisEngine[p].GetBlock(i, j).m_nColor]+AnimeFrame/BLOCK_CPF%BLOCK_FRAME);
					}
				/***********绘制正在下落的块**********/
				for(i=0;i<tmp.m_bBlocks;i++)//
				{
					float top, left;//center的坐标
					float rotatedtop, rotatedleft;//计算旋转后的坐标
					float rleft= tmp.m_ptBlocks[i].x-BaseShapeCenter[tmp.m_nColor].x, //rtop为相对center的坐标
						rtop = tmp.m_ptBlocks[i].y-BaseShapeCenter[tmp.m_nColor].y;
					if(m_smoothrotate)
					{
						float alpha = TetrisEngine[p].GetSmoothRotate() * PI / 2,//alpha为旋转的角度
							cosalpha = cosf(alpha), sinalpha = sinf(alpha);
						rotatedleft = rleft * cosalpha + rtop * sinalpha;
						rotatedtop = -rleft * sinalpha + rtop * cosalpha;
						if(TetrisEngine[p].GetSmoothRotate()!=0)
							alpha=alpha;
					}
					else
					{
						rotatedleft	= rleft;
						rotatedtop	= rtop;
					}

					left=(rotatedleft + tmp.m_ptPos.x + BaseShapeCenter[tmp.m_nColor].x)*BLOCK_WIDTH+PlayerRect[p].x;
					top = (rotatedtop + tmp.m_ptPos.y + BaseShapeCenter[tmp.m_nColor].y)*BLOCK_WIDTH+PlayerRect[p].y;
					if(m_smoothdown)
					{
						if(tmp.m_ptPos.y>0)
							top+= (TetrisEngine[p].GetSmoothDown() - 1) * BLOCK_WIDTH;
						else
						{
							float rate=TetrisEngine[p].GetSmoothDown()*2.0f+(float)i/8;
							if(rate>1)	rate=1;
							int nextleft=NextBlockRect[p].x-BLOCK_WIDTH*3+NextBlockTopLeft[tmp.m_nColor].x + (tmp.m_ptBlocks[i].x+tmp.m_ptPos.x) * BLOCK_WIDTH, 
								nexttop=NextBlockRect[p].y+NextBlockTopLeft[tmp.m_nColor].y + (tmp.m_ptBlocks[i].y+tmp.m_ptPos.y) * BLOCK_WIDTH;
							top	=nexttop *(1-rate) + top *	rate;
							left=nextleft*(1-rate) + left*	rate;		
						}
					}
					Blt3D( int(left), int(top), m_Texture_Block, 
									BlockRect[tmp.m_nColor]+AnimeFrame/BLOCK_CPF%BLOCK_FRAME);
				}
			}
		}
		/***********绘制下一个块**********/
		if(m_shownext)
		{
			for(i=0;i<tmp2.m_bBlocks;i++)//
			{
				int left, top;
				left=NextBlockRect[p].x-BLOCK_WIDTH*3+NextBlockTopLeft[tmp2.m_nColor].x;
				top=NextBlockRect[p].y+NextBlockTopLeft[tmp2.m_nColor].y;
				Blt3D( left + (tmp2.m_ptBlocks[i].x+tmp2.m_ptPos.x) * BLOCK_WIDTH, 
							top + (tmp2.m_ptBlocks[i].y+tmp2.m_ptPos.y) * BLOCK_WIDTH, m_Texture_Block, BlockRect[tmp2.m_nColor]);
			}
		}
		/***********绘制将要增加的层数提示**********/
		int nfloor=TetrisEngine[p].GetFloorsBuffer();
		int floortype=(nfloor-1)/2;
		if(floortype>=NFLOOR_TYPE)
			floortype=NFLOOR_TYPE-1;
		int nbomb=nfloor>10 ? 10 : nfloor;
		for(i=0;i<nbomb;i++)
			Blt3D(NFloorRect[p].x+NFLOOR_WIDTH*i, NFloorRect[p].y, m_Texture_NFloor, NFloorTypeRect[floortype]+AnimeFrame/NFLOOR_CPF%NFLOOR_FRAME);
		/***********绘制得分**********/
		int score=m_DisplayScore[p];
		int nspeed=(TetrisEngine[p].GetCurScore()-m_DisplayScore[p])/200;
		m_DisplayScore[p]+=SCORE_ADD_SPEED*(int)pow(2, nspeed);
		if(m_DisplayScore[p]>TetrisEngine[p].GetCurScore())
			m_DisplayScore[p]=TetrisEngine[p].GetCurScore();
		POINT curPoint=ScoreRect[p];
		for(i=0;i<SCORE_DIGIT;i++)
		{
			curPoint.x-=SCORE_WIDTH;
			Blt3D(curPoint.x, curPoint.y, m_Texture_Score, ScoreNumberRect+(score%SCORE_NUMBER));
			score/=SCORE_NUMBER;
		}
		/***********绘制Subtitle**********/
		for(i=0;i<MAX_SUBTITLE;i++)
			if(Subtitle[i].subcount>0)
			{
				int time=Subtitle[i].subtime;
				if(Subtitle[i].subcount<SUBTITLE_TIME1)
					Blt3D(SubtitleRect[Subtitle[i].player].x, SubtitleRect[Subtitle[i].player].y + BG_HEIGHT*Subtitle[i].subcount/3/SUBTITLE_TIME1, 
										m_Texture_Subtitle, SubtitleTypeRect+Subtitle[i].subtitle);
				else if(Subtitle[i].subcount>SUBTITLE_TIME1+time)
					Blt3D(SubtitleRect[Subtitle[i].player].x, SubtitleRect[Subtitle[i].player].y + int(BG_HEIGHT*(float(Subtitle[i].subcount-SUBTITLE_TIME1-time)/SUBTITLE_TIME3*2/3+0.33333f)), 
										m_Texture_Subtitle, SubtitleTypeRect+Subtitle[i].subtitle);
				else
					Blt3D(SubtitleRect[Subtitle[i].player].x, SubtitleRect[Subtitle[i].player].y + BG_HEIGHT/3, 
										m_Texture_Subtitle, SubtitleTypeRect+Subtitle[i].subtitle);
				Subtitle[i].subcount++;
				if(Subtitle[i].subcount>SUBTITLE_TIME1+time+SUBTITLE_TIME3)
					Subtitle[i].subcount=0;
			}
	}
	/***********绘制当前的级别level**********/
	if(m_curLevel<10&&m_curLevel>0)
	{
		Blt3D(LevelRect.x + LEVEL_WIDTH/2, LevelRect.y, m_Texture_Level, LevelNumberRect+m_curLevel);
	}
	else if(m_curLevel==10)
	{
		Blt3D(LevelRect.x, LevelRect.y, m_Texture_Level, LevelNumberRect+1);
		Blt3D(LevelRect.x + LEVEL_WIDTH, LevelRect.y, m_Texture_Level, LevelNumberRect);
	}
/**************/

	return S_OK;
}

int CTetris_Game::PlayerInputNotify(int player, int nkeydef, int defaultrow)
{
	int row=defaultrow;
	BOOL res;
	if(TetrisEngine[player].IsGameOver()||m_Explode[player]!=EFFECT_NOT_START||m_AddFloor[player]!=EFFECT_NOT_START)
		return row;

	switch(nkeydef)
	{
	case KeyDef_Left://左
		if(TetrisEngine[player].OnLeft())
			PlayTetrisSound(player, SOUND_MOVE);
		else
			PlayTetrisSound(player, SOUND_INVALID);
		break;
	case KeyDef_Right://右
		if(TetrisEngine[player].OnRight())
			PlayTetrisSound(player, SOUND_MOVE);
		else
			PlayTetrisSound(player, SOUND_INVALID);
		break;
	case KeyDef_Rotate://旋转
		if(m_smoothrotate)
			res = TetrisEngine[player].OnStartSmoothRotate();
		else
			res = TetrisEngine[player].OnRotate();
		if(res)
			PlayTetrisSound(player, SOUND_ROTATE);
		else
			PlayTetrisSound(player, SOUND_INVALID);
		break;
	case KeyDef_Bottom://底
		row=TetrisEngine[player].OnDownToBottom();
		break;
	case KeyDef_Down://下一层
		if(m_smoothdown)
			row=TetrisEngine[player].OnSmoothDown((float)ANIME_TIME/ACCE_DOWNSPEED);
		else
			row=TetrisEngine[player].OnDown();
		break;
	case KeyDef_SmoothDown://平滑下一层
		row=TetrisEngine[player].OnSmoothDown((float)ANIME_TIME/TimerInterval[m_curLevel]);
		break;
	case KeyDef_SmoothRotate://平滑旋转
		TetrisEngine[player].OnSmoothRotate((float)ANIME_TIME/ROTATE_TIME);
		break;
	default:;
	}
	return row;
}

void CTetris_Game::NewGame()
{
	StopAllSubtitle();
	LastTime_Down[0]=LastTime_Down[1]=timeGetTime();
	m_curLevel=m_Level;
	m_Explode[0]=m_Explode[1]=EFFECT_NOT_START;
	m_AddFloor[0]=m_AddFloor[1]=EFFECT_NOT_START;
	m_DisplayScore[0]=m_DisplayScore[1]=0;
	m_nAddFloorBuffer[0]=m_nAddFloorBuffer[1]=0;
	m_nAddingFloor[0]=m_nAddingFloor[1]=0;
	int seed=rand(), i, p;
	for(i=0;i<MAX_PLAYER;i++)
		m_bWindowRendering[i] = TRUE;
	switch(m_Mode)
	{
	case 1:
		if(m_leftwindow)
			m_bWindowRendering[1] = FALSE;
		else
			m_bWindowRendering[0] = FALSE;
		break;
	case 2:
		TetrisEngine[0].SetComputerPlay(false);
		TetrisEngine[1].SetComputerPlay(false);
		break;
	case 3:
		if(m_leftwindow)
		{
			TetrisEngine[0].SetComputerPlay(false);
			TetrisEngine[1].SetComputerPlay(true, m_AILevel);
		}
		else
		{
			TetrisEngine[0].SetComputerPlay(true, m_AILevel);
			TetrisEngine[1].SetComputerPlay(false);
		}
		break;
	case 4:
		TetrisEngine[0].SetComputerPlay(true, m_AILevel);
		m_bWindowRendering[1] = FALSE;
		break;
	case 5:
		TetrisEngine[0].SetComputerPlay(true, m_AILevel);
		TetrisEngine[1].SetComputerPlay(true, m_AILevel);
		break;
	}

	PlayTetrisMusic(MUSIC_LEVEL00 + m_curLevel);

	for(p=0;p<MAX_PLAYER;p++)	if(m_bWindowRendering[p])
	{
		TetrisEngine[p].SetInitFloors(m_difficulty);
		TetrisEngine[p].Start(seed);
	}
	AnimeFrame=0;
	m_bIsPaused=FALSE;
	m_bIsPlaying=TRUE;
}

void CTetris_Game::StopGame(BOOL ChangeSound)
{
	StopAllSubtitle();
	if(ChangeSound)
		PlayTetrisMusic(MUSIC_LEVEL00);
	m_bWindowRendering[0]=m_bWindowRendering[1]=FALSE;
	m_bIsPaused = FALSE;
	m_bIsPlaying=FALSE;
	Render();
}

void CTetris_Game::PauseGame()
{
	if(m_bIsPlaying)
	{
		m_bIsPaused = TRUE;
		Render();
	}
}

void CTetris_Game::PlayTetrisSound(int player, int nsound)
{
	if(m_bPlaySound&&nsound<MAX_SOUND&&g_pSound[nsound])
		g_pSound[nsound]->Play( DMUS_SEGF_DEFAULT | DMUS_SEGF_SECONDARY, g_p3DAudiopath );
}

void CTetris_Game::PlayTetrisMusic(int nmusic)
{
	StopTetrisMusic();

	if(m_bPlayMusic&&nmusic<MAX_MUSIC&&g_pMusic[nmusic])
	{
		g_pMusic[nmusic]->Play( DMUS_SEGF_DEFAULT, g_p3DAudiopath );
	}
}

void CTetris_Game::StopTetrisMusic()
{
	for(int i=0;i<MAX_MUSIC;i++)
		if(g_pMusic[i]&&g_pMusic[i]->IsPlaying())
			g_pMusic[i]->Stop();

}

void CTetris_Game::UpdateRect()
{
	if(m_pd3dDevice)
		Render();
}

void CTetris_Game::Animate(KeyStatus keystatus[MAX_PLAYER][MAX_KEYDEF], DWORD curTime)
{if(m_bWindowRendering[0]||m_bWindowRendering[1]){//至少有一个窗口需要Render

	DWORD interval;
	int p;
	int row[MAX_PLAYER]={-1, -1};//该状态为平常状态
	if(m_bIsPlaying)
	{
		EACH_PLAYER(p)	if(m_Explode[p]==EFFECT_NOT_START&&m_AddFloor[p]==EFFECT_NOT_START)
		{
			switch(TetrisEngine[p].ComputerPlay())//AI control/action execute
			{
			case ComputerMove_None:
				break;
			case ComputerMove_Left:
				row[p] = PlayerInputNotify(p, KeyDef_Left, row[p]);
				break;
			case ComputerMove_Right:
				row[p] = PlayerInputNotify(p, KeyDef_Right, row[p]);
				break;
			case ComputerMove_Rotate:
				row[p] = PlayerInputNotify(p, KeyDef_Rotate, row[p]);
				break;
			case ComputerMove_Bottom:
				row[p] = PlayerInputNotify(p, KeyDef_Bottom, row[p]);
				break;
			case ComputerMove_Down:
				row[p] = PlayerInputNotify(p, KeyDef_Down, row[p]);
				break;
			default:;
			}
			if(row[p]==-1)
				for(DWORD j = 0; j < MAX_KEYDEF; j++ ) 
				{
					if(keystatus[p][j].bKeyPress)
					{
						row[p]=PlayerInputNotify(p, j, row[p]);
						if(j==KeyDef_Down)
							PlayTetrisSound(p, SOUND_SPEEDUP);
					}
					/*****KEYDOWN REPEAT*******/
					if(keystatus[p][j].bKeydown&&j<2)
					{
						interval=curTime-keystatus[p][j].DownTime;
						if(interval > KEY_REPEAT_INTERVAL)
						{
							keystatus[p][j].DownTime+=interval/KEY_REPEAT_INTERVAL*KEY_REPEAT_INTERVAL;
							row[p] = PlayerInputNotify(p, j, row[p]);
						}
					}
				}
			/*****ID_GAME_TIMER*******/
			if(row[p]==-1)
			{
				if(m_smoothrotate)
					PlayerInputNotify(p, KeyDef_SmoothRotate);//系统要求的旋转

				interval=curTime-LastTime_Down[p];
				if(m_smoothdown)
				{
					if(keystatus[p][KeyDef_Down].bKeydown)
					{
						row[p]=PlayerInputNotify(p, KeyDef_Down, row[p]);//系统要求的下降
					}
					else
						row[p]=PlayerInputNotify(p, KeyDef_SmoothDown, row[p]);//系统要求的下降
				}
				else
				{
					if(keystatus[p][KeyDef_Down].bKeydown)
					{
						if(interval>ACCE_DOWNSPEED)
						{
							LastTime_Down[p]+=interval/ACCE_DOWNSPEED*ACCE_DOWNSPEED;
							row[p]=PlayerInputNotify(p, KeyDef_Down, row[p]);
						}
					}
					else
					{
						if(interval>TimerInterval[m_curLevel])
						{
							LastTime_Down[p]+=interval/TimerInterval[m_curLevel]*TimerInterval[m_curLevel];
							row[p]=PlayerInputNotify(p, KeyDef_Down, row[p]);
						}
					}
				}
			}
			if(row[p]!=-1)//如果方块放下，键 repeat取消
			{
				keystatus[p][0].bKeydown = FALSE;
				keystatus[p][1].bKeydown = FALSE;
				keystatus[p][3].bKeydown = FALSE;
				keystatus[p][4].bKeydown = FALSE;
			}
		}

		/*****判断分数是否够升级*******/
		EACH_PLAYER(p) if((m_Mode==1|| m_Mode == 4) &&TetrisEngine[p].GetCurScore()/LEVELUP_SCORE+m_Level>m_curLevel)
		{
			if(m_curLevel<MAX_LEVEL)//升级
			{
				AddSubtitle(p, m_curLevel+Subtitle_Draw);
				m_curLevel++;
				PlayTetrisMusic(MUSIC_LEVEL00 + m_curLevel);
				PlayTetrisSound(p, SOUND_LEVELUP);
			}
			else//通关
			{
				TetrisEngine[p].CreateNewShape();
				AddSubtitle(p, Subtitle_Win, 3*SUBTITLE_TIME2);
				PlayTetrisSound(p, SOUND_LEVELCLEAR);
				PlayTetrisMusic(MUSIC_LEVEL00);
				m_GameOver_Counter[p] = 0;
				m_bIsPaused	= FALSE;
				m_bIsPlaying= FALSE;
			}
		}
		/*****判断是否需要开启爆炸或者增长等效果*******/

		EACH_PLAYER(p)	if(row[p]>=0)//如果接触地面
			PlayTetrisSound(p, SOUND_BOTTOM);

		EACH_PLAYER(p)	if(row[p]>0)//爆炸开始
		{
			if(row[p]>1)
				m_nAddFloorBuffer[1-p]+=row[p];
			if(m_othereffect)
				m_Explode[p]=EFFECT_START;
			else
			{
				m_Explode[p]=DELLINE_TIME;
				PlayTetrisSound(p, SOUND_DELLINE);
			}
		}

		EACH_PLAYER(p)
			if(m_Explode[p]>=DELLINE_TIME||row[p]==0)	//爆炸完毕或者落地
			{
				if(TetrisEngine[p].GetFloorsBuffer()>0)	//如果有需要加的行
				{
					if(m_othereffect)
					{
						m_nAddingFloor[p]=TetrisEngine[p].GetFloorsBuffer();
						if(m_nAddingFloor[p]>VERTICAL_BLOCKS_NUMBER)
							m_nAddingFloor[p]=VERTICAL_BLOCKS_NUMBER;

						m_AddFloor[p]=EFFECT_START;
						PlayTetrisSound(p, SOUND_ADDLINE);
					}
				}
				TetrisEngine[p].CreateNewShape();
			}

		EACH_PLAYER(p)
			if(m_Explode[p]>=DELLINE_TIME)//爆炸完毕给对方加行
				if(m_nAddFloorBuffer[1-p]>0)
				{
					TetrisEngine[1-p].AddFloorsBuffer(m_nAddFloorBuffer[1-p]);
					m_nAddFloorBuffer[1-p]=0;
				}

		EACH_PLAYER(p)	if(m_Explode[p]==CHANGEWHITE_FRAME+1)//爆炸音效
			PlayTetrisSound(p, SOUND_DELLINE);

		EACH_PLAYER(p)	if(m_Explode[p]==EFFECT_NOT_START&&m_AddFloor[p]==EFFECT_NOT_START)
			TestGameOver(p);

		EACH_PLAYER(p)
		{
			if(m_Explode[p]>=DELLINE_TIME)
				m_Explode[p]=EFFECT_NOT_START;
			if(m_AddFloor[p]>=ADDFLOOR_FRAME*m_nAddingFloor[p])//增加行完毕
			{
				m_AddFloor[p]=EFFECT_NOT_START;
				m_nAddingFloor[p]=0;
			}
		}
	}

	/*****ANIME TIMER*******/
	AnimeFrame=(AnimeFrame+1)%10000;
	Render();

	if(m_bIsPlaying)
		EACH_PLAYER(p)
		{
			if(m_Explode[p]!=EFFECT_NOT_START)//爆炸动画
				m_Explode[p]++;

			if(m_AddFloor[p]!=EFFECT_NOT_START)//增加行动画
				m_AddFloor[p]++;
		}

}}

void CTetris_Game::AddSubtitle(int player, int sub, int subtime)
{
	if(sub>=SUBTITLE_NUMBER)
		return;
	int i = 0;
	for(i=0;i<MAX_SUBTITLE;i++)
		if(Subtitle[i].subcount==0)
			break;
	if(i<MAX_SUBTITLE)//可以显示
	{
		Subtitle[i].player=player;
		Subtitle[i].subtitle=sub;
		Subtitle[i].subcount=1;
		Subtitle[i].subtime=subtime;
	}
}

void CTetris_Game::SetMusicOn(BOOL bOn)	
{
	m_bPlayMusic = bOn;

	if(g_pMusicManager == NULL)
		return;
	if(m_bPlayMusic)
	{
		if(m_bWindowRendering[0]||m_bWindowRendering[1])
			PlayTetrisMusic(MUSIC_LEVEL00 + m_curLevel);
		else
			PlayTetrisMusic(MUSIC_LEVEL00);
	}
	else
		StopTetrisMusic();
}

HRESULT CTetris_Game::ForceFullscreenMode()
{
	DXUTDeviceSettings deviceSettings = DXUTGetDeviceSettings();
	if(deviceSettings.d3d9.pp.Windowed)
		DXUTToggleFullScreen();
	return S_OK;
}

HRESULT CTetris_Game::ForceWindowMode()
{
	DXUTDeviceSettings deviceSettings = DXUTGetDeviceSettings();
	if (!deviceSettings.d3d9.pp.Windowed)
		DXUTToggleFullScreen();
	return S_OK;
}

BOOL CTetris_Game::TestGameOver(int player)
{
	if(TetrisEngine[player].IsGameOver())//game over
	{
		PlayTetrisSound(player, SOUND_GAMEOVER);
		PlayTetrisMusic(MUSIC_LEVEL00);
		m_GameOver_Counter[player] = 0;
		if(m_Mode>1 && m_Mode != 4)
		{
			if(TetrisEngine[1-player].IsGameOver()&&m_AddFloor[1-player]==EFFECT_NOT_START)
				AddSubtitle(player, Subtitle_Draw, 3*SUBTITLE_TIME2);
			else
			{
				AddSubtitle(1-player, Subtitle_Win, 3*SUBTITLE_TIME2);
				AddSubtitle(player, Subtitle_Lose, 3*SUBTITLE_TIME2);
			}
		}
		else
			AddSubtitle(player, Subtitle_Lose, 3*SUBTITLE_TIME2);
		m_bIsPaused	= FALSE;
		m_bIsPlaying= FALSE;
		return TRUE;
	}
	return FALSE;
}

void CTetris_Game::StopAllSubtitle()
{
	for(int i=0;i<MAX_SUBTITLE;i++)
		Subtitle[i].subcount=0;
}
