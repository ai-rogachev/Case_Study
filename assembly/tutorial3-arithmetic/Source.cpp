#include <iostream>

extern "C" int AsmAddInt(int a, int b);
extern "C" int AsmSub(int a, int b);
extern "C" int AsmNeg(int a);

int main()
{
	std::cout << AsmAddInt(3, 5) << std::endl;
	std::cout << AsmSub(4, 4) << std::endl;
	std::cout << AsmNeg(3) << std::endl;
	return 0;
}