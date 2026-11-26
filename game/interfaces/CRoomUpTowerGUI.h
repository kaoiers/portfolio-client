//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/04/30
//
// File Name : CRoomUpTowerGUI.h
// 
// 업그레이드 타워 인터페이스
// 
//////////////////////////////////////////////////////////////////////////

#ifndef CROOM_UP_TOWER_GUI_H
#define CROOM_UP_TOWER_GUI_H

#include "IGameGUI.h"

class CGameRoomTower;


class CRoomUpTowerGUI : public CGameGUI
{

	CGameRoomTower*	m_pOwner;	

	virtual bool	interface_control(CEventHandler* pReceiver);

public :

	CRoomUpTowerGUI(position2d<s32> rect = position2di(0,0)) :
	   CGameGUI(rect){}

	   virtual	~CRoomUpTowerGUI() {};

	   virtual void	GUI_Initialize();

	   virtual void	SetOwner(CGameObject *obj);


};

#endif