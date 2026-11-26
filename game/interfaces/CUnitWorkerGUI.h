//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/06/26
//
// File Name : CUnitWorkerGUI.h
//
// 일꾼 인터페이스
//
//////////////////////////////////////////////////////////////////////////

#ifndef CUNIT_WOKRER_H
#define CUNIT_WORKER_H

#include "CUnitGUI.h"

enum
{
    COMMAND_ATTACK_BUTTON = 7200,
    COMMAND_WORKING_BUTTON,
    COMMAND_BUILDING_BUTTON,
    COMMAND_BUILDING_JAIL,
    COMMAND_BUILDING_WAREHOUSE,
    COMMAND_BUILDING_WAITING,
    COMMAND_BUILDING_TOWER,
    COMMAND_BUILDING_FARM,
    COMMAND_BUILDING_WOOD,
    COMMAND_BUILDING_GOLD,
    COMMAND_BUILDING_FRIEND,
    COMMAND_BUILDING_CANCEL,
    COMMAND_BUILDING_BACK,
    COMMAND_BUILDING_BUILDINGBACK,
    COMMAND_BUILDING_WORKERBACK,
    COMMAND_BUILDING_ARROWL,
    COMMAND_BUILDING_ARROWR
};

/// 일꾼 View의 채집 및 건설 입력을 ViewModel 명령으로 연결한다.
class CUnitWorkerGUI : public CUnitGUI
{
    virtual bool interfaceControl(CEventHandler* p_receiver);

public:
    CUnitWorkerGUI(position2d<s16> rect = position2di(0, 0)) :
    CUnitGUI(UnitViewRole::Worker, rect) {}

    virtual ~CUnitWorkerGUI() {};

    virtual void guiInitialize() {}

};

#endif
