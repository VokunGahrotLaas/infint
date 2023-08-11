#ifndef INFRATIOMATH_HPP
#define INFRATIOMATH_HPP

// InfInt libs
#include "InfInt.hpp"
#include "InfIntMath.hpp"

// InfRatio libs
#include "InfRatio.hpp"

namespace InfRatioMath
{

InfRatio abs(InfRatio const& infint);
InfInt round(InfRatio const& infint); // TODO
InfInt floor(InfRatio const& infint);
InfInt ceil(InfRatio const& infint); // TODO

InfRatio const& min(InfRatio const& a, InfRatio const& b);
InfRatio& min(InfRatio& a, InfRatio& b);

InfRatio const& max(InfRatio const& a, InfRatio const& b);
InfRatio& max(InfRatio& a, InfRatio& b);

/*InfRatio pow(const InfRatio& _a, const InfRatio& _b);
InfRatio modpow(const InfRatio& _a, const InfRatio& _b, const InfRatio&
m);*/

InfRatio sqrt(InfRatio const& n);
// InfRatio root(const InfRatio& a, const InfRatio& b);

InfRatio log2(InfInt const& a); // TODO
InfRatio log2(InfRatio const& a);
InfRatio log(InfRatio const& a, InfRatio const& b);

/*InfRatio modulo(const InfRatio& a, const InfRatio& b);

InfRatio lcm(const InfRatio& a, const InfRatio& b);
InfRatio gcd(const InfRatio& _a, const InfRatio& _b);
InfRatioEGCDResult egcd(const InfRatio& a, const InfRatio& b);
InfRatio modinv(const InfInt& a, const InfInt& b);

bool congruent_modulo(const InfRatio& a, const InfRatio& b, const InfRatio&
n); bool coprime(const InfRatio& a, const InfRatio& b);*/

} // namespace InfRatioMath

namespace InfRatioMath
{

InfRatio abs(InfRatio const& infratio)
{
	if (infratio.numerator().sign())
		return -infratio;
	else
		return infratio;
}

InfInt round(InfRatio const& infint)
{ // TODO
	return floor(infint);
}

InfInt floor(InfRatio const& infint) { return infint.numerator() / infint.divisor(); }

InfInt ceil(InfRatio const& infint)
{ // TODO
	return floor(infint);
}

InfRatio& min(InfRatio& a, InfRatio& b)
{
	if (a <= b)
		return a;
	else
		return b;
}

InfRatio const& min(InfRatio const& a, InfRatio const& b)
{
	if (a <= b)
		return a;
	else
		return b;
}

InfRatio& max(InfRatio& a, InfRatio& b)
{
	if (a >= b)
		return a;
	else
		return b;
}

InfRatio const& max(InfRatio const& a, InfRatio const& b)
{
	if (a >= b)
		return a;
	else
		return b;
}

InfRatio sqrt(InfRatio const& r)
{
	if (r < InfRatio::zero)
		throw std::invalid_argument("InfRatio sqrt(const InfRatio& n): must have n >= 0 (n=" + r.str() + ")");
	InfRatio x = r;
	InfRatio old_x;
	while (old_x != x)
	{
		old_x = x;
		x = x - (x * x - r) / (2_infratio * x);
		std::cout << x << " | " << floor(x) << std::endl;
	}
	return x;
}

InfRatio log2(InfInt const& a)
{ // TODO
	return InfIntMath::log2(a);
}

InfRatio log2(InfRatio const& a) { return log2(a.numerator()) - log2(a.divisor()); }

InfRatio log(InfRatio const& a, InfRatio const& b) { return log2(a) / log2(b); }

} // namespace InfRatioMath

#endif // INFRATIOMATH_HPP
