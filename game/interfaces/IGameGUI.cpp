//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/05/05
//
// File Name : CGameGUI.cpp
// 
// GUI 인터페이스
// 
//////////////////////////////////////////////////////////////////////////


#include <stdafx.h>
#include "IGameGUI.h"
#include "../CAppContext.h"
#include "../objects/CGameObject.h"
#include "../God_Game.h"
#include "../eventhandle/CEventHandleManager.h"
#include "CGUIManager.h"

u32 CGameGUI::m_iNextValidID = 0xFFF;


CGameGUI::CGameGUI(position2d<s16> pos )
	:  
m_abolutePosition(pos),
m_gid(m_iNextValidID++),
m_bNeedOwner(false),
m_bEnable(true),
m_pOwner(NULL),
m_bOneButtonSelect(false),
m_pFocusedObject(NULL)
{

}


CGameGUI::~CGameGUI()
{
	
	m_Group.clear();

	m_pElements.clear();
}


/*======================================================*/
// 보이기
/*======================================================*/
void CGameGUI::Show()
{
	GuiElementsList::iterator it;
	
	for(it = m_pElements.begin(); it != m_pElements.end(); it++)
	{
	
	}
	m_bEnable = true;

}



/*======================================================*/
// 숨기기
/*======================================================*/
void CGameGUI::Hide()
{

	GuiElementsList::iterator it;

	for(it = m_pElements.begin(); it != m_pElements.end(); it++)
	{
	
	}

	m_bEnable = false;
}


/*======================================================*/
// 오브젝트 등록
/*======================================================*/
void CGameGUI::RegisterElement( IGUIObject *pGui )
{
	m_pElements.push_back(pGui);
}	




/*======================================================*/
//  포지션 설정
/*======================================================*/
void CGameGUI::SetPosition( const vector2di pos )
{
}



/*======================================================*/
// 상대 포지션 가져오기
/*======================================================*/
position2d<s16> CGameGUI::GetRelativePosition( const position2d<s16> pos ) const
{
	position2d<s16> relPos;
	
	return relPos;
}


/*======================================================*/
// 절대 포지션 가조오기
/*======================================================*/
position2d<s16> CGameGUI::GetAbsolutePosition(const position2d<s16> pos) const
{
	position2d<s16> absPos;
	absPos.X = m_abolutePosition.X + pos.X;
	absPos.Y = m_abolutePosition.Y + pos.Y;

	return absPos;
}


/*======================================================*/
// 모든 오브젝트 컨트롤
/*======================================================*/
bool CGameGUI::element_control( CEventHandler* m_pReceiver )
{
	GuiElementsList::iterator it;

	for(it = m_pElements.begin(); it != m_pElements.end(); it++)
	{
		
	}
	return true;
}


/*======================================================*/
// 컨트롤
/*======================================================*/
bool CGameGUI::control( CEventHandler* m_pReceiver )
{
	element_control(m_pReceiver);

	interface_control(m_pReceiver);

	return true;
}


/*======================================================*/
// 아이디로 오브젝트 찾기
/*======================================================*/
IGUIObject* CGameGUI::FindElementByID( s16 eid )
{
	GuiElementsList::iterator it;
		
	for(it = m_pElements.begin(); it != m_pElements.end(); it++)
	{

	}
	
	return NULL;
}

/*======================================================*/
// 버튼 추가
/*======================================================*/
CButtonGUI*CGameGUI::addButton( const position2d<s16> Position, const char* defaultImage, s16 mID /*= -1 */,std::wstring text /*= 0*/ )
{

	return nullptr;
}

/*======================================================*/
// 원버튼 클릭 처리
/*======================================================*/
void CGameGUI::SetOneButtonSelectState( IGUIObject *guiobj )
{
	GuiElementsList::iterator it;

	for(it = m_pElements.begin(); it != m_pElements.end(); it++)
	{
		
	}	
}



/*======================================================*/
// 모든 버튼 셀렉트로 전환
/*======================================================*/
void	CGameGUI::SetAllButtonSelectState(const bool states)
{
	GuiElementsList::iterator it;

	for(it = m_pElements.begin(); it != m_pElements.end(); it++)
	{
		
	}
}



/*======================================================*/
// 원클릭 버튼 눌렸는지
/*======================================================*/
bool CGameGUI::isOneButtonSelectState()
{
	GuiElementsList::iterator it;

	for(it = m_pElements.begin(); it != m_pElements.end(); it++)
	{
	}

	return false;
}



/*======================================================*/
//인스턴스
/*======================================================*/
CGUIManager* CGameGUI::getGUIManager()
{
	return CGUIManager::GetInstance();

}