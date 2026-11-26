//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/06/02
//
// File Name : Goal_AttackTarget.h
// 
// 복합 목적 : 공격하기
//
//////////////////////////////////////////////////////////////////////////

#ifndef GOAL_ATTACKTARGET_H
#define GOAL_ATTACKTARGET_H
#pragma warning (disable:4786)

#include "Goal_Composite.h"

class CGameUnit;
class CGameUnitEnemy;
class Regulator;





class Goal_AttackTarget : public Goal_Composite<CGameUnit>
{

	Regulator*			m_attack_regulator;

	bool				m_is_enemy;


public:

	Goal_AttackTarget(CGameUnit* p_owner);

	void activate();


	s32  process();
	void terminate();
	bool notPresent(u32 goal_type)const;
};






#endif
