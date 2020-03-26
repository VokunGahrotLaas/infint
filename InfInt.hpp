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
	InfInt(std::string other, int base);
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
	std::string to_Bstr(void) const;
	std::string to_Bstr(size_type str_size) const;
	std::string to_str(int base) const;
	template <class T> T to_int(void) const;
	template <class T> T to_int_safe(void) const;
	// ??? //
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
	InfInt& pow(const InfInt& other);
	static InfInt pow(const InfInt& int0, const InfInt& int1);
protected:
	void clean(void);
	// Attributes //
	std::vector<bool> m_number;
	bool m_sign;
	//char padding[sizeof(void*) - (sizeof(std::vector<bool>) + sizeof(bool)) % sizeof(void*)]; // usualy 7, alows the struct to be round when used un arrays
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
			m_sign = false;
			m_number.push_back(false);
			return;
		}
		m_sign = false;
		while (other != 0) {
			m_number.push_back(static_cast<bool>(other & 1));
			other >>= 1;
		}
	}
	else {
		if (other == -1) {
			m_sign = true;
			m_number.push_back(true);
			return;
		}
		m_sign = true;
		while (other != -1) {
			m_number.push_back(static_cast<bool>(other & 1));
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
			m_sign = false;
			m_number.push_back(false);
			return;
		}
		m_sign = false;
		while (other != 0) {
			m_number.push_back(static_cast<bool>(other & 1));
			other >>= 1;
		}
	}
	else {
		if (other == -1) {
			m_sign = true;
			m_number.push_back(true);
			return;
		}
		m_sign = true;
		while (other != -1) {
			m_number.push_back(static_cast<bool>(other & 1));
			other >>= 1;
		}
	}
}

InfInt::InfInt(unsigned int other) {
	if (other == 0u) {
		m_sign = false;
		m_number.push_back(false);
		return;
	}
	m_sign = false;
	while (other != 0u) {
		m_number.push_back(static_cast<bool>(other & 1u));
		other >>= 1u;
	}
}

InfInt::InfInt(long other) {
	if (other >= 0l) {
		if (other == 0l) {
			m_sign = false;
			m_number.push_back(false);
			return;
		}
		m_sign = false;
		while (other != 0l) {
			m_number.push_back(static_cast<bool>(other & 1l));
			other >>= 1l;
		}
	}
	else {
		if (other == -1l) {
			m_sign = true;
			m_number.push_back(true);
			return;
		}
		m_sign = true;
		while (other != -1l) {
			m_number.push_back(static_cast<bool>(other & 1l));
			other >>= 1l;
		}
	}
}

InfInt::InfInt(unsigned long other) {
	if (other == 0ul) {
		m_sign = false;
		m_number.push_back(false);
		return;
	}
	m_sign = false;
	while (other != 0ul) {
		m_number.push_back(static_cast<bool>(other & 1ul));
		other >>= 1ul;
	}
}

InfInt::InfInt(long long other) {
	if (other >= 0ll) {
		if (other == 0ll) {
			m_sign = false;
			m_number.push_back(false);
			return;
		}
		m_sign = false;
		while (other != 0ll) {
			m_number.push_back(static_cast<bool>(other & 1ll));
			other >>= 1ll;
		}
	}
	else {
		if (other == -1ll) {
			m_sign = true;
			m_number.push_back(true);
			return;
		}
		m_sign = true;
		while (other != -1ll) {
			m_number.push_back(static_cast<bool>(other & 1ll));
			other >>= 1ll;
		}
	}
}

InfInt::InfInt(unsigned long long other) {
	if (other == 0ull) {
		m_sign = false;
		m_number.push_back(false);
		return;
	}
	m_sign = false;
	while (other != 0ull) {
		m_number.push_back(static_cast<bool>(other & 1ull));
		other >>= 1ull;
	}
}

InfInt::InfInt(std::string other) {
	if (other.empty()) {
		m_sign = false;
		m_number.push_back(false);
		return;
	}
	if (other.front() == '-') {
		m_sign = true;
		other.assign(other, 1, other.size());
	}
	else if (other.front() == '+') {
		m_sign = false;
		other.assign(other, 1, other.size());
	}
	else
		m_sign = false;
	m_number.reserve(other.size());
	while (other.size() > 0) {
		m_number.push_back(other.back() != '0');
		other.pop_back();
	}
	clean();
}

InfInt::~InfInt(void) {
	//
}

bool InfInt::sign(void) const {
	return m_sign;
}

bool InfInt::get(const size_type& pos) const {
	if (pos < size())
		return m_number[pos];
	else
		return m_sign;
}

typename InfInt::size_type InfInt::size(void) const {
	return m_number.size();
}

InfInt& InfInt::ones_complement(void) {
	m_sign = !sign();
	m_number.flip();
	return *this;
}

InfInt& InfInt::twos_complement(void) {
	if (*this == InfInt::zero)
		return *this;
	ones_complement();
	InfInt temp;
	temp.m_sign = sign();
	temp.m_number.resize(size() + 1, false);
	temp.m_number[1] = get(0);
	temp.m_number[0] = !get(0);
	for (size_type i = 1; i < size(); ++i) {
		temp.m_number[i + 1] = get(i) && temp.get(i);
		temp.m_number[i] = get(i) != temp.get(i);
	}
	if (!temp.m_number.back())
		temp.m_number.pop_back();
	temp.clean();
	*this = temp;
	return *this;
}

std::string InfInt::to_Bstr(void) const {
	std::string str;
	str.reserve(size());
	if (m_sign)
		str.push_back('-');
	else
		str.push_back('+');
	for (size_t i = size() - 1; i > 0; --i) {
		str.push_back('0' + get(i));
	}
	if (size() > 0) {
		str.push_back('0' + get(0));
	}
	return str;
}

std::string InfInt::to_Bstr(size_type str_size) const {
	if (str_size == 0)
		str_size = size() + 1;
	if (str_size <= size())
		throw std::logic_error("std::string InfInt::b_str(size_type str_size) const: str_size <= size()");
	std::string str;
	str.reserve(str_size);
	for (; str_size > size(); --str_size)
		str.push_back('0' + m_sign);
	for (size_t i = size() - 1; i > 0; --i) {
		str.push_back('0' + get(i));
	}
	if (size() > 0) {
		str.push_back('0' + get(0));
	}
	return str;
}

std::string InfInt::to_str(int base) const {
	if (base < 2 || base > 62)
		throw std::invalid_argument("std::string InfInt::str(int base) const: base must be beetween 2 and 62");
	std::string str;
	InfInt temp(*this);
	if (temp == InfInt::zero)
		str.push_back('0');
	if (temp.sign())
		temp.twos_complement();
	InfInt remainder;
	while (temp != InfInt::zero) {
		temp.full_div(base, temp, remainder);
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
		temp |= static_cast<T>(get(i)) << i;
	return temp;
}

template <class T>
T InfInt::to_int_safe(void) const {
	size_type bits_in_T = sizeof(T) * 8;
	if (bits_in_T < size())
		throw std::overflow_error("template <class T> T InfInt::to_int_safe(void) const: Given type is too litle!");
	if (sign())
		if (static_cast<T>(0) - static_cast<T>(1) < static_cast<T>(0))
			throw std::overflow_error("template <class T> T InfInt::to_int_safe(void) const: Given type do not have the right signess!");
	T temp = 0;
	for (size_type i = 0; i < bits_in_T; i++)
		temp |= static_cast<T>(get(i)) << i;
	return temp;
}

void InfInt::full_div(const InfInt& other, InfInt& quotient, InfInt& remainder) const {
	if (*this == InfInt::zero) {
		remainder = InfInt::zero;
		quotient = InfInt::zero;
		return;
	}
	if (other == InfInt::zero) {
		throw std::invalid_argument("void InfInt::full_div(const InfInt& other, InfInt& quotient, InfInt& remainder) const: Cannot divide by 0");
	}
	if (other == InfInt::pos_one) {
		remainder = InfInt::zero;
		quotient = *this;
		return;
	}
	if (other == InfInt::neg_one) {
		remainder = InfInt::zero;
		quotient = -*this;
		return;
	}
	if (other.size() > this->size()) {
		remainder = *this;
		quotient = InfInt::zero;
		return;
	}

	InfInt q(InfInt::zero);
	InfInt a(*this);
	if (a.sign())
		a.twos_complement();
	InfInt b(other);
	if (b.sign())
		b.twos_complement();

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
	if (sign() != other.sign()) {
		remainder.twos_complement();
		quotient.twos_complement();
	}
}

InfInt& InfInt::operator=(const InfInt& other) {
	m_sign = other.sign();
	m_number = other.m_number;
	return *this;
}

bool InfInt::operator==(const InfInt& other) const {
	if (size() != other.size())
		return false;
	if (sign() != other.sign())
		return false;
	for (unsigned long long i = 0; i < size(); ++i)
		if (m_number[i] != other.get(i))
			return false;
	return true;
}

bool InfInt::operator!=(const InfInt& other) const {
	return !(*this == other);
}

bool InfInt::operator>(const InfInt& other) const {
	if (!sign() && other.sign())
		return true;
	if (sign() && !other.sign())
		return false;
	if (size() > other.size())
		return !sign();
	if (size() < other.size())
		return sign();
	if (size() > 1) {
		for (size_type i = size() - 2; i > 0; --i) {
			if (get(i) == other.get(i))
				continue;
			return get(i);
		}
	}
	if (size() != 0)
		return get(0) != other.get(0) && get(0);
	return false;
}

bool InfInt::operator<=(const InfInt& other) const {
	return !(*this > other);
}

bool InfInt::operator<(const InfInt& other) const {
	if (sign() && !other.sign())
		return true;
	if (!sign() && other.sign())
		return false;
	if (size() < other.size())
		return !sign();
	if (size() > other.size())
		return sign();
	if (size() > 1) {
		for (size_type i = size() - 2; i > 0; --i) {
			if (get(i) == other.get(i))
				continue;
			return other.get(i);
		}
	}
	if (size() != 0)
		return get(0) != other.get(0) && other.get(0);
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
	if (!sign() && !other.sign()) { // both positive
		size_type max_size;
		if (m_number.size() < other.m_number.size())
			max_size = other.size();
		else
			max_size = size();
		InfInt temp;
		temp.m_number.resize(max_size + 1, false);
		for (size_type i = 0; i < max_size; ++i) {
			temp.m_number[i + 1] = ((get(i) != other.get(i)) && temp.get(i)) || (get(i) && other.get(i));
			temp.m_number[i] = (get(i) != other.get(i)) != temp.get(i);
		}
		temp.clean();
		return temp;
	}
	if (!sign() && other.sign()) { // only *this is positive
		size_type max_size;
		if (m_number.size() < other.m_number.size())
			max_size = other.size();
		else
			max_size = size();
		InfInt temp;
		temp.m_number.resize(max_size + 1, false);
		for (size_type i = 0; i < max_size; ++i) {
			temp.m_number[i + 1] = ((get(i) != other.get(i)) && temp.get(i)) || (get(i) && other.get(i));
			temp.m_number[i] = (get(i) != other.get(i)) != temp.get(i);
		}
		if (!temp.m_number.back())
			temp.twos_complement();
		temp.m_number.pop_back();
		temp.clean();
		return temp;
	}
	if (sign() && !other.sign()) { // only other is positive
		return other + *this;
	}
	else { // both are negative
		return -(-*this + -other);
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
	-- (*this);
	return return_val;
}

InfInt InfInt::operator*(const InfInt& other) const {
	if (other.size() < size())
		return other * (*this);
	InfInt temp;
	InfInt a(*this);
	if (a.sign())
		a.twos_complement();
	InfInt b(other);
	if (b.sign())
		b.twos_complement();
	for (size_type i = 0; i < a.size(); ++i)
		if (a.get(i))
			temp += b << i;
	if (sign() != other.sign())
		temp.twos_complement();
	return temp;
}

InfInt& InfInt::operator*=(const InfInt& other) {
	*this = (*this) * other;
	return *this;
}

InfInt InfInt::operator/(const InfInt& other) const {
	if (*this == InfInt::zero)
		return InfInt::zero;
	if (other == InfInt::zero)
		throw std::invalid_argument("InfInt InfInt::operator/(const InfInt& other) const: Cannot divide by 0");
	if (other == InfInt::pos_one)
		return *this;
	if (other == InfInt::neg_one)
		return -(*this);
	if (other.size() > this->size())
		return InfInt::zero;
	InfInt q;
	InfInt a(*this);
	if (a.sign())
		a.twos_complement();
	InfInt b(other);
	if (b.sign())
		b.twos_complement();
	
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

	if (sign() != other.sign())
		q.twos_complement();
	return q;
}

InfInt& InfInt::operator/=(const InfInt& other) {
	*this = *this / other;
	return *this;
}

InfInt InfInt::operator%(const InfInt& other) const {
	if (*this == InfInt::zero)
		return InfInt::zero;
	if (other == InfInt::zero)
		throw std::invalid_argument("InfInt InfInt::operator%(const InfInt& other) const: Cannot divide by 0");
	if (other == InfInt::pos_one)
		return InfInt::zero;
	if (other == InfInt::neg_one)
		return InfInt::zero;
	if (other.size() > this->size())
		return *this;
	InfInt a(*this);
	if (a.sign())
		a.twos_complement();
	InfInt b(other);
	if (b.sign())
		b.twos_complement();

	size_type size_diff = a.size() - b.size();
	b <<= size_diff;
	while (a >= other) {
		while (a < b)
			b >>= 1;
		a -= b;
		b >>= b.size() - a.size();
	}

	if (sign() != other.sign())
		a.twos_complement();
	return a;
}

InfInt& InfInt::operator%=(const InfInt& other) {
	*this = *this % other;
	return *this;
}

InfInt InfInt::operator&(const InfInt& other) const {
	size_type max_size = 1;
	if (size() < other.size())
		max_size = other.size();
	else
		max_size = size();
	InfInt temp;
	temp.m_sign = sign() && other.sign();
	temp.m_number.resize(max_size, temp.sign());
	for (size_type i = 0; i < max_size; ++i)
		temp.m_number[i] = get(i) && other.get(i);
	temp.clean();
	return temp;
}

InfInt& InfInt::operator&=(const InfInt& other) {
	*this = *this & other;
	return *this;
}

InfInt InfInt::operator|(const InfInt& other) const {
	size_type max_size;
	if (size() < other.size())
		max_size = other.size();
	else
		max_size = size();
	InfInt temp;
	temp.m_sign = sign() || other.sign();
	temp.m_number.resize(max_size, temp.sign());
	for (size_type i = 0; i < max_size; ++i)
		temp.m_number[i] = get(i) || other.get(i);
	temp.clean();
	return temp;
}

InfInt& InfInt::operator|=(const InfInt& other) {
	*this = *this | other;
	return *this;
}

InfInt InfInt::operator^(const InfInt& other) const {
	size_type max_size;
	if (size() < other.size())
		max_size = other.size();
	else
		max_size = size();
	InfInt temp;
	temp.m_sign = sign() != other.sign();
	temp.m_number.resize(max_size, temp.sign());
	for (size_type i = 0; i < max_size; ++i)
		temp.m_number[i] = get(i) != other.get(i);
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
	m_number.insert(m_number.begin(), other, false);
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
	if (other < size())
		m_number.erase(m_number.begin(), m_number.begin() + static_cast<long long>(other));
	else
		m_number.erase(m_number.begin(), m_number.begin() + static_cast<long long>(size() - 1));
	clean();
	return *this;
}

InfInt& InfInt::pow(const InfInt& other) {
	if (other == 0) {
		if (*this == 0)
			throw std::exception("Division by zero");
		*this = 1;
		return *this;
	}
	if (other < 0) {
		if (*this == 0)
			throw std::exception("Division by zero");
		*this = 0;
		return *this;
	}
	InfInt tmp(*this);
	for (InfInt i = other; i > 1; --i)
		*this *= tmp;
	return *this;
}

InfInt InfInt::pow(const InfInt& int0, const InfInt& int1) {
	InfInt tmp(int0);
	return tmp.pow(int1);
}

void InfInt::clean(void) {
	while (size() > 1 && m_number.back() == m_sign)
		m_number.pop_back();
	if (size() == 0)
		m_number.push_back(m_sign);
}

InfInt const InfInt::neg_one(-1);
InfInt const InfInt::zero(0);
InfInt const InfInt::pos_one(1);

// Outside the class //

InfInt operator "" _i(unsigned long long other) { // alows the use of the macro _i to transform a unsigned long long to an InfInt
	return static_cast<InfInt>(other);
}

// output .to_Bstr() to an ostream for convenience and readability
// bad code, strores in string before sending to stream, should directly send to stream
std::ostream& operator<<(std::ostream& out, const InfInt& integer) {
	out << integer.to_str(10);
	return out;
}

#endif /* INFINT_HPP */