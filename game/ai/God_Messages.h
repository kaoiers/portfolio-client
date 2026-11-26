//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/02/20
//
// File Name : God_Message.h
// 
// 메시지 종류
// 
//////////////////////////////////////////////////////////////////////////


#ifndef RAVEN_MESSAGES_H
#define RAVEN_MESSAGES_H

//메시지 종류
enum message_type
{
	Msg_Blank,
	Msg_PathReady,
	Msg_NoPathAvailable,


	Msg_TakeThatMF, 
	Msg_YouGotMeYouSOB,
	Msg_GoalQueueEmpty,
	Msg_OpenSesame,
	Msg_GunshotSound,
	Msg_UserHasRemovedBot,

	
	Msg_UnitDead,
	Msg_YouDead,
	Msg_EnemyKillUnit,
	Msg_EnemyAttackRoom,
	Msg_DestroyRoom,
	MSG_I_DAMAGED_YOU
};



//메시지 정보
inline std::string messageToString(s32 msg)
{
	switch(msg)
	{
	case Msg_PathReady:

		return "Msg_PathReady";

	case Msg_NoPathAvailable:

		return "Msg_NoPathAvailable";

	case Msg_TakeThatMF:

		return "Msg_TakeThatMF";

	case Msg_YouGotMeYouSOB:

		return "Msg_YouGotMeYouSOB";

	case Msg_GoalQueueEmpty:

		return "Msg_GoalQueueEmpty";

	case Msg_OpenSesame:

		return "Msg_OpenSesame";

	case Msg_GunshotSound:

		return "Msg_GunshotSound";

	case Msg_UserHasRemovedBot:

		return "Msg_UserHasRemovedBot";

	default:

		return "Undefined message!";
	}
}


#endif