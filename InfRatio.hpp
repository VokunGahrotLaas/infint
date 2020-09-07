#ifndef INFRATIO_HPP
#define INFRATIO_HPP

// std libs
#include <iostream>
#include <string>

// InfInt libs
#include "InfInt.hpp"
#include "InfIntMath.hpp"

class InfRatio {
public:
	InfRatio(const InfInt& numerator = InfInt::zero, const InfInt& divisor = InfInt::pos_one);
	virtual ~InfRatio(void); // empty

	const InfInt& numerator(void) const;
	void numerator(const InfInt& numerator);
	const InfInt& divisor(void) const;
	void divisor(const InfInt& divisor);

	bool sign(void) const;

	std::string Bstr(void) const;
	std::string str(int base) const;
	std::string str(void) const;

	InfRatio& operator=(const InfRatio& other);

	InfRatio operator*(const InfRatio& other) const;
	InfRatio& operator*=(const InfRatio& other);

	InfRatio operator+(void) const;
	InfRatio operator-(void) const;

	InfRatio operator/(const InfRatio& other) const;
	InfRatio& operator/=(const InfRatio& other);

	InfRatio operator+(const InfRatio& other) const;
	InfRatio& operator+=(const InfRatio& other);
	InfRatio& operator++(void);
	InfRatio operator++(int);

	InfRatio operator-(const InfRatio& other) const;
	InfRatio& operator-=(const InfRatio& other);
	InfRatio& operator--(void);
	InfRatio operator--(int);

	bool operator==(const InfRatio& other) const;
	bool operator!=(const InfRatio& other) const;

	bool operator>(const InfRatio& other) const;
	bool operator<(const InfRatio& other) const;
	bool operator>=(const InfRatio& other) const;
	bool operator<=(const InfRatio& other) const;

	static InfRatio zero;
	static InfRatio neg_one;
	static InfRatio pos_one;

protected:
	InfRatio& simplify(void);

	InfInt m_numerator;
	InfInt m_divisor;
};

InfRatio operator "" _infratio(unsigned long long other);
std::ostream& operator<<(std::ostream& stream, const InfRatio& ratio);

#endif // INFRATIO_HPP