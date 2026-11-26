//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/05/20
//
// File Name : Goal_HuntTarget.h
// 
// 복합 목적 : 목표물 쫓아가기 (적군)
//
//////////////////////////////////////////////////////////////////////////

#ifndef GOAL_FIND_TARGET_H
#define GOAL_FIND_TARGET_H
#pragma warning (disable:4786)


#include "Goal_Composite.h"


class CGameUnit;
class CGameUnitEnemy;
class Regulator;

class Goal_HuntTarget : public Goal_Composite<CGameUnit>
{
private:

  //this value is set to true if the last visible position of the target
  //bot has been searched without success
  bool  m_bLVPTried;
  CGameUnitEnemy*	m_pEnemyUnit;
  CGameUnit*		m_pTarget;

public:

  Goal_HuntTarget(CGameUnit* pBot):Goal_Composite<CGameUnit>(pBot, goal_hunt_target),
                                   m_bLVPTried(false), m_pTarget(NULL)
  {}

  ~Goal_HuntTarget();


   //the usual suspects
  void Activate();
  int  Process();
  void Terminate() {}

  void Render();
  void StopHunting();

};





#endif
