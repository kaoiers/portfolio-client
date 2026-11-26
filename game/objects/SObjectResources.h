//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/06/14
//
// File Name : SObjectResources.h
// 
// 오브젝트 데이터 관련
// 
//////////////////////////////////////////////////////////////////////////

#ifndef OBJECT_RESORUCE_DEFINE
#define OBJECT_RESOURCE_DEFINE

#include "../common/UncopyableUtil.h"

struct CAnimation_Info;
#include <vector>
#include <list>

struct BASIC_OBJECT_RESOURCE
{
	std::vector<CAnimation_Info *> m_Animations;
};



struct ROOM_RESOURCE :  BASIC_OBJECT_RESOURCE
{
	
	u32				m_iWidth_cells;
	u32				m_iHeight_cells;
	vector3di		doorVector;
	f32				m_iBuildingTime;
	s32				NeedGold;
	s32				NeedStone;
	s32				NeedWood;
};


struct UNIT_RESOURCE :   BASIC_OBJECT_RESOURCE
{
	f32				m_fMax_Speed;
	f32				m_fNormal_Speed;
	f32				m_fMass;
	f32				m_fTurnRate;
	f32				m_fMaxForce;
	f32				m_fHitRange;
	u32				m_uAttackFrm1;
	u32				m_uAttackFrm2;
	f32				m_fRadius;
	vector3df		m_vWeaponPos;
	vector3df		m_vWeaponScale;
	u32				m_uWeaponJointNumber;
	u32				m_uProdcutTime;
};







#endif