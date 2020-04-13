#ifndef INFINTRSA_HPP
#define INFINTRSA_HPP

#include "InfInt.hpp"
#include "InfIntMath.hpp"

class InfIntRSA {
public:
	InfIntRSA(void);
	InfIntRSA(const InfInt& p, const InfInt& q);
	InfIntRSA(const InfInt& p, const InfInt& q, const InfInt& min_e);
	~InfIntRSA(void);
	void create_keys(const InfInt& p, const InfInt& q);
	void create_keys(const InfInt& p, const InfInt& q, const InfInt& min_e);
	InfInt cypher(const InfInt& cyphered);
	InfInt uncypher(const InfInt& uncyphered);
	InfInt& e(void) { return this->m_e; }
	InfInt& d(void) { return this->m_d; }
	InfInt& n(void) { return this->m_n; }
protected:
	InfInt m_e;
	InfInt m_d;
	InfInt m_n;
};

#endif // INFINTRSA_HPP