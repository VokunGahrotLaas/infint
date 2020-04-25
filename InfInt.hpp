/* README.md
# InfInt

## Desc
 C++ library for infinit integers.\
 __Vers:__ 1.4

## Auth
 * [Maxence MICHOT](https://github.com/VokunGahrotLaas)
 */

#ifndef INFINT_HPP
#define INFINT_HPP

// std libs
#include <iostream> // iostreams (cout, cin, etc...)
#include <string> // std::string
#include <algorithm> // std::reverse() (reverse std::string, I was too lazy to do it myself...)
#include <vector> // std::vector<bool> for memory friendly data

// InfInt libs
#include "InfIntResult.hpp"

class InfInt {
public:
	// typedef //
	typedef std::vector<bool>::size_type size_type; // usualy unsigned long long
	// constructor //
	// default
	InfInt(void); // init to +0
	// copy
	InfInt(char other); // char
	InfInt(const InfInt& other); // InfInt
	InfInt(int other); // int
	InfInt(unsigned int other); // unsigned int
	InfInt(long other); // long
	InfInt(unsigned long other); // unsigned long
	InfInt(long long other); // long long
	InfInt(unsigned long long other); // unsigned long long
	InfInt(std::string other); // std::string
	InfInt(std::string other, int base); // std::string with base
	// destructor //
	virtual ~InfInt(void); // empty
	// const getter //
	bool sign(void) const;
	bool get(const size_type& pos) const;
	size_type size(void) const;
	// complements //
	InfInt& ones_complement(void);
	InfInt& twos_complement(void);
	// casting //
	std::string Bstr(void) const;
	std::string Bstr(size_type str_size) const;
	std::string str(int base) const;
	std::string str(void) const;
	template <class T> T to_int(void) const;
	template <class T> T to_int_safe(void) const;
	// 2 in 1 operator //
	static InfIntFullDivResult fulldiv(const InfInt& a, const InfInt& b);
	// operator //
	// equal
	InfInt& operator=(const InfInt& other);
	// cmp
	bool operator==(const InfInt& other) const;
	bool operator!=(const InfInt& other) const;
	bool operator>(const InfInt& other) const;
	bool operator<=(const InfInt& other) const;
	bool operator<(const InfInt& other) const;
	bool operator>=(const InfInt& other) const;
	// unary
	InfInt operator+(void) const;
	InfInt operator-(void) const;
	// add
	InfInt operator+(const InfInt& other) const;
	InfInt& operator+=(const InfInt& other);
	InfInt& operator++(void);
	InfInt operator++(int);
	// sub
	InfInt operator-(const InfInt& other) const;
	InfInt& operator-=(const InfInt& other);
	InfInt& operator--(void);
	InfInt operator--(int);
	// mul
	InfInt operator*(const InfInt& other) const;
	InfInt& operator*=(const InfInt& other);
	// div
	InfInt operator/(const InfInt& other) const;
	InfInt& operator/=(const InfInt& other);
	// mod
	InfInt operator%(const InfInt& other) const;
	InfInt& operator%=(const InfInt& other);
	// bitwise
	InfInt operator&(const InfInt& other) const;
	InfInt& operator&=(const InfInt& other);
	InfInt operator|(const InfInt& other) const;
	InfInt& operator|=(const InfInt& other);
	InfInt operator^(const InfInt& other) const;
	InfInt& operator^=(const InfInt& other);
	InfInt operator<<(size_type other) const;
	InfInt& operator<<=(size_type other);
	InfInt operator>>(size_type other) const;
	InfInt& operator>>=(size_type other);
	// Static Attributes //
	static const InfInt neg_one;
	static const InfInt zero;
	static const InfInt pos_one;
protected:
	InfInt& clean(void);
	// Attributes //
	std::vector<bool> m_number;
	bool m_sign;
};

template <class T>
T InfInt::to_int(void) const {
	size_type bits_in_T = sizeof(T) * 8;
	T tmp = 0;
	for (size_type i = 0; i < bits_in_T; i++)
		tmp |= static_cast<T>(this->get(i)) << i;
	return tmp;
}

template <class T>
T InfInt::to_int_safe(void) const {
	size_type bits_in_T = sizeof(T) * 8;
	if (bits_in_T < this->size())
		throw std::overflow_error("template <class T> T InfInt::to_int_safe(void) const: Given type is too litle!");
	if (this->sign())
		if (static_cast<T>(-1) >= static_cast<T>(0))
			throw std::overflow_error("template <class T> T InfInt::to_int_safe(void) const: Given type do not have the right signess!");
	T tmp = 0;
	for (size_type i = 0; i < bits_in_T; i++)
		tmp |= static_cast<T>(this->get(i)) << i;
	return tmp;
}



// Outside the class //

InfInt operator "" _infint(unsigned long long other); // alows the use of the macro _inf to transform a unsigned long long to an InfInt
std::ostream& operator<<(std::ostream& out, const InfInt& infint);
std::istream& operator>>(std::istream& in, InfInt& infint);

#endif // INFINT_HPP