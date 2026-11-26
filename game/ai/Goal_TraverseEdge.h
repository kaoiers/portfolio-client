//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/06/21
//
// File Name : Goal_TraverseEdge.h
//
// 단일 목적 : Edge 이동
//
//////////////////////////////////////////////////////////////////////////

#ifndef GOAL_TRAVERSE_EDGE_H
#define GOAL_TRAVERSE_EDGE_H
#pragma warning (disable:4786)

#include "Goal.h"

class CGameUnit;
class Regulator;

/// 경로의 개별 간선에 해당하는 이동 목표를 표현한다.
class Goal_TraverseEdge : public Goal<CGameUnit>
{
private:
    //true if m_Edge is the last in the path.
    bool m_last_edge_in_path;

    //the estimated time the bot should take to traverse the edge
    double m_time_expected;

    //this records the time this goal was activated
    double m_start_time;

    Regulator* m_update_send_move_packet_regulator;

    //returns true if the bot gets stuck
    bool isStuck() const;

public:
    Goal_TraverseEdge(CGameUnit* p_unit,
        bool last_edge);

    void activate() override;
    s32 process() override;
    void terminate() override;
};

#endif
