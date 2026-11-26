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


#include "Goal_MoveToPosition.h"
#include "../objects/CGameUnit.h"
#include "../objects/CGameUnitEnemy.h"
#include "Goal_SeekToPosition.h"


/*======================================================*/
// 유닛 헌팅 행동 초기화
/*======================================================*/
void Goal_UnitHuntTarget::activate()
{
	m_status = active;

	//if this goal is reactivated then there may be some existing subgoals that
	//must be removed
	removeAllSubgoals();



	

	//if their is no active target then this goal can be removed from the queue

}



/*======================================================*/
// 유닛 헌팅 행동 초기화
/*======================================================*/
s32 Goal_UnitHuntTarget::process()
{
	activateIfInactive();

	

	if (m_owner->getTarget())
	{
		//if target is in view this goal is satisfied
		if(m_owner->isInHitDistance(m_owner->getTarget()->getPos(), m_owner->getTarget()->getRadius()))
		{
			removeAllSubgoals();
			stopHunting();
			m_status = completed;
		}
		else
		{
		}


	}
	else
	{
		removeAllSubgoals();
		stopHunting();
		m_status = completed;
	}

	return m_status;

}


/*======================================================*/
// 이동 중당
/*======================================================*/
void Goal_UnitHuntTarget::stopHunting()
{
	
	m_owner->setVelocity(vector3df(0,0,0));

}



Goal_UnitHuntTarget::~Goal_UnitHuntTarget()
{
	

}