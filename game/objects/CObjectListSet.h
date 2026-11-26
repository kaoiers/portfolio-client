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

template <typename entity_type> 
class CObjectListSet
{
	typedef std::list<entity_type > EntityList;	

	

	EntityList m_EntityList;	

	inline bool find(entity_type entity)
	{
		std::list<entity_type >::iterator itr = m_EntityList.begin();

		for(itr; itr != m_EntityList.end(); itr++)
		{
			if((*itr) == entity)
			{
				return true;				
			}
		}			

		return false;
	}

public :


	inline void add(entity_type entity)
	{
		if(!find(entity))
		{
			m_EntityList.push_back(entity);
		}
	}

	inline void remove(entity_type entity)
	{
		std::list<entity_type >::iterator itr = m_EntityList.begin();

		for(itr; itr != m_EntityList.end(); itr++)
		{
			if((*itr) == entity)
			{
				m_EntityList.erase(itr);
				return;
			}
		}	
	}

	inline void clear()
	{
		m_EntityList.clear();
	}


	inline const  std::list<entity_type >& getAll()
	{
		return m_EntityList;
	}

	inline std::list<entity_type >& getNormalAll()
	{
		return m_EntityList;
	}

	~CObjectListSet() 
	{
		if(!m_EntityList.empty())
		{
			m_EntityList.clear();
		}
	}		
};

#endif