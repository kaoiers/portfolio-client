//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/06/15
//
// File Name : SGameUnitAttributeResources.h
// 
// 게임 유닛 속성 데이터 관리
// 
//////////////////////////////////////////////////////////////////////////

#ifndef GAME_UNIT_ATT_RESOURCE
#define GAME_UNIT_ATT_RESOURCE





struct GAMEUNIT_ATTRIBUTE
{

	u32 m_uDefaultLevel;
	u32 m_uDefaultExp;
	u32 m_uDefaultHP;
	u32 m_uDefaultAttack;
	u32 m_uDefaultDefence;
	f32 m_fCriticalRate;
	f32 m_fBlockingRate;
	f32 m_fDefaultAttackRange;
	f32 m_fDefaultFOV;
	f32 m_fDefaultViewDistance;

	f32 m_fExp_mul;
	f32 m_fExp_exp;
	f32 m_fHp_mul;
	f32 m_fHp_exp;
	f32 m_fAttack_mul;
	f32 m_fAttack_exp;
	f32 m_fDefence_mul;
	f32 m_fDefence_exp;
	u32 m_uAttackType;

};




#endif