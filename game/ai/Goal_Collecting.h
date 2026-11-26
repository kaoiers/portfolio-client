//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/08/06
//
// File Name : Goal_Collecting.h
// 
// 복합 목적 : 자원 채집 하기
//
//////////////////////////////////////////////////////////////////////////

#ifndef GOAL_COLLECTING_H
#define GOAL_COLLECTING_H

#pragma warning (disable:4786)

#include "Goal_Composite.h"

class CGameUnit;
class CGameUnitWorker;


class Goal_Collecting : public Goal_Composite<CGameUnit>
{
private:

	CGameUnitWorker*	m_pWorker;




	//the position the bot wants to reach
	vector3df m_vDestination;

public:

	Goal_Collecting(CGameUnit* pUnit, vector3df   pos):  
	  Goal_Composite<CGameUnit>(pUnit, 	goal_collecting),
		  m_vDestination(pos)
	  {}

	  //the usual suspects
	  void Activate();
	  int  Process();
	  void Terminate();

	  //this goal is able to accept messages
	  bool HandleMessage(const Telegram& msg);

	  void Render();
};




#endif 