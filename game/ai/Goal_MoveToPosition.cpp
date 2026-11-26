//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/08/19
//
// File Name : Goal_MoveToPosition.cpp
// 
// 복합 목적 : 이동
//
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "Goal_MoveToPosition.h"
#include "../objects/CGameUnit.h"

#include "Telegram.h"
#include "God_Messages.h"
#include "Goal_SeekToPosition.h"
#include "Goal_FollowPath.h"
#include "../CAppcontext.h"



/*======================================================*/
// 이동하기 행동 초기화
/*======================================================*/
void Goal_MoveToPosition::activate()
{
  m_status = active;
  
  //make sure the subgoal list is clear.



	if(m_owner->getOwnerType() == object_mine)
	{	
	} 
}

/*======================================================*/
// 이동하기 행동 처리
/*======================================================*/
s32 Goal_MoveToPosition::process()
{
  activateIfInactive();
    
  m_status = processSubgoals();
 
  //if any of the subgoals have failed then this goal re-plans
  reactivateIfFailed();

  return m_status;
}






/*======================================================*/
// 메시지 처리하기
/*======================================================*/
bool Goal_MoveToPosition::handleMessage(const Telegram& msg)
{
  //first, pass the message down the goal hierarchy
  bool b_handled = forwardMessageToFrontMostSubgoal(msg);

  //if the msg was not handled, test to see if this goal can handle it
  if (b_handled == false)
  {
    switch(msg.msg)
    {
    case Msg_PathReady:

      //clear any existing goals
      removeAllSubgoals();

      addSubgoal(new Goal_FollowPath(m_owner));

      return true; //msg handled


    case Msg_NoPathAvailable:

      m_status = failed;

      return true; //msg handled

    default: return false;
    }
  }

  //handled by subgoals
  return true;
}

/*======================================================*/
// 길 렌더링
/*======================================================*/
void Goal_MoveToPosition::render()
{
//   //forward the request to the subgoals
//   Goal_Composite<Raven_Bot>::Render();
//   
//   //draw a bullseye
}

void Goal_MoveToPosition::terminate()
{

	
}
