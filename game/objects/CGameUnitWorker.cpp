//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/04/06
//
// File Name : CGameUnitWorker.h
// 
// 게임 유닛 일꾼
// 
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include <list>
#include "CGameUnitWorker.h"
#include "../ai/Goal_Think.h"
#include "../eventhandle/CEventHandleManager.h"

#include "../ai/God_Messages.h"
#include "../interfaces/CControllerGUI.h"
#include "../interfaces/CMainGameGUI.h"

#include "../ai/Goal_Think.h"
#include "CGameObjectManager.h"
#include "CGameRoom.h"

#include "../attributes/GameResourceManager.h"
#include "../map/CGameMap.h"

/*======================================================*/
// 개별 초기화
/*======================================================*/
void CGameUnitWorker::PrivateInitialize()
{}





/*======================================================*/
//근거리 공격
/*======================================================*/
bool CGameUnitWorker::short_attack( CGameUnit* pTarget )
{
	



	return false;
}

CGameUnitWorker::CGameUnitWorker(OwnerType owner, unsigned int obj_id, unsigned int objtype,
								 const UNIT_RESOURCE* resource, const GAMEUNIT_ATTRIBUTE* attribute, 
								 UnitTypes unittype, const vector3df& pos /*= vector3df(0.0f, 0.0f, 0.0f)*/
								 , const vector3df& rot /*= vector3df(0.0f, 0.0f, 0.0f)*/
								 , const vector3df& scale /*= vector3df(1.0f, 1.0f, 1.0f)*/ )
								  : CGameUnit(owner , objtype, resource, attribute ,unittype, unit_mine, pos, rot, scale)
								  ,m_bBuildingComplete(false), m_pControlRoom(0), m_pBuildRoom(0),m_pProductRoom(0), m_bFixRoomToGround(false), m_bNetworkOnBuilding(false)
{
	CGameResourceManager::GetInstance()->addUnitCounts();	
	

}

CGameUnitWorker::~CGameUnitWorker()
{
	CGameResourceManager::GetInstance()->SubstractUnitCounts();	

	CGameMap::GetInstance()->WorkerDeadEvent();

	RemoveSubGoals();
}


/*======================================================*/
// 빌딩 목표 추가
/*======================================================*/
void CGameUnitWorker::AddGoal_Building( const vector3df& pos )
{
	m_pBrain->AddGoal_Building(pos);
}



/*======================================================*/
// 빌딩 시작하기
/*======================================================*/
void CGameUnitWorker::BuildingStart()
{
//===========================================================
//패킷 보내기(네트워크관련)
//===========================================================
// 	if(this->getOwnerType() == object_mine)
// 	{
// 		SendPacketStartBuildingReq(m_pBuildRoom, this);
// 	}

	m_pBuildRoom->BuildingStart(10);
}


/*======================================================*/
// 컨트롤 종료
/*======================================================*/
void CGameUnitWorker::exit_control()
{
	CControllerGUI::Instance()->DisableGUI();
}



/*======================================================*/
// 컨트롤 시작
/*======================================================*/
void CGameUnitWorker::enter_control()
{
	CControllerGUI::Instance()->setWorkerGUI(this);
}


/*======================================================*/
// 컨트롤 업데이트
/*======================================================*/
void CGameUnitWorker::update_control( CEventHandler* pReceiver )
{
	BuildingControl(pReceiver);

	CollectingControl(pReceiver);

	if(pReceiver->isMouseROneClick() 
		&& !m_pControlRoom 
		&& !m_pBuildRoom 
		&& this->getCommandType() == com_none
		&& !pReceiver->isCursorOnGUI())
	{
		m_pBrain->AddGoal_MoveToPosition(pReceiver->getMouseUpGroundPosition());	
	}	 
}


/*======================================================*/
// 빌딩용 컨트롤
/*======================================================*/
void CGameUnitWorker::BuildingControl( CEventHandler* pReceiver )
{
	if(m_pControlRoom && this->getCommandType() == com_building && !m_bFixRoomToGround)
	{
		m_pControlRoom->FollowMouse(pReceiver);

		if(m_pControlRoom->isBuildable(pReceiver->getMouseUpGroundPosition()))
		{
			m_pControlRoom->setBuildableColor(true);

			if(pReceiver->isMouseLOneClick() && !pReceiver->isCursorOnGUI())
			{
				m_pControlRoom->RemoveAndLinkNodes();

				
				//OnNetWorkBuildStartViewCommand(m_pControlRoom);

				m_pBuildRoom = m_pControlRoom;

				

				this->AddGoal_Building(m_pControlRoom->GetFrontPosToBuilding());

				//m_pControlRoom = 0;
				

				//if(m_pControlRoom->isNotWalkableRoom())
				//{
					//m_pControlRoom = 0;

					//this->getObjectManager()->setControlState(false);

				//}				
				//else
				//{


				//SendPacketBuildingReq(m_pControlRoom, this->GetID());				

				//m_bFixRoomToGround = true;

				m_pControlRoom->makeBaseGround();
				PushControlCompletedRoom();	

				m_bFixRoomToGround = false;

				

				//PushControlCompletedRoom();

				//}
			}
			


		}else
		{
			m_pControlRoom->setBuildableColor(false);			

		}



 		if(pReceiver->isMouseRUp())
 		{
 			CancelBuilding();		
 		}




	}

}


/*======================================================*/
// 빌딩 추가하기
/*======================================================*/
void CGameUnitWorker::AddBuilding( BuildingTypes roomType )
{
	if(!m_pControlRoom && !m_pBuildRoom)
	{
		m_pControlRoom = this->getObjectManager()->AddRoom(object_mine, roomType, 0, this);

		this->getObjectManager()->setControlState(true);

		this->setCommandType(com_building);
	}

}


/*======================================================*/
//빌딩 완료되었는지
/*======================================================*/
const	bool CGameUnitWorker::isBuildingCompleted() 
{
	return m_pBuildRoom->isBuildingCompleted();
}


/*======================================================*/
// 컨트롤 완료된 룸 추가하기
/*======================================================*/
void CGameUnitWorker::PushControlCompletedRoom()
{
	m_pBuildRoom = m_pControlRoom;	

	m_pControlRoom = 0;	

	this->getObjectManager()->setControlState(false);

	this->setCommandType(com_none);

	
	if(m_pBuildRoom && !isBuildingCompleted())
	{
		AddGoal_Building(m_pBuildRoom->GetFrontPosToBuilding());
	}

}



/*======================================================*/
// 업데이트
/*======================================================*/
void CGameUnitWorker::update(u32 timeMs)
{
	UpdateMoveMent(timeMs);

	UpdateBuildingRoom();

	m_pBrain->Process();

}




/*======================================================*/
// 빌딩완료된 룸 빼기
/*======================================================*/
void CGameUnitWorker::PopBuildingCompletedRoom()
{
	m_pBuildRoom = 0;	
}




/*======================================================*/
// 빌딩 취소
/*======================================================*/
void CGameUnitWorker::CancelBuilding()
{
	m_pBrain->AddGoal_MoveToPosition(this->Pos());

	if(m_pBuildRoom)
	{
		m_pBuildRoom->DeleteRoom();	
		m_pBuildRoom = 0;	
	}


	if(m_pControlRoom)
		CancelControl();
	
}




/*======================================================*/
// 네트워크용
/*======================================================*/
void CGameUnitWorker::OnNetWorkBuildCommand()
{
	//m_pControlRoom->RemoveAndLinkNodes();
	//m_pControlRoom->makeBaseGround();
	m_pControlRoom->makeBaseGround();
	PushControlCompletedRoom();	

	m_bFixRoomToGround = false;

	
}




/*======================================================*/
// 네트워크용
/*======================================================*/
void CGameUnitWorker::OnNetWorkBuildStartCommand(unsigned int seconds)
{
	m_pBuildRoom->BuildingStart(seconds);
}


/*======================================================*/
// 빌딩 컨트롤 취소하기
/*======================================================*/
void CGameUnitWorker::CancelControl()
{
	if(m_pControlRoom)
	{
		this->getObjectManager()->DeleteRequest(m_pControlRoom->GetID());					
		m_pControlRoom = 0;
		//this->setObjectType(com_none);
	}

	this->setCommandType(com_none);
}



/*======================================================*/
// 컨트롤 룸 가져오기
/*======================================================*/
CGameRoom* CGameUnitWorker::getBackRoom()
{
	return m_pBuildRoom;
}

/*======================================================*/
// 하위 목표 삭제
/*======================================================*/
void CGameUnitWorker::RemoveSubGoals()
{
	m_pBrain->RemoveAllSubgoals();
}


/*======================================================*/
// 채집 완료 완료
/*======================================================*/
void CGameUnitWorker::CollectingComplete()
{

	//네트워크관련 
	//NetworkPacketSpace::SendCollectCompleteReqPacket(m_pProductRoom->GetID());
	//m_pProductRoom->CollectProduct();
	this->ObtainExp(70);
}


/*======================================================*/
// 채집 컨트롤 처리
/*======================================================*/
void CGameUnitWorker::CollectingControl( CEventHandler* pReceiver )
{
	if(this->getCommandType() == com_collection)
	{
		if(pReceiver->isMouseLOneClick())
		{	

		}

		else if(pReceiver->isMouseRUp())
		{
			this->setCommandType(com_none);

		}
	}

}


/*======================================================*/
// 워킹 애니메이션
/*======================================================*/
void CGameUnitWorker::WorkingAnimation(const vector3df& dir)
{

}

/*======================================================*/
// 워킹 애니메이션 끄기
/*======================================================*/
void CGameUnitWorker::OffWorkingAnimation()
{

}


/*======================================================*/
// 네트워크용
/*======================================================*/
void CGameUnitWorker::OnNetWorkBuildStartViewCommand(CGameRoom*	pRoom )
{
	m_bNetworkOnBuilding = true;

	m_vNetworkOnBuildingPos = pRoom->GetFrontPosToBuilding();
}


/*======================================================*/
// 네트워크용
/*======================================================*/
void CGameUnitWorker::OnNetWorkBuildCompleteViewCommand()
{
	m_bNetworkOnBuilding = false;
	OffWorkingAnimation();
}


/*======================================================*/
// 업데이트 빌딩하기
/*======================================================*/
void CGameUnitWorker::UpdateBuildingRoom()
{
	if(m_bNetworkOnBuilding && getOwnerType() == object_frined)
	{
		if(this->isAtPosition(m_vNetworkOnBuildingPos))
		{

			SetHeading((m_vNetworkOnBuildingPos - Pos()).normalize() );


			WorkingAnimation(vector3df(0,0,0));
		}
	}


}
