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

#include "CRoomGUI.h"

class CRoomJailGUI : public CRoomGUI
{
    virtual bool interfaceControl(CEventHandler* p_receiver);

public:
    CRoomJailGUI(position2d<s16> rect = position2di(0, 0)) :
    CRoomGUI(BUILDING_JAIL, rect) {}

    virtual ~CRoomJailGUI() {};

    virtual void guiInitialize();

};

#endif
