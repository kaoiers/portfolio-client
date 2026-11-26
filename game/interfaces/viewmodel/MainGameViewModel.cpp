#include "stdafx.h"
#include "MainGameViewModel.h"
#include "../../attributes/GameResourceManager.h"
#include "../../objects/CGameObjectManager.h"
#include "../../objects/CGameUnit.h"
#include "../../objects/CGameRoom.h"
#include "../../map/CGameMap.h"
#include "../../God_Game.h"
#include <algorithm>
#include <tuple>
#include <utility>

namespace
{
auto stateFields(const MainGameViewState& state)
{
    return std::tie(state.crop, state.lumber, state.stone, state.units, state.unit_limit,
        state.level, state.exp, state.max_exp, state.exp_ratio, state.door_enabled, state.selection_available);
}
}

MainGameViewModel::MainGameViewModel(CGameResourceManager& resources, CGameObjectManager& objects, God_Game& game)
    : m_resources(resources), m_objects(objects), m_game(game)
{
    refresh();
}

void MainGameViewModel::setObserver(Observer observer)
{
    m_observer = std::move(observer);
    if (m_observer) m_observer(m_state);
}

void MainGameViewModel::refresh()
{
    MainGameViewState next;
    const auto resources = m_resources.getResources();
    next.crop = resources.crop;
    next.lumber = resources.lumber;
    next.stone = resources.stone;
    next.units = m_resources.getUnitCounts();
    next.unit_limit = m_resources.getTotalUnitCounts();
    next.level = m_resources.getCurrentLevel();
    next.exp = m_resources.getCurrentExp();
    next.max_exp = m_resources.getMaxPlayerExp(next.level);
    next.exp_ratio = next.max_exp ? std::clamp(static_cast<f32>(next.exp) / next.max_exp, 0.0f, 1.0f) : 0.0f;
    next.door_enabled = m_door_enabled;
    next.selection_available = m_selection_available;
    if (stateFields(next) != stateFields(m_state))
    {
        m_state = next;
        if (m_observer) m_observer(m_state);
    }
}

bool MainGameViewModel::requestSelect(CGameObject* object)
{
    if (!object || !m_selection_available || m_objects.isOnControlState() ||
        m_game.getCurrentGameState() != God_Game::GameState::on_game ||
        m_objects.getObjectFromId(object->getId()) != object)
        return false;

    if (auto* unit = dynamic_cast<CGameUnit*>(object); unit && unit->getAllyType() == unit_mine)
        m_objects.setController(unit);
    else if (auto* room = dynamic_cast<CGameRoom*>(object); room && room->getOwnerType() == object_mine)
        m_objects.setController(room);
    else
        return false;
    return true;
}

bool MainGameViewModel::requestWave()
{
    if (auto* map = m_game.getGameMap())
    {
        map->startEnemyGenerate();
        return true;
    }
    return false;
}

void MainGameViewModel::requestAddExp(u32 exp)
{
    if (m_game.getCurrentGameState() != God_Game::GameState::on_friend)
        m_resources.increaseExp(exp);
    refresh();
}

void MainGameViewModel::setDoorEnabled(bool enabled)
{
    m_door_enabled = enabled;
    refresh();
}

void MainGameViewModel::setSelectionAvailable(bool available)
{
    m_selection_available = available;
    refresh();
}
