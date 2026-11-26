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
void Goal_Collecting::Activate()
{

	m_pWorker = dynamic_cast<CGameUnitWorker* >(m_pOwner);


	m_iStatus = active;
	//make sure the subgoal list is clear.
	RemoveAllSubgoals();

	AddSubgoal(new Goal_MoveToPosition(m_pOwner, m_vDestination));


}


/*======================================================*/
// 자원채집 행동 처리
/*======================================================*/
int Goal_Collecting::Process()
{
	//if status is inactive, call Activate()
	ActivateIfInactive();

	//process the subgoals
	m_iStatus = ProcessSubgoals();

	//if any of the subgoals have failed then this goal re-plans
	ReactivateIfFailed();

	if( m_iStatus== completed )
	{
		m_pWorker->CollectingComplete();		
	}

	return m_iStatus;
}



/*======================================================*/
// 메시지 처리하기
/*======================================================*/
bool Goal_Collecting::HandleMessage( const Telegram& msg )
{
	bool bHandled = ForwardMessageToFrontMostSubgoal(msg);

	return bHandled;

}

void Goal_Collecting::Terminate()
{

}