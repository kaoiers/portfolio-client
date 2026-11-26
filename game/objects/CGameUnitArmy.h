//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/05/17
//
// File Name : CGameUnitArmy.h
// 
// 게임 적군 클래스
// 
//////////////////////////////////////////////////////////////////////////

#ifndef GAME_UNIT_ARMY
#define GAME_UNIT_ARMY

#include "CGameUnit.h"

class CGameRoomWaiting;
class CGameRoom;

class CGameUnitArmy : public CGameUnit
{
	

	CGameRoom*				m_pGuardRoom;


	bool					m_bCommandNone;

	bool					m_bGoingRoom;

public :

	void					Arbitrate();
	void					GuardRequest(const vector3df& pos);



public :

	virtual		void		update(const u32& timeMs);

	virtual		bool		short_attack(CGameUnit* pTarget); 

	virtual		bool		long_attack(CGameUnit*	pTarget) { return false; } 


	virtual void			enter_control();

	virtual void			update_control(CEventHandler* pReceiver);

	virtual void			exit_control();	


public :

	CGameUnitArmy(const OwnerType& owner,unsigned int obj_id, unsigned int objtype, 
		const UNIT_RESOURCE* resource, 
		const GAMEUNIT_ATTRIBUTE* attribute, 
		UnitTypes unittype, 
		const vector3df& pos = vector3df(0.0f, 0.0f, 0.0f),
		const vector3df& rot  = vector3df(0.0f, 0.0f, 0.0f),
		const vector3df& scale  = vector3df(1.0f, 1.0f, 1.0f));	

	CGameUnitArmy(const OwnerType& owner,unsigned int objtype, 
		const UNIT_RESOURCE* resource, 
		const GAMEUNIT_ATTRIBUTE* attribute, 
		UnitTypes unittype, 
		const vector3df& pos = vector3df(0.0f, 0.0f, 0.0f),
		const vector3df& rot  = vector3df(0.0f, 0.0f, 0.0f),
		const vector3df& scale  = vector3df(1.0f, 1.0f, 1.0f));	

	virtual ~CGameUnitArmy();

	
};




#endif