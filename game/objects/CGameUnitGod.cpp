//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/04/05
//
// File Name : CGameUnitGod.cpp
// 
// 게임 유닛 신
// 
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "CGameUnitGod.h"

#include "../ai/Goal_Think.h"
#include "../eventhandle/CEventHandleManager.h"
#include "../ai/God_Messages.h"
#include "../interfaces/CControllerGUI.h"
#include "../attributes/GameResourceManager.h"
#include "../map/CGameMap.h"


/*======================================================*/
// 개별 초기화
/*======================================================*/
void CGameUnitGod::PrivateInitialize()
{

}


/*======================================================*/
// 업데이트
/*======================================================*/
void CGameUnitGod::update( u32 timeMs )
{
	UpdateMoveMent(timeMs);

	m_pBrain->Process();

	if(this->getOwnerType() == object_mine)
	{
	
	}
}



/*======================================================*/
//근거리 공격
/*======================================================*/
bool CGameUnitGod::short_attack( CGameUnit* pTarget )
{
	
	return false;
}



/*======================================================*/
// 컨트롤 도입 처리
/*======================================================*/
void CGameUnitGod::enter_control()
{
	CControllerGUI::Instance()->setGodGUI(this);

}



CGameUnitGod::CGameUnitGod(OwnerType owner, unsigned int obj_id, unsigned int objtype,
						   const UNIT_RESOURCE* resource, 
						   const GAMEUNIT_ATTRIBUTE* attribute, 
						   UnitTypes unittype, 
						   const vector3df& pos /*= vector3df(0.0f, 0.0f, 0.0f)*/, 
						   const vector3df& rot /*= vector3df(0.0f, 0.0f, 0.0f)*/, 
						   const vector3df& scale /*= vector3df(1.0f, 1.0f, 1.0f)*/ )
						   : CGameUnit(owner, objtype, resource, attribute ,unittype,unit_mine, pos, rot, scale), 
						   m_bMoveFlag(false), m_pArbitrateRegulator(0), m_bCommandNone(false)
{

	
	m_pBrain->ArmyInit();

	CGameResourceManager::GetInstance()->addUnitCounts();	

}

CGameUnitGod::~CGameUnitGod()
{

	CGameMap::GetInstance()->GodDeadEvent();

	CGameResourceManager::GetInstance()->SubstractUnitCounts();		

}


/*======================================================*/
// 컨트롤 업데이트
/*======================================================*/
void CGameUnitGod::update_control( CEventHandler* pReceiver )
{
	if(m_bCommandNone && pReceiver->isMouseLUp())
	{
		this->setCommandType(com_none);
		m_bCommandNone = false;		
	}


	if(this->getCommandType() == com_none)
	{
		if(pReceiver->isMouseROneClick())
		{
			 m_pBrain->AddGoal_MoveToPosition(pReceiver->getMouseUpGroundPosition());

			 m_bMoveFlag =  true;
		}
	}
	

	if(this->getCommandType() == com_attack)
	{
		if(pReceiver->isMouseLOneClick())
		{
			m_pBrain->AddGoal_MoveToPosition(pReceiver->getMouseUpGroundPosition());

			m_bMoveFlag =  false;

			m_bCommandNone = true;
		}
	}


}




/*======================================================*/
// 행동 중재
/*======================================================*/
void CGameUnitGod::Arbitrate()
{	
// 	if(this->isAlive() && !m_bMoveFlag)
// 	{
// 		if(m_pTargetingSystem->isTargetPresent())
// 		{
// 
// 			if(!(this->isInHitDistance(this->getTargetingSystem()->getTarget()->Pos(),
// 				this->getTargetingSystem()->getTarget()->getRadius())))
// 			{
// 				m_pBrain->RemoveAllSubgoals();
// 				
// 				m_pBrain->AddGoal_AttackTarget();
// 			}
// 			else
// 			{
// 				m_pBrain->AddGoal_AttackTarget();
// 
// 			}		
// 		}
// 	}
// 
// 	if(m_pBrain->notPresent(goal_move_to_position))
// 	{
// 		m_bMoveFlag = false;
// 	}

}