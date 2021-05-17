//
//	TetrisControl.h
//
//		--	The declaration file of CTetrisControl class
//
///////////////////////////////////////////////////////

#ifndef _TETRIS_ENGINE_CLASS_ZJ_SM_SXC
#define _TETRIS_ENGINE_CLASS_ZJ_SM_SXC

///////////////////////////////////////////////////////
//	CBlock class
////////////////////////////////////////////////////////

#define	NO_BLOCK	0
#define	HAVE_BLOCK	1

class CBlock
{
public:
	CBlock::CBlock(BYTE nStatus = NO_BLOCK,BYTE nColor = 0, BYTE nStyle=0);
	BYTE	m_nStatus;	// contains the status of block, can be NO_BLOCK (not existed) or 
						// HAVE_BLOCK (existed).
	BYTE	m_nColor;	// contains the color of the existed block. The default maximum number
						// of the colors is equal to SHAPES_NUMBER, but you can change it in 
						// the constructor of CTetrisControl class.
	BYTE	m_nStyle;	// contains the explosion direction and type.
	void operator = (const CBlock& block);
};

///////////////////////////////////////////////////////
//	CBasicShape class
////////////////////////////////////////////////////////

#ifndef BLOCKS_IN_SHAPE	// the maximum number of blocks in one shape
#define BLOCKS_IN_SHAPE 4
#endif // BLOCKS_IN_SHAPE

class CBasicShape
{
public:
	CBasicShape::CBasicShape();
	CPoint	m_ptBlocks[BLOCKS_IN_SHAPE];
				// specifies the positions of blocks of this shape.
	BYTE	m_bBlocks;
	void operator = (const CBasicShape& shape);
				// assignment operator, reinitializing an existing object with new data.
	BOOL operator == (const CBasicShape& shape);
				// Checks for equality between two sizes. 
				// Returns nonzero if the sizes are equal, otherwize 0.
};

///////////////////////////////////////////////////////
//	CShape class
////////////////////////////////////////////////////////

class CShape : public CBasicShape
{
public:
	CShape::CShape();
	BYTE	m_nColor;	// contains the color of blocks in this shape.
	CPoint	m_ptPos;	// contains the position of the shape in the coordinate system of game 
						// area (not including the wall blocks).
	void operator = (const CShape& shape);
						// assignment operator, reinitializing an existing object with new data.
	void operator = (const CBasicShape& shape);
						// Checks for equality between two sizes. 
						// Returns nonzero if the sizes are equal, otherwize 0.
};

///////////////////////////////////////////////////////
//	CTetrisControl class
///////////////////////////////////////////////////////

// the number of blocks in a horizontal direction in the game area
#ifndef HORIZONTAL_BLOCKS_NUMBER
#define HORIZONTAL_BLOCKS_NUMBER 10
#endif // HORIZONTAL_BLOCKS_NUMBER

// the number of blocks in a vertical direction in the game area
#ifndef VERTICAL_BLOCKS_NUMBER
#define VERTICAL_BLOCKS_NUMBER 20
#endif // VERTICAL_BLOCKS_NUMBER

// the thickness of the wall of the game area in unit of block
#ifndef WALL_THICKNESS
#define WALL_THICKNESS 2
#endif // WALL_THICKNESS

// the number of basic shapes in the game
#ifndef SHAPES_NUMBER
#define SHAPES_NUMBER 8
#endif // SHAPES_NUMBER

// the movement direction of current shape
#define DIRECTION_UP	0
#define DIRECTION_RIGHT	1
#define DIRECTION_DOWN	2
#define DIRECTION_LEFT	3

// the maximum number of the existed blocks in a randamly created floor
#ifndef MAX_NO_BLOCK_NUMBER
#define MAX_NO_BLOCK_NUMBER 4
#endif

#ifndef MIN_NO_BLOCK_NUMBER // the minimum number of the existed blocks in a randamly created floor
#define MIN_NO_BLOCK_NUMBER 1
#endif

// the maximum number (+ 1) created by my own random function
#define OWN_RAND_MAX 65536

class CTetrisControl
{
public:
	CTetrisControl(int nBlockColorsNum = SHAPES_NUMBER);	
						// nBlockColorsNum specifies the number of the colors used in the block.
						// you may create a color table design color form 0 ~ nBlockColorsNum -1 
						// -1 is the reserved intial value.
	~CTetrisControl();
															
// Attributes
public:
	// General attributes
	CBlock&	GetBlock(int nx, int ny);
						// Call this function to retrieve info of the block specified by nx and ny.
						// nx, ny, the x and y coordinates based on the top-left corner of the 
						// game area (not including the wall blocks).
	CShape&	GetCurShape();
						// Call this function to retrieve the current shape.
	CShape&	GetNextShape();
						// Call this function to retrieve the next shape.
	int		GetCurScore();
						// Call this function to retrieve the current score.
	int		GetFloorsBuffer();
						// Call this function to retrieve the current number of floors to be added.
	BOOL	IsGameOver();
						// Call this function to judge if the game has been over.
	int		GetCurBlocksInFloor(int nFloor);
						// Call this function to retrieve the current number of existed blocks in
						// a certain floor specified by the nFloor.
						// nFloor, the index of the floor begin with 0 from the bottom floor
	int		GetCramedFloor(int nIndex);
						// Call this function to retrieve the index the floor which was crmed by 
						// the blocks which are to be deleted.
						// nIndex is the index of this kind of floors with a sequence according to
						// the floor index in the game area.
	static	BOOL	InitBasicShapes();
						// Call this function to intialize the static member of basic shapes from 
						// the ShapeFile.h header file.
						// you MUST call (once) this function before you start game.
	static	BOOL	InitScoreLevel(const int nScoreLevel[]);	
						// Call this function to intialize the score awarded level.
						// You should call this function before game start if you want to 
						// calculate scores during the game.
						// nScoreLevel specify a pointer to an int array indicating the score level 
						// with the size of BLOCKS_IN_SHAPE
	void	SetInitFloors(int nInitFloors = 0);
						// Call this function to set the number of intial floors in the beginning.

	// Attributes in some special mode
	float	GetSmoothDown();
						// Call this function to retrieve the step position in the Smooth-Down mode.
	float	GetSmoothRotate();
						// Call this function to retrieve the angle in the Smooth-Rotate mode.

public:
// General operations
	virtual	void	Start(int nSeed);
						// Call this function to start the game and create the current shape and 
						// the next shape.
						// nSeed specifies the seed of the our own pseudo-random function.
	BOOL	OnLeft();	// Call this function to respond to the go-left operation.
						// The return value specifies if the operation is successed.
	BOOL	OnRight();	// Call this function to respond to the go-right operation.
						// The return value specifies if the operation is successed.
	BOOL	OnRotate();	// Call this function to respond to the rotation operation
						// the return value specifies if the operation is successed.
	int		OnDown();	// Call this function to respond to the go-down (one step)operation.
						// The return value specifies the number of deleted floors.
						// You may get details of these floors in m_nCramedFloors.
						// If it equals -1, it means the current shape didn't reach the bottom.
						// If it equals -2, it means the game isover.
	int		OnDownToBottom();
						// Call this function to respond to the down-to-bottom operation.
						// The return value is as same as OnDown's.
	int		AddFloorsBuffer(int nAdd);
						// Call this function to add floors from the bottom.
						// The return value is the current total floor buffer.
	virtual BOOL	CreateNewShape();
						// Call this function to change current shape with next shape and create 
						// a new next shape.
						// The return value specifies if the game is over
						// if it is FALSE, it means the current shape collides with others
						// when it just come out
	void	FinishLineDeletion();

// Operations in some special mode 
	BOOL	OnStartSmoothRotate();
						// Call this function to start the smooth-rotate mode.
	float	OnSmoothRotate(float fSoomthInc);
						// Call this function to respond to the smooth rotation operaton
						// controled by the program timer.
	int		OnSmoothDown(float fSmoothInc);
						// Call this function to respond to the smooth down operation 
						// controled by the program timer.

protected:
	CBlock	m_Blocks[HORIZONTAL_BLOCKS_NUMBER + WALL_THICKNESS * 2][VERTICAL_BLOCKS_NUMBER + WALL_THICKNESS * 2];
				// contains the infomation of blocks including the wall blocks outside game area.
	CShape	m_CurShape;
				// specifies the current descendent shape.
	CShape	m_NextShape;
				// specifies the shape to be occur.
	int		m_nCurScore;
				// contains the current score.
	int		m_nFloorsBuffer;
				// contains the current number of floors to be added.
	BOOL	m_bIsGameOver;
				// specifies if the game is over.
	int		m_nCurBlocksInFloor[VERTICAL_BLOCKS_NUMBER];
				// contains the current number of existed blocks in all the floors.
				// The index of the floor begins with 0 from the bottom floor.
	int		m_nCramedFloors[BLOCKS_IN_SHAPE];	
				// contains the index the floor which was crmed by the blocks which are to be deleted.
	float	m_fSmoothDown;
				// contains the step position in the Smooth-Down mode.
	float	m_fSmoothRotate;
				// contains the angle in the Smooth-Rotate mode.
	BOOL	m_RotateClockwise;
				// specifies if the rotation direction is clockwise.
	int		m_nBlockColorsNum;
				// contains the maximum number of colors which could be appeared in a block.
	static	CBasicShape	m_ShapeList[SHAPES_NUMBER][4];
				// contains all the basic shapes in the game.
	static	int		m_nShapeRotateState[SHAPES_NUMBER];
				// contains the state information of the rotation of all the shapes.
	int		m_nCurShapeType;
				// speicfies the type of the current shape.
	int		m_nCurShapeDir;
				// specifies the direction of the current shape.
	int		m_nNextShapeType;
				// speicfies the type of the next shape.
	int		m_nNextShapeDir;
				// specifies the direction of the next shape.
	int		m_nInitFloors;
				// specifies the number of the initial floors.
	int		m_nHighestBlock;
				// specifies the number of blocks in the highest column.
	static	int	m_nScoreLevel[BLOCKS_IN_SHAPE];
				// contains the score awarded level.
	int		m_nShapeSeed;
				// specifies the seed of the pseudo-random function for creating new shape.
	int		m_nBlockSeed;
				// specifies the seed of 
	BYTE	m_bBlocksStatusInFloor[HORIZONTAL_BLOCKS_NUMBER];
				// contains the existence information of one floor used by the pseudo-random 
				// function for creating new floors.
	int		m_nCurDelFloors;
				// specified the number of the current floors to be deleted.
	BOOL	m_bIsWillFix;
				// specified if the current shape will be fixed.

protected:	
	void	InitWalls();
				// Call this function to initilize the wall blocks.
	BOOL	InitFloors(int nInitFloors = 0, int nBlockSeed = 0);
				// Call this function to prepare for the initial floors and clear old floors.
	void	CreateShape(BOOL bIsNext = TRUE);
				// Call this function to create a new shape.
	CShape	CreateSpecificShape(int nShapeType, int nDirection);
				// Call this function to create a certain type shape.
	static	void	CalcShapeRotateState();
				// Call this function to calculate the state information of the rotation.
	int		CalcDeletedFloors();
				// Call this function to calculate the floors to be deleted.
	void	FixCurShape();
				// Call this function to fix the current shape when it touch the existed blocks.
	void	DeleteFloors();
				// Call this function to delete the cramed floors.
	void	AddFloors();
				// Call this function to all floors from the bottom.
	void	CalcBlocksStatusInFloor();
				// Call this function to calculate the existence information of one floor used by 
				// the pseudo-random function for creating new floors.
	int		Rand(int nSeed, int nMax = OWN_RAND_MAX);
				// Call this function to create a pseudo-random number.
	
}; // class CTetrisControl

///////////////////////////////////////////////////////////////////////////////////////////

inline CBlock& CTetrisControl::GetBlock(int nx, int ny)
{
	ASSERT(nx > -1 && nx < HORIZONTAL_BLOCKS_NUMBER && ny > -1 && ny < VERTICAL_BLOCKS_NUMBER);
	return m_Blocks[nx + WALL_THICKNESS][ny + WALL_THICKNESS];
}

inline CShape& CTetrisControl::GetCurShape()
{
	return m_CurShape;
}

inline CShape& CTetrisControl::GetNextShape()
{
	return m_NextShape;
}

inline int CTetrisControl::GetCurScore()
{
	return m_nCurScore;
}

inline int CTetrisControl::GetFloorsBuffer()
{
	return m_nFloorsBuffer;
}

inline int CTetrisControl::IsGameOver()
{
	return m_bIsGameOver;
}

inline int CTetrisControl::GetCurBlocksInFloor(int nFloor)
{
	ASSERT(nFloor > -1 && nFloor < VERTICAL_BLOCKS_NUMBER);
	return m_nCurBlocksInFloor[nFloor];
}

inline int CTetrisControl::GetCramedFloor(int nIndex)
{
	ASSERT(nIndex > -1 && nIndex < BLOCKS_IN_SHAPE);
	return m_nCramedFloors[nIndex];
}

inline float CTetrisControl::GetSmoothDown()
{
	return m_fSmoothDown;
}

inline float CTetrisControl::GetSmoothRotate()
{
	return m_fSmoothRotate;
}

#endif // _TETRIS_ENGINE_CLASS_ZJ_SM_SXC