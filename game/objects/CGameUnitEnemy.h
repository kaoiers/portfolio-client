//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/05/29
//
// File Name : CGameUnitEnemy.h
//
// 게임 적군 클래스
//
//////////////////////////////////////////////////////////////////////////

#ifndef GAME_UNIT_ENEMY_H
#define GAME_UNIT_ENEMY_H

#include "CGameUnit.h"

class CEnemySensoryMemory;
class CEnemyTargetingSystem;
class CGameRoom;
class CEnemyGenerator;

/// 적 유닛의 공통 행동 및 제어 상태를 표현하는 기반 클래스이다.
class CGameUnitEnemy : public CGameUnit
{
protected:
    CEnemySensoryMemory* m_enemy_sensory_memory;

    CEnemyTargetingSystem* m_enemy_targeting_system;

    Regulator* m_enemy_target_regulator;

    Regulator* m_enemy_memory_regulator;

    Regulator* m_arbitrate_regulator;

    CEnemyGenerator* m_generator;

    u32 m_going_home_time;

    s16 m_remain_time;

    s16 m_elapsed_time;

public:
    virtual void control(CEventHandler* p_receiver) {};

    virtual void onCommand() {};

    virtual bool longAttack(CGameUnit* p_target) { return false; }

    CEnemyGenerator* getEnemyGenerator() { return m_generator; }

    virtual void enterControl() {};
    virtual void updateControl(CEventHandler* p_receiver) {};
    virtual void exitControl() {};

    void arbitrateBehavior();
    bool isOnAttack();

    void handleDestroyBuildingMessage(CGameRoom* p_room);
    void handleKillUnitMessage(CGameUnit* p_unit);
    void handleUnitDeadMessage(CGameUnit* p_unit);

    s16 getRemainTime() { return m_going_home_time - m_elapsed_time; }

public:
    CEnemySensoryMemory* getEnemySensoryMemory() { return m_enemy_sensory_memory; }

    CEnemyTargetingSystem* getEnemyTargetingSystem() { return m_enemy_targeting_system; }

    CGameUnitEnemy(CEnemyGenerator* p_generator, OwnerType owner, u32 obj_id, u32 objtype,
        const UNIT_RESOURCE* resource,
        const GAMEUNIT_ATTRIBUTE* attribute,
        UnitTypes unittype,
        const vector3df& pos = vector3df(0.0f, 0.0f, 0.0f),
        const vector3df& rot = vector3df(0.0f, 0.0f, 0.0f),
        const vector3df& scale = vector3df(1.0f, 1.0f, 1.0f));

    CGameUnitEnemy(CEnemyGenerator* p_generator, OwnerType owner, u32 objtype,
        const UNIT_RESOURCE* resource,
        const GAMEUNIT_ATTRIBUTE* attribute,
        UnitTypes unittype,
        const vector3df& pos = vector3df(0.0f, 0.0f, 0.0f),
        const vector3df& rot = vector3df(0.0f, 0.0f, 0.0f),
        const vector3df& scale = vector3df(1.0f, 1.0f, 1.0f));

    virtual ~CGameUnitEnemy();
};

#endif
