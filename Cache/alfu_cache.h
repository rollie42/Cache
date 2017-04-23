#pragma once

#include "_cache.h"

#include <list>
#include <string>
#include <queue>
#include <map>
#include <set>

using std::unordered_map;
using std::list;
using std::priority_queue;
using std::string;
using std::map;
using std::set;

const float c_weightMultiplier = 1.01f;
const float c_maxWeight = 1000.0f;

template <typename KeyT = string>
class alfu_replacement_policy
{
	unsigned char m_version = 0;
	float m_weight = 1.0;	

	struct element
	{		
		KeyT key;
		float weight;
		unsigned char version;

		bool operator<(const element & _rhs) const
		{
			return adjusted_weight(_rhs.version) < _rhs.adjusted_weight(version);
		}

		float adjusted_weight(unsigned char _compareVersion) const
		{
			if (_compareVersion - version > 2)
			{
				return 0.0;
			}
			else if (_compareVersion > version)
			{
				return weight / pow(c_maxWeight, _compareVersion - version);
			}
			else
			{
				return weight;
			}
		}
	};

	// TODO: this should be a priority_queue instead of a set, but we perform frequent updates to the elements, making the default STL priority_queue unviable
	map<int, set<element>> m_versionQueues;
	unordered_map<KeyT, element> m_queuePositions;

public:
	alfu_replacement_policy(size_t _maxSize)
	{
	}

	void add(const KeyT & _key)
	{
		element element;
		element.key = _key;
		element.weight = m_weight;
		element.version = m_version;

		add_element(_key, element);
	}

	void get(const KeyT & _key)
	{
		auto element = m_queuePositions[_key];
		m_versionQueues[element.version].erase(element);
		m_queuePositions.erase(_key);

		element.weight = element.adjusted_weight(m_version) + m_weight;
		element.version = m_version;
		
		add_element(_key, element);
	}

	KeyT remove()
	{
		// find lowest in all queues
		element lowest = *(m_versionQueues.begin()->second.begin());
		
		for (auto versionQueueItr : m_versionQueues)
		{
			auto versionQueue = versionQueueItr.second;
			if (versionQueue.begin()->weight < lowest.weight)
			{
				lowest = *(versionQueue.begin());
			}
		}

		// remove the lowest located element
		m_versionQueues[lowest.version].erase(lowest);
		m_queuePositions.erase(lowest.key);
		if (m_versionQueues[lowest.version].empty())
		{
			m_versionQueues.erase(lowest.version);
		}

		return lowest.key;
	}

private:
	void increment_version()
	{
		m_weight = 1.0;
		m_version++;
	}

	void add_element(const KeyT & _key, const element & _element)
	{
		auto newLocation = m_versionQueues[_element.version].insert(_element);
		m_queuePositions[_key] = _element;

		m_weight *= c_weightMultiplier;
		if (m_weight > c_maxWeight)
		{
			increment_version();
		}
	}
};

template <typename ValueT, typename KeyT = string>
class alfu_cache : public cache<ValueT, alfu_replacement_policy<>>
{
public:
	alfu_cache(size_t _maxSize = 1000)
		: cache<ValueT, alfu_replacement_policy<ValueT>, KeyT>(_maxSize)
	{
	}
};
