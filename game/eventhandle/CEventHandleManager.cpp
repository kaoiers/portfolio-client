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
void wcharToChar(const wchar_t* pwstr_src, s32 src_len, char* dest, s32 dest_len)
{
    size_t con_size = 0;
    wcstombs_s( &con_size, dest, src_len, pwstr_src, dest_len);
}

/*======================================================*/
// 생섵자
/*======================================================*/
CEventHandler::CEventHandler()
    :
    wheel_offset(0.0f),
    m_button_id(-1),
    mouse_position(position2d<s16>(0, 0)),
    mouse_relative_position(position2d<f32>(0.0f, 0.0f)),
    m_over_gui(false)
{
    for (u32 i = 0; i<3; i++)
    {
        b_mouse_button_down[i] = false;
        b_mouse_button_up[i] = false;
    }
}

/*======================================================*/
// 원키 업데이트
/*======================================================*/
void CEventHandler::allKeyUpdate()
{
    for (s32 i=0; i<3; i++)
    {
        b_mouse_one_click[i] = false;
        b_mouse_button_up[i] = false;
    }

    for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
    {
        one_key_is_down[i] = false;
    }

    m_pressed_keys.clear();
}

/*======================================================*/
// 마우스 광선 얻어오기
/*======================================================*/
const line3d<f32> CEventHandler::getRay()
{
    //scene::ISceneManager *smgr = CAppContext::GetDevice()->getSceneManager();

    line3d<f32> screen_ray;

    screen_ray.start = vector3df(0, 0, 0);
    screen_ray.end = vector3df(0, 0, 0);

    return screen_ray;
}

/*======================================================*/
// 버튼이 눌렸는지
/*======================================================*/
bool CEventHandler::isClickedButtonID(s16 button_id)
{
    if (m_button_id == button_id)
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
void CEventHandler::setCursorOnGUI(const IGUIObject* obj, const bool on /*= true*/)
{
    m_over_gui = on;
}

/*======================================================*/
// 눌린 키 가져오기
/*======================================================*/
bool CEventHandler::getPressedKey( KeyEventParam& key_param)
{
    if ( m_pressed_keys.empty())
    {
        return false;
    }

    key_param = m_pressed_keys.front();
    m_pressed_keys.erase( m_pressed_keys.begin());

    return true;
}
