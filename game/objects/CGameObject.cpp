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

unsigned int	CGameObject::m_iNextValidID = 1;

CGameObject::CGameObject(OwnerType owner, unsigned int objtype,
						 vector3df pos,
						 vector3df rot,
						 vector3df scale) :
							m_objType(objtype),  
							m_eOwnerType(owner),
							m_pAnimgr(NULL),
							m_bEnable(true),
							m_CommandType(com_none),
							m_pObjectManager(CAppContext::GetGodGame()->getObjectManager()),
							m_bTag(false)
{
	

}

CGameObject::CGameObject(OwnerType owner,  unsigned int obj_id,
						 unsigned int objtype, 
						 vector3df pos, 
						 vector3df rot, 
						 vector3df scale) :
m_objType(objtype),  
m_eOwnerType(owner),
m_pAnimgr(NULL),
m_bEnable(true),
m_CommandType(com_none),
m_pObjectManager(CAppContext::GetGodGame()->getObjectManager()),
m_bTag(false)
{
	
}


/*======================================================*/
// 신노드 지우기
/*======================================================*/
bool CGameObject::RemoveSceneNode()
{
	
	return true;	
}



/*======================================================*/
// 오브젝트 아이디 설정하기
/*======================================================*/
void CGameObject::SetIDFromValidTest()
{

	
	m_uid = m_iNextValidID;			
	
	m_iNextValidID++;
	

}



CGameObject::~CGameObject()
{

}


/*======================================================*/
// 컨트롤 되고 있는지
/*======================================================*/
bool CGameObject::isPossessed()
{	
	return (CObjectController::GetInstance()->isPossessed(this));
}



/*======================================================*/
// 모든 오브젝트들에게 메시지를 보내기
/*======================================================*/
bool CGameObject::SendMessageToAllObjects( double delay, int sender, int msg, void* ExtraInfo )
{
	 Dispatcher->DispatchMessageToAllObjects(delay,	 sender, msg, ExtraInfo);
	
	 return true;
}

/*======================================================*/
// 오브젝트 높이 가져오기
/*======================================================*/
vector3df CGameObject::getHeightPos()
{
	vector3df pos(0,0,0);
	
	
	return pos;
}

/*======================================================*/
// 명령 타입 설정하기
/*======================================================*/
void CGameObject::setCommandType( Command_Type type )
{
	m_CommandType = type; 
}


/*======================================================*/
// 메인 게임 GUI 인스턴스
/*======================================================*/
CMainGameGUI* CGameObject::getMainGameGUI()
{
	return CMainGameGUI::GetInstance();
}


/*======================================================*/
// 오브젝트 전용 GUI 인스턴스
/*======================================================*/
CGameGUI* CGameObject::getOwnedGUI()
{
	return CGUIManager::GetInstance()->getUnitController()->getCurrentControlGUI();
}