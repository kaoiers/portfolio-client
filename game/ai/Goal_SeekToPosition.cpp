//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/05/03
//
// File Name : Goal_SeekToPosition.cpp
// 
// 단일 목적 : 목적지점으로 이동하기
//
//////////////////////////////////////////////////////////////////////////


#include <stdafx.h>
#include "Goal_SeekToPosition.h"
#include "../objects/CGameUnit.h"



Goal_SeekToPosition::Goal_SeekToPosition( CGameUnit* pUnit, vector3df target )
:Goal<CGameUnit>(pUnit, goal_seek_to_position) , m_vPosition(target), m_dTimeToReachPos(0.0), m_pUpdateSendMovePacketRegulator(0)
{
	
}


/*======================================================*/
//  타겟 포지션으로 이동시키기 시작
/*======================================================*/
void Goal_SeekToPosition::Activate()
{
	m_iStatus = active;	

	//record the time the bot starts this goal
	m_dStartTime = 0;// Clock->GetCurrentTime();

	//This value is used to determine if the bot becomes stuck 	
	m_dTimeToReachPos = m_pOwner->CalculateTimeToReachPosition(m_vPosition);

	//factor in a margin of error for any reactive behavior
	const double MarginOfError = 1.0;

	m_dTimeToReachPos += MarginOfError;

	//m_pUpdateSendMovePacketRegulator->Initialize();
// 
// 	if(m_pOwner->getOwnerType() == object_mine)
// 	{	
// 		NetworkPacketSpace::SendUnitMovetoPositionPacket(m_pOwner->GetID(), m_pOwner->Pos());
// 	}


	
	
}
/*======================================================*/
//  도착 검사 처리
/*======================================================*/
s32 Goal_SeekToPosition::Process()
{
	//if status is inactive, call Activate()
	ActivateIfInactive();

	//test to see if the bot has become stuck
	if (isStuck())
	{
		m_iStatus = failed;
	}

	//test to see if the bot has reached the waypoint. If so terminate the goal
	else
	{ 
// 		if(m_pUpdateSendMovePacketRegulator->isReady() && m_pOwner->getOwnerType() == object_mine)
// 		{	
// 			NetworkPacketSpace::SendUnitMovetoPositionPacket(m_pOwner->GetID(), m_pOwner->Pos());
// 		}


		if (m_pOwner->isAtPosition(m_vPosition))
		{
			m_iStatus = completed;

// 			if(m_pOwner->getOwnerType() == object_mine)
// 				NetworkPacketSpace::SendUnitMovetoPositionPacket(m_pOwner->GetID(), m_vPosition);


			StopSeeking();


		}
	}

	return m_iStatus;
}


/*======================================================*/
// 종료
/*======================================================*/

void Goal_SeekToPosition::Terminate()
{

	m_pUpdateSendMovePacketRegulator = 0;

	m_iStatus = completed;

	



}


/*======================================================*/
//  목표지점으로 못가고 있을 때
/*======================================================*/
bool Goal_SeekToPosition::isStuck() const
{
	
	return false;
}


/*======================================================*/
//  멈추기
/*======================================================*/
bool Goal_SeekToPosition::StopSeeking()
{

	
	m_pOwner->SetVelocity(vector3df(0,0,0));

	


	return true;

}