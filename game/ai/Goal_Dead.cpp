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

void Goal_Dead::Activate()
{
	m_iStatus = active;

// 	if(!(m_pOwner->GetAnimationMgr()->IsOnAnimation(ANI_WALK)))
// 	{
	m_pOwner->setCurrentAni(ANI_DIE, false);
//	}	

	
}


/*======================================================*/
//  죽는 애니메이션 조작
/*======================================================*/
int  Goal_Dead::Process()
{
	ActivateIfInactive();

	return m_iStatus;
}

void Goal_Dead::Terminate()
{
	m_iStatus = completed;
}



Goal_Dead::Goal_Dead( CGameUnit* pUnit ) : Goal<CGameUnit>(pUnit, goal_die)
{

}