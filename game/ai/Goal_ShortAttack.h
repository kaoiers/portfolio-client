//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/06/09
//
// File Name : Goal_ShortAttack.h
// 
// 단일 목적 : 근거리 공격(아군)
//
//////////////////////////////////////////////////////////////////////////

#ifndef GOAL_SHORT_ATTACK_H
#define GOAL_SHORT_ATTACK_H

#pragma warning (disable:4786)

#include "Goal.h"

class CGameUnit;

class Goal_ShortAttack : public Goal<CGameUnit>
{
private:


	CGameUnit*		m_pTarget;		


public:

	Goal_ShortAttack(CGameUnit* pUnit, CGameUnit* pTarget);

	//the usual suspects
	void Activate();
	s32  Process();
	void Terminate();

};

#endif