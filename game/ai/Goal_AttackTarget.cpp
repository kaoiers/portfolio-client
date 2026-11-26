//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/06/02
//
// File Name : Goal_AttackTarget.cpp
// 
// 복합 목적 : 공격하기
//
//////////////////////////////////////////////////////////////////////////


#include <stdafx.h>
#include "Goal_AttackTarget.h"
#include "Goal_SeekToPosition.h"
#include "Goal_ShortAttack.h"
#include "Goal_Enemy_ShortAttack.h"
#include "Goal_MoveToPosition.h"

#include "../objects/CGameUnitEnemy.h"


#include "../objects/CGameUnit.h"




/*======================================================*/
//  타겟 공격 행동 초기화
/*======================================================*/
void Goal_AttackTarget::Activate()
{
	m_iStatus = completed;


}


/*======================================================*/
//  타겟 공격 행동 처리
/*======================================================*/
int Goal_AttackTarget::Process()
{
	ActivateIfInactive();

	m_iStatus = ProcessSubgoals();

	ReactivateIfFailed();


	return m_iStatus;
}

/*======================================================*/
//  자식 목표있는지 검사
/*======================================================*/
bool Goal_AttackTarget::notPresent(unsigned int GoalType)const
{
	if (!m_SubGoals.empty())
	{
		return m_SubGoals.front()->GetType() != GoalType;
	}

	return true;
}




void Goal_AttackTarget::Terminate()
{
	m_iStatus = completed;

}

Goal_AttackTarget::Goal_AttackTarget( CGameUnit* pOwner ):Goal_Composite<CGameUnit>(pOwner, goal_attack_target)
{
	
}