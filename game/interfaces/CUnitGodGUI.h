//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/08/04
//
// File Name : CUnitGodGUI.h
//
// 신수 인터페이스
//
//////////////////////////////////////////////////////////////////////////

#ifndef CUNIT_GOD_H
#define CUNIT_GOD_H

#include "CUnitGUI.h"

/// 신수 View의 입력을 역할별 ViewModel 명령으로 연결한다.
class CUnitGodGUI : public CUnitGUI
{
    virtual bool interfaceControl(CEventHandler* p_receiver);

public:
    CUnitGodGUI(position2d<s16> rect = position2di(0, 0)) :
    CUnitGUI(UnitViewRole::God, rect) {}

    virtual ~CUnitGodGUI() {};

    virtual void guiInitialize() {}

};

#endif
