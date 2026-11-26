//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/03/01
//
// File Name : Goal_Composite.h
// 
// 기본 복합 목적 클래스
//
//////////////////////////////////////////////////////////////////////////

#ifndef GOAL_COMPOSITE_H
#define GOAL_COMPOSITE_H
#include "Goal.h"


template <class entity_type>
class Goal_Composite : public Goal<entity_type>
{
private:

    typedef std::list<Goal<entity_type>* > SubgoalList;

protected:

  SubgoalList   m_SubGoals;

  int  ProcessSubgoals();

  bool ForwardMessageToFrontMostSubgoal(const Telegram& msg);


public:

  Goal_Composite(entity_type* pE, int type):Goal<entity_type>(pE,type){}

  virtual ~Goal_Composite(){RemoveAllSubgoals();}

  virtual void Activate() = 0;

  virtual int  Process() = 0;

  virtual void Terminate() = 0;

  virtual bool HandleMessage(const Telegram& msg)
  { return ForwardMessageToFrontMostSubgoal(msg);}

  void         AddSubgoal(Goal<entity_type>* g);

  void         RemoveAllSubgoals();

};





/*======================================================*/
// 하위 목표들 지우기
/*======================================================*/
template <class entity_type>
void Goal_Composite<entity_type>::RemoveAllSubgoals()
{
  for (SubgoalList::iterator it = m_SubGoals.begin(); it != m_SubGoals.end();        ++it)
  {

		(*it)->Terminate();
    
		SAFE_DELETE(*it);
  }

  m_SubGoals.clear();
}
 

/*======================================================*/
// 하위 목표들 실행시키기
/*======================================================*/
template <class entity_type>
int Goal_Composite<entity_type>::ProcessSubgoals()
{ 
  //remove all completed and failed goals from the front of the subgoal list
  while (!m_SubGoals.empty() &&
         (m_SubGoals.front()->isComplete() || m_SubGoals.front()->hasFailed()))
  {    
    m_SubGoals.front()->Terminate();
    delete m_SubGoals.front(); 
    m_SubGoals.pop_front();
  }



  if (!m_SubGoals.empty())
  {


    int StatusOfSubGoals = m_SubGoals.front()->Process();
    if (StatusOfSubGoals == completed && m_SubGoals.size() > 1)
    {
      return active;
    }

    return StatusOfSubGoals;
  }
  
  else
  {
    return completed;
  }
}



/*======================================================*/
// 하위 목표 추가하기
/*======================================================*/
template <class entity_type>
void Goal_Composite<entity_type>::AddSubgoal(Goal<entity_type>* g)
{   
  //add the new goal to the front of the list
  m_SubGoals.push_front(g);
  
}



/*======================================================*/
// 메시지 하위 목표들로 포워딩
/*======================================================*/
template <class entity_type>
bool Goal_Composite<entity_type>::ForwardMessageToFrontMostSubgoal(const Telegram& msg)
{
  if (!m_SubGoals.empty())
  {
    return m_SubGoals.front()->HandleMessage(msg);
  }

   return false;
}





#endif

