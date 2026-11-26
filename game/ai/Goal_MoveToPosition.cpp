//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/08/19
//
// File Name : Goal_MoveToPosition.cpp
//
// 복합 목적 : 이동
//
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "Goal_MoveToPosition.h"
#include "../objects/CGameUnit.h"

#include "Telegram.h"
#include "God_Messages.h"
#include "Goal_SeekToPosition.h"
#include "Goal_FollowPath.h"
#include "../map/CGameMap.h"
#include <chrono>
#include <utility>

/*======================================================*/
// 이동하기 행동 초기화
/*======================================================*/
void Goal_MoveToPosition::activate()
{
    removeAllSubgoals();
    if (!m_map) m_map = CGameMap::getInstance();
    if (!m_map)
    {
        m_status = failed;
        return;
    }

    auto start = m_map->getTileFromPos(m_owner->getPos());
    auto end = m_map->getTileFromPos(m_destination);
    try
    {
        m_pending_path = m_map->requestPathAsync({start.X, start.Y}, {end.X, end.Y});
        m_path_revision = m_map->getNavigationRevision();
        m_status = active;
    }
    catch (const std::exception&)
    {
        m_status = failed;
    }
}

s32 Goal_MoveToPosition::process()
{
    activateIfInactive();
    if (m_status != active) return m_status;

    // A changed obstacle map invalidates both pending and accepted paths.
    if (!m_pending_path.valid() && m_map->getNavigationRevision() != m_path_revision)
    {
        activate();
        return m_status;
    }
    if (m_pending_path.valid())
    {
        if (m_pending_path.wait_for(std::chrono::seconds(0)) != std::future_status::ready)
            return active;
        AsyncPathResult result{};
        try { result = m_pending_path.get(); }
        catch (const std::exception&) { m_status = failed; return m_status; }
        if (result.revision != m_map->getNavigationRevision())
        {
            activate();
            return m_status;
        }
        if (result.path.status != PathStatus::Found)
        {
            m_status = failed;
            return m_status;
        }

        std::vector<vector3df> waypoints;
        for (std::size_t i = 1; i < result.path.points.size(); ++i)
        {
            const auto point = result.path.points[i];
            waypoints.push_back(m_map->getPosByTile(point.x, point.y));
        }
        // Keep the requested location as the final waypoint, not just its tile center.
        if (waypoints.empty() || (waypoints.back() - m_destination).getLengthSquared() > 0.0f)
            waypoints.push_back(m_destination);
        addSubgoal(std::make_unique<Goal_FollowPath>(m_owner, std::move(waypoints)));
    }

    m_status = processSubgoals();
    return m_status;
}

bool Goal_MoveToPosition::handleMessage(const Telegram& msg)
{
    return forwardMessageToFrontMostSubgoal(msg);
}

/*======================================================*/
// 길 렌더링
/*======================================================*/
void Goal_MoveToPosition::render()
{
    //   //forward the request to the subgoals
    //   Goal_Composite<Raven_Bot>::Render();
    //
    //   //draw a bullseye
}

void Goal_MoveToPosition::terminate()
{
    m_pending_path = {}; // packaged-task futures do not block on destruction
    removeAllSubgoals();
    m_status = completed;
}
