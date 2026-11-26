//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/04/04
//
// File Name : CGameRoomGod.cpp
// 
// 신수방 클래스
// 
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "CGameRoomGod.h"
#include "../CAppContext.h"
#include "../shader/CLightEffectManager.h"
#include "../map/CGameMap.h"

void AddEarthMesh(CGameRoom* pRoom);
void AddTorchFireParticle(CGameRoom* pRoom,  const vector3df& pos);


CGameRoomGod::CGameRoomGod(const OwnerType& owner, unsigned int objtype, unsigned int btype, const ROOM_RESOURCE* res, const vector2di& TilePos, 
						   const vector3df& pos, 
						   const vector3df& rot /*= vector3df(0.0f, 0.0f, 0.0f)*/, 
						   const vector3df& scale /*= vector3df(1.0f, 1.0f, 1.0f)*/ )
						    : CGameRoom(owner, objtype, btype, res, pos, rot, scale) 
{
	initialize(TilePos);
}
CGameRoomGod::CGameRoomGod(const OwnerType& owner, unsigned int objtype, unsigned int btype, const ROOM_RESOURCE* res, const vector2di& TilePos)
: CGameRoom(owner, objtype, btype, res)
{
	initialize(TilePos);
}

/*======================================================*/
// 초기화
/*======================================================*/
void CGameRoomGod::initialize( const vector2di& TilePos )
{
	AddTorchFireParticle(this, vector3df(-180,200,-380));
	AddTorchFireParticle(this, vector3df(190,200,-380));
	AddEarthMesh(this);


//  	m_vFirstIndexTile = TilePos;
//  	//m_NodeIndex	=  CGameMap::GetInstance()->getNodeIndexFromTIle(m_vFirstIndexTile.X, m_vFirstIndexTile.Y );
//  
// 
// 	this->GetSceneNode()->setPosition(
// 		CGameMap::GetInstance()->getNodePos(m_vFirstIndexTile.X, m_vFirstIndexTile.Y)
// 		- getBuildingOffset());
// 
// 	this->GetSceneNode()->OnRegisterSceneNode();
// 	this->GetSceneNode()->OnAnimate((u32)(0));
// 	//this->GetSceneNode()->render();
// 
// 	RemoveAndLinkNodes();
// 
// 	//ShaderEffect->removeNode(this->GetSceneNode());
// 	//ShaderEffect->ApplyEffectToNode(this->GetSceneNode());
// 
// 	m_bBuildingFinished = true;
// 	
// 	this->GetSceneNode()->setID(IDFlag_IsBuildingPickable);


	
}


/*======================================================*/
// 컨트롤 초기화
/*======================================================*/
void CGameRoomGod::enter_control()
{

}


/*======================================================*/
// 컨트롤 업데이트
/*======================================================*/
void CGameRoomGod::update_control( CEventHandler* pReceiver )
{

}


/*======================================================*/
// 컨트롤 종료
/*======================================================*/
void CGameRoomGod::exit_control()
{

}


/*======================================================*/
// 업데이트
/*======================================================*/
void CGameRoomGod::update( const u32 timeMs )
{
	BuildingUpdate();

	//printf("%0.2f, %0.2f\n", this->GetSceneNode()->getTransformedBoundingBox().MaxEdge.X, this->GetSceneNode()->getTransformedBoundingBox().MaxEdge.Z );
	//printf("%0.2f, %0.2f\n\n", this->GetSceneNode()->getTransformedBoundingBox().MinEdge.X, this->GetSceneNode()->getTransformedBoundingBox().MinEdge.Z );

}













void AddEarthMesh(CGameRoom* pRoom)
{	
	
	

}










void AddTorchFireParticle(CGameRoom* pRoom,  const vector3df& pos)
{
	//ISceneNode* parent=0, s32 id=-1,
	//		const vector3df& position = vector3df(0,0,0),

}
