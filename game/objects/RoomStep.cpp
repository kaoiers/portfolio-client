#include <stdafx.h>
#include "CGameRoom.h"
#include "CRoomStep.h"



/*======================================================*/
// 빌딩 시작
/*======================================================*/
void	CRoomStep::startBuilding(const u32 time_ms)
{

}



/*======================================================*/
// 빌딩 지어질 때 업데이트
/*======================================================*/
bool CRoomStep::updateBuilding()
{
	if (m_on_building)
	{
		if (!m_step_time.empty())
		{


		}

		else
		{


			m_on_building = false;

			m_room->setBuildingCompleted();

			return true;
		}

		updateBuildingStatus();
	}
	return false;
}


/*======================================================*/
// 빌딩 상태 업데이트
/*======================================================*/
void CRoomStep::updateBuildingStatus()
{
	double building_process = 0.0; // (m_pTimer->end()) / (m_pRoom->getBuildingTime());

	wchar_t status[30];

	wsprintfW(status, L"%d %% 완료", static_cast<s32>((building_process)*100.0f));

}


