#include "InfIntMath.hpp"

namespace InfIntMath {

InfInt abs(const InfInt& infint) {
	InfInt tmp(infint);
	if (tmp.sign())
		tmp.twos_complement();
	return tmp;
}

InfInt& min(InfInt& a, InfInt& b) {
	if (a <= b)
		return a;
	else
		return b;
}

const InfInt& min(const InfInt& a, const InfInt& b) {
	if (a <= b)
		return a;
	else
		return b;
}

InfInt& max(InfInt& a, InfInt& b) {
	if (a >= b)
		return a;
	else
		return b;
}

const InfInt& max(const InfInt& a, const InfInt& b) {
	if (a >= b)
		return a;
	else
		return b;
}

InfInt pow(const InfInt& _a, const InfInt& _b) {
	if (_b == InfInt::zero) {
		if (_a == InfInt::zero)
			throw std::exception("InfInt InfIntMath::pow(const InfInt& _a, const InfInt& _b): Division by zero");
		return InfInt::pos_one;
	}
	if (_b < InfInt::zero) {
		if (_a == InfInt::zero)
			throw std::exception("InfInt InfIntMath::pow(const InfInt& _a, const InfInt& _b): Division by zero");
		return InfInt::zero;
	}

	InfInt a(_a);
	InfInt b(_b);
	InfInt r(InfInt::pos_one);

	while (b.size() != 1) {
		if (b.get(0))
			r *= a;
		a *= a;
		b >>= 1;
	}
	if (b.get(0))
		r *= a;

	return r;
}

InfInt modpow(const InfInt& _a, const InfInt& _b, const InfInt& m) {
	if (_b == InfInt::zero) {
		if (_a == InfInt::zero)
			throw std::exception("InfInt InfIntMath::modpow(const InfInt& _a, const InfInt& _b, const InfInt& m): Division by zero");
		return InfInt::pos_one;
	}
	if (_b < InfInt::zero) {
		if (_a == InfInt::zero)
			throw std::exception("InfInt InfIntMath::modpow(const InfInt& _a, const InfInt& _b, const InfInt& m): Division by zero");
		return InfInt::zero;
	}

	InfInt a(_a);
	InfInt b(_b);
	InfInt r(InfInt::pos_one);

	while (b.size() != 1) {
		if (b.get(0))
			r = r * a % m;
		a = a * a % m;
		b >>= 1;
	}
	if (b.get(0))
		r = r * a % m;

	return r;
}

InfInt lcm(const InfInt& a, const InfInt& b) {
	return a / gcd(a, b) * b;
}

InfInt gcd(const InfInt& _a, const InfInt& _b) {
	InfInt a(_a);
	InfInt b(_b);
	while (b != InfInt::zero) {
		InfInt c = a % b;
		a = b;
		b = c;
	}
	return a;
}

InfIntEGCDResult egcd(const InfInt& a, const InfInt& b) {
	InfInt r = b;
	InfInt old_r = a;

	InfInt s = InfInt::zero;
	InfInt old_s = InfInt::pos_one;

	InfInt t = InfInt::pos_one;
	InfInt old_t = InfInt::zero;

	while (r != InfInt::zero) {
		InfInt tmp_r(r), tmp_s(s), tmp_t(t);
		auto result = InfInt::full_div(old_r, r);

		r = result.remainder();
		s = old_s - result.quotient() * s;
		t = old_t - result.quotient() * t;

		old_r = tmp_r;
		old_s = tmp_s;
		old_t = tmp_t;
	}

	/*std::cout
	<< std::endl
	<< "EGCD:" << std::endl
	<< "gdc: " << old_r << std::endl
	<< "x: " << old_s << std::endl
	<< "y: " << old_t << std::endl
	<< std::endl;*/

	return InfIntEGCDResult(old_r, old_s, old_t);
}

InfInt modinv(const InfInt& a, const InfInt& b) {
	InfInt r = b;
	InfInt old_r = a;

	InfInt s = InfInt::zero;
	InfInt old_s = InfInt::pos_one;

	while (r != InfInt::zero) {
		InfInt tmp_r(r), tmp_s(s);
		auto result = InfInt::full_div(old_r, r);

		r = result.remainder();
		s = old_s - result.quotient() * s;

		old_r = tmp_r;
		old_s = tmp_s;
	}

	return old_s;
}

bool congruent_modulo(const InfInt& a, const InfInt& b, const InfInt& n) {
	return ((a - b) % n) == InfInt::zero;
}

bool coprime(const InfInt& a, const InfInt& b) {
	return gcd(a, b) == InfInt::pos_one;
	/*if (a == b)
	return false;
	if (!a.get(0) && !b.get(0))
	return false;
	const InfInt& min(min(a, b));
	const InfInt two(2);
	for (InfInt i = 3; i <= min; i += two)
	if (a % i == 0 && b % i == 0)
	return false;
	return true;*/
}

} // namespace InfIntMath