//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/05/07
//
// File Name : CGUIManager.cpp
//
// GUI 매니져
//
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "CGUIManager.h"
#include "IGameGUI.h"
#include "../common/CFontManager.h"

#include "../CAppcontext.h"
#include "../God_Game.h"
#include "../eventhandle/CEventHandleManager.h"
#include "CMainGameGUI.h"
#include "../attributes/GameResourceManager.h"
#include "CLoginGUI.h"
#include "CControllerGUI.h"

CGUIManager* CGUIManager::m_instance = nullptr;

CGUIManager::CGUIManager()
    : m_mouse_cursor_gui(0), m_main_game_gui(0), m_pop_up_gui(0), m_web_dialog(nullptr)
{
    m_instance = this;

    m_font_manager = std::make_unique<CFontManager>();
    m_controller_gui = std::make_unique<CControllerGUI>();
}

CGUIManager::~CGUIManager()
{
    for ( GUIMap::iterator it = m_guis.begin(); it != m_guis.end(); ++it)
    {
        SAFE_DELETE(it->second);
    }

    m_guis.clear();

    m_controller_gui.reset();
    m_font_manager.reset();
    if (m_instance == this)
        m_instance = nullptr;
}

/*======================================================*/
// 모든 오브젝트 컨트롤
/*======================================================*/
bool CGUIManager::control( CEventHandler* p_receiver)
{
    GUIMap::iterator itr;

    for (itr = m_guis.begin(); itr != m_guis.end(); itr++)
    {
        if (!(itr->second)->isEnable()) continue;

        (itr->second)->control(p_receiver);
    }

    if (auto* selected = m_controller_gui->getCurrentControlGUI(); selected && selected->isEnable())
        selected->control(p_receiver);

    return true;
}

/*======================================================*/
// 모든 오브젝트 렌더링
/*======================================================*/
bool CGUIManager::render()
{
    GUIMap::iterator itr;// = (--(m_pGUIs.end()));

    return true;
}

/*======================================================*/
// 아이디로 GUI 등록하기
/*======================================================*/
void CGUIManager::registerGuiById( CGameGUI *p_gui)
{
    m_guis[p_gui->getId()] = p_gui;
}

/*======================================================*/
// 아이디로부터 인터페이스 찾기
/*======================================================*/
CGameGUI* CGUIManager::findInterfaceFromId( s32 cid)
{
    GUIMap::iterator itr = m_guis.find(cid);

    if (itr != m_guis.end())
    {
        return itr->second;
    }
    return nullptr;
}

/*======================================================*/
// Register and initialize the GUI.
/*======================================================*/
void CGUIManager::interfaceInit(CGameGUI* BaseGUI)
{
    if (BaseGUI)
    {
        registerGuiById(BaseGUI);
        BaseGUI->guiInitialize();
    }
}

/*======================================================*/
// 인터페이스 불러오기
/*======================================================*/
bool CGUIManager::gameLoading()
{
    return true;
}

/*======================================================*/
// 마지막으로 저장된 GUI ID
/*======================================================*/
u32 CGUIManager::getLastGUIID()
{
    GUIMap::iterator itr;
    itr = m_guis.end();
    itr--;
    return (itr->second)->getId();
}

/*======================================================*/
// GUI가 눌렸는지
/*======================================================*/
bool CGUIManager::isPressed()
{
    GUIMap::iterator itr;

    for (itr = m_guis.begin(); itr != m_guis.end(); itr++)
    {
        if ((itr->second)->isClicked() == true)
        {
            return true;
        }
    }
    return false;
}

/*======================================================*/
// 이벤트 전
/*======================================================*/
bool CGUIManager::postEvent( const SEvent& event)
{
    GUIMap::iterator itr;

    for (itr = m_guis.begin(); itr != m_guis.end(); itr++)
    {
        if ((itr->second)->isEnable())
        {
            (itr->second)->postEvent(event);
        }
    }

    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
