#include "stdafx.h"
#include "UnitViewModel.h"
#include "../../objects/CGameUnitArmy.h"
#include "../../objects/CGameUnitGod.h"
#include "../../objects/CGameUnitWorker.h"
#include <algorithm>
#include <tuple>
#include <utility>

namespace
{
auto stateFields(const UnitViewState& state)
{
    return std::tie(state.bound, state.id, state.level, state.hp, state.max_hp,
        state.hp_ratio, state.exp, state.max_exp, state.command);
}
}

void UnitViewModel::bind(CGameObject* object)
{
    switch (m_role)
    {
    case UnitViewRole::Army: m_unit = dynamic_cast<CGameUnitArmy*>(object); break;
    case UnitViewRole::God: m_unit = dynamic_cast<CGameUnitGod*>(object); break;
    case UnitViewRole::Worker: m_unit = dynamic_cast<CGameUnitWorker*>(object); break;
    }
    m_lifetime = m_unit ? m_unit->getLifetimeToken() : std::weak_ptr<const int>{};
    refresh();
}

void UnitViewModel::unbind()
{
    m_unit = nullptr;
    m_lifetime.reset();
    refresh();
}

CGameUnit* UnitViewModel::model() const
{
    return m_lifetime.expired() ? nullptr : m_unit;
}

void UnitViewModel::refresh()
{
    UnitViewState next;
    if (auto* unit = model())
    {
        next.bound = true;
        next.id = unit->getId();
        next.level = unit->getLevel();
        next.hp = unit->getHp();
        next.max_hp = unit->getMaxHp();
        next.hp_ratio = next.max_hp ? std::clamp(static_cast<f32>(next.hp) / next.max_hp, 0.0f, 1.0f) : 0.0f;
        next.exp = unit->getExp();
        next.max_exp = unit->getMaxExp();
        next.command = unit->getCommandType();
    }

    if (stateFields(next) != stateFields(m_state))
    {
        m_state = next;
        if (m_observer)
            m_observer(m_state);
    }
}

void UnitViewModel::setObserver(Observer observer)
{
    m_observer = std::move(observer);
    if (m_observer)
        m_observer(m_state);
}

bool UnitViewModel::requestCommand(UnitViewRole required_role, Command_Type command)
{
    auto* unit = model();
    if (!unit || m_role != required_role)
        return false;
    unit->setCommandType(command);
    refresh();
    return true;
}

bool UnitViewModel::requestGuard() { return requestCommand(UnitViewRole::Army, com_room_guard); }
bool UnitViewModel::requestAttack() { return requestCommand(UnitViewRole::God, com_attack); }
bool UnitViewModel::requestCollect() { return requestCommand(UnitViewRole::Worker, com_collection); }
bool UnitViewModel::requestIdle() { return requestCommand(UnitViewRole::Worker, com_none); }

bool UnitViewModel::requestBuild(BuildingTypes type)
{
    auto* worker = dynamic_cast<CGameUnitWorker*>(model());
    if (!worker || !worker->getObjectManager() || m_role != UnitViewRole::Worker)
        return false;
    worker->cancelControl();
    worker->addBuilding(type);
    refresh();
    return true;
}

bool UnitViewModel::requestCancelBuilding()
{
    auto* worker = dynamic_cast<CGameUnitWorker*>(model());
    if (!worker || !worker->getObjectManager() || m_role != UnitViewRole::Worker)
        return false;
    worker->cancelBuilding();
    refresh();
    return true;
}
