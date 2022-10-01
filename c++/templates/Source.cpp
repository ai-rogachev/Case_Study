#include "TypenameTest.h"

int main()
{
	smell(A::rose());
	smell(B<A>::foo());

	std::cin.get();
	return 0;
}