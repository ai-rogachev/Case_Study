#include <iostream>
#include <stdlib.h>

extern "C" void ZeroArray(void* array, int sizeInBytes);

void printArray(const char* array, int size)
{
	for (size_t i = 0; i < size; ++i) {
		std::cout << (int) array[i] << " ";
		if (i % 15 == 0)
			std::cout << std::endl;
	}
}

int main()
{
	const int size = 1024;
	char* array = new char[size];

	for (size_t i = 0; i < size; ++i) {
		array[i] = (char)rand();
	}

	printArray(array, size);
	ZeroArray(array, size);
	printArray(array, size);

	delete[] array;

	std::cin.get();
	return 0;
}