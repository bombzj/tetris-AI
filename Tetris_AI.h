// Tetris_AI.h: interface for the CTetris_AI class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TETRIS_AI_H__D9D7C37B_13F4_44F0_A6C7_4444AAAC6E46__INCLUDED_)
#define AFX_TETRIS_AI_H__D9D7C37B_13F4_44F0_A6C7_4444AAAC6E46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TetrisControl.h"

#define SEARCH_DEPTH 2	//������ȣ�һ����2����Ϊֻ֪��nextblock��
#define INFINIT_VALUE 100000.0f	//�����
#define MAX_ACTION 15	//���ж�ʱ��

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
											//����������Ϸ����Ŀ�����
	int nBlocksInFloor[VERTICAL_BLOCKS_NUMBER];	//ÿ�еĿ���
};

class CTetris_AI : public CTetrisControl  
{
public:
	CTetris_AI();
	virtual ~CTetris_AI();
	BOOL CreateNewShape();	//�ڴ���һ���µĿ�֮��ʼAI����
	ComputerMove ComputerPlay();	//�����ж������ص��ԵĶ���

public:
	void Start(int nSeed);	//��Ϸ��ʼ��ʼAI����
	void SetComputerPlay(bool computerplay, int level = 3, int alg = 0);	//�����Ƿ���AI�����Լ�AI����
	bool m_bIsComputerPlay;	//�Ƿ��ɵ���AI����

private:
	bool AddShape(CBlockData& blockdata, CShape* shape, int x, int r);	//��һ����ӵ���������ɹ��򷵻�true
										//xΪλ�ã�rΪת������������޷�����λ���򷵻�false
	float CalcValue(const CBlockData& blockdata);		//��ֵ����
	float SearchStep(CBlockData& CBlockData, int& nMoveX, int& nRotate, int level);	//����������ֵ
	void CalcRowHeight(const CBlockData& blockdata);	//����ÿ����ߵĿ�ĸ߶�
	int CalcHole(const CBlockData& blockdata);			//�����϶����������calcrowhight�����У�
	float CalcSqrAverage(const CBlockData& blockdata);	//������ƽ����ƽ����������calcrowhight�����У�
	bool CalcBestMove();	//������õ��ƶ���������������
	void GetCurrentBlocks(CBlockData& blockdata);	//����ǰ��Ϸ��Ϣ���浽���ݽṹ��
	float CalcDangerousLevel();	//Σ�ճ̶Ȳ�������
	int CalcMinRowHeight();
	int CalcMaxRowHeight();
	int CalcAllNewHole();	//�����²����Ŀ�
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
	int m_ComputerInterval[MAX_AILEVEL+1];//1/40��Ϊ��λ
	int m_nActionFailed;	//���Ϊ0��ʧ��
	int m_nWaitTodown;	//��ʱ����¼�
	int m_nBestMoveX, m_nBestRotate;	//��ѵ�����Ӧ���ƶ�����ת����
	CShape* m_Shapes[SEARCH_DEPTH];	//�������µĿ����״
	int m_nRowHeight[HORIZONTAL_BLOCKS_NUMBER];	//����ÿ����ߵĿ�ĸ߶�
	int m_nOriRowHeight[HORIZONTAL_BLOCKS_NUMBER];	//�����ʼÿ����ߵĿ�ĸ߶�
	int m_nNewHole[SEARCH_DEPTH];	//�²����Ŀ���
	int m_nDeleteFloor[SEARCH_DEPTH];	//����ȥ������

};


#endif // !defined(AFX_TETRIS_AI_H__D9D7C37B_13F4_44F0_A6C7_4444AAAC6E46__INCLUDED_)
