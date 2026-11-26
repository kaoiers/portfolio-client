#pragma once

struct Telegram;
class CEventHandler;

class IGameObject
{
public:

	IGameObject() {}
	virtual ~IGameObject() {};

	virtual	void				control(CEventHandler* pReceiver) = 0;
	virtual	void				OnCommand() = 0;
	virtual bool				HandleMessage(const Telegram& msg) = 0;
};
