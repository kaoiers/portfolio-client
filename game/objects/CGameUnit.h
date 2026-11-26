//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/03/03
//
// File Name : CGameUnit.h
// 
// 게임 유닛 기본 클래스
// 
//////////////////////////////////////////////////////////////////////////

#ifndef DEF_GAME_UNIT
#define DEF_GAME_UNIT


#include "IBaseGameUnit.h"
#include "IBaseController.h"
#include "../attributes/CGameUnitAttribute.h"
#include "MovingEntity.h"


struct GAMEUNIT_BASE_ATTRIBUTE;
class CSteering;
class CMoveAnimator;
class CPathPlanner;
class CMoveAnimator;
class CTargetingSystem;
class CSensoryMemory;
class CAttack;
class Regulator;
class Goal_Think;
class CLongTimeRegulator;


typedef enum 
{
	unit_mine,
	unit_opponet,
	unit_alliance

}AllianceType;


class CGameUnit : public  IBaseGameUnit,  public MovingEntity, public CGameUnitAttribute, public IBaseController
{

protected :

	CSteering*									m_steering;

	CSensoryMemory*								m_sensory_memory;
	
	CTargetingSystem*							m_targeting_system;

	CPathPlanner*								m_path_planner;

	Goal_Think*									m_brain;

	Regulator*									m_target_selection_regulator;

	Regulator*									m_vision_update_regulator;

	CLongTimeRegulator*							m_hp_update_regulator;
	
	bool										m_hit_once;

private :

	u32								m_unit_type;

	const UNIT_RESOURCE* 						m_unit_resource;

	AllianceType								m_ally_type;

	const f32									m_healthbar_height, m_healthbar_width;

	const u32									m_hp_update_time;


public :

	void										initAnimation();

	void										initWeapon();

	void										updateMovement(u32 time_ms);

	bool										handleMessage(const Telegram& msg);

	CSteering*									getSteering() const { return m_steering; }

	CSensoryMemory*								getSensoryMem()		{ return m_sensory_memory; }

	CTargetingSystem*							getTargetingSystem() { return m_targeting_system; }

	CPathPlanner*								getPathPlanner()    { return m_path_planner; }

	Goal_Think*									getBrain() { return m_brain; }



	const UNIT_RESOURCE* 						getUnitResource()  { return m_unit_resource; }
	u32						getUnitType() {return m_unit_type;}
	AllianceType							getAllyType() const { return m_ally_type; }
	virtual	bool								isAttackSuccess(CGameObject* opponent );

	void										setCurrentAni(const u32 atype, const bool b_loop);
	CGameUnit*									getTarget() const;
	bool										isInHitDistance(const vector3df& pos, f32 b_radius);
	vector3df									getApproachPosition(const vector3df& pos);

	


public :
	
	const f32									getHitRange() {return  m_unit_resource->m_hit_range; }
	const f32									getRadius() {return m_unit_resource->m_radius; }
	const f32									getUnitViewDistance() {  return  getViewDistance();  }

	void										dispatchMessageKill(CGameUnit* p_target);
	void										addGoalDead();
	void										addGoalMoveToPosition(const vector3df& pos);
	void										addDamage(const u32 damage, CGameUnit*	p_attacker);
	void										damageShow(const u32 damage);
	void										removeSubGoals();
	void										damageStatusUpdate();
	bool										canWalkTo(const vector3df&  target_pos);
	bool										canWalkBetween(const vector3df& from, const vector3df& to);

	void										obtainExp(const u32  u_exp);
	void										sendDamageReq(const u32	damage, CGameUnit*	p_unit);

	void										updateHP( const u32 time_ms );
	void										updateHpBar();
	
	
	CGameUnit(OwnerType owner,u32 obj_id, u32 objtype, const UNIT_RESOURCE* resource, const GAMEUNIT_ATTRIBUTE* attribute,
		UnitTypes unittype,AllianceType ally_type,
		const vector3df& pos = vector3df(0.0f, 0.0f, 0.0f),
		const vector3df& rot  = vector3df(0.0f, 0.0f, 0.0f),
		const vector3df& scale  = vector3df(1.0f, 1.0f, 1.0f));	

	CGameUnit(OwnerType owner,u32 objtype, const UNIT_RESOURCE* resource, const GAMEUNIT_ATTRIBUTE* attribute,
		UnitTypes unittype,AllianceType ally_type,
		const vector3df& pos = vector3df(0.0f, 0.0f, 0.0f),
		const vector3df& rot  = vector3df(0.0f, 0.0f, 0.0f),
		const vector3df& scale  = vector3df(1.0f, 1.0f, 1.0f));

	virtual ~CGameUnit();


};


namespace nsUnit
{
	inline void unitInit(CGameUnit* p_unit)
	{
		if (p_unit == nullptr)
			return;

		p_unit->initWeapon();
		p_unit->initAnimation();
		p_unit->privateInitialize();
	}
};



#endif