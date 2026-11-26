//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/04/04
//
// File Name : CGameRoomGod.h
// 
// 신수방 클래스
// 
//////////////////////////////////////////////////////////////////////////



#ifndef CGAME_ROOM_GOD_H
#define CGAME_ROOM_GOD_H
#include "CGameRoom.h"

class CGameRoomGod : public CGameRoom
{

	void									initialize(const vector2di& TilePos);

public :

	CGameRoomGod(OwnerType owner, u32 objtype,  u32 btype, const ROOM_RESOURCE* res, const vector2di& TilePos,
		const vector3df& pos,
		const vector3df& rot  = vector3df(0.0f, 0.0f, 0.0f),
		const vector3df& scale  = vector3df(1.0f, 1.0f, 1.0f));


	void						enter_control();
	void						update_control(CEventHandler* pReceiver) ;
	void						exit_control();
	void						update(const u32 timeMs);
	void						extra_node_setting(){};


	CGameRoomGod(OwnerType owner, u32 objtype,  u32 btype, const ROOM_RESOURCE* res, const vector2di& TilePos);

	virtual		bool						HandleMessage(const Telegram& msg) {return true;}

	virtual ~CGameRoomGod(){};
};


#endif