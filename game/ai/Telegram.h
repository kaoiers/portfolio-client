//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/02/06
//
// File Name : Telegram.h
//
// 메시지 조합기
//
//////////////////////////////////////////////////////////////////////////

#ifndef TELEGRAM_H
#define TELEGRAM_H

#include "../../basicType.h"

#include <ostream>
#include <cmath>

struct Telegram
{
    //the entity that sent this telegram
    s32 sender;

    //the entity that is to receive this telegram
    s32 receiver;

    //the message itself. These are all enumerated in the file
    //"MessageTypes.h"
    s32 msg;

    //messages can be dispatched immediately or delayed for a specified amount
    //of time. If a delay is necessary this field is stamped with the time
    //the message should be dispatched.
    double dispatch_time;

    //any additional information that may accompany the message
    void* extra_info;

    Telegram():sender(-1),
    receiver(-1),
    msg(-1),
    dispatch_time(-1),
    extra_info(nullptr)
    {}

    Telegram(double time,
        s32 sender,
        s32 receiver,
        s32 msg,
        void* info = nullptr): sender(sender),
    receiver(receiver),
    msg(msg),
    dispatch_time(time),
    extra_info(info)
    {}
};

//these telegrams will be stored in a priority queue. Therefore the >
//operator needs to be overloaded so that the PQ can sort the telegrams
//by time priority. Note how the times must be smaller than
//SmallestDelay apart before two Telegrams are considered unique.
const double smallest_delay = 0.25;

inline bool operator==(const Telegram& t1, const Telegram& t2)
{
    return ( fabs(t1.dispatch_time-t2.dispatch_time) < smallest_delay) &&
    (t1.sender == t2.sender) &&
    (t1.receiver == t2.receiver) &&
    (t1.msg == t2.msg);
}

inline bool operator<(const Telegram& t1, const Telegram& t2)
{
    if (t1 == t2)
    {
        return false;
    }

    else
    {
        return (t1.dispatch_time < t2.dispatch_time);
    }
}

inline std::ostream& operator<<(std::ostream& os, const Telegram& t)
{
    os << "time: " << t.dispatch_time << "  Sender: " << t.sender
    << "   Receiver: " << t.receiver << "   Msg: " << t.msg;

    return os;
}

//handy helper function for dereferencing the ExtraInfo field of the Telegram
//to the required type.
template <class T>
inline T dereferenceToType(void* p)
{
    return *(T*)(p);
}

#endif
