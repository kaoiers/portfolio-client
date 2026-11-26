//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/05/20
//
// File Name : CGameUnitNapoleon.h
// 
// 게임 유닛 나폴레옹 클래스
// 
//////////////////////////////////////////////////////////////////////////

#ifndef CGAME_UNIT_NAPOLEON_H
#define CGAME_UNIT_NAPOLEON_H

#include "CGameUnitArmy.h"
#include "../attributes/CGameUnitAttribute.h"


class CGameUnitNapoleon : public CGameUnitArmy
{
	virtual		void		PrivateInitialize();

public :

	virtual		void		control(CEventHandler* pReceiver);

	virtual		void		OnCommand();

	CGameUnitNapoleon(OwnerType owner,u32 obj_id, u32 objtype,
		const UNIT_RESOURCE* resource, 
		const GAMEUNIT_ATTRIBUTE* attribute, 
		UnitTypes unittype, 
		const vector3df& pos = vector3df(0.0f, 0.0f, 0.0f),
		const vector3df& rot  = vector3df(0.0f, 0.0f, 0.0f),
		const vector3df& scale  = vector3df(1.0f, 1.0f, 1.0f));	

	CGameUnitNapoleon(OwnerType owner,u32 objtype,
		const UNIT_RESOURCE* resource, 
		const GAMEUNIT_ATTRIBUTE* attribute, 
		UnitTypes unittype, 
		const vector3df& pos = vector3df(0.0f, 0.0f, 0.0f),
		const vector3df& rot  = vector3df(0.0f, 0.0f, 0.0f),
		const vector3df& scale  = vector3df(1.0f, 1.0f, 1.0f));	


	virtual ~CGameUnitNapoleon();

};


#endif