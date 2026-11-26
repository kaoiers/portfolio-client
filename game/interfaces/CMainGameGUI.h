//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/06/30
//
// File Name : CMainGameGUI.h
//
// 게임 메인 GUI
//
//////////////////////////////////////////////////////////////////////////

#include "IGameGUI.h"

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

class CMainGameGUI : public CGameGUI
{
    CBuildingObject* m_building;
    CGameObjectManager* m_obj_man;
    CGameTimerLimiter* m_time_limiter;
    CGameResourceManager* m_game_resource_manager;
    bool m_object_select_available;

    CImageGUI* m_level_bar;
    CTextGUI* m_level_text;

    CImageGUI* m_warning_image;
    CTextGUI* m_warning_text;

    CButtonGUI* m_go_home_button;
    CButtonGUI* m_facebook_button;

    God_Game* m_game;

    f32 m_alpha_ratio;

    static CMainGameGUI* m_instance;

private:
    virtual bool interfaceControl(CEventHandler * p_receiver);
    void addMeshControl(CEventHandler * p_receiver);

public:
    CMainGameGUI(CGameObjectManager* p_obj_man);
    virtual ~CMainGameGUI();

    static CMainGameGUI* getInstance() { return m_instance; }

    void startTimer();
    void endTimerEvent();

    void showWaveButton();
    void setObjectSelectAvailable(const bool b_available) { m_object_select_available = b_available; }
    const bool getObjectSelectAvailable() const { return m_object_select_available; }
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
