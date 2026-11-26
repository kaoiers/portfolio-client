//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/05/03
//
// File Name : Goal_SeekToPosition.h
// 
// 단일 목적 : 목적지점으로 이동하기
//
//////////////////////////////////////////////////////////////////////////


#ifndef GOAL_SEEK_TO_POSITION_H
#define GOAL_SEEK_TO_POSITION_H

#pragma warning (disable:4786)

#include "Goal.h"

class CGameUnit;
class Regulator;

class Goal_SeekToPosition : public Goal<CGameUnit>
{
private:

	//the position the bot is moving to
	vector3df	m_vPosition;

	//the approximate time the bot should take to travel the target location
	double					m_dTimeToReachPos;

	//this records the time this goal was activated
	double					m_dStartTime;

	Regulator*				m_pUpdateSendMovePacketRegulator;

	//returns true if a bot gets stuck
	bool      isStuck()const;

	bool		StopSeeking();

public:

	Goal_SeekToPosition(CGameUnit* pUnit, vector3df target);

	//the usual suspects
	void Activate();
	s32  Process();
	void Terminate();
	
};

#endif