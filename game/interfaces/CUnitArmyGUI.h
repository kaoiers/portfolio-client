//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/08/08
//
// File Name : CunitArmyGUI.h
// 
// 전사 인터페이스
// 
//////////////////////////////////////////////////////////////////////////



#ifndef CUNIT_ARMY_H
#define CUNIT_ARMY_H

#include "IGameGUI.h"

class CGameUnitArmy;


class CUnitArmyGUI : public CGameGUI
{

	CGameUnitArmy*	m_pOwner;	

	virtual bool	interface_control(CEventHandler* pReceiver);

public :

	CUnitArmyGUI(position2d<s32> rect = position2di(0,0)) :
	   CGameGUI(rect){}

	   virtual	~CUnitArmyGUI() {};

	   virtual void	GUI_Initialize();

	   virtual void	SetOwner(CGameObject *obj);


	 
};




#endif