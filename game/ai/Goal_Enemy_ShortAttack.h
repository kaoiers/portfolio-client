//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/05/19
//
// File Name : Goal_ShortAttack.h
//
// 단일 목적 : 근거리 공격하기
//
//////////////////////////////////////////////////////////////////////////

#ifndef GOAL_ENEMY_SHORT_ATTACK_H
#define GOAL_ENEMY_SHORT_ATTACK_H

#pragma warning (disable:4786)

#include "Goal.h"

class CGameUnit;
class CGameUnitEnemy;

/// 적 유닛의 근거리 공격 목표 상태를 표현한다.
class Goal_Enemy_ShortAttack : public Goal<CGameUnit>
{
private:
    CGameUnitEnemy* m_enemy;

    CGameUnit* m_target;

public:
    Goal_Enemy_ShortAttack(CGameUnitEnemy* p_unit, CGameUnit* p_target);

    void activate() override;
    s32 process() override;
    void terminate() override;
};

#endif
