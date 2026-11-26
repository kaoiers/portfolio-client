#pragma once

struct Telegram;
class CEventHandler;

/// 게임 객체의 입력, 명령 및 메시지 처리 계약을 정의한다.
class IGameObject
{
public:
    IGameObject() {}
    virtual ~IGameObject() {};

    virtual void control(CEventHandler* p_receiver) = 0;
    virtual void onCommand() = 0;
    virtual bool handleMessage(const Telegram& msg) = 0;
};
