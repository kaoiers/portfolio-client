//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/02/26
//
// File Name : CGameObjectManager.h
//
// 게임 오브젝트 관리
//
//////////////////////////////////////////////////////////////////////////

#ifndef GAME_OBJECT_MANAGER_H
#define GAME_OBJECT_MANAGER_H

#include <memory>
#include <map>
#include <list>

#include "CObjectListSet.h"
#include "EnumObjectType.h"

class CGameObject;
struct CAnimation_Info;
class CBuildingBlock;
class CBuildingObject;

class CGameRoom;
class CGameRoomGod;

class CGameUnit;
class CGameUnitArmy;
class CGameUnitEnemy;

class CEventHandler;
class CAppContext;
class CTerrainObject;
class IBaseController;
class CObjectSelector;
class CEnemyGenerator;
struct Telegram;

#define EntityMgr CGameObjectManager::getInstance()

class CObjectController;

class CGameObjectManager
{
using ObjectMap = std::map<u32, std::unique_ptr<CGameObject>>;

    ObjectMap m_map_id_character;
    std::list<u32> m_delete_queue;

    std::vector<CGameUnit* > m_unit_set;

    std::vector<CGameRoom* > m_room_set;

    std::unique_ptr<CObjectController> m_object_controller;

private:
    static CGameObjectManager * m_instance;

public:
    static CGameObjectManager* getInstance();

public:
    CGameObjectManager();

    ~CGameObjectManager();

    bool removeObject(u32 cid);

    void removeAllObjects();

    CGameObject* getObjectFromId(u32 cid);

    void deleteRequest(s32 idkey);

    void removeDeleteQueue();

    bool isValidId(u32 obj_id);

public:
    // Transfers ownership; duplicate or null objects are rejected.
    bool registerObject(std::unique_ptr<CGameObject> obj);

public:
    CGameUnitEnemy* addUnitEnemy(OwnerType owner, u32 unit_id, UnitTypes Unittype,
        const vector3df& pos, const vector3df& rot = vector3df(0.0f, 0.0f, 0.0f));

    CGameUnitEnemy* addUnitEnemy(const vector3df& pos, CEnemyGenerator* p_generator);

    CGameUnit* addUnit(OwnerType owner, u32 unit_id, UnitTypes Unittype,
        const vector3df& pos, const vector3df& rot = vector3df(0.0f, 0.0f, 0.0f));

    CGameUnitArmy* addUnitArmy(OwnerType owner, UnitTypes Unittype, const vector3df& pos,
        const vector3df& rot = vector3df(0.0f, 0.0f, 0.0f));

    CGameRoom* addRoom(OwnerType owner, const BuildingTypes Roomtype, u32 room_id = 0, CGameUnit* p_worker = 0);

    CGameRoom* addRoomOnTile(OwnerType owner, const BuildingTypes Roomtype, const vector2di& tile, u32 room_id = 0);

    CGameRoomGod* addGodRoom(OwnerType owner, const vector2di& tile_pos);

    CTerrainObject* addTerrainMap(OwnerType owner, s32 cx, s32 cz, f32 sx, f32 sz) { return nullptr; };

public:
    bool control(CEventHandler *p_receiver);

    void update();

    void render();

    bool drop();

    void setController(IBaseController* controller);

    bool isControlled(CGameObject* obj) const;

    bool isOnControlState();

    void setControlState(const bool on = true);

public:
    void dispatchMsg(const Telegram& msg);

    bool init();

    void removeUnitFromSet(CGameUnit* p_unit);

    void removeRoomFromSet(CGameRoom* p_room);

    void clearMemoryFromObject(CGameObject* p_obj);

    void clearTargetFromObject( CGameObject* p_obj);
};

#endif
