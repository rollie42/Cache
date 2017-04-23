#include "Test.h"

#include <iostream>

using std::cout;
using std::endl;

void test::verify(bool _success, string _text)
{
	if (_success)
	{
		cout << "\tSUCCESS: " << _text << endl;
	}
	else
	{
		cout << "\tFAILURE: " << _text << endl;
	}
}