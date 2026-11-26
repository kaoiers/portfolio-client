//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/05/25
//
// File Name : Goal_Dead.h
// 
// 단일 목적 : 유닛 죽기
//
//////////////////////////////////////////////////////////////////////////

#ifndef GOAL_DEAD_H
#define GOAL_DEAD_H

#pragma warning (disable:4786)

#include "Goal.h"

class CGameUnit;

class Goal_Dead : public Goal<CGameUnit>
{
private:



public:

	Goal_Dead(CGameUnit* pUnit);

	//the usual suspects
	void Activate();
	int  Process();
	void Terminate();
	
};

#endif