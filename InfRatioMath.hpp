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

#endif // INFRATIOMATH_HPP