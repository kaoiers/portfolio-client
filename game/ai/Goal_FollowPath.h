//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/08/06
//
// File Name : Goal_FollowPath.h
//
// 복합 목적 : 길따라 움직이기
//
//////////////////////////////////////////////////////////////////////////

#ifndef GOAL_FOLLOWPATH_H
#define GOAL_FOLLOWPATH_H
#pragma warning (disable:4786)

#include "Goal_Composite.h"
#include <vector>

class CGameUnit;

/// 경유점을 순서대로 실행할 이동 하위 목표로 구성한다.
class Goal_FollowPath : public Goal_Composite<CGameUnit>
{
private:
    std::vector<vector3df> m_waypoints;
public:
    Goal_FollowPath(CGameUnit* p_unit, std::vector<vector3df> waypoints);

    void activate() override;
    s32 process() override;
    void render();
    void terminate() override;

    bool stopSeeking();
};

#endif
