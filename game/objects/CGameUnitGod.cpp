//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/04/05
//
// File Name : CGameUnitGod.cpp
//
// 게임 유닛 신
//
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "CGameUnitGod.h"

#include "../ai/Goal_Think.h"
#include "../eventhandle/CEventHandleManager.h"
#include "../ai/God_Messages.h"
#include "../interfaces/CControllerGUI.h"
#include "../attributes/GameResourceManager.h"
#include "../map/CGameMap.h"

/*======================================================*/
// 개별 초기화
/*======================================================*/
void CGameUnitGod::privateInitialize()
{
}

/*======================================================*/
// 업데이트
/*======================================================*/
void CGameUnitGod::update( u32 time_ms)
{
    updateMovement(time_ms);

    m_brain->process();

    if (this->getOwnerType() == object_mine)
    {
    }
}

/*======================================================*/
//근거리 공격
/*======================================================*/
bool CGameUnitGod::shortAttack( CGameUnit* p_target)
{
    return false;
}

/*======================================================*/
// 컨트롤 도입 처리
/*======================================================*/
void CGameUnitGod::enterControl()
{
    CControllerGUI::instance()->setGodGUI(this);
}

CGameUnitGod::CGameUnitGod(OwnerType owner, u32 obj_id, u32 objtype,
    const UNIT_RESOURCE* resource,
    const GAMEUNIT_ATTRIBUTE* attribute,
    UnitTypes unittype,
    const vector3df& pos /*= vector3df(0.0f, 0.0f, 0.0f)*/,
    const vector3df& rot /*= vector3df(0.0f, 0.0f, 0.0f)*/,
    const vector3df& scale /*= vector3df(1.0f, 1.0f, 1.0f)*/)
    : CGameUnit(owner, objtype, resource, attribute, unittype, unit_mine, pos, rot, scale),
    m_move_flag(false), m_arbitrate_regulator(0), m_command_none(false)
{
    m_brain->armyInit();

    CGameResourceManager::getInstance()->addUnitCounts();
}

CGameUnitGod::~CGameUnitGod()
{
    CGameMap::getInstance()->godDeadEvent();

    CGameResourceManager::getInstance()->subtractUnitCounts();
}

/*======================================================*/
// 컨트롤 업데이트
/*======================================================*/
void CGameUnitGod::updateControl( CEventHandler* p_receiver)
{
    if (m_command_none && p_receiver->isMouseLUp())
    {
        this->setCommandType(com_none);
        m_command_none = false;
    }

    if (this->getCommandType() == com_none)
    {
        if (p_receiver->isMouseROneClick())
        {
            m_brain->addGoalMoveToPosition(p_receiver->getMouseUpGroundPosition());

            m_move_flag = true;
        }
    }

    if (this->getCommandType() == com_attack)
    {
        if (p_receiver->isMouseLOneClick())
        {
            m_brain->addGoalMoveToPosition(p_receiver->getMouseUpGroundPosition());

            m_move_flag = false;

            m_command_none = true;
        }
    }
}

/*======================================================*/
// 행동 중재
/*======================================================*/
void CGameUnitGod::arbitrate()
{
    //
    //
    //
    //
}
