//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/05/17
//
// File Name : CGameUnitArmy.cpp
// 
// 게임 적군 클래스
// 
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "CGameUnitArmy.h"
#include "../interfaces/CControllerGUI.h"


//#include "CObjectController.h"
#include "../eventhandle/CEventHandleManager.h"
//#include "myUtil.h"
//#include "CGameObjectManager.h"
#include "../ai/Goal_Think.h"
#include "../ai/God_Messages.h"
#include "CGameObjectManager.h"
#include "../attributes/GameResourceManager.h"
#include "CGameRoom.h"


CGameUnitArmy::CGameUnitArmy(const OwnerType& owner, unsigned int obj_id, unsigned int objtype, const UNIT_RESOURCE* resource,
							 const GAMEUNIT_ATTRIBUTE* attribute, UnitTypes unittype, 
							 const vector3df& pos /*= vector3df(0.0f, 0.0f, 0.0f)*/, 
							 const vector3df& rot /*= vector3df(0.0f, 0.0f, 0.0f)*/, 
							 const vector3df& scale /*= vector3df(1.0f, 1.0f, 1.0f)*/ ) 
							 : CGameUnit( owner, obj_id, objtype, resource, attribute ,unittype, unit_mine, pos, rot, scale)
							 , m_bGoingRoom(false), m_pGuardRoom(0), m_bCommandNone(false)
{
	m_pBrain->ArmyInit();
	CGameResourceManager::GetInstance()->addUnitCounts();	
}

CGameUnitArmy::CGameUnitArmy(const OwnerType& owner, unsigned int objtype, const UNIT_RESOURCE* resource, 
							 const GAMEUNIT_ATTRIBUTE* attribute, UnitTypes unittype, 
							 const vector3df& pos /*= vector3df(0.0f, 0.0f, 0.0f)*/, 
							 const vector3df& rot /*= vector3df(0.0f, 0.0f, 0.0f)*/, 
							 const vector3df& scale /*= vector3df(1.0f, 1.0f, 1.0f)*/ )
							 : CGameUnit( owner, objtype, resource, attribute ,unittype, unit_mine, pos, rot, scale)
							 , m_bGoingRoom(false), m_pGuardRoom(0), m_bCommandNone(false)
{
	m_pBrain->ArmyInit();
	CGameResourceManager::GetInstance()->addUnitCounts();	

}
CGameUnitArmy::~CGameUnitArmy()
{
	CGameResourceManager::GetInstance()->SubstractUnitCounts();	
}

/*======================================================*/
// 컨트롤 선택 초기화
/*======================================================*/
void CGameUnitArmy::enter_control()
{
	CControllerGUI::Instance()->setArmyGUI(this);
}


/*======================================================*/
// 컨트롤 업데이트
/*======================================================*/
void CGameUnitArmy::update_control( CEventHandler* pReceiver )
{

	if(pReceiver->isMouseLUp() && m_bCommandNone)
	{
		this->setCommandType(com_none);
		m_bCommandNone = false;		
	}


	if(pReceiver->isMouseROneClick()) 
	{
		m_pBrain->AddGoal_MoveToPosition(pReceiver->getMouseUpGroundPosition());	
	}	


}


/*======================================================*/
// 가드 요청하기
/*======================================================*/
void CGameUnitArmy::GuardRequest( const vector3df& pos )
{
	if(m_pBrain->notPresent(goal_move_to_position) && m_pBrain->notPresent(goal_attack_target) )
	{
		m_pBrain->AddGoal_MoveToPosition(pos);
	}	
}





void CGameUnitArmy::Arbitrate()
{


}


/*======================================================*/
// 컨트롤 종료처리
/*======================================================*/
void CGameUnitArmy::exit_control()
{
	CControllerGUI::Instance()->DisableGUI();
}



/*======================================================*/
// 업데이트
/*======================================================*/
void CGameUnitArmy::update( const u32& timeMs )
{
	UpdateMoveMent(timeMs);

	m_pBrain->Process();

	updateHP(timeMs);


	if(this->getOwnerType() == object_mine)
	{
		if(m_pGuardRoom  &&  !m_bGoingRoom &&
			this->isAtPosition(m_pGuardRoom->GetGuardPos()))
		{
			m_pGuardRoom->setGuardian(this);
			m_bGoingRoom = true;
		}

	}
}


/*======================================================*/
// 근거리 공격 처리
/*======================================================*/
bool CGameUnitArmy::short_attack( CGameUnit* pTarget )
{


	return false;
}

