//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/05/03
//
// File Name : Goal_SeekToPosition.h
//
// 단일 목적 : 목적지점으로 이동하기
//
//////////////////////////////////////////////////////////////////////////

#ifndef GOAL_SEEK_TO_POSITION_H
#define GOAL_SEEK_TO_POSITION_H

#pragma warning (disable:4786)

#include "Goal.h"

class CGameUnit;
class Regulator;

class Goal_SeekToPosition : public Goal<CGameUnit>
{
private:
    //the position the bot is moving to
    vector3df m_position;

    //the approximate time the bot should take to travel the target location
    double m_time_to_reach_pos;

    //this records the time this goal was activated
    double m_start_time;

    Regulator* m_update_send_move_packet_regulator;

    //returns true if a bot gets stuck
    bool isStuck() const;

    bool stopSeeking();

public:
    Goal_SeekToPosition(CGameUnit* p_unit, vector3df target);

    void activate() override;
    s32 process() override;
    void terminate() override;
};

#endif
