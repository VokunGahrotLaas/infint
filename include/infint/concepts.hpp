#pragma once

// C++ std
#include <array>
#include <concepts>
#include <limits>
#include <utility>
#include <vector>

namespace infint
{

template <typename T>
concept boolish = requires(T t, bool b) {
	static_cast<bool>(t);
	static_cast<T>(b);
	b = t;
	t = b;
	{
		!t
	} -> std::same_as<bool>;
	{
		(t && t)
	} -> std::same_as<bool>;
	{
		t || t
	} -> std::same_as<bool>;
	{
		t != t
	} -> std::same_as<bool>;
	{
		t == t
	} -> std::same_as<bool>;
};

template <typename T, typename U>
concept iterator_of = requires(T& t, std::size_t size) {
	{
		*t
	} -> std::convertible_to<U>;
	{
		t[size]
	} -> std::convertible_to<U>;
	{
		++t
	} -> std::same_as<T&>;
	{
		t++
	} -> std::same_as<T>;
	{
		--t
	} -> std::same_as<T&>;
	{
		t--
	} -> std::same_as<T>;
	{
		t += size
	} -> std::same_as<T&>;
	{
		t -= size
	} -> std::same_as<T&>;
	{
		t + size
	} -> std::same_as<T>;
	{
		t - size
	} -> std::same_as<T>;
};

template <typename T, typename U>
concept iterable_of = requires(T& t) {
	{
		std::begin(t)
	} -> iterator_of<U>;
	{
		std::end(t)
	} -> iterator_of<U>;
	{
		std::cbegin(t)
	} -> iterator_of<U>;
	{
		std::cend(t)
	} -> iterator_of<U>;
};

static_assert(iterable_of<int[10], int>);
static_assert(iterator_of<decltype(std::declval<std::vector<int>>().begin()), int>);
static_assert(iterable_of<std::array<int, 10>, int>);
static_assert(iterable_of<std::vector<int>, int>);
static_assert(!iterable_of<std::vector<std::vector<int>>, int>);
static_assert(!iterable_of<int[10], int[10]>);
static_assert(iterable_of<std::vector<std::vector<int>>, std::vector<int>>);

template <typename T>
concept infint_container = std::regular<T> and boolish<typename T::value_type>
	and iterable_of<T, typename T::value_type> and iterator_of<typename T::iterator, typename T::value_type>
	and iterator_of<typename T::const_iterator, typename T::value_type>
	and requires(T&& t, T& tm, typename T::value_type v, std::size_t size, typename T::const_iterator it, bool b) {
			tm.clear();
			tm.insert(it, size, v);
			tm.reserve(size);
			tm.resize(size, v);
			tm.emplace_back(v);
			tm.emplace_back(b);
			tm.pop_back();
			tm.erase(it, it);
			{
				std::forward<T>(t).size()
			} -> std::convertible_to<std::size_t>;
			{
				std::forward<T>(t).back()
			} -> std::convertible_to<bool>;
			{
				std::forward<T>(t)[size]
			} -> std::convertible_to<bool>;
		};

template <infint_container vector_t, boolish bool_t>
class infint;

template <typename InfInt>
concept is_infint = std::same_as<::infint::infint<typename InfInt::vector_type, typename InfInt::bool_type>, InfInt>;

template <int base>
concept valid_base = 2 <= base and base <= 62;

template <is_infint InfInt>
struct fulldiv_t;

template <typename T>
concept custom_integral = std::numeric_limits<T>::is_integer;

template <typename T>
concept integral = std::integral<T> or custom_integral<T>;

template <typename T>
concept custom_signed_integral = std::numeric_limits<T>::is_integer and std::numeric_limits<T>::is_signed;

template <typename T>
concept signed_integral = std::signed_integral<T> or custom_signed_integral<T>;

template <typename T>
concept custom_unsigned_integral = std::numeric_limits<T>::is_integer and not std::numeric_limits<T>::is_signed;

template <typename T>
concept unsigned_integral = std::unsigned_integral<T> or custom_unsigned_integral<T>;

template <typename F, auto Test = std::bool_constant<(F{}(), true)>()>
consteval auto is_constexpr(F)
{
	return Test;
}

template <auto value, std::constructible_from<decltype(value)> I = decltype(value)>
constinit I const const_integer{ value };

template <integral I>
constinit I const zero = const_integer<0, I>;

template <integral I>
constinit I const pos_one = const_integer<1, I>;

template <signed_integral I>
constinit I const neg_one = const_integer<-1, I>;

template <typename T>
class reversed_container
{
public:
	constexpr reversed_container(T& t)
		: t_{ t }
	{}
	constexpr auto begin() { return std::rbegin(t_); }
	constexpr auto begin() const { return std::crbegin(t_); }
	constexpr auto cbegin() const { return std::crbegin(t_); }
	constexpr auto end() { return std::rend(t_); }
	constexpr auto end() const { return std::crend(t_); }
	constexpr auto cend() const { return std::crend(t_); }
	constexpr auto rbegin() { return std::begin(t_); }
	constexpr auto rbegin() const { return std::cbegin(t_); }
	constexpr auto crbegin() const { return std::cbegin(t_); }
	constexpr auto rend() { return std::end(t_); }
	constexpr auto rend() const { return std::cend(t_); }
	constexpr auto crend() const { return std::cend(t_); }

private:
	T& t_;
};

template <typename T>
class const_reversed_container
{
public:
	[[gnu::always_inline]] constexpr const_reversed_container(T const& t)
		: t_{ t }
	{}
	[[gnu::always_inline]]
	constexpr auto begin() const
	{
		return std::crbegin(t_);
	}
	[[gnu::always_inline]]
	constexpr auto cbegin() const
	{
		return std::crbegin(t_);
	}
	[[gnu::always_inline]]
	constexpr auto end() const
	{
		return std::crend(t_);
	}
	[[gnu::always_inline]]
	constexpr auto cend() const
	{
		return std::crend(t_);
	}
	[[gnu::always_inline]]
	constexpr auto rbegin() const
	{
		return std::cbegin(t_);
	}
	[[gnu::always_inline]]
	constexpr auto crbegin() const
	{
		return std::cbegin(t_);
	}
	[[gnu::always_inline]]
	constexpr auto rend() const
	{
		return std::cend(t_);
	}
	[[gnu::always_inline]]
	constexpr auto crend() const
	{
		return std::cend(t_);
	}

private:
	T const& t_;
};

template <typename T>
[[gnu::always_inline]]
reversed_container<T> reversed(T& t)
{
	return { t };
}

template <typename T>
[[gnu::always_inline]]
const_reversed_container<T> reversed(T const& t)
{
	return { t };
}

} // namespace infint

template <::infint::infint_container vector_t, ::infint::boolish bool_t>
class std::numeric_limits<::infint::infint<vector_t, bool_t>>
{
public:
	using type = ::infint::infint<vector_t, bool_t>;

	static constexpr bool is_specialized = true;

	static constexpr type min() noexcept { return type::zero::value; }
	static constexpr type max() noexcept { return type::zero::value; }
	static constexpr type lowest() noexcept { return type::zero::value; }

	static constexpr int digits = numeric_limits<int>::max();
	static constexpr int digits10 = numeric_limits<int>::max();
	static constexpr int max_digits10 = 0;

	static constexpr bool is_signed = true;
	static constexpr bool is_integer = true;
	static constexpr bool is_exact = true;
	static constexpr int radix = 2;
	static constexpr type epsilon() noexcept { return type::zero::value; }
	static constexpr type round_error() noexcept { return type::zero::value; }

	static constexpr int min_exponent = 0;
	static constexpr int min_exponent10 = 0;
	static constexpr int max_exponent = 0;
	static constexpr int max_exponent10 = 0;

	static constexpr bool has_infinity = false;
	static constexpr bool has_quiet_NaN = false;
	static constexpr bool has_signaling_NaN = false;
	static constexpr float_denorm_style has_denorm = denorm_absent;
	static constexpr bool has_denorm_loss = false;
	static constexpr type infinity() noexcept { return type::zero::value; }
	static constexpr type quiet_NaN() noexcept { return type::zero::value; }
	static constexpr type signaling_NaN() noexcept { return type::zero::value; }
	static constexpr type denorm_min() noexcept { return type::zero::value; }

	static constexpr bool is_iec559 = false;
	static constexpr bool is_bounded = false;
	static constexpr bool is_modulo = false;

	static constexpr bool traps = false;
	static constexpr bool tinyness_before = false;
	static constexpr float_round_style round_style = round_toward_zero;
};
