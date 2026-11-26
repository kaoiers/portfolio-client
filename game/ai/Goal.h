#ifndef GOAL_H
#define GOAL_H
//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/02/15
//
// File Name : Goal.h
// 
// 기본 목적 클래스
//
//////////////////////////////////////////////////////////////////////////
#include <stdexcept>
#include <string>


struct Telegram;

enum
{
	goal_think,
	goal_explore,
	goal_arrive_at_position,
	goal_seek_to_position,
	goal_follow_path,
	goal_traverse_edge,
	goal_move_to_position,
	goal_get_health,
	goal_get_shotgun,
	goal_get_rocket_launcher,
	goal_get_railgun,
	goal_wander,
	goal_negotiate_door,
	goal_attack_target,
	goal_attack_unit_target,
	goal_hunt_target,
	goal_unithunt_target,
	goal_strafe,
	goal_adjust_range,
	goal_say_phrase,
	
	
	goal_short_attack,
	goal_enemy_short_attack,
	goal_long_attack,
	goal_die,
	goal_buildingMotion,
	goal_building,
	goal_collecting,
	goal_goinghome,
	goal_attack_building,
	goal_short_attack_building
};



template <class entity_type>
class Goal
{
public:

   enum {active, inactive, completed, failed};
  
protected:


  int             m_iType;


  entity_type*    m_pOwner;


  int             m_iStatus;



  void ActivateIfInactive();


  void ReactivateIfFailed();

public:

  Goal(entity_type*  pE, int type):m_iType(type),
                                   m_pOwner(pE),
                                   m_iStatus(inactive)
  {}

  virtual ~Goal(){}


  virtual void Activate() = 0;


  virtual int  Process() = 0;


  virtual void Terminate() = 0;

  virtual bool HandleMessage(const Telegram& msg){return false;}


  virtual void AddSubgoal(Goal<entity_type>* g)
  {
	  throw std::runtime_error("Cannot add goals to atomic goals");
  }


  bool         isComplete()const{return m_iStatus == completed;} 
  bool         isActive()const{return m_iStatus == active;}
  bool         isInactive()const{return m_iStatus == inactive;}
  bool         hasFailed()const{return m_iStatus == failed;}
  int          GetType()const{return m_iType;}
  
};





template <class entity_type>
void  Goal<entity_type>::ReactivateIfFailed()
{
  if (hasFailed())
  {
     m_iStatus = inactive;
  }
}

  
template <class entity_type>
void  Goal<entity_type>::ActivateIfInactive()
{
  if (isInactive())
  {
    Activate();   
  }
}

#endif