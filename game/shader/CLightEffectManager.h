//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/10/03
//
// File Name : CLightEffectManager.h
//
// 조명 관리
//
//////////////////////////////////////////////////////////////////////////

#ifndef LIGHTEFFECT_MANAGER_H
#define LIGHTEFFECT_MANAGER_H

#include "../common/UncopyableUtil.h"

class EffectHandler;

#define	ShaderEffect CLightEffectManager::getInstance()

class CLightEffectManager : public UnCopyable
{
    u32 FilterType;
    u32 ShadowMode;

public:
    CLightEffectManager();
    ~CLightEffectManager() {};

    static CLightEffectManager* getInstance();

    void drop();
    u32 addMineShadowLight(const vector3df& position, const vector3df& target);
    void removeNode();
    void setMainShadowLightParameter(const f32 farvalue);
    void setMainLightPositionFromRadius(const f32 radius);
    void drawAll();
};

#endif
