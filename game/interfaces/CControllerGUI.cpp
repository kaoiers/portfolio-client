//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/02/11
//
// File Name : CControllerGUI.cpp
//
// 컨트롤 GUI 인터페이스 관리
//
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IGameGUI.h"
#include "CGUIManager.h"
#include "CControllerGUI.h"

#include "CUnitGodGUI.h"
#include "CUnitWorkerGUI.h"
#include "CUnitArmyGUI.h"
#include "CRoomJailGUI.h"
#include "CRoomCommunityGUI.h"
#include "CRoomStockGUI.h"
#include "CRoomUpTowerGUI.h"

#include "../objects/CGameUnitGod.h"
#include "../objects/CGameUnitWorker.h"
#include "../objects/CGameUnitArmy.h"

#include "../objects/CGameRoomJail.h"
#include "../objects/CGameRoomCommunity.h"
#include "../objects/CGameRoomStock.h"

CControllerGUI* CControllerGUI::p_instance = nullptr;

CControllerGUI::CControllerGUI() :
    m_current_gui(nullptr),
    m_unit_god_gui(std::make_unique<CUnitGodGUI>()),
    m_unit_worker_gui(std::make_unique<CUnitWorkerGUI>()),
    m_unit_army_gui(std::make_unique<CUnitArmyGUI>())
{
    p_instance = this;
    m_unit_god_gui->hide();
    m_unit_worker_gui->hide();
    m_unit_army_gui->hide();
}

CControllerGUI::~CControllerGUI()
{
    if (p_instance == this)
        p_instance = nullptr;
}

/*======================================================*/
// 신수GUI 컨트롤 지정
/*======================================================*/
void CControllerGUI::setGodGUI( CGameUnitGod* p_god)
{
    m_unit_god_gui->setOwner(p_god);
    setGuiController(m_unit_god_gui.get());
}

/*======================================================*/
// 일꾼 GUI 컨트롤 지정
/*======================================================*/
void CControllerGUI::setWorkerGUI( CGameUnitWorker* p_worker)
{
    m_unit_worker_gui->setOwner(p_worker);
    setGuiController(m_unit_worker_gui.get());
    m_unit_worker_gui->showGroup("building_main", false);
    m_unit_worker_gui->showGroup("building1", false);
    m_unit_worker_gui->showGroup("building2", false);
    m_unit_worker_gui->showGroup("base", true);
}

/*======================================================*/
// 병사 GUI 컨트롤 지정
/*======================================================*/
void CControllerGUI::setArmyGUI( CGameUnitArmy* p_army)
{
    m_unit_army_gui->setOwner(p_army);
    setGuiController(m_unit_army_gui.get());
}

/*======================================================*/
// 현재 GUI 지정
/*======================================================*/
void CControllerGUI::setGuiController( CGameGUI* p_gui)
{
    if (m_current_gui && m_current_gui != p_gui)
    {
        m_current_gui->setOwner(nullptr);
        m_current_gui->hide();
    }

    m_current_gui = p_gui;

    if (m_current_gui)
        m_current_gui->show();
}

/*======================================================*/
// 인스턴스
/*======================================================*/
CControllerGUI* CControllerGUI::instance()
{
    return p_instance;
}

/*======================================================*/
// 비활성화 시키기
/*======================================================*/
void CControllerGUI::disableGui()
{
    if (m_current_gui)
    {
        m_current_gui->setOwner(nullptr);
        m_current_gui->hide();
    }

    m_current_gui = nullptr;
}

/*======================================================*/
// 현재 컨트롤 GUI
/*======================================================*/
CGameGUI* CControllerGUI::setCurrentControlGUI(CGameObject* obj)
{
    if (auto* god = dynamic_cast<CGameUnitGod*>(obj))
        setGodGUI(god);
    else if (auto* worker = dynamic_cast<CGameUnitWorker*>(obj))
        setWorkerGUI(worker);
    else if (auto* army = dynamic_cast<CGameUnitArmy*>(obj))
        setArmyGUI(army);
    else
        disableGui();
    return m_current_gui;
}
