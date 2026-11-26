//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/05/20
//
// File Name : CGameUnitTiger.cpp
// 
// 게임 유닛 타이거 클래스
// 
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "CGameUnitTiger.h"
#include "../eventhandle/CEventHandleManager.h"
#include "../ai/Goal_Think.h"
#include "../ai/God_Messages.h"


CGameUnitTiger::CGameUnitTiger(OwnerType owner,u32 obj_id,
								   u32 objtype,
								   const UNIT_RESOURCE* resource, 
								   const GAMEUNIT_ATTRIBUTE* attribute,
								   UnitTypes unittype, 								   
								   const vector3df& 
								   pos /*= vector3df(0.0f, 0.0f, 0.0f)*/, 
								   const vector3df& rot /*= vector3df(0.0f, 0.0f, 0.0f)*/, 
								   const vector3df& scale /*= vector3df(1.0f, 1.0f, 1.0f)*/ ) : 
CGameUnitArmy(owner, obj_id, objtype, resource, attribute ,unittype, pos, rot, scale)
{

}

CGameUnitTiger::CGameUnitTiger(OwnerType owner, u32 objtype, const UNIT_RESOURCE* resource,
							   const GAMEUNIT_ATTRIBUTE* attribute, UnitTypes unittype, 
							   const vector3df& pos /*= vector3df(0.0f, 0.0f, 0.0f)*/, 
							   const vector3df& rot /*= vector3df(0.0f, 0.0f, 0.0f)*/, 
							   const vector3df& scale /*= vector3df(1.0f, 1.0f, 1.0f)*/ )
							   : CGameUnitArmy(owner, objtype, resource, attribute ,unittype, pos, rot, scale)
{

}


CGameUnitTiger::~CGameUnitTiger()
{

}

void CGameUnitTiger::control(CEventHandler* p_receiver)
{
	
}


void CGameUnitTiger::onCommand()
{

}





void CGameUnitTiger::privateInitialize()
{

	


}




// 
// 
// 	
// // 
// // 	 if(pReceiver->isMouseLOneClick())
// // 	 {
// // 		m_pBrain->RemoveAllSubgoals(); 
// // 		m_pBrain->AddGoal_AttackTarget(this);
// // 
// // 	 }
// // 	 
// // 	 else 
// 		 
// 		//printf("빛방울");
// 
// 



