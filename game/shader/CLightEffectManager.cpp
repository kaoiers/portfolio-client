//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/10/03
//
// File Name : CLightEffectManager.cpp
// 
// 조명 관리
// 
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>

#include "CLightEffectManager.h"
#include "../CAppcontext.h"
#include "../option/CGodOption.h"

CLightEffectManager::CLightEffectManager(  )

{

}


/*======================================================*/
// 인스턴스
/*======================================================*/
CLightEffectManager* CLightEffectManager::getInstance()
{
	static std::unique_ptr<CLightEffectManager> instance = std::make_unique<CLightEffectManager>();

	return	instance.get();
}



/*======================================================*/
// 렌더링
/*======================================================*/
void CLightEffectManager::drawAll()
{

}


/*======================================================*/
// 인스턴스 삭제
/*======================================================*/
void CLightEffectManager::drop()
{	
	
}



/*======================================================*/
// 노드에 가해진 효과 없애기
/*======================================================*/
void CLightEffectManager::removeNode(  )
{

}



/*======================================================*/
// 쉐도우 라이트 파라미터 지정
/*======================================================*/
void CLightEffectManager::setMainShadowLightParameter( const f32 farvalue )
{

}


/*======================================================*/
// 메인 라이팅 포지션 지정
/*======================================================*/
void CLightEffectManager::setMainLightPositionFromRadius( const f32 radius )
{
	f32	new_value = 0.0f;


}



/*======================================================*/
// 현재 GUI 지정
/*======================================================*/
u32 CLightEffectManager::addMineShadowLight( const vector3df& position, const vector3df& target )
{
	return 0;

}



