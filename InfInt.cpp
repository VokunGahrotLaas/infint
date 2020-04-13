#include "InfInt.hpp"

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
		auto result = InfInt::full_div(temp, infint_base);
		temp = result.quotient();
		remainder = result.remainder();
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

InfIntFullDivResult InfInt::full_div(const InfInt& _a, const InfInt& _b) {
	if (_b == InfInt::zero)
		throw std::invalid_argument("static InfIntFulldivResult InfInt::full_div(const InfInt& _a, const InfInt& _b): Cannot divide by 0");

	InfInt q;
	InfInt a(_a);
	if (a.sign())
		a.twos_complement();
	InfInt b(_b);
	if (b.sign())
		b.twos_complement();

	if (b >= a) {
		InfInt remainder, quotient;
		if (b == a) {
			quotient = InfInt::pos_one;
		} else {
			if (_a.sign() != _b.sign())
				a.twos_complement();
			remainder = a;
		}
		return InfIntFullDivResult(quotient, remainder);
	}

	InfInt::size_type size_diff = a.size() - b.size();
	InfInt mask = InfInt::pos_one << size_diff;
	b <<= size_diff;
	while (a >= _b) {
		while (a < b) {
			mask >>= 1;
			b >>= 1;
		}
		a -= b;
		q |= mask;
		mask >>= b.size() - a.size();
		b >>= b.size() - a.size();
	}

	InfInt quotient = q;
	InfInt remainder = a;
	if (_a.sign() != _b.sign()) {
		quotient.twos_complement();
		remainder.twos_complement();
	}
	return InfIntFullDivResult(quotient, remainder);
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
		if (*this < (-other))
			return -((-other) + (-(*this)));
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
		bool sign = temp.m_number.back();
		temp.m_number.pop_back();
		temp.clean();
		if (!sign)
			temp.twos_complement();
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
	InfInt a(*this);
	if (a.sign())
		a.twos_complement();
	InfInt b(other);
	if (b.sign())
		b.twos_complement();
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
	InfInt a(*this);
	if (a.sign())
		a.twos_complement();
	InfInt abs_other(other);
	if (abs_other.sign())
		abs_other.twos_complement();
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

	InfInt a(*this);
	if (a.sign())
		a.twos_complement();
	InfInt b(other);
	if (b.sign())
		b.twos_complement();

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

// alows the use of the macro _inf to transform a unsigned long long to an InfInt
InfInt operator "" _inf(unsigned long long other) {
	return static_cast<InfInt>(other);
}

std::ostream& operator<<(std::ostream& out, const InfInt& infint) {
	out << infint.str(10);
	return out;
}

std::istream& operator>>(std::istream& in, InfInt& infint) {
	std::string str;
	in >> str;
	infint = InfInt(str, 10);
	return in;
}
