//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/04/11
//
// File Name : Goal_Think.h
//
// 인공지능 클래스
//
//////////////////////////////////////////////////////////////////////////

#ifndef GOAL_THINK_H
#define GOAL_THINK_H
#pragma warning (disable:4786)

#include "Goal_Composite.h"

class CGameUnit;

class Goal_Think : public Goal_Composite<CGameUnit >
{
public:
    Goal_Think(CGameUnit* p_unit);
    ~Goal_Think();

    void arbitrate();
    void enemyInit();
    void armyInit();

    bool notPresent(u32 goal_type) const;

    s32 process();
    void activate();
    void terminate() {}

    void removeSubGoals();

    //top level goal types
    void addGoalMoveToPosition(vector3df pos);
    void addGoalGetItem(u32 item_type);
    void addGoalExplore();
    void addGoalDie();
    void addGoalBuilding(const vector3df& pos);
    void addGoalCollecting(const vector3df& pos);
    void addGoalHuntTarget();
    void addGoalUnitHuntTarget();
    void addGoalAttackTargetForEnemy();
    void addGoalGoingHome();
    void addGoalAttackTarget();
    void queueGoalMoveToPosition(vector3df pos);
};

#endif
