//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/05/29
//
// File Name : CGameUnitEnemySoldier.h
// 
// 게임 적군 군사 클래스
// 
//////////////////////////////////////////////////////////////////////////

#ifndef	GAME_UNIT_ENEMY_SOLDIER
#define GAME_UNIT_ENEMY_SOLDIER

#include "CGameUnitEnemy.h"


class CGameUnitEnemySoldier : public CGameUnitEnemy
{

private :



	virtual		void		PrivateInitialize();



public :

	virtual		void		update(u32 timeMs);

	virtual		bool		short_attack(CGameUnit* pTarget); 


	CGameUnitEnemySoldier(CEnemyGenerator* pGenerator,  OwnerType owner,u32 obj_id, u32 objtype,
		const UNIT_RESOURCE* resource, 
		const GAMEUNIT_ATTRIBUTE* attribute, 
		UnitTypes unittype, 
		const vector3df& pos = vector3df(0.0f, 0.0f, 0.0f),
		const vector3df& rot  = vector3df(0.0f, 0.0f, 0.0f),
		const vector3df& scale  = vector3df(1.0f, 1.0f, 1.0f));	

	CGameUnitEnemySoldier(CEnemyGenerator* pGenerator, OwnerType owner,u32 objtype,
		const UNIT_RESOURCE* resource, 
		const GAMEUNIT_ATTRIBUTE* attribute, 
		UnitTypes unittype, 
		const vector3df& pos = vector3df(0.0f, 0.0f, 0.0f),
		const vector3df& rot  = vector3df(0.0f, 0.0f, 0.0f),
		const vector3df& scale  = vector3df(1.0f, 1.0f, 1.0f));

	virtual ~CGameUnitEnemySoldier(); 

};



#endif