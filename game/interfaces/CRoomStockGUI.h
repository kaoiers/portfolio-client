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

#include "IGameGUI.h"

class CGameRoomStock;

class CRoomStockGUI : public CGameGUI
{
    CGameRoomStock* m_owner;

    CTextGUI* m_damage_text;

    virtual bool interfaceControl(CEventHandler* p_receiver);

public:
    CRoomStockGUI(position2d<s16> rect = position2di(0, 0)) :
    CGameGUI(rect) {}

    virtual ~CRoomStockGUI() {};

    virtual void guiInitialize();

    virtual void setOwner(CGameObject *obj);
};

#endif
