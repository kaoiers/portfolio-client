//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/06/19
//
// File Name : Goal_UnitHuntTarget.h
//
// 복합 목적 : 쫓아가기(적군)
//
//////////////////////////////////////////////////////////////////////////

#ifndef GOAL_HUNT_TARGET_H
#define GOAL_HUNT_TARGET_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   Goal_HuntTarget.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   Causes a bot to search for its current target. Exits when target
//          is in view
//-----------------------------------------------------------------------------
#include "Goal_Composite.h"

class CGameUnit;
class Regulator;

class Goal_UnitHuntTarget : public Goal_Composite<CGameUnit>
{
private:
    //this value is set to true if the last visible position of the target
    //bot has been searched without success
    bool m_lvp_tried;
    CGameUnit* m_target;

public:
    Goal_UnitHuntTarget(CGameUnit* p_bot):Goal_Composite<CGameUnit>(p_bot, goal_unithunt_target),
    m_lvp_tried(false), m_target(NULL)
    {}

    ~Goal_UnitHuntTarget();

    void activate();
    s32 process();
    void terminate() {}

    void render();
    void stopHunting();
};

#endif
