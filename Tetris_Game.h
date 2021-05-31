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
#include "TetrisRecord.h"

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
	void NewGame(BOOL replay = FALSE);	//new game
	void StopGame(BOOL ChangeSound = TRUE);	//stop game if playing
	void Destroy();	//game resource release
	HRESULT Create(CWnd *pwnd);
	void SetParam(BOOL smoothdown, BOOL smoothrotate, BOOL leftwindow, int ailevel,
		int level, int difficulty, BOOL shownext, BOOL othereffect, int volumn);
	void Animate(KeyStatus keystatus[MAX_PLAYER][MAX_KEYDEF], DWORD curTime);//游戏中的动画或者闪烁等（比如平滑下降以及块的闪烁）
	void UpdateRect();

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
	CTetrisRecord m_record;
	BOOL m_bReplay;

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

	BOOL m_bIsPlaying;	// keyboard not allowed if game is not playing
	BOOL m_bIsPaused;	// keyboard and animation not allowed if game paused
	BOOL m_bWindowRendering[MAX_PLAYER];	// don't render if status is nonplayer or ?
	int  m_Explode[MAX_PLAYER];		// >0 if animation started
	int  m_AddFloor[MAX_PLAYER];	// >0 if animation started
	int  m_nAddFloorBuffer[MAX_PLAYER];	// number of adding rows to the opponent
	int  m_nAddingFloor[MAX_PLAYER];	// number of adding rows
	int m_Mode;					// 1: 1player, 2: 2player, 3: vs AI, 4: AI only, 5: AI vs AI
	int m_curLevel;		// current level (falling speed)
	int m_Level;		// initial level
	int m_AILevel;		// AI level (speed)
	int m_difficulty;	// initial rows
	int m_DisplayScore[MAX_PLAYER];
	int m_volumn;
	BOOL m_othereffect;
	BOOL m_smoothdown;	
	BOOL m_smoothrotate;
	BOOL m_shownext;
	BOOL m_leftwindow;

	BOOL m_bPlaySound;
	BOOL m_bPlayMusic;

	struct
	{
		int subcount;	// 0 if not exist
		byte subtitle;	// type
		int player;	
		int subtime;	// time to elapse
	}	Subtitle[MAX_SUBTITLE];

	DWORD LastTime_Down[MAX_PLAYER];
	DWORD TimerInterval[MAX_LEVEL+1];	// ms
	
	int AnimeFrame;	// common animation frame control

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
