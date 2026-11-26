#pragma once

struct Telegram;
class CEventHandler;

class IGameObject
{
public:

	IGameObject() {}
	virtual ~IGameObject() {};

	virtual	void				control(CEventHandler* p_receiver) = 0;
	virtual	void				onCommand() = 0;
	virtual bool				handleMessage(const Telegram& msg) = 0;
};
