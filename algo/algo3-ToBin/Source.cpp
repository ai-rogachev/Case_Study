#include <iostream>

void PrintBin(int num)
{
	std::string bin_test;

	int length = sizeof(num) * 8;
	for (int i = length - 1; i >= 0; --i)
	{
		int bit = (num & (1 << i)) != 0;
		std::cout << bit;
	}
}

int main() 
{
	int number;
	
	for (int i = 1'000'000; i > -1'000'000; --i) 
	{
		PrintBin(i);
		std::cout << std::endl;
	}
	std::cout << "OK!!" << std::endl;

	return 0;
}