#ifndef INFINTMATH_HPP
#define INFINTMATH_HPP

// InfInt libs
#include "InfInt.hpp"
#include "InfIntResult.hpp"
#include "InfIntRandom.hpp"

namespace InfIntMath {

InfInt abs(const InfInt& infint);

const InfInt& min(const InfInt& a, const InfInt& b);
InfInt& min(InfInt& a, InfInt& b);

const InfInt& max(const InfInt& a, const InfInt& b);
InfInt& max(InfInt& a, InfInt& b);

InfInt pow(const InfInt& _a, const InfInt& _b);
InfInt modpow(const InfInt& _a, const InfInt& _b, const InfInt& m);

InfInt sqrt(const InfInt& n);
InfInt root(const InfInt& a, const InfInt& b);

InfInt log2(const InfInt& a);
InfInt log(const InfInt& a, const InfInt& b);

InfInt modulo(const InfInt& a, const InfInt& b);

InfInt lcm(const InfInt& a, const InfInt& b);
InfInt gcd(const InfInt& _a, const InfInt& _b);
InfIntEGCDResult egcd(const InfInt& a, const InfInt& b);
InfInt modinv(const InfInt& a, const InfInt& b);

bool congruent_modulo(const InfInt& a, const InfInt& b, const InfInt& n);
bool coprime(const InfInt& a, const InfInt& b);

bool probable_prime_base(const InfInt& n, const InfInt& a);
bool probable_prime(const InfInt& n);

} // namesapce InfIntMath

#endif // INFINTMATH_HPP