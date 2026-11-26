//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/05/25
//
// File Name : Goal_Dead.cpp
// 
// 단일 목적 : 유닛 죽기
//
//////////////////////////////////////////////////////////////////////////
#include <stdafx.h>
#include "Goal_Dead.h"
#include "../objects/CGameUnit.h"
#include "../CAppContext.h"
#include "God_Messages.h"
#include "Telegram.h"
#include "MessageDispatcher.h"



/*======================================================*/
//  죽는 애니메이션  시작
/*======================================================*/

void Goal_Dead::activate()
{
	m_status = active;

	m_owner->setCurrentAni(ANI_DIE, false);

	
}


/*======================================================*/
//  죽는 애니메이션 조작
/*======================================================*/
s32  Goal_Dead::process()
{
	activateIfInactive();

	return m_status;
}

void Goal_Dead::terminate()
{
	m_status = completed;
}



Goal_Dead::Goal_Dead( CGameUnit* p_unit ) : Goal<CGameUnit>(p_unit, goal_die)
{

}