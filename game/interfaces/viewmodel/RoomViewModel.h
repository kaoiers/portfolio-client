#pragma once

#include "../../../basicType.h"
#include "../../objects/EnumObjectType.h"
#include <functional>
#include <memory>

class CGameObject;
class CGameRoom;

struct RoomViewState
{
    bool bound = false;
    u32 id = 0;
    u32 hp = 0;
    u32 max_hp = 0;
    f32 hp_ratio = 0;
    bool alive = false;
};

class RoomViewModel
{
public:
    using Observer = std::function<void(const RoomViewState&)>;
    explicit RoomViewModel(BuildingTypes type) : m_type(type) {}
    void bind(CGameObject* object);
    void refresh();
    void setObserver(Observer observer);
    const RoomViewState& state() const { return m_state; }
    bool requestDestroy();

private:
    CGameRoom* model() const;
    BuildingTypes m_type;
    CGameRoom* m_room = nullptr;
    std::weak_ptr<const int> m_lifetime;
    RoomViewState m_state;
    Observer m_observer;
};
