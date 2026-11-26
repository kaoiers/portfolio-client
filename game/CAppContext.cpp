//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/02/10
//
// File Name : CAppcontext.cpp
//
// 게임 주요 개체 싱글톤
//
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "CAppcontext.h"
#include "God_Game.h"
#include "option/CGodOption.h"

/*======================================================*/
// 게임 인스턴스 가져오기
/*======================================================*/
God_Game* CAppContext::getGodGame()
{
    return God_Game::getInstance();
}

/*======================================================*/
// 옵션 정보 가져오기
/*======================================================*/
CGodOption* CAppContext::getGodOption()
{
    return CGodOption::getInstance();
}

