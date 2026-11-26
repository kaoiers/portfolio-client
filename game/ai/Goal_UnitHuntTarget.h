//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/06/19
//
// File Name : Goal_UnitHuntTarget.h
// 
// 복합 목적 : 쫓아가기(적군)
//
//////////////////////////////////////////////////////////////////////////

#ifndef GOAL_HUNT_TARGET_H
#define GOAL_HUNT_TARGET_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   Goal_HuntTarget.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   Causes a bot to search for its current target. Exits when target
//          is in view
//-----------------------------------------------------------------------------
#include "Goal_Composite.h"


class CGameUnit;
class Regulator;

class Goal_UnitHuntTarget : public Goal_Composite<CGameUnit>
{
private:

	//this value is set to true if the last visible position of the target
	//bot has been searched without success
	bool  m_bLVPTried;
	CGameUnit*		m_pTarget;
	

public:

	Goal_UnitHuntTarget(CGameUnit* pBot):Goal_Composite<CGameUnit>(pBot, goal_unithunt_target),
		m_bLVPTried(false), m_pTarget(NULL)
	{}

	~Goal_UnitHuntTarget();


	//the usual suspects
	void Activate();
	int  Process();
	void Terminate() {}

	void Render();
	void StopHunting();

};





#endif
