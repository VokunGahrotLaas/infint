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
		Int(void); // init to +0
		// copy
		Int(const Int& other); // Int
		Int(int other); // int
		Int(unsigned int other); // unsigned int
		Int(long other); // long
		Int(unsigned long other); // unsigned long
		Int(long long other); // long long
		Int(unsigned long long other); // unsigned long long
		Int(std::string other); // std::string
		Int(std::string other, int base);
		// destructor //
		~Int(void); // empty
		// const getter //
		bool sign(void) const;
		bool get(const size_type& pos) const;
		size_type size(void) const;
		// complements //
		Int& ones_complement(void);
		Int& twos_complement(void);
		// casting //
		std::string to_Bstr(void) const;
		std::string to_Bstr(size_type str_size) const;
		std::string to_str(int base) const;
		template <class T> T to_int(void) const;
		template <class T> T to_int_safe(void) const;
		// operator //
		// equal
		Int& operator=(const Int& other);
		// cmp
		bool operator==(const Int& other) const;
		bool operator!=(const Int& other) const;
		bool operator>(const Int& other) const;
		bool operator<=(const Int& other) const;
		bool operator<(const Int& other) const;
		bool operator>=(const Int& other) const;
		// unary
		Int operator+(void) const;
		Int operator-(void) const;
		// add
		Int operator+(const Int& other) const;
		Int& operator+=(const Int& other);
		Int& operator++(void);
		Int operator++(int);
		// sub
		Int operator-(const Int& other) const;
		Int& operator-=(const Int& other);
		Int& operator--(void);
		Int operator--(int);
		// mul
		Int operator*(const Int& other) const;
		Int& operator*=(const Int& other);
		// div
		Int operator/(const Int& other) const;
		Int& operator/=(const Int& other);
		// mod
		Int operator%(const Int& other) const;
		Int& operator%=(const Int& other);
		// bitwise
		Int operator&(const Int& other) const;
		Int& operator&=(const Int& other);
		Int operator|(const Int& other) const;
		Int& operator|=(const Int& other);
		Int operator^(const Int& other) const;
		Int& operator^=(const Int& other);
		Int operator<<(size_type other) const;
		Int& operator<<=(size_type other);
		Int operator>>(size_type other) const;
		Int& operator>>=(size_type other);
	protected:
		void clean(void);
		// Attributes //
		std::vector<bool> m_number;
		bool m_sign;
		char padding[sizeof(void*) - (sizeof(std::vector<bool>) + sizeof(bool)) % sizeof(void*)]; // usualy 7, alows the struct to be round when used un arrays
		// Static Attributes //
		static Int neg_one;
		static Int zero;
		static Int pos_one;
};

Int::Int(void):
	m_number({false}),
	m_sign(false)
{
	//
}

Int::Int(const Int& other):
	m_number(other.m_number),
	m_sign(other.m_sign)
{
	//
}

Int::Int(int other) {
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
	} else {
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

Int::Int(unsigned int other) {
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

Int::Int(long other) {
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
	} else {
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

Int::Int(unsigned long other) {
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

Int::Int(long long other) {
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
	} else {
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

Int::Int(unsigned long long other) {
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

Int::Int(std::string other) {
	if (other.empty()) {
		m_sign = false;
		m_number.push_back(false);
		return;
	}
	if (other.front() == '-')
		m_sign = true;
	else if (other.front() == '+')
		m_sign = false;
	else
		m_sign = false;
	other.assign(other, 1, other.size());
	m_number.reserve(other.size());
	while (other.size() > 0) {
		m_number.push_back(other.back() != '0');
		other.pop_back();
	}
	clean();
}

Int::~Int(void) {
	//
}

bool Int::sign(void) const {
	return m_sign;
}

bool Int::get(const unsigned long long& pos) const {
	if (pos < size())
		return m_number[pos];
	else
		return m_sign;
}

typename Int::size_type Int::size(void) const {
	return m_number.size();
}

Int& Int::ones_complement(void) {
	m_sign = !sign();
	m_number.flip();
	return *this;
}

Int& Int::twos_complement(void) {
	if (*this == Int::zero)
		return *this;
	ones_complement();
	Int temp;
	temp.m_sign = sign();
	temp.m_number.resize(size() + 1, false);
	temp.m_number[1] = get(0);
	temp.m_number[0] = !get(0);
	for (size_type i = 1; i < size(); i++) {
		temp.m_number[i + 1] = get(i) && temp.get(i);
		temp.m_number[i] = get(i) != temp.get(i);
	}
	if (!temp.m_number.back())
		temp.m_number.pop_back();
	temp.clean();
	*this = temp;
	return *this;
}

std::string Int::to_Bstr(void) const {
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

std::string Int::to_Bstr(size_type str_size) const {
	if (str_size == 0)
		str_size = size() + 1;
	if (str_size <= size())
		throw std::logic_error("std::string Int::b_str(size_type str_size) const: str_size <= size()");
	std::string str;
	str.reserve(str_size);
	for (; str_size > size(); str_size--)
		str.push_back('0' + m_sign);
	for (size_t i = size() - 1; i > 0; --i) {
		str.push_back('0' + get(i));
	}
	if (size() > 0) {
		str.push_back('0' + get(0));
	}
	return str;
}

std::string Int::to_str(int base) const {
	if (base < 2 || base > 62)
		throw std::invalid_argument("std::string Int::str(int base) const: base must be beetween 2 and 62");
	std::string str;
	Int temp(*this);
	if (temp == Int())
		str.push_back('0');
	while (temp != Int()) {
		Int r = temp % base;
		if (r < 10)
			str.push_back('0' + r.to_int<char>());
		else if (r < 36)
			str.push_back('a' + r.to_int<char>() - 10);
		else
			str.push_back('A' + r.to_int<char>() - 36);
		temp /= base;
	}
	if (sign())
		str.push_back('-');
	else
		str.push_back('+');
	std::reverse(str.begin(), str.end());
	return str;
}

template <class T>
T Int::to_int(void) const {
	size_type bits_in_T = sizeof(T) * 8;
	T temp = 0;
	for (size_type i = 0; i < bits_in_T; i++)
		temp |= static_cast<T>(get(i)) << i;
	return temp;
}

template <class T>
T Int::to_int_safe(void) const {
	size_type bits_in_T = sizeof(T) * 8;
	if (bits_in_T < size())
		throw std::overflow_error("template <class T> T Int::to_int_safe(void) const: Given type is too litle!");
	if (sign())
		if (static_cast<T>(0) - static_cast<T>(1) < static_cast<T>(0))
			throw std::overflow_error("template <class T> T Int::to_int_safe(void) const: Given type do not have the right signess!");
	T temp = 0;
	for (size_type i = 0; i < bits_in_T; i++)
		temp |= static_cast<T>(get(i)) << i;
	return temp;
}

Int& Int::operator=(const Int& other) {
	m_sign = other.sign();
	m_number = other.m_number;
	return *this;
}

bool Int::operator==(const Int& other) const {
	if (size() != other.size())
		return false;
	if (sign() != other.sign())
		return false;
	for (unsigned long long i = 0; i < size(); i++)
		if (m_number[i] != other.get(i))
			return false;
	return true;
}

bool Int::operator!=(const Int& other) const {
	return !(*this == other);
}

bool Int::operator>(const Int& other) const {
	if (!sign() && other.sign())
		return true;
	if (sign() && !other.sign())
		return false;
	if (size() > other.size())
		return !sign();
	if (size() < other.size())
		return sign();
	if (size() > 1) {
		for (size_type i = size() - 2; i > 0; i--) {
			if (get(i) == other.get(i))
				continue;
			if (get(i) == sign())
				return false;
			return true;
		}
	} else
		return get(0) != other.get(0) && get(0) != sign();
	return false;
}

bool Int::operator<=(const Int& other) const {
	return !(*this > other);
}

bool Int::operator<(const Int& other) const {
	if (sign() && !other.sign())
		return true;
	if (!sign() && other.sign())
		return false;
	if (size() < other.size())
		return !sign();
	if (size() > other.size())
		return sign();
	if (size() > 1) {
		for (size_type i = size() - 2; i > 0; i--) {
			if (get(i) == other.get(i))
				continue;
			if (other.get(i) == sign())
				return false;
			return true;
		}
	} else
		return get(0) != other.get(0) && other.get(0) != sign();
	return false;
}

bool Int::operator>=(const Int& other) const {
	return !(*this < other);
}

Int Int::operator+(void) const {
	return *this;
}

Int Int::operator-(void) const {
	Int temp(*this);
	temp.twos_complement();
	return temp;
}

Int Int::operator+(const Int& other) const {
	if (!sign() && !other.sign()) { // both positive
		size_type max_size;
		if (m_number.size() < other.m_number.size())
			max_size = other.size();
		else
			max_size = size();
		Int temp;
		temp.m_number.resize(max_size + 1, false);
		for (size_type i = 0; i < max_size; i++) {
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
		Int temp;
		temp.m_number.resize(max_size + 1, false);
		for (size_type i = 0; i < max_size; i++) {
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
	} else { // both are negative
		return -(-*this + -other);
	}
}

Int& Int::operator+=(const Int& other) {
	*this = *this + other;
	return *this;
}

Int& Int::operator++(void) {
	*this += Int::pos_one;
	return *this;
}

Int Int::operator++(int) {
	Int return_val(*this);
	++*this;
	return return_val;
}

Int Int::operator-(const Int& other) const {
	return *this + -other;
}

Int& Int::operator-=(const Int& other) {
	*this = *this - other;
	return *this;
}

Int& Int::operator--(void) {
	*this -= Int::pos_one;
	return *this;
}

Int Int::operator--(int) {
	Int return_val(*this);
	--*this;
	return return_val;
}

Int Int::operator*(const Int& other) const {
	Int temp;
	Int a(*this);
	if (a.sign())
		a.twos_complement();
	Int b(other);
	if (b.sign())
		b.twos_complement();
	for (; b > 0; b--)
		temp += a;
	if (sign() != other.sign())
		temp.twos_complement();
	return temp;
}

Int& Int::operator*=(const Int& other) {
	*this = *this * other;
	return *this;
}

Int Int::operator/(const Int& other) const {
	if (other == Int::zero)
		throw std::invalid_argument("Cannot divide by 0");
	if (*this == Int::zero)
		return Int::zero;
	Int temp;
	Int a(*this);
	if (a.sign())
		a.twos_complement();
	Int b(other);
	if (b.sign())
		b.twos_complement();
	for (; a >= b; a -= b, temp++);
	if (sign() != other.sign())
		temp.twos_complement();
	return temp;
}

Int& Int::operator/=(const Int& other) {
	*this = *this / other;
	return *this;
}

Int Int::operator%(const Int& other) const {
	Int a(*this);
	if (a.sign())
		a.twos_complement();
	Int b(other);
	if (b.sign())
		b.twos_complement();
	for (; a >= b; a -= b);
	return a;
}

Int& Int::operator%=(const Int& other) {
	*this = *this % other;
	return *this;
}

Int Int::operator&(const Int& other) const {
	size_type max_size = 1;
	if (size() < other.size())
		max_size = other.size();
	else
		max_size = size();
	Int temp;
	temp.m_sign = sign() && other.sign();
	temp.m_number.resize(max_size, temp.sign());
	for (unsigned long long i = 0; i < max_size; i++)
		temp.m_number[i] = get(i) && other.get(i);
	temp.clean();
	return temp;
}

Int& Int::operator&=(const Int& other) {
	*this = *this & other;
	return *this;
}

Int Int::operator|(const Int& other) const {
	size_type max_size;
	if (size() < other.size())
		max_size = other.size();
	else
		max_size = size();
	Int temp;
	temp.m_sign = sign() || other.sign();
	temp.m_number.resize(max_size, temp.sign());
	for (unsigned long long i = 0; i < max_size; i++)
		temp.m_number[i] = get(i) || other.get(i);
	temp.clean();
	return temp;
}

Int& Int::operator|=(const Int& other) {
	*this = *this | other;
	return *this;
}

Int Int::operator^(const Int& other) const {
	size_type max_size;
	if (size() < other.size())
		max_size = other.size();
	else
		max_size = size();
	Int temp;
	temp.m_sign = sign() != other.sign();
	temp.m_number.resize(max_size, temp.sign());
	for (unsigned long long i = 0; i < max_size; i++)
		temp.m_number[i] = get(i) != other.get(i);
	temp.clean();
	return temp;
}

Int& Int::operator^=(const Int& other) {
	*this = *this ^ other;
	return *this;
}

Int Int::operator<<(size_type other) const {
	if (other == 0)
		return *this;
	Int temp(*this);
	temp.m_number.insert(temp.m_number.begin(), other, false);
	return temp;
}

Int& Int::operator<<=(size_type other) {
	if (other == 0)
		return *this;
	m_number.insert(m_number.begin(), other, false);
	return *this;
}

Int Int::operator>>(size_type other) const {
	if (other == 0)
		return *this;
	Int temp(*this);
	if (other < size())
		temp.m_number.erase(temp.m_number.begin(), temp.m_number.begin() + static_cast<long long>(other));
	else
		temp.m_number.erase(temp.m_number.begin(), temp.m_number.begin() + static_cast<long long>(size() - 1));
	temp.clean();
	return temp;
}

Int& Int::operator>>=(size_type other) {
	if (other == 0)
		return *this;
	if (other < size())
		m_number.erase(m_number.begin(), m_number.begin() + static_cast<long long>(other));
	else
		m_number.erase(m_number.begin(), m_number.begin() + static_cast<long long>(size() - 1));
	clean();
	return *this;
}

void Int::clean(void) {
	while (size() > 1 && m_number.back() == m_sign)
		m_number.pop_back();
	if (size() == 0)
		m_number.push_back(m_sign);
}

Int Int::neg_one(-1);
Int Int::zero(0);
Int Int::pos_one(1);

// Outside the class //

Int operator "" _i(unsigned long long other) { // alows the use of the macro _i to transform a unsigned long long to an Int
	return static_cast<Int>(other);
}

// output .to_Bstr() to an ostream for convenience and readability
// bad code, strores in string before sending to stream, should directly send to stream
std::ostream& operator<<(std::ostream& out, const Int& integer) {
	out << integer.to_Bstr();
	return out;
}
