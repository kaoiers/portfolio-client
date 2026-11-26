//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/06/27
//
// File Name : GameResourceManager.h
//
// 구리, 은, 쌀 리소스 자원 관리
//
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "../../basicType.h"

#include <memory>

#define GameResource CGameResourceManager::getInstance()


/// 현재 자원 수량을 전달하는 값 타입이다.
struct GlobalResource
{
    u32 crop;
    u32 lumber;
    u32 stone;
};

/// 플레이어 자원, 레벨, 경험치 및 유닛 수를 관리하는 모델이다.
class CGameResourceManager
{
    std::unique_ptr<GlobalResource> m_game_global_resource;
    u32 m_current_player_level;
    u32 m_current_player_exp;
    const u32 m_initial_exp;
    u32 m_unit_counts;
    u32 m_total_unit_counts;

    u32 m_flag;
    const u32 time_descendent_interval;

    u32 last_updated_time;
    u32 current_crop = 0, current_stone = 0, current_wood = 0;


    static CGameResourceManager* m_instance;

public:
    CGameResourceManager(u32 unit_limits = 10);

    ~CGameResourceManager();

    void init();

    static CGameResourceManager* getInstance() { return m_instance; };

    void update(u32 time_ms);
    void increaseStatusCycle();
    void decreaseStatusCycle();
    bool isAllResourcesSetting() const;

    void addPlayerExp(u32 exp);
    void increaseExp( u32 exp);
    u32 getCurrentLevel() const { return m_current_player_level; }
    u32 getCurrentExp() const { return m_current_player_exp; }
    GlobalResource getResources() const { return *m_game_global_resource; }

    void addUnitCounts();
    void subtractUnitCounts();
    u32 getUnitCounts() const { return m_unit_counts; }
    u32 getTotalUnitCounts() const { return m_total_unit_counts; }
    u32 getMaxPlayerExp(u32 level) const;

    inline void addAllResources(s32 g, s32 l, s32 s)
    {
        GlobalResource temp;
        temp.crop = g;
        temp.lumber = l;
        temp.stone = s;
    }

    inline void addCropResource(u32 crop)
    {
        GlobalResource temp;
        temp.crop = crop;
    }

    inline void addLumberResource(u32 lum)
    {
        GlobalResource temp;
        temp.lumber = lum;
    }

    inline void addStoneResource(u32 stone)
    {
        GlobalResource temp;
        temp.stone = stone;
    }

    bool isOnMyGame();

public:
    void onNetworkSetResources(u32 crop,
        u32 woods, u32 gold);
};
