//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/03/08
//
// File Name : CGameRoomProduct.h
//
// 자원 생산 클래스
//
//////////////////////////////////////////////////////////////////////////

#ifndef GAME_ROOM_PRODUCT_H
#define	GAME_ROOM_PRODUCT_H

#include <map>

#include "../attributes/GameResourceManager.h"
#include "../shader/CLightEffectManager.h"

class CGameRoomProduct
{
    CGameRoomProductBase* m_room;

    const f32 m_status_width, m_status_height, m_bar_width, m_bar_height;

    u32 m_product_completed_time, m_product_time;

    ProductTypes m_product_type;

    bool m_produced;

    void assignTime(const u32 sec);
    void setCompletedEffect();

public:
    CGameRoomProduct(CGameRoomProductBase* p_product_room) :
    m_room(p_product_room),
    m_status_width(250),
    m_status_height(22),
    m_bar_width(240),
    m_bar_height(20),
    m_product_completed_time(0),
    m_product_time(0),
    m_product_type(PRODUCT_COUNTS),
    m_produced(false)

    {
    }

    const bool isProduced() const { return m_produced; }
    void setProduced(const bool pro) { m_produced = pro; }

    f32 productProcessing();
    void setProductToProcessing(ProductTypes type) { m_product_type = type; }

    bool isOnProduct() { return (m_product_completed_time != 0); }

    void turnOnProcessing(ProductTypes type, const u32 sec);
    void completeProcessing();
    void cancelProcessing();

    ~CGameRoomProduct() {};
};

/*======================================================*/
// 자원 생산 처리
/*======================================================*/
inline f32 CGameRoomProduct::productProcessing()
{
    return 0.0f;
}

/*======================================================*/
// 자원 생산 설정하기
/*======================================================*/
inline void CGameRoomProduct::turnOnProcessing( ProductTypes type, const u32 sec)
{
    setProductToProcessing(type);

    assignTime(sec);
}

/*======================================================*/
// 자원 생산 시간 설정하기
/*======================================================*/
inline void CGameRoomProduct::assignTime(const u32 sec)
{
    if (m_product_type != PRODUCT_COUNTS)
    {
    }
}

/*======================================================*/
// 자원 생산 완료 처리
/*======================================================*/

inline void CGameRoomProduct::completeProcessing()
{
    m_product_completed_time = 0;

    m_product_time = 0;

    m_product_type = PRODUCT_COUNTS;

    m_produced = false;

    m_room->collectProductCompleteProcedure();
}

/*======================================================*/
// 처리 취소
/*======================================================*/
inline void CGameRoomProduct::cancelProcessing()
{
    m_product_completed_time = 0;

    m_product_time = 0;

    m_product_type = PRODUCT_COUNTS;
}

/*======================================================*/
// 처리효과 완료
/*======================================================*/
inline void CGameRoomProduct::setCompletedEffect()
{
}

#endif
