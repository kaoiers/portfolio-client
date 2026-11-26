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
#include "../CAppContext.h"
//#include "FrameCounter.h"
#include "../objects/CGameObjectManager.h"

using std::set;

MessageDispatcher* MessageDispatcher::Instance()
{
  static MessageDispatcher instance; 
  
  return &instance;
}


void MessageDispatcher::Discharge(CGameObject* pReceiver, const Telegram& telegram)
{
 
}


void MessageDispatcher::DispatchMsg(double       delay,
                                    int          sender,
                                    int          receiver,
                                    int          msg,
                                    void*        AdditionalInfo = NULL)
{


  CGameObject* pReceiver = EntityMgr->GetObjectFromID(receiver);


  if (pReceiver == NULL)
  {
    return;
  }
  

  Telegram telegram(0, sender, receiver, msg, AdditionalInfo);
  
                    
  if (delay <= 0.0)                                                        
  {

    Discharge(pReceiver, telegram);
  }

  else
  {
	  double CurrentTime = 0;

    telegram.DispatchTime = CurrentTime + delay * 1000;

    PriorityQ.insert(telegram);

	
  }
}


void MessageDispatcher::DispatchDelayedMessages()
{ 

	double CurrentTime = 0;


  while( !PriorityQ.empty() &&
	     (PriorityQ.begin()->DispatchTime < CurrentTime) && 
         (PriorityQ.begin()->DispatchTime > 0) )
  {

    const Telegram& telegram = *PriorityQ.begin();


    CGameObject* pReceiver = EntityMgr->GetObjectFromID(telegram.Receiver);


	if(pReceiver)
		Discharge(pReceiver, telegram);

    PriorityQ.erase(PriorityQ.begin());
  }
}

void MessageDispatcher::DispatchMessageToAllObjects( double delay, int sender, int msg, void* ExtraInfo )
{

	CGameObject* pSender = EntityMgr->GetObjectFromID(sender);


	if (pSender == NULL)
	{
		return;
	}


	Telegram telegram(0, sender, 0, msg, ExtraInfo);

	pSender->getObjectManager()->DispatchMsg(telegram);



}
