#include <iostream>
#define INT_MAX 2147483647
namespace spc
{
	template <typename T>
	void input(T& number)
	{
		std::cin >> number;
		while (!std::cin.good())
		{
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << "ERROR - Reingrese el valor: ";
			std::cin >> number;
		}
		std::cin.sync();
	}
}
