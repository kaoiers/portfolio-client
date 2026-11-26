//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/06/22
//
// File Name : CObjectController.cpp
//
// 오브젝트 컨트롤 관리
//
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "../CAppcontext.h"
#include "../God_Game.h"
#include "CGameObject.h"
#include "CObjectController.h"
#include "IBaseController.h"

#include <map>
#include "../PlugIn/PluginManager.h"
#include "../PlugIn/plugin.h"
#include "../shader/CLightEffectManager.h"
#include "CGameRoom.h"
#include "../interfaces/CControllerGUI.h"
#include "CGameUnit.h"

CObjectController::CObjectController() : m_controller(0), m_owner(0), m_control_state(0), m_plug_in_particle(0)
{
}

/*======================================================*/
// 컨트롤 설정
/*======================================================*/
void CObjectController::setController( IBaseController * p_controller)
{
    if ( m_controller != p_controller)
    {
        if (m_controller)
        {
            m_controller->exitControl();
            if (auto* gui = CControllerGUI::instance())
                gui->disableGui();
        }

        m_controller = p_controller;

        p_controller->enterControl();

        m_owner = dynamic_cast<CGameObject *>(m_controller);

        commonEnterControlForType(m_owner->getObjectType());

        m_control_state = false;
    }
}

/*======================================================*/
// 업데이트
/*======================================================*/
void CObjectController::update(CEventHandler* event_handler)
{
    if (m_controller)
    {
        commonUpdateControlForType(m_owner->getObjectType());

        m_controller->updateControl(event_handler);
    }
}

/*======================================================*/
// 컨트롤 중인지
/*======================================================*/
bool CObjectController::isOnControlState() const
{
    if (m_controller == 0)
    {
        return false;
    }

    CGameObject* obj = dynamic_cast<CGameObject *>(m_controller);

    if (obj->getCommandType() != com_none)
    {
        return true;
    }

    return false;
}

/*======================================================*/
// 개체가 컨트롤을 가지고 있는지
/*======================================================*/
bool CObjectController::isPossessed( CGameObject * obj)
{
    return (m_owner == obj);
}

/*======================================================*/
// 타입마다 컨트롤 설정
/*======================================================*/
void CObjectController::commonEnterControlForType( const u32 type)
{
    switch (type)
    {
    case GODTYPE_UNIT :
        {
        }

        break;

    case GODTYPE_BUILDING :

        break;
    }
}

/*======================================================*/
// 컨트롤별 컨트롤 업데이트
/*======================================================*/
void CObjectController::commonUpdateControlForType( const u32 type)
{
    switch (type)
    {
    case GODTYPE_UNIT :
        break;

    case GODTYPE_BUILDING :

        break;

    default :

        break;
    }
}

/*======================================================*/
// 컨트롤러 무효화
/*======================================================*/
void CObjectController::nullifyController()
{
    if (m_controller)
    {
        m_controller->exitControl();

        m_owner = 0;
    }

    if (auto* gui = CControllerGUI::instance())
        gui->disableGui();

    m_controller = nullptr;
    m_owner = nullptr;
}
