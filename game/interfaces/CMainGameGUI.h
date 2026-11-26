//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/06/30
//
// File Name : CMainGameGUI.h
// 
// 게임 메인 GUI 
// 
//////////////////////////////////////////////////////////////////////////


#include "IGameGUI.h"


class CBuildingObject;
class CGameObject;
class CEventHandler;
class CGameObjectManager;
class CGameTimerLimiter;

enum eMAINMENU_GUI_ID
{
	GUI_MAINMENU_OPTION_BUTTON	= 1501,
	GUI_MAINMENU_TIME_TEXT		= 1502,
	GUI_MAINMENU_TIMEINFO_TEXT  = 1503,
	GUI_MAINMENU_RESOURCE_GOLD	= 1504,
	GUI_MAINMENU_RESOURCE_LUMBER= 1505,
	GUI_MAINMENU_RESOURCE_STONE = 1506,
	GUI_MAINMENU_RESOURCE_UNIT = 1507,


	GUI_MAINMENU_LOAD_LOGIN_BUTTON = 1508,
	GUI_MAINMENU_WAVESTART_BUTTON  = 1509,
	GUI_MAINMENU_TIME_IMAGE = 1510,
	GUI_MAINMENU_LEVELBAR_BACK_IMAGE = 1511,
	GUI_MAINMENU_LEVELBAR_FRONT_IMAGE = 1512,
	//GUI_MAINMENU_LEVELBAR_DEMIGOD_IMAGE = 1511,
	GUI_MAINMENU_LEVEL_TEXT = 1514,
	GUI_MAINMENU_WARNING_TEXT = 1515,
	GUI_MAINMENU_WARNING_IMAGE = 1516,


	GUI_MAINMENU_BACKTOHOME_BUTTON = 1517,

	GUI_MAINMENU_RESOURCE_FARM_IMAGE = 1518,
	GUI_MAINMENU_RESOURCE_LUMBER_IMAGE = 1519,
	GUI_MAINMENU_RESOURCE_STONE_IMAGE = 1520,
	GUI_MAINMENU_RESOURCE_UNIT_IMAGE = 1521,

	GUI_MAINMENU_FACEBOOK_LOGIN = 1530
};



class CGameResourceManager;
class God_Game;
class WebBrowserView;

class CMainGameGUI : public CGameGUI
{
	CBuildingObject*		m_pBuilding;
	CGameObjectManager*		m_pObjMan;
	CGameTimerLimiter*		m_pTimeLimiter;
	CGameResourceManager*	m_pGameResourceManager;
	bool					m_bObjectSelectAvailable;

	CImageGUI*				m_pLevelBar;	
	CTextGUI*				m_pLevelText;

	CImageGUI*				m_pWaringImage;
	CTextGUI*				m_pWaringText;
	
	CButtonGUI*				m_pGoHomeButton;
	CButtonGUI*				m_pFaceBookBUtton;


	God_Game*				m_pGame;		

	f32						m_fAlphaRatio;

	
	static	CMainGameGUI*	m_pInstance;

	//PLAYER_ID				m_playerId;
	
private :

	virtual bool			interface_control(CEventHandler * pReceiver);
	void					AddMeshControl(CEventHandler * pReceiver);

public :
	
	CMainGameGUI(CGameObjectManager*		pObjMan);
	virtual	~CMainGameGUI();

	static	CMainGameGUI*	GetInstance() { return m_pInstance; }  

	void					StartTimer();
	void					EndTimerEvent();				



	void					showWaveButton();
	void					setObjectSelectAvailable(const bool bAvailable) { m_bObjectSelectAvailable = bAvailable; } 
	const	bool			getObjectSelectAvailable() const { return m_bObjectSelectAvailable;  }
	void					setLevelStatus(const f32 percent, const u32 level);

	void					AddPlayerExp(const u32 exp);

	void					FadeOutWarningMessage(const u32 timeMs);
	void					playSound2D(const char* soundname, const bool loop = false);
	void					playSound3D(const char* soundname , const vector3df& pos, const bool loop = false);
	void					playoffAllSounds();


	void					EnableDoorButton(const bool on);




	virtual void			GUI_Initialize();

	virtual	void			SetOwner(CGameObject *owner);


	//NETWORK
	void					SetMyPlayerID(/* PLAYER_ID playerId */);
};