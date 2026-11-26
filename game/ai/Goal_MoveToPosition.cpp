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
//#include "../Raven_Game.h"

#include "../ai/Telegram.h"
#include "../ai/God_Messages.h"
#include "Goal_SeekToPosition.h"
#include "Goal_FollowPath.h"
#include "../CAppContext.h"



/*======================================================*/
// 이동하기 행동 초기화
/*======================================================*/
void Goal_MoveToPosition::Activate()
{
  m_iStatus = active;
  
  //make sure the subgoal list is clear.
  //RemoveAllSubgoals();



	if(m_pOwner->getOwnerType() == object_mine)
	{	
		//NetworkPacketSpace::SendUnitMovetoPositionPacket(m_pOwner->GetID(), m_vDestination);
	} 
}

/*======================================================*/
// 이동하기 행동 처리
/*======================================================*/
int Goal_MoveToPosition::Process()
{
  //if status is inactive, call Activate()
  ActivateIfInactive();
    
  //process the subgoals
  m_iStatus = ProcessSubgoals();
 
  //if any of the subgoals have failed then this goal re-plans
  ReactivateIfFailed();

  return m_iStatus;
}






/*======================================================*/
// 메시지 처리하기
/*======================================================*/
bool Goal_MoveToPosition::HandleMessage(const Telegram& msg)
{
  //first, pass the message down the goal hierarchy
  bool bHandled = ForwardMessageToFrontMostSubgoal(msg);

  //if the msg was not handled, test to see if this goal can handle it
  if (bHandled == false)
  {
    switch(msg.Msg)
    {
    case Msg_PathReady:

      //clear any existing goals
      RemoveAllSubgoals();

      AddSubgoal(new Goal_FollowPath(m_pOwner));

      return true; //msg handled


    case Msg_NoPathAvailable:

      m_iStatus = failed;

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
void Goal_MoveToPosition::Render()
{
//   //forward the request to the subgoals
//   Goal_Composite<Raven_Bot>::Render();
//   
//   //draw a bullseye
//   gdi->BlackPen();
//   gdi->BlueBrush();
//   gdi->Circle(m_vDestination, 6);
//   gdi->RedBrush();
//   gdi->RedPen();
//   gdi->Circle(m_vDestination, 4);
//   gdi->YellowBrush();
//   gdi->YellowPen();
//   gdi->Circle(m_vDestination, 2);
}

void Goal_MoveToPosition::Terminate()
{

	
}
