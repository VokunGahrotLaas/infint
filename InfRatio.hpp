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



InfRatio::InfRatio(const InfInt& numerator, const InfInt& divisor):
	m_numerator(numerator),
	m_divisor(divisor)
{
	this->simplify();
}

InfRatio::~InfRatio(void) {
	//
}

const InfInt& InfRatio::numerator(void) const {
	return this->m_numerator;
}

void InfRatio::numerator(const InfInt& numerator) {
	if (this->numerator() != numerator) {
		this->m_numerator = numerator;
		simplify();
	}
}

const InfInt& InfRatio::divisor(void) const {
	return m_divisor;
}

void InfRatio::divisor(const InfInt& divisor) {
	if (this->divisor() != divisor) {
		this->m_divisor = divisor;
		simplify();
	}
}

bool InfRatio::sign(void) const {
	return this->numerator().sign();
}

std::string InfRatio::Bstr(void) const {
	if (this->divisor() != InfInt::pos_one)
		return this->numerator().Bstr() + "/" + this->divisor().Bstr();
	else
		return this->numerator().Bstr();
}

std::string InfRatio::str(int base) const {
	if (this->divisor() != InfInt::pos_one)
		return this->numerator().str(base) + "/" + this->divisor().str(base);
	else
		return this->numerator().str(base);
}

std::string InfRatio::str(void) const {
	if (this->divisor() != InfInt::pos_one)
		return this->numerator().str() + "/" + this->divisor().str();
	else
		return this->numerator().str();
}

InfRatio& InfRatio::operator=(const InfRatio& other) {
	this->m_numerator = other.numerator();
	this->m_divisor = other.divisor();
	return *this;
}

InfRatio InfRatio::operator*(const InfRatio& other) const {
	return InfRatio(*this) *= other;
}

InfRatio& InfRatio::operator*=(const InfRatio& other) {
	this->m_numerator *= other.numerator();
	this->m_divisor *= other.divisor();
	return this->simplify();
}

InfRatio InfRatio::operator+(void) const {
	return *this;
}

InfRatio InfRatio::operator-(void) const {
	InfRatio tmp(*this);
	tmp.m_numerator.twos_complement();
	return tmp.simplify();
}

InfRatio InfRatio::operator/(const InfRatio& other) const {
	return InfRatio(*this) /= other;
}

InfRatio& InfRatio::operator/=(const InfRatio& other) {
	this->m_numerator *= other.divisor();
	this->m_divisor *= other.numerator();
	return this->simplify();
}

InfRatio InfRatio::operator+(const InfRatio& other) const {
	return InfRatio(*this) += other;
}

InfRatio& InfRatio::operator+=(const InfRatio& other) {
	if (this->divisor() != other.divisor()) {
		InfInt lcm = InfIntMath::lcm(this->divisor(), other.divisor());
		this->m_numerator = this->numerator() * (lcm / this->divisor()) + other.numerator() * (lcm / other.divisor());
		this->m_divisor = lcm;
	} else
		this->m_numerator += other.numerator();
	return this->simplify();
}

InfRatio& InfRatio::operator++(void) { // prefix -> return after change
	*this += InfRatio::pos_one;
	return *this;
}

InfRatio InfRatio::operator++(int) { // postfix -> retrun before change
	InfRatio tmp(*this);
	*this += InfRatio::pos_one;
	return tmp;
}

InfRatio InfRatio::operator-(const InfRatio& other) const {
	return InfRatio(*this) -= other;
}

InfRatio& InfRatio::operator-=(const InfRatio& other) {
	if (this->divisor() != other.divisor()) {
		InfInt lcmVal = InfIntMath::lcm(this->divisor(), other.divisor());
		this->m_numerator = this->numerator() * (lcmVal / this->divisor()) - other.numerator() * (lcmVal / other.divisor());
		this->m_divisor = lcmVal;
	}
	else
		this->m_numerator -= other.numerator();
	return this->simplify();
}

InfRatio& InfRatio::operator--(void) { // prefix -> return after change
	*this -= InfRatio::pos_one;
	return *this;
}

InfRatio InfRatio::operator--(int) { // postfix -> retrun before change
	InfRatio tmp(*this);
	*this -= InfRatio::pos_one;
	return tmp;
}

bool InfRatio::operator==(const InfRatio& other) const {
	return this->numerator() == other.numerator() && this->divisor() == other.divisor();
}

bool InfRatio::operator!=(const InfRatio& other) const {
	return this->numerator() != other.numerator() || this->divisor() != other.divisor();
}

bool InfRatio::operator>(const InfRatio& other) const {
	if (this->divisor() != other.divisor()) {
		InfInt lcm = InfIntMath::lcm(this->divisor(), other.divisor());
		return this->numerator() * (lcm / this->divisor()) > other.numerator() * (lcm / other.divisor());
	}
	else
		return this->numerator() > other.numerator();
}

bool InfRatio::operator<(const InfRatio& other) const {
	if (this->divisor() != other.divisor()) {
		InfInt lcm = InfIntMath::lcm(this->divisor(), other.divisor());
		return this->numerator() * (lcm / this->divisor()) < other.numerator() * (lcm / other.divisor());
	}
	else
		return this->numerator() < other.numerator();
}

bool InfRatio::operator>=(const InfRatio& other) const {
	if (m_divisor != other.divisor()) {
		InfInt lcm = InfIntMath::lcm(this->divisor(), other.divisor());
		return this->numerator() * (lcm / this->divisor()) >= other.numerator() * (lcm / other.divisor());
	}
	else
		return this->numerator() >= other.numerator();
}

bool InfRatio::operator<=(const InfRatio& other) const {
	if (this->divisor() != other.divisor()) {
		InfInt lcm = InfIntMath::lcm(this->divisor(), other.divisor());
		return this->numerator() * (lcm / this->divisor()) <= other.numerator() * (lcm / other.divisor());
	}
	else
		return this->numerator() <= other.numerator();
}

InfRatio InfRatio::zero = InfInt::zero;
InfRatio InfRatio::neg_one = InfInt::neg_one;
InfRatio InfRatio::pos_one = InfInt::pos_one;



InfRatio& InfRatio::simplify(void) {
	if (this->divisor() == InfInt::zero)
		throw std::invalid_argument("Divisor can not be 0 !");
	if (this->numerator() == InfInt::zero)
		this->m_divisor = InfInt::pos_one;
	else {
		InfInt gcd = InfIntMath::gcd(this->m_numerator, this->m_divisor);
		this->m_numerator /= gcd;
		this->m_divisor /= gcd;
	}
	if (this->divisor() < InfInt::zero) {
		this->m_numerator.twos_complement();
		this->m_divisor.twos_complement();
	}
	return *this;
}



InfRatio operator "" _infratio(unsigned long long other) {
	return static_cast<InfRatio>(other);
}

std::ostream& operator<<(std::ostream& out, const InfRatio& ratio) {
	if (ratio.divisor() != InfInt::pos_one)
		out << ratio.numerator() << "/" << ratio.divisor();
	else
		out << ratio.numerator();
	return out;
}

#endif // INFRATIO_HPP