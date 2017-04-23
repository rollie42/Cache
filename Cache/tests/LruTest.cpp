#include "LruTest.h"

#include <iostream>

using std::cout;
using std::endl;

using namespace cache;

void lru_test::test()
{
	cout << "lru_test" << endl;

	{
		lru_cache<string> cache(2);
		cache.add("k1", "Hello");
		cache.add("k2", "World");
		cache.add("k3", "!");

		verify(!cache.has("k1"), "k1 not present");
		verify(cache.has("k2"), "k2 present");
		verify(cache.has("k3"), "k3 present");
	}

	{
		lru_cache<string> cache(4);
		cache.add("k1", "Hello");
		cache.add("k2", "World");
		cache.add("k3", "!");
		cache.add("k4", " :)");

		cache.get("k2");
		cache.get("k3");

		cache.add("k5", "Good");
		cache.add("k6", "bye");

		verify(!cache.has("k1"), "k1 not present");
		verify(cache.has("k2"), "k2 present");
		verify(cache.has("k3"), "k3 present");
		verify(!cache.has("k4"), "k3 not present");
		verify(cache.has("k5"), "k3 present");
		verify(cache.has("k6"), "k3 present");
	}
}