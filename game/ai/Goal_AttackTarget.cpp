//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/06/02
//
// File Name : Goal_AttackTarget.cpp
//
// 복합 목적 : 공격하기
//
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "Goal_AttackTarget.h"
#include "Goal_SeekToPosition.h"
#include "Goal_ShortAttack.h"
#include "Goal_Enemy_ShortAttack.h"
#include "Goal_MoveToPosition.h"

#include "../objects/CGameUnitEnemy.h"

#include "../objects/CGameUnit.h"

/*======================================================*/
//  타겟 공격 행동 초기화
/*======================================================*/
void Goal_AttackTarget::activate()
{
    m_status = completed;
}

/*======================================================*/
//  타겟 공격 행동 처리
/*======================================================*/
s32 Goal_AttackTarget::process()
{
    activateIfInactive();

    m_status = processSubgoals();

    reactivateIfFailed();

    return m_status;
}

/*======================================================*/
//  자식 목표있는지 검사
/*======================================================*/
bool Goal_AttackTarget::notPresent(u32 goal_type) const
{
    if (!m_sub_goals.empty())
    {
        return m_sub_goals.front()->getType() != goal_type;
    }

    return true;
}

void Goal_AttackTarget::terminate()
{
    m_status = completed;
}

Goal_AttackTarget::Goal_AttackTarget( CGameUnit* p_owner):Goal_Composite<CGameUnit>(p_owner, goal_attack_target)
{
}
