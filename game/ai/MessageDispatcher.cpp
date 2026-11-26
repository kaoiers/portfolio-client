//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/02/15
//
// File Name : MessageDispatcher.h
// 
// 메시지 전달기
// 
//////////////////////////////////////////////////////////////////////////




#include <stdafx.h>
#include "MessageDispatcher.h"
#include "../objects/CGameObject.h"
#include "../CAppcontext.h"
#include "../objects/CGameObjectManager.h"

using std::set;

MessageDispatcher* MessageDispatcher::getInstance()
{
  static MessageDispatcher instance; 
  
  return &instance;
}


void MessageDispatcher::discharge(CGameObject* p_receiver, const Telegram& telegram)
{
 
}


void MessageDispatcher::dispatchMsg(double       delay,
                                    s32          sender,
                                    s32          receiver,
                                    s32          msg,
                                    void*        additional_info = NULL)
{


  CGameObject* p_receiver = EntityMgr->getObjectFromId(receiver);


  if (p_receiver == NULL)
  {
    return;
  }
  

  Telegram telegram(0, sender, receiver, msg, additional_info);
  
                    
  if (delay <= 0.0)                                                        
  {

    discharge(p_receiver, telegram);
  }

  else
  {
	  double current_time = 0;

    telegram.dispatch_time = current_time + delay * 1000;

    priority_q.insert(telegram);

	
  }
}


void MessageDispatcher::dispatchDelayedMessages()
{ 

	double current_time = 0;


  while( !priority_q.empty() &&
	     (priority_q.begin()->dispatch_time < current_time) && 
         (priority_q.begin()->dispatch_time > 0) )
  {

    const Telegram& telegram = *priority_q.begin();


    CGameObject* p_receiver = EntityMgr->getObjectFromId(telegram.receiver);


	if(p_receiver)
		discharge(p_receiver, telegram);

    priority_q.erase(priority_q.begin());
  }
}

void MessageDispatcher::dispatchMessageToAllObjects( double delay, s32 sender, s32 msg, void* extra_info )
{

	CGameObject* p_sender = EntityMgr->getObjectFromId(sender);


	if (p_sender == NULL)
	{
		return;
	}


	Telegram telegram(0, sender, 0, msg, extra_info);

	p_sender->getObjectManager()->dispatchMsg(telegram);



}
