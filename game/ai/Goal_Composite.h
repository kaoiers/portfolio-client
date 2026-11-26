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
    SubgoalList m_sub_goals;

    s32 processSubgoals();

    bool forwardMessageToFrontMostSubgoal(const Telegram& msg);

public:
    Goal_Composite(entity_type* p_e, s32 type):Goal<entity_type>(p_e, type) {}

    virtual ~Goal_Composite() { removeAllSubgoals(); }

    virtual void activate() = 0;

    virtual s32 process() = 0;

    virtual void terminate() = 0;

    virtual bool handleMessage(const Telegram& msg)
    { return forwardMessageToFrontMostSubgoal(msg); }

    void addSubgoal(Goal<entity_type>* g);

    void removeAllSubgoals();
};

/*======================================================*/
// 하위 목표들 지우기
/*======================================================*/
template <class entity_type>
void Goal_Composite<entity_type>::removeAllSubgoals()
{
    for (typename SubgoalList::iterator it = m_sub_goals.begin(); it != m_sub_goals.end(); ++it)
    {
        (*it)->terminate();

        SAFE_DELETE(*it);
    }

    m_sub_goals.clear();
}

/*======================================================*/
// 하위 목표들 실행시키기
/*======================================================*/
template <class entity_type>
s32 Goal_Composite<entity_type>::processSubgoals()
{
    //remove all completed and failed goals from the front of the subgoal list
    while (!m_sub_goals.empty() &&
        (m_sub_goals.front()->isComplete() || m_sub_goals.front()->hasFailed()))
    {
        m_sub_goals.front()->terminate();
        delete m_sub_goals.front();
        m_sub_goals.pop_front();
    }

    if (!m_sub_goals.empty())
    {
        s32 status_of_sub_goals = m_sub_goals.front()->process();
        if (status_of_sub_goals == Goal<entity_type>::completed && m_sub_goals.size() > 1)
        {
            return Goal<entity_type>::active;
        }

        return status_of_sub_goals;
    }

    else
    {
        return Goal<entity_type>::completed;
    }
}

/*======================================================*/
// 하위 목표 추가하기
/*======================================================*/
template <class entity_type>
void Goal_Composite<entity_type>::addSubgoal(Goal<entity_type>* g)
{
    //add the new goal to the front of the list
    m_sub_goals.push_front(g);
}

/*======================================================*/
// 메시지 하위 목표들로 포워딩
/*======================================================*/
template <class entity_type>
bool Goal_Composite<entity_type>::forwardMessageToFrontMostSubgoal(const Telegram& msg)
{
    if (!m_sub_goals.empty())
    {
        return m_sub_goals.front()->handleMessage(msg);
    }

    return false;
}

#endif
