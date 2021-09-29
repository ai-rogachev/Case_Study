#include <iostream>

extern "C" int OrTest(int value, int mask);

int main()
{
	int value = 3;
	int mask = 5;

	std::cout << OrTest(value, mask) << std::endl;
	
	std::cin.get();
	return 0;
}