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
#include "../CAppcontext.h"
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
#include "CGameRoomGod.h"
#include "CGameUnitTiger.h"
#include "../map/CGameMap.h"
#include "CObjectController.h"
#include "../ai/MessageDispatcher.h"

CGameObjectManager * CGameObjectManager::m_instance = nullptr;

CGameObjectManager::CGameObjectManager()
{
    m_instance = this;
    m_object_controller = std::make_unique<CObjectController>();
}

CGameObjectManager::~CGameObjectManager()
{
    m_object_controller.reset();

    m_map_id_character.clear();
    m_delete_queue.clear();
}

/*======================================================*/
// 특정 오브젝트 지우기
/*======================================================*/
bool CGameObjectManager::removeObject( u32 cid)
{
    CGameObject* object = getObjectFromId(cid);

    if (object)
    {
        if (object->removeSceneNode())
        {
            unregisterObject(object);

            delete object;
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
void CGameObjectManager::unregisterById( CGameObject *obj)
{
    std::map<u32, CGameObject*>::iterator iditr = m_map_id_character.find(obj->getId());
    if (iditr != m_map_id_character.end())
    {
        m_map_id_character.erase(iditr);
    }
}

/*======================================================*/
// 오브젝트 등록 해제하기
/*======================================================*/
void CGameObjectManager::unregisterObject(CGameObject* obj)
{
    std::map<u32, CGameObject*>::iterator iditr = m_map_id_character.find(obj->getId());
    if (iditr != m_map_id_character.end())
    {
        m_map_id_character.erase(iditr);
    }
}

/*======================================================*/
// 오브젝트 아이디 가져오기
/*======================================================*/
CGameObject* CGameObjectManager::getObjectFromId( u32 cid)
{
    std::map<u32, CGameObject*>::iterator itr = m_map_id_character.find(cid);

    if (itr != m_map_id_character.end())
    {
        return itr->second;
    }

    return nullptr;
}

/*======================================================*/
// 객체 지우기
/*======================================================*/
bool CGameObjectManager::drop()
{
    removeAllObjects();
    return true;
}

/*======================================================*/
// 모든 오브젝트 지우기
/*======================================================*/
void CGameObjectManager::removeAllObjects()
{
    std::map<u32, CGameObject*>::iterator itr;

    for (itr = m_map_id_character.begin(); itr != m_map_id_character.end(); itr++)
    {
        CGameObject* character = (itr->second);

        if (character->removeSceneNode())
        {
            delete character;
        }
    }

    m_map_id_character.clear();
    m_unit_set.clear();
    m_room_set.clear();
}

/*======================================================*/
// 인스턴스
/*======================================================*/
CGameObjectManager* CGameObjectManager::getInstance()
{
    return m_instance;
}

/*======================================================*/
// 컨트롤러 설정
/*======================================================*/
void CGameObjectManager::setController( IBaseController* controller)
{
    if (controller)
    {
        m_object_controller->setController(controller);

        return;
    }

    m_object_controller->nullifyController();
}

/*======================================================*/
// 컨트롤 선택 초기화
/*======================================================*/
bool CGameObjectManager::isOnControlState()
{
    return m_object_controller->isOnControlState();
}

void CGameObjectManager::setControlState(const bool on)
{
    m_object_controller->setControlState(on);
}

/*======================================================*/
// 적군 추가
/*======================================================*/
CGameUnitEnemy* CGameObjectManager::addUnitEnemy(OwnerType owner, u32 unit_id, UnitTypes Unittype,
    const vector3df& pos,
    const vector3df& rot)
{
    CGameUnitEnemy* unit = 0;

    switch (Unittype)
    {
    case UNIT_ENEMY_SOLDIER :

        break;
    }

    registerObject(unit);

    m_unit_set.push_back(unit);

    nsUnit::unitInit(unit);

    return unit;
}

/*======================================================*/
// 적군 추가
/*======================================================*/
CGameUnitEnemy* CGameObjectManager::addUnitEnemy( const vector3df& pos, CEnemyGenerator* p_generator)
{
    CGameUnitEnemy* unit = 0;

    registerObject(unit);

    m_unit_set.push_back(unit);

    nsUnit::unitInit(unit);

    return unit;
}

/*======================================================*/
// 유닛 추가
/*======================================================*/
CGameUnit* CGameObjectManager::addUnit(OwnerType owner, u32 unit_id, UnitTypes Unittype,
    const vector3df& pos,
    const vector3df& rot)
{
    CGameUnit* unit = 0;

    if (unit != 0)
    {
        registerObject(unit);
        m_unit_set.push_back(unit);
        nsUnit::unitInit(unit);
    }
    return unit;
}

/*======================================================*/
// 아군 추가
/*======================================================*/
CGameUnitArmy* CGameObjectManager::addUnitArmy(OwnerType owner, UnitTypes Unittype, const vector3df& pos,
    const vector3df& rot)
{
    CGameUnitArmy* unit = 0;

    if (unit != nullptr)
    {
        registerObject(unit);

        m_unit_set.push_back(unit);

        nsUnit::unitInit(unit);
    }

    return unit;
}

/*======================================================*/
// 아이디로 오브젝트 등록하기
/*======================================================*/
void CGameObjectManager::registerById(CGameObject *obj)
{
    //m_mapIdCharacter[obj->GetID()] = obj;
}

/*======================================================*/
// 오브젝트 컨트롤
/*======================================================*/
bool CGameObjectManager::control( CEventHandler *p_receiver)
{
    ObjectMap::iterator itr;

    itr = m_map_id_character.begin();

    for (itr = m_map_id_character.begin(); itr != m_map_id_character.end(); itr++)
    {
        CGameObject *object = (itr->second);
        object->control(p_receiver);
    }

    return true;
}

/*======================================================*/
// 업데이트
/*======================================================*/
void CGameObjectManager::update()
{
    Dispatcher->dispatchDelayedMessages();

    m_object_controller->update();

    removeDeleteQueue();
}

/*======================================================*/
// 삭제기
/*======================================================*/
void CGameObjectManager::deleteRequest(s32 idkey)
{
    m_delete_queue.push_back(idkey);
}

/*======================================================*/
// 삭제기 큐에 있는 오브젝트 삭제하기
/*======================================================*/
void CGameObjectManager::removeDeleteQueue()
{
    if (!m_delete_queue.empty())
    {
        deletion_queue::iterator cur_del = m_delete_queue.begin();
        for (;cur_del != m_delete_queue.end(); ++cur_del)
        {
            CGameUnit* p_set_unit_member = 0;
            CGameRoom* p_set_room_member = 0;

            p_set_unit_member = dynamic_cast<CGameUnit* >(getObjectFromId(*cur_del));

            if (p_set_unit_member)
            {
            }

            p_set_room_member = dynamic_cast<CGameRoom* >(getObjectFromId(*cur_del));

            removeObject((*cur_del));
        }
        m_delete_queue.clear();
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
void CGameObjectManager::registerObject( CGameObject *obj)
{
    registerById(obj);

    registerBySceneNode(obj);
}

/*======================================================*/
// 유효한 아이디인지
/*======================================================*/
bool CGameObjectManager::isValidId( u32 obj_id)
{
    ObjectMap::iterator itr;

    for (itr = m_map_id_character.begin(); itr != m_map_id_character.end(); itr++)
    {
        u32 ex_id = (itr->first);

        if (ex_id == obj_id)
        {
            return false;
        }
    }

    return true;
}

/*======================================================*/
// 메시지 보내기
/*======================================================*/
void CGameObjectManager::dispatchMsg( const Telegram& msg)
{
    ObjectMap::iterator itr;

    for (itr = m_map_id_character.begin(); itr != m_map_id_character.end(); itr++)
    {
        (itr->second)->handleMessage(msg);
    }
}

/*======================================================*/
// 신수방 추가하기
/*======================================================*/
CGameRoomGod* CGameObjectManager::addGodRoom( OwnerType owner, const vector2di& tile_pos)
{
    CGameRoomGod* p_god_room = 0;

    p_god_room->setOnTile(tile_pos);

    registerObject(p_god_room);

    return p_god_room;
}

/*======================================================*/
//방 추가하기
/*======================================================*/
CGameRoom* CGameObjectManager::addRoom( OwnerType owner, const BuildingTypes Roomtype, u32 room_id, CGameUnit* p_worker)
{
    CGameRoom* room = nullptr;

    switch (Roomtype)
    {
    case 1:
        printf("모르는 건물(%d)\n", Roomtype);
        return nullptr;
    }

    if (room_id != 0)
        room->setId(room_id);

    registerObject(room);

    m_room_set.push_back(room);

    return room;
}

/*======================================================*/
// 방 특정 타일에 추가하기
/*======================================================*/
CGameRoom* CGameObjectManager::addRoomOnTile( OwnerType owner, const BuildingTypes Roomtype, const vector2di& tile, u32 room_id)
{
    CGameRoom* room = 0;

    if (Roomtype == BUILDING_GOD)
    {
        room = addGodRoom(owner, tile);
    }

    else
    {
        room = addRoom(owner, Roomtype, room_id);

        if ( room)
            room->setOnTile(tile);
    }

    return room;
}

/*======================================================*/
// 현재 오븍제트가 컨트롤이 되고 있는지
/*======================================================*/
bool CGameObjectManager::isControlled( CGameObject* obj) const
{
    return (m_object_controller->isPossessed(obj));
}

/*======================================================*/
// 유닛을 집합으로부터 삭제
/*======================================================*/
void CGameObjectManager::removeUnitFromSet(CGameUnit* p_unit)
{
}

/*======================================================*/
// 오브젝트 메모리를 삭제하기
/*======================================================*/
void CGameObjectManager::clearMemoryFromObject(CGameObject* p_obj)
{
    std::vector<CGameUnit *> unit_set = m_unit_set;

    std::vector<CGameUnit *>::iterator itr = unit_set.begin();

    CGameUnit* p_unit = nullptr;
    if (p_obj->getObjectType() == GODTYPE_UNIT)
    {
        p_unit = dynamic_cast<CGameUnit *>(p_obj);
    }
}

/*======================================================*/
// 오브젝트로부터 타겟에 대한 기억 지우기
/*======================================================*/
void CGameObjectManager::clearTargetFromObject(CGameObject* p_obj)
{
    std::vector<CGameUnit *> unit_set = m_unit_set;

    std::vector<CGameUnit *>::iterator itr = unit_set.begin();

    for (itr; itr != unit_set.end(); itr++)
    {
        if ((*itr)->getAllyType() == unit_mine)
        {
            continue;
        }
        else if ((*itr)->getAllyType() == unit_opponet)
        {
            CGameUnitEnemy* p_enemy = dynamic_cast<CGameUnitEnemy *>(*itr);
        }
    }
}

/*======================================================*/
// 집합으로부터 룸 지우기
/*======================================================*/
void CGameObjectManager::removeRoomFromSet(CGameRoom* p_room)
{
}
