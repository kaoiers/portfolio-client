//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/06/02
//
// File Name : Goal_AttackTarget.h
//
// 복합 목적 : 공격하기
//
//////////////////////////////////////////////////////////////////////////

#ifndef GOAL_ATTACKTARGET_H
#define GOAL_ATTACKTARGET_H
#pragma warning (disable:4786)

#include "Goal_Composite.h"

class CGameUnit;
class CGameUnitEnemy;
class Regulator;

/// 대상 공격을 위한 하위 목표를 조합하는 복합 AI 목표이다.
class Goal_AttackTarget : public Goal_Composite<CGameUnit>
{
    Regulator* m_attack_regulator;

    bool m_is_enemy;

public:
    Goal_AttackTarget(CGameUnit* p_owner);

    void activate() override;

    s32 process() override;
    void terminate() override;
    bool notPresent(u32 goal_type) const;
};

#endif
