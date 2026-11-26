#pragma once
#include "../../../basicType.h"
#include <functional>

class CGameResourceManager;
class CGameObjectManager;
class CGameObject;
class God_Game;

/// 메인 UI에 필요한 자원, 레벨, 경험치 및 선택 상태의 값 스냅샷이다.
struct MainGameViewState
{
    u32 crop = 0;
    u32 lumber = 0;
    u32 stone = 0;
    u32 units = 0;
    u32 unit_limit = 0;
    u32 level = 0;
    u32 exp = 0;
    u32 max_exp = 0;
    f32 exp_ratio = 0;
    bool door_enabled = false;
    bool selection_available = true;
};

/// 게임 모델에서 메인 UI 표시 정보를 읽고 선택 및 웨이브 명령을 전달한다.
class MainGameViewModel
{
public:
    using Observer = std::function<void(const MainGameViewState&)>;
    MainGameViewModel(CGameResourceManager& resources, CGameObjectManager& objects, God_Game& game);
    void refresh();
    void setObserver(Observer observer);
    const MainGameViewState& state() const { return m_state; }
    bool requestSelect(CGameObject* object);
    bool requestWave();
    void requestAddExp(u32 exp);
    void setDoorEnabled(bool enabled);
    void setSelectionAvailable(bool available);

private:
    CGameResourceManager& m_resources;
    CGameObjectManager& m_objects;
    God_Game& m_game;
    MainGameViewState m_state;
    Observer m_observer;
    bool m_door_enabled = false;
    bool m_selection_available = true;
};
