//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/05/15
//
// File Name : CGameUnitAttribute.cpp
// 
// 게임 유닛 속성 클래스
// 
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "../objects/SGameUnitAttributeResources.h"
#include "CGameUnitAttribute.h"

GAMEUNIT_ATTRIBUTE* m_resource_ptr;



CGameUnitAttribute::CGameUnitAttribute(const GAMEUNIT_ATTRIBUTE* att )
: m_game_attribute(att),
  m_current_level(att->m_default_level), //실제 레벨로 대체
  m_current_hp(att->m_default_hp),
  m_attack(att->m_default_attack),
  m_defence(att->m_default_defence),
  m_attack_range(att->m_default_attack_range),
  m_critical_rate(att->m_critical_rate),
  m_blocking_rate(att->m_blocking_rate),
  m_max_exp(att->m_default_exp),
  m_max_hp(att->m_default_hp),
  m_fov(att->m_default_fov),
  m_view_distance(att->m_default_view_distance),
  m_alive(true)
{

}


/*======================================================*/
// 레벨업 처리하기
/*======================================================*/
void CGameUnitAttribute::levelUp()
{
	m_current_level++;
	m_current_hp = m_max_hp;
}


/*======================================================*/
// 공격 당했을 HP수치 처리하기
/*======================================================*/
u32 CGameUnitAttribute::calAttacked( u32 att )
{
	s16 attack = att - m_defence;
	
	if(attack < 0)
		attack = 1;

	m_current_hp -= attack;

	if(m_current_hp <= 0)
	{
		m_current_hp = 0 ;
		m_alive = false;
	}	

	return attack;
}