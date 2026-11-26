#pragma once

#include "../../basicType.h"

class CGameObject;
class CEventHandler;

class IBaseGameGUI
{
public :

	IBaseGameGUI() {}
	virtual ~IBaseGameGUI() {}

	virtual	bool			interface_control(CEventHandler* m_pReceiver) = 0;

	virtual void			GUI_Initialize() = 0;

	virtual void			SetOwner(CGameObject *owner) = 0;

	virtual void			setDamage(const u32	damage, const u32	Totaldamage) = 0;
};
