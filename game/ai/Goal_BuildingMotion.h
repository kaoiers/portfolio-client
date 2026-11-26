//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/03/08
//
// File Name : Goal_BuildingMotion.h
//
// 단일 목적 : 빌딩 모션 취하기
//
//////////////////////////////////////////////////////////////////////////

#ifndef GOAL_BUILDING_MOTION_H
#define GOAL_BUILDING_MOTION_H

#pragma warning (disable:4786)

#include "Goal.h"

class CGameUnit;
class CGameUnitWorker;

/// 건설 작업 중 모션에 대응하는 단일 목표이다.
class Goal_BuildingMotion : public Goal<CGameUnit>
{
private:
    CGameUnitWorker* m_worker;

public:
    Goal_BuildingMotion(CGameUnit* p_unit);

    void activate() override;
    s32 process() override;
    void terminate() override;
};

#endif
