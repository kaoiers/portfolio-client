//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/01/30
//
// File Name : God_Game.cpp
//
// 게임 메인
//
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "God_Game.h"
#include "objects/CGameObjectManager.h"
#include "objects/CGameObject.h"
#include "camera/CCameraManager.h"
#include "eventhandle/CEventHandleManager.h"
#include "CAppcontext.h"
#include "controller/EnumPickingType.h"
#include "interfaces/CGUIManager.h"
#include "interfaces/CControllerGUI.h"
#include "PlugIn/PluginManager.h"

#include "map/CGameMap.h"
#include "objects/CObjectController.h"
#include "objects/CGameUnit.h"
#include "interfaces/CLoginGUI.h"
#include "shader/CLightEffectManager.h"
#include "interfaces/CMainGameGUI.h"
#include "attributes/GameResourceManager.h"
#include "option/CGodOption.h"

namespace
{
    constexpr s32 INITIAL_MAP_CELLS_X = 60;
    constexpr s32 INITIAL_MAP_CELLS_Z = 80;
    constexpr s32 INITIAL_MAP_PARTITION_X = 10;
    constexpr s32 INITIAL_MAP_PARTITION_Z = 10;
}

God_Game::God_Game()
    :
    m_game_state(GameState::on_intro),
    m_running(true)
{
}

God_Game::~God_Game()
{
    m_object_manager.reset();
}

/*======================================================*/
// 게임 로딩 처리
/*======================================================*/
bool God_Game::gameLoading()
{
    m_object_manager.reset();
    m_game_map.reset();
    m_gui_manager.reset();
    m_resources = std::make_unique<CGameResourceManager>();
    m_gui_manager = std::make_unique<CGUIManager>();
    m_event_handler = std::make_unique<CEventHandler>();
    m_object_manager = std::make_unique<CGameObjectManager>(m_gui_manager->getUnitController());
    m_object_manager->setSoundSink([this](const char* name, bool loop) { playSound(name, loop); });
    if (!m_gui_manager->gameLoading(*m_resources, *m_object_manager, *this))
        return false;
    m_camera_manager = std::make_unique<CCameraManager>();
    if (!m_camera_manager->init())
        return false;
    m_game_map = std::make_unique<CGameMap>(*m_object_manager, *m_camera_manager);

    if (!m_game_map->init(INITIAL_MAP_CELLS_X, INITIAL_MAP_CELLS_Z,
        INITIAL_MAP_PARTITION_X, INITIAL_MAP_PARTITION_Z))
        return false;
    if (!m_gui_manager->gameLoadingComplete())
        return false;

    setGameState(God_Game::GameState::on_game);

    return true;
}

/*======================================================*/
// 게임 리셋
/*======================================================*/
bool God_Game::gameReset()
{
    return true;
}

/*======================================================*/
// 초기화
/*======================================================*/
bool God_Game::initialize()
{
    return gameLoading();
}

/*======================================================*/
// 렌더링
/*======================================================*/
void God_Game::render()
{
    if (m_game_state == GameState::on_game || m_game_state == GameState::on_friend)
    {
        if (CAppContext::getGodOption()->isShaderOn())
        {
        }
        else
        {
        }
        if (m_game_map)
            m_game_map->render();

    }
    else
    {
    }

    if (m_gui_manager)
        m_gui_manager->render();
}

/*======================================================*/
// 업데이트
/*======================================================*/
void God_Game::update(u32 time_ms)
{
    if (m_game_state == GameState::on_game || m_game_state == GameState::on_friend)
    {
        //순서유의
        if (m_object_manager)
            m_object_manager->update(m_event_handler.get(), time_ms);

        if (m_game_map)
            m_game_map->update(time_ms);
    }

    if (m_event_handler)
        m_event_handler->update();
}

/*======================================================*/
// 컨트롤
/*======================================================*/
bool God_Game::control()
{
    if (m_gui_manager)
        m_gui_manager->control(m_event_handler.get());

    if (m_game_state == GameState::on_game || m_game_state == GameState::on_friend)
    {
        if (m_object_manager)
            m_object_manager->control(m_event_handler.get());
    }

    return true;
}

/*======================================================*/
// 인터페이스 렌더링
/*======================================================*/
void God_Game::drawSceneForInterface()
{
    if (m_gui_manager)
    {
        m_gui_manager->render();
    }
}

/*======================================================*/
// 인스턴스
/*======================================================*/
God_Game* God_Game::getInstance()
{
    static std::unique_ptr<God_Game> instance = std::make_unique<God_Game >();

    return instance.get();
}

/*======================================================*/
// 게임 초기화
/*======================================================*/
void God_Game::clearGame(const GameState state)
{
    m_game_state = state;

    m_game_map->removeAllTrees();

    m_object_manager->setController(nullptr);

    m_object_manager->removeAllObjects();

    m_camera_manager->init();

    if (m_game_state == GameState::on_friend)
        m_gui_manager->getMainGameGUI()->enableDoorButton(true);
    else
        m_gui_manager->getMainGameGUI()->enableDoorButton(false);
}

/*======================================================*/
// 사운드 플레이
/*======================================================*/
void God_Game::playSound( const char *sound_name, const bool loop /*= true*/)
{
}

