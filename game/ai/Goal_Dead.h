//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/05/25
//
// File Name : Goal_Dead.h
//
// 단일 목적 : 유닛 죽기
//
//////////////////////////////////////////////////////////////////////////

#ifndef GOAL_DEAD_H
#define GOAL_DEAD_H

#pragma warning (disable:4786)

#include "Goal.h"

class CGameUnit;

/// 유닛 사망 시 처리하는 단일 목표이다.
class Goal_Dead : public Goal<CGameUnit>
{
private:
public:
    Goal_Dead(CGameUnit* p_unit);

    void activate() override;
    s32 process() override;
    void terminate() override;
};

#endif
