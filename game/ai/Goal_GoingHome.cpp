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
#include "Telegram.h"
#include "MessageDispatcher.h"
#include "God_Messages.h"
#include "../objects/CGameObjectManager.h"

/*======================================================*/
//  철수하기 행동 시작
/*======================================================*/
void Goal_GoingHome::activate()
{
    m_status = active;
    //make sure the subgoal list is clear.
    removeAllSubgoals();

    CGameUnitEnemy* p_enemy = dynamic_cast<CGameUnitEnemy* >(m_owner);

    line3df l = p_enemy->getEnemyGenerator()->getEnemyGenerateLine();

    l.start = l.start + vector3df(0, 0, -100);
    l.end = l.end + vector3df(0, 0, -100);

    vector3df v_des;// = l.getClosestPoint(pEnemy->Pos());

    addSubgoal(std::make_unique<Goal_MoveToPosition>(m_owner, v_des));
}

/*======================================================*/
//  철수하기 행동 처리
/*======================================================*/
s32 Goal_GoingHome::process()
{
    activateIfInactive();

    m_status = processSubgoals();

    if (m_status == completed)
    {
        m_owner->getObjectManager()->clearMemoryFromObject( m_owner);

        Dispatcher->dispatchMsg(0.0, 1, m_owner->getId(), Msg_YouDead, nullptr);
    }

    //if any of the subgoals have failed then this goal re-plans
    reactivateIfFailed();

    return m_status;
}

/*======================================================*/
//  메시지 포워딩
/*======================================================*/
bool Goal_GoingHome::handleMessage( const Telegram& msg)
{
    bool b_handled = forwardMessageToFrontMostSubgoal(msg);

    return b_handled;
}
