//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/08/27
//
// File Name : CRoomJailGUI.h
//
// 감옥실 인터페이스
//
//////////////////////////////////////////////////////////////////////////

#ifndef CROOM_JAIL_GUI_H
#define CROOM_JAIL_GUI_H

#include "IGameGUI.h"

class CGameRoomJail;

class CRoomJailGUI : public CGameGUI
{
    CGameRoomJail* m_owner;

    virtual bool interfaceControl(CEventHandler* p_receiver);

public:
    CRoomJailGUI(position2d<s16> rect = position2di(0, 0)) :
    CGameGUI(rect) {}

    virtual ~CRoomJailGUI() {};

    virtual void guiInitialize();

    virtual void setOwner(CGameObject *obj);
};

#endif
