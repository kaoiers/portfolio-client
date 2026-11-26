//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/11/09
//
// File Name : CGodOption.h
//
// 게임 옵션 설정 클래스
//
//////////////////////////////////////////////////////////////////////////

#ifndef GOD_OPTION_H
#define GOD_OPTION_H

#include "../common/UncopyableUtil.h"

class CGodOption : private UnCopyable
{
    bool m_use_sound; //	사운드
    bool m_use_shader; //	쉐이더
    bool m_use_shadow; //	그림자
    bool m_use_volume; //	볼륨
    bool m_use_full_screen; //	풀스크린

public:
    CGodOption() :
    m_use_sound(false),
    m_use_shader(false),
    m_use_shadow(false),
    m_use_volume(false),
    m_use_full_screen(false)

    {
    }

    ~CGodOption()
    {};

    void setUseSound(bool _on) { m_use_sound = _on; }
    void setUseShader(bool _on) { m_use_shader = _on; }
    void setUseShadow(bool _on) { m_use_shadow = _on; }
    void setUseVolume(bool _on) { m_use_volume = _on; }
    void setUseFullScreen(bool _on) { m_use_full_screen = _on; }

    const bool isSoundOn() const { return m_use_sound; }
    const bool isShaderOn() const { return m_use_shader; }
    const bool isShadowOn() const { return m_use_shadow; }
    const bool isVolumeOn() const { return m_use_volume; }
    const bool isFullScreen() const { return m_use_full_screen; }

    static CGodOption* getInstance();
};

#endif
