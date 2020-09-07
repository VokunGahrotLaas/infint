#ifndef INFINTRESULT_HPP
#define INFINTRESULT_HPP

class InfInt;

class InfIntResult {};



class InfIntFullDivResult: InfIntResult {
public:
	InfIntFullDivResult(const InfInt& quotient, const InfInt& remainder);
	~InfIntFullDivResult(void);
	const InfInt& quotient(void) const;
	const InfInt& remainder(void) const;
protected:
	InfInt* m_quotient;
	InfInt* m_remainder;
};



class InfIntEGCDResult: InfIntResult {
public:
	InfIntEGCDResult(const InfInt& gcd, const InfInt& x, const InfInt& y);
	~InfIntEGCDResult(void);
	const InfInt& gcd(void) const;
	const InfInt& x(void) const;
	const InfInt& y(void) const;
protected:
	InfInt* m_gcd;
	InfInt* m_x;
	InfInt* m_y;
};



// InfInt libs
#include "InfInt.hpp"

InfIntFullDivResult::InfIntFullDivResult(const InfInt& quotient, const InfInt& remainder):
	m_quotient(new InfInt(quotient)),
	m_remainder(new InfInt(remainder))
{
	//
}

InfIntFullDivResult::~InfIntFullDivResult(void) {
	delete m_quotient;
	delete m_remainder;
}

const InfInt& InfIntFullDivResult::quotient(void) const { return *m_quotient; }
const InfInt& InfIntFullDivResult::remainder(void) const { return *m_remainder; }



InfIntEGCDResult::InfIntEGCDResult(const InfInt& gcd, const InfInt& x, const InfInt& y) :
	m_gcd(new InfInt(gcd)),
	m_x(new InfInt(x)),
	m_y(new InfInt(y))
{
	//
}

InfIntEGCDResult::~InfIntEGCDResult(void) {
	delete m_gcd;
	delete m_x;
	delete m_y;
}

const InfInt& InfIntEGCDResult::gcd(void) const { return *m_gcd; }
const InfInt& InfIntEGCDResult::x(void) const { return *m_x; }
const InfInt& InfIntEGCDResult::y(void) const { return *m_y; }

#endif // INFINTRESULT_HPP