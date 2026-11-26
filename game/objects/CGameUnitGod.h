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
	virtual		void		privateInitialize();

	bool					m_move_flag;

	bool					m_command_none;

	Regulator*				m_arbitrate_regulator;

public :

	virtual		void		control(CEventHandler* p_receiver) {};

	virtual		void		onCommand() {};

	virtual		void		update(u32 time_ms);

	virtual		bool		shortAttack(CGameUnit* p_target); 

	virtual		bool		longAttack(CGameUnit*	p_target) { return false; } 

	virtual		void		enterControl();

	virtual		void			updateControl(CEventHandler* p_receiver);

	virtual		void			exitControl(){};	


public :

	void					arbitrate();

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