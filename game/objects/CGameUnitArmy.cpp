//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/05/17
//
// File Name : CGameUnitArmy.cpp
//
// 게임 적군 클래스
//
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "CGameUnitArmy.h"
#include "../interfaces/CControllerGUI.h"

#include "../eventhandle/CEventHandleManager.h"
#include "../ai/Goal_Think.h"
#include "../ai/God_Messages.h"
#include "CGameObjectManager.h"
#include "../attributes/GameResourceManager.h"
#include "CGameRoom.h"

CGameUnitArmy::CGameUnitArmy(OwnerType owner, u32 obj_id, u32 objtype, const UNIT_RESOURCE* resource,
    const GAMEUNIT_ATTRIBUTE* attribute, UnitTypes unittype,
    const vector3df& pos /*= vector3df(0.0f, 0.0f, 0.0f)*/,
    const vector3df& rot /*= vector3df(0.0f, 0.0f, 0.0f)*/,
    const vector3df& scale /*= vector3df(1.0f, 1.0f, 1.0f)*/)
    : CGameUnit( owner, obj_id, objtype, resource, attribute, unittype, unit_mine, pos, rot, scale)
, m_going_room(false), m_guard_room(0), m_command_none(false)
{
    m_brain->armyInit();
    CGameResourceManager::getInstance()->addUnitCounts();
}

CGameUnitArmy::CGameUnitArmy(OwnerType owner, u32 objtype, const UNIT_RESOURCE* resource,
    const GAMEUNIT_ATTRIBUTE* attribute, UnitTypes unittype,
    const vector3df& pos /*= vector3df(0.0f, 0.0f, 0.0f)*/,
    const vector3df& rot /*= vector3df(0.0f, 0.0f, 0.0f)*/,
    const vector3df& scale /*= vector3df(1.0f, 1.0f, 1.0f)*/)
    : CGameUnit( owner, objtype, resource, attribute, unittype, unit_mine, pos, rot, scale)
, m_going_room(false), m_guard_room(0), m_command_none(false)
{
    m_brain->armyInit();
    CGameResourceManager::getInstance()->addUnitCounts();
}
CGameUnitArmy::~CGameUnitArmy()
{
    CGameResourceManager::getInstance()->subtractUnitCounts();
}

/*======================================================*/
// 컨트롤 선택 초기화
/*======================================================*/
void CGameUnitArmy::enterControl()
{
}

/*======================================================*/
// 컨트롤 업데이트
/*======================================================*/
void CGameUnitArmy::updateControl( CEventHandler* p_receiver)
{
    if (p_receiver->isMouseLUp() && m_command_none)
    {
        this->setCommandType(com_none);
        m_command_none = false;
    }

    if (p_receiver->isMouseROneClick())
    {
        m_brain->addGoalMoveToPosition(p_receiver->getMouseUpGroundPosition());
    }
}

/*======================================================*/
// 가드 요청하기
/*======================================================*/
void CGameUnitArmy::guardRequest( const vector3df& pos)
{
    if (m_brain->notPresent(goal_move_to_position) && m_brain->notPresent(goal_attack_target))
    {
        m_brain->addGoalMoveToPosition(pos);
    }
}

void CGameUnitArmy::arbitrate()
{
}

/*======================================================*/
// 컨트롤 종료처리
/*======================================================*/
void CGameUnitArmy::exitControl()
{
}

/*======================================================*/
// 업데이트
/*======================================================*/
void CGameUnitArmy::update( u32 time_ms)
{
    updateMovement(time_ms);

    m_brain->process();

    updateHP(time_ms);

    if (this->getOwnerType() == object_mine)
    {
        if (m_guard_room && !m_going_room &&
            this->isAtPosition(m_guard_room->getGuardPos()))
        {
            m_guard_room->setGuardian(this);
            m_going_room = true;
        }
    }
}

/*======================================================*/
// 근거리 공격 처리
/*======================================================*/
bool CGameUnitArmy::shortAttack( CGameUnit* p_target)
{
    return false;
}
