#include "AlfuTest.h"

#include <iostream>

using std::cout;
using std::endl;

void alfu_test::test()
{
	cout << "lru_test" << endl;

	{
		alfu_cache<string> cache(2);
		cache.add("k1", "Hello");
		cache.get("k1");
		cache.add("k2", "World");		
		cache.add("k3", "!");

		verify(cache.has("k1"), "k1 present");
		verify(!cache.has("k2"), "k2 not present");
		verify(cache.has("k3"), "k3 present");
	}
}