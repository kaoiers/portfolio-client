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
#include <tuple>

/// 송신자, 수신자, 메시지 종류, 전달 시간과 비소유 부가 데이터를 표현한다.
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

// Compare message identity fields exactly. Scheduling uses its own time-keyed queue.
inline bool operator==(const Telegram& lhs, const Telegram& rhs)
{
    return std::tie(lhs.dispatch_time, lhs.sender, lhs.receiver, lhs.msg) ==
        std::tie(rhs.dispatch_time, rhs.sender, rhs.receiver, rhs.msg);
}

inline bool operator<(const Telegram& lhs, const Telegram& rhs)
{
    return std::tie(lhs.dispatch_time, lhs.sender, lhs.receiver, lhs.msg) <
        std::tie(rhs.dispatch_time, rhs.sender, rhs.receiver, rhs.msg);
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
