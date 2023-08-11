#include <algorithm>
#include <cassert>
#include <infint/infint.hpp>
#include <infint/stack_allocator.hpp>
#include <infint/stack_vector.hpp>

using ulong_allocator_t = ::infint::stack_allocator<unsigned long>;
using int_allocator_t = ::infint::stack_allocator<int>;
using char_allocator_t = ::infint::stack_allocator<char>;

using vector_t = std::vector<bool>;
using stack_vector_t = std::vector<bool, ulong_allocator_t>;
using my_stack_vector_t = ::infint::stack_vector<bool, 1'024>;

using infint_ = ::infint::infint<vector_t>;
using stack_infint = ::infint::infint<stack_vector_t>;
using my_stack_infint = ::infint::infint<my_stack_vector_t>;

template <::infint::is_infint InfInt, std::integral T>
consteval T id(T value)
{
	return (InfInt::of(value) / InfInt::of(1)).template to_int<T>();
}

template <std::size_t size, std::size_t base = 0, ::infint::is_infint InfInt>
constexpr std::array<char, size> str(InfInt const& i)
{
	std::string str;
	if constexpr (base == 0)
		str = i.str();
	else
		str = i.template str<base>();
	assert(str.size() + 1 <= size);
	std::array<char, size> arr{ '\0' };
	std::copy(str.cbegin(), str.cend(), arr.begin());
	return arr;
}

template <std::size_t size>
constexpr std::string_view str_view(std::array<char const, size> arr)
{
	return std::string_view{ arr.data(), size };
}

template <std::size_t size, std::integral T>
constexpr my_stack_infint stack_infint_of(T i)
{
	std::array<unsigned long, size> stack{};
	ulong_allocator_t allocator{ stack };
	return stack_infint::of(i, stack_vector_t(allocator));
}

int main()
{
	constexpr auto a = stack_infint_of<1'024>(1'618);
	constexpr auto arr = str<5, 10, infint_>(a);
	constexpr int i = id<infint_>(1'618);
	std::cout << str_view(arr) << std::endl;
	std::cout << i << std::endl;
	return 0;
}
