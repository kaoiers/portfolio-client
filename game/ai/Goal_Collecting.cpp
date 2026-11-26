//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/04/30
//
// File Name : Goal_Collecting.cpp
// 
// 복합 목적 : 자원 채집 하기
//
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>



#include "Goal_Collecting.h"
#include "Goal_MoveToPosition.h"
#include "../objects/CGameUnitWorker.h"


/*======================================================*/
// 자원채집 행동 초기화
/*======================================================*/
void Goal_Collecting::activate()
{

	m_worker = dynamic_cast<CGameUnitWorker* >(m_owner);


	m_status = active;
	//make sure the subgoal list is clear.
	removeAllSubgoals();

	addSubgoal(new Goal_MoveToPosition(m_owner, m_destination));


}


/*======================================================*/
// 자원채집 행동 처리
/*======================================================*/
s32 Goal_Collecting::process()
{
	//if status is inactive, call Activate()
	activateIfInactive();

	//process the subgoals
	m_status = processSubgoals();

	//if any of the subgoals have failed then this goal re-plans
	reactivateIfFailed();

	if( m_status== completed )
	{
		m_worker->collectingComplete();		
	}

	return m_status;
}



/*======================================================*/
// 메시지 처리하기
/*======================================================*/
bool Goal_Collecting::handleMessage( const Telegram& msg )
{
	bool b_handled = forwardMessageToFrontMostSubgoal(msg);

	return b_handled;

}

void Goal_Collecting::terminate()
{

}