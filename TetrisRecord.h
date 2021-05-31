#pragma once
#include <list>

struct TetrisAction {
	TetrisAction(int tick, int action) {
		this->tick = tick;
		this->action = action;
	}
	int tick;
	int action;
};

class CTetrisRecord
{
public:
	int m_curTick;
	std::list<TetrisAction> m_actionList;
	int seed;
	std::list<TetrisAction>::iterator iter;


	void AddAction(int action);
	void init(int seed);
	void initRead();
	int read();
};

