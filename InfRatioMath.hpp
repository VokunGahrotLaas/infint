#ifndef INFRATIOMATH_HPP
#define INFRATIOMATH_HPP

// InfInt libs
#include "InfInt.hpp"
#include "InfIntMath.hpp"

// InfRatio libs
#include "InfRatio.hpp"

namespace InfRatioMath {

InfRatio abs(const InfRatio& infint);
InfInt round(const InfRatio& infint); // TODO
InfInt floor(const InfRatio& infint);
InfInt ceil(const InfRatio& infint); // TODO

const InfRatio& min(const InfRatio& a, const InfRatio& b);
InfRatio& min(InfRatio& a, InfRatio& b);

const InfRatio& max(const InfRatio& a, const InfRatio& b);
InfRatio& max(InfRatio& a, InfRatio& b);

/*InfRatio pow(const InfRatio& _a, const InfRatio& _b);
InfRatio modpow(const InfRatio& _a, const InfRatio& _b, const InfRatio& m);*/

InfRatio sqrt(const InfRatio& n);
//InfRatio root(const InfRatio& a, const InfRatio& b);

InfRatio log2(const InfInt& a); // TODO
InfRatio log2(const InfRatio& a);
InfRatio log(const InfRatio& a, const InfRatio& b);

/*InfRatio modulo(const InfRatio& a, const InfRatio& b);

InfRatio lcm(const InfRatio& a, const InfRatio& b);
InfRatio gcd(const InfRatio& _a, const InfRatio& _b);
InfRatioEGCDResult egcd(const InfRatio& a, const InfRatio& b);
InfRatio modinv(const InfInt& a, const InfInt& b);

bool congruent_modulo(const InfRatio& a, const InfRatio& b, const InfRatio& n);
bool coprime(const InfRatio& a, const InfRatio& b);*/

} // namesapce InfRatioMath



namespace InfRatioMath {

InfRatio abs(const InfRatio& infratio) {
	if (infratio.numerator().sign())
		return -infratio;
	else
		return infratio;
}

InfInt round(const InfRatio& infint) { // TODO
	return floor(infint);
}

InfInt floor(const InfRatio& infint) {
	return infint.numerator() / infint.divisor();
}

InfInt ceil(const InfRatio& infint) { // TODO
	return floor(infint);
}

InfRatio& min(InfRatio& a, InfRatio& b) {
	if (a <= b)
		return a;
	else
		return b;
}

const InfRatio& min(const InfRatio& a, const InfRatio& b) {
	if (a <= b)
		return a;
	else
		return b;
}

InfRatio& max(InfRatio& a, InfRatio& b) {
	if (a >= b)
		return a;
	else
		return b;
}

const InfRatio& max(const InfRatio& a, const InfRatio& b) {
	if (a >= b)
		return a;
	else
		return b;
}

InfRatio sqrt(const InfRatio& r) {
	if (r < InfRatio::zero)
		throw std::invalid_argument("InfRatio sqrt(const InfRatio& n): must have n >= 0 (n=" + r.str() + ")");
	InfRatio x = r;
	InfRatio old_x;
	while (old_x != x) {
		old_x = x;
		x = x - ( x * x - r ) / ( 2_infratio * x );
		std::cout << x << " | " << floor(x) << std::endl;
	}
	return x;
}

InfRatio log2(const InfInt& a) { // TODO
	return InfIntMath::log2(a);
}

InfRatio log2(const InfRatio& a) {
	return log2(a.numerator()) - log2(a.divisor());
}

InfRatio log(const InfRatio& a, const InfRatio& b) {
	return log2(a) / log2(b);
}

} // namespace InfIntMath

#endif // INFRATIOMATH_HPP