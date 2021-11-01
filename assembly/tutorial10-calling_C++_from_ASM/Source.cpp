#include <iostream>
#include <stdlib.h>
#include <cassert>

extern "C" void CallACPPProcedure();

extern "C" void MyProc(int a, int b, int c, int d, int e, int f)
{
	std::cout << a << b << c << d << e << f << std::endl;
}

int main()
{
	CallACPPProcedure();

	std::cin.get();
	return 0;
}
