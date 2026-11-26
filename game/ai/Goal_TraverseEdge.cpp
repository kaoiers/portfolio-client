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
// #include "debug/DebugConsole.h"




Goal_TraverseEdge::Goal_TraverseEdge(CGameUnit* p_unit,
                           
                                     bool       last_edge):

                                Goal<CGameUnit>(p_unit, goal_traverse_edge),
                                
                                m_time_expected(0.0),
                                m_last_edge_in_path(last_edge)
                                
{




}


                                             

void Goal_TraverseEdge::activate()
{
  m_status = active;
  



  //Set the appropriate steering behavior. If this is the last edge in the path
  //the bot should arrive at the position it points to, else it should seek
 }




s32 Goal_TraverseEdge::process()
{
  //if status is inactive, call Activate()
  activateIfInactive();
  
  //if the bot has become stuck return failure

//   if(m_pUpdateSendMovePacketRegulator->isReady() && m_pOwner->getOwnerType() == object_mine)
//   {	
// 	  NetworkPacketSpace::SendUnitMovetoPositionPacket(m_pOwner->GetID(), m_pOwner->Pos());
//   }



  if (isStuck())
  {
    m_status = failed;
  }
  
  //if the bot has reached the end of the edge return completed
  else
  { 
  
  }

  return m_status;
}

bool Goal_TraverseEdge::isStuck()const
{  
	double time_taken = 0;// Clock->GetCurrentTime() - m_dStartTime;

  if (time_taken > m_time_expected)
  {
   // debug_con << "BOT " << m_pOwner->ID() << " IS STUCK!!" << "";

    return true;
  }

  return false;
}


void Goal_TraverseEdge::terminate()
{
  //turn off steering behaviors.
  
  //m_pOwner->GetSteering()->SeekOff();

  //m_pOwner->GetSteering()->ArriveOff();

// m_pOwner->GetAnimationMgr()->SetDefaultAni();
  
  //return max speed back to normal3  
  
  //m_pOwner->SetMaxSpeed(m_pOwner->getUnitResource()->m_fMax_Speed);

  //m_pOwner->SetVelocity(vector3df(0,0,0));
}

