#pragma once

#define DIRECTINPUT_VERSION  0x0800
#include <dinput.h>

#define DINPUT_BUFFER_SIZE 8	//键盘sample缓冲大小
#define KEY_REPEAT_INTERVAL 100		//键盘重复的速度
#define MAX_KEYDEF 5		//Key Define for Each Player
#define ACCE_DOWNSPEED 50	//加速后的下降速度

enum _KeyDef
{
	KeyDef_Left=0,
	KeyDef_Right,
	KeyDef_Rotate,
	KeyDef_Bottom,
	KeyDef_Down,
	KeyDef_SmoothDown,
	KeyDef_SmoothRotate,
};

HRESULT InitDirectInput( HWND hwnd );	//初始化 direct input
HRESULT ReadBufferedData(DIDEVICEOBJECTDATA *didod, DWORD& dwElements);	//read direct input buffer data
VOID    FreeDirectInput();	//释放 direct input
VOID UnaccquireInput();
VOID AccquireInput();