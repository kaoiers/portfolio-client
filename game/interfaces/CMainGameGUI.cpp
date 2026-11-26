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
#include "../CAppcontext.h"
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

CMainGameGUI::CMainGameGUI(CGameResourceManager& resources, CGameObjectManager& objects, God_Game& game)
    : CGameGUI(position2d<s16>(0, 0)), m_view_model(resources, objects, game), m_game(game)
{
    m_view_model.setObserver([this](const MainGameViewState& state) { m_view_state = state; });
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
void CMainGameGUI::setOwner( CGameObject *owner)
{
}

/*======================================================*/
// 컨트롤
/*======================================================*/
bool CMainGameGUI::interfaceControl(CEventHandler* p_receiver)
{
    refreshView();
    // Picking is engine-specific and unavailable in the source-only sample.
    // A renderer can forward the picked object via selectObject().
    return p_receiver != nullptr;
}

CMainGameGUI::~CMainGameGUI() = default;

/*======================================================*/
// 웨이브 버튼 보이기
/*======================================================*/
void CMainGameGUI::showWaveButton()
{
    IGUIObject* p_button = findElementById(GUI_MAINMENU_WAVESTART_BUTTON);
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
    m_view_model.requestWave();
}

/*======================================================*/
// 레벨 상태 설정
/*======================================================*/
void CMainGameGUI::setLevelStatus(const f32, const u32)
{
    refreshView();
}

/*======================================================*/
// 경험치 더하기
/*======================================================*/
void CMainGameGUI::addPlayerExp( const u32 exp)
{
    m_view_model.requestAddExp(exp);
}

/*======================================================*/
// 경고메시지창 사라지게 하기
/*======================================================*/
void CMainGameGUI::fadeOutWarningMessage(const u32 time_ms)
{
    static u32 pre_time = 0;

    if (pre_time == 0)
        pre_time = time_ms;

    f32 delta = f32(time_ms - pre_time)/1000.0f;
    pre_time = time_ms;
    m_alpha_ratio = m_alpha_ratio - delta * 100.0f;

    if (m_alpha_ratio >= 0.0f)
    {
    }
}

/*======================================================*/
// 사운드 재생
/*======================================================*/
void CMainGameGUI::playSound2D( const char* soundname, const bool loop)
{
    m_game.playSound(soundname, loop);
}

/*======================================================*/
// 3D 사운드
/*======================================================*/
void CMainGameGUI::playSound3D( const char* soundname, const vector3df& pos, const bool loop)
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
void CMainGameGUI::enableDoorButton(const bool on)
{
    m_view_model.setDoorEnabled(on);
}
