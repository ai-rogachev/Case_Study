#include <iostream>
#include <stdlib.h>

extern "C" void PushAndPopTest();
extern "C" void BasicCallTest();
extern "C" void CallTestFunction();

int main()
{
	PushAndPopTest();
	BasicCallTest();
	CallTestFunction();

	std::cin.get();
	return 0;
}