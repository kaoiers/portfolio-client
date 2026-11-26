//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/05/07
//
// File Name : CGUIManager.cpp
// 
// GUI 매니져
// 
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "CGUIManager.h"

#include "../CAppContext.h"
#include "../God_Game.h"
#include "../eventhandle/CEventHandleManager.h"
#include "CMainGameGUI.h"
#include "../attributes/GameResourceManager.h"
#include "CLoginGUI.h"
#include "CControllerGUI.h"
//#include "CWebDialog.h"

CGUIManager* CGUIManager::m_pInstance = NULL;




CGUIManager::CGUIManager()
: m_pMouseCursorGUI(0), m_pMainGameGUI(0), m_pPopUpGUI(0), m_pWebDialog(NULL)
{
	m_pInstance = this;

	m_pFontManager = new CFontManager();	
}

CGUIManager::~CGUIManager()
{
	for( GUIMap::iterator it = m_pGUIs.begin(); it != m_pGUIs.end(); ++it )
	{
		SAFE_DELETE(it->second);
	}

	m_pGUIs.clear();

	delete	m_pFontManager;
}


/*======================================================*/
// 모든 오브젝트 컨트롤
/*======================================================*/
bool CGUIManager::control( CEventHandler* pReceiver )
{
	GUIMap::iterator itr;

	for(itr = m_pGUIs.begin(); itr != m_pGUIs.end(); itr++)
	{
		if(!(itr->second)->isEnable()) continue;
		
		
		(itr->second)->control(pReceiver);			
	}
	
	return true;
}



/*======================================================*/
// 모든 오브젝트 렌더링
/*======================================================*/
bool CGUIManager::render()
{	
	GUIMap::iterator itr;// = (--(m_pGUIs.end()));

	
	return true;
}


/*======================================================*/
// 아이디로 GUI 등록하기
/*======================================================*/
void CGUIManager::RegisterGUIByID( CGameGUI *pGui )
{
	m_pGUIs[pGui->GetID()] = pGui;
}


/*======================================================*/
// 아이디로부터 인터페이스 찾기
/*======================================================*/
CGameGUI* CGUIManager::FindInterfaceFromID( int cid )
{
	GUIMap::iterator itr = m_pGUIs.find(cid);
	
	if(itr != m_pGUIs.end())
	{
		return itr->second;
	}
	return NULL;
}



/*======================================================*/
// Register and initialize the GUI.
/*======================================================*/
void CGUIManager::Interface_Init(CGameGUI* BaseGUI)
{
	if(BaseGUI)
	{
		RegisterGUIByID(BaseGUI);
		BaseGUI->GUI_Initialize();	
	}
}




/*======================================================*/
// 인터페이스 불러오기
/*======================================================*/
bool CGUIManager::GameLoading( )
{


	return true;
}



/*======================================================*/
// 마지막으로 저장된 GUI ID
/*======================================================*/
unsigned int CGUIManager::getLastGUIID()
{
	GUIMap::iterator itr;
	itr = m_pGUIs.end();
	itr--;
	return (itr->second)->GetID();	
}





/*======================================================*/
// GUI가 눌렸는지
/*======================================================*/
bool CGUIManager::IsPressed()
{
	GUIMap::iterator itr;

	for(itr = m_pGUIs.begin(); itr != m_pGUIs.end(); itr++)
	{
		if((itr->second)->isClicked() == true)
		{
			return true;					
		}				
	}	
	return false;
}


/*======================================================*/
// 이벤트 전 
/*======================================================*/
bool CGUIManager::PostEvent( const SEvent& event )
{
	GUIMap::iterator itr;

	for(itr = m_pGUIs.begin(); itr != m_pGUIs.end(); itr++)
	{
		if((itr->second)->isEnable())
		{
 			(itr->second)->PostEvent(event);
		}				
	}
	
	return true;
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


