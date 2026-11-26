//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/08/11
//
// File Name : CLongTimeRegulator.h
//
// 폰트 생성
//
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "../../basicType.h"

/// GUI에 사용할 폰트 종류와 폰트 자원 참조를 관리한다.
class CFontManager
{
public:
    enum eFONT_TYPE
    {
        FONTTYPE_FOR_GAMESTATUS,
        FONTTYPE_FOR_CHARACTERDAMAGE,
        FONT_TYPE3,
        FONTTYPE_FOR_BUILDINGPROCESS,
        FONTTYPE_SMALL_MAINMENU,

        FONTTYPE_SMALL_MAINMENU14,
        FONTTYPE_SMALL_MAINMENU16,
        FONTTYPE_SMALL_MAINMENU18,
        FONTTYPE_SMALL_MAINMENU20,
        FONT_TYPE4,

        FONTTYPE_FOR_TIME,

        FONT_TYPE_COUNT
    };

    s32* m_font[FONT_TYPE_COUNT];

public:
    CFontManager();
    virtual ~CFontManager();
};
