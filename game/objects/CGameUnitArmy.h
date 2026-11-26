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
	

	CGameRoom*				m_guard_room;


	bool					m_command_none;

	bool					m_going_room;

public :

	void					arbitrate();
	void					guardRequest(const vector3df& pos);



public :

	virtual		void		update(u32 time_ms);

	virtual		bool		shortAttack(CGameUnit* p_target); 

	virtual		bool		longAttack(CGameUnit*	p_target) { return false; } 


	virtual void			enterControl();

	virtual void			updateControl(CEventHandler* p_receiver);

	virtual void			exitControl();	


public :

	CGameUnitArmy(OwnerType owner,u32 obj_id, u32 objtype,
		const UNIT_RESOURCE* resource, 
		const GAMEUNIT_ATTRIBUTE* attribute, 
		UnitTypes unittype, 
		const vector3df& pos = vector3df(0.0f, 0.0f, 0.0f),
		const vector3df& rot  = vector3df(0.0f, 0.0f, 0.0f),
		const vector3df& scale  = vector3df(1.0f, 1.0f, 1.0f));	

	CGameUnitArmy(OwnerType owner,u32 objtype,
		const UNIT_RESOURCE* resource, 
		const GAMEUNIT_ATTRIBUTE* attribute, 
		UnitTypes unittype, 
		const vector3df& pos = vector3df(0.0f, 0.0f, 0.0f),
		const vector3df& rot  = vector3df(0.0f, 0.0f, 0.0f),
		const vector3df& scale  = vector3df(1.0f, 1.0f, 1.0f));	

	virtual ~CGameUnitArmy();

	
};




#endif