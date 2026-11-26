//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/01/30
//
// File Name : God_Game.h
// 
// 게임 메인
// 
//////////////////////////////////////////////////////////////////////////


#include "common/UncopyableUtil.h"

class CGameObjectManager;
class CCameraManager;
class CEventHandler;
class CGridSceneNode;
class CGUIManager;
class CPathPlanner;
class CObjectResourceManager;
class PluginManager;
class CGameMap;

void WarningBox(const std::wstring str);
struct PACKET_ACCOUNT_LOGIN_CL_LN_REQ;



class God_Game : private UnCopyable
{
public :
	typedef enum 
	{
		on_intro,
		on_game,
		on_friend
	
	}GameState;

private :

	GameState							m_eGameState;


	std::unique_ptr<CGameObjectManager>					m_pObjectManager;
	std::unique_ptr<CCameraManager>						m_pCameraManager;
	std::unique_ptr<CEventHandler>						m_pEventHandler;
	std::unique_ptr<CGUIManager>						m_pGUIManager;
	std::unique_ptr<PluginManager>						m_pPlugInManager;
	std::unique_ptr<CGameMap>							m_pGameMap;
	
	bool								m_bRunning;

public :

	bool								Initialize();
	bool								GameLoading();
	bool								GameReset();

	void								setGameState(const GameState state) {m_eGameState = state; }


	const	bool						isRunning() {return m_bRunning;}
	void								setRunning(const bool r) { m_bRunning = r; }


	void								render();
	void								upadte(u32 timeMs);
	bool								control();




	CGameObjectManager*					getObjectManager()			{return m_pObjectManager.get(); }
	CCameraManager*						getCameraManager()			{return m_pCameraManager.get(); }
	CEventHandler*						getEventHandler()			{return m_pEventHandler.get();}
	CGUIManager*						getGUIManager()				{return m_pGUIManager.get();}

	CGameMap*							getGameMap()				{return m_pGameMap.get(); }
	PluginManager*						getPluginManager()			{return m_pPlugInManager.get(); }

	void								DrawScneneForInterface();	
	void								ClearGame(const GameState	state );
	void								playSound(const char *sundName, const bool loop /*= true*/);
	const GameState						getCurrentGameState() { return m_eGameState; }
	
	God_Game();
	~God_Game(); 
	
public :

	static God_Game* GetInstance();
};
