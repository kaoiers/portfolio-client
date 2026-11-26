//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/05/04
//
// File Name : Goal_AttackTarget.h
// 
// 복합 목적 : 공격하기
//
//////////////////////////////////////////////////////////////////////////

#ifndef GOAL_ATTACKUNITTARGET_H
#define GOAL_ATTACKUNITTARGET_H
#pragma warning (disable:4786)

#include "Goal_Composite.h"

class CGameUnit;
class CGameUnitEnemy;
class Regulator;





class Goal_AttackUnitTarget : public Goal_Composite<CGameUnit>
{

	Regulator*			m_pAttackRegulator;

	bool				m_bEnemy;

	CGameUnitEnemy*		m_pEnemy;
	CGameUnit*			m_pTarget;
	


public:

	Goal_AttackUnitTarget(CGameUnit* pOwner);
	~Goal_AttackUnitTarget() 
	{


	};

	void Activate();

	
	void ActivateForUnit(CGameUnit*	pUnit);
	s32  Process();
	void Terminate();
	bool notPresent(u32 GoalType)const;
  void StopHunting();

};






#endif
