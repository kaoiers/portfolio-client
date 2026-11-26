//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/03/30
//
// File Name : CEventHandleManager.cpp
// 
// 게임 이벤트 관리
// 
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "CEventHandleManager.h"
#include "../CAppcontext.h"
#include "../God_Game.h"
#include "../interfaces/CGUIManager.h"


/*======================================================*/
// wchar -> char
/*======================================================*/
void WCharToChar(const wchar_t* pwstrSrc, int src_len, char* dest, int dest_len)
{
//	WideCharToMultiByte( 949, 0, pwstrSrc, -1, pstr, len, NULL, NULL);

	size_t conSize = 0;
	wcstombs_s( &conSize ,dest, src_len, pwstrSrc,  dest_len);
}



/*======================================================*/
// 생섵자
/*======================================================*/
CEventHandler::CEventHandler()
	:
	iOffsetWheel(0.0f),
	m_iButtonID(-1),
	MousePosition(position2d<s32>(0, 0)),
	MouseRelativePosition(position2d<f32>(0.0f, 0.0f)),
	m_bOverGUI(false)
{
	for (u32 i = 0; i<3; i++)
	{
		bMouseButtonDown[i] = false;
		bMouseButtonUp[i] = false;
	}

}



/*======================================================*/
// 원키 업데이트
/*======================================================*/
void CEventHandler::allkeyUpdate()
{
	for(int i=0; i<3; i++)
	{
		bMouseOneclick[i] = false;
		bMouseButtonUp[i] = false;
	}

	for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
	{
		OneKeyIsDown[i] = false;
	}

	m_pressedKeys.clear();
}



/*======================================================*/
// 마우스 광선 얻어오기
/*======================================================*/
const line3d<f32> CEventHandler::getRay()
{
	//scene::ISceneManager *smgr = CAppContext::GetDevice()->getSceneManager();

	//position2d<s32> clickScreenPos(getMousePosition());

	//line3df screenRay = smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(clickScreenPos, smgr->getActiveCamera());

	line3d<f32> screenRay;

	screenRay.start = vector3df(0,0,0);
	screenRay.end = vector3df(0,0,0);

	return screenRay;
}





/*======================================================*/
// 버튼이 눌렸는지
/*======================================================*/
bool CEventHandler::isClickedButtonID(s32 buttonID)
{
	if(m_iButtonID == buttonID)
	{
		return true;
	}

	return false;
}


/*======================================================*/
// 마우스가 스크린 밖으로 나갔는지
/*======================================================*/
const bool CEventHandler::isMouseOutOfScreen()
{
	return (getRelativeMousePosition().X > 1.0/* || 
			getMousePosition().X < 0 ||
			u32(getMousePosition().Y) > CAppContext::GetDevice()->getVideoDriver()->getScreenSize().Height ||
			getMousePosition().Y < 0*/
			
			);
}


/*======================================================*/
// 커서 GUI 설정
/*======================================================*/
void CEventHandler::setCursorOnGUI(const IGUIObject* obj,  const bool on /*= true*/ )
{	
	m_bOverGUI = on;
}



/*======================================================*/
// 눌린 키 가져오기
/*======================================================*/
bool CEventHandler::getPressedKey( KeyEventParam& keyParam )
{
	if( m_pressedKeys.empty() )
	{
		return false;
	}

	keyParam = m_pressedKeys.front();
	m_pressedKeys.erase( m_pressedKeys.begin() );

	return true;
}