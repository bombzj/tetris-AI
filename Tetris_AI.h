// Tetris_AI.h: interface for the CTetris_AI class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TETRIS_AI_H__D9D7C37B_13F4_44F0_A6C7_4444AAAC6E46__INCLUDED_)
#define AFX_TETRIS_AI_H__D9D7C37B_13F4_44F0_A6C7_4444AAAC6E46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TetrisControl.h"

#define SEARCH_DEPTH 2	//搜索深度（一般是2，因为只知道nextblock）
#define INFINIT_VALUE 100000.0f	//无穷大
#define MAX_ACTION 15	//总行动时间

#define EACHCOLUMN(x) for(x=0;x<HORIZONTAL_BLOCKS_NUMBER;x++)
#define EACHROW(y) for(y=0;y<VERTICAL_BLOCKS_NUMBER;y++)

enum ComputerMove
{
	ComputerMove_Left=0,
	ComputerMove_Right,
	ComputerMove_Rotate,
	ComputerMove_Bottom,
	ComputerMove_Down,
	ComputerMove_None=100,
};

class CBlockData
{
public:
	bool bBlock[HORIZONTAL_BLOCKS_NUMBER][VERTICAL_BLOCKS_NUMBER];
											//保存整个游戏区域的块数据
	int nBlocksInFloor[VERTICAL_BLOCKS_NUMBER];	//每行的块数
};

class CTetris_AI : public CTetrisControl  
{
public:
	CTetris_AI();
	virtual ~CTetris_AI();
	BOOL CreateNewShape();	//在创建一个新的块之后开始AI计算
	ComputerMove ComputerPlay();	//电脑行动，返回电脑的动作

public:
	void Start(int nSeed);	//游戏开始后开始AI计算
	void SetComputerPlay(bool computerplay, int level = 3, int alg = 0);	//设置是否由AI控制以及AI级别
	bool m_bIsComputerPlay;	//是否由电脑AI控制

private:
	bool AddShape(CBlockData& blockdata, CShape* shape, int x, int r);	//把一个块加到区域，如果成功则返回true
										//x为位置，r为转动次数，如果无法到达位置则返回false
	float CalcValue(const CBlockData& blockdata);		//估值函数
	float SearchStep(CBlockData& CBlockData, int& nMoveX, int& nRotate, int level);	//搜索并给出值
	void CalcRowHeight(const CBlockData& blockdata);	//计算每行最高的块的高度
	int CalcHole(const CBlockData& blockdata);			//计算空隙数（必须在calcrowhight后运行）
	float CalcSqrAverage(const CBlockData& blockdata);	//计算行平方和平均（必须在calcrowhight后运行）
	bool CalcBestMove();	//计算最好的移动方法（主函数）
	void GetCurrentBlocks(CBlockData& blockdata);	//将当前游戏信息保存到数据结构中
	float CalcDangerousLevel();	//危险程度参数计算
	int CalcMinRowHeight();
	int CalcMaxRowHeight();
	int CalcAllNewHole();	//计算新产生的孔
	void CalcOriRowHeight(CBlockData& blockdata);
	float CalcHoleLevel(const CBlockData& blockdata);
	int CalcNewHole(const CBlockData& blockdata);
	float CalcSqrAverage2(const CBlockData& blockdata);	
	int CalcSurfaceLevel();
	int CalcDeletedFloor();

private:
	int DeleteFullFloor(CBlockData& blockdata);
	int m_AILevel;
	int m_Alg;		// different AI algorithms
	int m_ComputerInterval[MAX_AILEVEL+1];//1/40秒为单位
	int m_nActionFailed;	//如果为0则失败
	int m_nWaitTodown;	//到时间后按下键
	int m_nBestMoveX, m_nBestRotate;	//最佳的落点对应的移动和旋转方向
	CShape* m_Shapes[SEARCH_DEPTH];	//次序落下的块的形状
	int m_nRowHeight[HORIZONTAL_BLOCKS_NUMBER];	//保存每行最高的块的高度
	int m_nOriRowHeight[HORIZONTAL_BLOCKS_NUMBER];	//保存初始每行最高的块的高度
	int m_nNewHole[SEARCH_DEPTH];	//新产生的空数
	int m_nDeleteFloor[SEARCH_DEPTH];	//被消去的行数

};


#endif // !defined(AFX_TETRIS_AI_H__D9D7C37B_13F4_44F0_A6C7_4444AAAC6E46__INCLUDED_)
