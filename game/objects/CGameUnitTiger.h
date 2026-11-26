//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/05/20
//
// File Name : CGameUnitTiger.h
// 
// 게임 유닛 타이거 클래스
// 
//////////////////////////////////////////////////////////////////////////

#ifndef CGAME_UNIT_ARMY_TIGER_H
#define CGAME_UNIT_ARMY_TIGER_H

#include "CGameUnitArmy.h"
#include "../attributes/CGameUnitAttribute.h"


class CGameUnitTiger : public CGameUnitArmy
{	
	


	virtual		void		PrivateInitialize();

public :

	virtual		void		control(CEventHandler* pReceiver);
	
	virtual		void		OnCommand();



	CGameUnitTiger(OwnerType owner,unsigned int obj_id, unsigned int objtype,
		const UNIT_RESOURCE* resource, 
		const GAMEUNIT_ATTRIBUTE* attribute, 
		 UnitTypes unittype, 
		const vector3df& pos = vector3df(0.0f, 0.0f, 0.0f),
		const vector3df& rot  = vector3df(0.0f, 0.0f, 0.0f),
		const vector3df& scale  = vector3df(1.0f, 1.0f, 1.0f));	

	CGameUnitTiger(OwnerType owner,unsigned int objtype,
		const UNIT_RESOURCE* resource, 
		const GAMEUNIT_ATTRIBUTE* attribute, 
		UnitTypes unittype, 
		const vector3df& pos = vector3df(0.0f, 0.0f, 0.0f),
		const vector3df& rot  = vector3df(0.0f, 0.0f, 0.0f),
		const vector3df& scale  = vector3df(1.0f, 1.0f, 1.0f));

	virtual ~CGameUnitTiger();

};


#endif