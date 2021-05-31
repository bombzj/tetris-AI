#include "stdafx.h"
#include "TetrisRecord.h"

void CTetrisRecord::AddAction(int action)
{
	m_actionList.push_back(TetrisAction(m_curTick, action));
}

void CTetrisRecord::init(int seed)
{
	m_actionList.clear();
	this->seed = seed;
	m_curTick = 0;
}

void CTetrisRecord::initRead()
{
	m_curTick = 0;
	this->iter = m_actionList.begin();
}

int CTetrisRecord::read()
{
	if (iter != m_actionList.end()) {
		TetrisAction act = (*iter);
		if (act.tick <= m_curTick) {
			iter++;
			return act.action;
		}
	}
	return -1;
}
