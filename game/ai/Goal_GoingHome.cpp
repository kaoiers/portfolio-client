//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/05/08
//
// File Name : Goal_GOingHome.cpp
// 
// 복합 목적 : 집에 가기(적군)
//
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "Goal_GoingHome.h"
#include "Goal_MoveToPosition.h"
#include "Goal_Dead.h"
#include "../objects/CGameUnit.h"
#include "../objects/CGameUnitEnemy.h"
#include "../enemy_gen/CEnemyGenerator.h"
#include "../ai/Telegram.h"
#include "../ai/MessageDispatcher.h"
#include "../ai/God_Messages.h"
#include "../objects/CGameObjectManager.h"


/*======================================================*/
//  철수하기 행동 시작
/*======================================================*/
void Goal_GoingHome::Activate()
{
	m_iStatus = active;
	//make sure the subgoal list is clear.
	RemoveAllSubgoals();

	CGameUnitEnemy* pEnemy =  dynamic_cast<CGameUnitEnemy* >(m_pOwner);

	line3df l =  pEnemy->getEnemyGenerator()->getEnemyGenerateLine();

	l.start = l.start + vector3df(0,0,-100);
	l.end = l.end + vector3df(0,0,-100);

	
	vector3df vDes;// = l.getClosestPoint(pEnemy->Pos());

	AddSubgoal(new Goal_MoveToPosition(m_pOwner, vDes));
}



/*======================================================*/
//  철수하기 행동 처리
/*======================================================*/
int Goal_GoingHome::Process()
{
	//if status is inactive, call Activate()
	ActivateIfInactive();

	//process the subgoals
	m_iStatus = ProcessSubgoals();

	if(m_iStatus == completed)
	{
		//m_pOwner->SendMessageToAllObjects(0.0, m_pOwner->GetID(), Msg_UnitDead , this);

		m_pOwner->getObjectManager()->ClearMemoryFromObject( m_pOwner);

		Dispatcher->DispatchMsg(0.0, 1, m_pOwner->GetID(), Msg_YouDead, NULL);
	}

	//if any of the subgoals have failed then this goal re-plans
	ReactivateIfFailed();

	return m_iStatus;
}


/*======================================================*/
//  메시지 포워딩
/*======================================================*/
bool Goal_GoingHome::HandleMessage( const Telegram& msg )
{
	bool bHandled = ForwardMessageToFrontMostSubgoal(msg);

	return bHandled;
}