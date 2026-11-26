//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/06/22
//
// File Name : IBaseController.h
//
// 오브젝트 컨트롤 인터페이스
//
//////////////////////////////////////////////////////////////////////////

#ifndef BASE_CONTROLLER_H
#define BASE_CONTROLLER_H

class CEventHandler;

/// 객체 선택 진입, 입력 갱신, 선택 종료 및 명령 처리 계약을 정의한다.
class IBaseController
{
public:
    virtual void enterControl() = 0;
    virtual void updateControl(CEventHandler* p_receiver) = 0;
    virtual void exitControl() = 0;
    virtual void onCommand() = 0;

    virtual ~IBaseController() {};
};

#endif
