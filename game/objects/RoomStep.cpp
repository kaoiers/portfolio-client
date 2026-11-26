#include <stdafx.h>
#include "CGameRoom.h"
#include "CRoomStep.h"



/*======================================================*/
// 빌딩 시작
/*======================================================*/
void	CRoomStep::StartBuilding(const u32 timeMs)
{

}



/*======================================================*/
// 빌딩 지어질 때 업데이트
/*======================================================*/
bool CRoomStep::UpdateBuilding()
{
	if (m_bOnBuilding)
	{
		if (!m_uStepTime.empty())
		{


		}

		else
		{

			//m_pRoom->GetSceneNode()->setMesh(m_pRoomMesh);
			//m_pRoom->GetSceneNode()->setMaterialFlag(video::EMF_LIGHTING, false);

			m_bOnBuilding = false;

			m_pRoom->setBuildingCompleted();

			return true;
		}

		UpdateBuildingStatus();
	}
	return false;
}


/*======================================================*/
// 빌딩 상태 업데이트
/*======================================================*/
void CRoomStep::UpdateBuildingStatus()
{
	double building_process = 0.0; // (m_pTimer->end()) / (m_pRoom->getBuildingTime());

	wchar_t status[30];

	wsprintfW(status, L"%d %% 완료", static_cast<int>((building_process)*100.0f));

}


