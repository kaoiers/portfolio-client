//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/05/20
//
// File Name : CGameUnitNapoleon.cpp
// 
// 게임 유닛 나폴레옹 클래스
// 
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "CGameUnitNapoleon.h"




void CGameUnitNapoleon::privateInitialize()
{

}

void CGameUnitNapoleon::control( CEventHandler* p_receiver )
{

}

void CGameUnitNapoleon::onCommand()
{

}



CGameUnitNapoleon::~CGameUnitNapoleon()
{

}

CGameUnitNapoleon::CGameUnitNapoleon(OwnerType owner, u32 obj_id, u32 objtype, const UNIT_RESOURCE* resource,
									 const GAMEUNIT_ATTRIBUTE* attribute, UnitTypes unittype, 
									 const vector3df& pos /*= vector3df(0.0f, 0.0f, 0.0f)*/, 
									 const vector3df& rot /*= vector3df(0.0f, 0.0f, 0.0f)*/, 
									 const vector3df& scale /*= vector3df(1.0f, 1.0f, 1.0f)*/ )
									 :  CGameUnitArmy(owner, obj_id, objtype, resource, attribute ,unittype, pos, rot, scale)
{

}

CGameUnitNapoleon::CGameUnitNapoleon(OwnerType owner, u32 objtype, const UNIT_RESOURCE* resource,
									 const GAMEUNIT_ATTRIBUTE* attribute, UnitTypes unittype, 
									 const vector3df& pos /*= vector3df(0.0f, 0.0f, 0.0f)*/, 
									 const vector3df& rot /*= vector3df(0.0f, 0.0f, 0.0f)*/, 
									 const vector3df& scale /*= vector3df(1.0f, 1.0f, 1.0f)*/ )
									 :  CGameUnitArmy(owner, objtype, resource, attribute ,unittype, pos, rot, scale)
{

}