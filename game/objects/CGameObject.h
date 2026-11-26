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
	CGameObjectManager*			m_object_manager;

	s32							m_uid;

	s32							m_obj_type;

	OwnerType					m_owner_type;

	bool						m_selected;

	Command_Type				m_command_type;

	bool						m_tag;
	
protected:

	bool						m_enable;

	CGameAnimationMgr*			m_animgr;

public:	

	static  u32		m_next_valid_id;

	bool         isTagged()const{return m_tag;}
	void         tag(){m_tag = true;}
	void         untag(){m_tag = false;}
	
	
	CGameObject(OwnerType owner , u32 objtype,
				vector3df pos = vector3df(0.0f, 0.0f, 0.0f),
				vector3df rot = vector3df(0.0f, 0.0f, 0.0f),
				vector3df scale = vector3df(1.0f, 1.0f, 1.0f));


	CGameObject(OwnerType owner , u32 obj_id, u32 objtype,
		vector3df pos = vector3df(0.0f, 0.0f, 0.0f),
		vector3df rot = vector3df(0.0f, 0.0f, 0.0f),
		vector3df scale = vector3df(1.0f, 1.0f, 1.0f));


	virtual						~CGameObject();

	void						setOwnerType(OwnerType owner) { m_owner_type = owner; }
	OwnerType			getOwnerType() { return m_owner_type; }



	CGameAnimationMgr*			getAnimationMgr() { return m_animgr; }	
	void						setId(s32 cid) { m_uid = cid; }
	u32							getId() {return m_uid;}
	bool						isPossessed();
	CGameObjectManager*			getObjectManager() const { return m_object_manager; }
	s32							getObjectType() const { return m_obj_type; }
	void						setObjectType(const s32 i_type) { m_obj_type = i_type;  }
	bool						removeSceneNode();

	CMainGameGUI*				getMainGameGUI();
	CGameGUI*			getOwnedGUI();

	void						setCommandType(Command_Type type);
	Command_Type		getCommandType() const { return m_command_type; }

	void						setIdFromValidTest();
	bool						sendMessageToAllObjects( double delay, s32 sender, s32 msg, void* extra_info );
	vector3df					getHeightPos();
};






