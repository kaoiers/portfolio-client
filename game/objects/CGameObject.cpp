//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/02/01
//
// File Name : CGameObject.cpp
//
// 게임 오브젝트 클래스
//
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "CGameObject.h"
#include "../God_Game.h"
#include "../CAppcontext.h"
#include "../controller/EnumPickingType.h"
#include "../eventhandle/CEventHandleManager.h"

#include "CGameObjectManager.h"
#include "../ai/MessageDispatcher.h"
#include "../shader/CLightEffectManager.h"
#include "../interfaces/CMainGameGUI.h"
#include "../interfaces/CControllerGUI.h"
#include "../interfaces/CGUIManager.h"

u32 CGameObject::m_next_valid_id = 1;

CGameObject::CGameObject(OwnerType owner, u32 objtype,
    vector3df pos,
    vector3df rot,
    vector3df scale) :
    m_obj_type(objtype),
    m_owner_type(owner),
    m_animgr(NULL),
    m_enable(true),
    m_command_type(com_none),
    m_object_manager(CAppContext::getGodGame()->getObjectManager()),
    m_tag(false)
{
}

CGameObject::CGameObject(OwnerType owner, u32 obj_id,
    u32 objtype,
    vector3df pos,
    vector3df rot,
    vector3df scale) :
    m_obj_type(objtype),
    m_owner_type(owner),
    m_animgr(NULL),
    m_enable(true),
    m_command_type(com_none),
    m_object_manager(CAppContext::getGodGame()->getObjectManager()),
    m_tag(false)
{
}

/*======================================================*/
// 신노드 지우기
/*======================================================*/
bool CGameObject::removeSceneNode()
{
    return true;
}

/*======================================================*/
// 오브젝트 아이디 설정하기
/*======================================================*/
void CGameObject::setIdFromValidTest()
{
    m_uid = m_next_valid_id;

    m_next_valid_id++;
}

CGameObject::~CGameObject()
{
}

/*======================================================*/
// 컨트롤 되고 있는지
/*======================================================*/
bool CGameObject::isPossessed()
{
    return (CObjectController::getInstance()->isPossessed(this));
}

/*======================================================*/
// 모든 오브젝트들에게 메시지를 보내기
/*======================================================*/
bool CGameObject::sendMessageToAllObjects( double delay, s32 sender, s32 msg, void* extra_info)
{
    Dispatcher->dispatchMessageToAllObjects(delay, sender, msg, extra_info);

    return true;
}

/*======================================================*/
// 오브젝트 높이 가져오기
/*======================================================*/
vector3df CGameObject::getHeightPos()
{
    vector3df pos(0, 0, 0);

    return pos;
}

/*======================================================*/
// 명령 타입 설정하기
/*======================================================*/
void CGameObject::setCommandType( Command_Type type)
{
    m_command_type = type;
}

/*======================================================*/
// 메인 게임 GUI 인스턴스
/*======================================================*/
CMainGameGUI* CGameObject::getMainGameGUI()
{
    return CMainGameGUI::getInstance();
}

/*======================================================*/
// 오브젝트 전용 GUI 인스턴스
/*======================================================*/
CGameGUI* CGameObject::getOwnedGUI()
{
    return CGUIManager::getInstance()->getUnitController()->getCurrentControlGUI();
}
