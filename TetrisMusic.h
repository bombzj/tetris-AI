#pragma once

//#include "DMUtil.h"
#include "DXUtil.h"
#include <dxerr.h>

#define MAX_SOUND 10	//����Ч����
#define MAX_MUSIC 11	//����������

enum	//ÿ����Ч��Ӧ
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

HRESULT InitDirectMusic( HWND hwnd );	//��ʼ��direct music
VOID    FreeDirectMusic();				//�ͷ�  direct music
