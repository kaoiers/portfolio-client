#include "stdafx.h"
#include "RoomViewModel.h"
#include "../../objects/CGameRoom.h"
#include <algorithm>
#include <tuple>
#include <utility>

namespace
{
auto stateFields(const RoomViewState& state)
{
    return std::tie(state.bound, state.id, state.hp, state.max_hp, state.hp_ratio, state.alive);
}
}

void RoomViewModel::bind(CGameObject* object)
{
    auto* room = dynamic_cast<CGameRoom*>(object);
    m_room = room && room->getRoomType() == m_type ? room : nullptr;
    m_lifetime = m_room ? m_room->getLifetimeToken() : std::weak_ptr<const int>{};
    refresh();
}

CGameRoom* RoomViewModel::model() const
{
    return m_lifetime.expired() ? nullptr : m_room;
}

void RoomViewModel::refresh()
{
    RoomViewState next;
    if (auto* room = model())
    {
        next.bound = true;
        next.id = room->getId();
        next.hp = room->getRoomHp();
        next.max_hp = room->getTotalRoomHP();
        next.hp_ratio = next.max_hp ? std::clamp(static_cast<f32>(next.hp) / next.max_hp, 0.0f, 1.0f) : 0.0f;
        next.alive = room->isAlive();
    }
    if (stateFields(next) != stateFields(m_state))
    {
        m_state = next;
        if (m_observer)
            m_observer(m_state);
    }
}

void RoomViewModel::setObserver(Observer observer)
{
    m_observer = std::move(observer);
    if (m_observer)
        m_observer(m_state);
}

bool RoomViewModel::requestDestroy()
{
    auto* room = model();
    if (!room || !room->getObjectManager())
        return false;
    room->explosion();
    room->deleteRoom();
    return true;
}
