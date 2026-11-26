//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/04/08
//
// File Name : CRoomStep.h
//
// 빌딩 과정 처리 클래스
//
//////////////////////////////////////////////////////////////////////////

#ifndef DEF_BUILDINGSTEP
#define DEF_BUILDINGSTEP

#include "../CAppcontext.h"
#include "../shader/CLightEffectManager.h"

class CRoomStep
{
    u32 m_all_steps;
    f32 m_periodical_time;
    std::list<f32> m_step_time;
    CGameRoom* m_room;
    bool m_on_building;

public:
    bool updateBuilding();
    void updateBuildingStatus();

    /*======================================================*/
    // 빌딩중인지
    /*======================================================*/
    const bool isOnBuilding()
    {
        return m_on_building;
    }

    void startBuilding(const u32 time_ms);

    CRoomStep(const ROOM_RESOURCE* res, CGameRoom* p_room)
        :
    m_room(p_room),
    m_periodical_time(0),
    m_on_building(false)

    {
    }

    ~CRoomStep()
    {
        m_step_time.clear();
    }
};

#endif
