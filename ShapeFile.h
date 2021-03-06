//
//	ShapeFile.h
//
//		--	define the shape in the game
//
///////////////////////////////////////////////////////

#ifndef _TETRIS_SHAPEFILE_ZJ_SM_SXC
#define _TETRIS_SHAPEFILE_ZJ_SM_SXC

const int nShapeList[] = {
	4,	// stick
	-1, 0, 0, 0, 1, 0, 2, 0, 
	1, -1, 1, 0, 1, 1, 1, 2, 
	-1, 0, 0, 0, 1, 0, 2, 0, 
	1, -1, 1, 0, 1, 1, 1, 2, 
	4,	// 'L' shape
	0, 0, 1, 0, 2, 0, 0, 1,
	1, -1, 1, 0, 1, 1, 2, 1, 
	2, -1, 0, 0, 1, 0, 2, 0, 
	0, -1, 1, -1, 1, 0, 1, 1, 
	4, // 'J' shape
	0, 0, 1, 0, 2, 0, 2, 1, 
	1, -1, 2, -1, 1, 0, 1, 1, 
	0, -1, 0, 0, 1, 0, 2, 0, 
	1, -1, 1, 0, 0, 1, 1, 1,
	4, // 'S' shape
	1, 0, 2, 0, 0, 1, 1, 1,
	0, 0, 0, 1, 1, 1, 1, 2,
	1, 0, 2, 0, 0, 1, 1, 1,
	0, 0, 0, 1, 1, 1, 1, 2,
	4, // 'Z' shape
	0, 0, 1, 0, 1, 1, 2, 1, 
	1, 0, 0, 1, 1, 1, 0, 2,
	0, 0, 1, 0, 1, 1, 2, 1, 
	1, 0, 0, 1, 1, 1, 0, 2,
	4, // convex shape
	0, 0, 1, 0, 2, 0, 1, 1,
	1, -1, 1, 0, 2, 0, 1, 1,
	1, -1, 0, 0, 1, 0, 2, 0,
	1, -1, 0, 0, 1, 0, 1, 1,
	4, // block
	0, 0, 1, 0, 0, 1, 1, 1,
	0, 0, 1, 0, 0, 1, 1, 1,
	0, 0, 1, 0, 0, 1, 1, 1,
	0, 0, 1, 0, 0, 1, 1, 1,
	1, // point
	1, 0,
	1, 0,
	1, 0,
	1, 0,
};

#endif // _TETRIS_SHAPEFILE_ZJ_SM_SXC

