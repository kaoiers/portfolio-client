//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/08/01
//
// File Name : CObjectListSet.h
//
// 오브젝트 집합 클래스
//
//////////////////////////////////////////////////////////////////////////

#ifndef ENTITY_GROUP
#define ENTITY_GROUP

#include <list>

template <typename entity_type>
class CObjectListSet
{
    typedef std::list<entity_type > entity_list;

    entity_list m_entity_list;

    inline bool find(entity_type entity)
    {
        typename std::list<entity_type >::iterator itr = m_entity_list.begin();

        for (; itr != m_entity_list.end(); ++itr)
        {
            if ((*itr) == entity)
            {
                return true;
            }
        }

        return false;
    }

public:
    inline void add(entity_type entity)
    {
        if (!find(entity))
        {
            m_entity_list.push_back(entity);
        }
    }

    inline void remove(entity_type entity)
    {
        typename std::list<entity_type >::iterator itr = m_entity_list.begin();

        for (; itr != m_entity_list.end(); ++itr)
        {
            if ((*itr) == entity)
            {
                m_entity_list.erase(itr);
                return;
            }
        }
    }

    inline void clear()
    {
        m_entity_list.clear();
    }

    inline const std::list<entity_type >& getAll()
    {
        return m_entity_list;
    }

    inline std::list<entity_type >& getNormalAll()
    {
        return m_entity_list;
    }

    ~CObjectListSet()
    {
        if (!m_entity_list.empty())
        {
            m_entity_list.clear();
        }
    }
};

#endif
