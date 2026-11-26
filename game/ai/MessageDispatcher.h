//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/02/15
//
// File Name : MessageDispatcher.h
//
// 메시지 전달기
//
//////////////////////////////////////////////////////////////////////////

#ifndef MESSAGE_DISPATCHER_H
#define MESSAGE_DISPATCHER_H

#include <map>
#include "Telegram.h"

class CGameObjectManager;

inline constexpr double SEND_MSG_IMMEDIATELY = 0.0;
inline constexpr s32 NO_ADDITIONAL_INFO = 0;
inline constexpr s32 SENDER_ID_IRRELEVANT = -1;

// One dispatcher per object manager. Delay is in seconds; frame updates are in milliseconds.
/// 관리자별 즉시 메시지 및 시간 순서가 보장되는 지연 메시지를 전달한다.
class MessageDispatcher
{
public:
    explicit MessageDispatcher(CGameObjectManager& manager);
    MessageDispatcher(const MessageDispatcher&) = delete;
    MessageDispatcher& operator=(const MessageDispatcher&) = delete;

    // Payloads are borrowed during immediate delivery only.
    bool dispatchMsg(double delay, s32 sender, s32 receiver, s32 msg, void* extra_info = nullptr);
    bool dispatchMessageToAllObjects(double delay, s32 sender, s32 msg, void* extra_info = nullptr);
    void dispatchDelayedMessages(u32 elapsed_ms);
    void cancelReceiver(u32 id);
    void clear();

private:
    CGameObjectManager& m_manager;
    double m_time_ms = 0.0;
    // Equivalent keys preserve insertion order, including identical messages.
    std::multimap<double, Telegram> m_pending;
};

#endif
