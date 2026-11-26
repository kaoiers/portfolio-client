//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/04/30
//
// File Name : CRoomUpTowerGUI.h
//
// 업그레이드 타워 인터페이스
//
//////////////////////////////////////////////////////////////////////////

#ifndef CROOM_UP_TOWER_GUI_H
#define CROOM_UP_TOWER_GUI_H

#include "CRoomGUI.h"

/// 업그레이드 타워의 화면 표시와 입력 인터페이스를 담당한다.
class CRoomUpTowerGUI : public CRoomGUI
{
    virtual bool interfaceControl(CEventHandler* p_receiver);

public:
    CRoomUpTowerGUI(position2d<s16> rect = position2di(0, 0)) :
    CRoomGUI(BUILDING_TOWER, rect) {}

    virtual ~CRoomUpTowerGUI() {};

    virtual void guiInitialize();

};

#endif
