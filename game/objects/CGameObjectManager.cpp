//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/02/26
//
// File Name : CGameObjectManager.cpp
// 
// 게임 오브젝트 관리
// 
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "CGameObject.h"
#include "CGameObjectManager.h"
#include "../CAppContext.h"
#include "../God_Game.h"
#include "CGameUnit.h"
#include "CGameUnitEnemySoldier.h"
#include "CGameUnitWorker.h"
#include "CGameUnitGod.h"
#include "CGameUnitArmy.h"
#include "CGameUnitBunny.h"
#include "CGameUnitTiger.h"
#include "CGameUnitNapoleon.h"
#include "CGameRoom.h"
#include "CGameRoomJail.h"
#include "CGameRoomCommunity.h"
#include "CGameRoomStock.h"
#include "CgameRoomGod.h"
#include "CGameUnitTiger.h"
#include "../map/CGameMap.h"
#include "CObjectController.h"
#include "../ai/MessageDispatcher.h"



CGameObjectManager * CGameObjectManager::m_pInstance = NULL;




CGameObjectManager::CGameObjectManager() 
{
	m_pInstance = this;
	m_pObjectController = new CObjectController();
}




CGameObjectManager::~CGameObjectManager()
{
	SAFE_DELETE(m_pObjectController);

	m_mapIdCharacter.clear();
	m_deleteque.clear();	
	
}



/*======================================================*/
// 특정 오브젝트 지우기
/*======================================================*/
bool CGameObjectManager::RemoveObject( u32 cid )
{
	CGameObject*	object = GetObjectFromID(cid);

	if(object)
	{
 		if(object->RemoveSceneNode())
 		{			
			UnRegisterObject(object);
 
 			delete	object;
 		}

 		else
 		{
 			return false;
 		}
	}
	
	return true;
}


/*======================================================*/
// 오브젝트 등록 해제하기
/*======================================================*/
void CGameObjectManager::UnRegisterbyID( CGameObject *obj )
{
	std::map<u32 , CGameObject*>::iterator iditr = m_mapIdCharacter.find(obj->GetID());
	if(iditr != m_mapIdCharacter.end())
	{
		m_mapIdCharacter.erase(iditr);
	}	

}

/*======================================================*/
// 오브젝트 등록 해제하기
/*======================================================*/
void CGameObjectManager::UnRegisterObject(CGameObject* obj)
{	

	std::map<u32 , CGameObject*>::iterator iditr = m_mapIdCharacter.find(obj->GetID());
	if(iditr != m_mapIdCharacter.end())
	{
			m_mapIdCharacter.erase(iditr);
	}	

}


/*======================================================*/
// 오브젝트 아이디 가져오기
/*======================================================*/
CGameObject* CGameObjectManager::GetObjectFromID( u32 cid )
{
	std::map<u32 , CGameObject*>::iterator itr = m_mapIdCharacter.find(cid);

	if(itr != m_mapIdCharacter.end())
	{
		return itr->second;
	}

	return NULL;
}





/*======================================================*/
// 객체 지우기
/*======================================================*/
bool CGameObjectManager::drop()
{
	RemoveAllObjects();
	return true;
}



/*======================================================*/
// 모든 오브젝트 지우기
/*======================================================*/
void CGameObjectManager::RemoveAllObjects()
{
	std::map<u32 , CGameObject*>::iterator itr;

	for(itr = m_mapIdCharacter.begin(); itr != m_mapIdCharacter.end(); itr++)
	{
		CGameObject*	character = (itr->second);		

		if(character->RemoveSceneNode())
		{		
			delete	character;
		}	
	}

	m_mapIdCharacter.clear();
	m_UnitSet.clear();
	m_RoomSet.clear();
	

	
}


/*======================================================*/
// 인스턴스
/*======================================================*/
CGameObjectManager* CGameObjectManager::GetInstance()
{
	return m_pInstance;
}


/*======================================================*/
// 컨트롤러 설정
/*======================================================*/
void CGameObjectManager::setController( IBaseController* controller )
{

	if(controller)
	{
		m_pObjectController->setController(controller);

		return ;
	}

	m_pObjectController->NullifyController();

}



/*======================================================*/
// 컨트롤 선택 초기화
/*======================================================*/
bool	 CGameObjectManager::isOnControlState()
{
	return m_pObjectController->IsOnControlState();
}

void	CGameObjectManager::setControlState(const bool on)
{
	m_pObjectController->setControlState(on);
	
}


/*======================================================*/
// 적군 추가
/*======================================================*/
CGameUnitEnemy* CGameObjectManager::AddUnitEnemy(OwnerType owner,u32 unit_id, UnitTypes Unittype,
												 const vector3df& pos, 
												 vector3df& rot)
{

	CGameUnitEnemy* unit = 0;


	switch(Unittype)
	{
	case UNIT_ENEMY_SOLDIER : 
	
		break;	
	}

	RegisterObject(unit);

	m_UnitSet.push_back(unit);

	nsUnit::UnitInit(unit);
	
	return unit;
}



/*======================================================*/
// 적군 추가
/*======================================================*/
CGameUnitEnemy* CGameObjectManager::AddUnitEnemy( const vector3df& pos , CEnemyGenerator* pGenerator)
{

	CGameUnitEnemy* unit = 0;

	RegisterObject(unit);
	
	m_UnitSet.push_back(unit);
	
	nsUnit::UnitInit(unit);

	return unit;
}


/*======================================================*/
// 유닛 추가
/*======================================================*/
CGameUnit* CGameObjectManager::AddUnit(OwnerType owner, u32 unit_id, UnitTypes Unittype,
									   const vector3df& pos,
									   vector3df& rot)
{
	
	CGameUnit* unit = 0;

	if (unit != 0)
	{
		RegisterObject(unit);
		m_UnitSet.push_back(unit);
		nsUnit::UnitInit(unit);
	}
	return unit;
}


/*======================================================*/
// 아군 추가
/*======================================================*/
CGameUnitArmy* CGameObjectManager::AddUnitArmy(OwnerType owner, UnitTypes Unittype, const vector3df& pos,
											   vector3df& rot)
{

	CGameUnitArmy* unit = 0;

	/*
	switch(Unittype)
	{

		case UNIT_ARMY_BUNNY : 
			att = resman->Get_UnitAttribute(ATT_UNIT_ARMY_BUNNY);
			unit = new CGameUnitBunny( owner, GODTYPE_UNIT, res, att, Unittype, pos, rot);
			break;

		case UNIT_ARMY_TIGER : 
			att = resman->Get_UnitAttribute(ATT_UNIT_ARMY_TIGER);
			unit = new CGameUnitTiger(owner,  GODTYPE_UNIT, res, att, Unittype, pos, rot);
			break;

		case UNIT_ARMY_NAPOLEON : 
			att = resman->Get_UnitAttribute(ATT_UNIT_ARMY_NAPOLEON);
			unit = new CGameUnitNapoleon(owner, GODTYPE_UNIT, res, att, Unittype, pos, rot);
			break;
	}

	*/

	if (unit != nullptr)
	{
		RegisterObject(unit);

		m_UnitSet.push_back(unit);

		nsUnit::UnitInit(unit);
	}

	return unit;
}




/*======================================================*/
// 아이디로 오브젝트 등록하기
/*======================================================*/
void CGameObjectManager::RegisterbyID(CGameObject *obj)
{
	//m_mapIdCharacter[obj->GetID()] = obj;

}	


/*======================================================*/
// 오브젝트 컨트롤
/*======================================================*/
bool CGameObjectManager::control( CEventHandler *pReceiver )
{
	ObjectMap::iterator itr;

	itr = m_mapIdCharacter.begin();

	for(itr = m_mapIdCharacter.begin(); itr != m_mapIdCharacter.end(); itr++)
	{
		CGameObject *object = (itr->second);
		//object->OnCommand();
		object->control(pReceiver);

		//printf("%d\n", object->GetID());
		
		//object->update(CAppContext::GetDevice()->getTimer()->getTime());
	}

	return true;
}


/*======================================================*/
// 업데이트
/*======================================================*/
void CGameObjectManager::update()
{

	Dispatcher->DispatchDelayedMessages();

	m_pObjectController->update();

	RemoveDeleteQue();
}



/*======================================================*/
// 삭제기
/*======================================================*/
void CGameObjectManager::DeleteRequest(s32 idkey)
{
	m_deleteque.push_back(idkey);
}


/*======================================================*/
// 삭제기 큐에 있는 오브젝트 삭제하기
/*======================================================*/
void CGameObjectManager::RemoveDeleteQue()
{	
	if(!m_deleteque.empty())
	{	
		DeletionQue::iterator curDel = m_deleteque.begin();
		for(;curDel != m_deleteque.end(); ++curDel)
		{
			CGameUnit*	pSetUnitMember = 0;
			CGameRoom*	pSetRoomMember = 0;

			pSetUnitMember = dynamic_cast<CGameUnit* >(GetObjectFromID(*curDel));
			
			if(pSetUnitMember)
			{
				
			}

			pSetRoomMember = dynamic_cast<CGameRoom* >(GetObjectFromID(*curDel));
			


			RemoveObject((*curDel));		
		}
		m_deleteque.clear();
	}
}


/*======================================================*/
// 렌더링
/*======================================================*/
void CGameObjectManager::render()
{

}


/*======================================================*/
// 오브젝트 등록하기
/*======================================================*/
void CGameObjectManager::RegisterObject( CGameObject *obj )
{
	RegisterbyID(obj);

	RegisterbySceneNode(obj);
}



/*======================================================*/
// 유효한 아이디인지
/*======================================================*/
bool CGameObjectManager::IsValidID( u32 obj_id )
{
	ObjectMap::iterator itr;

	for(itr = m_mapIdCharacter.begin(); itr != m_mapIdCharacter.end(); itr++)
	{
		u32 ex_id = (itr->first);

		if(ex_id == obj_id)
		{
			return false;			
		}
	}

	return true;
}


/*======================================================*/
// 메시지 보내기
/*======================================================*/
void CGameObjectManager::DispatchMsg( const Telegram& msg )
{
	ObjectMap::iterator itr;

	for(itr = m_mapIdCharacter.begin(); itr != m_mapIdCharacter.end(); itr++)
	{
		(itr->second)->HandleMessage(msg);
	}

}



/*======================================================*/
// 신수방 추가하기
/*======================================================*/
CGameRoomGod* CGameObjectManager::AddGodRoom( OwnerType owner, const vector2di& tilePos )
{
	CGameRoomGod* pGodRoom = 0;
	


	pGodRoom->setOnTile(tilePos);

	RegisterObject(pGodRoom);
	
	return pGodRoom;
}


/*======================================================*/
//방 추가하기
/*======================================================*/
CGameRoom* CGameObjectManager::AddRoom( OwnerType owner, const BuildingTypes Roomtype, u32 RoomID , CGameUnit* pWorker )
{

	CGameRoom* room = NULL;


	switch(Roomtype)
	{

		case 1:
			printf("모르는 건물(%d)\n", Roomtype);
			return NULL;
	}

	if(RoomID != 0)
		room->SetID(RoomID);



	RegisterObject(room);

	m_RoomSet.push_back(room);

	return room;
}


/*======================================================*/
// 방 특정 타일에 추가하기
/*======================================================*/
CGameRoom* CGameObjectManager::AddRoomOnTile( OwnerType owner, const BuildingTypes Roomtype, const vector2di& tile ,  u32 RoomID)
{
	CGameRoom* room = 0;

	if(Roomtype == BUILDING_GOD)
	{
		room = AddGodRoom(owner, tile);
	}


	else
	{
		room = AddRoom(owner, Roomtype, RoomID );

		if( room )
			room->setOnTile(tile);
	}	

	return room;
}




/*======================================================*/
// 현재 오븍제트가 컨트롤이 되고 있는지
/*======================================================*/
bool CGameObjectManager::isControled( CGameObject* obj ) const
{
	return (m_pObjectController->isPossessed(obj));

}


/*======================================================*/
// 유닛을 집합으로부터 삭제
/*======================================================*/
void CGameObjectManager::RemoveUnitFromSet(CGameUnit* pUnit)
{
	
}



/*======================================================*/
// 오브젝트 메모리를 삭제하기
/*======================================================*/
void CGameObjectManager::ClearMemoryFromObject(CGameObject* pObj)
{
	std::vector<CGameUnit *> UnitSet = m_UnitSet;

	std::vector<CGameUnit *>::iterator itr = UnitSet.begin();

	CGameUnit* pUnit = NULL;
	if (pObj->getObjectType() == GODTYPE_UNIT)
	{
		pUnit = dynamic_cast<CGameUnit *>(pObj);
	}
}


/*======================================================*/
// 오브젝트로부터 타겟에 대한 기억 지우기
/*======================================================*/
void CGameObjectManager::ClearTargetFromObject(CGameObject* pObj)
{
	std::vector<CGameUnit *> UnitSet = m_UnitSet;

	std::vector<CGameUnit *>::iterator itr = UnitSet.begin();

	for (itr; itr != UnitSet.end(); itr++)
	{
		if ((*itr)->getAllyType() == unit_mine)
		{
			continue;
		}
		else if ((*itr)->getAllyType() == unit_opponet)
		{
			CGameUnitEnemy* pEnemy = dynamic_cast<CGameUnitEnemy *>(*itr);

			//pEnemy->getEnemyTargetingSystem()->clearTarget(pObj);
		}
	}



}

/*======================================================*/
// 집합으로부터 룸 지우기
/*======================================================*/
void CGameObjectManager::RemoveRoomFromSet(CGameRoom* pRoom)
{
	

}
