//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/04/05
//
// File Name : CGameUnitGod.h
// 
// 게임 유닛 신
// 
//////////////////////////////////////////////////////////////////////////

#ifndef CGAME_UNIT_GOD_H
#define CGAME_UNIT_GOD_H

#include "CGameUnit.h"
#include "../attributes/CGameUnitAttribute.h"

class Regulator;


class CGameUnitGod : public CGameUnit
{
	virtual		void		PrivateInitialize();

	bool					m_bMoveFlag;

	bool					m_bCommandNone;

	Regulator*				m_pArbitrateRegulator;

public :

	virtual		void		control(CEventHandler* pReceiver) {};

	virtual		void		OnCommand() {};

	virtual		void		update(u32 timeMs);

	virtual		bool		short_attack(CGameUnit* pTarget); 

	virtual		bool		long_attack(CGameUnit*	pTarget) { return false; } 

	virtual		void		enter_control();

	virtual		void			update_control(CEventHandler* pReceiver);

	virtual		void			exit_control(){};	


public :

	void					Arbitrate();

	CGameUnitGod(OwnerType owner, u32 obj_id, u32 objtype,
		const UNIT_RESOURCE* resource, 
		const GAMEUNIT_ATTRIBUTE* attribute, 
		UnitTypes unittype, 
		const vector3df& pos = vector3df(0.0f, 0.0f, 0.0f),
		const vector3df& rot  = vector3df(0.0f, 0.0f, 0.0f),
		const vector3df& scale  = vector3df(1.0f, 1.0f, 1.0f));	

	virtual ~CGameUnitGod();
};


#endif