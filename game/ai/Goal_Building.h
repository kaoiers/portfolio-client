//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/06/05
//
// File Name : Goal_Building.h
//
// 복합 목적 : 건설하기
//
//////////////////////////////////////////////////////////////////////////

#ifndef GOAL_BUILDING_H
#define GOAL_BUILDING_H

#pragma warning (disable:4786)

#include "Goal_Composite.h"

class CGameUnit;

/// 건설 행동의 이동과 작업 모션 목표를 조합한다.
class Goal_Building : public Goal_Composite<CGameUnit>
{
private:
    //the position the bot wants to reach
    vector3df m_destination;

public:
    Goal_Building(CGameUnit* p_unit, vector3df pos);

    void activate() override;
    s32 process() override;
    void terminate() override {}

    bool handleMessage(const Telegram& msg) override;

    void render();
};

#endif
