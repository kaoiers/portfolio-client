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

#include "../common/UnCopyableUtil.h"


class EffectHandler;

#define	ShaderEffect CLightEffectManager::GetInstance()


class CLightEffectManager : public UnCopyable
{


	unsigned int					FilterType;
	unsigned int					ShadowMode;

public :
	

	
	CLightEffectManager();
	~CLightEffectManager() {};

	static	CLightEffectManager* GetInstance();

	void						drop();
	unsigned int				AddMineShadowLight(const vector3df& position, 	const vector3df& target);
	void						removeNode();
	void						SetMainShadowLightParameter(const f32 farvalue );
	void						setMainLightPositionFromRadius(const f32 radius);
	void						drawAll();

};

#endif