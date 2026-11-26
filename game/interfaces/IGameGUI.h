//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/05/05
//
// File Name : CGameGUI.h
// 
// GUI 인터페이스
// 
//////////////////////////////////////////////////////////////////////////

#ifndef GAME_GUI
#define	GAME_GUI

#include "IBaseGameGUI.h"
#include "EnumGUITypes.h"
#include "../objects/CObjectListSet.h"


class IGUIObject;
class CButtonGUI;
class CImageGUI;
class CTextGUI;
class CGameObject;
class CEditBoxGUI;
class CEventHandler;
class CGUIManager;


class CGameGUI : public IBaseGameGUI
{

	unsigned	int		m_gid;

	bool				m_bNeedOwner;

	bool				m_bEnable;

	bool				m_useOneSelectButton;

	bool				m_bOneButtonSelect;

	IGUIObject*			m_pFocusedObject;

	static  unsigned int				m_iNextValidID;


	bool					element_control(CEventHandler* m_pReceiver);
protected :

typedef std::list<IGUIObject *> GuiElementsList	;

typedef std::map<std::string , CObjectListSet<IGUIObject *> > GroupGUI ;

	GroupGUI							m_Group;
	position2d<s32>						m_abolutePosition;
	GuiElementsList						m_pElements;
	CGameObject*						m_pOwner;


public :


	CGameGUI() {};
	CGameGUI(position2d<s32> pos = position2d<s32>(0,0) );

	virtual ~CGameGUI();

	void					SetOneButtonInterface(const bool sel = true) { m_useOneSelectButton  = sel;  } 

	bool					isOneButtonInterface() const {return m_useOneSelectButton; }


	void					SetOneButtonSelectState( IGUIObject *guiobj );

	void					SetAllButtonSelectState(const bool states = true);

	bool					isOneButtonSelectState();

	bool					isMouseOnButton();

	bool					hasFocus(IGUIObject* obj);


public :

	
	bool					control(CEventHandler* m_pReceiver);	


	void					Show();

	void					Hide();

	bool					isEnable() const { return m_bEnable; }

	bool					isClicked() { return true; };

public :


	void					SetPosition(const vector2di pos);
		
	void					RegisterElement( IGUIObject *pGui );

	IGUIObject*				FindElementByID(s32 eid);

	position2d<s32>			GetPosition() const  { return  m_abolutePosition; }
	
	unsigned int			GetID() const { return m_gid; }


	void					SetNeedOwner(const bool need = true) {m_bNeedOwner = need;}

	bool					isNeedOwner() const { return m_bNeedOwner; }

	bool					PostEvent(SEvent event) { return true; };

public :

	CButtonGUI*				addButton(const position2d<s32> Position, const char* defaultImage, s32 mID = -1 ,std::wstring text = L"");
	
	CImageGUI*				addImage(const position2d<s32> Position, const char* defaultImage , s32 mID = -1);
	
	position2d<s32> GetRelativePosition( const position2d<s32> pos ) const;
	
	position2d<s32> GetAbsolutePosition(const position2d<s32> pos) const;

	bool							FindGroupByName(const char * name, std::list<IGUIObject *>* pGroupList);
	
	CObjectListSet<IGUIObject *>* 	FindGroupByName( const char * name);

	void							addGroup(const char * name, IGUIObject* obj);

	void							showGroup(const char *name, const bool bshow = true) {};

	CGUIManager*					getGUIManager();
};




#endif
