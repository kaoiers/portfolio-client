//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/04/06
//
// File Name : CGameUnitWorker.h
// 
// 게임 유닛 일꾼
// 
//////////////////////////////////////////////////////////////////////////

#ifndef CGAME_UNIT_WORKER_H
#define CGAME_UNIT_WORKER_H

#include "CGameUnit.h"
#include "../attributes/CGameUnitAttribute.h"


class CGameRoom;
class CGameRoomProductBase;


class CGameUnitWorker : public CGameUnit
{
	virtual		void		PrivateInitialize();

	bool					m_bBuildingComplete;

	CGameRoom*				m_pControlRoom;

	CGameRoom*				m_pBuildRoom;

	CGameRoomProductBase*	m_pProductRoom;

	bool					m_bFixRoomToGround;


	bool					m_bNetworkOnBuilding;
	vector3df	m_vNetworkOnBuildingPos;



	void					BuildingControl(CEventHandler* pReceiver);
	void					CollectingControl(CEventHandler* pReceiver);

	

public :



	virtual		void		control(CEventHandler* pReceiver) {};
	virtual		void		OnCommand() {};
	virtual		void		update(const u32& timeMs);
	virtual		bool		short_attack(CGameUnit* pTarget); 
	virtual		bool		long_attack(CGameUnit*	pTarget) { return false; } 
	virtual		void		enter_control();
	virtual		void		update_control(CEventHandler* pReceiver);
	virtual		void		exit_control();	



	CGameUnitWorker(const OwnerType& owner, unsigned int obj_id, unsigned int objtype, 
		const UNIT_RESOURCE* resource, 
		const GAMEUNIT_ATTRIBUTE* attribute, 
		UnitTypes unittype, 
		const vector3df& pos = vector3df(0.0f, 0.0f, 0.0f),
		const vector3df& rot  = vector3df(0.0f, 0.0f, 0.0f),
		const vector3df& scale  = vector3df(1.0f, 1.0f, 1.0f));	

	virtual ~CGameUnitWorker();


public :

	void					AddGoal_Building(const vector3df& pos);
	const	bool			isBuildingComplete() { return m_bBuildingComplete; }
	void					setBuildingComplete(const bool comp = true) {m_bBuildingComplete = comp; }
	void					RemoveSubGoals();
	
	void					AddBuilding(const BuildingTypes&  roomType);
	
	
	const	bool			isBuildingCompleted() ;
	void					BuildingStart();
	void					UpdateBuildingRoom();	


	CGameRoom*				getCurrentBuildingRoom() { return m_pBuildRoom; }
	CGameRoom*				getBackRoom();
	
	void					setCurrentBuildingRoom(CGameRoom* pRoom) {m_pBuildRoom = pRoom;  }
	void					setCurrentControlRoom(CGameRoom* pRoom) {m_pControlRoom = pRoom;  }

	bool					getCurrentControlRoom() { return (m_pControlRoom != 0); }
	void					WorkingAnimation(const vector3df& dir);
	void					OffWorkingAnimation();

	void					PushControlCompletedRoom();
	void					PopBuildingCompletedRoom();
	
	void					CancelBuilding();
	void					CancelControl();

	void					CollectingComplete();


public :
	
	void					OnNetWorkBuildCommand();
	void					OnNetWorkBuildStartCommand(const unsigned int& seconds);
	void					OnNetWorkBuildStartViewCommand(CGameRoom*	pRoom);
	void					OnNetWorkBuildCompleteViewCommand();
	

};


#endif