//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/06/21
//
// File Name : Goal_TraverseEdge.h
// 
// 단일 목적 : Edge 이동
//
//////////////////////////////////////////////////////////////////////////


#ifndef GOAL_TRAVERSE_EDGE_H
#define GOAL_TRAVERSE_EDGE_H
#pragma warning (disable:4786)

#include "Goal.h"


//#include "../navigation/Raven_PathPlanner.h"


class CGameUnit;
class Regulator;


class Goal_TraverseEdge : public Goal<CGameUnit>
{
private:

  //true if m_Edge is the last in the path.
  bool      m_bLastEdgeInPath;

  //the estimated time the bot should take to traverse the edge
  double     m_dTimeExpected;
  
  //this records the time this goal was activated
  double     m_dStartTime;

 	Regulator*				m_pUpdateSendMovePacketRegulator;

  //returns true if the bot gets stuck
  bool      isStuck()const;

public:

  Goal_TraverseEdge(CGameUnit* pUnit,
                    bool       LastEdge); 

  //the usual suspects
  void Activate();
  int  Process();
  void Terminate();

};




#endif

