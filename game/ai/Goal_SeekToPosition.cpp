//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/05/03
//
// File Name : Goal_SeekToPosition.cpp
//
// 단일 목적 : 목적지점으로 이동하기
//
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "Goal_SeekToPosition.h"
#include "../objects/CGameUnit.h"

Goal_SeekToPosition::Goal_SeekToPosition( CGameUnit* p_unit, vector3df target)
    :Goal<CGameUnit>(p_unit, goal_seek_to_position), m_position(target), m_time_to_reach_pos(0.0), m_update_send_move_packet_regulator(0)
{
}

/*======================================================*/
//  타겟 포지션으로 이동시키기 시작
/*======================================================*/
void Goal_SeekToPosition::activate()
{
    m_status = active;

    //record the time the bot starts this goal
    m_start_time = 0;// Clock->GetCurrentTime();

    //This value is used to determine if the bot becomes stuck
    m_time_to_reach_pos = m_owner->calculateTimeToReachPosition(m_position);

    //factor in a margin of error for any reactive behavior
    const double margin_of_error = 1.0;

    m_time_to_reach_pos += margin_of_error;

    //
}
/*======================================================*/
//  도착 검사 처리
/*======================================================*/
s32 Goal_SeekToPosition::process()
{
    activateIfInactive();

    //test to see if the bot has become stuck
    if (isStuck())
    {
        m_status = failed;
    }

    //test to see if the bot has reached the waypoint. If so terminate the goal
    else
    {
        if (m_owner->isAtPosition(m_position))
        {
            m_status = completed;

            stopSeeking();
        }
    }

    return m_status;
}

/*======================================================*/
// 종료
/*======================================================*/

void Goal_SeekToPosition::terminate()
{
    m_update_send_move_packet_regulator = 0;

    m_status = completed;
}

/*======================================================*/
//  목표지점으로 못가고 있을 때
/*======================================================*/
bool Goal_SeekToPosition::isStuck() const
{
    return false;
}

/*======================================================*/
//  멈추기
/*======================================================*/
bool Goal_SeekToPosition::stopSeeking()
{
    m_owner->setVelocity(vector3df(0, 0, 0));

    return true;
}
