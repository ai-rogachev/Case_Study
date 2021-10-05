#include <iostream>

// https://habr.com/ru/post/59558/

int main()
{
	const int i = 0;
	int j = 9;

	i = j;

	const int* ptr = &j;
	ptr = &i;
	*ptr = 10;

	int* const constPtr = &j;
	constPtr = &i;
	*constPtr = i;

	const char* arrayOne = new char[10];
	const char* const arrayTwo = new char[10];

	arrayOne[0] = 5;
	arrayOne[1] = 7;
	arrayOne[5] = 10;

	arrayOne = arrayTwo;

	arrayTwo[0] = 5;
	arrayTwo[1] = 7;
	arrayTwo[5] = 10;

	arrayTwo = arrayOne;

	char* const arrayTree = new char[10];

	arrayTree[0] = 5;
	arrayTree[1] = 7;
	arrayTree[5] = 10;

	arrayTree = arrayTwo;


	int g = 10;
	const int& refG = g;

	refG = 20;
	refG = i;


	std::cin.get();
	return 0;
}