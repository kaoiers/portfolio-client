#pragma once

#include "../../basicType.h"

class CGameObject;
class CEventHandler;

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
