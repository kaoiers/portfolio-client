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



	m_status = completed;


}




//-------------------------- Process ------------------------------------------
//-----------------------------------------------------------------------------
s32 Goal_AttackUnitTarget::process()
{
	activateIfInactive();

	m_status = processSubgoals();




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
}

void Goal_AttackUnitTarget::stopHunting()
{

	


}