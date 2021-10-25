#include <iostream>
#include <stdlib.h>
#include <cassert>

extern "C" void ToUpperCase(char* str, int count);
extern "C" void LoadE(char* str, int count);
extern "C" void LoadE5(char* str, int count);
extern "C" int FoundChar(char* str, char found);
extern "C" bool CompareString(char* str1, char* str2, int size);
extern "C" void InitArray(char* to, char* from, int size);

int main()
{
	char* string1 = new char[15] {
		"hello world"
	};
	int size = 15;
	
	char* string2 = new char[15]{
	"hello world"
	};

	char* string3 = new char[15]{
		"hello qorld"
	};

	// LoadE5(string, size);
	
	//int ind = FoundChar(string1, 'r');

	//bool result = CompareString(string1, string2, size);
	//assert(result);
	//std::cout << result << std::endl;
	//result = CompareString(string1, string3, size);
	//assert(!result);
	//std::cout << result << std::endl;

	char* string4 = new char[15];
	InitArray(string4, string1, size);
	std::cout << std::string(string4) << std::endl;

	delete[] string1;
	delete[] string2;
	delete[] string3;
	delete[] string4;

	std::cin.get();
	return 0;
}
