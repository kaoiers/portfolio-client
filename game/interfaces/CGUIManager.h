//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/05/07
//
// File Name : CGUIManager.h
// 
// GUI 매니져
// 
//////////////////////////////////////////////////////////////////////////

#include "IGameGUI.h"
#include "../common/CFontManager.h"
#include <map>

class CFontManager;
class CMainGameGUI;
class COptionGUI;
class CMouseCursorGUI;
class CLoginGUI;
class CEventHandler;
class CDialogBox;
class CGameIntroGUI;
class CPopUpGUI;
class CControllerGUI;
class CWebDialog;


class CGUIManager
{
	CFontManager*		m_pFontManager;
	CMainGameGUI*		m_pMainGameGUI;
	COptionGUI*			m_pOptionGUI;
	CMouseCursorGUI*	m_pMouseCursorGUI;
	CLoginGUI*			m_pLoginGUI;
	CDialogBox*			m_pDialogBoxGUI;
	CControllerGUI*		m_pControllerGUI;
	CGameIntroGUI*		m_pGameIntroGUI;
	CPopUpGUI*			m_pPopUpGUI;
	CWebDialog*			m_pWebDialog;

	typedef std::map<u32 , CGameGUI *> GUIMap;
	GUIMap	m_pGUIs;

	

public :



	CGUIManager();

	static	   CGUIManager*		m_pInstance;
	static	   CGUIManager*		GetInstance()   {return m_pInstance; }

	virtual				~CGUIManager();

	CGameGUI*			FindInterfaceFromID( s32 cid );

	void				RegisterGUIByID(CGameGUI *pGui);

	bool				IsPressed();

	bool				PostEvent(const SEvent& event);

	void				Interface_Init(CGameGUI* BaseGUI);

public :

	bool				GameLoading();

	bool				GameLoadingComplete() { return true;  };

	bool				control(CEventHandler* pReceiver);

	bool				render();

	COptionGUI*			getOptionGUI() const { return m_pOptionGUI; }
	CMainGameGUI*		getMainGameGUI() const {return m_pMainGameGUI; }
	CMouseCursorGUI*	getMouseCursorGUI() const { return m_pMouseCursorGUI; }
	CLoginGUI*			getLoginGUI() const { return m_pLoginGUI; }
	CDialogBox*			getDIalogGUI() const { return m_pDialogBoxGUI; }
	CControllerGUI*		getUnitController() const {return m_pControllerGUI; }
	CGameIntroGUI*		getGameIntroGUI() const {return m_pGameIntroGUI; }
	CControllerGUI*		getControllerGUI() const { return  m_pControllerGUI;}
	CPopUpGUI*			getPopUpGUI() const { return m_pPopUpGUI; }
	CWebDialog*			getWebDialog() const { return m_pWebDialog; }

public :
	u32 getLastGUIID();

private :

};