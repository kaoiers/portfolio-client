//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/08/06
//
// File Name : Goal_FollowPath.h
// 
// 복합 목적 : 길따라 움직이기
//
//////////////////////////////////////////////////////////////////////////

#ifndef GOAL_FOLLOWPATH_H
#define GOAL_FOLLOWPATH_H
#pragma warning (disable:4786)

#include "Goal_Composite.h"

class CGameUnit;

class Goal_FollowPath : public Goal_Composite<CGameUnit>
{
private:


public:

  Goal_FollowPath(CGameUnit* pUnit);

  //the usual suspects
  void Activate();
  s32 Process();
  void Render();
  void Terminate();

bool		StopSeeking();
};

#endif

