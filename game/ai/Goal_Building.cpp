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
void Goal_Building::activate()
{
	m_status = active;
	//make sure the subgoal list is clear.
	removeAllSubgoals();

	addSubgoal(new Goal_BuildingMotion(m_owner));

	addSubgoal(new Goal_MoveToPosition(m_owner, m_destination));
}


/*======================================================*/
//  건물 짓기 행동 처리
/*======================================================*/
s32 Goal_Building::process()
{
	activateIfInactive();

	m_status = processSubgoals();

	//if any of the subgoals have failed then this goal re-plans
	reactivateIfFailed();

	return m_status;
}

bool Goal_Building::handleMessage( const Telegram& msg )
{

	return true;

}

Goal_Building::Goal_Building( CGameUnit* p_unit, vector3df pos ) :  Goal_Composite<CGameUnit>(p_unit, goal_building), m_destination(pos)
{

}