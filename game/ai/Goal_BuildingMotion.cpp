//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/03/08
//
// File Name : Goal_BuildingMotion.cpp
// 
// 단일 목적 : 빌딩 모션 취하기
//
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "Goal_BuildingMotion.h"
#include "../objects/CGameUnitWorker.h"


/*======================================================*/
//  빌딩 애니메이션 시작하기 
/*======================================================*/
void Goal_BuildingMotion::Activate()
{
	m_iStatus = active;

	m_pWorker = dynamic_cast<CGameUnitWorker *>(m_pOwner);

	m_pWorker->BuildingStart();

	

}


/*======================================================*/
//  빌딩 애니메이션 처리
/*======================================================*/
s32 Goal_BuildingMotion::Process()
{
	ActivateIfInactive();




 	if(m_pWorker->isBuildingCompleted())
 	{

		m_iStatus = completed;		 

		m_pWorker->PopBuildingCompletedRoom();

		m_pWorker->ObtainExp(50);
		
 	}
	
	else
	{
		//if(!(m_pWorker->GetAnimationMgr()->IsOnAnimation(ANI_WORKING)))
		{
			m_pWorker->setCurrentAni(ANI_WORKING, false);
		}
	}

	m_pWorker->SetHeading(vector3df(0,0,1));


	return m_iStatus;
}


/*======================================================*/
//  빌딩 애니메이션 끝내기
/*======================================================*/
void Goal_BuildingMotion::Terminate()
{
	m_iStatus = completed;		 

	//m_pWorker->PopBuildingCompletedRoom();

	//m_iStatus = completed;

	//m_pWorker->PopBuildingCompletedRoom();


}

Goal_BuildingMotion::Goal_BuildingMotion( CGameUnit* pUnit ) : Goal<CGameUnit>(pUnit, goal_buildingMotion)
{

}