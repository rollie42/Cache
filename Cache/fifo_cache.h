#pragma once

#include "_cache.h"

#include <queue>
#include <string>

using std::string;
using std::queue;

template <typename KeyT = string>
class fifo_replacement_policy
{
	queue<KeyT> m_removalQueue;

public:
	fifo_replacement_policy(size_t _maxSize)
	{}

	void add(const KeyT & _key)
	{
		m_removalQueue.push(_key);
	}

	void get(const KeyT & _key)
	{
		// no-op for this policy
	}

	KeyT remove()
	{
		KeyT removed_key = m_removalQueue.front();
		m_removalQueue.pop();
		return removed_key;
	}
};

template <typename ValueT, typename KeyT = string>
class fifo_cache : public cache<ValueT, fifo_replacement_policy<>>
{
public:
	fifo_cache(size_t _maxSize = 1000)
		: cache<ValueT, fifo_replacement_policy<ValueT>, KeyT>(_maxSize)
	{
	}
};