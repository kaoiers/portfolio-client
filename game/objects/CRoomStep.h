//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/04/08
//
// File Name : CRoomStep.h
// 
// 빌딩 과정 처리 클래스
// 
//////////////////////////////////////////////////////////////////////////

#ifndef DEF_BUILDINGSTEP
#define DEF_BUILDINGSTEP


#include "../CAppContext.h"
#include "../interfaces/CGUIManager.h"
#include "../shader/CLightEffectManager.h"


class CRoomStep
{
	u32								m_uAllSteps;
	f32								m_fPeriodicalTime;
	std::list<f32>					m_uStepTime;
	CGameRoom*						m_pRoom;
	bool							m_bOnBuilding;

public :

	bool							UpdateBuilding();
	void							UpdateBuildingStatus();
	
	
	/*======================================================*/
	// 빌딩중인지
	/*======================================================*/
	const bool CRoomStep::isOnBuilding()
	{
		return  m_bOnBuilding;
	}

	void							StartBuilding(const u32 timeMs);

	CRoomStep(const ROOM_RESOURCE* res, CGameRoom*	pRoom) 
	:   
		m_pRoom(pRoom),
		m_fPeriodicalTime(0),
		m_bOnBuilding(false)
	
	{
	}

	~CRoomStep()
	{
		m_uStepTime.clear();
	}
};



#endif