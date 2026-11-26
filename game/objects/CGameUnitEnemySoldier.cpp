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


CGameUnitEnemySoldier::CGameUnitEnemySoldier(CEnemyGenerator* pGenerator, OwnerType owner, unsigned int obj_id, unsigned int objtype,
											 const UNIT_RESOURCE* resource, const GAMEUNIT_ATTRIBUTE* attribute, 
											 UnitTypes unittype, 
											 const vector3df& pos /*= vector3df(0.0f, 0.0f, 0.0f)*/, 
											 const vector3df& rot /*= vector3df(0.0f, 0.0f, 0.0f)*/, 
											 const vector3df& scale /*= vector3df(1.0f, 1.0f, 1.0f)*/ )
											  : CGameUnitEnemy(pGenerator,owner, obj_id, objtype, resource, attribute ,unittype, pos, rot, scale)
{



}

CGameUnitEnemySoldier::CGameUnitEnemySoldier(CEnemyGenerator* pGenerator, OwnerType owner, unsigned int objtype, const UNIT_RESOURCE* resource,
											 const GAMEUNIT_ATTRIBUTE* attribute, UnitTypes unittype, 
											 const vector3df& pos /*= vector3df(0.0f, 0.0f, 0.0f)*/, 
											 const vector3df& rot /*= vector3df(0.0f, 0.0f, 0.0f)*/, 
											 const vector3df& scale /*= vector3df(1.0f, 1.0f, 1.0f)*/ )
											  : CGameUnitEnemy(pGenerator, owner, objtype, resource, attribute ,unittype, pos, rot, scale)
{

}


/*======================================================*/
// 업데이트
/*======================================================*/
void CGameUnitEnemySoldier::update( u32 timeMs )
{
	UpdateMoveMent(timeMs);

	m_pBrain->Process();


	if(this->getOwnerType() == object_mine)
	{

		
	}

	if(m_sRemainTime == 0)
	{
		m_sRemainTime = timeMs;
	}
	else
	{
		m_sElapsedTime = timeMs - m_sRemainTime;
	}




	
}



/*======================================================*/
// 근거리 공격하기
/*======================================================*/
bool CGameUnitEnemySoldier::short_attack( CGameUnit* pTarget )
{

	if(!m_bHitOnce)
	{	
		{

			if(this->getOwnerType() == object_mine)
				pTarget->SendDamageReq(getAttack(), this);

			Dispatcher->DispatchMsg(0.0, 0, pTarget->GetID(), Msg_IDemagedYou , this);

			m_bHitOnce = true;
		}	 
	}

	return false;

}

void CGameUnitEnemySoldier::PrivateInitialize()
{

}


CGameUnitEnemySoldier::~CGameUnitEnemySoldier()
{
	//m_pBrain->RemoveAllSubgoals();
}