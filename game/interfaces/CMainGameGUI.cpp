//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/06/30
//
// File Name : CMainGameGUI.cpp
// 
// 게임 메인 GUI 
// 
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include <list>

#include "CMainGameGUI.h"

#include "../objects/CGameObject.h"
#include "../eventhandle/CEventHandleManager.h"
#include "../objects/CGameObjectManager.h"
#include "../CAppContext.h"
#include "../God_Game.h"
#include "CGUIManager.h"

#include "CLoginGUI.h"

#include "../objects/CGameUnitTiger.h"
#include "../objects/CGameRoom.h"

#include "../shader/CLightEffectManager.h"

// #include "network/CNetworkManager.h"
// #include "PacketGame.h"
// #include "network/CNetworkManager.h"


#include "../objects/CGameRoom.h"
#include "../map/CGameMap.h"

#include "../attributes/GameResourceManager.h"

#include "../camera/CCameraManager.h"

#include "../PlugIn/PluginManager.h"


// #include "web/WebBrowserView.h"
// #include "CWebGUI.h"
// #include "CWebDialog.h"

//NETWORK
// PACKET_GAME_WAVE_START_CL_AG_REQ* CreateWaveStartPacket()
// {
// 	return (new PACKET_GAME_WAVE_START_CL_AG_REQ());
// }

CMainGameGUI	*CMainGameGUI::m_pInstance = NULL;




CMainGameGUI::CMainGameGUI(CGameObjectManager*	pObjMan) : 
CGameGUI(position2d<s16>(0, 0)),
m_pBuilding(NULL), 
m_pObjMan(pObjMan), 
m_bObjectSelectAvailable(true), 
m_pGameResourceManager(0), 
m_pLevelBar(0),
m_fAlphaRatio(0.0f)
{
	

	m_pInstance = this;

	m_pGame = CAppContext::GetGodGame();
	
	//m_playerId		= INVALID_PLAYER_ID;

	
	
//SetNeedOwner(true);
}



/*======================================================*/
// GUI 별도 초기화
/*======================================================*/
void CMainGameGUI::GUI_Initialize()
{
	Show();
	

	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////






}





/*======================================================*/
// 인터페이스 주인 오브젝트 설정
/*======================================================*/
void CMainGameGUI::SetOwner( CGameObject *owner )
{

}




/*======================================================*/
// 컨트롤
/*======================================================*/
bool CMainGameGUI::interface_control( CEventHandler * pReceiver )
{
	

	u32 millyseconds = 0;

	FadeOutWarningMessage(millyseconds);

	if(m_pGameResourceManager)
		m_pGameResourceManager->update(millyseconds);

	if(pReceiver->isMouseLUp() 
		&& !pReceiver->isCursorOnGUI() 
		&& !m_pObjMan->isOnControlState() && CAppContext::GetGodGame()->getCurrentGameState() == God_Game::on_game )
	{	
		CGameObject *obj = nullptr; // m_pObjMan->getPicker()->getMouseOverObject(pReceiver);
		
		{
			if(obj->getObjectType() == GODTYPE_UNIT)
			{
				CGameUnit* unit = dynamic_cast<CGameUnit *>(obj);

				if(unit->getAllyType() == unit_mine)
				{
					m_pObjMan->setController(unit);
					
				}
			}
			
			else if(obj->getObjectType() == GODTYPE_BUILDING)
			{
				CGameRoom* room = dynamic_cast<CGameRoom *>(obj);

				m_pObjMan->setController(room);
			}
		}
	}


	return true;
}






CMainGameGUI::~CMainGameGUI()
{
	SAFE_DELETE(m_pGameResourceManager);
}




/*======================================================*/
// 웨이브 버튼 보이기
/*======================================================*/
void CMainGameGUI::showWaveButton()
{
	IGUIObject*	pButton =  FindElementByID(GUI_MAINMENU_WAVESTART_BUTTON);
}



/*======================================================*/
// 타이머 시작하기
/*======================================================*/
void CMainGameGUI::StartTimer()
{
	IGUIObject* pTextGUI = FindElementByID(GUI_MAINMENU_TIME_TEXT);
}




/*======================================================*/
// 타이머 이벤트 끝내기
/*======================================================*/
void CMainGameGUI::EndTimerEvent()
{
	CGameMap::GetInstance()->StartEnemyGenerate();	
	


}



/*======================================================*/
// 레벨 상태 설정
/*======================================================*/
void CMainGameGUI::setLevelStatus( const f32 percent, const u32 level )
{

}



/*======================================================*/
// 경험치 더하기
/*======================================================*/
void CMainGameGUI::AddPlayerExp( const u32 exp )
{
	m_pGameResourceManager->AddPlayerExp(exp);
}





/*======================================================*/
// 경고메시지창 사라지게 하기
/*======================================================*/
void CMainGameGUI::FadeOutWarningMessage(const u32 timeMs)
{
	static u32 preTime = 0;

	if(preTime == 0)
		preTime = timeMs;

	f32 delta = f32(timeMs - preTime)/1000.0f;
	preTime = timeMs;
	m_fAlphaRatio = m_fAlphaRatio - delta * 100.0f; 

	if(m_fAlphaRatio >= 0.0f)
	{
	}
}


/*======================================================*/
// 사운드 재생
/*======================================================*/
void CMainGameGUI::playSound2D( const char* soundname , const bool loop)
{	
	m_pGame->playSound(soundname, loop);		
}




/*======================================================*/
// 3D 사운드
/*======================================================*/
void CMainGameGUI::playSound3D( const char* soundname , const vector3df& pos , const bool loop )
{
	//vector3df Campos  = CAppContext::GetDevice()->getSceneManager()->getActiveCamera()->getPosition();

	//vector3df SoundPos = Campos - pos;

	//m_pGame->getPluginManager()->getSoundManager()->PlaySound3D(soundname, SoundPos ,loop);
}



/*======================================================*/
// 사운드 종료
/*======================================================*/
void CMainGameGUI::playoffAllSounds()
{

}




/*======================================================*/
// 놀러가기 버튼 활성화
/*======================================================*/
void CMainGameGUI::EnableDoorButton( const bool on )
{

}