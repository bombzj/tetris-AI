#pragma once

#define DIRECTINPUT_VERSION  0x0800
#include <dinput.h>

#define DINPUT_BUFFER_SIZE 8	//����sample�����С
#define KEY_REPEAT_INTERVAL 100		//�����ظ����ٶ�
#define MAX_KEYDEF 5		//Key Define for Each Player
#define ACCE_DOWNSPEED 50	//���ٺ���½��ٶ�

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

HRESULT InitDirectInput( HWND hwnd );	//��ʼ�� direct input
HRESULT ReadBufferedData(DIDEVICEOBJECTDATA *didod, DWORD& dwElements);	//read direct input buffer data
VOID    FreeDirectInput();	//�ͷ� direct input
VOID UnaccquireInput();
VOID AccquireInput();