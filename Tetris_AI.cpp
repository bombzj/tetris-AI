// Tetris_AI.cpp: implementation of the CTetris_AI class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Tetris.h"
#include "Tetris_AI.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define SHAPE_ORIGIN_Y 0
#define SHAPE_ORIGIN_X 4
#define INVALID_MOVE -100

CTetris_AI::CTetris_AI()
{
	m_AILevel = 3;
	m_ComputerInterval[10]=0;
	float tmp = 30.0f;
	for(int i=MAX_AILEVEL-1;i>0;i--)
	{
		m_ComputerInterval[i]=int(tmp);
		tmp*=1.3f;
	}
	m_bIsComputerPlay = false;
}

CTetris_AI::~CTetris_AI()
{

}

void CTetris_AI::CalcRowHeight(const CBlockData& blockdata)
{
	int x;
	EACHCOLUMN(x)
	{
		m_nRowHeight[x] = 0;
		for(int y=0;y<VERTICAL_BLOCKS_NUMBER;y++)
			if(blockdata.bBlock[x][y])
			{
				m_nRowHeight[x] = VERTICAL_BLOCKS_NUMBER - y;
				break;
			}
	}
}

int CTetris_AI::DeleteFullFloor(CBlockData& blockdata)
{
	int x, y, y2, nfloor=0;
	EACHROW(y)
		if(blockdata.nBlocksInFloor[y]>=HORIZONTAL_BLOCKS_NUMBER)
		{
			nfloor++;
			for(y2=y; y2>0; y2--)	
			{
				EACHCOLUMN(x)
				{
					blockdata.bBlock[x][y2]=blockdata.bBlock[x][y2-1];
				}
				blockdata.nBlocksInFloor[y2]=blockdata.nBlocksInFloor[y2-1];
			}
			EACHCOLUMN(x)
			{
				blockdata.bBlock[x][0]=false;
			}
			blockdata.nBlocksInFloor[0]=0;
		}
	return nfloor;
}

void CTetris_AI::CalcOriRowHeight(CBlockData &blockdata)
{
	int x;
	EACHCOLUMN(x)
	{
		m_nOriRowHeight[x] = 0;
		for(int y=0;y<VERTICAL_BLOCKS_NUMBER;y++)
			if(blockdata.bBlock[x][y])
			{
				m_nOriRowHeight[x] = VERTICAL_BLOCKS_NUMBER - y;
				break;
			}
	}
}

int CTetris_AI::CalcMaxRowHeight()
{
	int x, maxrowheight=0;
	EACHCOLUMN(x)
		if(m_nRowHeight[x] > maxrowheight)
			maxrowheight=m_nRowHeight[x];
	return maxrowheight;
}

int CTetris_AI::CalcMinRowHeight()
{
	int x, minrowheight=VERTICAL_BLOCKS_NUMBER;
	EACHCOLUMN(x)
		if(m_nRowHeight[x] < minrowheight)
			minrowheight=m_nRowHeight[x];
	return minrowheight;
}

int CTetris_AI::CalcHole(const CBlockData& blockdata)
{
	int x, nHole=0;
	EACHCOLUMN(x)
		for(int y=0;y<m_nRowHeight[x];y++)
			if(!blockdata.bBlock[x][VERTICAL_BLOCKS_NUMBER-y-1])	//凡是上方存在方块的空位置都是空隙
				nHole++;
	return nHole;
}

float CTetris_AI::CalcHoleLevel(const CBlockData& blockdata)
{
	int x;
	float nHole=0;
	EACHCOLUMN(x)
		for(int y=VERTICAL_BLOCKS_NUMBER-m_nRowHeight[x];y<VERTICAL_BLOCKS_NUMBER;y++)
//			if(!blockdata.bBlock[x][y]&&VERTICAL_BLOCKS_NUMBER-y>m_nOriRowHeight[x]-3)	//凡是上方存在方块的空位置都是空隙
			if(!blockdata.bBlock[x][y])	//凡是上方存在方块的空位置都是空隙
				nHole+=m_nRowHeight[x];
	return nHole / VERTICAL_BLOCKS_NUMBER;
}

float CTetris_AI::CalcSqrAverage(const CBlockData& blockdata)
{
	float sum=0;
	int x;
	EACHCOLUMN(x)
		sum+=powf(float(m_nRowHeight[x]), 2)*(1-(float)abs(x-5)/200);
	sum=sqrtf(sum);
	return sum;
}

void CTetris_AI::GetCurrentBlocks(CBlockData& blockdata)
{
	int x, y;
	EACHROW(y)
	{
		EACHCOLUMN(x)
			blockdata.bBlock[x][y]=(m_Blocks[x+WALL_THICKNESS][y+WALL_THICKNESS].m_nStatus==HAVE_BLOCK);
		blockdata.nBlocksInFloor[y]=m_nCurBlocksInFloor[VERTICAL_BLOCKS_NUMBER-y-1];
	}
}

bool CTetris_AI::CalcBestMove()
{
	m_Shapes[0]=&m_CurShape;
	m_Shapes[1]=&m_NextShape;

	CBlockData blockdata;
	GetCurrentBlocks(blockdata);//get current information

	CalcOriRowHeight(blockdata);

	m_nBestMoveX=INVALID_MOVE;
	m_nBestRotate=0;
	SearchStep(blockdata, m_nBestMoveX, m_nBestRotate, 0);
	if(m_nBestMoveX==INVALID_MOVE)	//no avalible move, just stay there
	{
		m_nBestMoveX=SHAPE_ORIGIN_X;
		return false;
	}
	return true;
}

float CTetris_AI::SearchStep(CBlockData& source, int& nMoveX, int& nRotate, int level)
{
	if(level>=SEARCH_DEPTH)
		return CalcValue(source);

	CBlockData blockdata;
	float minValue=INFINIT_VALUE, tmpvalue;
	int x, r;
	int retX, retR;	// x->movex, r->rotate

	for(r=0; r<4; r++)	//列举所有可能的位置和旋转
		for(x=-1;x<9;x++)
		{
			memcpy(&blockdata, &source, sizeof(CBlockData));
			CalcRowHeight(blockdata);
			if(AddShape(blockdata, m_Shapes[level], x, r))
			{
				m_nNewHole[level]=CalcNewHole(blockdata);
				m_nDeleteFloor[level]=DeleteFullFloor(blockdata);
				tmpvalue = SearchStep(blockdata, retX, retR, level+1);

				if(tmpvalue<minValue)
				{
					minValue=tmpvalue;
					nMoveX=x, nRotate=r;
				}
			}
		}

	return minValue;
}

float CTetris_AI::CalcValue(const CBlockData& blockdata)
{
	float para0 = 0;
	for(int i=0;i<SEARCH_DEPTH;i++)
	{
		if(m_nDeleteFloor[i]>1)
			para0-=m_nDeleteFloor[i]/2;
		else
			para0+=m_nDeleteFloor[i]*1;
	}	
	
	CalcRowHeight(blockdata);
	int para1 = CalcMaxRowHeight();
	if(para1>15)
		para1=(para1-15);
	else
		para1=0;
	int para2=CalcHole(blockdata);
	float para3=CalcSqrAverage2(blockdata);
	float para4=CalcDangerousLevel();
	float para5=0;//CalcBlockLevel();
	float para6=CalcHoleLevel(blockdata);
	int para7=CalcSurfaceLevel();
	int para8=CalcNewHole(blockdata);
	if(m_Alg == 1)
		return para0 * 1 + 5 * para1 + 5 * para2 + 3.6f * para3 + 3 * para4/* + para5*/ + para6 / 10 + (float)para7 / 50 + para8;
	return para0 * 10 + 5 * para1 + 5 * para2 + 3.6f * para3 + 3 * para4/* + para5*/ + para6 / 10 + (float)para7 / 50 + para8;
}

bool CTetris_AI::AddShape(CBlockData &blockdata, CShape *shape, int MoveX, int Rotate)
{
	
	int i;
	int curX, curY;

	for(i=0;i<shape->m_bBlocks;i++)	//不能出边框
	{
		curX=m_ShapeList[shape->m_nColor][Rotate].m_ptBlocks[i].x+MoveX;
		if(curX<0||curX>=HORIZONTAL_BLOCKS_NUMBER)
			return false;
	}
	CBasicShape* rshape;
	for(int PassByRotate=0; PassByRotate<Rotate; PassByRotate++)//旋转过程中如果碰到块则失败
	{
		rshape=&m_ShapeList[shape->m_nColor][PassByRotate];
		for(i=0;i<rshape->m_bBlocks;i++)
			if(SHAPE_ORIGIN_Y+rshape->m_ptBlocks[i].y>=0&&blockdata.bBlock[rshape->m_ptBlocks[i].x+SHAPE_ORIGIN_X][SHAPE_ORIGIN_Y+rshape->m_ptBlocks[i].y])
				return false;
	}
	rshape=&m_ShapeList[shape->m_nColor][Rotate];	//旋转后的shape
	int lowest=100;	//掉到最低

	for(i=0;i<shape->m_bBlocks;i++)
	{
		curX=rshape->m_ptBlocks[i].x+MoveX;
		curY=VERTICAL_BLOCKS_NUMBER-m_nRowHeight[curX]-rshape->m_ptBlocks[i].y-1;
		if(curY<lowest)
			lowest=curY;
	}
	if(lowest<0||lowest==100)
		return false;

	for(i=0;i<rshape->m_bBlocks;i++)
	{
		int fixX=rshape->m_ptBlocks[i].x+MoveX;
		int fixY=rshape->m_ptBlocks[i].y+lowest;
		if(MoveX>SHAPE_ORIGIN_X)	//经过过程如果碰到块则不能过去
		{
			for(int PassbyX=SHAPE_ORIGIN_X; PassbyX<MoveX; PassbyX++)
				if(SHAPE_ORIGIN_Y+rshape->m_ptBlocks[i].y>=0&&blockdata.bBlock[rshape->m_ptBlocks[i].x+PassbyX][SHAPE_ORIGIN_Y+rshape->m_ptBlocks[i].y])
					return false;
		}
		else if(MoveX<SHAPE_ORIGIN_X)
		{
			for(int PassbyX=SHAPE_ORIGIN_X; PassbyX>MoveX; PassbyX--)
				if(SHAPE_ORIGIN_Y+rshape->m_ptBlocks[i].y>=0&&blockdata.bBlock[rshape->m_ptBlocks[i].x+PassbyX][SHAPE_ORIGIN_Y+rshape->m_ptBlocks[i].y])
					return false;
		}
		if(fixY<0)
			return false;	//无法移动到那里
		blockdata.bBlock[fixX][fixY]=true;
		blockdata.nBlocksInFloor[rshape->m_ptBlocks[i].y+lowest]++;
	}

	return true;
}

BOOL CTetris_AI::CreateNewShape()
{
	BOOL res=CTetrisControl::CreateNewShape();
	if(m_bIsComputerPlay)
	{
		CalcBestMove();
		m_nActionFailed = MAX_ACTION;
		m_nWaitTodown = m_ComputerInterval[m_AILevel];
	}
	return res;
}

void CTetris_AI::Start(int nSeed)
{
	CTetrisControl::Start(nSeed);
	if(m_bIsComputerPlay)
	{
		CalcBestMove();
		m_nActionFailed = MAX_ACTION;
		m_nWaitTodown = m_ComputerInterval[m_AILevel];
	}
}

ComputerMove CTetris_AI::ComputerPlay()
{
	if(!m_bIsComputerPlay||m_nActionFailed==-1)
		return ComputerMove_None;

	m_nActionFailed--;

	// rotate first, after that, move, then press downtobottom
	if(m_nActionFailed>0)
	{
		if(m_nBestRotate>0)
		{
			m_nBestRotate--;
			return	ComputerMove_Rotate;
		}
		if(m_nBestMoveX>m_CurShape.m_ptPos.x)
			return	ComputerMove_Right;
		if(m_nBestMoveX<m_CurShape.m_ptPos.x)
			return	ComputerMove_Left;
	}
	if(m_nWaitTodown>0)
	{
		m_nWaitTodown--;
		m_nActionFailed++;
		return ComputerMove_None;
	}
	else
	{
		m_nActionFailed=-1; //action complete or failed
		return ComputerMove_Bottom;
	}

}

void CTetris_AI::SetComputerPlay(bool computerplay, int level, int alg)
{
	m_AILevel = level;
	m_bIsComputerPlay=computerplay;
	m_Alg = alg;
}

int CTetris_AI::CalcDeletedFloor()
{
	int ndel=0;
	for(int i=0;i<SEARCH_DEPTH;i++)
		ndel+=m_nDeleteFloor[i];
	return ndel;
}

float CTetris_AI::CalcSqrAverage2(const CBlockData& blockdata)
{
	float sum=0;
	int ndel=CalcDeletedFloor();
	int x;
	EACHCOLUMN(x)
		sum+=powf(float(m_nRowHeight[x]+ndel), 2)*(1-(float)abs(x-5)/200);
	sum=sqrtf(sum);
	return sum;
}

int CTetris_AI::CalcSurfaceLevel()
{
	int left1=0, right1=0, flat=0, flatleft1=0, flatright1=0;
	int left2=0, right2=0, flat3=0, flatleft_1=0, flatright_1=0;
	int surface=0;


	for(int i=0;i<9;i++)
	{
		if(m_nRowHeight[i]-m_nRowHeight[i+1]==1)
			left1++;
		else if(m_nRowHeight[i]-m_nRowHeight[i+1]==-1)
			right1++;
		else if(m_nRowHeight[i]-m_nRowHeight[i+1]==2)
			left2++;
		else if(m_nRowHeight[i]-m_nRowHeight[i+1]==-2)
			right2++;
		else if(m_nRowHeight[i]==m_nRowHeight[i+1])
		{
			flat++;
			if(i>0&&m_nRowHeight[i-1]-m_nRowHeight[i]==1)
				flatleft1++;
			else if(i>0&&m_nRowHeight[i-1]-m_nRowHeight[i]==-1)
				flatleft_1++;
			if(i<8&&m_nRowHeight[i+2]-m_nRowHeight[i+1]==1)
				flatright1++;
			else if(i<8&&m_nRowHeight[i+2]-m_nRowHeight[i+1]==-1)
				flatright_1++;
			if(i>0&&m_nRowHeight[i-1]==m_nRowHeight[i])
				flat3++;
		}
	}

	if(left1+flatright1==0)
		surface++;
	if(right1+flatleft1==0)
		surface++;
	if(flat+flatright_1+left2==0)
		surface++;
	if(flat+flatleft_1+right2==0)
		surface++;
	if(flat==0)
		surface++;

	return surface;
}

float CTetris_AI::CalcDangerousLevel()
{
	int dangerrow = 0, dangerrow2 = 0;
	float danger=0;
	int dheight, x;
	/*****三格深度的缝****/
	dheight=m_nRowHeight[1]-m_nRowHeight[0];
	if(dheight>2){		danger+=dheight;	dangerrow++;}
	else if(dheight==2)	dangerrow2++;
	dheight=m_nRowHeight[8]-m_nRowHeight[9];
	if(dheight>2){		danger+=dheight;	dangerrow++;}
	else if(dheight==2)	dangerrow2++;
	for(x=1;x<9;x++)
	{
		int dheight1=m_nRowHeight[x+1]-m_nRowHeight[x];
		int dheight2=m_nRowHeight[x-1]-m_nRowHeight[x];
		dheight=dheight1<dheight2?dheight1:dheight2;
		if(dheight>2){		danger+=dheight;	dangerrow++;}
		else if(dheight==2)	dangerrow2++;
	}
//	if(dangerrow==1)
//		danger=1;
	/*****两格深度的缝****/
//	if(dangerrow+dangerrow2>2)
//		danger+=(dangerrow+dangerrow2-2);
//	else
	danger+=(float)dangerrow2/5;

	/***************/
	return danger;
}

int CTetris_AI::CalcNewHole(const CBlockData &blockdata)
{
	int x, newhole=0;
	EACHCOLUMN(x)
		for(int y=m_nOriRowHeight[x];y<m_nRowHeight[x];y++)
			if(!blockdata.bBlock[x][VERTICAL_BLOCKS_NUMBER-y-1]&&m_nRowHeight[x]-y<4)	//凡是上方存在方块的空位置都是空隙
				newhole++;
	return newhole;
}

int CTetris_AI::CalcAllNewHole()
{
	int nhole=0;
	for(int i=0;i<SEARCH_DEPTH;i++)
		nhole+=m_nNewHole[i];
	return nhole;
}

