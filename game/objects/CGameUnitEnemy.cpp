//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/05/29
//
// File Name : CGameUnitEnemy.cpp
// 
// 게임 적군 클래스
// 
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "CGameUnitEnemy.h"
#include "../ai/Goal_Think.h"
#include "CGameRoom.h"
#include "../ai/God_Messages.h"
#include "../ai/MessageDispatcher.h"
#include "CGameObjectManager.h"
#include "../enemy_gen/CEnemyGenerator.h"

CGameUnitEnemy::CGameUnitEnemy(CEnemyGenerator* pGenerator ,const OwnerType& owner, unsigned int obj_id, unsigned int objtype, 
							   const UNIT_RESOURCE* resource, const GAMEUNIT_ATTRIBUTE* attribute, 
							   UnitTypes unittype, 
							   const vector3df& pos , 
							   const vector3df& rot , 
							   const vector3df& scale  )
							   : CGameUnit(owner, obj_id, objtype, resource, attribute ,unittype, unit_opponet, pos, rot, scale)
							   , m_pGenerator(pGenerator), m_sRemainTime(0), m_sElapsedTime(0)
{

	
	m_pBrain->EnemyInit();

	m_sGoingHomeTime = 120 * 1000;

}

CGameUnitEnemy::CGameUnitEnemy(CEnemyGenerator* pGenerator, const OwnerType& owner, unsigned int objtype, const UNIT_RESOURCE* resource, 
							   const GAMEUNIT_ATTRIBUTE* attribute, UnitTypes unittype, 
							   const vector3df& pos , 
							   const vector3df& rot , 
							   const vector3df& scale  )
							   : CGameUnit(owner, objtype, resource, attribute ,unittype, unit_opponet, pos, rot, scale)
							   , m_pGenerator(pGenerator), m_sRemainTime(0), m_sElapsedTime(0)
{
	
	m_sGoingHomeTime = 120 * 1000;

	m_pBrain->EnemyInit();
}

CGameUnitEnemy::~CGameUnitEnemy()
{

	if(m_pGenerator)
		m_pGenerator->addDeadCount();

}

/*======================================================*/
// 행동 중재하기
/*======================================================*/

void CGameUnitEnemy::ArbitrateBehavior()
{
// 
// 	if(this->isAlive())
// 	{
// 		if(m_pEnemyTargetingSystem->getTargetType() == target_building  )
// 		{
// 			
// 			m_pBrain->AddGoal_AttackBuilding();				
// 		}
// 
// 		
// 		else if(m_pEnemyTargetingSystem->getTargetType() == target_unit)
// 		{
// 			if(!(this->isInHitDistance(this->getEnemyTargetingSystem()->getUnitTarget()->Pos())))
// 			{
// 				m_pBrain->RemoveAllSubgoals();
// 				
// 				m_pBrain->AddGoal_AttackTarget(m_pEnemyTargetingSystem->getUnitTarget());
// 			}
// 			else
// 			{
// 				m_pBrain->AddGoal_AttackTarget(m_pEnemyTargetingSystem->getUnitTarget());
// 
// 			}
// 
// 			//printf("타겟 유닛 포착!! ");
// 			
// 		}
// 
// 
// 	}
}


/*======================================================*/
// 공격 중인지
/*======================================================*/
bool	CGameUnitEnemy::isOnAttack()
{
	return (!(m_pBrain->notPresent(goal_attack_building) ) || !(m_pBrain->notPresent(goal_attack_target) ) );

}


/*======================================================*/
// 빌딩 파괴 메시지 처리하기
/*======================================================*/
void CGameUnitEnemy::HandleDestroyBuildingMessage( CGameRoom* pRoom )
{

	//this->RemoveSubGoals();

	//this->getEnemySensoryMemory()->RemoveRoomFromMemory(pRoom);

	
}


/*======================================================*/
// 죽기 메시지 처리하기
/*======================================================*/
void CGameUnitEnemy::HandleKillUnitMessage( CGameUnit* pUnit )
{
	
}


/*======================================================*/
// 데미지 메시지 처리하기
/*======================================================*/
void CGameUnitEnemy::HandleUnitDeadMessage( CGameUnit* pUnit )
{
	
}