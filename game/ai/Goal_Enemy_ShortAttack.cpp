//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/05/19
//
// File Name : Goal_ShortAttack.cpp
//
// 단일 목적 : 근거리 공격하기
//
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "Goal_Enemy_ShortAttack.h"
#include "../objects/CGameUnitEnemy.h"
#include "Goal_SeekToPosition.h"
#include "Goal_ShortAttack.h"
#include "../objects/CGameRoom.h"
#include "../objects/CGameUnit.h"

Goal_Enemy_ShortAttack::Goal_Enemy_ShortAttack( CGameUnitEnemy* p_unit, CGameUnit* p_target)
    :Goal(p_unit, goal_enemy_short_attack), m_enemy(p_unit), m_target(p_target)
{
}
/*======================================================*/
//  프로세스 진입
/*======================================================*/
void Goal_Enemy_ShortAttack::activate()
{
    m_status = active;
}

/*======================================================*/
//  프로세스 시작
/*======================================================*/
s32 Goal_Enemy_ShortAttack::process()
{
    activateIfInactive();

    return m_status;
}

void Goal_Enemy_ShortAttack::terminate()
{
}
