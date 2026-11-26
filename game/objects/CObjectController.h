//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/06/22
//
// File Name : CObjectController.h
//
// 오브젝트 컨트롤 관리
//
//////////////////////////////////////////////////////////////////////////

#ifndef OBJECT_CONTROLLER_H
#define OBJECT_CONTROLLER_H
#include "../common/UncopyableUtil.h"

class IBaseController;
class CEventHandler;
class CObjectSelector;
class CGameObject;
class CParticleManager;

class CObjectController : public UnCopyable
{
    IBaseController* m_controller;

    CParticleManager* m_plug_in_particle;

    CGameObject* m_owner;

    bool m_control_state;

    static CObjectController* instance;

public:
    static CObjectController* getInstance();

    CObjectController();
    ~CObjectController()
    {
        if (instance == this)
            instance = nullptr;
    }

    void setController(IBaseController * p_controller);

    void nullifyController();

    CGameObject* getOwner() { return m_owner; }

    IBaseController* getController() const { return m_controller; }

    void getMouseClicked();

    bool isPossessed(CGameObject * obj);

    bool isOnControlState() const;

    void setControlState(const bool state) { m_control_state = state; }

    void update();

    void commonEnterControlForType(const u32 type);
    void commonUpdateControlForType(const u32 type);
};

#endif
