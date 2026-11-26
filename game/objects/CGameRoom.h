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


#include "CGameObject.h"
#include "IBaseController.h"

class CGameUnitWorker;
class CRoomStep;
class CGameResourceManager;
class CGameUnitArmy;
class CGameUnit;

class CGameRoom : public CGameObject , public IBaseController
{
	
	const ROOM_RESOURCE*					m_rResource;
	u32							m_uWidth_cells, m_uHeight_cells;
	CRoomStep*								m_pBuildingStep;
	u32							m_uTotalRoomHp;
	u32										m_uRoomHp;
	CGameUnitArmy*							m_pGuardian;
	bool									m_bNetLive;
	u32							room_type;

protected :

	bool									m_bBuildingFinished;
	vector2di								m_vFirstIndexTile;
	s32										m_NodeIndex;


public :

	u32					getRoomType() { return room_type; }

	CGameResourceManager*					getGameResource();
	bool									isProductRoom();

	bool									isAlive() {return  (m_uRoomHp > 0); }
	bool									addDamage(const u32 damage, CGameUnit* pAttacker);
	const u32								getRoomHp() { return m_uRoomHp;}
	const u32								getTotalRoomHP() { return m_uTotalRoomHp; }

	void									setGuardian(CGameUnitArmy* pUnit) { m_pGuardian = pUnit; } 
	CGameUnitArmy*							getGuardian() { return m_pGuardian; }
	void									NullifyGuardian() { m_pGuardian = 0; };
	bool									isGuardianPresent() const { return (m_pGuardian != NULL); }
	void									setNetLive(const bool on) { m_bNetLive = on; }
	bool									getNetLive() {return m_bNetLive;}
 


public :

	CGameRoom(OwnerType owner, u32 objtype,  u32 btype, const ROOM_RESOURCE* res,
		const vector3df& pos,
		const vector3df& rot  = vector3df(0.0f, 0.0f, 0.0f),
		const vector3df& scale  = vector3df(1.0f, 1.0f, 1.0f));	


	CGameRoom(OwnerType owner, u32 objtype,  u32 btype, const ROOM_RESOURCE* res);
	virtual		~CGameRoom();


	bool									HandleMessage(const Telegram& msg);

public :

	void									setOnebyOneNode();
	void									setOnTile(const vector2di& FirstIndexTile);
	const vector2di&						getFirstTile() {return m_vFirstIndexTile; }


public :

	void									BuildingUpdate();
	bool									isNotWalkableRoom();
	void									setBuildingCompleted() {m_bBuildingFinished = true;}
	vector3df								Pos();
	vector3df								getIntersectPoint(const vector3df& point);
	void									OnBuildingCompleted();

public :

	
	bool									isBuildable(const vector3df& MousePos);
	f32										getBuildingTime();
	
	void									BuildingStart(const u32 seconds);

	void									FollowMouse(CEventHandler* pReceiver);
	void									RemoveAndLinkNodes();
	void									setBuildableColor(const bool buildable = true);
	
	vector3df								GetCenterPosToBuilding();
	vector3df								GetFrontPosToBuilding();
	vector3df								GetGuardPos();


	void									makeBaseGround();
	const bool								isBuildingCompleted();
	void									RestoreRoomAreaEdges();
	void									DeleteRoom();
	void									DeleteRoomReal();
	s32										getRoomNodeIndex();
	bool									RemoveAllNodesForDestroy();
	void									Explosion();

protected :

	vector2di								getTile( const vector3df& GroundPoint );
	vector3df								getBuildingOffset();
	void									RemoveBoundaryLines();
	void									AddBoundaryLines(const bool walkable = true);
	s32										LinkDoorEdges();

};











#endif