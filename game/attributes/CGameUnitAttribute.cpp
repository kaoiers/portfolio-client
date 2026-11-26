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
#include "../attributes/CGameUnitAttribute.h"

GAMEUNIT_ATTRIBUTE* m_pResource;



CGameUnitAttribute::CGameUnitAttribute(const GAMEUNIT_ATTRIBUTE* att )
: m_pGameAttribute(att),
  m_uCurrentLevel(att->m_uDefaultLevel), //실제 레벨로 대체
  m_uCurrentHp(att->m_uDefaultHP),
  m_uAttack(att->m_uDefaultAttack),
  m_uDefence(att->m_uDefaultDefence),
  m_fAttackRange(att->m_fDefaultAttackRange),
  m_fCriticalRate(att->m_fCriticalRate),
  m_fBlockingRate(att->m_fBlockingRate),
  m_uMaxExp(att->m_uDefaultExp),
  m_uMaxHp(att->m_uDefaultHP),
  m_fFOV(att->m_fDefaultFOV),
  m_fViewDistance(att->m_fDefaultViewDistance),
  m_bAlive(true)
{

}


/*======================================================*/
// 레벨업 처리하기
/*======================================================*/
void CGameUnitAttribute::Levelup()
{
	m_uCurrentLevel++;
	m_uCurrentHp = m_uMaxHp;
}


/*======================================================*/
// 공격 당했을 HP수치 처리하기
/*======================================================*/
u32 CGameUnitAttribute::CalAttacked( u32 att )
{
	s16 attack = att - m_uDefence;
	
	if(attack < 0)
		attack = 1;

	m_uCurrentHp -= attack;

	if(m_uCurrentHp <= 0)
	{
		m_uCurrentHp = 0 ;
		m_bAlive = false;
	}	

	return attack;
}