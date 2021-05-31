#include "stdafx.h"
#include "TetrisRecord.h"

void CTetrisRecord::AddAction(int player, int action)
{
	if(player == 0)
		m_actionList.push_back(TetrisAction(m_curTick, action));
	else
		m_actionList2.push_back(TetrisAction(m_curTick, action));
}

void CTetrisRecord::init(int seed)
{
	m_actionList.clear();
	m_actionList2.clear();
	this->seed = seed;
	m_curTick = 0;
}

void CTetrisRecord::initRead()
{
	m_curTick = 0;
	iter = m_actionList.begin();
	iter2 = m_actionList2.begin();
}

int CTetrisRecord::read(int player)
{
	if (player == 0) {
		if (iter != m_actionList.end()) {
			TetrisAction act = (*iter);
			if (act.tick <= m_curTick) {
				iter++;
				return act.action;
			}
		}
	}
	else {
		if (iter2 != m_actionList2.end()) {
			TetrisAction act = (*iter2);
			if (act.tick <= m_curTick) {
				iter2++;
				return act.action;
			}
		}
	}
	return -1;
}
