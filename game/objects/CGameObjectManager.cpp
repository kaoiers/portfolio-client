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
#include <algorithm>
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
    removeAllObjects();
    m_object_controller.reset();
    if (m_instance == this)
        m_instance = nullptr;
}

/*======================================================*/
// 특정 오브젝트 지우기
/*======================================================*/
bool CGameObjectManager::removeObject(u32 cid)
{
    auto it = m_map_id_character.find(cid);
    if (it == m_map_id_character.end())
        return true;

    CGameObject* object = it->second.get();
    if (!object->removeSceneNode())
        return false;

    if (m_object_controller->isPossessed(object))
        m_object_controller->nullifyController();
    if (auto* unit = dynamic_cast<CGameUnit*>(object))
        removeUnitFromSet(unit);
    if (auto* room = dynamic_cast<CGameRoom*>(object))
        removeRoomFromSet(room);

    m_map_id_character.erase(it);
    return true;
}

/*======================================================*/
// 오브젝트 아이디 가져오기
/*======================================================*/
CGameObject* CGameObjectManager::getObjectFromId(u32 cid)
{
    const auto it = m_map_id_character.find(cid);
    return it == m_map_id_character.end() ? nullptr : it->second.get();
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
    std::vector<u32> ids;
    for (const auto& entry : m_map_id_character)
        ids.push_back(entry.first);
    for (u32 id : ids)
        removeObject(id);
    m_delete_queue.clear();
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
    // Engine-backed factory is unavailable in this source-only sample.
    return nullptr;
}

/*======================================================*/
// 적군 추가
/*======================================================*/
CGameUnitEnemy* CGameObjectManager::addUnitEnemy( const vector3df& pos, CEnemyGenerator* p_generator)
{
    // Engine-backed factory is unavailable in this source-only sample.
    return nullptr;
}

/*======================================================*/
// 유닛 추가
/*======================================================*/
CGameUnit* CGameObjectManager::addUnit(OwnerType owner, u32 unit_id, UnitTypes Unittype,
    const vector3df& pos,
    const vector3df& rot)
{
    // Engine-backed factory is unavailable in this source-only sample.
    return nullptr;
}

/*======================================================*/
// 아군 추가
/*======================================================*/
CGameUnitArmy* CGameObjectManager::addUnitArmy(OwnerType owner, UnitTypes Unittype, const vector3df& pos,
    const vector3df& rot)
{
    // Engine-backed factory is unavailable in this source-only sample.
    return nullptr;
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
        CGameObject *object = itr->second.get();
        object->control(p_receiver);
    }

    return true;
}

/*======================================================*/
// 업데이트
/*======================================================*/
void CGameObjectManager::update(CEventHandler* event_handler)
{
    Dispatcher->dispatchDelayedMessages();

    m_object_controller->update(event_handler);

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
    auto pending = std::move(m_delete_queue);
    m_delete_queue.clear();
    for (u32 id : pending)
    {
        if (!removeObject(id))
            m_delete_queue.push_back(id);
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
bool CGameObjectManager::registerObject(std::unique_ptr<CGameObject> obj)
{
    if (!obj)
        return false;

    if (obj->getId() == 0)
    {
        do
        {
            obj->setIdFromValidTest();
        } while (obj->getId() == 0 || !isValidId(obj->getId()));
    }
    if (!isValidId(obj->getId()))
        return false;

    auto* raw = obj.get();
    raw->m_object_manager = this;
    const auto id = raw->getId();
    m_map_id_character.emplace(id, std::move(obj));
    if (auto* unit = dynamic_cast<CGameUnit*>(raw))
        m_unit_set.push_back(unit);
    if (auto* room = dynamic_cast<CGameRoom*>(raw))
        m_room_set.push_back(room);
    return true;
}

/*======================================================*/
// 유효한 아이디인지
/*======================================================*/
bool CGameObjectManager::isValidId(u32 obj_id)
{
    return m_map_id_character.find(obj_id) == m_map_id_character.end();
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
    // Engine-backed factory is unavailable in this source-only sample.
    return nullptr;
}

/*======================================================*/
//방 추가하기
/*======================================================*/
CGameRoom* CGameObjectManager::addRoom( OwnerType owner, const BuildingTypes Roomtype, u32 room_id, CGameUnit* p_worker)
{
    // Engine-backed factory is unavailable in this source-only sample.
    return nullptr;
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
    m_unit_set.erase(std::remove(m_unit_set.begin(), m_unit_set.end(), p_unit), m_unit_set.end());
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
    m_room_set.erase(std::remove(m_room_set.begin(), m_room_set.end(), p_room), m_room_set.end());
}
