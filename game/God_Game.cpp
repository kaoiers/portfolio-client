//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/01/30
//
// File Name : God_Game.cpp
// 
// 게임 메인
// 
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "God_Game.h"
#include "objects/CGameObjectManager.h"
#include "objects/CGameObject.h"
#include "camera/CCameraManager.h"
#include "eventhandle/CEventHandleManager.h"
#include "CAppContext.h"
#include "controller/EnumPickingType.h"
#include "interfaces/CGUIManager.h"
#include "PlugIn/PluginManager.h"


#include "map/CGameMap.h"
#include "objects/CObjectController.h"
#include "objects/CGameUnit.h"
#include "interfaces/CLoginGUI.h"
#include "shader/CLightEffectManager.h"
#include "interfaces/CMainGameGUI.h"
#include "option/CGodOption.h"


God_Game::God_Game() 
: 
m_eGameState(on_intro),
m_bRunning(true)
{

}



God_Game::~God_Game()
{
	
}


/*======================================================*/
// 게임 로딩 처리
/*======================================================*/
bool God_Game::GameLoading()
{
	m_pGUIManager = std::make_unique<CGUIManager>();
	m_pEventHandler = std::make_unique<CEventHandler>();
	m_pObjectManager = std::make_unique<CGameObjectManager>();
	m_pGUIManager->GameLoading();	
	m_pCameraManager = std::make_unique<CCameraManager>();
	m_pCameraManager->Init();
	m_pGameMap		= std::make_unique<CGameMap>(getObjectManager());
	
	setGameState(God_Game::on_game);	
	
	m_pGameMap->init(60, 80,  10, 10);
	m_pGUIManager->GameLoadingComplete();

	return true;
}

/*======================================================*/
// 게임 리셋
/*======================================================*/
bool God_Game::GameReset()
{



	return true;

}


/*======================================================*/
// 초기화
/*======================================================*/
bool God_Game::Initialize()
{
	GameLoading();

	return true;
}


/*======================================================*/
// 렌더링
/*======================================================*/
void God_Game::render()
{
	if(m_eGameState == on_game || m_eGameState == on_friend)
	{
		if(CAppContext::GetGodOption()->isShaderOn())
		{
		}
		else
		{
		}
		if(m_pGameMap)
			m_pGameMap->render();


	}else
	{
	}



	if(m_pGUIManager)
		m_pGUIManager->render();

}	

/*======================================================*/
// 업데이트
/*======================================================*/
void God_Game::upadte(u32 timeMs)
{


	if(m_eGameState == on_game || m_eGameState == on_friend)
	{
		//순서유의
		if(m_pObjectManager)
			m_pObjectManager->update();


		if(m_pGameMap)
			m_pGameMap->update(timeMs);
	}

	if(m_pEventHandler)
		m_pEventHandler->update();	
}




/*======================================================*/
// 컨트롤
/*======================================================*/
bool God_Game::control()
{
	if(m_pGUIManager)
		m_pGUIManager->control(m_pEventHandler.get());			
	
	if(m_eGameState == on_game || m_eGameState == on_friend)
	{
		if(m_pObjectManager)
			m_pObjectManager->control(m_pEventHandler.get());
	}

	return true;
}




/*======================================================*/
// 인터페이스 렌더링
/*======================================================*/
void God_Game::DrawScneneForInterface()
{

	if(m_pGUIManager)
	{
		m_pGUIManager->render();
	}

}



/*======================================================*/
// 인스턴스
/*======================================================*/
God_Game* God_Game::GetInstance()
{
	static std::unique_ptr<God_Game> Instance = std::make_unique<God_Game >();

	return Instance.get();
}



/*======================================================*/
// 게임 초기화
/*======================================================*/
void God_Game::ClearGame(const GameState state )
{
	m_eGameState = state;

	m_pGameMap->removeAllTrees();

	m_pObjectManager->setController(NULL);

	m_pObjectManager->RemoveAllObjects();

	m_pCameraManager->Init();

	if(m_eGameState == on_friend)
		m_pGUIManager->getMainGameGUI()->EnableDoorButton(true);
	else
		m_pGUIManager->getMainGameGUI()->EnableDoorButton(false);
}


/*======================================================*/
// 사운드 플레이
/*======================================================*/
void God_Game::playSound( const char *sundName, const bool loop /*= true*/ )
{
	
}




/*======================================================*/
// 경고 박스 띄우기
/*======================================================*/
void WarningBox( const std::wstring str )
{
}

