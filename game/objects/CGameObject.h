//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/02/01
//
// File Name : CGameObject.h
// 
// 게임 오브젝트 클래스
// 
//////////////////////////////////////////////////////////////////////////

#pragma  once

#include "IGameObject.h"
#include "EnumObjectType.h"
#include "../controller/EnumPickingType.h"
#include "SObjectResources.h"
#include "CObjectController.h"



enum {	

	ANI_NONE = 0,
	ANI_IDLE1,
	ANI_IDLE2, 
	ANI_WALK,  
	ANI_RUN,
	ANI_WORKING,
	ANI_ATTACK1,
	ANI_ATTACK2,
	ANI_SHOCKED,
	ANI_DIE,
	ANI_BUILDING
};

class	CGameAnimationMgr;
class   CGameObjectManager;
struct	Telegram;
class	CEventHandler;
class	CMainGameGUI;
class	CGameGUI;

class CGameObject : public IGameObject
{
	CGameObjectManager*			m_pObjectManager;

	s32							m_uid;

	s32							m_objType;

	OwnerType					m_eOwnerType;

	bool						m_bSeleted;

	Command_Type				m_CommandType;

	bool						m_bTag;
	
protected:

	bool						m_bEnable;

	CGameAnimationMgr*			m_pAnimgr;

public:	

	static  u32		m_iNextValidID;

	bool         IsTagged()const{return m_bTag;}
	void         Tag(){m_bTag = true;}
	void         UnTag(){m_bTag = false;}
	
	
	CGameObject(OwnerType owner , u32 objtype,
				vector3df pos = vector3df(0.0f, 0.0f, 0.0f),
				vector3df rot = vector3df(0.0f, 0.0f, 0.0f),
				vector3df scale = vector3df(1.0f, 1.0f, 1.0f));


	CGameObject(OwnerType owner , u32 obj_id, u32 objtype,
		vector3df pos = vector3df(0.0f, 0.0f, 0.0f),
		vector3df rot = vector3df(0.0f, 0.0f, 0.0f),
		vector3df scale = vector3df(1.0f, 1.0f, 1.0f));


	virtual						~CGameObject();

	void						setOwnerType(OwnerType owner) { m_eOwnerType = owner; }
	OwnerType			getOwnerType() { return m_eOwnerType; }



	CGameAnimationMgr*			GetAnimationMgr() { return m_pAnimgr; }	
	void						SetID(s32 cid) { m_uid = cid; }
	u32							GetID() {return m_uid;}
	bool						isPossessed();
	CGameObjectManager*			getObjectManager() const { return m_pObjectManager; }
	s32							getObjectType() const { return m_objType; }
	void						setObjectType(const s32 iType) { m_objType = iType;  }
	bool						RemoveSceneNode();

	CMainGameGUI*				getMainGameGUI();
	CGameGUI*			getOwnedGUI();

	void						setCommandType(Command_Type type);
	Command_Type		getCommandType() const { return m_CommandType; }

	void						SetIDFromValidTest();
	bool						SendMessageToAllObjects( double delay, s32 sender, s32 msg, void* ExtraInfo );
	vector3df					getHeightPos();
};






