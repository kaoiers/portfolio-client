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

	CGameRoomTower*	m_owner;	

	virtual bool	interfaceControl(CEventHandler* p_receiver);

public :

	CRoomUpTowerGUI(position2d<s16> rect = position2di(0,0)) :
	   CGameGUI(rect){}

	   virtual	~CRoomUpTowerGUI() {};

	   virtual void	guiInitialize();

	   virtual void	setOwner(CGameObject *obj);


};

#endif