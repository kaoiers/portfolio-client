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

u32 CGameGUI::m_next_valid_id = 0xFFF;


CGameGUI::CGameGUI(position2d<s16> pos )
	:  
m_absolute_position(pos),
m_gid(m_next_valid_id++),
m_need_owner(false),
m_enable(true),
m_owner(NULL),
m_one_button_select(false),
m_focused_object(NULL)
{

}


CGameGUI::~CGameGUI()
{
	
	m_group.clear();

	m_elements.clear();
}


/*======================================================*/
// 보이기
/*======================================================*/
void CGameGUI::show()
{
	GuiElementsList::iterator it;
	
	for(it = m_elements.begin(); it != m_elements.end(); it++)
	{
	
	}
	m_enable = true;

}



/*======================================================*/
// 숨기기
/*======================================================*/
void CGameGUI::hide()
{

	GuiElementsList::iterator it;

	for(it = m_elements.begin(); it != m_elements.end(); it++)
	{
	
	}

	m_enable = false;
}


/*======================================================*/
// 오브젝트 등록
/*======================================================*/
void CGameGUI::registerElement( IGUIObject *p_gui )
{
	m_elements.push_back(p_gui);
}	




/*======================================================*/
//  포지션 설정
/*======================================================*/
void CGameGUI::setPosition( const vector2di pos )
{
}



/*======================================================*/
// 상대 포지션 가져오기
/*======================================================*/
position2d<s16> CGameGUI::getRelativePosition( const position2d<s16> pos ) const
{
	position2d<s16> rel_pos;
	
	return rel_pos;
}


/*======================================================*/
// 절대 포지션 가조오기
/*======================================================*/
position2d<s16> CGameGUI::getAbsolutePosition(const position2d<s16> pos) const
{
	position2d<s16> abs_pos;
	abs_pos.X = m_absolute_position.X + pos.X;
	abs_pos.Y = m_absolute_position.Y + pos.Y;

	return abs_pos;
}


/*======================================================*/
// 모든 오브젝트 컨트롤
/*======================================================*/
bool CGameGUI::elementControl( CEventHandler* m_receiver )
{
	GuiElementsList::iterator it;

	for(it = m_elements.begin(); it != m_elements.end(); it++)
	{
		
	}
	return true;
}


/*======================================================*/
// 컨트롤
/*======================================================*/
bool CGameGUI::control( CEventHandler* m_receiver )
{
	elementControl(m_receiver);

	interfaceControl(m_receiver);

	return true;
}


/*======================================================*/
// 아이디로 오브젝트 찾기
/*======================================================*/
IGUIObject* CGameGUI::findElementById( s16 eid )
{
	GuiElementsList::iterator it;
		
	for(it = m_elements.begin(); it != m_elements.end(); it++)
	{

	}
	
	return NULL;
}

/*======================================================*/
// 버튼 추가
/*======================================================*/
CButtonGUI*CGameGUI::addButton( const position2d<s16> position, const char* default_image, s16 m_id /*= -1 */,std::wstring text /*= 0*/ )
{

	return nullptr;
}

/*======================================================*/
// 원버튼 클릭 처리
/*======================================================*/
void CGameGUI::setOneButtonSelectState( IGUIObject *guiobj )
{
	GuiElementsList::iterator it;

	for(it = m_elements.begin(); it != m_elements.end(); it++)
	{
		
	}	
}



/*======================================================*/
// 모든 버튼 셀렉트로 전환
/*======================================================*/
void	CGameGUI::setAllButtonSelectState(const bool states)
{
	GuiElementsList::iterator it;

	for(it = m_elements.begin(); it != m_elements.end(); it++)
	{
		
	}
}



/*======================================================*/
// 원클릭 버튼 눌렸는지
/*======================================================*/
bool CGameGUI::isOneButtonSelectState()
{
	GuiElementsList::iterator it;

	for(it = m_elements.begin(); it != m_elements.end(); it++)
	{
	}

	return false;
}



/*======================================================*/
//인스턴스
/*======================================================*/
CGUIManager* CGameGUI::getGUIManager()
{
	return CGUIManager::getInstance();

}