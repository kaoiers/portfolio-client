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

class Goal_BuildingMotion : public Goal<CGameUnit>
{
private:
    CGameUnitWorker* m_worker;

public:
    Goal_BuildingMotion(CGameUnit* p_unit);

    void activate();
    s32 process();
    void terminate();
};

#endif
