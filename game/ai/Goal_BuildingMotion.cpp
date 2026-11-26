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
void Goal_BuildingMotion::activate()
{
	m_status = active;

	m_worker = dynamic_cast<CGameUnitWorker *>(m_owner);

	m_worker->buildingStart();

	

}


/*======================================================*/
//  빌딩 애니메이션 처리
/*======================================================*/
s32 Goal_BuildingMotion::process()
{
	activateIfInactive();




 	if(m_worker->isBuildingCompleted())
 	{

		m_status = completed;		 

		m_worker->popBuildingCompletedRoom();

		m_worker->obtainExp(50);
		
 	}
	
	else
	{
		{
			m_worker->setCurrentAni(ANI_WORKING, false);
		}
	}

	m_worker->setHeading(vector3df(0,0,1));


	return m_status;
}


/*======================================================*/
//  빌딩 애니메이션 끝내기
/*======================================================*/
void Goal_BuildingMotion::terminate()
{
	m_status = completed;		 





}

Goal_BuildingMotion::Goal_BuildingMotion( CGameUnit* p_unit ) : Goal<CGameUnit>(p_unit, goal_buildingMotion)
{

}