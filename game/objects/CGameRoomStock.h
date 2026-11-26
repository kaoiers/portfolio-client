//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/09/28
//
// File Name : CGameRoomStock.h
// 
// 창고 클래스
// 
//////////////////////////////////////////////////////////////////////////


#ifndef CGAME_ROOM_STOCK_H
#define CGAME_ROOM_STOCK_H


#include "CGameRoom.h"

class CGameRoomStock : public CGameRoom
{

public :

	CGameRoomStock(OwnerType owner, u32 objtype,  u32 btype, const ROOM_RESOURCE* res,
		const vector3df& pos,
		const vector3df& rot  = vector3df(0.0f, 0.0f, 0.0f),
		const vector3df& scale  = vector3df(1.0f, 1.0f, 1.0f));


	virtual		void						enterControl();

	virtual		void						updateControl(CEventHandler* p_receiver) ;

	virtual		void						exitControl();

	virtual		void						update(const u32 time_ms);

	virtual		void						extraNodeSetting(){};


	CGameRoomStock(OwnerType owner,u32 objtype,  u32 btype, const ROOM_RESOURCE* res);

	virtual		bool						handleMessage(const Telegram& msg) {return true;}

	~CGameRoomStock(){};
};

#endif