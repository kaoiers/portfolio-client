//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/06/09
//
// File Name : Goal_ShortAttack.h
//
// 단일 목적 : 근거리 공격(아군)
//
//////////////////////////////////////////////////////////////////////////

#ifndef GOAL_SHORT_ATTACK_H
#define GOAL_SHORT_ATTACK_H

#pragma warning (disable:4786)

#include "Goal.h"

class CGameUnit;

class Goal_ShortAttack : public Goal<CGameUnit>
{
private:
    CGameUnit* m_target;

public:
    Goal_ShortAttack(CGameUnit* p_unit, CGameUnit* p_target);

    void activate() override;
    s32 process() override;
    void terminate() override;
};

#endif
