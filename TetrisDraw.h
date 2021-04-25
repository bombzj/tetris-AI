#pragma once

#define BLOCK_WIDTH	24
#define BLOCK_TYPE	8
#define BLOCK_FRAME	4
#define BLOCK_CPF	12//Change per frmae
#define BG_WIDTH	760
#define BG_HEIGHT	550

#define SCORE_WIDTH		21
#define SCORE_HEIGHT	39
#define SCORE_NUMBER	10

#define LEVEL_WIDTH		28
#define LEVEL_HEIGHT	47
#define LEVEL_NUMBER	10

#define SUBTITLE_WIDTH	220
#define SUBTITLE_HEIGHT	80
#define SUBTITLE_NUMBER	12
#define MAX_SUBTITLE	10//���ͬʱ���ֵ�subtitle
#define SUBTITLE_TIME1	15//subtitle����
#define SUBTITLE_TIME2	35//subtitle����ʱ��
#define SUBTITLE_TIME3	30//subtitle�ٴ�����

#define NFLOOR_WIDTH	24
#define NFLOOR_HEIGHT	24
#define NFLOOR_TYPE		3
#define NFLOOR_FRAME	6
#define NFLOOR_CPF	4//Change per frmae
#define NFLOOR_MAX_NUMBER		6

#define GAMEOVER_WIDTH	200
#define GAMEOVER_HEIGHT	100

#define GAMEPAUSED_WIDTH	600
#define GAMEPAUSED_HEIGHT	165

#define ANIME_TIME 25	//�����Ĳ����ٶȣ�ÿ��ռ��ʱ�䣩
#define ROTATE_TIME 200	//��תһ����Ķ�����Ҫ��ʱ��

#define CHANGEWHITE_FRAME		8
#define	CRASH_FRAME				10
#define CRASH_WIDTH				BLOCK_WIDTH*10
#define CRASH_HEIGHT			BLOCK_WIDTH
#define	EXPLODE_TYPE			4//���ֿ��ܴ��ڵı�ը
#define	EXPLODE_DIRECTION		8//��ը��8������
#define	EXPLODE_FRAME			15
#define EXPLODE_WIDTH			50
#define EXPLODE_HEIGHT			50

#define DELLINE_TIME	CHANGEWHITE_FRAME+CRASH_FRAME+EXPLODE_FRAME		//���е��ܶ�������
#define DELLINE_DOWN_TIME		17		//�������½��Ŀ�ʼʱ��
#define DELLINE_DOWN_FRAME		((DELLINE_TIME-DELLINE_DOWN_TIME)/4)		//�������½�ÿ�е�ʱ�䣨Ӧ�����������ǰ������

#define ADDFLOOR_FRAME		5		//ÿ��һ�еĶ�������
#define CHANGEGRAY_FRAME	1		//���һ����Ҫ��ʱ��

#define SCORE_ADD_SPEED		2		//�����ӵ��ٶ�

