//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/05/29
//
// File Name : CGameUnitEnemySoldier.h
// 
// 게임 적군 군사 클래스
// 
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "CGameUnitEnemySoldier.h"
#include "../ai/Goal_Think.h"
#include "../ai/God_Messages.h"
#include "CGameObjectManager.h"
#include "../ai/God_Messages.h"
#include "../ai/MessageDispatcher.h"
#include "../shader/CLightEffectManager.h"


CGameUnitEnemySoldier::CGameUnitEnemySoldier(CEnemyGenerator* p_generator, OwnerType owner, u32 obj_id, u32 objtype,
											 const UNIT_RESOURCE* resource, const GAMEUNIT_ATTRIBUTE* attribute, 
											 UnitTypes unittype, 
											 const vector3df& pos /*= vector3df(0.0f, 0.0f, 0.0f)*/, 
											 const vector3df& rot /*= vector3df(0.0f, 0.0f, 0.0f)*/, 
											 const vector3df& scale /*= vector3df(1.0f, 1.0f, 1.0f)*/ )
											  : CGameUnitEnemy(p_generator,owner, obj_id, objtype, resource, attribute ,unittype, pos, rot, scale)
{



}

CGameUnitEnemySoldier::CGameUnitEnemySoldier(CEnemyGenerator* p_generator, OwnerType owner, u32 objtype, const UNIT_RESOURCE* resource,
											 const GAMEUNIT_ATTRIBUTE* attribute, UnitTypes unittype, 
											 const vector3df& pos /*= vector3df(0.0f, 0.0f, 0.0f)*/, 
											 const vector3df& rot /*= vector3df(0.0f, 0.0f, 0.0f)*/, 
											 const vector3df& scale /*= vector3df(1.0f, 1.0f, 1.0f)*/ )
											  : CGameUnitEnemy(p_generator, owner, objtype, resource, attribute ,unittype, pos, rot, scale)
{

}


/*======================================================*/
// 업데이트
/*======================================================*/
void CGameUnitEnemySoldier::update( u32 time_ms )
{
	updateMovement(time_ms);

	m_brain->process();


	if(this->getOwnerType() == object_mine)
	{

		
	}

	if(m_remain_time == 0)
	{
		m_remain_time = time_ms;
	}
	else
	{
		m_elapsed_time = time_ms - m_remain_time;
	}




	
}



/*======================================================*/
// 근거리 공격하기
/*======================================================*/
bool CGameUnitEnemySoldier::shortAttack( CGameUnit* p_target )
{

	if(!m_hit_once)
	{	
		{

			if(this->getOwnerType() == object_mine)
				p_target->sendDamageReq(getAttack(), this);

			Dispatcher->dispatchMsg(0.0, 0, p_target->getId(), MSG_I_DAMAGED_YOU , this);

			m_hit_once = true;
		}	 
	}

	return false;

}

void CGameUnitEnemySoldier::privateInitialize()
{

}


CGameUnitEnemySoldier::~CGameUnitEnemySoldier()
{
	//m_pBrain->RemoveAllSubgoals();
}