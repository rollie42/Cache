#pragma once

#include "_cache.h"

#include <list>
#include <string>

using std::unordered_map;
using std::list;
using std::string;

template <typename KeyT = string>
class lru_replacement_policy
{
	unordered_map<KeyT, typename list<KeyT>::iterator> m_queuePositions;
	list<KeyT> m_removalQueue;

public:
	lru_replacement_policy(size_t _maxSize) : m_queuePositions(_maxSize)
	{
	}

	void add(const KeyT & _key)
	{
		m_removalQueue.push_back(_key);		
		m_queuePositions[_key] = --m_removalQueue.end();
	}

	void get(const KeyT & _key)
	{
		auto & itr = m_queuePositions[_key];
		m_removalQueue.erase(itr);
		m_queuePositions.erase(_key);
		add(_key);
	}

	KeyT remove()
	{
		KeyT removed_key = m_removalQueue.front();
		m_removalQueue.pop_front();
		m_queuePositions.erase(removed_key);
		return removed_key;
	}
};

template <typename ValueT, typename KeyT = string>
class lru_cache : public cache<ValueT, lru_replacement_policy<>>
{
public:
	lru_cache(size_t _maxSize = 1000)
		: cache<ValueT, lru_replacement_policy<ValueT>, KeyT>(_maxSize)
	{
	}
};
