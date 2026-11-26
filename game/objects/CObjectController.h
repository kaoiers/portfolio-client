//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/06/22
//
// File Name : CObjectController.h
// 
// 오브젝트 컨트롤 관리
// 
//////////////////////////////////////////////////////////////////////////



#ifndef OBJECT_CONTROLLER_H
#define OBJECT_CONTROLLER_H
#include "../common/UnCopyableUtil.h"


class IBaseController;
class CEventHandler;
class CObjectSelector;
class CGameObject;
class CParticleManager;



class CObjectController : public UnCopyable
{
	IBaseController*							m_pController;

	CParticleManager*							m_pPlugInParticle;

	CGameObject*								m_pOwner;

	bool										m_bControlState;


	static				CObjectController*		instance;





public :

	static				CObjectController*		GetInstance();
	
	CObjectController();
	~CObjectController() {};

	void				setController(IBaseController * pController);

	void				NullifyController();

	CGameObject*		getOwner() { return m_pOwner; }

	IBaseController*	getController() const { return m_pController; }

	void				getMouseClicked(); 	

	bool				isPossessed(CGameObject * obj);

	bool				IsOnControlState() const;

	void				setControlState(const bool state) { m_bControlState = state;}

	void				update();

	void				CommonEnterControlForType(const u32 type);
	void				CommonUpdateControlForType(const u32 type);


};




#endif