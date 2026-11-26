//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/05/29
//
// File Name : CGameUnitEnemy.h
// 
// 게임 적군 클래스
// 
//////////////////////////////////////////////////////////////////////////

#ifndef GAME_UNIT_ENEMY_H
#define GAME_UNIT_ENEMY_H

#include "CGameUnit.h"

class CEnemySensoryMemory;
class CEnemyTargetingSystem;
class CGameRoom;
class CEnemyGenerator;


class CGameUnitEnemy : public CGameUnit
{

protected :
	
	CEnemySensoryMemory*			m_pEnemySensoryMemory;

	CEnemyTargetingSystem*			m_pEnemyTargetingSystem;

	Regulator*						m_pEnemyTargetRegulator;

	Regulator*						m_pEnemyMemoryRegulator;

	Regulator*						m_pArbitrateRegulator;

	CEnemyGenerator*				m_pGenerator;

	u32						m_sGoingHomeTime;

	s16						m_sRemainTime;

	s16						m_sElapsedTime;


public :

	virtual		void				control(CEventHandler* pReceiver){};

	virtual		void				OnCommand(){};

	virtual		bool				long_attack(CGameUnit*	pTarget) { return false; } 

	CEnemyGenerator*				getEnemyGenerator() { return m_pGenerator; }




	virtual void					enter_control(){};
	virtual void					update_control(CEventHandler* pReceiver){};
	virtual void					exit_control(){};	

	void							ArbitrateBehavior();
	bool							isOnAttack();

	void							HandleDestroyBuildingMessage(CGameRoom*	pRoom);
	void							HandleKillUnitMessage(CGameUnit*	pUnit);
	void							HandleUnitDeadMessage(CGameUnit*	pUnit);

	s16								getRemainTime() {return m_sGoingHomeTime - m_sElapsedTime; }


	
	

public :

	CEnemySensoryMemory*			getEnemySensoryMemory() {return m_pEnemySensoryMemory; }

	CEnemyTargetingSystem*			getEnemyTargetingSystem() {return m_pEnemyTargetingSystem; }

	CGameUnitEnemy(CEnemyGenerator* pGenerator , OwnerType owner,u32 obj_id, u32 objtype,
		const UNIT_RESOURCE* resource, 
		const GAMEUNIT_ATTRIBUTE* attribute, 
		UnitTypes unittype, 
		const vector3df& pos = vector3df(0.0f, 0.0f, 0.0f),
		const vector3df& rot  = vector3df(0.0f, 0.0f, 0.0f),
		const vector3df& scale  = vector3df(1.0f, 1.0f, 1.0f));	

	CGameUnitEnemy(CEnemyGenerator* pGenerator , OwnerType owner,u32 objtype,
		const UNIT_RESOURCE* resource, 
		const GAMEUNIT_ATTRIBUTE* attribute, 
		UnitTypes unittype, 
		const vector3df& pos = vector3df(0.0f, 0.0f, 0.0f),
		const vector3df& rot  = vector3df(0.0f, 0.0f, 0.0f),
		const vector3df& scale  = vector3df(1.0f, 1.0f, 1.0f));	

	virtual ~CGameUnitEnemy();	
};







#endif