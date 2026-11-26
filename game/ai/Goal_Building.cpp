//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/06/05
//
// File Name : Goal_Building.cpp
// 
// 복합 목적 : 건설하기
//
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "Goal_Building.h"
#include "Goal_MoveToPosition.h"
#include "Goal_BuildingMotion.h"


/*======================================================*/
//  건물 짓기 행동 초기화
/*======================================================*/
void Goal_Building::Activate()
{
	m_iStatus = active;
	//make sure the subgoal list is clear.
	RemoveAllSubgoals();

	AddSubgoal(new Goal_BuildingMotion(m_pOwner));

	AddSubgoal(new Goal_MoveToPosition(m_pOwner, m_vDestination));
}


/*======================================================*/
//  건물 짓기 행동 처리
/*======================================================*/
s32 Goal_Building::Process()
{
	//if status is inactive, call Activate()
	ActivateIfInactive();

	//process the subgoals
	m_iStatus = ProcessSubgoals();

	//if any of the subgoals have failed then this goal re-plans
	ReactivateIfFailed();

	return m_iStatus;
}

bool Goal_Building::HandleMessage( const Telegram& msg )
{
	//bool bHandled = ForwardMessageToFrontMostSubgoal(msg);

	return true;

}

Goal_Building::Goal_Building( CGameUnit* pUnit, vector3df pos ) :  Goal_Composite<CGameUnit>(pUnit, goal_building), m_vDestination(pos)
{

}