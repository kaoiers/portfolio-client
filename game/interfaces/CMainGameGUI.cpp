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



#include "../objects/CGameRoom.h"
#include "../map/CGameMap.h"

#include "../attributes/GameResourceManager.h"

#include "../camera/CCameraManager.h"

#include "../PlugIn/PluginManager.h"




CMainGameGUI	*CMainGameGUI::m_instance = NULL;




CMainGameGUI::CMainGameGUI(CGameObjectManager*	p_obj_man) : 
CGameGUI(position2d<s16>(0, 0)),
m_building(NULL), 
m_obj_man(p_obj_man), 
m_object_select_available(true), 
m_game_resource_manager(0), 
m_level_bar(0),
m_alpha_ratio(0.0f)
{
	

	m_instance = this;

	m_game = CAppContext::getGodGame();
	

	
	
}



/*======================================================*/
// GUI 별도 초기화
/*======================================================*/
void CMainGameGUI::guiInitialize()
{
	show();
	

	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////






}





/*======================================================*/
// 인터페이스 주인 오브젝트 설정
/*======================================================*/
void CMainGameGUI::setOwner( CGameObject *owner )
{

}




/*======================================================*/
// 컨트롤
/*======================================================*/
bool CMainGameGUI::interfaceControl( CEventHandler * p_receiver )
{
	

	u32 millyseconds = 0;

	fadeOutWarningMessage(millyseconds);

	if(m_game_resource_manager)
		m_game_resource_manager->update(millyseconds);

	if(p_receiver->isMouseLUp() 
		&& !p_receiver->isCursorOnGUI() 
		&& !m_obj_man->isOnControlState() && CAppContext::getGodGame()->getCurrentGameState() == God_Game::on_game )
	{	
		CGameObject *obj = nullptr; // m_pObjMan->getPicker()->getMouseOverObject(pReceiver);
		
		{
			if(obj->getObjectType() == GODTYPE_UNIT)
			{
				CGameUnit* unit = dynamic_cast<CGameUnit *>(obj);

				if(unit->getAllyType() == unit_mine)
				{
					m_obj_man->setController(unit);
					
				}
			}
			
			else if(obj->getObjectType() == GODTYPE_BUILDING)
			{
				CGameRoom* room = dynamic_cast<CGameRoom *>(obj);

				m_obj_man->setController(room);
			}
		}
	}


	return true;
}






CMainGameGUI::~CMainGameGUI()
{
	SAFE_DELETE(m_game_resource_manager);
}




/*======================================================*/
// 웨이브 버튼 보이기
/*======================================================*/
void CMainGameGUI::showWaveButton()
{
	IGUIObject*	p_button =  findElementById(GUI_MAINMENU_WAVESTART_BUTTON);
}



/*======================================================*/
// 타이머 시작하기
/*======================================================*/
void CMainGameGUI::startTimer()
{
	IGUIObject* p_text_gui = findElementById(GUI_MAINMENU_TIME_TEXT);
}




/*======================================================*/
// 타이머 이벤트 끝내기
/*======================================================*/
void CMainGameGUI::endTimerEvent()
{
	CGameMap::getInstance()->startEnemyGenerate();	
	


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
void CMainGameGUI::addPlayerExp( const u32 exp )
{
	m_game_resource_manager->addPlayerExp(exp);
}





/*======================================================*/
// 경고메시지창 사라지게 하기
/*======================================================*/
void CMainGameGUI::fadeOutWarningMessage(const u32 time_ms)
{
	static u32 pre_time = 0;

	if(pre_time == 0)
		pre_time = time_ms;

	f32 delta = f32(time_ms - pre_time)/1000.0f;
	pre_time = time_ms;
	m_alpha_ratio = m_alpha_ratio - delta * 100.0f; 

	if(m_alpha_ratio >= 0.0f)
	{
	}
}


/*======================================================*/
// 사운드 재생
/*======================================================*/
void CMainGameGUI::playSound2D( const char* soundname , const bool loop)
{	
	m_game->playSound(soundname, loop);		
}




/*======================================================*/
// 3D 사운드
/*======================================================*/
void CMainGameGUI::playSound3D( const char* soundname , const vector3df& pos , const bool loop )
{


}



/*======================================================*/
// 사운드 종료
/*======================================================*/
void CMainGameGUI::stopAllSounds()
{

}




/*======================================================*/
// 놀러가기 버튼 활성화
/*======================================================*/
void CMainGameGUI::enableDoorButton( const bool on )
{

}