//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/04/11
//
// File Name : Goal_Think.h
//
// 인공지능 클래스
//
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "Goal_Think.h"
#include <list>
#include "../objects/CGameUnit.h"
#include "Goal_MoveToPosition.h"
#include "Goal_ShortAttack.h"
#include "Goal_AttackTarget.h"
#include "Goal_Dead.h"
#include "Goal_Building.h"
#include "Goal_Collecting.h"
#include "Goal_HuntTarget.h"
#include "Goal_UnitHuntTarget.h"
#include "Goal_GoingHome.h"
#include "Goal_AttackUnitTarget.h"
#include "../map/CGameMap.h"
#include "../interfaces/CMainGameGUI.h"

Goal_Think::Goal_Think(CGameUnit* p_unit):Goal_Composite<CGameUnit>(p_unit, goal_think)
{
    const double low_range_of_bias = 0.5;
    const double high_range_of_bias = 1.5;
}

Goal_Think::~Goal_Think()
{
    removeAllSubgoals();
}

/*======================================================*/
// 유닛 군사용 목표 평가기 추가
/*======================================================*/
void Goal_Think::armyInit()
{
    double attack_bias = 1.0;
}

/*======================================================*/
// 적군용 목표 평가기 추가
/*======================================================*/
void Goal_Think::enemyInit()
{
    double attack_bias = 1.0;
}

/*======================================================*/
// 초기화
/*======================================================*/
void Goal_Think::activate()
{
    if (!m_owner->isPossessed())
    {
    }

    m_status = active;
}

/*======================================================*/
// 처리하기
/*======================================================*/
s32 Goal_Think::process()
{
    activateIfInactive();

    s32 subgoal_status = processSubgoals();

    reactivateIfFailed();

    return m_status;
}

/*======================================================*/
// 목표 중재기
/*======================================================*/
void Goal_Think::arbitrate()
{
    double best = 0;

    if (!(m_owner->isAlive()))
    {
        return;
    }

    if (!notPresent(goal_move_to_position) && m_owner->getUnitType() != UNIT_ENEMY_SOLDIER)
    {
        return;
    }
}

/*======================================================*/
// 하위 목표 실행 확인
/*======================================================*/
bool Goal_Think::notPresent(u32 goal_type) const
{
    if (!m_sub_goals.empty())
    {
        return m_sub_goals.front()->getType() != goal_type;
    }

    return true;
}

/*======================================================*/
// 하위 목표로 이동하기 추가
/*======================================================*/
void Goal_Think::addGoalMoveToPosition(vector3df pos)
{
    s32 idx = -1;

    CGameMap* p_map = CGameMap::getInstance();

    vector3df br = p_map->getBottomRightUsablePos();
    vector3df tl = p_map->getTopLeftUsablePos();

    if (m_owner->getAllyType() == unit_mine)
    {
        if (pos.Z >= tl.Z || pos.Z <= br.Z || pos.X <= tl.X || pos.X >= br.X)
        {
            return;
        }
    }

    if (CGameMap::getInstance()->isInBoundaries(pos, idx))
    {
        if ((CGameMap::getInstance()->isWalkableWall(idx)))
        {
            removeAllSubgoals();
            addSubgoal( new Goal_MoveToPosition(m_owner, pos));

            return;
        }

    }
    else
    {
        removeAllSubgoals();
        addSubgoal( new Goal_MoveToPosition(m_owner, pos));
    }
}

/*======================================================*/
// 하위 목표로 탐험하기 추가
/*======================================================*/
void Goal_Think::addGoalExplore()
{
    if (notPresent(goal_explore))
    {
        removeAllSubgoals();
    }
}

void Goal_Think::addGoalGetItem(u32 item_type)
{
}

/*======================================================*/
// 하위 목표로 공격하기 추가
/*======================================================*/
void Goal_Think::addGoalAttackTarget()
{
    if (notPresent(goal_attack_target))
    {
        removeAllSubgoals();
        addSubgoal( new Goal_AttackTarget(m_owner));
    }
}

void Goal_Think::queueGoalMoveToPosition(vector3df pos)
{
}

/*======================================================*/
// 하위 목표로 죽기 추가
/*======================================================*/
void Goal_Think::addGoalDie()
{
    removeAllSubgoals();
    addSubgoal( new Goal_Dead(m_owner));
}

/*======================================================*/
// 하위 목표로 수집하기 추가
/*======================================================*/
void Goal_Think::addGoalCollecting( const vector3df& pos)
{
    removeAllSubgoals();

    addSubgoal(new Goal_Collecting(m_owner, pos));
}

/*======================================================*/
// 하위 목표로 건설하기 추가
/*======================================================*/
void Goal_Think::addGoalBuilding( const vector3df& pos)
{
    removeAllSubgoals();

    addSubgoal(new Goal_Building(m_owner, pos));
}

/*======================================================*/
// 하위 목표들 모두 지우기
/*======================================================*/
void Goal_Think::removeSubGoals()
{
    removeAllSubgoals();
}

/*======================================================*/
// 하위 목표로 헌팅하기 추가
/*======================================================*/
void Goal_Think::addGoalHuntTarget()
{
    if (notPresent(goal_hunt_target))
    {
        removeAllSubgoals();
        addSubgoal(new Goal_HuntTarget(m_owner));
    }
}

/*======================================================*/
// 하위 목표로 철수하기 추가
/*======================================================*/
void Goal_Think::addGoalGoingHome()
{
    if (notPresent(goal_goinghome))
    {
        removeAllSubgoals();
        addSubgoal(new Goal_GoingHome(m_owner));
    }
}

/*======================================================*/
// 하위 목표로 유닛 헌팅 추가
/*======================================================*/
void Goal_Think::addGoalUnitHuntTarget()
{
    if (notPresent(goal_unithunt_target))
    {
        removeAllSubgoals();
        addSubgoal(new Goal_UnitHuntTarget(m_owner));
    }
}

/*======================================================*/
// 하위 목표로 아군 공격하기 추가
/*======================================================*/
void Goal_Think::addGoalAttackTargetForEnemy()
{
    if (notPresent(goal_attack_target))
    {
        removeAllSubgoals();
        addSubgoal( new Goal_AttackUnitTarget(m_owner));
    }
}
