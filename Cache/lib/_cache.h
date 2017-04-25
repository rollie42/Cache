#pragma once

#include <string>
#include <unordered_map>

namespace cache
{
	using std::string;
	using std::unordered_map;

	// template class for all cache types; allows specification of a replacement policy
	template <typename ValueT, typename ReplPolicyT, typename KeyT = string>
	class cache
	{
		ReplPolicyT m_replacementPolicy;

		unordered_map<KeyT, ValueT> m_data;
		size_t m_maxSize;

	public:
		cache(size_t _maxSize = 1000)
			: m_data(_maxSize),
			m_maxSize(_maxSize),
			m_replacementPolicy(_maxSize)
		{
		}

		void add(const KeyT & _key, const ValueT & _val)
		{
			if (has(_key))
			{
				m_data[_key] = _val;
				m_replacementPolicy.get(_key); // treat modification of the value for a given key like a 'get' operation
				return;
			}

			if (m_data.size() >= m_maxSize)
			{
				m_data.erase(m_replacementPolicy.remove());
			}

			m_replacementPolicy.add(_key);
			m_data[_key] = _val;
		}

		ValueT & get(const KeyT & _key)
		{
			m_replacementPolicy.get(_key);
			return m_data[_key];
		}

		bool has(const KeyT & _key) const
		{
			return m_data.find(_key) != m_data.end();
		}

		ValueT & operator[](const KeyT & _key)
		{
			return get(_key);
		}

		auto begin()
		{
			return m_data.begin();
		}

		auto end()
		{
			return m_data.end();
		}
	};
}