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
void Goal_AttackUnitTarget::Activate()
{
	m_iStatus = active;

	m_pEnemy = dynamic_cast<CGameUnitEnemy *>(m_pOwner);

	//m_pTarget = m_pEnemy->getEnemyTargetingSystem()->getUnitTarget();


	m_iStatus = completed;


}




//-------------------------- Process ------------------------------------------
//-----------------------------------------------------------------------------
s32 Goal_AttackUnitTarget::Process()
{
	//if status is inactive, call Activate()
	ActivateIfInactive();

	//process the subgoals
	m_iStatus = ProcessSubgoals();

	//m_SubGoals.front().front();



	//it is possible for a bot's target to die whilst this goal is active so we
	//must test to make sure the bot always has an active target	
	ReactivateIfFailed();


	return m_iStatus;
}


bool Goal_AttackUnitTarget::notPresent(u32 GoalType)const
{
	if (!m_SubGoals.empty())
	{
		return m_SubGoals.front()->GetType() != GoalType;
	}

	return true;
}




void Goal_AttackUnitTarget::Terminate()
{
	m_iStatus = completed;
}

Goal_AttackUnitTarget::Goal_AttackUnitTarget( CGameUnit* pOwner ):Goal_Composite<CGameUnit>(pOwner, goal_attack_unit_target)
{
	//m_pUpdateRegulator = new Regulator(2.0f);
}

void Goal_AttackUnitTarget::StopHunting()
{
	//m_pOwner->GetSteering()->SeekOff();

	//m_pOwner->GetSteering()->ArriveOff();
	
	//m_pOwner->SetVelocity(vector3df(0,0,0));

	//m_pOwner->GetAnimationMgr()->SetDefaultAni();

}