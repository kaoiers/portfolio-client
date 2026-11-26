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
class	cLua;
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

#define	ObjectMap std::map<unsigned int , CGameObject *>

	ObjectMap										m_mapIdCharacter;


#define NodeObjMap std::map<ISceneNode *, CGameObject *>	


	cLua*											m_pLuaState;


#define	 DeletionQue	std::list<unsigned int>

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

	bool				RemoveObject(unsigned int cid);

	void				RemoveAllObjects();

	CGameObject*		GetObjectFromID(unsigned int cid);

	void				DeleteRequest(int idkey);

	void				RemoveDeleteQue();

	bool				IsValidID(unsigned int obj_id);



public:

	void				RegisterObject(CGameObject *obj);

	void				RegisterbySceneNode(CGameObject *obj) {};

	void				RegisterbyID(CGameObject *obj);

	void				UnRegisterObject(CGameObject *obj);

	void				UnRegisterbyID(CGameObject *obj);



public:


	CGameUnitEnemy*		AddUnitEnemy(const OwnerType& owner, unsigned int unit_id, UnitTypes Unittype,
		const vector3df& pos, vector3df& rot = vector3df(0.0f, 0.0f, 0.0f));

	CGameUnitEnemy*		AddUnitEnemy(const vector3df& pos, CEnemyGenerator* pGenerator);


	CGameUnit*			AddUnit(const OwnerType& owner, unsigned int unit_id, UnitTypes Unittype,
		const vector3df& pos, vector3df& rot = vector3df(0.0f, 0.0f, 0.0f));

	CGameUnitArmy*		AddUnitArmy(const OwnerType& owner, UnitTypes Unittype, const vector3df& pos,
		vector3df& rot = vector3df(0.0f, 0.0f, 0.0f));


	CGameRoom*			AddRoom(const OwnerType& owner, const BuildingTypes Roomtype, unsigned int RoomID = 0, CGameUnit* pWorker = 0);

	CGameRoom*			AddRoomOnTile(const OwnerType& owner, const BuildingTypes Roomtype, const vector2di& tile, unsigned int RoomID = 0);



	CGameRoomGod*		AddGodRoom(const OwnerType& owner, const vector2di& tilePos);

	CTerrainObject*		AddTerrainMap(const OwnerType& owner, const int& cx, const int& cz, const float& sx, const float& sz) { return nullptr; };


public :

	bool				control(CEventHandler *pReceiver);

	void				update();

	void				render();

	cLua*				getLua();

	bool				drop();

	void				setController(IBaseController* controller);

	bool				isControled(CGameObject* obj) const;

	bool				isOnControlState();

	void				setControlState(const bool on = true);

public :

	void				DispatchMsg(const Telegram& msg);

	bool				Lua_Init( cLua *lua, const char *luafilename );

	bool				Init();

	
	void				RemoveUnitFromSet(CGameUnit* pUnit);

	void				RemoveRoomFromSet(CGameRoom* pRoom);

	void				ClearMemoryFromObject(CGameObject* pObj);

	void				ClearTargetFromObject( CGameObject* pObj );
};





#endif