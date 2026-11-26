//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/05/08
//
// File Name : Goal_GOingHome.h
//
// 복합 목적 : 집에 가기
//
//////////////////////////////////////////////////////////////////////////

#ifndef GOAL_GOINGHOME_H
#define GOAL_GOINGHOME_H

#pragma warning (disable:4786)

#include "Goal_Composite.h"

class CGameUnit;

/// 복귀 목적지로 이동하는 하위 목표와 복귀 완료 처리를 관리한다.
class Goal_GoingHome : public Goal_Composite<CGameUnit>
{
private:
public:
    Goal_GoingHome(CGameUnit* p_unit):
    Goal_Composite<CGameUnit>(p_unit, goal_goinghome) {}

    void activate() override;
    s32 process() override;
    void terminate() override {}

    bool handleMessage(const Telegram& msg) override;

    void render();
};

#endif
