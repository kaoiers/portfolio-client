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


CGameRoom::CGameRoom(const OwnerType& owner, unsigned int objtype, unsigned int btype, const ROOM_RESOURCE* res, 
					 const vector3df& pos, 
					 const vector3df& rot /*= vector3df(0.0f, 0.0f, 0.0f)*/, 
					 const vector3df& scale /*= vector3df(1.0f, 1.0f, 1.0f)*/ ) : 
CGameObject(owner, objtype, pos, rot, scale), room_type(btype), m_rResource(res)
,m_uWidth_cells(res->m_iWidth_cells), m_uHeight_cells(res->m_iHeight_cells),
m_pBuildingStep(0),m_NodeIndex(-1),m_bBuildingFinished(false), m_uTotalRoomHp(1000) ,m_uRoomHp(1000), m_pGuardian(0), m_bNetLive(true)
{



}

CGameRoom::CGameRoom(const OwnerType& owner, unsigned int objtype, unsigned int btype, const ROOM_RESOURCE* res )
:CGameObject(owner, objtype), room_type(btype), m_rResource(res) 
,m_uWidth_cells(res->m_iWidth_cells), m_uHeight_cells(res->m_iHeight_cells),

m_pBuildingStep(0), m_NodeIndex(-1),m_bBuildingFinished(false), m_uTotalRoomHp(1000), m_uRoomHp(1000), m_pGuardian(0),m_bNetLive(true)
{
	
}

CGameRoom::~CGameRoom()
{
	if(m_pBuildingStep)
		delete	m_pBuildingStep;

}



/*======================================================*/
// 건물 지어지는 과정 업데이트
/*======================================================*/
void CGameRoom::BuildingUpdate()
{
	if(m_pBuildingStep)
	{
		if(m_pBuildingStep->UpdateBuilding())
		{
			SAFE_DELETE(m_pBuildingStep);

			m_pBuildingStep = 0;

			m_bBuildingFinished = true;			

			GameResource->AddAllResources(m_rResource->NeedGold, 
				m_rResource->NeedWood, 
				m_rResource->NeedStone);

			
			
		}
	}

}


/*======================================================*/
// 건물 폭발 함수
/*======================================================*/
void	CGameRoom::Explosion()
{
	CGameMap *pMap = CGameMap::GetInstance();

	this->getMainGameGUI()->playSound2D( "explosion" );	

}




/*======================================================*/
// 건물이 현재 위치에 지어질 수 있는지
/*======================================================*/
bool CGameRoom::isBuildable(const vector3df& MousePos)
{
	CGameMap *pMap = CGameMap::GetInstance();

	vector2di Curtile = getTile(MousePos);

	Curtile.X -= 1;
	Curtile.Y -= 1;

	for(unsigned int i = 0; i<m_uHeight_cells+2; i++)
	{
		for(unsigned int j = 0; j<m_uWidth_cells+2; j++)
		{
			if( !(pMap->IsNodePresent(Curtile.X + j, Curtile.Y + i)) || 

				!(pMap->IsInUsableArea(Curtile.X + j, Curtile.Y + i))

				/*
				unsigned int(pMap->getNumCellsX()) <= (Curtile.X + j) 
				|| unsigned int(pMap->getNumCellsZ()) <= (Curtile.Y + i)   
				|| (Curtile.X + j) < 0 || (Curtile.Y + i) < 0 */)
			{

				return false;
			}
		}
	}

// 	if( getObjectManager()->IsIntersectWithUnits(GetSceneNode()->getTransformedBoundingBox()) )
// 	{
// 		return false;
// 	}

	m_vFirstIndexTile = getTile(MousePos);

	return true;
}


/*======================================================*/
// 포지션 -> 타일 인덱스
/*======================================================*/
vector2di CGameRoom::getTile( const vector3df& GroundPoint )
{
	CGameMap*	pMap = CGameMap::GetInstance();

	vector2di tile = pMap->getTileFromPos(GroundPoint);

	return tile;
}


/*======================================================*/
// 빌딩 간격 가져오기
/*======================================================*/
vector3df CGameRoom::getBuildingOffset()
{
	vector3df  vOffset;

	return vOffset;

}


/*======================================================*/
// 건물 지어지는 시간정보 가져오기
/*======================================================*/
f32 CGameRoom::getBuildingTime()
{
	return m_rResource->m_iBuildingTime;
}




/*======================================================*/
// 모든 건물해당 노드들 지우기
/*======================================================*/
bool CGameRoom::RemoveAllNodesForDestroy()
{
	CGameMap*	pMap = CGameMap::GetInstance();

 	for(unsigned int i=0; i<m_uHeight_cells; i++)
 	{
 		for(unsigned int j=0; j<m_uWidth_cells; j++)
 		{			
			if(pMap->IsNodePresent(m_vFirstIndexTile.X + j, m_vFirstIndexTile.Y + i))
			{
				pMap->RemoveNode(m_vFirstIndexTile.X + j, m_vFirstIndexTile.Y + i);
			}
 		}
 	}

	return true;
}

/*======================================================*/
// 빌딩 중심위치 가져오기
/*======================================================*/
vector3df CGameRoom::GetCenterPosToBuilding()
{
	vector3df  vCenter;

	return vCenter;	
}


/*======================================================*/
// 1x1 노드 설정하기
/*======================================================*/
void CGameRoom::setOnebyOneNode()
{
	CGameMap* pMap = CGameMap::GetInstance();

	pMap->setOnebyOneBuildingNode(m_vFirstIndexTile.X, m_vFirstIndexTile.Y);
}


/*======================================================*/
// 문노드 연결하기
/*======================================================*/
int CGameRoom::LinkDoorEdges()
{
	CGameMap* pMap = CGameMap::GetInstance();
	vector2di rTile;

	rTile.X  = m_vFirstIndexTile.X + (m_uWidth_cells - 1)/2;
	rTile.Y  = m_vFirstIndexTile.Y + (m_uHeight_cells - 1);
	

	if(isNotWalkableRoom())
	{
		vector2di newTile = m_vFirstIndexTile;

		newTile.Y += 1;

		pMap->AddNodeByTile(m_vFirstIndexTile.X, m_vFirstIndexTile.Y);

		pMap->LinkEdges(m_vFirstIndexTile, newTile);

		m_NodeIndex = pMap->getNodeIndexFromTIle(m_vFirstIndexTile.X, m_vFirstIndexTile.Y);

		return -1;
	}
	
	

	if(m_rResource->doorVector.Y == 1)
	{
		rTile.Y  = m_vFirstIndexTile.Y;
		pMap->AddNodeAndLinkEdges(rTile.X,rTile.Y);
		for(unsigned int i = 0; i<m_uHeight_cells; i++)
		{
			rTile.Y += 1;
			if(pMap->IsNodePresent(rTile.X,rTile.Y))
				return -1;

			pMap->AddNodeAndLinkEdges(rTile.X,rTile.Y);		
		}
	}

	return -1;
}


/*======================================================*/
// 건물 건설시 건물이 마우스 따라다니게
/*======================================================*/
void CGameRoom::FollowMouse( CEventHandler* pReceiver )
{
	vector3df pos;

	CGameMap *pMap = CGameMap::GetInstance();

	pMap->getNodePosFromMousePos(pReceiver->getMouseUpGroundPosition() ,pos);
}

/*======================================================*/
// 지우고 노드연결하기
/*======================================================*/
void CGameRoom::RemoveAndLinkNodes()
{
	
	RemoveAllNodesForDestroy();
	
	LinkDoorEdges();

	AddBoundaryLines();		

}

/*======================================================*/
// 건설할 수 있는지 색 설정하기
/*======================================================*/
void CGameRoom::setBuildableColor( const bool buildable )
{

}

/*======================================================*/
// 건설 시작하기
/*======================================================*/
void CGameRoom::makeBaseGround()
{
	m_pBuildingStep = new CRoomStep(this->m_rResource, this);

}

/*======================================================*/
// 건설 됬는지
/*======================================================*/
const bool	CGameRoom::isBuildingCompleted()
{
	return m_bBuildingFinished;	
}


/*======================================================*/
// 건설 시작되기
/*======================================================*/
void CGameRoom::BuildingStart(const unsigned int seconds)
{
	m_pBuildingStep->StartBuilding(seconds);
}


/*======================================================*/
// 해당 건물 엣지들 복구하기
/*======================================================*/
void CGameRoom::RestoreRoomAreaEdges()
{
	RemoveAllNodesForDestroy();	

	RemoveBoundaryLines();

	CGameMap*	pMap = CGameMap::GetInstance();

	for(unsigned int i=0; i<m_uHeight_cells; i++)
	{
		for(unsigned int j=0; j<m_uWidth_cells; j++)
		{			
			pMap->AddNodeAndLinkEdges(m_vFirstIndexTile.X + j, m_vFirstIndexTile.Y + i);
		}
	}
}


/*======================================================*/
// 래퍼 클래스
/*======================================================*/
void CGameRoom::DeleteRoom()
{
	//if(CAppContext::GetGodGame()->getCurrentGameState() == God_Game::on_game)
	//{
		if(this->getOwnerType() == object_mine)
		{

			//네트워크 관련
			//NetworkPacketSpace::SendDestroyRoomReqPacket(this->GetID());		
		}

		DeleteRoomReal();
}



/*======================================================*/
// 건물 지우기
/*======================================================*/
void CGameRoom::DeleteRoomReal()
{
	

	this->getObjectManager()->DeleteRequest(GetID());

	if(this->getObjectManager()->isControled(this))
	{
		this->getObjectManager()->setController(NULL);

		CControllerGUI::Instance()->DisableGUI();
	}

}


/*======================================================*/
// 건물 경계선 더하기
/*======================================================*/
void CGameRoom::AddBoundaryLines(const bool walkable )
{
	CGameMap*	pMap = CGameMap::GetInstance();

}


/*======================================================*/
// 건물 경계선 지우기
/*======================================================*/
void CGameRoom::RemoveBoundaryLines()
{
	CGameMap*	pMap = CGameMap::GetInstance();
}


/*======================================================*/
// 건물 인덱스 가져오기
/*======================================================*/
int CGameRoom::getRoomNodeIndex()
{
	CGameMap*	pMap = CGameMap::GetInstance(); 
	
	return pMap->getNodeIndexFromTIle(m_vFirstIndexTile.X, m_vFirstIndexTile.Y );

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
vector3df CGameRoom::GetFrontPosToBuilding()
{
	//vector3df maxEdge = this->GetSceneNode()->getTransformedBoundingBox().MaxEdge;
	//vector3df minEdge = this->GetSceneNode()->getTransformedBoundingBox().MinEdge;

	vector3df front(2.0f, 0.0f,100.0f );
	
	return front;
}


/*======================================================*/
// 룸 포지션
/*======================================================*/
vector3df CGameRoom::Pos()
{
	return vector3df(0,0,0);
}



/*======================================================*/
// 건물과 포지션이 교차되는 지점
/*======================================================*/
vector3df CGameRoom::getIntersectPoint( const vector3df& point )
{	
	return point;// (point + (dir* (closestDistance + 50.0f)));
}



/*======================================================*/
// 건물에 데미지 입히기
/*======================================================*/
bool CGameRoom::addDamage( const u32 damage, CGameUnit*  pAttacker )
{
	m_uRoomHp -= damage;
	
	if(!isAlive())
	{

		m_bNetLive = false;

 		CGameUnitEnemy*	pEnemy = dynamic_cast<CGameUnitEnemy*>(pAttacker);
 
		//this->DeleteRoomReal();

		return true;
	}  	

	if(isPossessed())
	{
		//this->getOwnedGUI()->setDamage(m_uRoomHp, m_uTotalRoomHp);
	}

	return false;

	
}


/*======================================================*/
// 건물 지키는 위치 가져오기
/*======================================================*/
vector3df CGameRoom::GetGuardPos()
{
	return (vector3df(300,0,0));

}


/*======================================================*/
// 메시지 처리하기
/*======================================================*/
bool CGameRoom::HandleMessage( const Telegram& msg )
{
	switch(msg.Msg)
	{

	case Msg_EnemyAttackRoom :

		if(isGuardianPresent())
		{
			CGameUnit*	pUnit = reinterpret_cast<CGameUnit* >(msg.ExtraInfo);

			m_pGuardian->GuardRequest(pUnit->Pos());
			
		}

		break;
	}

	return true;
}



/*======================================================*/
// 건물 지정
/*======================================================*/
void CGameRoom::setOnTile( const vector2di& FirstIndexTile )
{

}

void CGameRoom::OnBuildingCompleted()
{
	

}
