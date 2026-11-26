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

	Regulator*			m_pAttackRegulator;

	bool				m_bEnemy;


public:

	Goal_AttackTarget(CGameUnit* pOwner);

	void Activate();


	int  Process();
	void Terminate();
	bool notPresent(unsigned int GoalType)const;
};






#endif
