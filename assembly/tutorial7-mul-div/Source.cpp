#include <iostream>
#include <stdlib.h>

extern "C" int Multiply(int a, int b);
extern "C" int Divide(int a, int b);
extern "C" int Remainder(int a, int b);

int main()
{
	int x, y;

	while (true)
	{
		std::cout << "Input number (0 for exit): ";
		std::cin >> x;
		if (x == 0)
			break;

		std::cout << "Input another (0 for exit): ";
		std::cin >> y;
		if (y == 0)
			break;

		std::cout << x << " * " << y << " = " << Multiply(x, y) << std::endl;
		std::cout << x << " / " << y << " = " << Divide(x, y) << std::endl;
		std::cout << x << " % " << y << " = " << Remainder(x, y) << std::endl;
	}

	std::cin.get();
	return 0;
}