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
#include "../CAppContext.h"
#include "../option/CGodOption.h"

CLightEffectManager::CLightEffectManager(  )

{

}


/*======================================================*/
// 인스턴스
/*======================================================*/
CLightEffectManager* CLightEffectManager::GetInstance()
{
	static std::unique_ptr<CLightEffectManager> Instance = std::make_unique<CLightEffectManager>();

	return	Instance.get();
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
void CLightEffectManager::SetMainShadowLightParameter( const f32 farvalue )
{
	//m_pEffectHandler->getShadowLight(0).setPosition(vector3df(0, farvalue, 0));

	//m_pEffectHandler->getShadowLight(0).set
}


/*======================================================*/
// 메인 라이팅 포지션 지정
/*======================================================*/
void CLightEffectManager::setMainLightPositionFromRadius( const f32 radius )
{
	f32	newValue = 0.0f;

	//newValue =   radius/(45 * DEGTORAD);

}



/*======================================================*/
// 현재 GUI 지정
/*======================================================*/
unsigned int CLightEffectManager::AddMineShadowLight( const vector3df& position, const vector3df& target )
{
	return 0;

}



