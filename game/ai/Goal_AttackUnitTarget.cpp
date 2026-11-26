//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/05/04
//
// File Name : Goal_AttacUnitkTarget.cpp
// 
// 복합 목적 : 공격하기
//
//////////////////////////////////////////////////////////////////////////


#include <stdafx.h>
#include "Goal_AttackUnitTarget.h"
#include "Goal_SeekToPosition.h"
#include "Goal_ShortAttack.h"
#include "Goal_Enemy_ShortAttack.h"
#include "Goal_MoveToPosition.h"


#include "../objects/CGameUnitEnemy.h"



#include "../objects/CGameUnit.h"



//------------------------------- Activate ------------------------------------
//-----------------------------------------------------------------------------
void Goal_AttackUnitTarget::activate()
{
	m_status = active;

	m_enemy = dynamic_cast<CGameUnitEnemy *>(m_owner);

	//m_pTarget = m_pEnemy->getEnemyTargetingSystem()->getUnitTarget();


	m_status = completed;


}




//-------------------------- Process ------------------------------------------
//-----------------------------------------------------------------------------
s32 Goal_AttackUnitTarget::process()
{
	//if status is inactive, call Activate()
	activateIfInactive();

	//process the subgoals
	m_status = processSubgoals();

	//m_SubGoals.front().front();



	//it is possible for a bot's target to die whilst this goal is active so we
	//must test to make sure the bot always has an active target	
	reactivateIfFailed();


	return m_status;
}


bool Goal_AttackUnitTarget::notPresent(u32 goal_type)const
{
	if (!m_sub_goals.empty())
	{
		return m_sub_goals.front()->getType() != goal_type;
	}

	return true;
}




void Goal_AttackUnitTarget::terminate()
{
	m_status = completed;
}

Goal_AttackUnitTarget::Goal_AttackUnitTarget( CGameUnit* p_owner ):Goal_Composite<CGameUnit>(p_owner, goal_attack_unit_target)
{
	//m_pUpdateRegulator = new Regulator(2.0f);
}

void Goal_AttackUnitTarget::stopHunting()
{
	//m_pOwner->GetSteering()->SeekOff();

	//m_pOwner->GetSteering()->ArriveOff();
	
	//m_pOwner->SetVelocity(vector3df(0,0,0));

	//m_pOwner->GetAnimationMgr()->SetDefaultAni();

}