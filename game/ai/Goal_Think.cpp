//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/04/11
//
// File Name : Goal_Think.h
// 
// 인공지능 클래스
//
//////////////////////////////////////////////////////////////////////////


#include <stdafx.h>
#include "Goal_Think.h"
#include <list>
#include "../objects/CGameUnit.h"
#include "Goal_MoveToPosition.h"
#include "Goal_ShortAttack.h"
#include "Goal_AttackTarget.h"
#include "Goal_Dead.h"
#include "Goal_Building.h"
#include "Goal_Collecting.h"
#include "Goal_HuntTarget.h"
#include "Goal_UnitHuntTarget.h"
#include "Goal_GoingHome.h"
#include "Goal_AttackUnitTarget.h"
#include "../map/CGameMap.h"
#include "../interfaces/CMainGameGUI.h"

Goal_Think::Goal_Think(CGameUnit* pUnit):Goal_Composite<CGameUnit>(pUnit, goal_think)
{

	const double LowRangeOfBias = 0.5;
	const double HighRangeOfBias = 1.5;

	
}



Goal_Think::~Goal_Think()
{
	RemoveAllSubgoals();


}



/*======================================================*/
// 유닛 군사용 목표 평가기 추가
/*======================================================*/
void Goal_Think::ArmyInit()
{
	double AttackBias = 1.0;

	
}



/*======================================================*/
// 적군용 목표 평가기 추가
/*======================================================*/
void Goal_Think::EnemyInit()
{
	double AttackBias = 1.0;
 	
	


}



/*======================================================*/
// 초기화
/*======================================================*/
void Goal_Think::Activate()
{
	if (!m_pOwner->isPossessed())
	{
		//Arbitrate();
	}

	m_iStatus = active;
}

/*======================================================*/
// 처리하기
/*======================================================*/
int Goal_Think::Process()
{
 	ActivateIfInactive();

	int SubgoalStatus =  ProcessSubgoals();

// 	if (SubgoalStatus == completed || SubgoalStatus == failed)
// 	{
//   		if (!(m_pOwner->isPossessed()))
//   		{
//   			m_iStatus = inactive;
//   		}
// 	}

	ReactivateIfFailed();

	return m_iStatus;
}

/*======================================================*/
// 목표 중재기
/*======================================================*/
void Goal_Think::Arbitrate()
{
	double best = 0;
	

	if(!(m_pOwner->isAlive()))
	{
		return ;
	}

	if (!notPresent(goal_move_to_position) && m_pOwner->getUnitType() != UNIT_ENEMY_SOLDIER)
	{
		return ;		
	}


}


/*======================================================*/
// 하위 목표 실행 확인
/*======================================================*/
bool Goal_Think::notPresent(unsigned int GoalType)const
{
	if (!m_SubGoals.empty())
	{
		return m_SubGoals.front()->GetType() != GoalType;
	}

	return true;
}



/*======================================================*/
// 하위 목표로 이동하기 추가
/*======================================================*/
void Goal_Think::AddGoal_MoveToPosition(vector3df pos)
{
	int idx	= -1;


	CGameMap*	pMap =	CGameMap::GetInstance();

	vector3df  br = pMap->getBottomRightUsablePos();
	vector3df  tl = pMap->getTopLeftUsablePos();



	if(m_pOwner->getAllyType() == unit_mine)
	{
		if(pos.Z >= tl.Z || pos.Z <= br.Z ||  pos.X <= tl.X || pos.X >= br.X )
		{
			return ;
		}
	}

	if(CGameMap::GetInstance()->isInBoundaries(pos, idx))
	{
		if((CGameMap::GetInstance()->isWalkableWall(idx)))
		{

			RemoveAllSubgoals();
			AddSubgoal( new Goal_MoveToPosition(m_pOwner, pos));

			return;

		}
	
	}else
	{
		RemoveAllSubgoals();
		AddSubgoal( new Goal_MoveToPosition(m_pOwner, pos));
	}


}

/*======================================================*/
// 하위 목표로 탐험하기 추가
/*======================================================*/
void Goal_Think::AddGoal_Explore()
{
	if (notPresent(goal_explore))
	{
		RemoveAllSubgoals();
		//AddSubgoal( new Goal_Explore(m_pOwner));
	}
}

void Goal_Think::AddGoal_GetItem(unsigned int ItemType)
{
	//if (notPresent(ItemTypeToGoalType(ItemType)))
	//{
	//	RemoveAllSubgoals();
		//AddSubgoal( new Goal_GetItem(m_pOwner, ItemType));
	//}
}




/*======================================================*/
// 하위 목표로 공격하기 추가
/*======================================================*/
void Goal_Think::AddGoal_AttackTarget()
{
	if (notPresent(goal_attack_target))
	{
		RemoveAllSubgoals();
		AddSubgoal( new Goal_AttackTarget(m_pOwner));
	}
}


void Goal_Think::QueueGoal_MoveToPosition(vector3df pos)
{
	//m_SubGoals.push_back(new Goal_MoveToPosition(m_pOwner, pos));
}


/*======================================================*/
// 하위 목표로 죽기 추가
/*======================================================*/
void Goal_Think::AddGoal_Die()
{
	RemoveAllSubgoals();
	AddSubgoal( new Goal_Dead(m_pOwner));
}


/*======================================================*/
// 하위 목표로 수집하기 추가
/*======================================================*/
void Goal_Think::AddGoal_Collecting( const vector3df& pos )
{
	RemoveAllSubgoals();

	AddSubgoal(new Goal_Collecting(m_pOwner, pos));
}


/*======================================================*/
// 하위 목표로 건설하기 추가
/*======================================================*/
void Goal_Think::AddGoal_Building( const vector3df& pos )
{
	RemoveAllSubgoals();

	AddSubgoal(new Goal_Building(m_pOwner, pos));

}


/*======================================================*/
// 하위 목표들 모두 지우기
/*======================================================*/
void Goal_Think::RemoveSubGoals()
{
	RemoveAllSubgoals();
}



/*======================================================*/
// 하위 목표로 헌팅하기 추가
/*======================================================*/
void Goal_Think::AddGoal_HuntTarget()
{
	if (notPresent(goal_hunt_target))
	{
		RemoveAllSubgoals();
		AddSubgoal(new Goal_HuntTarget(m_pOwner));

		//printf("적군 아이디[%d] : Goal_HuntTarget\n", m_pOwner->GetID());
	}
}


/*======================================================*/
// 하위 목표로 철수하기 추가
/*======================================================*/
void Goal_Think::AddGoal_GoingHome()
{
	if (notPresent(goal_goinghome))
	{
		RemoveAllSubgoals();
		AddSubgoal(new Goal_GoingHome(m_pOwner));

		//printf("적군 아이디[%d] : Goal_HuntTarget\n", m_pOwner->GetID());
	}
}



/*======================================================*/
// 하위 목표로 유닛 헌팅 추가
/*======================================================*/
void Goal_Think::AddGoal_UnitHuntTarget()
{
	if (notPresent(goal_unithunt_target))
	{
		RemoveAllSubgoals();
		AddSubgoal(new Goal_UnitHuntTarget(m_pOwner));
	}

		//printf("적군 아이디[%d] : Goal_HuntTarget\n", m_pOwner->GetID());


}


/*======================================================*/
// 하위 목표로 아군 공격하기 추가
/*======================================================*/
void Goal_Think::AddGoal_AttackTargetForEnemy()
{
	if (notPresent(goal_attack_target))
	{
		RemoveAllSubgoals();
		AddSubgoal( new Goal_AttackUnitTarget(m_pOwner));
	}
	//printf(".. ");
}