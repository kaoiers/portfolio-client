//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/06/19
//
// File Name : Goal_UnitHuntTarget.cpp
// 
// 복합 목적 : 쫓아가기(적군)
//
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "Goal_UnitHuntTarget.h"

//#include "Goal_Explore.h"

#include "Goal_MoveToPosition.h"
#include "../objects/CGameUnit.h"
#include "../objects/CGameUnitEnemy.h"
#include "Goal_SeekToPosition.h"


/*======================================================*/
// 유닛 헌팅 행동 초기화
/*======================================================*/
void Goal_UnitHuntTarget::Activate()
{
	m_iStatus = active;

	//if this goal is reactivated then there may be some existing subgoals that
	//must be removed
	RemoveAllSubgoals();



	

	//if their is no active target then this goal can be removed from the queue

}



/*======================================================*/
// 유닛 헌팅 행동 초기화
/*======================================================*/
s32 Goal_UnitHuntTarget::Process()
{
	//if status is inactive, call Activate()
	ActivateIfInactive();

	
	// m_iStatus = ProcessSubgoals();

	if (m_pOwner->getTarget())
	{
		//if target is in view this goal is satisfied
		if(m_pOwner->isInHitDistance(m_pOwner->getTarget()->Pos(), m_pOwner->getTarget()->getRadius()))
		{
			RemoveAllSubgoals();
			StopHunting();
			m_iStatus = completed;
		}
		else
		{
		}


	}
	else
	{
		RemoveAllSubgoals();
		StopHunting();
		m_iStatus = completed;
	}

	return m_iStatus;

}


/*======================================================*/
// 이동 중당
/*======================================================*/
void Goal_UnitHuntTarget::StopHunting()
{
	
	m_pOwner->SetVelocity(vector3df(0,0,0));

}



Goal_UnitHuntTarget::~Goal_UnitHuntTarget()
{
	

}