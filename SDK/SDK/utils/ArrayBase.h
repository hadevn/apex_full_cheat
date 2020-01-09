#pragma once
#include <vector>
using namespace std;


template <class T>
struct TArrayMgr
{
	TArrayMgr()
	{
		m_List.clear();
	}

	void clear()
	{
		m_List.clear();
	}

	void Push(T p)
	{
		m_List.push_back(p);
	}

	size_t GetCount()
	{
		return m_List.size();
	}

	T *GetData(int i)
	{
		if (i >= 0 && i < m_List.size())
			return &m_List[i];
		return NULL;
	}
	std::vector<T> m_List;
};
