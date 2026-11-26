//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/08/28
//
// File Name : CRoomStockGUI.h
//
// 창고 인터페이스
//
//////////////////////////////////////////////////////////////////////////

#ifndef CROOM_STOCK_GUI_H
#define CROOM_STOCK_GUI_H

#include "CRoomGUI.h"

/// 창고 View의 입력 및 건물 상태 표시를 담당한다.
class CRoomStockGUI : public CRoomGUI
{
    CTextGUI* m_damage_text;

    virtual bool interfaceControl(CEventHandler* p_receiver);

public:
    CRoomStockGUI(position2d<s16> rect = position2di(0, 0)) :
    CRoomGUI(BUILDING_WAREHOUSE, rect) {}

    virtual ~CRoomStockGUI() {};

    virtual void guiInitialize();

};

#endif
