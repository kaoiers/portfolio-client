//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/06/05
//
// File Name : Goal_Building.h
// 
// 복합 목적 : 건설하기
//
//////////////////////////////////////////////////////////////////////////

#ifndef GOAL_BUILDING_H
#define GOAL_BUILDING_H

#pragma warning (disable:4786)

#include "Goal_Composite.h"

class CGameUnit;



class Goal_Building : public Goal_Composite<CGameUnit>
{
private:

	//the position the bot wants to reach
	vector3df m_vDestination;

public:

	Goal_Building(CGameUnit* pUnit, vector3df   pos);
	

	  //the usual suspects
	  void Activate();
	  int  Process();
	  void Terminate(){}

	  //this goal is able to accept messages
	  bool HandleMessage(const Telegram& msg);

	  void Render();
};




#endif 