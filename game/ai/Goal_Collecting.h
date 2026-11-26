//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/08/06
//
// File Name : Goal_Collecting.h
//
// 복합 목적 : 자원 채집 하기
//
//////////////////////////////////////////////////////////////////////////

#ifndef GOAL_COLLECTING_H
#define GOAL_COLLECTING_H

#pragma warning (disable:4786)

#include "Goal_Composite.h"

class CGameUnit;
class CGameUnitWorker;

/// 자원 채집에 필요한 이동 등 하위 목표를 관리한다.
class Goal_Collecting : public Goal_Composite<CGameUnit>
{
private:
    CGameUnitWorker* m_worker;

    //the position the bot wants to reach
    vector3df m_destination;

public:
    Goal_Collecting(CGameUnit* p_unit, vector3df pos):
    Goal_Composite<CGameUnit>(p_unit, goal_collecting),
    m_destination(pos)
    {}

    void activate() override;
    s32 process() override;
    void terminate() override;

    bool handleMessage(const Telegram& msg) override;

    void render();
};

#endif
