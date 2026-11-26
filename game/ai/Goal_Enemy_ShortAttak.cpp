//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/05/19
//
// File Name : Goal_ShortAttack.cpp
// 
// 단일 목적 : 근거리 공격하기
//
//////////////////////////////////////////////////////////////////////////



#include <stdafx.h>
#include "Goal_Enemy_ShortAttack.h"
#include "../objects/CGameUnitEnemy.h"
#include "Goal_SeekToPosition.h"
#include "Goal_ShortAttack.h"
#include "../objects/CGameRoom.h"
#include "../objects/CGameUnit.h"


Goal_Enemy_ShortAttack::Goal_Enemy_ShortAttack( CGameUnitEnemy* pUnit, CGameUnit* pTarget )
:Goal(pUnit, goal_enemy_short_attack) ,m_pEnemy(pUnit) ,  m_pTarget(pTarget)
{

}
/*======================================================*/
//  프로세스 진입
/*======================================================*/
void Goal_Enemy_ShortAttack::Activate()
{
	m_iStatus = active;	
}


/*======================================================*/
//  프로세스 시작
/*======================================================*/
s32 Goal_Enemy_ShortAttack::Process()
{
	//if status is inactive, call Activate()
	ActivateIfInactive();


	
	return m_iStatus;
}

void Goal_Enemy_ShortAttack::Terminate()
{

}