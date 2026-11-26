//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/09/30
//
// File Name : CGameRoomJail.h
// 
// 감옥 클래스
// 
//////////////////////////////////////////////////////////////////////////


#ifndef CGAME_ROOM_JAIL_H
#define CGAME_ROOM_JAIL_H
#include "CGameRoom.h"

class CGameRoomJail : public CGameRoom
{

public :

	CGameRoomJail(const OwnerType& owner,unsigned int objtype,  unsigned int btype, const ROOM_RESOURCE* res, 
		const vector3df& pos,
		const vector3df& rot  = vector3df(0.0f, 0.0f, 0.0f),
		const vector3df& scale  = vector3df(1.0f, 1.0f, 1.0f));


	void						enter_control();
	void						update_control(CEventHandler* pReceiver) ;
	void						exit_control();
	void						update(const u32 timeMs);
	void						extra_node_setting(){};
	bool						HandleMessage(const Telegram& msg) {return true;}


	CGameRoomJail(const OwnerType& owner, unsigned int objtype, unsigned int btype, const ROOM_RESOURCE* res);

	virtual ~CGameRoomJail(){};
};










#endif