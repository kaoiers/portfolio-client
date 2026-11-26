//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/01/30
//
// File Name : God_Game.h
//
// 게임 메인
//
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "../basicType.h"
#include "common/UncopyableUtil.h"

#include <memory>
#include <string>

class CGameObjectManager;
class CCameraManager;
class CEventHandler;
class CGridSceneNode;
class CGUIManager;
class CPathPlanner;
class CObjectResourceManager;
class PluginManager;
class CGameMap;

void warningBox(const std::wstring str);
struct PACKET_ACCOUNT_LOGIN_CL_LN_REQ;

class God_Game : private UnCopyable
{
public:
    typedef enum
    {
        on_intro,
        on_game,
        on_friend

    }GameState;

private:
    GameState m_game_state;

    std::unique_ptr<CGameObjectManager> m_object_manager;
    std::unique_ptr<CCameraManager> m_camera_manager;
    std::unique_ptr<CEventHandler> m_event_handler;
    std::unique_ptr<CGUIManager> m_gui_manager;
    std::unique_ptr<PluginManager> m_plug_in_manager;
    std::unique_ptr<CGameMap> m_game_map;

    bool m_running;

public:
    bool initialize();
    bool gameLoading();
    bool gameReset();

    void setGameState(const GameState state) { m_game_state = state; }

    const bool isRunning() { return m_running; }
    void setRunning(const bool r) { m_running = r; }

    void render();
    void update(u32 time_ms);
    bool control();

    CGameObjectManager* getObjectManager() { return m_object_manager.get(); }
    CCameraManager* getCameraManager() { return m_camera_manager.get(); }
    CEventHandler* getEventHandler() { return m_event_handler.get(); }
    CGUIManager* getGUIManager() { return m_gui_manager.get(); }

    CGameMap* getGameMap() { return m_game_map.get(); }
    PluginManager* getPluginManager() { return m_plug_in_manager.get(); }

    void drawSceneForInterface();
    void clearGame(const GameState state);
    void playSound(const char *sound_name, const bool loop /*= true*/);
    const GameState getCurrentGameState() { return m_game_state; }

    God_Game();
    ~God_Game();

public:
    static God_Game* getInstance();
};
