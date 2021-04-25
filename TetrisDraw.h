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
#define MAX_SUBTITLE	10//最多同时出现的subtitle
#define SUBTITLE_TIME1	15//subtitle下落
#define SUBTITLE_TIME2	35//subtitle持续时间
#define SUBTITLE_TIME3	30//subtitle再次下落

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

#define ANIME_TIME 25	//动画的播放速度（每桢占的时间）
#define ROTATE_TIME 200	//旋转一个块的动画需要的时间

#define CHANGEWHITE_FRAME		8
#define	CRASH_FRAME				10
#define CRASH_WIDTH				BLOCK_WIDTH*10
#define CRASH_HEIGHT			BLOCK_WIDTH
#define	EXPLODE_TYPE			4//四种可能存在的爆炸
#define	EXPLODE_DIRECTION		8//爆炸的8个方向
#define	EXPLODE_FRAME			15
#define EXPLODE_WIDTH			50
#define EXPLODE_HEIGHT			50

#define DELLINE_TIME	CHANGEWHITE_FRAME+CRASH_FRAME+EXPLODE_FRAME		//消行的总动画桢数
#define DELLINE_DOWN_TIME		17		//其他行下降的开始时间
#define DELLINE_DOWN_FRAME		((DELLINE_TIME-DELLINE_DOWN_TIME)/4)		//其他行下降每行的时间（应该在消行完成前结束）

#define ADDFLOOR_FRAME		5		//每加一行的动画桢数
#define CHANGEGRAY_FRAME	1		//变灰一行需要的时间

#define SCORE_ADD_SPEED		2		//分数加的速度

