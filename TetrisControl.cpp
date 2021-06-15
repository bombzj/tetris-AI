//
//TetrisControl.cpp
//
//		--	The implementation file of CTetrisControl class
//
///////////////////////////////////////////////////////

#include "stdafx.h"
#include "TetrisControl.h"
#include "ShapeFile.h"

CBasicShape	CTetrisControl::m_ShapeList[SHAPES_NUMBER][4];
int	CTetrisControl::m_nScoreLevel[BLOCKS_IN_SHAPE];
int	CTetrisControl::m_nShapeRotateState[SHAPES_NUMBER];

CTetrisControl::CTetrisControl(int nBlockColorsNum)
{
	m_nBlockColorsNum = nBlockColorsNum;
	m_nCurShapeType = -1;
	m_nCurShapeDir = -1;
	m_nHighestBlock = 0;
	m_nInitFloors = 0;
	for(int i = 0; i < BLOCKS_IN_SHAPE; i++)
		m_nScoreLevel[i] = 0;
	InitWalls();
}

CTetrisControl::~CTetrisControl()
{
}

void CTetrisControl::InitWalls()
{
	for(int j = 0; j < VERTICAL_BLOCKS_NUMBER + WALL_THICKNESS * 2; j++)
		for(int i = 0; i < WALL_THICKNESS; i++)
		{
			m_Blocks[i][j].m_nStatus = HAVE_BLOCK;
			m_Blocks[HORIZONTAL_BLOCKS_NUMBER + WALL_THICKNESS + i][j].m_nStatus = HAVE_BLOCK;
		}
	for(int i = WALL_THICKNESS; i < HORIZONTAL_BLOCKS_NUMBER + WALL_THICKNESS; i++)
		for(int j = 0; j < WALL_THICKNESS; j++)
		{
			m_Blocks[i][j].m_nStatus = NO_BLOCK;
			m_Blocks[i][VERTICAL_BLOCKS_NUMBER + WALL_THICKNESS + j] = HAVE_BLOCK;
		}
}

BOOL CTetrisControl::InitBasicShapes()
{
	int nShapeListIndex = 0;
	int nBlockNum;
	for(int i = 0; i < SHAPES_NUMBER; i++)
	{
		nBlockNum = nShapeList[nShapeListIndex++];
		for(int j = 0; j < 4; j++)
		{
			m_ShapeList[i][j].m_bBlocks = nBlockNum;
			for(int k = 0; k < nBlockNum; k++)
			{
				m_ShapeList[i][j].m_ptBlocks[k].x = nShapeList[nShapeListIndex++];
				m_ShapeList[i][j].m_ptBlocks[k].y = nShapeList[nShapeListIndex++];
			}
		}
	}

	CalcShapeRotateState();
	return TRUE;
}

BOOL CTetrisControl::InitScoreLevel(const int nScoreLevel[])
{
	for(int i = 0; i < BLOCKS_IN_SHAPE; i++)
		m_nScoreLevel[i] = nScoreLevel[i];
	return TRUE;
}

void CTetrisControl::SetInitFloors(int nInitFloors)
{
	m_nInitFloors = nInitFloors;
}

BOOL CTetrisControl::InitFloors(int nInitFloors, int nBlockSeed)
{
	if(nInitFloors < 0 || nInitFloors > VERTICAL_BLOCKS_NUMBER)
		return FALSE;
	m_nHighestBlock = nInitFloors;
	for(int i = 0; i < VERTICAL_BLOCKS_NUMBER; i++)
		m_nCurBlocksInFloor[i] = 0;
	// initialize the exist blocks
	m_nBlockSeed = nBlockSeed;
	BYTE nStatus;
	int j;
	for(j = 0; j < nInitFloors; j++)
	{
		CalcBlocksStatusInFloor();
		int i;
		for(i = WALL_THICKNESS; i < HORIZONTAL_BLOCKS_NUMBER + WALL_THICKNESS; i ++)
		{
			// choose a existence status randomly
			if((nStatus = m_bBlocksStatusInFloor[i - WALL_THICKNESS])== HAVE_BLOCK)
				m_nCurBlocksInFloor[j]++;
			m_Blocks[i][VERTICAL_BLOCKS_NUMBER + WALL_THICKNESS - 1 - j].m_nStatus = nStatus;
			// choose a color randomly
			m_nBlockSeed = Rand(m_nBlockSeed);
			m_Blocks[i][VERTICAL_BLOCKS_NUMBER + WALL_THICKNESS - 1 - j].m_nColor
				 = m_nBlockSeed * m_nBlockColorsNum / OWN_RAND_MAX;
			m_Blocks[i][VERTICAL_BLOCKS_NUMBER + WALL_THICKNESS - 1 - j].m_nStyle
				 = int(rand()*32/RAND_MAX);
		}
	}
	// clear other positions
	for(; j < VERTICAL_BLOCKS_NUMBER + WALL_THICKNESS; j++)
		for(int i = WALL_THICKNESS; i < HORIZONTAL_BLOCKS_NUMBER + WALL_THICKNESS; i ++)
			m_Blocks[i][VERTICAL_BLOCKS_NUMBER + WALL_THICKNESS - 1 - j].m_nStatus = NO_BLOCK;

	return TRUE;
}

void CTetrisControl::CalcShapeRotateState()
{
	for(int i = 0; i < SHAPES_NUMBER; i++)
	{
		if(m_ShapeList[i][0].m_bBlocks == 1)
		{
			m_nShapeRotateState[i] = 1;
			break;
		}
		if(m_ShapeList[i][0] == m_ShapeList[i][2] && m_ShapeList[i][1] == m_ShapeList[i][3])
		{
			if(m_ShapeList[i][0] == m_ShapeList[i][1])
				m_nShapeRotateState[i] = 4;
			else
				m_nShapeRotateState[i] = 2;
		}
		else
			m_nShapeRotateState[i] = 4;
	}
}

void CTetrisControl::Start(int nSeed)
{
	// reset some members
	m_nFloorsBuffer = 0;
	m_nShapeSeed = nSeed;
	m_fSmoothDown = 0;
	m_fSmoothRotate = 0;
	m_bIsGameOver = FALSE;
	m_nCurDelFloors = 0;
	m_bIsWillFix = TRUE;
	InitFloors(m_nInitFloors, nSeed);
	m_nCurScore = 0;
	for(int i = 0; i < BLOCKS_IN_SHAPE; i++)
		m_nCramedFloors[i] = -1;

	CreateShape(FALSE);
	int max = 10;	// try 10 times to get a decent shape
	while (m_nCurShapeType > 2 && m_nCurShapeType != 5 && max-- > 0) {
		CreateShape(FALSE);
	}
	m_NextShape.m_nColor = -1;		// clear data from last game. :if(nShapeType == m_NextShape.m_nColor)
	CreateShape();
}

void CTetrisControl::CreateShape(BOOL bIsNext)
{
	m_RotateClockwise = FALSE;
	m_fSmoothRotate	= 0;
	m_nShapeSeed = Rand(m_nShapeSeed);
	int nShapeType = m_nShapeSeed* (SHAPES_NUMBER - 1) / OWN_RAND_MAX;
	int	nDirection = DIRECTION_UP;
	if(bIsNext)
	{
		if(nShapeType == m_NextShape.m_nColor)
			nShapeType = Rand(m_nShapeSeed) * (SHAPES_NUMBER - 1) / OWN_RAND_MAX;
		m_NextShape = CreateSpecificShape(nShapeType, nDirection);
		m_nNextShapeType = nShapeType;
		m_nNextShapeDir = nDirection;
	}
	else
	{
		m_CurShape = CreateSpecificShape(nShapeType, nDirection);
		m_nCurShapeType = nShapeType;
		m_nCurShapeDir = nDirection;
	}

}

CShape CTetrisControl::CreateSpecificShape(int nShapeType, int nDirection)
{
	int nMidPosX = (HORIZONTAL_BLOCKS_NUMBER - 1) / 2;
	CShape shape;
	shape = m_ShapeList[nShapeType][nDirection];
	shape.m_nColor = nShapeType;
	shape.m_ptPos = CPoint(nMidPosX, 0);
	return shape;
}

BOOL CTetrisControl::OnLeft()
{
	int x, y;
	for(int i = 0; i < m_CurShape.m_bBlocks; i++)
	{
		x = m_CurShape.m_ptPos.x + WALL_THICKNESS + m_CurShape.m_ptBlocks[i].x - 1;
		y = m_CurShape.m_ptPos.y + WALL_THICKNESS + m_CurShape.m_ptBlocks[i].y;
		if(m_Blocks[x][y].m_nStatus == HAVE_BLOCK)
			return FALSE;
	}
	m_CurShape.m_ptPos.x--;
	return TRUE;
}

BOOL CTetrisControl::OnRight()
{
	int x, y;
	for(int i = 0; i < m_CurShape.m_bBlocks; i++)
	{
		x = m_CurShape.m_ptPos.x + WALL_THICKNESS + m_CurShape.m_ptBlocks[i].x + 1;
		y = m_CurShape.m_ptPos.y + WALL_THICKNESS + m_CurShape.m_ptBlocks[i].y;
		if(m_Blocks[x][y].m_nStatus == HAVE_BLOCK)
			return FALSE;
	}
	m_CurShape.m_ptPos.x++;
	return TRUE;
}

BOOL CTetrisControl::OnRotate()
{
	CShape shape;
	int nDirection;
	if((nDirection = m_nCurShapeDir + 1) == 4)
		nDirection = 0;
	shape = m_ShapeList[m_nCurShapeType][nDirection];
	
	int x, y;
	for(int i = 0; i < m_CurShape.m_bBlocks; i++)
	{
		x = m_CurShape.m_ptPos.x + WALL_THICKNESS + shape.m_ptBlocks[i].x;
		y = m_CurShape.m_ptPos.y + WALL_THICKNESS + shape.m_ptBlocks[i].y;
		if(m_Blocks[x][y].m_nStatus == HAVE_BLOCK)
			return FALSE;
	}
	m_CurShape = m_ShapeList[m_nCurShapeType][nDirection];
	m_nCurShapeDir = nDirection;
	return TRUE;
}

BOOL CTetrisControl::OnStartSmoothRotate()
{
	BOOL bResult = OnRotate();
	if(bResult)
	{
		if(m_nShapeRotateState[m_nCurShapeType] == 4)
			m_fSmoothRotate--;
		if(m_nShapeRotateState[m_nCurShapeType] == 2)
		{
			if(m_RotateClockwise)
				m_fSmoothRotate++;
			else
				m_fSmoothRotate--;
			m_RotateClockwise=!m_RotateClockwise;
		}
	}
	return bResult;
}

float CTetrisControl::OnSmoothRotate(float fSmoothInc)
{
	if(m_fSmoothRotate < 0)
	{
		m_fSmoothRotate += fSmoothInc;
		if(m_fSmoothRotate < -1)
			m_fSmoothRotate += fSmoothInc;
		if(m_fSmoothRotate < -2)
			m_fSmoothRotate += fSmoothInc;
		if(m_fSmoothRotate > 0)
			m_fSmoothRotate = 0;
	}
	else if(m_fSmoothRotate > 0)
	{
		m_fSmoothRotate -= fSmoothInc;
		if(m_fSmoothRotate < 0)
			m_fSmoothRotate = 0;
	}
	return m_fSmoothRotate;
}

int CTetrisControl::OnDown()
{
	int x, y;
	int i;
	for(i = 0; i < m_CurShape.m_bBlocks; i++)
	{
		x = m_CurShape.m_ptPos.x + WALL_THICKNESS + m_CurShape.m_ptBlocks[i].x;
		y = m_CurShape.m_ptPos.y + WALL_THICKNESS + m_CurShape.m_ptBlocks[i].y + 1;
		if(m_Blocks[x][y].m_nStatus == HAVE_BLOCK)
			break;
	}
	if(i < m_CurShape.m_bBlocks) // the shape has been blocked
	{
		FixCurShape();
		m_nCurDelFloors = CalcDeletedFloors();
		if(m_nCurDelFloors > 0)
			m_nCurScore += m_nScoreLevel[m_nCurDelFloors - 1];
		if(m_nHighestBlock - m_nCurDelFloors + m_nFloorsBuffer > VERTICAL_BLOCKS_NUMBER)
		{
			m_bIsGameOver = TRUE;
			m_bIsWillFix = FALSE;
		}
		else
		{
		}
		return m_nCurDelFloors;
	}
	else
	{
		m_CurShape.m_ptPos.y++;
		return -1;
	}
}

void CTetrisControl::FinishLineDeletion()
{
	// finished the last time operation
	if (m_nCurDelFloors > 0)
		DeleteFloors();
	if (m_nFloorsBuffer > 0)
		AddFloors();
}

BOOL CTetrisControl::CreateNewShape()
{
	FinishLineDeletion();
	m_CurShape = m_NextShape;
	m_nCurShapeType = m_nNextShapeType;
	m_nCurShapeDir = m_nNextShapeDir;
	CreateShape();
	int x, y;
	for(int i = 0; i < m_CurShape.m_bBlocks; i++)
	{
		x = m_CurShape.m_ptPos.x + WALL_THICKNESS + m_CurShape.m_ptBlocks[i].x;
		y = m_CurShape.m_ptPos.y + WALL_THICKNESS + m_CurShape.m_ptBlocks[i].y;
		if(m_Blocks[x][y].m_nStatus == HAVE_BLOCK)
		{
			m_bIsGameOver = TRUE;
			FixCurShape();
			return FALSE;
		}
	}
	return TRUE;
}

int CTetrisControl::OnSmoothDown(float fSmoothInc)
{
	int nResult = -1;
	m_fSmoothDown += fSmoothInc;
	if(m_fSmoothDown > 1)
	{
		nResult = OnDown();
		m_fSmoothDown -= 1;
		if(nResult > -1)
			m_fSmoothDown = 0;
	}
	return nResult;
}

int CTetrisControl::OnDownToBottom()
{
	int nResult;
	while((nResult = OnDown()) == -1);
	m_fSmoothDown = 0;
	return nResult;
}

void CTetrisControl::FixCurShape()
{
	if(m_bIsWillFix)
	{
		int x, y;
		for(int i = 0; i < m_CurShape.m_bBlocks; i++)
		{
			x = m_CurShape.m_ptPos.x + WALL_THICKNESS + m_CurShape.m_ptBlocks[i].x;
			y = m_CurShape.m_ptPos.y + WALL_THICKNESS + m_CurShape.m_ptBlocks[i].y;
			m_Blocks[x][y].m_nStatus = HAVE_BLOCK;
			m_Blocks[x][y].m_nColor = m_CurShape.m_nColor;
			m_Blocks[x][y].m_nStyle = int(rand()*32/RAND_MAX);
			m_nCurBlocksInFloor[VERTICAL_BLOCKS_NUMBER + WALL_THICKNESS - 1 - y]++;
			if(VERTICAL_BLOCKS_NUMBER + WALL_THICKNESS - y > m_nHighestBlock)
				m_nHighestBlock = VERTICAL_BLOCKS_NUMBER + WALL_THICKNESS - y;
		}
	}
	else
		m_bIsWillFix = TRUE;
}

int CTetrisControl::CalcDeletedFloors()
{
	int nDelFloors = 0;
	for(int i = 0; i < m_CurShape.m_bBlocks; i++)
	{
		int y = m_CurShape.m_ptPos.y + WALL_THICKNESS + m_CurShape.m_ptBlocks[i].y;
		if(m_nCurBlocksInFloor[VERTICAL_BLOCKS_NUMBER + WALL_THICKNESS - 1 - y] == HORIZONTAL_BLOCKS_NUMBER)
		// the current floor is full
		{
			// save the index (y-coordiate) of the floor
			int j;
			for(j = 0; j < BLOCKS_IN_SHAPE; j++)
			{
				// the floor existed, don't save anymore
				if(m_nCramedFloors[j] == (y - WALL_THICKNESS))
					break;
			}
			if(j == BLOCKS_IN_SHAPE)
			{
				nDelFloors++;
				for(j = 0; j < nDelFloors; j++)
					if(m_nCramedFloors[j] < (y - WALL_THICKNESS))
					{
						for(int k = nDelFloors - 1; k > j ; k--)
							m_nCramedFloors[k] = m_nCramedFloors[k - 1];
						m_nCramedFloors[j] = y - WALL_THICKNESS;
						break;
					}
			}
		}
	}
	return nDelFloors;
}

void CTetrisControl::DeleteFloors()
{
	// delete floors 
	int nDelCounter = 0;
	for(int i = 0; i < BLOCKS_IN_SHAPE; i++)
		if(m_nCramedFloors[i] != -1)
		{
			for(int k = WALL_THICKNESS; k < HORIZONTAL_BLOCKS_NUMBER + WALL_THICKNESS; k++)
				m_Blocks[k][m_nCramedFloors[i] + WALL_THICKNESS].m_nStatus = NO_BLOCK;
			m_nCurBlocksInFloor[VERTICAL_BLOCKS_NUMBER - 1 - m_nCramedFloors[i]] = 0;
			nDelCounter--;
		}
	// move the remaining floors
	for(int i = VERTICAL_BLOCKS_NUMBER - 1;
		i > VERTICAL_BLOCKS_NUMBER - 1 - m_nHighestBlock; i--)
	{
		int j;
		for(j = 0; j < BLOCKS_IN_SHAPE; j++)
			if(m_nCramedFloors[j] <= i)
				break;
		if(j > 0)
		{
			for(int k = WALL_THICKNESS; k < HORIZONTAL_BLOCKS_NUMBER + WALL_THICKNESS; k++)
			{
				m_Blocks[k][i + j + WALL_THICKNESS] = m_Blocks[k][i + WALL_THICKNESS];
				m_Blocks[k][i + WALL_THICKNESS].m_nStatus = NO_BLOCK;
			}
			m_nCurBlocksInFloor[VERTICAL_BLOCKS_NUMBER - 1 - i - j]
				= m_nCurBlocksInFloor[VERTICAL_BLOCKS_NUMBER - 1 - i];
			m_nCurBlocksInFloor[VERTICAL_BLOCKS_NUMBER - 1 - i] = 0;
		}
	}
	// reset the m_nCramedFloors array
	for(int i = 0; i < BLOCKS_IN_SHAPE; i++)
		m_nCramedFloors[i] = -1;
	m_nHighestBlock += nDelCounter;
	m_nCurDelFloors = 0;
}

int CTetrisControl::AddFloorsBuffer(int nAdd)
{
	m_nFloorsBuffer += nAdd;
	return m_nFloorsBuffer;
}

void CTetrisControl::AddFloors()
{
	// find the start floor to move
	int nStart;
	if(m_nFloorsBuffer + m_nHighestBlock > VERTICAL_BLOCKS_NUMBER)
		nStart = m_nFloorsBuffer + WALL_THICKNESS;
	else
		nStart = VERTICAL_BLOCKS_NUMBER - m_nHighestBlock + WALL_THICKNESS;
	// move the remaining floors;
	for(int i = nStart; i < VERTICAL_BLOCKS_NUMBER + WALL_THICKNESS; i++)
		for(int j = WALL_THICKNESS; j < HORIZONTAL_BLOCKS_NUMBER + WALL_THICKNESS; j++)
		{
			m_Blocks[j][i - m_nFloorsBuffer] = m_Blocks[j][i];
			m_nCurBlocksInFloor[VERTICAL_BLOCKS_NUMBER + WALL_THICKNESS - 1 - i + m_nFloorsBuffer]
				= m_nCurBlocksInFloor[VERTICAL_BLOCKS_NUMBER + WALL_THICKNESS - 1 - i];
		}
	// add new floors from the bottom
	BYTE nStatus;
	for(int j = 0; j < m_nFloorsBuffer; j++)
	{
		CalcBlocksStatusInFloor();
		m_nCurBlocksInFloor[j] = 0;
		for(int i = WALL_THICKNESS; i < HORIZONTAL_BLOCKS_NUMBER + WALL_THICKNESS; i ++)
		{
			// choose a existence status randomly
			if((nStatus = m_bBlocksStatusInFloor[i - WALL_THICKNESS])== HAVE_BLOCK)
				m_nCurBlocksInFloor[j]++;
			m_Blocks[i][VERTICAL_BLOCKS_NUMBER + WALL_THICKNESS - 1 - j].m_nStatus = nStatus;
			// choose a color randomly
			m_nBlockSeed = Rand(m_nBlockSeed);
			m_Blocks[i][VERTICAL_BLOCKS_NUMBER + WALL_THICKNESS - 1 - j].m_nColor = 
				m_nBlockSeed * m_nBlockColorsNum / OWN_RAND_MAX;
			m_Blocks[i][VERTICAL_BLOCKS_NUMBER + WALL_THICKNESS - 1 - j].m_nStyle = 
				int(rand()*32/RAND_MAX);
		}
	}
	m_nHighestBlock += m_nFloorsBuffer;
	m_nFloorsBuffer = 0;
}

void CTetrisControl::CalcBlocksStatusInFloor()
{
	for(int i = 0; i < HORIZONTAL_BLOCKS_NUMBER; i++)
		m_bBlocksStatusInFloor[i] = HAVE_BLOCK;
	m_nBlockSeed = Rand(m_nBlockSeed);
	int nNoBlockNum = MIN_NO_BLOCK_NUMBER + (MAX_NO_BLOCK_NUMBER - MIN_NO_BLOCK_NUMBER + 1)
		* m_nBlockSeed / OWN_RAND_MAX;
	int nPos;
	for(int i = 0; i < nNoBlockNum; i++)
	{
		m_nBlockSeed = Rand(m_nBlockSeed);
		nPos = HORIZONTAL_BLOCKS_NUMBER * m_nBlockSeed / OWN_RAND_MAX;
		m_bBlocksStatusInFloor[nPos] = NO_BLOCK;
	}
}

int CTetrisControl::Rand(int nSeed, int nMax)
{
	return	(nSeed*25173+13849) % nMax;
}

////////////////////////////////////////////////////////

CBlock::CBlock(BYTE nStatus,BYTE nColor, BYTE nStyle)
{
	m_nStatus = nStatus;
	m_nColor = nColor;
	m_nStyle = nStyle;
}

void CBlock::operator = (const CBlock& block)
{
	m_nStatus = block.m_nStatus;
	m_nColor = block.m_nColor;
	m_nStyle = block.m_nStyle;
}

////////////////////////////////////////////////////////

CBasicShape::CBasicShape()
{
	for(int i = 0; i < BLOCKS_IN_SHAPE; i++)
		m_ptBlocks[i] = CPoint(-BLOCKS_IN_SHAPE, -BLOCKS_IN_SHAPE);
	m_bBlocks = 0;
}

void CBasicShape::operator = (const CBasicShape& shape)
{
	for(int i = 0; i < BLOCKS_IN_SHAPE; i++)
		m_ptBlocks[i] = shape.m_ptBlocks[i];
	m_bBlocks = shape.m_bBlocks;
}

BOOL CBasicShape::operator == (const CBasicShape& shape)
{
	BOOL bResult = TRUE;
	for(int i = 0; i < BLOCKS_IN_SHAPE; i++)
		if(m_ptBlocks[i] != shape.m_ptBlocks[i])
			return FALSE;
	return bResult;
}

////////////////////////////////////////////////////////

CShape::CShape()
{
	CBasicShape::CBasicShape();
	m_nColor = 0;
	m_ptPos = CPoint(0, 0);
}

void CShape::operator = (const CShape& shape)
{
	for(int i = 0; i < BLOCKS_IN_SHAPE; i++)
		m_ptBlocks[i] = shape.m_ptBlocks[i];
	m_bBlocks = shape.m_bBlocks;
	m_nColor = shape.m_nColor;
	m_ptPos = shape.m_ptPos;
}

void CShape::operator = (const CBasicShape& shape)
{
	for(int i = 0; i < BLOCKS_IN_SHAPE; i++)
		m_ptBlocks[i] = shape.m_ptBlocks[i];
	m_bBlocks = shape.m_bBlocks;
}