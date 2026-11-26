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
#include "../CAppcontext.h"
#include "../shader/CLightEffectManager.h"
#include "../map/CGameMap.h"

void addEarthMesh(CGameRoom* p_room);
void addTorchFireParticle(CGameRoom* p_room,  const vector3df& pos);


CGameRoomGod::CGameRoomGod(OwnerType owner, u32 objtype, u32 btype, const ROOM_RESOURCE* res, const vector2di& tile_pos,
						   const vector3df& pos, 
						   const vector3df& rot /*= vector3df(0.0f, 0.0f, 0.0f)*/, 
						   const vector3df& scale /*= vector3df(1.0f, 1.0f, 1.0f)*/ )
						    : CGameRoom(owner, objtype, btype, res, pos, rot, scale) 
{
	initialize(tile_pos);
}
CGameRoomGod::CGameRoomGod(OwnerType owner, u32 objtype, u32 btype, const ROOM_RESOURCE* res, const vector2di& tile_pos)
: CGameRoom(owner, objtype, btype, res)
{
	initialize(tile_pos);
}

/*======================================================*/
// 초기화
/*======================================================*/
void CGameRoomGod::initialize( const vector2di& tile_pos )
{
	addTorchFireParticle(this, vector3df(-180,200,-380));
	addTorchFireParticle(this, vector3df(190,200,-380));
	addEarthMesh(this);


//  	//m_NodeIndex	=  CGameMap::GetInstance()->getNodeIndexFromTIle(m_vFirstIndexTile.X, m_vFirstIndexTile.Y );
//  
// 
// 		- getBuildingOffset());
// 
// 	//this->GetSceneNode()->render();
// 
// 
// 	//ShaderEffect->removeNode(this->GetSceneNode());
// 	//ShaderEffect->ApplyEffectToNode(this->GetSceneNode());
// 
// 	


	
}


/*======================================================*/
// 컨트롤 초기화
/*======================================================*/
void CGameRoomGod::enterControl()
{

}


/*======================================================*/
// 컨트롤 업데이트
/*======================================================*/
void CGameRoomGod::updateControl( CEventHandler* p_receiver )
{

}


/*======================================================*/
// 컨트롤 종료
/*======================================================*/
void CGameRoomGod::exitControl()
{

}


/*======================================================*/
// 업데이트
/*======================================================*/
void CGameRoomGod::update( const u32 time_ms )
{
	buildingUpdate();


}













void addEarthMesh(CGameRoom* p_room)
{	
	
	

}










void addTorchFireParticle(CGameRoom* p_room,  const vector3df& pos)
{

}
