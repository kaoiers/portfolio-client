//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/05/19
//
// File Name : Goal_ShortAttack.h
// 
// 단일 목적 : 근거리 공격하기
//
//////////////////////////////////////////////////////////////////////////

#ifndef GOAL_ENEMY_SHORT_ATTACK_H
#define GOAL_ENEMY_SHORT_ATTACK_H

#pragma warning (disable:4786)

#include "Goal.h"

class CGameUnit;
class CGameUnitEnemy;

class Goal_Enemy_ShortAttack : public Goal<CGameUnit>
{
private:

	CGameUnitEnemy*	m_enemy;

	CGameUnit*		m_target;		


public:

	Goal_Enemy_ShortAttack(CGameUnitEnemy* p_unit, CGameUnit* p_target);

	void activate();
	s32  process();
	void terminate();

};


#endif