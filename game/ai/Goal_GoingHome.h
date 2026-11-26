//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/05/08
//
// File Name : Goal_GOingHome.h
// 
// 복합 목적 : 집에 가기
//
//////////////////////////////////////////////////////////////////////////

#ifndef GOAL_GOINGHOME_H
#define GOAL_GOINGHOME_H

#pragma warning (disable:4786)

#include "Goal_Composite.h"

class CGameUnit;



class Goal_GoingHome : public Goal_Composite<CGameUnit>
{
private:

	

public:

	Goal_GoingHome(CGameUnit* pUnit):  
	  Goal_Composite<CGameUnit>(pUnit, goal_goinghome){}

	  //the usual suspects
	  void Activate();
	  int  Process();
	  void Terminate(){}

	  //this goal is able to accept messages
	  bool HandleMessage(const Telegram& msg);

	  void Render();
};




#endif 