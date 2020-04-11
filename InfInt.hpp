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
 * 255_i is equivalent to InfInt(255) just like 255l is equivalent to long(255)
 * Overloaded operator << for ostream, example cout << 5_i << endl; outputs: "+101\n"
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
 */

#ifndef INFINT_HPP
#define INFINT_HPP

// C++ libs
#include <iostream> // std::ostream and std::string
#include <algorithm> // std::reverse() (reverse std::string, I was too lazy to do it myself...)
#include <vector> // std::vector<bool> for memory friendly data

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
	InfInt& full_div(const InfInt& other, InfInt& remainder);
	void full_div(const InfInt& other, InfInt& remainder, InfInt& quotient) const;
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
	// pow
	static InfInt pow(const InfInt& _a, const InfInt& _b);
	static InfInt modpow(const InfInt& _a, const InfInt& _b, const InfInt& m);
	// abs
	InfInt& abs(void);
	static InfInt abs(const InfInt& infint);
protected:
	void clean(void);
	// Attributes //
	std::vector<bool> m_number;
	bool m_sign;
	//char padding[sizeof(void*) - (sizeof(std::vector<bool>) + sizeof(bool)) % sizeof(void*)]; // usualy 7, alows the struct to be round when used in an arrays
	// Static Attributes //
	static const InfInt neg_one;
	static const InfInt zero;
	static const InfInt pos_one;
};

InfInt::InfInt(void) :
	m_number({ false }),
	m_sign(false)
{
	//
}

InfInt::InfInt(char other) {
	if (other >= 0) {
		if (other == 0) {
			this->m_sign = false;
			this->m_number.push_back(false);
			return;
		}
		this->m_sign = false;
		while (other != 0) {
			this->m_number.push_back(static_cast<bool>(other & 1));
			other >>= 1;
		}
	} else {
		if (other == -1) {
			this->m_sign = true;
			this->m_number.push_back(true);
			return;
		}
		this->m_sign = true;
		while (other != -1) {
			this->m_number.push_back(static_cast<bool>(other & 1));
			other >>= 1;
		}
		twos_complement();
		*this += InfInt(128);
	}
}

InfInt::InfInt(const InfInt& other) :
	m_number(other.m_number),
	m_sign(other.m_sign)
{
	//
}

InfInt::InfInt(int other) {
	if (other >= 0) {
		if (other == 0) {
			this->m_sign = false;
			this->m_number.push_back(false);
			return;
		}
		this->m_sign = false;
		while (other != 0) {
			this->m_number.push_back(static_cast<bool>(other & 1));
			other >>= 1;
		}
	} else {
		if (other == -1) {
			this->m_sign = true;
			this->m_number.push_back(true);
			return;
		}
		this->m_sign = true;
		while (other != -1) {
			this->m_number.push_back(static_cast<bool>(other & 1));
			other >>= 1;
		}
	}
}

InfInt::InfInt(unsigned int other) {
	if (other == 0u) {
		this->m_sign = false;
		this->m_number.push_back(false);
		return;
	}
	this->m_sign = false;
	while (other != 0u) {
		this->m_number.push_back(static_cast<bool>(other & 1u));
		other >>= 1u;
	}
}

InfInt::InfInt(long other) {
	if (other >= 0l) {
		if (other == 0l) {
			this->m_sign = false;
			this->m_number.push_back(false);
			return;
		}
		this->m_sign = false;
		while (other != 0l) {
			this->m_number.push_back(static_cast<bool>(other & 1l));
			other >>= 1l;
		}
	} else {
		if (other == -1l) {
			this->m_sign = true;
			this->m_number.push_back(true);
			return;
		}
		this->m_sign = true;
		while (other != -1l) {
			this->m_number.push_back(static_cast<bool>(other & 1l));
			other >>= 1l;
		}
	}
}

InfInt::InfInt(unsigned long other) {
	if (other == 0ul) {
		this->m_sign = false;
		this->m_number.push_back(false);
		return;
	}
	this->m_sign = false;
	while (other != 0ul) {
		this->m_number.push_back(static_cast<bool>(other & 1ul));
		other >>= 1ul;
	}
}

InfInt::InfInt(long long other) {
	if (other >= 0ll) {
		if (other == 0ll) {
			this->m_sign = false;
			this->m_number.push_back(false);
			return;
		}
		this->m_sign = false;
		while (other != 0ll) {
			this->m_number.push_back(static_cast<bool>(other & 1ll));
			other >>= 1ll;
		}
	} else {
		if (other == -1ll) {
			this->m_sign = true;
			this->m_number.push_back(true);
			return;
		}
		this->m_sign = true;
		while (other != -1ll) {
			this->m_number.push_back(static_cast<bool>(other & 1ll));
			other >>= 1ll;
		}
	}
}

InfInt::InfInt(unsigned long long other) {
	if (other == 0ull) {
		this->m_sign = false;
		this->m_number.push_back(false);
		return;
	}
	this->m_sign = false;
	while (other != 0ull) {
		this->m_number.push_back(static_cast<bool>(other & 1ull));
		other >>= 1ull;
	}
}

InfInt::InfInt(std::string other) {
	if (other.empty()) {
		this->m_sign = false;
		this->m_number.push_back(false);
		return;
	} if (other.front() == '-') {
		this->m_sign = true;
		other.assign(other, 1, other.size());
	} else if (other.front() == '+') {
		this->m_sign = false;
		other.assign(other, 1, other.size());
	} else
		this->m_sign = false;
	this->m_number.reserve(other.size());
	while (other.size() > 0) {
		this->m_number.push_back(other.back() != '0');
		other.pop_back();
	}
	this->clean();
}

InfInt::InfInt(std::string other, int base) {
	if (base < 2 || base > 62)
		throw std::invalid_argument("InfInt::InfInt(std::string other, int base): base must be beetween 2 and 62");
	if (other.empty()) {
		this->m_sign = false;
		this->m_number.push_back(false);
		return;
	}
	bool sign = false;
	if (other.front() == '-') {
		sign = true;
		other.assign(other, 1, other.size());
	} else if (other.front() == '+') {
		sign = false;
		other.assign(other, 1, other.size());
	}
	this->m_sign = false;
	this->m_number.push_back(false);
	InfInt p = InfInt::pos_one;
	InfInt infint_base = base;
	while (other.size() > 0) {
		unsigned char c = other.back();
		if ('0' <= c && c <= '9')
			c -= '0';
		else if ('a' <= c && c <= 'z')
			c -= 'a' - 10;
		else if ('A' <= c && c <= 'Z')
			c -= 'A' - 36;
		if (c < base)
			*this += InfInt(c) * p;
		other.pop_back();
		p *= infint_base;
	}
	this->clean();
	if (sign)
		this->twos_complement();
}

InfInt::~InfInt(void) {
	//
}

bool InfInt::sign(void) const {
	return this->m_sign;
}

bool InfInt::get(const size_type& pos) const {
	if (pos < this->size())
		return this->m_number[pos];
	else
		return this->m_sign;
}

typename InfInt::size_type InfInt::size(void) const {
	return this->m_number.size();
}

InfInt& InfInt::ones_complement(void) {
	this->m_sign = !sign();
	this->m_number.flip();
	return *this;
}

InfInt& InfInt::twos_complement(void) {
	if (*this == InfInt::zero)
		return *this;
	this->ones_complement();
	InfInt temp;
	temp.m_sign = this->sign();
	temp.m_number.resize(this->size() + 1, false);
	temp.m_number[1] = this->get(0);
	temp.m_number[0] = !this->get(0);
	for (size_type i = 1; i < this->size(); ++i) {
		temp.m_number[i + 1] = this->get(i) && temp.get(i);
		temp.m_number[i] = this->get(i) != temp.get(i);
	}
	if (!temp.m_number.back())
		temp.m_number.pop_back();
	temp.clean();
	*this = temp;
	return *this;
}

std::string InfInt::Bstr(void) const {
	std::string str;
	str.reserve(this->size());
	if (this->m_sign)
		str.push_back('-');
	else
		str.push_back('+');
	for (size_t i = size() - 1; i > 0; --i) {
		str.push_back('0' + this->get(i));
	}
	if (this->size() > 0) {
		str.push_back('0' + this->get(0));
	}
	return str;
}

std::string InfInt::Bstr(size_type str_size) const {
	if (str_size == 0)
		str_size = this->size() + 1;
	if (str_size <= this->size())
		throw std::logic_error("std::string InfInt::b_str(size_type str_size) const: str_size <= size()");
	std::string str;
	str.reserve(str_size);
	for (; str_size > this->size(); --str_size)
		str.push_back('0' + this->m_sign);
	for (size_t i = this->size() - 1; i > 0; --i) {
		str.push_back('0' + get(i));
	}
	if (this->size() > 0) {
		str.push_back('0' + get(0));
	}
	return str;
}

std::string InfInt::str(int base) const {
	if (base < 2 || base > 62)
		throw std::invalid_argument("std::string InfInt::str(int base) const: base must be beetween 2 and 62");
	std::string str;
	InfInt temp(*this);
	if (temp == InfInt::zero)
		str.push_back('0');
	if (temp.sign())
		temp.twos_complement();
	InfInt remainder;
	InfInt infint_base(base);
	while (temp != InfInt::zero) {
		temp.full_div(infint_base, remainder);
		if (remainder < 10)
			str.push_back('0' + remainder.to_int<char>());
		else if (remainder < 36)
			str.push_back('a' + remainder.to_int<char>() - 10);
		else
			str.push_back('A' + remainder.to_int<char>() - 36);
	}
	if (sign())
		str.push_back('-');
	else
		str.push_back('+');
	std::reverse(str.begin(), str.end());
	return str;
}

template <class T>
T InfInt::to_int(void) const {
	size_type bits_in_T = sizeof(T) * 8;
	T temp = 0;
	for (size_type i = 0; i < bits_in_T; i++)
		temp |= static_cast<T>(this->get(i)) << i;
	return temp;
}

template <class T>
T InfInt::to_int_safe(void) const {
	size_type bits_in_T = sizeof(T) * 8;
	if (bits_in_T < this->size())
		throw std::overflow_error("template <class T> T InfInt::to_int_safe(void) const: Given type is too litle!");
	if (this->sign())
		if (static_cast<T>(0) - static_cast<T>(1) < static_cast<T>(0))
			throw std::overflow_error("template <class T> T InfInt::to_int_safe(void) const: Given type do not have the right signess!");
	T temp = 0;
	for (size_type i = 0; i < bits_in_T; i++)
		temp |= static_cast<T>(this->get(i)) << i;
	return temp;
}

InfInt& InfInt::full_div(const InfInt& other, InfInt& remainder) {
	if (other == InfInt::zero)
		throw std::invalid_argument("InfInt& InfInt::full_div(const InfInt& other, InfInt& remainder): Cannot divide by 0");

	InfInt q;
	bool sign = this->sign();
	this->abs();
	InfInt b(InfInt::abs(other));

	if (b >= (*this)) {
		if (b == (*this)) {
			*this = InfInt::zero;
			remainder = InfInt::pos_one;
		} else {
			if (this->sign() != other.sign())
				this->twos_complement();
			remainder = *this;
			*this = InfInt::zero;
		}
		return *this;
	}

	size_type size_diff = this->size() - b.size();
	InfInt mask = InfInt::pos_one << size_diff;
	b <<= size_diff;
	while ((*this) >= other) {
		while ((*this) < b) {
			mask >>= 1;
			b >>= 1;
		}
		*this -= b;
		q |= mask;
		mask >>= b.size() - this->size();
		b >>= b.size() - this->size();
	}

	remainder = *this;
	*this = q;
	if (sign != other.sign()) {
		this->twos_complement();
		remainder.twos_complement();
	}
	return *this;
}

void InfInt::full_div(const InfInt& other, InfInt& remainder, InfInt& quotient) const {
	if (other == InfInt::zero)
		throw std::invalid_argument("void InfInt::full_div(const InfInt& other, InfInt& remainder, InfInt& quotient) const: Cannot divide by 0");

	InfInt q;
	InfInt a(InfInt::abs(*this));
	InfInt b(InfInt::abs(other));

	if (b >= a) {
		if (b == a) {
			remainder = InfInt::zero;
			quotient = InfInt::pos_one;
		} else {
			if (this->sign() != other.sign())
				a.twos_complement();
			remainder = a;
			quotient = InfInt::zero;
		}
		return;
	}

	size_type size_diff = a.size() - b.size();
	InfInt mask = InfInt::pos_one << size_diff;
	b <<= size_diff;
	while (a >= other) {
		while (a < b) {
			mask >>= 1;
			b >>= 1;
		}
		a -= b;
		q |= mask;
		mask >>= b.size() - a.size();
		b >>= b.size() - a.size();
	}

	remainder = a;
	quotient = q;
	if (this->sign() != other.sign()) {
		remainder.twos_complement();
		quotient.twos_complement();
	}
}

InfInt& InfInt::operator=(const InfInt& other) {
	this->m_sign = other.sign();
	this->m_number = other.m_number;
	return *this;
}

bool InfInt::operator==(const InfInt& other) const {
	if (this->size() != other.size())
		return false;
	if (this->sign() != other.sign())
		return false;
	for (unsigned long long i = 0; i < this->size(); ++i)
		if (this->m_number[i] != other.get(i))
			return false;
	return true;
}

bool InfInt::operator!=(const InfInt& other) const {
	return !(*this == other);
}

bool InfInt::operator>(const InfInt& other) const {
	if (!this->sign() && other.sign())
		return true;
	if (this->sign() && !other.sign())
		return false;
	if (this->size() > other.size())
		return !this->sign();
	if (this->size() < other.size())
		return this->sign();
	if (this->size() > 1) {
		for (size_type i = this->size() - 2; i > 0; --i) {
			if (this->get(i) == other.get(i))
				continue;
			return this->get(i);
		}
	}
	if (this->size() != 0)
		return this->get(0) != other.get(0) && this->get(0);
	return false;
}

bool InfInt::operator<=(const InfInt& other) const {
	return !(*this > other);
}

bool InfInt::operator<(const InfInt& other) const {
	if (this->sign() && !other.sign())
		return true;
	if (!this->sign() && other.sign())
		return false;
	if (this->size() < other.size())
		return !this->sign();
	if (this->size() > other.size())
		return this->sign();
	if (this->size() > 1) {
		for (size_type i = this->size() - 2; i > 0; --i) {
			if (this->get(i) == other.get(i))
				continue;
			return other.get(i);
		}
	}
	if (this->size() != 0)
		return this->get(0) != other.get(0) && other.get(0);
	return false;
}

bool InfInt::operator>=(const InfInt& other) const {
	return !(*this < other);
}

InfInt InfInt::operator+(void) const {
	return *this;
}

InfInt InfInt::operator-(void) const {
	InfInt temp(*this);
	temp.twos_complement();
	return temp;
}

InfInt InfInt::operator+(const InfInt& other) const {
	if (!this->sign() && !other.sign()) { // both positive
		size_type max_size;
		if (this->m_number.size() < other.m_number.size())
			max_size = other.size();
		else
			max_size = this->size();
		InfInt temp;
		temp.m_number.resize(max_size + 1, false);
		for (size_type i = 0; i < max_size; ++i) {
			temp.m_number[i + 1] = ((this->get(i) != other.get(i)) && temp.get(i)) || (this->get(i) && other.get(i));
			temp.m_number[i] = (this->get(i) != other.get(i)) != temp.get(i);
		}
		temp.clean();
		return temp;
	}
	if (!this->sign() && other.sign()) { // only *this is positive
		size_type max_size;
		if (this->m_number.size() < other.m_number.size())
			max_size = other.size();
		else
			max_size = this->size();
		InfInt temp;
		temp.m_number.resize(max_size + 1, false);
		for (size_type i = 0; i < max_size; ++i) {
			temp.m_number[i + 1] = ((this->get(i) != other.get(i)) && temp.get(i)) || (this->get(i) && other.get(i));
			temp.m_number[i] = (this->get(i) != other.get(i)) != temp.get(i);
		}
		if (!temp.m_number.back())
			temp.twos_complement();
		temp.m_number.pop_back();
		temp.clean();
		return temp;
	}
	if (this->sign() && !other.sign()) { // only other is positive
		return other + *this;
	} else { // both are negative
		return -(-(*this) + -other);
	}
}

InfInt& InfInt::operator+=(const InfInt& other) {
	*this = *this + other;
	return *this;
}

InfInt& InfInt::operator++(void) {
	*this += InfInt::pos_one;
	return *this;
}

InfInt InfInt::operator++(int) {
	InfInt return_val(*this);
	++(*this);
	return return_val;
}

InfInt InfInt::operator-(const InfInt& other) const {
	return (*this) + (-other);
}

InfInt& InfInt::operator-=(const InfInt& other) {
	*this = (*this) - other;
	return *this;
}

InfInt& InfInt::operator--(void) {
	*this -= InfInt::pos_one;
	return *this;
}

InfInt InfInt::operator--(int) {
	InfInt return_val(*this);
	--(*this);
	return return_val;
}

InfInt InfInt::operator*(const InfInt& other) const {
	if (other.size() < this->size())
		return other * (*this);
	InfInt temp;
	InfInt a(InfInt::abs(*this));
	InfInt b(InfInt::abs(other));
	for (size_type i = 0; i < a.size(); ++i)
		if (a.get(i))
			temp += b << i;
	if (this->sign() != other.sign())
		temp.twos_complement();
	return temp;
}

InfInt& InfInt::operator*=(const InfInt& other) {
	*this = (*this) * other;
	return *this;
}

InfInt InfInt::operator/(const InfInt& other) const {
	if (other == InfInt::zero)
		throw std::invalid_argument("InfInt InfInt::operator/(const InfInt& other) const: Cannot divide by 0");

	InfInt q;
	InfInt a = InfInt::abs(*this);
	InfInt abs_other = InfInt::abs(other);
	InfInt b = abs_other;

	if (b >= a) {
		if (b == a)
			return InfInt::pos_one;
		else
			return InfInt::zero;
	}

	size_type size_diff = a.size() - b.size();
	InfInt mask = InfInt::pos_one << size_diff;
	b <<= size_diff;
	while (a >= abs_other) {
		while (a < b) {
			mask >>= 1;
			b >>= 1;
		}
		a -= b;
		q |= mask;
		mask >>= b.size() - a.size();
		b >>= b.size() - a.size();
	}

	if (this->sign() != other.sign())
		q.twos_complement();
	return q;
}

InfInt& InfInt::operator/=(const InfInt& other) {
	*this = *this / other;
	return *this;
}

InfInt InfInt::operator%(const InfInt& other) const {
	if (other == InfInt::zero)
		throw std::invalid_argument("InfInt InfInt::operator%(const InfInt& other) const: Cannot divide by 0");

	InfInt a(InfInt::abs(*this));
	InfInt b(InfInt::abs(other));

	if (b >= a) {
		if (b == a)
			return InfInt::zero;
		else {
			if (sign() != other.sign())
				a.twos_complement();
			return a;
		}
	}

	size_type size_diff = a.size() - b.size();
	b <<= size_diff;
	while (a >= other) {
		while (a < b)
			b >>= 1;
		a -= b;
		b >>= b.size() - a.size();
	}

	if (this->sign() != other.sign())
		a.twos_complement();
	return a;
}

InfInt& InfInt::operator%=(const InfInt& other) {
	*this = *this % other;
	return *this;
}

InfInt InfInt::operator&(const InfInt& other) const {
	size_type max_size = 1;
	if (this->size() < other.size())
		max_size = other.size();
	else
		max_size = this->size();
	InfInt temp;
	temp.m_sign = this->sign() && other.sign();
	temp.m_number.resize(max_size, temp.sign());
	for (size_type i = 0; i < max_size; ++i)
		temp.m_number[i] = this->get(i) && other.get(i);
	temp.clean();
	return temp;
}

InfInt& InfInt::operator&=(const InfInt& other) {
	*this = (*this) & other;
	return *this;
}

InfInt InfInt::operator|(const InfInt& other) const {
	size_type max_size;
	if (this->size() < other.size())
		max_size = other.size();
	else
		max_size = this->size();
	InfInt temp;
	temp.m_sign = this->sign() || other.sign();
	temp.m_number.resize(max_size, temp.sign());
	for (size_type i = 0; i < max_size; ++i)
		temp.m_number[i] = this->get(i) || other.get(i);
	temp.clean();
	return temp;
}

InfInt& InfInt::operator|=(const InfInt& other) {
	*this = *this | other;
	return *this;
}

InfInt InfInt::operator^(const InfInt& other) const {
	size_type max_size;
	if (this->size() < other.size())
		max_size = other.size();
	else
		max_size = this->size();
	InfInt temp;
	temp.m_sign = this->sign() != other.sign();
	temp.m_number.resize(max_size, temp.sign());
	for (size_type i = 0; i < max_size; ++i)
		temp.m_number[i] = this->get(i) != other.get(i);
	temp.clean();
	return temp;
}

InfInt& InfInt::operator^=(const InfInt& other) {
	*this = *this ^ other;
	return *this;
}

InfInt InfInt::operator<<(size_type other) const {
	if (other == 0)
		return *this;
	InfInt temp(*this);
	temp.m_number.insert(temp.m_number.begin(), other, false);
	return temp;
}

InfInt& InfInt::operator<<=(size_type other) {
	if (other == 0)
		return *this;
	this->m_number.insert(this->m_number.begin(), other, false);
	return *this;
}

InfInt InfInt::operator>>(size_type other) const {
	if (other == 0)
		return *this;
	InfInt temp(*this);
	if (other < size())
		temp.m_number.erase(temp.m_number.begin(), temp.m_number.begin() + static_cast<long long>(other));
	else
		temp.m_number.erase(temp.m_number.begin(), temp.m_number.begin() + static_cast<long long>(size() - 1));
	temp.clean();
	return temp;
}

InfInt& InfInt::operator>>=(size_type other) {
	if (other == 0)
		return *this;
	if (other < this->size())
		this->m_number.erase(this->m_number.begin(), this->m_number.begin() + static_cast<long long>(other));
	else
		this->m_number.erase(this->m_number.begin(), this->m_number.begin() + static_cast<long long>(this->size() - 1));
	this->clean();
	return *this;
}

InfInt InfInt::pow(const InfInt& _a, const InfInt& _b) {
	if (_b == InfInt::zero) {
		if (_a == InfInt::zero)
			throw std::exception("InfInt InfInt::pow(const InfInt& _a, const InfInt& _b): Division by zero");
		return InfInt::pos_one;
	}
	if (_b < InfInt::zero) {
		if (_a == InfInt::zero)
			throw std::exception("InfInt InfInt::pow(const InfInt& _a, const InfInt& _b): Division by zero");
		return InfInt::zero;
	}

	InfInt a(_a);
	InfInt b(_b);
	InfInt r(InfInt::pos_one);

	while (b.size() != 1) {
		if (b.get(0))
			r *= a;
		a *= a;
		b >>= 1;
	}
	if (b.get(0))
		r *= a;

	return r;
}

InfInt InfInt::modpow(const InfInt& _a, const InfInt& _b, const InfInt& m) {
	if (_b == InfInt::zero) {
		if (_a == InfInt::zero)
			throw std::exception("InfInt InfInt::modpow(const InfInt& _a, const InfInt& _b, const InfInt& m): Division by zero");
		return InfInt::pos_one;
	}
	if (_b < InfInt::zero) {
		if (_a == InfInt::zero)
			throw std::exception("InfInt InfInt::modpow(const InfInt& _a, const InfInt& _b, const InfInt& m): Division by zero");
		return InfInt::zero;
	}

	InfInt a(_a);
	InfInt b(_b);
	InfInt r(InfInt::pos_one);

	while (b.size() != 1) {
		if (b.get(0))
			r = r * a % m;
		a = a * a % m;
		b >>= 1;
	}
	if (b.get(0))
		r = r * a % m;

	return r;
}

InfInt& InfInt::abs(void) {
	if (this->sign())
		this->twos_complement();
	return *this;
}

InfInt InfInt::abs(const InfInt& infint) {
	InfInt tmp(infint);
	tmp.abs();
	return tmp;
}

void InfInt::clean(void) {
	while (this->size() > 1 && this->m_number.back() == this->m_sign)
		this->m_number.pop_back();
	if (this->size() == 0)
		this->m_number.push_back(this->m_sign);
}

InfInt const InfInt::neg_one(-1);
InfInt const InfInt::zero(0);
InfInt const InfInt::pos_one(1);

// Outside the class //

InfInt operator "" _i(unsigned long long other) { // alows the use of the macro _i to transform a unsigned long long to an InfInt
	return static_cast<InfInt>(other);
}

// output .to_str(10) to an ostream for convenience and readability
// bad code, strores in string before sending to stream, should directly send to stream
std::ostream& operator<<(std::ostream& out, const InfInt& infint) {
	out << infint.str(10);
	return out;
}

#endif /* INFINT_HPP */