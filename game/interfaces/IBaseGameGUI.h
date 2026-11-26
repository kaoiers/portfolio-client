#pragma once

#include "../../basicType.h"

class CGameObject;
class CEventHandler;

/// GUI 초기화, 소유 객체 바인딩, 입력 및 상태 갱신 계약을 정의한다.
class IBaseGameGUI
{
public:
    IBaseGameGUI() {}
    virtual ~IBaseGameGUI() {}

    virtual bool interfaceControl(CEventHandler* m_receiver) = 0;

    virtual void guiInitialize() = 0;

    virtual void setOwner(CGameObject *owner) = 0;

    virtual void setDamage(const u32 damage, const u32 total_damage) = 0;
};
