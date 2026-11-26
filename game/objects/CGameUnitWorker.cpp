//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/04/06
//
// File Name : CGameUnitWorker.h
//
// 게임 유닛 일꾼
//
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include <list>
#include "CGameUnitWorker.h"
#include "../ai/Goal_Think.h"
#include "../eventhandle/CEventHandleManager.h"

#include "../ai/God_Messages.h"
#include "../interfaces/CControllerGUI.h"
#include "../interfaces/CMainGameGUI.h"

#include "../ai/Goal_Think.h"
#include "CGameObjectManager.h"
#include "CGameRoom.h"

#include "../attributes/GameResourceManager.h"
#include "../map/CGameMap.h"

/*======================================================*/
// 개별 초기화
/*======================================================*/
void CGameUnitWorker::privateInitialize()
{}

/*======================================================*/
//근거리 공격
/*======================================================*/
bool CGameUnitWorker::shortAttack( CGameUnit* p_target)
{
    return false;
}

CGameUnitWorker::CGameUnitWorker(OwnerType owner, u32 obj_id, u32 objtype,
    const UNIT_RESOURCE* resource, const GAMEUNIT_ATTRIBUTE* attribute,
    UnitTypes unittype, const vector3df& pos /*= vector3df(0.0f, 0.0f, 0.0f)*/
    , const vector3df& rot /*= vector3df(0.0f, 0.0f, 0.0f)*/
    , const vector3df& scale /*= vector3df(1.0f, 1.0f, 1.0f)*/)
    : CGameUnit(owner, objtype, resource, attribute, unittype, unit_mine, pos, rot, scale)
, m_building_complete(false), m_control_room(0), m_build_room(0), m_product_room(0), m_fix_room_to_ground(false), m_network_on_building(false)
{
    CGameResourceManager::getInstance()->addUnitCounts();
}

CGameUnitWorker::~CGameUnitWorker()
{
    CGameResourceManager::getInstance()->subtractUnitCounts();

    CGameMap::getInstance()->workerDeadEvent();

    removeSubGoals();
}

/*======================================================*/
// 빌딩 목표 추가
/*======================================================*/
void CGameUnitWorker::addGoalBuilding( const vector3df& pos)
{
    m_brain->addGoalBuilding(pos);
}

/*======================================================*/
// 빌딩 시작하기
/*======================================================*/
void CGameUnitWorker::buildingStart()
{
    //===========================================================
    //패킷 보내기(네트워크관련)
    //===========================================================

    m_build_room->buildingStart(10);
}

/*======================================================*/
// 컨트롤 종료
/*======================================================*/
void CGameUnitWorker::exitControl()
{
    CControllerGUI::instance()->disableGui();
}

/*======================================================*/
// 컨트롤 시작
/*======================================================*/
void CGameUnitWorker::enterControl()
{
    CControllerGUI::instance()->setWorkerGUI(this);
}

/*======================================================*/
// 컨트롤 업데이트
/*======================================================*/
void CGameUnitWorker::updateControl( CEventHandler* p_receiver)
{
    buildingControl(p_receiver);

    collectingControl(p_receiver);

    if (p_receiver->isMouseROneClick()
        && !m_control_room
        && !m_build_room
        && this->getCommandType() == com_none
        && !p_receiver->isCursorOnGUI())
    {
        m_brain->addGoalMoveToPosition(p_receiver->getMouseUpGroundPosition());
    }
}

/*======================================================*/
// 빌딩용 컨트롤
/*======================================================*/
void CGameUnitWorker::buildingControl( CEventHandler* p_receiver)
{
    if (m_control_room && this->getCommandType() == com_building && !m_fix_room_to_ground)
    {
        m_control_room->followMouse(p_receiver);

        if (m_control_room->isBuildable(p_receiver->getMouseUpGroundPosition()))
        {
            m_control_room->setBuildableColor(true);

            if (p_receiver->isMouseLOneClick() && !p_receiver->isCursorOnGUI())
            {
                m_control_room->removeAndLinkNodes();

                m_build_room = m_control_room;

                this->addGoalBuilding(m_control_room->getFrontPosToBuilding());

                m_control_room->makeBaseGround();
                pushControlCompletedRoom();

                m_fix_room_to_ground = false;
            }

        }
        else
        {
            m_control_room->setBuildableColor(false);
        }

        if (p_receiver->isMouseRUp())
        {
            cancelBuilding();
        }
    }
}

/*======================================================*/
// 빌딩 추가하기
/*======================================================*/
void CGameUnitWorker::addBuilding( BuildingTypes room_type)
{
    if (!m_control_room && !m_build_room)
    {
        m_control_room = this->getObjectManager()->addRoom(object_mine, room_type, 0, this);

        this->getObjectManager()->setControlState(true);

        this->setCommandType(com_building);
    }
}

/*======================================================*/
//빌딩 완료되었는지
/*======================================================*/
const bool CGameUnitWorker::isBuildingCompleted()
{
    return m_build_room->isBuildingCompleted();
}

/*======================================================*/
// 컨트롤 완료된 룸 추가하기
/*======================================================*/
void CGameUnitWorker::pushControlCompletedRoom()
{
    m_build_room = m_control_room;

    m_control_room = 0;

    this->getObjectManager()->setControlState(false);

    this->setCommandType(com_none);

    if (m_build_room && !isBuildingCompleted())
    {
        addGoalBuilding(m_build_room->getFrontPosToBuilding());
    }
}

/*======================================================*/
// 업데이트
/*======================================================*/
void CGameUnitWorker::update(u32 time_ms)
{
    updateMovement(time_ms);

    updateBuildingRoom();

    m_brain->process();
}

/*======================================================*/
// 빌딩완료된 룸 빼기
/*======================================================*/
void CGameUnitWorker::popBuildingCompletedRoom()
{
    m_build_room = 0;
}

/*======================================================*/
// 빌딩 취소
/*======================================================*/
void CGameUnitWorker::cancelBuilding()
{
    m_brain->addGoalMoveToPosition(this->getPos());

    if (m_build_room)
    {
        m_build_room->deleteRoom();
        m_build_room = 0;
    }

    if (m_control_room)
        cancelControl();
}

/*======================================================*/
// 네트워크용
/*======================================================*/
void CGameUnitWorker::onNetworkBuildCommand()
{
    m_control_room->makeBaseGround();
    pushControlCompletedRoom();

    m_fix_room_to_ground = false;
}

/*======================================================*/
// 네트워크용
/*======================================================*/
void CGameUnitWorker::onNetworkBuildStartCommand(u32 seconds)
{
    m_build_room->buildingStart(seconds);
}

/*======================================================*/
// 빌딩 컨트롤 취소하기
/*======================================================*/
void CGameUnitWorker::cancelControl()
{
    if (m_control_room)
    {
        this->getObjectManager()->deleteRequest(m_control_room->getId());
        m_control_room = 0;
    }

    this->setCommandType(com_none);
}

/*======================================================*/
// 컨트롤 룸 가져오기
/*======================================================*/
CGameRoom* CGameUnitWorker::getBackRoom()
{
    return m_build_room;
}

/*======================================================*/
// 하위 목표 삭제
/*======================================================*/
void CGameUnitWorker::removeSubGoals()
{
    m_brain->removeAllSubgoals();
}

/*======================================================*/
// 채집 완료 완료
/*======================================================*/
void CGameUnitWorker::collectingComplete()
{
    //네트워크관련
    this->obtainExp(70);
}

/*======================================================*/
// 채집 컨트롤 처리
/*======================================================*/
void CGameUnitWorker::collectingControl( CEventHandler* p_receiver)
{
    if (this->getCommandType() == com_collection)
    {
        if (p_receiver->isMouseLOneClick())
        {
        }

        else if (p_receiver->isMouseRUp())
        {
            this->setCommandType(com_none);
        }
    }
}

/*======================================================*/
// 워킹 애니메이션
/*======================================================*/
void CGameUnitWorker::workingAnimation(const vector3df& dir)
{
}

/*======================================================*/
// 워킹 애니메이션 끄기
/*======================================================*/
void CGameUnitWorker::offWorkingAnimation()
{
}

/*======================================================*/
// 네트워크용
/*======================================================*/
void CGameUnitWorker::onNetworkBuildStartViewCommand(CGameRoom* p_room)
{
    m_network_on_building = true;

    m_network_on_building_pos = p_room->getFrontPosToBuilding();
}

/*======================================================*/
// 네트워크용
/*======================================================*/
void CGameUnitWorker::onNetworkBuildCompleteViewCommand()
{
    m_network_on_building = false;
    offWorkingAnimation();
}

/*======================================================*/
// 업데이트 빌딩하기
/*======================================================*/
void CGameUnitWorker::updateBuildingRoom()
{
    if (m_network_on_building && getOwnerType() == object_frined)
    {
        if (this->isAtPosition(m_network_on_building_pos))
        {
            setHeading((m_network_on_building_pos - getPos()).normalize());

            workingAnimation(vector3df(0, 0, 0));
        }
    }
}
