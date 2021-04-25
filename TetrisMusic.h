#pragma once

//#include "DMUtil.h"
#include "DXUtil.h"
#include <dxerr.h>

#define MAX_SOUND 10	//总音效数量
#define MAX_MUSIC 11	//总音乐数量

enum	//每个音效对应
{
	SOUND_BOTTOM=0,
	SOUND_MOVE,
	SOUND_ROTATE,
	SOUND_SPEEDUP,
	SOUND_INVALID,
	SOUND_GAMEOVER,
	SOUND_DELLINE,
	SOUND_ADDLINE,
	SOUND_LEVELUP,
	SOUND_LEVELCLEAR,
};

enum
{
	MUSIC_LEVEL00=0,
	MUSIC_LEVEL01,
	MUSIC_LEVEL02,
	MUSIC_LEVEL03,
	MUSIC_LEVEL04,
	MUSIC_LEVEL05,
	MUSIC_LEVEL06,
	MUSIC_LEVEL07,
	MUSIC_LEVEL08,
	MUSIC_LEVEL09,
	MUSIC_LEVEL10,
};

HRESULT InitDirectMusic( HWND hwnd );	//初始化direct music
VOID    FreeDirectMusic();				//释放  direct music
