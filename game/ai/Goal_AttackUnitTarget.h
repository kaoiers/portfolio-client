//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/05/04
//
// File Name : Goal_AttackTarget.h
//
// 복합 목적 : 공격하기
//
//////////////////////////////////////////////////////////////////////////

#ifndef GOAL_ATTACKUNITTARGET_H
#define GOAL_ATTACKUNITTARGET_H
#pragma warning (disable:4786)

#include "Goal_Composite.h"

class CGameUnit;
class CGameUnitEnemy;
class Regulator;

class Goal_AttackUnitTarget : public Goal_Composite<CGameUnit>
{
    Regulator* m_attack_regulator;

    bool m_is_enemy;

    CGameUnitEnemy* m_enemy;
    CGameUnit* m_target;

public:
    Goal_AttackUnitTarget(CGameUnit* p_owner);
    ~Goal_AttackUnitTarget()
    {
    };

    void activate();

    void activateForUnit(CGameUnit* p_unit);
    s32 process();
    void terminate();
    bool notPresent(u32 goal_type) const;
    void stopHunting();
};

#endif
