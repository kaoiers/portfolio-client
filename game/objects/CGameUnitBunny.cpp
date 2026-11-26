//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/05/20
//
// File Name : CGameUnitBunny.cpp
// 
// 게임 유닛 토끼
// 
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "CGameUnitBunny.h"
void CGameUnitBunny::PrivateInitialize()
{


}

void CGameUnitBunny::control( CEventHandler* pReceiver )
{

}

void CGameUnitBunny::OnCommand()
{

}





CGameUnitBunny::CGameUnitBunny(OwnerType owner, u32 obj_id, u32 objtype, const UNIT_RESOURCE* resource,
							   const GAMEUNIT_ATTRIBUTE* attribute, UnitTypes unittype, 
							   const vector3df& pos /*= vector3df(0.0f, 0.0f, 0.0f)*/, 
							   const vector3df& rot /*= vector3df(0.0f, 0.0f, 0.0f)*/, 
							   const vector3df& scale /*= vector3df(1.0f, 1.0f, 1.0f)*/ )
							   : CGameUnitArmy(owner, obj_id, objtype, resource, attribute ,unittype, pos, rot, scale)
{

}

CGameUnitBunny::CGameUnitBunny(OwnerType owner, u32 objtype, const UNIT_RESOURCE* resource,
							   const GAMEUNIT_ATTRIBUTE* attribute, UnitTypes unittype, 
							   const vector3df& pos /*= vector3df(0.0f, 0.0f, 0.0f)*/, 
							   const vector3df& rot /*= vector3df(0.0f, 0.0f, 0.0f)*/, 
							   const vector3df& scale /*= vector3df(1.0f, 1.0f, 1.0f)*/ )
							   : CGameUnitArmy(owner, objtype, resource, attribute ,unittype, pos, rot, scale)
{


}




CGameUnitBunny::~CGameUnitBunny()
{

}