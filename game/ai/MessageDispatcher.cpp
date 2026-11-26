//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/02/15
//
// File Name : MessageDispatcher.h
//
// 메시지 전달기
//
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "MessageDispatcher.h"
#include "../objects/CGameObject.h"
#include "../objects/CGameObjectManager.h"

#include <cmath>

MessageDispatcher::MessageDispatcher(CGameObjectManager& manager)
    : m_manager(manager)
{
}

bool MessageDispatcher::dispatchMsg(double delay, s32 sender, s32 receiver, s32 msg, void* extra_info)
{
    if (!std::isfinite(delay) || (delay > 0.0 && extra_info))
        return false;

    auto* object = m_manager.getObjectFromId(static_cast<u32>(receiver));
    if (!object)
        return false;

    if (delay <= 0.0)
    {
        object->handleMessage(Telegram(m_time_ms, sender, receiver, msg, extra_info));
        return true;
    }

    const double due = m_time_ms + delay * 1000.0;
    if (!std::isfinite(due))
        return false;
    m_pending.emplace(due, Telegram(due, sender, receiver, msg));
    return true;
}

bool MessageDispatcher::dispatchMessageToAllObjects(double delay, s32 sender, s32 msg, void* extra_info)
{
    if (!std::isfinite(delay) || (delay > 0.0 && extra_info))
        return false;
    if (sender != SENDER_ID_IRRELEVANT && !m_manager.getObjectFromId(static_cast<u32>(sender)))
        return false;

    // Snapshot IDs so message handlers may request deletion without invalidating iteration.
    const auto ids = m_manager.getObjectIds();
    bool accepted = false;
    for (u32 id : ids)
        accepted = dispatchMsg(delay, sender, static_cast<s32>(id), msg, extra_info) || accepted;
    return accepted;
}

void MessageDispatcher::dispatchDelayedMessages(u32 elapsed_ms)
{
    m_time_ms += elapsed_ms;
    while (!m_pending.empty() && m_pending.begin()->first <= m_time_ms)
    {
        const Telegram telegram = m_pending.begin()->second;
        m_pending.erase(m_pending.begin()); // Remove before calling potentially reentrant handlers.
        if (auto* object = m_manager.getObjectFromId(static_cast<u32>(telegram.receiver)))
            object->handleMessage(telegram);
    }
}

void MessageDispatcher::cancelReceiver(u32 id)
{
    for (auto it = m_pending.begin(); it != m_pending.end();)
    {
        if (static_cast<u32>(it->second.receiver) == id)
            it = m_pending.erase(it);
        else
            ++it;
    }
}

void MessageDispatcher::clear()
{
    m_pending.clear();
}
