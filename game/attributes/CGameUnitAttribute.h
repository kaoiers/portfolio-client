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

	const GAMEUNIT_ATTRIBUTE* m_game_attribute;

	////////////////////////////////////////////////

	u32	m_current_level;

	s16	m_current_hp;
	
	u32	m_current_exp;

	////////////////////////////////////////////////

	u32	m_attack;
	
	u32	m_defence;
	
	f32	m_attack_range;
	
	f32    m_critical_rate;
	
	f32    m_blocking_rate;

	//////////////////////////////////////////////

	u32    m_max_exp;
	
	u32    m_max_hp;

	//////////////////////////////////////////////

	f32	m_fov;

	f32	m_view_distance;

	bool		m_alive;

	ATTACK_TYPE			m_attack_type;


public :

	CGameUnitAttribute(const GAMEUNIT_ATTRIBUTE* att);
	virtual ~CGameUnitAttribute() {} ; 

	u32				getLevel() const {	return	m_current_level; }
	
	s16				getHp() { return m_current_hp;  }
	u32				getMaxHp() const {return m_max_hp; }
	void			increaseHp() { m_current_hp++; }
	
	u32				getExp() { return m_current_exp;  }
	u32				getMaxExp() const { return m_max_exp;  }	
	
	u32				getAttack() const { return m_attack;  }
	u32				getDefence() const { return m_defence;  }
	f32				getAttackRange() const { return m_attack_range;  }

	f32				getFOV() const { return m_fov; }
	f32				getViewDistance() const { return m_view_distance; }

	const bool			isLevelUpAvailable() const {return (m_current_exp >= m_max_exp); }
	const bool			isDead() const {return (m_current_hp <= 0); }

	const bool			isAlive() {return m_alive; }


	ATTACK_TYPE	getAttackType ()  { return m_attack_type; }

	
	
	
	void				levelUp();

	u32			calAttacked(u32 att);
};




#endif