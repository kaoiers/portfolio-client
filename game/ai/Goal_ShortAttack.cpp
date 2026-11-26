//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/06/09
//
// File Name : Goal_ShortAttack.cpp
// 
// 단일 목적 : 근거리 공격(아군)
//
//////////////////////////////////////////////////////////////////////////


#include <stdafx.h>
#include "Goal_ShortAttack.h"
#include "../objects/CGameUnit.h"



/*======================================================*/
// 근거리 공격 시작
/*======================================================*/
void Goal_ShortAttack::activate()
{
	m_status = active;	
}


/*======================================================*/
//  근거리 공격 도중관련 처리
/*======================================================*/
s32 Goal_ShortAttack::process()
{
	//if status is inactive, call Activate()
	activateIfInactive();	
	
	if(!(m_owner->isInHitDistance(m_owner->getTarget()->getPos(), m_owner->getTarget()->getRadius() ))  )
	{
		m_status = failed;
		return m_status;
	}
	

	if(m_owner->shortAttack(m_owner->getTarget()))
	{
		m_status = completed;
		return m_status;	
	}

// 	//test to see if the bot has become stuck
// 	if (isStuck())
// 	{
// 		m_iStatus = failed;
// 	}

	//test to see if the bot has reached the waypoint. If so terminate the goal
// 	else
// 	{ 
// 		if (m_pOwner->isAtPosition(m_vPosition))
// 		{
 			//m_iStatus = inactive;
// 		}
// 	}

	return m_status;

}

void Goal_ShortAttack::terminate()
{
	//m_iStatus = completed;
}

Goal_ShortAttack::Goal_ShortAttack( CGameUnit* p_unit, CGameUnit* p_target )
:Goal(p_unit, goal_short_attack) , m_target(p_target)
{
	

}

