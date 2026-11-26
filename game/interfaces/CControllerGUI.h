//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/02/11
//
// File Name : CControllerGUI.h
// 
// 컨트롤 GUI 인터페이스 관리
// 
//////////////////////////////////////////////////////////////////////////


#ifndef CUNIT_CONTROLLER_GUI_H
#define CUNIT_CONTROLLER_GUI_H

class CGameGUI;
class cLua;
class CUnitGodGUI;
class CUnitWorkerGUI;
class CUnitArmyGUI;


class CGameUnitGod;
class CGameUnitWorker;
class CRoomJailGUI;
class CRoomWaitingGUI;

class CRoomFarmGUI;
class CRoomMineGUI;
class CRoomWoodGUI;
class CRoomCommunityGUI;
class CRoomStockGUI;
class CRoomTowerGUI;
class CRoomUpTowerGUI;



class CGameUnitArmy;
class CGameUnitGod;
class CGameUnitWorker;

class CGameObject;





class CControllerGUI
{
	CGameGUI*		m_pCurrentGUI;
	CUnitGodGUI*			m_pUnitGodGUI;
	CUnitWorkerGUI*			m_pUnitWorkerGUI;	
	CUnitArmyGUI*			m_pUnitArmyGUI;


	CRoomJailGUI*			m_pRoomJailGUI;
	CRoomWaitingGUI*		m_pRoomWaitingGUI;
	CRoomFarmGUI*			m_pRoomFarmGUI;
	CRoomMineGUI*			m_pRoomMineGUI;

	CRoomWoodGUI*			m_pRoomWoodGUI;

	CRoomCommunityGUI*		m_pRoomCommunityGUI;
	CRoomStockGUI*			m_pRoomStockGUI;
	CRoomTowerGUI*			m_pRoomTowerGUI;
	CRoomUpTowerGUI*		m_pRoomUpTowerGUI;



	void					SetGUIController(CGameGUI* pGUI);

	static	CControllerGUI*	pInstance;

	void					InitRoomGUI(cLua *pLua);
	
	void					InitUnitGUI(cLua *pLua);

	

public :

		
	CControllerGUI();

	~CControllerGUI();

	static	CControllerGUI*	Instance();

	void					init(cLua *pLua);

	void					setGodGUI(CGameUnitGod* pGod);

	void					setWorkerGUI(CGameUnitWorker* pWorker);

	void					setArmyGUI(CGameUnitArmy*	pArmy);

	CGameGUI*		setCurrentControlGUI(CGameObject * obj);

	CGameGUI*		getCurrentControlGUI() {return m_pCurrentGUI;}

	CRoomCommunityGUI*		getCommunityGUI() { return m_pRoomCommunityGUI; }

	void					DisableGUI();


	





};



#endif