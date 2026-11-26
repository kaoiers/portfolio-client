//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/08/19
//
// File Name : Goal_MoveToPosition.h
//
// 복합 목적 : 이동
//
//////////////////////////////////////////////////////////////////////////

#ifndef GOAL_MOVE_POS_H
#define GOAL_MOVE_POS_H
#pragma warning (disable:4786)

#include "Goal_Composite.h"

class CGameUnit;

class Goal_MoveToPosition : public Goal_Composite<CGameUnit>
{
private:
    //the position the bot wants to reach
    vector3df m_destination;

public:
    Goal_MoveToPosition(CGameUnit* p_unit, vector3df pos):
    Goal_Composite<CGameUnit>(p_unit, goal_move_to_position),
    m_destination(pos)
    {}

    void activate();
    s32 process();
    void terminate();

    bool handleMessage(const Telegram& msg);

    void render();
};

#endif
