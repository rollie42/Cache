#include "FifoTest.h"

#include <iostream>

using std::cout;
using std::endl;

using namespace cache;

void fifo_test::test()
{
	cout << "lru_test" << endl;

	{
		fifo_cache<string> cache(2);
		cache.add("k1", "Hello");
		cache.add("k2", "World");
		cache.add("k3", "!");

		verify(!cache.has("k1"), "k1 not present");
		verify(cache.has("k2"), "k2 present");
		verify(cache.has("k3"), "k3 present");
	}
}