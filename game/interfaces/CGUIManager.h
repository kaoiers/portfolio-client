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
	CFontManager*		m_font_manager;
	CMainGameGUI*		m_main_game_gui;
	COptionGUI*			m_option_gui;
	CMouseCursorGUI*	m_mouse_cursor_gui;
	CLoginGUI*			m_login_gui;
	CDialogBox*			m_dialog_box_gui;
	CControllerGUI*		m_controller_gui;
	CGameIntroGUI*		m_game_intro_gui;
	CPopUpGUI*			m_pop_up_gui;
	CWebDialog*			m_web_dialog;

	typedef std::map<u32 , CGameGUI *> GUIMap;
	GUIMap	m_guis;

	

public :



	CGUIManager();

	static	   CGUIManager*		m_instance;
	static	   CGUIManager*		getInstance()   {return m_instance; }

	virtual				~CGUIManager();

	CGameGUI*			findInterfaceFromId( s32 cid );

	void				registerGuiById(CGameGUI *p_gui);

	bool				isPressed();

	bool				postEvent(const SEvent& event);

	void				interfaceInit(CGameGUI* BaseGUI);

public :

	bool				gameLoading();

	bool				gameLoadingComplete() { return true;  };

	bool				control(CEventHandler* p_receiver);

	bool				render();

	COptionGUI*			getOptionGUI() const { return m_option_gui; }
	CMainGameGUI*		getMainGameGUI() const {return m_main_game_gui; }
	CMouseCursorGUI*	getMouseCursorGUI() const { return m_mouse_cursor_gui; }
	CLoginGUI*			getLoginGUI() const { return m_login_gui; }
	CDialogBox*			getDialogGui() const { return m_dialog_box_gui; }
	CControllerGUI*		getUnitController() const {return m_controller_gui; }
	CGameIntroGUI*		getGameIntroGUI() const {return m_game_intro_gui; }
	CControllerGUI*		getControllerGUI() const { return  m_controller_gui;}
	CPopUpGUI*			getPopUpGUI() const { return m_pop_up_gui; }
	CWebDialog*			getWebDialog() const { return m_web_dialog; }

public :
	u32 getLastGUIID();

private :

};