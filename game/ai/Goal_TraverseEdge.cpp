//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/06/21
//
// File Name : Goal_TraverseEdge.cpp
// 
// 단일 목적 : Edge 이동
//
//////////////////////////////////////////////////////////////////////////

#include <stdafx.h>

#include "Goal_TraverseEdge.h"
#include "../objects/CGameUnit.h"


//#include "game/CObjectResourceManager.h"
// #include "..\constants.h"
// #include "../navigation/Raven_PathPlanner.h"
// #include "../lua/Raven_Scriptor.h"
// #include "debug/DebugConsole.h"




Goal_TraverseEdge::Goal_TraverseEdge(CGameUnit* pUnit,
                           
                                     bool       LastEdge):

                                Goal<CGameUnit>(pUnit, goal_traverse_edge),
                                
                                m_dTimeExpected(0.0),
                                m_bLastEdgeInPath(LastEdge)
                                
{




}


                                             

void Goal_TraverseEdge::Activate()
{
  m_iStatus = active;
  



  //Set the appropriate steering behavior. If this is the last edge in the path
  //the bot should arrive at the position it points to, else it should seek
 }




int Goal_TraverseEdge::Process()
{
  //if status is inactive, call Activate()
  ActivateIfInactive();
  
  //if the bot has become stuck return failure

//   if(m_pUpdateSendMovePacketRegulator->isReady() && m_pOwner->getOwnerType() == object_mine)
//   {	
// 	  NetworkPacketSpace::SendUnitMovetoPositionPacket(m_pOwner->GetID(), m_pOwner->Pos());
//   }



  if (isStuck())
  {
    m_iStatus = failed;
  }
  
  //if the bot has reached the end of the edge return completed
  else
  { 
  
  }

  return m_iStatus;
}

bool Goal_TraverseEdge::isStuck()const
{  
	double TimeTaken = 0;// Clock->GetCurrentTime() - m_dStartTime;

  if (TimeTaken > m_dTimeExpected)
  {
   // debug_con << "BOT " << m_pOwner->ID() << " IS STUCK!!" << "";

    return true;
  }

  return false;
}


void Goal_TraverseEdge::Terminate()
{
  //turn off steering behaviors.
  
  //m_pOwner->GetSteering()->SeekOff();

  //m_pOwner->GetSteering()->ArriveOff();

// m_pOwner->GetAnimationMgr()->SetDefaultAni();
  
  //return max speed back to normal3  
  
  //m_pOwner->SetMaxSpeed(m_pOwner->getUnitResource()->m_fMax_Speed);

  //m_pOwner->SetVelocity(vector3df(0,0,0));
}

