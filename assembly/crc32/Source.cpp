#include <iostream>

// for test
// https://crc32.online/

/*  
	Width  : 32
	Poly   : 0x04c11db7
	Init   : parameter, typically 0xffffffff
	RefIn  : false
	RefOut : false
	XorOut : 0
*/

extern "C" size_t _cdecl CalcCrc32(char* msg, size_t len);

int main()
{
	char* msg = "0123456789";
	size_t len = 10;

	auto crc = CalcCrc32(msg, len);

	std::cout << std::hex << crc << std::endl;

	std::cin.get();
	return 0;
}
