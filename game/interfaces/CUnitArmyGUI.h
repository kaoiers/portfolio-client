//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/08/08
//
// File Name : CunitArmyGUI.h
//
// 전사 인터페이스
//
//////////////////////////////////////////////////////////////////////////

#ifndef CUNIT_ARMY_H
#define CUNIT_ARMY_H

#include "CUnitGUI.h"

class CUnitArmyGUI : public CUnitGUI
{
    virtual bool interfaceControl(CEventHandler* p_receiver);

public:
    CUnitArmyGUI(position2d<s16> rect = position2di(0, 0)) :
    CUnitGUI(UnitViewRole::Army, rect) {}

    virtual ~CUnitArmyGUI() {};

    virtual void guiInitialize();

};

#endif
