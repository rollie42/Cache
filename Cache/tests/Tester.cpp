#include "Tester.h"

#include "FifoTest.h"
#include "LruTest.h"
#include "AlfuTest.h"

void tester::test()
{
	fifo_test().test();
	lru_test().test();
	alfu_test().test();
}