//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/08/06
//
// File Name : Goal_FollowPath.cpp
// 
// 복합 목적 : 길따라 움직이기
//
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "Goal_FollowPath.h"
#include "../objects/CGameUnit.h"
//#include "../Raven_Game.h"
#include "Goal_TraverseEdge.h"
#include <string>
//#include "Goal_NegotiateDoor.h"




Goal_FollowPath::
Goal_FollowPath(CGameUnit* p_unit):Goal_Composite<CGameUnit>(p_unit, goal_follow_path)
{
}


/*======================================================*/
// 그래프 길 따라가기 행동 초기화
/*======================================================*/
void Goal_FollowPath::activate()
{
  m_status = active;
  //remove the edge from the path
  
}


/*======================================================*/
// 그래프 길 따라가기 행동 처리
/*======================================================*/
s32 Goal_FollowPath::process()
{
  //if status is inactive, call Activate()
  activateIfInactive();

  m_status = processSubgoals();

  //if there are no subgoals present check to see if the path still has edges.
  //remaining. If it does then call activate to grab the next edge.
  if (m_status == completed )
  {
    activate(); 
  }

  else if(m_status == completed)
  {
	  stopSeeking();
  }



  return m_status;
}

void Goal_FollowPath::terminate()
{

}


/*======================================================*/
// 멈추기
/*======================================================*/
bool Goal_FollowPath::stopSeeking()
{
	m_owner->setVelocity(vector3df(0,0,0));

	return true;
}


