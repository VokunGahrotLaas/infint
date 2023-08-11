#pragma once

// C++ std lib
#include <algorithm>
#include <concepts>
#include <exception>
#include <iostream>
#include <limits>
#include <string>
#include <type_traits>
#include <vector>

// C std lib
#include <cmath>

// infint
#include <infint/concepts.hpp>

namespace infint
{

template <infint_container vector_t = std::vector<bool>, boolish bool_t = typename vector_t::value_type>
class infint
{
public:
	using bool_type = bool_t;
	using vector_type = vector_t;
	using vector_const_iterator = typename vector_t::const_iterator;
	using size_type = typename vector_t::size_type;

	constexpr infint(vector_t&& vec = {}); // init to +0
	constexpr infint(infint const& other) = default; // copy
	constexpr infint(infint&& other); // move
	constexpr ~infint() = default;

	template <infint_container ovector_t, boolish obool_t>
	constexpr infint(infint<ovector_t, obool_t> const& other);

	// from ints
	template <std::signed_integral T>
	constexpr infint(T other, vector_t&& vec = {});
	template <std::unsigned_integral T>
	constexpr infint(T other, vector_t&& vec = {});

	template <std::signed_integral T>
	static constexpr infint of(T other, vector_t&& vec = {});
	template <std::unsigned_integral T>
	static constexpr infint of(T other, vector_t&& vec = {});

	// from strings
	explicit constexpr infint(std::string_view other); // base 2
	template <int base_>
		requires valid_base<base_>
	explicit constexpr infint(std::string_view other,
							  std::integral_constant<int, base_> base); // custom base from 2 to 62

	static constexpr infint of(std::string_view other); // base 2
	template <int base>
		requires valid_base<base>
	static constexpr infint of(std::string_view other); // custom base from 2 to 62

	constexpr infint& operator=(infint const& other) = default; // copy
	constexpr infint& operator=(infint&& other); // move

	constexpr operator bool() const;

	constexpr vector_t const& number() const;
	constexpr bool_t sign() const;
	constexpr bool_t get(size_type pos) const;
	template <std::integral T>
	constexpr T get_int(size_type pos) const;
	constexpr bool_t operator[](size_type pos) const;
	constexpr size_type size() const;
	// complements //
	constexpr infint& ones_complement(void);
	constexpr infint& twos_complement(void);
	// casting //
	constexpr std::string Bstr() const;
	constexpr std::string Bstr(size_type str_size) const;
	template <int base_>
		requires valid_base<base_>
	constexpr std::string str(std::integral_constant<int, base_> base = std::integral_constant<int, base_>()) const;
	constexpr std::string str() const;
	template <std::integral T>
	constexpr T to_int(void) const;
	template <std::integral T>
	constexpr T to_int_safe(void) const;
	// 2 in 1 operator //
	static constexpr fulldiv_t<infint> fulldiv(infint const& a, infint const& b);
	// operator //
	// cmp
	constexpr bool operator==(infint const& other) const;
	constexpr bool operator!=(infint const& other) const = default;
	constexpr bool operator>(infint const& other) const = default;
	constexpr bool operator<=(infint const& other) const = default;
	constexpr bool operator<(infint const& other) const = default;
	constexpr bool operator>=(infint const& other) const = default;
	constexpr std::strong_ordering operator<=>(infint const& other) const;
	// unary
	constexpr infint operator+(void) const;
	constexpr infint operator-(void) const;
	// add
	constexpr infint operator+(infint const& other) const;
	constexpr infint& operator+=(infint const& other);
	constexpr infint& operator++(void);
	constexpr infint operator++(int);
	// sub
	constexpr infint operator-(infint const& other) const;
	constexpr infint& operator-=(infint const& other);
	constexpr infint& operator--(void);
	constexpr infint operator--(int);
	// mul
	constexpr infint operator*(infint const& other) const;
	constexpr infint& operator*=(infint const& other);
	// div
	constexpr infint operator/(infint const& other) const;
	constexpr infint& operator/=(infint const& other);
	// mod
	constexpr infint operator%(infint const& other) const;
	constexpr infint& operator%=(infint const& other);
	// bitwise
	constexpr infint operator&(infint const& other) const;
	constexpr infint& operator&=(infint const& other);
	constexpr infint operator|(infint const& other) const;
	constexpr infint& operator|=(infint const& other);
	constexpr infint operator^(infint const& other) const;
	constexpr infint& operator^=(infint const& other);
	constexpr infint operator<<(size_type other) const;
	constexpr infint& operator<<=(size_type other);
	constexpr infint operator>>(size_type other) const;
	constexpr infint& operator>>=(size_type other);

	[[nodiscard]]
	static constexpr infint zero();
	[[nodiscard]]
	static constexpr infint pos_one();
	[[nodiscard]]
	static constexpr infint neg_one();

protected:
	constexpr infint(bool_t sign, vector_t&& number);
	constexpr infint& clean(void);
	// Attributes //
	vector_t number_;
	bool_t sign_;
};

// alows the use of the macro _infint to
// transform a unsigned long long to an infint
constexpr infint<> operator"" _infint(unsigned long long other);
template <infint_container vector_t, boolish bool_t>
std::ostream& operator<<(std::ostream& out, infint<vector_t, bool_t> const& infint);
template <infint_container vector_t, boolish bool_t>
std::istream& operator>>(std::istream& in, infint<vector_t, bool_t>& infint);

} // namespace infint

#include <infint/infint.hxx>
