//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/03/09
//
// File Name : CCameraManager.h
//
// 카메라 관리기
//
//////////////////////////////////////////////////////////////////////////

#include "../common/UncopyableUtil.h"

class CAppContext;

/// 카메라 위치와 이동 설정 인터페이스를 제공하며 엔진 의존 구현은 일부 생략되어 있다.
class CCameraManager : private UnCopyable
{
public:
    CCameraManager();
    virtual ~CCameraManager();
    bool init();

    void setPosition(const vector3df &pos);
    vector3df getPosition() const;
    void setTarget(const vector3df &tar);
    vector3df getTarget() const;

    ///////////////////////////////////////////////////////
    void setRotationSpeed(f32 spd);
    void setMoveSpeed(f32 spd);
    void setZoomSpeed(f32 spd);
    void setAngleRange(f32 mina, f32 maxa);
    void setBoundary(const vector2df& topleft, const vector2df& bottomright);
};
