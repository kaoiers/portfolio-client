//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/04/05
//
// File Name : CGameRoom.cpp
//
// 건물 기본 클래스
//
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "CGameRoom.h"
#include "../map/CGameMap.h"
#include "../eventhandle/CEventHandleManager.h"
#include "CGameUnitWorker.h"
#include "CGameObjectManager.h"
#include "CRoomStep.h"
#include "../attributes/GameResourceManager.h"
#include "../interfaces/CControllerGUI.h"
#include "../shader/CLightEffectManager.h"
#include "../ai/God_Messages.h"
#include "../ai/MessageDispatcher.h"
#include "CGameUnitArmy.h"
#include "../interfaces/CMainGameGUI.h"
#include "../interfaces/IGameGUI.h"
#include "CGameUnitEnemy.h"
#include "../God_Game.h"

CGameRoom::CGameRoom(OwnerType owner, u32 objtype, u32 btype, const ROOM_RESOURCE* res,
    const vector3df& pos,
    const vector3df& rot /*= vector3df(0.0f, 0.0f, 0.0f)*/,
    const vector3df& scale /*= vector3df(1.0f, 1.0f, 1.0f)*/) :
    CGameObject(owner, objtype, pos, rot, scale), room_type(btype), m_resource(res)
, m_room_width_cells(res->m_width_cells), m_room_height_cells(res->m_height_cells),
    m_building_step(nullptr), m_node_index(-1), m_building_finished(false), m_total_room_hp(1000), m_room_hp(1000), m_guardian(0), m_net_live(true)
{
}

CGameRoom::CGameRoom(OwnerType owner, u32 objtype, u32 btype, const ROOM_RESOURCE* res)
    :CGameObject(owner, objtype), room_type(btype), m_resource(res)
, m_room_width_cells(res->m_width_cells), m_room_height_cells(res->m_height_cells),

    m_building_step(nullptr), m_node_index(-1), m_building_finished(false), m_total_room_hp(1000), m_room_hp(1000), m_guardian(0), m_net_live(true)
{
}

CGameRoom::~CGameRoom()
{
    m_building_step.reset();
}

/*======================================================*/
// 건물 지어지는 과정 업데이트
/*======================================================*/
void CGameRoom::buildingUpdate()
{
    if (m_building_step)
    {
        if (m_building_step->updateBuilding())
        {
            m_building_step.reset();

            m_building_finished = true;

            GameResource->addAllResources(m_resource->need_gold,
                m_resource->need_wood,
                m_resource->need_stone);
        }
    }
}

/*======================================================*/
// 건물 폭발 함수
/*======================================================*/
void CGameRoom::explosion()
{
    CGameMap *p_map = CGameMap::getInstance();

    this->getMainGameGUI()->playSound2D( "explosion");
}

/*======================================================*/
// 건물이 현재 위치에 지어질 수 있는지
/*======================================================*/
bool CGameRoom::isBuildable(const vector3df& mouse_pos)
{
    CGameMap *p_map = CGameMap::getInstance();

    vector2di current_tile = getTile(mouse_pos);

    current_tile.X -= 1;
    current_tile.Y -= 1;

    for (u32 i = 0; i<m_room_height_cells+2; i++)
    {
        for (u32 j = 0; j<m_room_width_cells+2; j++)
        {
            if ( !(p_map->isNodePresent(current_tile.X + j, current_tile.Y + i)) ||

                !(p_map->isInUsableArea(current_tile.X + j, current_tile.Y + i))

            /*
            u32(pMap->getNumCellsX()) <= (Curtile.X + j)
            || u32(pMap->getNumCellsZ()) <= (Curtile.Y + i)
            || (Curtile.X + j) < 0 || (Curtile.Y + i) < 0 */)
                {
                    return false;
            }
        }
    }

        m_first_index_tile = getTile(mouse_pos);

        return true;
}

/*======================================================*/
// 포지션 -> 타일 인덱스
/*======================================================*/
    vector2di CGameRoom::getTile( const vector3df& ground_point)
    {
        CGameMap* p_map = CGameMap::getInstance();

        vector2di tile = p_map->getTileFromPos(ground_point);

        return tile;
}

/*======================================================*/
// 빌딩 간격 가져오기
/*======================================================*/
    vector3df CGameRoom::getBuildingOffset()
    {
        vector3df v_offset;

        return v_offset;
}

/*======================================================*/
// 건물 지어지는 시간정보 가져오기
/*======================================================*/
    f32 CGameRoom::getBuildingTime()
    {
        return m_resource->m_building_time;
}

/*======================================================*/
// 모든 건물해당 노드들 지우기
/*======================================================*/
    bool CGameRoom::removeAllNodesForDestroy()
    {
        CGameMap* p_map = CGameMap::getInstance();

        for (u32 i=0; i<m_room_height_cells; i++)
        {
            for (u32 j=0; j<m_room_width_cells; j++)
            {
                if (p_map->isNodePresent(m_first_index_tile.X + j, m_first_index_tile.Y + i))
                {
                    p_map->removeNode(m_first_index_tile.X + j, m_first_index_tile.Y + i);
            }
        }
    }

        return true;
}

/*======================================================*/
// 빌딩 중심위치 가져오기
/*======================================================*/
    vector3df CGameRoom::getCenterPosToBuilding()
    {
        vector3df v_center;

        return v_center;
}

/*======================================================*/
// 1x1 노드 설정하기
/*======================================================*/
    void CGameRoom::setOnebyOneNode()
    {
        CGameMap* p_map = CGameMap::getInstance();

        p_map->setOnebyOneBuildingNode(m_first_index_tile.X, m_first_index_tile.Y);
}

/*======================================================*/
// 문노드 연결하기
/*======================================================*/
    s32 CGameRoom::linkDoorEdges()
    {
        CGameMap* p_map = CGameMap::getInstance();
        vector2di r_tile;

        r_tile.X = m_first_index_tile.X + (m_room_width_cells - 1)/2;
        r_tile.Y = m_first_index_tile.Y + (m_room_height_cells - 1);

        if (isNotWalkableRoom())
        {
            vector2di new_tile = m_first_index_tile;

            new_tile.Y += 1;

            p_map->addNodeByTile(m_first_index_tile.X, m_first_index_tile.Y);

            p_map->linkEdges(m_first_index_tile, new_tile);

            m_node_index = p_map->getNodeIndexFromTile(m_first_index_tile.X, m_first_index_tile.Y);

            return -1;
    }

        if (m_resource->door_vector.Y == 1)
        {
            r_tile.Y = m_first_index_tile.Y;
            p_map->addNodeAndLinkEdges(r_tile.X, r_tile.Y);
            for (u32 i = 0; i<m_room_height_cells; i++)
            {
                r_tile.Y += 1;
                if (p_map->isNodePresent(r_tile.X, r_tile.Y))
                    return -1;

                p_map->addNodeAndLinkEdges(r_tile.X, r_tile.Y);
        }
    }

        return -1;
}

/*======================================================*/
// 건물 건설시 건물이 마우스 따라다니게
/*======================================================*/
    void CGameRoom::followMouse( CEventHandler* p_receiver)
    {
        vector3df pos;

        CGameMap *p_map = CGameMap::getInstance();

        p_map->getNodePosFromMousePos(p_receiver->getMouseUpGroundPosition(), pos);
}

/*======================================================*/
// 지우고 노드연결하기
/*======================================================*/
    void CGameRoom::removeAndLinkNodes()
    {
        removeAllNodesForDestroy();

        linkDoorEdges();

        addBoundaryLines();
}

/*======================================================*/
// 건설할 수 있는지 색 설정하기
/*======================================================*/
    void CGameRoom::setBuildableColor( const bool buildable)
    {
}

/*======================================================*/
// 건설 시작하기
/*======================================================*/
    void CGameRoom::makeBaseGround()
    {
        m_building_step = std::make_unique<CRoomStep>(this->m_resource, this);
}

/*======================================================*/
// 건설 됬는지
/*======================================================*/
    const bool CGameRoom::isBuildingCompleted()
    {
        return m_building_finished;
}

/*======================================================*/
// 건설 시작되기
/*======================================================*/
    void CGameRoom::buildingStart(const u32 seconds)
    {
        m_building_step->startBuilding(seconds);
}

/*======================================================*/
// 해당 건물 엣지들 복구하기
/*======================================================*/
    void CGameRoom::restoreRoomAreaEdges()
    {
        removeAllNodesForDestroy();

        removeBoundaryLines();

        CGameMap* p_map = CGameMap::getInstance();

        for (u32 i=0; i<m_room_height_cells; i++)
        {
            for (u32 j=0; j<m_room_width_cells; j++)
            {
                p_map->addNodeAndLinkEdges(m_first_index_tile.X + j, m_first_index_tile.Y + i);
        }
    }
}

/*======================================================*/
// 래퍼 클래스
/*======================================================*/
    void CGameRoom::deleteRoom()
    {
        if (this->getOwnerType() == object_mine)
        {
        //네트워크 관련
    }

        deleteRoomReal();
}

/*======================================================*/
// 건물 지우기
/*======================================================*/
    void CGameRoom::deleteRoomReal()
    {
        this->getObjectManager()->deleteRequest(getId());

        if (this->getObjectManager()->isControlled(this))
        {
            this->getObjectManager()->setController(nullptr);

            CControllerGUI::instance()->disableGui();
    }
}

/*======================================================*/
// 건물 경계선 더하기
/*======================================================*/
    void CGameRoom::addBoundaryLines(const bool walkable)
    {
        CGameMap* p_map = CGameMap::getInstance();
}

/*======================================================*/
// 건물 경계선 지우기
/*======================================================*/
    void CGameRoom::removeBoundaryLines()
    {
        CGameMap* p_map = CGameMap::getInstance();
}

/*======================================================*/
// 건물 인덱스 가져오기
/*======================================================*/
    s32 CGameRoom::getRoomNodeIndex()
    {
        CGameMap* p_map = CGameMap::getInstance();

        return p_map->getNodeIndexFromTile(m_first_index_tile.X, m_first_index_tile.Y);
}

/*======================================================*/
// 이동할수 없는 룸인지
/*======================================================*/
    bool CGameRoom::isNotWalkableRoom()
    {
        return (room_type == BUILDING_FARM ||
        room_type == BUILDING_GOLD ||
        room_type == BUILDING_WOOD||
        room_type == BUILDING_TOWER ||
        room_type == BUILDING_FRIEND);
}

/*======================================================*/
// 게임 리소스 인스턴트 가져오기
/*======================================================*/
    CGameResourceManager* CGameRoom::getGameResource()
    {
        return GameResource;
}

/*======================================================*/
// 생산룸인지
/*======================================================*/
    bool CGameRoom::isProductRoom()
    {
        return (room_type == BUILDING_FARM ||
        room_type == BUILDING_GOLD ||
        room_type == BUILDING_WOOD ||
        room_type == BUILDING_FRIEND);
}

/*======================================================*/
// 빌딩을 위한 위치 가져오기
/*======================================================*/
    vector3df CGameRoom::getFrontPosToBuilding()
    {
        vector3df front(2.0f, 0.0f, 100.0f);

        return front;
}

/*======================================================*/
// 룸 포지션
/*======================================================*/
    vector3df CGameRoom::getPos()
    {
        return vector3df(0, 0, 0);
}

/*======================================================*/
// 건물과 포지션이 교차되는 지점
/*======================================================*/
    vector3df CGameRoom::getIntersectPoint( const vector3df& point)
    {
        return point;// (point + (dir* (closestDistance + 50.0f)));
}

/*======================================================*/
// 건물에 데미지 입히기
/*======================================================*/
    bool CGameRoom::addDamage( const u32 damage, CGameUnit* p_attacker)
    {
        m_room_hp -= damage;

        if (!isAlive())
        {
            m_net_live = false;

            CGameUnitEnemy* p_enemy = dynamic_cast<CGameUnitEnemy*>(p_attacker);

            return true;
    }

        if (isPossessed())
        {
    }

        return false;
}

/*======================================================*/
// 건물 지키는 위치 가져오기
/*======================================================*/
    vector3df CGameRoom::getGuardPos()
    {
        return (vector3df(300, 0, 0));
}

/*======================================================*/
// 메시지 처리하기
/*======================================================*/
    bool CGameRoom::handleMessage( const Telegram& msg)
    {
        switch (msg.msg)
        {
    case Msg_EnemyAttackRoom :

            if (isGuardianPresent())
            {
                CGameUnit* p_unit = reinterpret_cast<CGameUnit* >(msg.extra_info);

                m_guardian->guardRequest(p_unit->getPos());
        }

            break;
    }

        return true;
}

/*======================================================*/
// 건물 지정
/*======================================================*/
    void CGameRoom::setOnTile( const vector2di& first_index_tile)
    {
}

    void CGameRoom::onBuildingCompleted()
    {
}
