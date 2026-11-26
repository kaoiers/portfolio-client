//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/02/11
//
// File Name : CControllerGUI.h
//
// 컨트롤 GUI 인터페이스 관리
//
//////////////////////////////////////////////////////////////////////////

#ifndef CUNIT_CONTROLLER_GUI_H
#define CUNIT_CONTROLLER_GUI_H

class CGameGUI;
class CUnitGodGUI;
class CUnitWorkerGUI;
class CUnitArmyGUI;

class CGameUnitGod;
class CGameUnitWorker;
class CRoomJailGUI;
class CRoomWaitingGUI;

class CRoomFarmGUI;
class CRoomMineGUI;
class CRoomWoodGUI;
class CRoomCommunityGUI;
class CRoomStockGUI;
class CRoomTowerGUI;
class CRoomUpTowerGUI;

class CGameUnitArmy;
class CGameUnitGod;
class CGameUnitWorker;

class CGameObject;

class CControllerGUI
{
    CGameGUI* m_current_gui;
    CUnitGodGUI* m_unit_god_gui;
    CUnitWorkerGUI* m_unit_worker_gui;
    CUnitArmyGUI* m_unit_army_gui;

    CRoomJailGUI* m_room_jail_gui;
    CRoomWaitingGUI* m_room_waiting_gui;
    CRoomFarmGUI* m_room_farm_gui;
    CRoomMineGUI* m_room_mine_gui;

    CRoomWoodGUI* m_room_wood_gui;

    CRoomCommunityGUI* m_room_community_gui;
    CRoomStockGUI* m_room_stock_gui;
    CRoomTowerGUI* m_room_tower_gui;
    CRoomUpTowerGUI* m_room_up_tower_gui;

    void setGuiController(CGameGUI* p_gui);

    static CControllerGUI* p_instance;

public:
    CControllerGUI();

    ~CControllerGUI();

    static CControllerGUI* instance();

    void setGodGUI(CGameUnitGod* p_god);

    void setWorkerGUI(CGameUnitWorker* p_worker);

    void setArmyGUI(CGameUnitArmy* p_army);

    CGameGUI* setCurrentControlGUI(CGameObject * obj);

    CGameGUI* getCurrentControlGUI() { return m_current_gui; }

    CRoomCommunityGUI* getCommunityGUI() { return m_room_community_gui; }

    void disableGui();
};

#endif
