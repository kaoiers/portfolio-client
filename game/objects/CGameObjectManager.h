//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/02/26
//
// File Name : CGameObjectManager.h
// 
// 게임 오브젝트 관리
// 
//////////////////////////////////////////////////////////////////////////


#ifndef GAME_OBJECT_MANAGER_H
#define GAME_OBJECT_MANAGER_H

#include <map>
#include <list>

#include "CObjectListSet.h"
#include "EnumObjectType.h"



class	CGameObject;
struct  CAnimation_Info;
class   CBuildingBlock;
class	CBuildingObject;

class	CGameRoom;
class	CGameRoomGod;


class	CGameUnit;
class   CGameUnitArmy;
class	CGameUnitEnemy;


class   CEventHandler;
class	CAppContext;
class	CTerrainObject;
class	IBaseController;
class	CObjectSelector;
class	CEnemyGenerator;
struct	Telegram;





#define EntityMgr CGameObjectManager::GetInstance()


class CObjectController;



class CGameObjectManager
{

#define	ObjectMap std::map<u32 , CGameObject *>

	ObjectMap										m_mapIdCharacter;


#define NodeObjMap std::map<ISceneNode *, CGameObject *>	



#define	 DeletionQue	std::list<u32>

	DeletionQue										m_deleteque;

	std::vector<CGameUnit* >						m_UnitSet;

	std::vector<CGameRoom* >						m_RoomSet;

	CObjectController*								m_pObjectController;




private:
	static CGameObjectManager * m_pInstance;

public:
	static CGameObjectManager* GetInstance();

public:

	CGameObjectManager();

	~CGameObjectManager();

	ObjectMap			getObjIDMap() { return m_mapIdCharacter; }

	bool				RemoveObject(u32 cid);

	void				RemoveAllObjects();

	CGameObject*		GetObjectFromID(u32 cid);

	void				DeleteRequest(s32 idkey);

	void				RemoveDeleteQue();

	bool				IsValidID(u32 obj_id);



public:

	void				RegisterObject(CGameObject *obj);

	void				RegisterbySceneNode(CGameObject *obj) {};

	void				RegisterbyID(CGameObject *obj);

	void				UnRegisterObject(CGameObject *obj);

	void				UnRegisterbyID(CGameObject *obj);



public:


	CGameUnitEnemy*		AddUnitEnemy(OwnerType owner, u32 unit_id, UnitTypes Unittype,
		const vector3df& pos, vector3df& rot = vector3df(0.0f, 0.0f, 0.0f));

	CGameUnitEnemy*		AddUnitEnemy(const vector3df& pos, CEnemyGenerator* pGenerator);


	CGameUnit*			AddUnit(OwnerType owner, u32 unit_id, UnitTypes Unittype,
		const vector3df& pos, vector3df& rot = vector3df(0.0f, 0.0f, 0.0f));

	CGameUnitArmy*		AddUnitArmy(OwnerType owner, UnitTypes Unittype, const vector3df& pos,
		vector3df& rot = vector3df(0.0f, 0.0f, 0.0f));


	CGameRoom*			AddRoom(OwnerType owner, const BuildingTypes Roomtype, u32 RoomID = 0, CGameUnit* pWorker = 0);

	CGameRoom*			AddRoomOnTile(OwnerType owner, const BuildingTypes Roomtype, const vector2di& tile, u32 RoomID = 0);



	CGameRoomGod*		AddGodRoom(OwnerType owner, const vector2di& tilePos);

	CTerrainObject*		AddTerrainMap(OwnerType owner, s32 cx, s32 cz, f32 sx, f32 sz) { return nullptr; };


public :

	bool				control(CEventHandler *pReceiver);

	void				update();

	void				render();

	bool				drop();

	void				setController(IBaseController* controller);

	bool				isControled(CGameObject* obj) const;

	bool				isOnControlState();

	void				setControlState(const bool on = true);

public :

	void				DispatchMsg(const Telegram& msg);

	bool				Init();

	
	void				RemoveUnitFromSet(CGameUnit* pUnit);

	void				RemoveRoomFromSet(CGameRoom* pRoom);

	void				ClearMemoryFromObject(CGameObject* pObj);

	void				ClearTargetFromObject( CGameObject* pObj );
};





#endif