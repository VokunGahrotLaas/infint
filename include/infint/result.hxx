#pragma once

#include <infint/result.hpp>

namespace infint
{

template <is_infint InfInt>
constexpr fulldiv_t<InfInt>::fulldiv_t(infint_type&& quotient, infint_type&& remainder)
	: q(std::move(quotient))
	, r(std::move(remainder))
{}

template <is_infint InfInt>
constexpr fulldiv_t<InfInt>::fulldiv_t(infint_type const& quotient, infint_type const& remainder)
	: q(quotient)
	, r(remainder)
{}

template <is_infint InfInt>
constexpr egcd_t<InfInt>::egcd_t(infint_type&& gcd, infint_type&& x, infint_type&& y)
	: gcd(std::move(gcd))
	, x(std::move(x))
	, y(std::move(y))
{}

template <is_infint InfInt>
constexpr egcd_t<InfInt>::egcd_t(infint_type const& gcd, infint_type const& x, infint_type const& y)
	: gcd(gcd)
	, x(x)
	, y(y)
{}

} // namespace infint
