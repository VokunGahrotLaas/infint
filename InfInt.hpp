/* README.md
# InfInt

## Desc
 C++ library for infinit integers.\
 __Vers:__ 1.3

## Auth
 * [Maxence MICHOT](https://github.com/VokunGahrotLaas)

## Stuff it does
 * Numbers are stored as binary in std::vector<bool>, it as the adventage of using as few storage as posible
 * Bitwise operators as &, |, ^, << and >> are implemented
 * Comparaison operator as ==, !=, >, <=, < and >= are implemented
 * Basic operation are obviusly permited +, -, *, / and %
 * Those things are in too +=, -=, *=, /=, %=, &=, |=, ^=, <<= and >>=
 * Incrementation and decrementation operators are implemented in postfix and prefix
 * .size() returns the number of bits the number is composed of
 * .get(pos) returns the bool in the number at pos or .sign() if pos >= .size()
 * .sign() returns, well... the sign of the number
 * .Bstr() returns a std::string representing the memory
 * .Bstr(str_size) same as .Bstr() but add bits until the string is at least str_size long
 * .str(int base) give out a std::string starting with '+' or '-' and ending with the number in the given base from 2 to 62, base 2 will not reflect memory sush as in .to_Bstr()
 * 255_inf is equivalent to InfInt(255) just like 255l is equivalent to long(255)
 * Overloaded operator << for ostream, example cout << 5_inf << endl; outputs: "+101\n"
 * You can static_cast<InfInt>(x) or (InfInt)x or InfInt(x) or whatever from these types:
   * c++ char (char)
   * c++ integers (int, long long, unsigned long long, etc...)
   * c++ string (std::string)
 * Cast from std::string have some rules:
   * If the string doesn't starts with '+' or '-' the number will be assumed to be positive
   * Any char other than '0' will be considered as '1' (except for the first char who can also be '+' or '-'), exemple: InfInt("10+3") == InfInt(0b1011) == InfInt(11)
   * Numbers will be assumed to be signed binary, exemple: InfInt("+101") == InfInt("101") == -InfInt("-011")
 * The same rules applies to the output of .to_Bstr()
 * added {void InfInt::full_div(divisor, remainder, quotient) const} that calculate the remainder and the quotient in one execution
 * added consts InfInt::neg_one, InfInt::zero and InfInt::pos_one, the most useful is InfInt::zero wich is used very often, this alows one allocation for multiple uses
 * re-done operator* (faster algorithm)
 * re-done operator/, operator% and full_div (faster algorithm)
 * Cast from std::string with base:
   * Same format as {void InfInt::to_str(int base)}
   * Base between 2 and 62 included
   * The '+' sign can be implicite
   * Any thing other than the sign or a digit under base will be 0
 * Added {InfInt& InfInt::full_div(divisor, remainder)} use (*this) as quotient
 * All not const operators return a reference to self
 * pow is now using binary exponentiation, went from O(n) to O(log2(n))
 * added modpow(a, b, m), return a ** b % m
 * added istream in addition to ostream (input / output)
 * put math in InfIntMath
 */

#ifndef INFINT_HPP
#define INFINT_HPP

// std libs
#include <iostream> // std::ostream and std::string
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
	~InfInt(void); // empty
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
	template <class T> T to_int(void) const;
	template <class T> T to_int_safe(void) const;
	// 2 in 1 operator //
	static InfIntFullDivResult full_div(const InfInt& a, const InfInt& b);
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
	void clean(void);
	// Attributes //
	std::vector<bool> m_number;
	bool m_sign;
};



// Outside the class //

InfInt operator "" _inf(unsigned long long other); // alows the use of the macro _inf to transform a unsigned long long to an InfInt
std::ostream & operator<<(std::ostream & out, const InfInt & infint);
std::istream& operator>>(std::istream& in, InfInt& infint);

#endif // INFINT_HPP