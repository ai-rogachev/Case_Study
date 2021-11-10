#include <iostream>

extern "C" size_t _cdecl CalcCrc32(char* msg, size_t len);
//extern "C" size_t _cdecl CalcCrc32(int msg, int len);

int main()
{
	char* msg = "0123456789";
	size_t len = 10;

	auto crc = CalcCrc32(msg, len);

	std::cout << std::hex << crc << std::endl;

	std::cin.get();
	return 0;
}
