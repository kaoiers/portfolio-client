//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/04/03
//
// File Name : CGameUnit.h
// 
// 게임 유닛 기본 클래스
// 
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "CGameUnit.h"
#include "../CAppContext.h"
#include "../God_Game.h"
#include "CGameObject.h"
#include "../eventhandle/CEventHandleManager.h"
#include "../interfaces/CGUIManager.h"
#include "../ai/Goal_Think.h"
#include "../ai/God_Messages.h"
#include "../ai/MessageDispatcher.h"
#include "CGameObjectManager.h"
#include "../map/CGameMap.h"
#include "CGameRoom.h"
#include "CGameUnitEnemy.h"
#include "../shader/CLightEffectManager.h"
#include "../interfaces/CMainGameGUI.h"


CGameUnit::CGameUnit(OwnerType owner,u32 obj_id, u32 objtype, const UNIT_RESOURCE* resource,
					const GAMEUNIT_ATTRIBUTE* attribute,
					 UnitTypes unittype,
					 AllianceType ally,
				   const vector3df& pos, 
				   const vector3df& rot , 
				   const vector3df& scale ) :
MovingEntity(owner, obj_id, objtype,
			
			 resource->m_max_speed,
			 resource->m_mass,
			 resource->m_turn_rate,
			 resource->m_max_force,
			 resource->m_normal_speed, 
			 pos, rot, scale),
			 m_unit_type(unittype),
			 m_unit_resource(resource),
			 m_ally_type(ally), 
			 m_hit_once(false),			 
			 CGameUnitAttribute(attribute),
			 m_healthbar_height(10.0f), 
			 m_healthbar_width(90.0f),
			 m_hp_update_time(2500)

{	
	m_brain = new Goal_Think(this);
}

CGameUnit::CGameUnit(OwnerType owner, u32 objtype, const UNIT_RESOURCE* resource,
					 const GAMEUNIT_ATTRIBUTE* attribute, UnitTypes unittype,AllianceType ally,
					 const vector3df& pos /*= vector3df(0.0f, 0.0f, 0.0f)*/, 
					 const vector3df& rot /*= vector3df(0.0f, 0.0f, 0.0f)*/, 
					 const vector3df& scale /*= vector3df(1.0f, 1.0f, 1.0f)*/ ) :
MovingEntity(owner, objtype,
			 resource->m_max_speed,
			 resource->m_mass,
			 resource->m_turn_rate,
			 resource->m_max_force,
			 resource->m_normal_speed, 
			 pos, rot, scale),
			 m_unit_type(unittype),
			 m_unit_resource(resource),
			 m_ally_type(ally), 
			 m_hit_once(false),			 
			 CGameUnitAttribute(attribute),
			 m_healthbar_height(10.0f), 
			 m_healthbar_width(90.0f),
			 m_hp_update_time(2500)
{
}




CGameUnit::~CGameUnit()
{

}


/*======================================================*/
// 유닛 애니메이션 초기화
/*======================================================*/
void CGameUnit::initAnimation()
{

}



/*======================================================*/
// 무기 초기화
/*======================================================*/
void CGameUnit::initWeapon()
{


}





/*======================================================*/
// 메시지 처리하기
/*======================================================*/
bool CGameUnit::handleMessage( const Telegram& msg )
{
	m_brain->handleMessage(msg);

	switch(msg.msg)
	{

	case Msg_YouDead :

		getObjectManager()->deleteRequest(this->getId());


		break;


	case Msg_DestroyRoom :		
		{
			CGameUnitEnemy*	unit = dynamic_cast<CGameUnitEnemy * >(this);

			if(unit != NULL)
			{
				CGameRoom*	room = reinterpret_cast<CGameRoom * >(msg.extra_info);

				unit->handleDestroyBuildingMessage(room);

			}
		}
		break;

	case Msg_EnemyKillUnit :
		{
			CGameUnitEnemy*	unit = dynamic_cast<CGameUnitEnemy * >(this);

			if(unit != NULL)
			{
				CGameUnit*	p_target = reinterpret_cast<CGameUnit * >(msg.extra_info);

				unit->handleKillUnitMessage(p_target);

			}

		}

		break;

	case MSG_I_DAMAGED_YOU :

		{
			if(this->getUnitType() != UNIT_ENEMY_SOLDIER)
			{
				if(this->getUnitType() != UNIT_WORKER1)
				{	

					if(m_brain->notPresent(goal_attack_target) && m_brain->notPresent(goal_move_to_position))
					{			
					}

				}

			}




		}


		break;



	case Msg_UnitDead :


		CGameUnitEnemy*	enemy = dynamic_cast<CGameUnitEnemy* >(this);

		CGameUnit*	unit = reinterpret_cast<CGameUnit * >(msg.extra_info);

		if(enemy != NULL)
		{		
			if(enemy != unit)
			{
				enemy->handleUnitDeadMessage(unit);
			}
		}


		else
		{	


			CGameUnit*	unit = reinterpret_cast<CGameUnit * >(msg.extra_info);

			if(unit != this)
				if(unit && unit->getAllyType() != this->getAllyType())
				{

				}

				return false;
		}
		break;
	}

	return false;
}




/*======================================================*/
// 공격 성공햿는지
/*======================================================*/
bool CGameUnit::isAttackSuccess(CGameObject* opponent )
{
	return false;
	
}



/*======================================================*/
// 현재 애니메이션 설정하기
/*======================================================*/
void CGameUnit::setCurrentAni( const u32 atype, const bool b_loop )
{
	

}



/*======================================================*/
// 이동 업데이트
/*======================================================*/
void CGameUnit::updateMovement(u32 time_ms)
{
	
}



/*======================================================*/
// 공격대상 가져오기
/*======================================================*/
CGameUnit* CGameUnit::getTarget() const
{
	return nullptr;

}


/*======================================================*/
// 공격범위에 들어왔는지
/*======================================================*/
bool CGameUnit::isInHitDistance( const vector3df& pos, f32 b_radius)
{
	vector3df distance = pos - getPos();
	
	f32	hit_distance = getHitRange() + b_radius;

	hit_distance *= hit_distance;

	return (distance.getLength() < hit_distance);

}


/*======================================================*/
// 공격 가능 거리 가져오기
/*======================================================*/
vector3df CGameUnit::getApproachPosition( const vector3df& pos ) 
{
	vector3df distance = pos - getPos();
	
	f32 new_length = distance.getLength() - getHitRange();
			
	return (getPos() + (new_length * distance.normalize()));
}



/*======================================================*/
// 죽이기 메시지 보내기
/*======================================================*/
void CGameUnit::dispatchMessageKill( CGameUnit* p_target )
{
	void *killed_target = reinterpret_cast<CGameUnit *>(p_target);

	Dispatcher->dispatchMessageToAllObjects(SEND_MSG_IMMEDIATELY, SENDER_ID_IRRELEVANT , Msg_UnitDead, killed_target);
}


/*======================================================*/
// 죽기 목표 설정
/*======================================================*/
void CGameUnit::addGoalDead()
{
	m_brain->addGoalDie();

}


/*======================================================*/
// 이동하기 목표 설정
/*======================================================*/
void CGameUnit::addGoalMoveToPosition(const vector3df& pos)
{
	m_brain->addGoalMoveToPosition(pos);
}



/*======================================================*/
// 데미지 더하기
/*======================================================*/
void CGameUnit::addDamage( const u32 damage, CGameUnit* p_attacker)
{

	if(p_attacker)
	{
	calAttacked(p_attacker->getAttack());


	if(this->getOwnerType() == object_mine){
		if(this->getUnitType() == UNIT_ENEMY_SOLDIER)
		{
			if(!this->isAlive())
			{
				sendMessageToAllObjects(0.0, p_attacker->getId() , Msg_UnitDead , this);
				this->addGoalDead(); 		

				//NETWORK
				//NetworkPacketSpace::SendUnitKillReqPacket(this->GetID());
			}
		}

		else
		{

			if(!this->isAlive())
			{
				CGameUnitEnemy* p_enemy = dynamic_cast<CGameUnitEnemy *>(p_attacker);

				sendMessageToAllObjects(0.0, p_enemy->getId(), Msg_UnitDead , this);

				sendMessageToAllObjects(0.0, p_enemy->getId(), Msg_EnemyKillUnit , this);

				this->addGoalDead();  
				
				//NETWORK
				//NetworkPacketSpace::SendUnitKillReqPacket(this->GetID());



				if(this->isPossessed())
				{
					this->getObjectManager()->setController(NULL);
				}			
			}

		}
	}

	}

	damageShow(damage);

	updateHpBar();



}


/*======================================================*/
// 걸어갈 수 있는지
/*======================================================*/
bool CGameUnit::canWalkTo(const vector3df&  target_pos)
{
	return  (!(CGameMap::getInstance())->isPathObstructed( this->getPos()  ,target_pos, this->getRadius()));	
}


/*======================================================*/
// 사이간 걸어갈 수 있는지
/*======================================================*/
bool CGameUnit::canWalkBetween( const vector3df& from, const vector3df& to ) 
{
	return  (!(CGameMap::getInstance())->isPathObstructed( from, to, getRadius()));	

}


/*======================================================*/
// 데미지 표시하기
/*======================================================*/
void CGameUnit::damageShow( const u32 damage )
{
	
}



/*======================================================*/
// 경험치 획득 처리하기
/*======================================================*/
void CGameUnit::obtainExp( const u32 u_exp )
{
	//scene::IParticleSystemSceneNode* ps;

}



/*======================================================*/
// 데미지 처리하기
/*======================================================*/
void CGameUnit::sendDamageReq( const u32 damage, CGameUnit*	p_attacker )
{
	//NETWORK
	//NetworkPacketSpace::SendDamageReqPacket(GetID(), damage, true, pAttacker->GetID());
	
}


/*======================================================*/
// 하위 목표 삭제하기
/*======================================================*/
void CGameUnit::removeSubGoals()
{
	m_brain->removeAllSubgoals();

}


/*======================================================*/
// 시간에 따라 HP 증가시키기
/*======================================================*/
void CGameUnit::updateHP( const u32 time_ms )
{
	if(getHp() < static_cast<s32>(getMaxHp()))
	{
		

	}
	else
	{
	}
}


/*======================================================*/
// HP 바 업데이트
/*======================================================*/
void CGameUnit::updateHpBar()
{
	f32 percent =  (f32(getHp())/f32(getMaxHp())) * m_healthbar_width;
	//	f32 abc = (50.0f - percent)/m_fHealthbarWidth;
}