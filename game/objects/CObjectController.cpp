//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/06/22
//
// File Name : CObjectController.cpp
// 
// 오브젝트 컨트롤 관리
// 
//////////////////////////////////////////////////////////////////////////


#include <stdafx.h>
#include "../CAppContext.h"
#include "../God_Game.h"
#include "../objects/CGameObject.h"
#include "../objects/CObjectController.h"
#include "../objects/IBaseController.h"

#include <map>
#include "../Plugin/PluginManager.h"
#include "../Plugin/plugin.h"
#include "../shader/CLightEffectManager.h"
#include "../objects/CGameRoom.h"
#include "../interfaces/CControllerGUI.h"
#include "../objects/CGameUnit.h"



CObjectController*		CObjectController::instance = NULL;



CObjectController::CObjectController() : m_pController(0), m_pOwner(0), m_bControlState(0), m_pPlugInParticle(0)
{

	

	
	//ShaderEffect->ExcludeLightingCalculations(m_pSpotLight);

	
	//ShaderEffect->setMaterialFlag(video::EMF_LIGHTING, false);
	

	//m_pSpotLight->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
	//m_pSpotLight->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF);


	//m_pSpotLight->set

	//m_pSpotLight->setLightType(video::E_LIGHT_TYPE::ELT_SPOT);

	instance = this;
}



/*======================================================*/
// 인스턴트
/*======================================================*/
CObjectController* CObjectController::GetInstance()
{
	return instance;
}


/*======================================================*/
// 컨트롤 설정
/*======================================================*/
void CObjectController::setController( IBaseController * pController )
{
	if( m_pController != pController)
	{
		if(m_pController)
		{
			m_pController->exit_control();
			CControllerGUI::Instance()->DisableGUI();
		}

		m_pController = pController;

		pController->enter_control();	

		m_pOwner = dynamic_cast<CGameObject *>(m_pController);		

		CommonEnterControlForType(m_pOwner->getObjectType());

		m_bControlState = false;
	}
}


/*======================================================*/
// 업데이트
/*======================================================*/
void CObjectController::update()
{
	if(m_pController)
	{
		CommonUpdateControlForType(m_pOwner->getObjectType());

		m_pController->update_control(CAppContext::GetGodGame()->getEventHandler());


	}
}


/*======================================================*/
// 컨트롤 중인지
/*======================================================*/
bool CObjectController::IsOnControlState() const
{
	if(m_pController == 0)
	{
		return false;		
	}

	CGameObject* obj = dynamic_cast<CGameObject *>(m_pController);

	if(obj->getCommandType() != com_none)
	{
		return true;
	}


	return false;
}

/*======================================================*/
// 개체가 컨트롤을 가지고 있는지
/*======================================================*/
bool CObjectController::isPossessed( CGameObject * obj )
{
	return (m_pOwner == obj);
}


/*======================================================*/
// 타입마다 컨트롤 설정
/*======================================================*/
void CObjectController::CommonEnterControlForType( const u32 type )
{
	switch(type)
	{
	case GODTYPE_UNIT : 
		{

		
		}		

		break;
		
	case GODTYPE_BUILDING : 

			
		break; 
	}

}


/*======================================================*/
// 컨트롤별 컨트롤 업데이트
/*======================================================*/
void CObjectController::CommonUpdateControlForType( const u32 type )
{
	switch(type)
	{

	case GODTYPE_UNIT : 
		break; 

	case GODTYPE_BUILDING : 

		break;

	default : 


		break;
	}
}


/*======================================================*/
// 컨트롤러 무효화
/*======================================================*/
void CObjectController::NullifyController()
{
	if(m_pController)
	{
		m_pController->exit_control();

		m_pOwner = 0;
	}

	CControllerGUI::Instance()->DisableGUI();


	m_pController = 0;

}