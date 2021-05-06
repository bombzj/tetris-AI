// CTetris_Game.h: interface for the CTetris_Game class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CTETRIS_GAME_H__6C3F65AD_C149_4A3B_B735_18DC02853748__INCLUDED_)
#define AFX_CTETRIS_GAME_H__6C3F65AD_C149_4A3B_B735_18DC02853748__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <mmsystem.h>
#include "Tetris_AI.h"
#include "Tetrisdraw.h"
#include "Tetrismusic.h"
#include "TetrisInput.h"

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_TEX1)
struct CUSTOMVERTEX
{
    D3DXVECTOR3 position; // The position
    FLOAT       tu, tv;   // The texture coordinates
};
struct RECT3D
{
	CUSTOMVERTEX point[4];
	int width, height;
};

#define LEVELUP_SCORE 2000
#define BASELEVEL_INTERVAL 500
#define LEVEL_DIFFERENCE	1.25

struct KeyStatus
{
	DWORD Keydef;
	BOOL bKeydown;
	DWORD DownTime;
	BOOL bKeyPress;
};

enum	//SubTitle
{
	Subtitle_Win = 0,
	Subtitle_Lose,
	Subtitle_Draw,
	Subtitle_Level2,
	Subtitle_Level3,
	Subtitle_Level4,
	Subtitle_Level5,
	Subtitle_Level6,
	Subtitle_Level7,
	Subtitle_Level8,
	Subtitle_Level9,
	Subtitle_Level10,
};

class CTetris_Game	//tetris full engine with image/sound/control...
{
public:
	void PauseGame();
	CTetris_Game();
	~CTetris_Game();
	int GetMode()		{	return m_Mode;}
	int SetMode(int n)	{	return m_Mode=n;}
	BOOL IsPaused()				{	return m_bIsPaused;}
	void TogglePause()			{	m_bIsPaused=!m_bIsPaused;	if(m_bIsPaused)	PauseGame();}
	BOOL IsPlaying()			{	return m_bIsPlaying;}
	void NewGame();	//new game
	void StopGame(BOOL ChangeSound = TRUE);	//stop game if playing
	void Destroy();	//game resource release
	HRESULT Create(CWnd *pwnd);	//引擎启动
	void SetParam(BOOL smoothdown, BOOL smoothrotate, BOOL leftwindow, int ailevel,
		int level, int difficulty, BOOL shownext, BOOL othereffect, int volumn);
	void Animate(KeyStatus keystatus[MAX_PLAYER][MAX_KEYDEF], DWORD curTime);//游戏中的动画或者闪烁等（比如平滑下降以及块的闪烁）
	void UpdateRect();//让directdraw重新绑定到指定的窗口位置

	BOOL IsMusicOn()			{	return m_bPlayMusic;}
	void SetMusicOn(BOOL bOn);
	BOOL IsSoundOn()			{	return m_bPlaySound;}
	void SetSoundOn(BOOL bOn)	{	m_bPlaySound = bOn;	}
	HRESULT ForceFullscreenMode();
	HRESULT ForceWindowMode();
	IDirect3DDevice9* m_pd3dDevice = NULL;
	HRESULT DeleteDeviceObjects();	//release directx resource
	HRESULT InitDeviceObjects();	//load directx resource
	HRESULT RestoreDeviceObjects();

private:
	void ChangeDevice();
	HRESULT Render();	//render
	BOOL TestGameOver(int player);	//检测引擎，游戏是否结束
	void StopTetrisMusic();	//stop all music if playing
	void StopAllSubtitle();	//close all subtitle if visible
	void SetallOffset(SIZE* size, int cx, int cy);	//set texture information
	void Blt3D( DWORD x, DWORD y, LPDIRECT3DTEXTURE9 pTexture, int width, int height );
	void Blt3D( DWORD x, DWORD y, LPDIRECT3DTEXTURE9 pTexture, RECT3D* prc );
	void SetTextureRect(RECT3D& rect3d, float left, float top, float right, float bottom, int cx, int cy, BOOL CCW = TRUE);
	HRESULT Display();	//blt all image on backbuffer
	void AddSubtitle(int player, int sub, int subtime = SUBTITLE_TIME2);//add a new subtitle
	void PlayTetrisSound(int player, int nsound);//播放一个音效
	void PlayTetrisMusic(int nmusic);	//播放音乐
	int PlayerInputNotify(int player, int nkeydef, int defaultrow = -1);//游戏操作
	inline void SetColor(int color);	//设置directx颜色和material
	inline void UnSetColor();	//取消设置directx颜色


private:
	CTetris_AI TetrisEngine[MAX_PLAYER];

	int m_GameOver_Counter[MAX_PLAYER];

	BOOL m_bIsPlaying;	//若为假表示游戏不在进行中，不响应键盘，但可能显示动画等
	BOOL m_bIsPaused;	//若为真表示程序处于暂停状态，游戏暂停并且不响应键盘
	BOOL m_bWindowRendering[MAX_PLAYER];	//左、右两个窗口是否需要绘制（游戏可能正在进行，也可能在其他状态）
	int  m_Explode[MAX_PLAYER];//>0表示正进行消行动画
	int  m_AddFloor[MAX_PLAYER];//>0表示正进行加行动画
	int  m_nAddFloorBuffer[MAX_PLAYER];	//给对方增加的行数量
	int  m_nAddingFloor[MAX_PLAYER];	//正在增加的行的数量
	int m_Mode;					// 1: 1player, 2: 2player, 3: vs AI, 4: AI only, 5: AI vs AI
	int m_curLevel;		//当前级别（下落速度）
	int m_Level;		//处世级别
	int m_AILevel;		//AI级别（速度）
	int m_difficulty;	//行数难度级别
	int m_DisplayScore[MAX_PLAYER];	//当前显示的分数
	int m_volumn;		//音量
	BOOL m_othereffect;
	BOOL m_smoothdown;	
	BOOL m_smoothrotate;
	BOOL m_shownext;
	BOOL m_leftwindow;

	BOOL m_bPlaySound;	//是否播放音效
	BOOL m_bPlayMusic;	//是否播放音乐

	struct
	{
		int subcount;	//0则该sub不存在
		byte subtitle;	//出现的subtitle类型
		int player;		//对应那个player（窗口）
		int subtime;	//停留时间
	}	Subtitle[MAX_SUBTITLE];

	DWORD LastTime_Down[MAX_PLAYER];
	DWORD TimerInterval[MAX_LEVEL+1];//ms为单位
	
	int AnimeFrame;//普通闪烁动画桢的控制

	//directx resource
	LPDIRECT3DTEXTURE9 m_Texture_Block;
	LPDIRECT3DTEXTURE9 m_Texture_Background;
	LPDIRECT3DTEXTURE9 m_Texture_Score;
	LPDIRECT3DTEXTURE9 m_Texture_Level;
	LPDIRECT3DTEXTURE9 m_Texture_NFloor;
	LPDIRECT3DTEXTURE9 m_Texture_GrayBlock;
	LPDIRECT3DTEXTURE9 m_Texture_GamePaused;
	LPDIRECT3DTEXTURE9 m_Texture_Subtitle;
	LPDIRECT3DTEXTURE9 m_Texture_Changewhite;
	LPDIRECT3DTEXTURE9 m_Texture_Explode;
	LPDIRECT3DTEXTURE9 m_Texture_Crash;

	D3DMATERIAL9 mtrl;
	//texture tile position
	RECT3D ChangewhiteRect[BLOCK_TYPE][CHANGEWHITE_FRAME];
	RECT3D CrashRect[CRASH_FRAME];
	RECT3D ExplodeRect[EXPLODE_DIRECTION*EXPLODE_TYPE][EXPLODE_FRAME];
	RECT3D BlockRect[BLOCK_TYPE][BLOCK_FRAME];
	RECT3D ScoreNumberRect[SCORE_NUMBER];
	RECT3D LevelNumberRect[LEVEL_NUMBER];
	RECT3D NFloorTypeRect[NFLOOR_TYPE][NFLOOR_FRAME];
	RECT3D SubtitleTypeRect[SUBTITLE_NUMBER];

	D3DCOLORVALUE BlockColor[BLOCK_TYPE];

	SIZE ExplodeCenterOffset[EXPLODE_DIRECTION*BLOCK_TYPE];	//explode center position
};

inline void CTetris_Game::SetColor(int color)
{
	m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
	mtrl.Emissive.r = BlockColor[color].r / 255;
	mtrl.Emissive.g = BlockColor[color].g / 255;
	mtrl.Emissive.b = BlockColor[color].b / 255;
	mtrl.Emissive.a = 1.0f;
	m_pd3dDevice->SetMaterial( &mtrl );	
}

inline void CTetris_Game::UnSetColor()
{
	m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1 );
}

#endif // !defined(AFX_CTETRIS_GAME_H__6C3F65AD_C149_4A3B_B735_18DC02853748__INCLUDED_)
