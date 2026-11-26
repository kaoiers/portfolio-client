//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/06/27
//
// File Name : GameResourceManager.h
// 
// 구리, 은, 쌀 리소스 자원 관리
// 
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "GameResourceManager.h"
#include "../CAppContext.h"
#include "../God_Game.h"
#include "../interfaces/CMainGameGUI.h"



CGameResourceManager* CGameResourceManager::m_pInstance = NULL;

CGameResourceManager::CGameResourceManager(u32 unitLimits) : m_pGameGlobalResource(new GlobalResource()), 
m_iFlag(0), 
TimeDescendentInterval(5), 
LastUpdatedTime(0),
m_uCurrentPlayerLevel(1),
m_uCurrentPlayerExp(0),
m_uUnitCounts(0),
m_uInitialExp(100),
m_uTotalUnitCounts(unitLimits)
{



	m_pInstance = this;
}




/*======================================================*/
// 초기화
/*======================================================*/
void CGameResourceManager::Init()
{


}


/*======================================================*/
// 업데이트
/*======================================================*/
void CGameResourceManager::update(u32 timeMs )
{
	if(!IsAllResourcesSetting())
	{
		if(timeMs >= LastUpdatedTime + TimeDescendentInterval)
		{
			LastUpdatedTime = timeMs;

			IncreaseStatusCycle();
			DecreaseStatusCycle();		
		}
	}

	
	
}


/*======================================================*/
// 목표 수치 표시 증기 시키기 
/*======================================================*/
void CGameResourceManager::IncreaseStatusCycle()
{

	if(m_pGameGlobalResource->crop < CurrentCrop)
	{
		CurrentCrop--;
	}

	if(m_pGameGlobalResource->lumber < CurrentWood)
	{
		CurrentWood--;
	}

	if(m_pGameGlobalResource->stone < CurrentStone)
	{
		CurrentStone--;
	}
}


/*======================================================*/
// 목표 수치 표시 감소 시키기
/*======================================================*/
void CGameResourceManager::DecreaseStatusCycle()
{
	if(m_pGameGlobalResource->crop > CurrentCrop)
	{
		CurrentCrop++;
	}

	if(m_pGameGlobalResource->lumber > CurrentWood)
	{
		CurrentWood++;
	}

	if(m_pGameGlobalResource->stone > CurrentStone)
	{
		CurrentStone++;
	}
}

/*======================================================*/
// 모든 수치들이 목표 수치로 세팅 되었는지
/*======================================================*/
bool CGameResourceManager::IsAllResourcesSetting() const
{
	return !((m_pGameGlobalResource->stone != CurrentStone) 
		|| (m_pGameGlobalResource->lumber != CurrentWood) 
		|| (m_pGameGlobalResource->crop != CurrentCrop));

}


/*======================================================*/
// 경험치 추가하기
/*======================================================*/
void CGameResourceManager::AddPlayerExp( u32 exp )
{
	if(CAppContext::GetGodGame()->getCurrentGameState() == God_Game::on_game ||
		CAppContext::GetGodGame()->getCurrentGameState() == God_Game::on_intro
		)
	{
		IncreaseExp(exp);
		CMainGameGUI* pGUI = CMainGameGUI::GetInstance();
		f32 a = float(int(m_uCurrentPlayerExp));
		f32 b = float(getMaxPlayerExp(m_uCurrentPlayerLevel));
		pGUI->setLevelStatus( a/b , m_uCurrentPlayerLevel);		
	}
}


/*======================================================*/
// 경험치 추가하기
/*======================================================*/
void CGameResourceManager::IncreaseExp( u32 exp )
{
	u32 maxExp =  getMaxPlayerExp(m_uCurrentPlayerLevel);

	u32 tempExp = m_uCurrentPlayerExp + exp;

	if(maxExp <= tempExp)
	{
		m_uCurrentPlayerLevel++;
		m_uCurrentPlayerExp = 0;
		IncreaseExp((tempExp - maxExp));
		
	}
	
	else
	{
		m_uCurrentPlayerExp = tempExp;
	}

	
}



/*======================================================*/
// 현제래벨 경험치 최대치 가져오기
/*======================================================*/
u32 CGameResourceManager::getMaxPlayerExp(u32 level)
{
	if(level == 0)
		return 0;

	return (100 * u32(pow(double(level), 1.2)) + m_uInitialExp);
}



/*======================================================*/
// 네트워크용 
/*======================================================*/
void CGameResourceManager::OnNetworkSetResources(unsigned int crop,
												 unsigned int woods,
												 unsigned int gold )
{
	GlobalResource temp;
	temp.crop = crop;
	temp.lumber = woods;
	temp.stone = gold;

	(*m_pGameGlobalResource) = temp;

	//printf("[리소스]진짜 보내주나??\n");
}


/*======================================================*/
// 네크워크용
/*======================================================*/
bool CGameResourceManager::isOnMyGame()
{
	return (CAppContext::GetGodGame()->getCurrentGameState() == God_Game::on_game);

}



/*======================================================*/
// 유닛 수 더하기
/*======================================================*/
void CGameResourceManager::addUnitCounts()
{
	m_uUnitCounts++;

}


/*======================================================*/
// 유닛 수 빼기
/*======================================================*/
void CGameResourceManager::SubstractUnitCounts()
{
	m_uUnitCounts--;
}