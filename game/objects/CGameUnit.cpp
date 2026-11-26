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
					 AllianceType Ally,
				   const vector3df& pos, 
				   const vector3df& rot , 
				   const vector3df& scale ) :
MovingEntity(owner, obj_id, objtype,
			
			 resource->m_fMax_Speed,
			 resource->m_fMass,
			 resource->m_fTurnRate,
			 resource->m_fMaxForce,
			 resource->m_fNormal_Speed, 
			 pos, rot, scale),
			 m_unit_type(unittype),
			 m_rUnitResource(resource),
			 m_eAlly(Ally), 
			 m_bHitOnce(false),			 
			 CGameUnitAttribute(attribute),
			 m_fHealthbarHeight(10.0f), 
			 m_fHealthbarWidth(90.0f),
			 m_uHPUpdateTime(2500)

{	
	m_pBrain = new Goal_Think(this);
}

CGameUnit::CGameUnit(OwnerType owner, u32 objtype, const UNIT_RESOURCE* resource,
					 const GAMEUNIT_ATTRIBUTE* attribute, UnitTypes unittype,AllianceType Ally,
					 const vector3df& pos /*= vector3df(0.0f, 0.0f, 0.0f)*/, 
					 const vector3df& rot /*= vector3df(0.0f, 0.0f, 0.0f)*/, 
					 const vector3df& scale /*= vector3df(1.0f, 1.0f, 1.0f)*/ ) :
MovingEntity(owner, objtype,
			 resource->m_fMax_Speed,
			 resource->m_fMass,
			 resource->m_fTurnRate,
			 resource->m_fMaxForce,
			 resource->m_fNormal_Speed, 
			 pos, rot, scale),
			 m_unit_type(unittype),
			 m_rUnitResource(resource),
			 m_eAlly(Ally), 
			 m_bHitOnce(false),			 
			 CGameUnitAttribute(attribute),
			 m_fHealthbarHeight(10.0f), 
			 m_fHealthbarWidth(90.0f),
			 m_uHPUpdateTime(2500)
{
}




CGameUnit::~CGameUnit()
{

}


/*======================================================*/
// 유닛 애니메이션 초기화
/*======================================================*/
void CGameUnit::InitAnimation()
{

}



/*======================================================*/
// 무기 초기화
/*======================================================*/
void CGameUnit::InitWeapon()
{


}





/*======================================================*/
// 메시지 처리하기
/*======================================================*/
bool CGameUnit::HandleMessage( const Telegram& msg )
{
	m_pBrain->HandleMessage(msg);

	switch(msg.Msg)
	{

	case Msg_YouDead :

		getObjectManager()->DeleteRequest(this->GetID());


		break;


	case Msg_DestroyRoom :		
		{
			CGameUnitEnemy*	unit = dynamic_cast<CGameUnitEnemy * >(this);

			if(unit != NULL)
			{
				CGameRoom*	room = reinterpret_cast<CGameRoom * >(msg.ExtraInfo);

				unit->HandleDestroyBuildingMessage(room);

			}
		}
		break;

	case Msg_EnemyKillUnit :
		{
			CGameUnitEnemy*	unit = dynamic_cast<CGameUnitEnemy * >(this);

			if(unit != NULL)
			{
				CGameUnit*	pTarget = reinterpret_cast<CGameUnit * >(msg.ExtraInfo);

				unit->HandleKillUnitMessage(pTarget);

			}

		}

		break;

	case Msg_IDemagedYou :

		{
			if(this->getUnitType() != UNIT_ENEMY_SOLDIER)
			{
				if(this->getUnitType() != UNIT_WORKER1)
				{	

					if(m_pBrain->notPresent(goal_attack_target) && m_pBrain->notPresent(goal_move_to_position))
					{			
					}

				}

			}




		}


		break;



	case Msg_UnitDead :


		CGameUnitEnemy*	enemy = dynamic_cast<CGameUnitEnemy* >(this);

		CGameUnit*	unit = reinterpret_cast<CGameUnit * >(msg.ExtraInfo);

		if(enemy != NULL)
		{		
			if(enemy != unit)
			{
				enemy->HandleUnitDeadMessage(unit);
			}
		}


		else
		{	


			CGameUnit*	unit = reinterpret_cast<CGameUnit * >(msg.ExtraInfo);

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
void CGameUnit::setCurrentAni( const u32 atype, const bool bLoop )
{
	

}



/*======================================================*/
// 이동 업데이트
/*======================================================*/
void CGameUnit::UpdateMoveMent(u32 timeMs)
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
bool CGameUnit::isInHitDistance( const vector3df& pos, f32 bRadius)
{
	vector3df distance = pos - Pos();
	
	f32	hitDistance = getHitRange() + bRadius;

	hitDistance *= hitDistance;

	return (distance.getLength() < hitDistance);

}


/*======================================================*/
// 공격 가능 거리 가져오기
/*======================================================*/
vector3df CGameUnit::getApproachPosition( const vector3df& pos ) 
{
	vector3df distance = pos - Pos();
	
	f32 newLength = distance.getLength() - getHitRange();
			
	return (Pos() + (newLength * distance.normalize()));
}



/*======================================================*/
// 죽이기 메시지 보내기
/*======================================================*/
void CGameUnit::DispatchMessageKill( CGameUnit* pTarget )
{
	void *killedTarget = reinterpret_cast<CGameUnit *>(pTarget);

	Dispatcher->DispatchMessageToAllObjects(SEND_MSG_IMMEDIATELY, SENDER_ID_IRRELEVANT , Msg_UnitDead, killedTarget);
}


/*======================================================*/
// 죽기 목표 설정
/*======================================================*/
void CGameUnit::AddGoal_Dead()
{
	m_pBrain->AddGoal_Die();

}


/*======================================================*/
// 이동하기 목표 설정
/*======================================================*/
void CGameUnit::AddGoal_MoveToPosition(const vector3df& pos)
{
	m_pBrain->AddGoal_MoveToPosition(pos);
}



/*======================================================*/
// 데미지 더하기
/*======================================================*/
void CGameUnit::AddDamage( const u32 damage, CGameUnit* pAttacker)
{

	if(pAttacker)
	{
	CalAttacked(pAttacker->getAttack());


	if(this->getOwnerType() == object_mine){
		if(this->getUnitType() == UNIT_ENEMY_SOLDIER)
		{
			if(!this->isAlive())
			{
				SendMessageToAllObjects(0.0, pAttacker->GetID() , Msg_UnitDead , this);
				this->AddGoal_Dead(); 		

				//NETWORK
				//NetworkPacketSpace::SendUnitKillReqPacket(this->GetID());
			}
		}

		else
		{

			if(!this->isAlive())
			{
				CGameUnitEnemy* pEnemy = dynamic_cast<CGameUnitEnemy *>(pAttacker);

				SendMessageToAllObjects(0.0, pEnemy->GetID(), Msg_UnitDead , this);

				SendMessageToAllObjects(0.0, pEnemy->GetID(), Msg_EnemyKillUnit , this);

				this->AddGoal_Dead();  
				
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

	DamageShow(damage);

	updateHpBar();



}


/*======================================================*/
// 걸어갈 수 있는지
/*======================================================*/
bool CGameUnit::canWalkTo(const vector3df&  TargetPos)
{
	return  (!(CGameMap::GetInstance())->isPathObstructed( this->Pos()  ,TargetPos, this->getRadius()));	
}


/*======================================================*/
// 사이간 걸어갈 수 있는지
/*======================================================*/
bool CGameUnit::canWalkBetween( const vector3df& from, const vector3df& to ) 
{
	return  (!(CGameMap::GetInstance())->isPathObstructed( from, to, getRadius()));	

}


/*======================================================*/
// 데미지 표시하기
/*======================================================*/
void CGameUnit::DamageShow( const u32 damage )
{
	
}



/*======================================================*/
// 경험치 획득 처리하기
/*======================================================*/
void CGameUnit::ObtainExp( const u32 uExp )
{
	//scene::IParticleSystemSceneNode* ps;

}



/*======================================================*/
// 데미지 처리하기
/*======================================================*/
void CGameUnit::SendDamageReq( const u32 damage, CGameUnit*	pAttacker )
{
	//NETWORK
	//NetworkPacketSpace::SendDamageReqPacket(GetID(), damage, true, pAttacker->GetID());
	
}


/*======================================================*/
// 하위 목표 삭제하기
/*======================================================*/
void CGameUnit::RemoveSubGoals()
{
	m_pBrain->RemoveAllSubgoals();

}


/*======================================================*/
// 시간에 따라 HP 증가시키기
/*======================================================*/
void CGameUnit::updateHP( const u32 timeMs )
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
	f32 percent =  (f32(getHp())/f32(getMaxHp())) * m_fHealthbarWidth;
	//	f32 abc = (50.0f - percent)/m_fHealthbarWidth;
}