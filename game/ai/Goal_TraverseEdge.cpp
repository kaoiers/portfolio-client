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
  activateIfInactive();
  
  //if the bot has become stuck return failure




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
  


  
  //return max speed back to normal3  
  

}

