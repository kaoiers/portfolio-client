//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/08/06
//
// File Name : Goal_FollowPath.cpp
//
// 복합 목적 : 길따라 움직이기
//
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "Goal_FollowPath.h"
#include "../objects/CGameUnit.h"
#include "Goal_SeekToPosition.h"
#include <utility>
#include <string>

Goal_FollowPath::
Goal_FollowPath(CGameUnit* p_unit, std::vector<vector3df> waypoints)
    : Goal_Composite<CGameUnit>(p_unit, goal_follow_path), m_waypoints(std::move(waypoints))
{
}

/*======================================================*/
// 그래프 길 따라가기 행동 초기화
/*======================================================*/
void Goal_FollowPath::activate()
{
    m_status = active;
    removeAllSubgoals();
    for (auto it = m_waypoints.rbegin(); it != m_waypoints.rend(); ++it)
        addSubgoal(std::make_unique<Goal_SeekToPosition>(m_owner, *it));
}

/*======================================================*/
// 그래프 길 따라가기 행동 처리
/*======================================================*/
s32 Goal_FollowPath::process()
{
    activateIfInactive();

    m_status = processSubgoals();

    if (m_status == completed || m_status == failed)
        stopSeeking();

    return m_status;
}

void Goal_FollowPath::terminate()
{
    removeAllSubgoals();
    stopSeeking();
}

/*======================================================*/
// 멈추기
/*======================================================*/
bool Goal_FollowPath::stopSeeking()
{
    m_owner->setVelocity(vector3df(0, 0, 0));

    return true;
}
