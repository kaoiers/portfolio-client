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

	CSteering*									m_pSteering;

	CSensoryMemory*								m_pSensoryMemory;
	
	CTargetingSystem*							m_pTargetingSystem;

	CPathPlanner*								m_pPathPlanner;

	Goal_Think*									m_pBrain;

	Regulator*									m_pTargetSelectionRegulator;

	Regulator*									m_pVisionUpdateRegulator;

	CLongTimeRegulator*							m_pHPUpdateRegulator;
	
	bool										m_bHitOnce;

private :

	u32								m_unit_type;

	const UNIT_RESOURCE* 						m_rUnitResource;

	AllianceType								m_eAlly;

	const f32									m_fHealthbarHeight, m_fHealthbarWidth;

	const u32									m_uHPUpdateTime;


public :

	void										InitAnimation();

	void										InitWeapon();

	void										UpdateMoveMent(u32 timeMs);

	bool										HandleMessage(const Telegram& msg);

	CSteering*									GetSteering() const { return m_pSteering; }

	CSensoryMemory*								GetSensoryMem()		{ return m_pSensoryMemory; }

	CTargetingSystem*							getTargetingSystem() { return m_pTargetingSystem; }

	CPathPlanner*								GetPathPlanner()    { return m_pPathPlanner; }

	Goal_Think*									getBrain() { return m_pBrain; }



	const UNIT_RESOURCE* 						getUnitResource()  { return m_rUnitResource; }
	u32						getUnitType() {return m_unit_type;}
	AllianceType							getAllyType() const { return m_eAlly; }
	virtual	bool								isAttackSuccess(CGameObject* opponent );

	void										setCurrentAni(const u32 atype, const bool bLoop);
	CGameUnit*									getTarget() const;
	bool										isInHitDistance(const vector3df& pos, f32 bRadius);
	vector3df									getApproachPosition(const vector3df& pos);

	


public :
	
	const f32									getHitRange() {return  m_rUnitResource->m_fHitRange; }
	const f32									getRadius() {return m_rUnitResource->m_fRadius; }
	const f32									GetViewDistance() {  return  getViewDistance();  }

	void										DispatchMessageKill(CGameUnit* pTarget);
	void										AddGoal_Dead();
	void										AddGoal_MoveToPosition(const vector3df& pos);
	void										AddDamage(const u32 damage, CGameUnit*	pAttacker);
	void										DamageShow(const u32 damage);
	void										RemoveSubGoals();
	void										DamageStatusUpdate();
	bool										canWalkTo(const vector3df&  TargetPos);
	bool										canWalkBetween(const vector3df& from, const vector3df& to);

	void										ObtainExp(const u32  uExp);
	void										SendDamageReq(const u32	damage, CGameUnit*	pUnit);

	void										updateHP( const u32 timeMs );
	void										updateHpBar();
	
	
	CGameUnit(OwnerType owner,u32 obj_id, u32 objtype, const UNIT_RESOURCE* resource, const GAMEUNIT_ATTRIBUTE* attribute,
		UnitTypes unittype,AllianceType m_bAlly,
		const vector3df& pos = vector3df(0.0f, 0.0f, 0.0f),
		const vector3df& rot  = vector3df(0.0f, 0.0f, 0.0f),
		const vector3df& scale  = vector3df(1.0f, 1.0f, 1.0f));	

	CGameUnit(OwnerType owner,u32 objtype, const UNIT_RESOURCE* resource, const GAMEUNIT_ATTRIBUTE* attribute,
		UnitTypes unittype,AllianceType m_bAlly,
		const vector3df& pos = vector3df(0.0f, 0.0f, 0.0f),
		const vector3df& rot  = vector3df(0.0f, 0.0f, 0.0f),
		const vector3df& scale  = vector3df(1.0f, 1.0f, 1.0f));

	virtual ~CGameUnit();


};


namespace nsUnit
{
	inline void UnitInit(CGameUnit* pUnit)
	{
		if (pUnit == nullptr)
			return;

		pUnit->InitWeapon();
		pUnit->InitAnimation();
		pUnit->PrivateInitialize();
	}
};



#endif