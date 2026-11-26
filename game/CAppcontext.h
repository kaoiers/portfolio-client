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

/// 기존 게임 시스템 접근점을 제공하는 컨텍스트 어댑터이다.
class CAppContext : public UnCopyable
{
public:
    static God_Game *getGodGame();

    static CGodOption* getGodOption();
};
