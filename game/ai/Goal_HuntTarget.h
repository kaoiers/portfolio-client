//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/05/20
//
// File Name : Goal_HuntTarget.h
//
// 복합 목적 : 목표물 쫓아가기 (적군)
//
//////////////////////////////////////////////////////////////////////////

#ifndef GOAL_FIND_TARGET_H
#define GOAL_FIND_TARGET_H
#pragma warning (disable:4786)

#include "Goal_Composite.h"

class CGameUnit;
class CGameUnitEnemy;
class Regulator;

class Goal_HuntTarget : public Goal_Composite<CGameUnit>
{
private:
    //this value is set to true if the last visible position of the target
    //bot has been searched without success
    bool m_lvp_tried;
    CGameUnitEnemy* m_enemy_unit;
    CGameUnit* m_target;

public:
    Goal_HuntTarget(CGameUnit* p_bot):Goal_Composite<CGameUnit>(p_bot, goal_hunt_target),
    m_lvp_tried(false), m_target(nullptr)
    {}

    ~Goal_HuntTarget();

    void activate() override;
    s32 process() override;
    void terminate() override {}

    void render();
    void stopHunting();
};

#endif
