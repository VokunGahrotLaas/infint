#include <iostream>
#include <vector>

template <typename T, T value = T{}>
constexpr std::size_t foo()
{
	std::vector<T> vec{ value, value, value };
	return vec.size();
}

int main()
{
	constexpr auto bar = foo<bool>();
	std::cout << bar << std::endl;
	return 0;
}
