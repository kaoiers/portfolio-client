//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/04/05
//
// File Name : CGameRoom.h
//
// 건물 기본 클래스
//
//////////////////////////////////////////////////////////////////////////

#ifndef CGAME_ROOM_H
#define CGAME_ROOM_H

#include <memory>
#include "CGameObject.h"
#include "IBaseController.h"

class CGameUnitWorker;
class CRoomStep;
class CGameResourceManager;
class CGameUnitArmy;
class CGameUnit;

/// 건물의 체력, 건설 상태, 자원 및 타일 관련 인터페이스를 제공하는 모델이다.
class CGameRoom : public CGameObject, public IBaseController
{
    const ROOM_RESOURCE* m_resource;
    u32 m_room_width_cells, m_room_height_cells;
    std::unique_ptr<CRoomStep> m_building_step;
    u32 m_total_room_hp;
    u32 m_room_hp;
    CGameUnitArmy* m_guardian;
    bool m_net_live;
    u32 room_type;

protected:
    bool m_building_finished;
    vector2di m_first_index_tile;
    s32 m_node_index;

public:
    u32 getRoomType() const { return room_type; }

    CGameResourceManager* getGameResource();
    bool isProductRoom();

    bool isAlive() const { return (m_room_hp > 0); }
    bool addDamage(const u32 damage, CGameUnit* p_attacker);
    u32 getRoomHp() const { return m_room_hp; }
    u32 getTotalRoomHP() const { return m_total_room_hp; }

    void setGuardian(CGameUnitArmy* p_unit) { m_guardian = p_unit; }
    CGameUnitArmy* getGuardian() { return m_guardian; }
    void nullifyGuardian() { m_guardian = 0; };
    bool isGuardianPresent() const { return (m_guardian != nullptr); }
    void setNetLive(const bool on) { m_net_live = on; }
    bool getNetLive() const { return m_net_live; }

public:
    CGameRoom(OwnerType owner, u32 objtype, u32 btype, const ROOM_RESOURCE* res,
        const vector3df& pos,
        const vector3df& rot = vector3df(0.0f, 0.0f, 0.0f),
        const vector3df& scale = vector3df(1.0f, 1.0f, 1.0f));

    CGameRoom(OwnerType owner, u32 objtype, u32 btype, const ROOM_RESOURCE* res);
    virtual ~CGameRoom();

    bool handleMessage(const Telegram& msg);

public:
    void setOnebyOneNode();
    void setOnTile(const vector2di& first_index_tile);
    const vector2di& getFirstTile() const { return m_first_index_tile; }

public:
    void buildingUpdate();
    bool isNotWalkableRoom();
    void setBuildingCompleted() { m_building_finished = true; }
    vector3df getPos();
    vector3df getIntersectPoint(const vector3df& point);
    void onBuildingCompleted();

public:
    bool isBuildable(const vector3df& mouse_pos);
    f32 getBuildingTime();

    void buildingStart(const u32 seconds);

    void followMouse(CEventHandler* p_receiver);
    void removeAndLinkNodes();
    void setBuildableColor(const bool buildable = true);

    vector3df getCenterPosToBuilding();
    vector3df getFrontPosToBuilding();
    vector3df getGuardPos();

    void makeBaseGround();
    const bool isBuildingCompleted();
    void restoreRoomAreaEdges();
    void deleteRoom();
    void deleteRoomReal();
    s32 getRoomNodeIndex();
    bool removeAllNodesForDestroy();
    void explosion();

protected:
    vector2di getTile( const vector3df& ground_point);
    vector3df getBuildingOffset();
    void removeBoundaryLines();
    void addBoundaryLines(const bool walkable = true);
    s32 linkDoorEdges();
};

#endif
