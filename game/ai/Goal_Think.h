//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/04/11
//
// File Name : Goal_Think.h
// 
// 인공지능 클래스
//
//////////////////////////////////////////////////////////////////////////

#ifndef GOAL_THINK_H
#define GOAL_THINK_H
#pragma warning (disable:4786)


#include "Goal_Composite.h"



class CGameUnit;


class Goal_Think : public Goal_Composite<CGameUnit >
{


public:

	Goal_Think(CGameUnit* pUnit);
	~Goal_Think();

	
	void Arbitrate();
	void EnemyInit();
	void ArmyInit();

	bool notPresent(unsigned int GoalType)const;

	int  Process();
	void Activate();
	void Terminate(){}

	void RemoveSubGoals();

	//top level goal types
	void AddGoal_MoveToPosition(vector3df pos);
	void AddGoal_GetItem(unsigned int ItemType);
	void AddGoal_Explore();
	void AddGoal_Die();
	void AddGoal_Building(const vector3df& pos);
	void AddGoal_Collecting(const vector3df& pos);
	void AddGoal_HuntTarget();
	void AddGoal_UnitHuntTarget();
	void AddGoal_AttackTargetForEnemy();
	void AddGoal_GoingHome();
	void AddGoal_AttackTarget();
	void QueueGoal_MoveToPosition(vector3df pos);


};


#endif