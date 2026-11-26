//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/04/06
//
// File Name : CGameUnitWorker.h
//
// 게임 유닛 일꾼
//
//////////////////////////////////////////////////////////////////////////

#ifndef CGAME_UNIT_WORKER_H
#define CGAME_UNIT_WORKER_H

#include "CGameUnit.h"
#include "../attributes/CGameUnitAttribute.h"

class CGameRoom;
class CGameRoomProductBase;

/// 일꾼의 건설, 채집 및 제어 상태를 관리한다.
class CGameUnitWorker : public CGameUnit
{
    virtual void privateInitialize();

    bool m_building_complete;

    CGameRoom* m_control_room;

    CGameRoom* m_build_room;

    CGameRoomProductBase* m_product_room;

    bool m_fix_room_to_ground;

    bool m_network_on_building;
    vector3df m_network_on_building_pos;

    void buildingControl(CEventHandler* p_receiver);
    void collectingControl(CEventHandler* p_receiver);

public:
    virtual void control(CEventHandler* p_receiver) {};
    virtual void onCommand() {};
    virtual void update(u32 time_ms);
    virtual bool shortAttack(CGameUnit* p_target);
    virtual bool longAttack(CGameUnit* p_target) { return false; }
    virtual void enterControl();
    virtual void updateControl(CEventHandler* p_receiver);
    virtual void exitControl();

    CGameUnitWorker(OwnerType owner, u32 obj_id, u32 objtype,
        const UNIT_RESOURCE* resource,
        const GAMEUNIT_ATTRIBUTE* attribute,
        UnitTypes unittype,
        const vector3df& pos = vector3df(0.0f, 0.0f, 0.0f),
        const vector3df& rot = vector3df(0.0f, 0.0f, 0.0f),
        const vector3df& scale = vector3df(1.0f, 1.0f, 1.0f));

    virtual ~CGameUnitWorker();

public:
    void addGoalBuilding(const vector3df& pos);
    const bool isBuildingComplete() { return m_building_complete; }
    void setBuildingComplete(const bool comp = true) { m_building_complete = comp; }
    void removeSubGoals();

    void addBuilding(BuildingTypes room_type);

    const bool isBuildingCompleted();
    void buildingStart();
    void updateBuildingRoom();

    CGameRoom* getCurrentBuildingRoom() { return m_build_room; }
    CGameRoom* getBackRoom();

    void setCurrentBuildingRoom(CGameRoom* p_room) { m_build_room = p_room; }
    void setCurrentControlRoom(CGameRoom* p_room) { m_control_room = p_room; }

    bool getCurrentControlRoom() { return (m_control_room != 0); }
    void workingAnimation(const vector3df& dir);
    void offWorkingAnimation();

    void pushControlCompletedRoom();
    void popBuildingCompletedRoom();

    void cancelBuilding();
    void cancelControl();

    void collectingComplete();

public:
    void onNetworkBuildCommand();
    void onNetworkBuildStartCommand(u32 seconds);
    void onNetworkBuildStartViewCommand(CGameRoom* p_room);
    void onNetworkBuildCompleteViewCommand();
};

#endif
