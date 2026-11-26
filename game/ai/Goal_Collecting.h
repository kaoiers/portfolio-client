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

	CGameUnitWorker*	m_worker;




	//the position the bot wants to reach
	vector3df m_destination;

public:

	Goal_Collecting(CGameUnit* p_unit, vector3df   pos):  
	  Goal_Composite<CGameUnit>(p_unit, 	goal_collecting),
		  m_destination(pos)
	  {}

	  //the usual suspects
	  void activate();
	  s32  process();
	  void terminate();

	  //this goal is able to accept messages
	  bool handleMessage(const Telegram& msg);

	  void render();
};




#endif 