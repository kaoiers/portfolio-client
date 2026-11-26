//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/08/04
//
// File Name : CUnitGodGUI.h
// 
// 신수 인터페이스
// 
//////////////////////////////////////////////////////////////////////////

#ifndef CUNIT_GOD_H
#define CUNIT_GOD_H

#include "IGameGUI.h"

class CGameUnitGod;


class CUnitGodGUI : public CGameGUI
{

	CGameUnitGod*	m_owner;	

	virtual bool	interfaceControl(CEventHandler* p_receiver);

public :

	CUnitGodGUI(position2d<s16> rect = position2di(0,0)) :
	   CGameGUI(rect){}

	virtual	~CUnitGodGUI() {};

	virtual void	guiInitialize(){}

	virtual void	setOwner(CGameObject *obj);
};




#endif