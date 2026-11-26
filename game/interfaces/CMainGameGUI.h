//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/06/30
//
// File Name : CMainGameGUI.h
//
// 게임 메인 GUI
//
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "IGameGUI.h"
#include "viewmodel/MainGameViewModel.h"

class CBuildingObject;
class CGameObject;
class CEventHandler;
class CGameObjectManager;
class CGameTimerLimiter;

enum eMAINMENU_GUI_ID
{
    GUI_MAINMENU_OPTION_BUTTON = 1501,
    GUI_MAINMENU_TIME_TEXT = 1502,
    GUI_MAINMENU_TIMEINFO_TEXT = 1503,
    GUI_MAINMENU_RESOURCE_GOLD = 1504,
    GUI_MAINMENU_RESOURCE_LUMBER= 1505,
    GUI_MAINMENU_RESOURCE_STONE = 1506,
    GUI_MAINMENU_RESOURCE_UNIT = 1507,

    GUI_MAINMENU_LOAD_LOGIN_BUTTON = 1508,
    GUI_MAINMENU_WAVESTART_BUTTON = 1509,
    GUI_MAINMENU_TIME_IMAGE = 1510,
    GUI_MAINMENU_LEVELBAR_BACK_IMAGE = 1511,
    GUI_MAINMENU_LEVELBAR_FRONT_IMAGE = 1512,
    GUI_MAINMENU_LEVEL_TEXT = 1514,
    GUI_MAINMENU_WARNING_TEXT = 1515,
    GUI_MAINMENU_WARNING_IMAGE = 1516,

    GUI_MAINMENU_BACKTOHOME_BUTTON = 1517,

    GUI_MAINMENU_RESOURCE_FARM_IMAGE = 1518,
    GUI_MAINMENU_RESOURCE_LUMBER_IMAGE = 1519,
    GUI_MAINMENU_RESOURCE_STONE_IMAGE = 1520,
    GUI_MAINMENU_RESOURCE_UNIT_IMAGE = 1521,

    GUI_MAINMENU_FACEBOOK_LOGIN = 1530
};

class CGameResourceManager;
class God_Game;
class WebBrowserView;

/// 메인 게임 ViewModel의 자원 및 진행 상태를 표시용 스냅샷으로 받아 관리한다.
class CMainGameGUI : public CGameGUI
{
    MainGameViewModel m_view_model;
    MainGameViewState m_view_state;
    God_Game& m_game;
    f32 m_alpha_ratio = 0.0f;

private:
    virtual bool interfaceControl(CEventHandler * p_receiver);

public:
    CMainGameGUI(CGameResourceManager& resources, CGameObjectManager& objects, God_Game& game);
    virtual ~CMainGameGUI();

    const MainGameViewState& getViewState() const { return m_view_state; }
    void refreshView() { m_view_model.refresh(); }
    bool selectObject(CGameObject* object) { return m_view_model.requestSelect(object); }
    void setDamage(u32, u32) override {}

    void startTimer();
    void endTimerEvent();

    void showWaveButton();
    void setObjectSelectAvailable(const bool b_available) { m_view_model.setSelectionAvailable(b_available); }
    const bool getObjectSelectAvailable() const { return m_view_state.selection_available; }
    void setLevelStatus(const f32 percent, const u32 level);

    void addPlayerExp(const u32 exp);

    void fadeOutWarningMessage(const u32 time_ms);
    void playSound2D(const char* soundname, const bool loop = false);
    void playSound3D(const char* soundname, const vector3df& pos, const bool loop = false);
    void stopAllSounds();

    void enableDoorButton(const bool on);

    virtual void guiInitialize();

    virtual void setOwner(CGameObject *owner);

    void setMyPlayerId(/* PLAYER_ID playerId */);
};
