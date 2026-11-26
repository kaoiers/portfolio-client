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
#include "../CAppcontext.h"
#include "../God_Game.h"
#include "../interfaces/CMainGameGUI.h"

CGameResourceManager* CGameResourceManager::m_instance = nullptr;

CGameResourceManager::CGameResourceManager(u32 unit_limits) : m_game_global_resource(std::make_unique<GlobalResource>()),
    m_flag(0),
    time_descendent_interval(5),
    last_updated_time(0),
    m_current_player_level(1),
    m_current_player_exp(0),
    m_unit_counts(0),
    m_initial_exp(100),
    m_total_unit_counts(unit_limits)
{
    m_instance = this;
}

/*======================================================*/
// 초기화
/*======================================================*/
void CGameResourceManager::init()
{
}

/*======================================================*/
// 업데이트
/*======================================================*/
void CGameResourceManager::update(u32 time_ms)
{
    if (!isAllResourcesSetting())
    {
        if (time_ms >= last_updated_time + time_descendent_interval)
        {
            last_updated_time = time_ms;

            increaseStatusCycle();
            decreaseStatusCycle();
        }
    }
}

/*======================================================*/
// 목표 수치 표시 증기 시키기
/*======================================================*/
void CGameResourceManager::increaseStatusCycle()
{
    if (m_game_global_resource->crop < current_crop)
    {
        current_crop--;
    }

    if (m_game_global_resource->lumber < current_wood)
    {
        current_wood--;
    }

    if (m_game_global_resource->stone < current_stone)
    {
        current_stone--;
    }
}

/*======================================================*/
// 목표 수치 표시 감소 시키기
/*======================================================*/
void CGameResourceManager::decreaseStatusCycle()
{
    if (m_game_global_resource->crop > current_crop)
    {
        current_crop++;
    }

    if (m_game_global_resource->lumber > current_wood)
    {
        current_wood++;
    }

    if (m_game_global_resource->stone > current_stone)
    {
        current_stone++;
    }
}

/*======================================================*/
// 모든 수치들이 목표 수치로 세팅 되었는지
/*======================================================*/
bool CGameResourceManager::isAllResourcesSetting() const
{
    return !((m_game_global_resource->stone != current_stone)
        || (m_game_global_resource->lumber != current_wood)
        || (m_game_global_resource->crop != current_crop));
}

/*======================================================*/
// 경험치 추가하기
/*======================================================*/
void CGameResourceManager::addPlayerExp( u32 exp)
{
    if (CAppContext::getGodGame()->getCurrentGameState() == God_Game::GameState::on_game ||
        CAppContext::getGodGame()->getCurrentGameState() == God_Game::GameState::on_intro
    )
    {
        increaseExp(exp);
        CMainGameGUI* p_gui = CMainGameGUI::getInstance();
        f32 a = f32(s32(m_current_player_exp));
        f32 b = f32(getMaxPlayerExp(m_current_player_level));
        p_gui->setLevelStatus( a/b, m_current_player_level);
    }
}

/*======================================================*/
// 경험치 추가하기
/*======================================================*/
void CGameResourceManager::increaseExp( u32 exp)
{
    u32 max_exp = getMaxPlayerExp(m_current_player_level);

    u32 temp_exp = m_current_player_exp + exp;

    if (max_exp <= temp_exp)
    {
        m_current_player_level++;
        m_current_player_exp = 0;
        increaseExp((temp_exp - max_exp));
    }

    else
    {
        m_current_player_exp = temp_exp;
    }
}

/*======================================================*/
// 현제래벨 경험치 최대치 가져오기
/*======================================================*/
u32 CGameResourceManager::getMaxPlayerExp(u32 level)
{
    if (level == 0)
        return 0;

    return (100 * u32(pow(double(level), 1.2)) + m_initial_exp);
}

/*======================================================*/
// 네트워크용
/*======================================================*/
void CGameResourceManager::onNetworkSetResources(u32 crop,
    u32 woods,
    u32 gold)
{
    GlobalResource temp;
    temp.crop = crop;
    temp.lumber = woods;
    temp.stone = gold;

    (*m_game_global_resource) = temp;
}

/*======================================================*/
// 네크워크용
/*======================================================*/
bool CGameResourceManager::isOnMyGame()
{
    return (CAppContext::getGodGame()->getCurrentGameState() == God_Game::GameState::on_game);
}

/*======================================================*/
// 유닛 수 더하기
/*======================================================*/
void CGameResourceManager::addUnitCounts()
{
    m_unit_counts++;
}

/*======================================================*/
// 유닛 수 빼기
/*======================================================*/
void CGameResourceManager::subtractUnitCounts()
{
    m_unit_counts--;
}
