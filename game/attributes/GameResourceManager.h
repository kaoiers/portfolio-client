//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/06/27
//
// File Name : GameResourceManager.h
//
// 구리, 은, 쌀 리소스 자원 관리
//
//////////////////////////////////////////////////////////////////////////

#define GameResource CGameResourceManager::getInstance()

class CTextGUI;

struct GlobalResource
{
    u32 crop;
    u32 lumber;
    u32 stone;
};

class CGameResourceManager
{
    GlobalResource* m_game_global_resource;
    u32 m_current_player_level;
    u32 m_current_player_exp;
    const u32 m_initial_exp;
    u32 m_unit_counts;
    u32 m_total_unit_counts;

    u32 m_flag;
    const u32 time_descendent_interval;

    u32 last_updated_time;
    u32 current_crop, current_stone, current_wood;

    CTextGUI* text_gold;
    CTextGUI* text_lumber;
    CTextGUI* text_stone;
    CTextGUI* text_unit;

    static CGameResourceManager* m_instance;

public:
    CGameResourceManager(u32 unit_limits = 10);

    ~CGameResourceManager()
    {
        SAFE_DELETE(m_game_global_resource);
    }

    void init();

    static CGameResourceManager* getInstance() { return m_instance; };

    void update(u32 time_ms);
    void increaseStatusCycle();
    void decreaseStatusCycle();
    bool isAllResourcesSetting() const;

    void addPlayerExp(u32 exp);
    void increaseExp( u32 exp);
    const u32 getCurrentLevel() { return m_current_player_level; }

    void addUnitCounts();
    void subtractUnitCounts();
    const u32 getUnitCounts() { return m_unit_counts; }
    const u32 getTotalUnitCounts() { return m_total_unit_counts; }
    u32 getMaxPlayerExp(u32 level);

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
