//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/08/19
//
// File Name : Goal_MoveToPosition.h
//
// 복합 목적 : 이동
//
//////////////////////////////////////////////////////////////////////////

#ifndef GOAL_MOVE_POS_H
#define GOAL_MOVE_POS_H
#pragma warning (disable:4786)

#include "Goal_Composite.h"
#include "../navigation/AsyncPathfinder.h"

class CGameUnit;
class CGameMap;

/// 비동기 경로 요청을 기다리고 결과를 경유점 이동 목표로 연결한다.
class Goal_MoveToPosition : public Goal_Composite<CGameUnit>
{
private:
    //the position the bot wants to reach
    vector3df m_destination;
    CGameMap* m_map;
    std::future<AsyncPathResult> m_pending_path;
    std::uint64_t m_path_revision = 0;

public:
    Goal_MoveToPosition(CGameUnit* p_unit, vector3df pos, CGameMap* map = nullptr):
    Goal_Composite<CGameUnit>(p_unit, goal_move_to_position),
    m_destination(pos), m_map(map)
    {}

    void activate() override;
    s32 process() override;
    void terminate() override;

    bool handleMessage(const Telegram& msg) override;

    void render();
};

#endif
