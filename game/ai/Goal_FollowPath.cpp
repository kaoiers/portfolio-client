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
Goal_FollowPath(CGameUnit* pUnit):Goal_Composite<CGameUnit>(pUnit, goal_follow_path)
{
}


/*======================================================*/
// 그래프 길 따라가기 행동 초기화
/*======================================================*/
void Goal_FollowPath::Activate()
{
  m_iStatus = active;
  //remove the edge from the path
  
}


/*======================================================*/
// 그래프 길 따라가기 행동 처리
/*======================================================*/
s32 Goal_FollowPath::Process()
{
  //if status is inactive, call Activate()
  ActivateIfInactive();

  m_iStatus = ProcessSubgoals();

  //if there are no subgoals present check to see if the path still has edges.
  //remaining. If it does then call activate to grab the next edge.
  if (m_iStatus == completed )
  {
    Activate(); 
  }

  else if(m_iStatus == completed)
  {
	  StopSeeking();
  }



  return m_iStatus;
}

void Goal_FollowPath::Terminate()
{

}


/*======================================================*/
// 멈추기
/*======================================================*/
bool Goal_FollowPath::StopSeeking()
{
	m_pOwner->SetVelocity(vector3df(0,0,0));

	return true;
}


