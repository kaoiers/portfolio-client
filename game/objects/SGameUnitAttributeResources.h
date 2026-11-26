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

	u32 m_default_level;
	u32 m_default_exp;
	u32 m_default_hp;
	u32 m_default_attack;
	u32 m_default_defence;
	f32 m_critical_rate;
	f32 m_blocking_rate;
	f32 m_default_attack_range;
	f32 m_default_fov;
	f32 m_default_view_distance;

	f32 m_exp_mul;
	f32 m_exp_exp;
	f32 m_hp_mul;
	f32 m_hp_exp;
	f32 m_attack_mul;
	f32 m_attack_exp;
	f32 m_defence_mul;
	f32 m_defence_exp;
	u32 m_attack_type_code;

};




#endif