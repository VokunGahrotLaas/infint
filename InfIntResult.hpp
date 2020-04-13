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

#endif // INFINTRESULT_HPP