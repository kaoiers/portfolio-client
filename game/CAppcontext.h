//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/02/10
//
// File Name : CAppcontext.h
//
// 게임 주요 개체 중재자, 싱글톤 패턴 사용
//
//////////////////////////////////////////////////////////////////////////

#pragma  once

#include "common/UncopyableUtil.h"

class CGodOption;
class God_Game;
class CShapeDrawer;

class CAppContext : public UnCopyable
{
public:
    static God_Game *getGodGame();
    static CShapeDrawer* getShapeDrawer();
    static CGodOption* getGodOption();
};
