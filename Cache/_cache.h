#pragma once

#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

template <typename ValueT, typename ReplP, typename KeyT = string>
class cache
{
	ReplP m_replacementPolicy;

	unordered_map<KeyT, ValueT> m_data;
	size_t m_maxSize;

public:
	cache(size_t _maxSize = 1000) 
		: m_data(_maxSize + 1), 
		m_maxSize(_maxSize),
		m_replacementPolicy(_maxSize)
	{
	}

	void add(const KeyT & _key, const ValueT & _val)
	{
		m_replacementPolicy.add(_key);
		m_data[_key] = _val;
		if (m_data.size() > m_maxSize)
		{
			m_data.erase(m_replacementPolicy.remove());
		}
	}

	// TODO: T? T&?
	const ValueT & get(const KeyT & _key)
	{
		m_replacementPolicy.get(_key);
		return m_data.at(_key);
	}

	bool has(const KeyT & _key) const
	{
		return m_data.find(_key) != m_data.end();
	}

	const ValueT & operator[](const KeyT & _key)
	{
		return this->get(_key);
	}
};
