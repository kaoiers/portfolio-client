//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/05/20
//
// File Name : Goal_HuntTarget.cpp
// 
// 복합 목적 : 목표물 쫓아가기 (적군)
//
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "Goal_HuntTarget.h"


#include "Goal_MoveToPosition.h"
#include "../objects/CGameUnit.h"
#include "../objects/CGameUnitEnemy.h"
#include "Goal_SeekToPosition.h"



/*======================================================*/
//  타겟 헌팅 행동 초기화
/*======================================================*/
void Goal_HuntTarget::activate()
{
  m_status = active;
  
  //if this goal is reactivated then there may be some existing subgoals that
  //must be removed
  removeAllSubgoals();




  m_enemy_unit = dynamic_cast<CGameUnitEnemy *>(m_owner);
  

  if (m_enemy_unit == NULL)
  {
	  m_status = completed;
	  return;

  }


  //if their is no active target then this goal can be removed from the queue

    
}



/*======================================================*/
//  타겟 헌팅 행동 처리
/*======================================================*/
s32 Goal_HuntTarget::process()
{
  activateIfInactive();






	 removeAllSubgoals();
	 stopHunting();
	 m_status = completed;


  return m_status;
}

void Goal_HuntTarget::render(){}



Goal_HuntTarget::~Goal_HuntTarget()
{
	 
}




/*======================================================*/
//  타겟 헌팅 중지 함수
/*======================================================*/
void Goal_HuntTarget::stopHunting()
{

}