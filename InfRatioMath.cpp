#include "InfRatioMath.hpp"

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