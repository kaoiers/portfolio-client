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
void Goal_ShortAttack::Activate()
{
	m_iStatus = active;	
}


/*======================================================*/
//  근거리 공격 도중관련 처리
/*======================================================*/
int Goal_ShortAttack::Process()
{
	//if status is inactive, call Activate()
	ActivateIfInactive();	
	
	if(!(m_pOwner->isInHitDistance(m_pOwner->getTarget()->Pos(), m_pOwner->getTarget()->getRadius() ))  )
	{
		m_iStatus = failed;
		return m_iStatus;
	}
	

	if(m_pOwner->short_attack(m_pOwner->getTarget()))
	{
		m_iStatus = completed;
		return m_iStatus;	
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

	return m_iStatus;

}

void Goal_ShortAttack::Terminate()
{
	//m_iStatus = completed;
}

Goal_ShortAttack::Goal_ShortAttack( CGameUnit* pUnit, CGameUnit* pTarget )
:Goal(pUnit, goal_short_attack) , m_pTarget(pTarget)
{
	

}

