#include "InfIntResult.hpp"

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