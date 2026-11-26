//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/04/06
//
// File Name : CGameUnitProduct.h
//
// 자원 생산 클래스
//
//////////////////////////////////////////////////////////////////////////

#ifndef GAME_UNIT_PRODUCT_H
#define GAME_UNIT_PRODUCT_H

#include "../CAppcontext.h"

/// 유닛 생산에 필요한 처리 상태를 관리하는 클래스이다.
class CGameUnitProduct
{
    CGameRoomWaiting* m_waiting_room;
    UnitTypes m_current_unit_type;
    u32 m_destination_time;
    u32 m_product_duration;
    f32 m_percentage;

    void completeProcessing();

public:
    void beginProcessing(UnitTypes type);
    void updateProcessing(u32 ms);
    void cancelProcessing();
    f32 getPercentage() { return m_percentage; }

    bool isOnProcessing() { return (m_destination_time > 0); }

    CGameUnitProduct(CGameRoomWaiting* p_room) :m_waiting_room(p_room), m_current_unit_type(UNIT_COUNTS), m_destination_time(0), m_product_duration(0), m_percentage(0) {}
    ~CGameUnitProduct() {};
};

/*======================================================*/
// 유닛 생성시 처리
/*======================================================*/
inline void CGameUnitProduct::beginProcessing( UnitTypes type)
{
    m_current_unit_type = type;

    m_product_duration *= 1000;
}

/*======================================================*/
// 유닛 생성과정 업데이트
/*======================================================*/
inline void CGameUnitProduct::updateProcessing( u32 current_time)
{
    if (m_destination_time > 0)
    {
        if (current_time >= m_destination_time)
        {
            completeProcessing();
        }

        m_percentage = f32(m_destination_time - current_time)/f32(m_product_duration);
    }
}

/*======================================================*/
// 프로세싱 완료시 처리
/*======================================================*/
inline void CGameUnitProduct::completeProcessing()
{
    m_waiting_room->createArmy(m_current_unit_type);
    m_waiting_room->hideProcessing();
    m_destination_time = 0;
    m_product_duration = 0;
    m_percentage = 0.0f;
    m_current_unit_type = UNIT_COUNTS;
}

/*======================================================*/
// 유닛 생산 처리 중지하기
/*======================================================*/
inline void CGameUnitProduct::cancelProcessing()
{
    m_waiting_room->hideProcessing();
    m_destination_time = 0;
    m_product_duration = 0;
    m_percentage = 0.0f;
    m_current_unit_type = UNIT_COUNTS;
}

#endif
