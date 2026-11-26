//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/05/15
//
// File Name : CGameUnitAttribute.h
// 
// 게임 유닛 속성 클래스
// 
//////////////////////////////////////////////////////////////////////////


#ifndef GAMEUNIT_ATTRIBUTE_CLASS
#define GAMEUNIT_ATTRIBUTE_CLASS


struct GAMEUNIT_ATTRIBUTE;



typedef enum  
{
	SHORT_ATTACK = 0,
	LONG_ATTACK,
	BOTH_ATTACK

}ATTACK_TYPE;




class CGameUnitAttribute
{

	const GAMEUNIT_ATTRIBUTE* m_pGameAttribute;

	////////////////////////////////////////////////

	u32	m_uCurrentLevel;

	s16	m_uCurrentHp;
	
	u32	m_uCurrentExp;

	////////////////////////////////////////////////

	u32	m_uAttack;
	
	u32	m_uDefence;
	
	f32	m_fAttackRange;
	
	f32    m_fCriticalRate;
	
	f32    m_fBlockingRate;

	//////////////////////////////////////////////

	u32    m_uMaxExp;
	
	u32    m_uMaxHp;

	//////////////////////////////////////////////

	f32	m_fFOV;

	f32	m_fViewDistance;

	bool		m_bAlive;

	ATTACK_TYPE			m_eAttackType;


public :

	CGameUnitAttribute(const GAMEUNIT_ATTRIBUTE* att);
	virtual ~CGameUnitAttribute() {} ; 

	u32				getLevel() const {	return	m_uCurrentLevel; }
	
	s16				getHp() { return m_uCurrentHp;  }
	u32				getMaxHp() const {return m_uMaxHp; }
	void			IncreaseHp() { m_uCurrentHp++; }
	
	u32				getExp() { return m_uCurrentExp;  }
	u32				getMaxExp() const { return m_uMaxExp;  }	
	
	u32				getAttack() const { return m_uAttack;  }
	u32				getDefence() const { return m_uDefence;  }
	f32				getAttackRange() const { return m_fAttackRange;  }

	f32				getFOV() const { return m_fFOV; }
	f32				getViewDistance() const { return m_fViewDistance; }

	const bool			isLevelUpAvailable() const {return (m_uCurrentExp >= m_uMaxExp); }
	const bool			isDead() const {return (m_uCurrentHp <= 0); }

	const bool			isAlive() {return m_bAlive; }


	ATTACK_TYPE	getAttackType ()  { return m_eAttackType; }

	
	
	
	void				Levelup();

	u32			CalAttacked(u32 att);
};




#endif