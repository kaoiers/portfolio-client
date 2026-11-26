//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/02/15
//
// File Name : MessageDispatcher.h
// 
// 메시지 전달기
// 
//////////////////////////////////////////////////////////////////////////


#ifndef MESSAGE_DISPATCHER_H
#define MESSAGE_DISPATCHER_H
#pragma warning (disable:4786)



#include <set>


#include "Telegram.h"



class CGameObject;


//to make life easier...
#define Dispatcher MessageDispatcher::getInstance()

//to make code easier to read
const double SEND_MSG_IMMEDIATELY = 0.0;
const s32    NO_ADDITIONAL_INFO   = 0;
const s32    SENDER_ID_IRRELEVANT = -1;


class MessageDispatcher
{
private:  
  
  //a std::set is used as the container for the delayed messages
  //because of the benefit of automatic sorting and avoidance
  //of duplicates. Messages are sorted by their dispatch time.
  std::set<Telegram> priority_q;

  //this method is utilized by DispatchMsg or DispatchDelayedMessages.
  //This method calls the message handling member function of the receiving
  //entity, pReceiver, with the newly created telegram
  void discharge(CGameObject* p_receiver, const Telegram& msg);

  MessageDispatcher(){}

  //copy ctor and assignment should be private
  MessageDispatcher(const MessageDispatcher&);
  MessageDispatcher& operator=(const MessageDispatcher&);

public:

  static MessageDispatcher* getInstance();

  //send a message to another agent. Receiving agent is referenced by ID.
  void dispatchMsg(double      delay,
                   s32         sender,
                   s32         receiver,
                   s32         msg,
                   void*       extra_info);

  //send out any delayed messages. This method is called each time through   
  //the main game loop.
  void dispatchDelayedMessages();

  void dispatchMessageToAllObjects(double      delay,
	  s32         sender,
	  s32         msg,
	  void*       extra_info);


};



#endif