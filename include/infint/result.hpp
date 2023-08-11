#pragma once

#include <infint/infint.hpp>

namespace infint
{

template <is_infint InfInt>
struct result_t
{
	using infint_type = InfInt;
};

template <is_infint InfInt>
struct fulldiv_t : result_t<InfInt>
{
	using super = result_t<InfInt>;
	using infint_type = typename super::infint_type;

	constexpr fulldiv_t() = default;
	constexpr fulldiv_t(fulldiv_t const&) = default;
	constexpr fulldiv_t(fulldiv_t&&) = default;
	constexpr fulldiv_t(infint_type&& quotient, infint_type&& remainder);
	constexpr fulldiv_t(infint_type const& quotient, infint_type const& remainder);

	constexpr fulldiv_t& operator=(fulldiv_t const&) = default;
	constexpr fulldiv_t& operator=(fulldiv_t&&) = default;

	infint_type q;
	infint_type r;
};

template <is_infint InfInt>
struct egcd_t : result_t<InfInt>
{
	using super = result_t<InfInt>;
	using infint_type = typename super::infint_type;

	constexpr egcd_t() = default;
	constexpr egcd_t(egcd_t const&) = default;
	constexpr egcd_t(egcd_t&&) = default;
	constexpr egcd_t(infint_type&& gcd, infint_type&& x, infint_type&& y);
	constexpr egcd_t(infint_type const& gcd, infint_type const& x, infint_type const& y);

	constexpr egcd_t& operator=(egcd_t const&) = default;
	constexpr egcd_t& operator=(egcd_t&&) = default;

	infint_type gcd;
	infint_type x;
	infint_type y;
};

} // namespace infint

#include <infint/result.hxx>
