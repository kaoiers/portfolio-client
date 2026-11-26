//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/03/09
//
// File Name : CCameraManager.cpp
// 
// 카메라 관리기
// 
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "CCameraManager.h"
#include "../controller/EnumPickingType.h"
#include "../CAppcontext.h"



/*======================================================*/
// 카메라 이동 속도 지정
/*======================================================*/
void CCameraManager::setMoveSpeed(f32 spd )
{
	//list<ISceneNodeAnimator *>::ConstIterator anm  = (rtsCamera->getAnimators()).getLast();
	
	//CSceneNodeAnimatorCameraRTS * RTSAnimator = static_cast<CSceneNodeAnimatorCameraRTS *>(*anm);

	//RTSAnimator->setMoveSpeed(spd);
}



/*======================================================*/
// 회전 속도 지정
/*======================================================*/
void CCameraManager::setRotationSpeed(f32 spd)
{
	//list<ISceneNodeAnimator *>::ConstIterator anm  = (rtsCamera->getAnimators()).getLast();

	//CSceneNodeAnimatorCameraRTS * RTSAnimator = static_cast<CSceneNodeAnimatorCameraRTS *>(*anm);

	//RTSAnimator->setRotateSpeed(spd);

}


/*======================================================*/
// 줌 속도 지정
/*======================================================*/
void CCameraManager::setZoomSpeed( f32 spd )
{
	//list<ISceneNodeAnimator *>::ConstIterator anm  = (rtsCamera->getAnimators()).getLast();

	//CSceneNodeAnimatorCameraRTS * RTSAnimator = static_cast<CSceneNodeAnimatorCameraRTS *>(*anm);

	//RTSAnimator->setZoomSpeed(spd);

}


/*======================================================*/
// 카메로 포지션 지정
/*======================================================*/
void CCameraManager::setPosition(const vector3df &pos )
{
	//rtsCamera->setPosition(pos);	
}


/*======================================================*/
// 카메라 포지션 가져오기
/*======================================================*/
vector3d<f32> CCameraManager::getPosition( ) const
{
	return vector3d<f32>(0, 0, 0);
}


/*======================================================*/
// 타겟 포지션 지정
/*======================================================*/
void CCameraManager::setTarget(const vector3df &tar )
{

}


/*======================================================*/
// 타겟 포지션 가져오기 
/*======================================================*/
vector3df CCameraManager::getTarget( ) const
{
	return vector3d<f32>(0,0,0);	
}

/*======================================================*/
// 초기화
/*======================================================*/
bool CCameraManager::init()
{


	return true;
}




CCameraManager::~CCameraManager()
{
	
}

CCameraManager::CCameraManager()
{

}



/*======================================================*/
// 회줜 앵글 조정
/*======================================================*/
void CCameraManager::setAngleRange(f32 mina, f32 maxa )
{
 
}


/*======================================================*/
// 카메라 경계 설정
/*======================================================*/
void CCameraManager::setBoundary( const vector2df& topleft, const vector2df& bottomright )
{

}


