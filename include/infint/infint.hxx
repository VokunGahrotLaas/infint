#pragma once

#include <infint/infint.hpp>

// infint
#include <infint/result.hpp>

// std
#include <climits>
#include <compare>
#include <ranges>
#include <type_traits>

namespace infint
{

namespace
{

template <int base>
	requires valid_base<base>
constexpr char digit_value(char c)
{
	if (unsigned char dec = c - '0'; dec < 10) return dec;
	if (unsigned char alpha = c - 'a'; alpha < 26) return alpha + 10;
	if (unsigned char alpha_maj = c - 'A'; alpha_maj < 26)
	{
		if constexpr (base < 36) return alpha_maj + 10;
		return alpha_maj + 36;
	}
	return -1;
}

template <int base, is_infint InfInt>
	requires valid_base<base>
constinit std::vector<InfInt> digit_coefs{
	InfInt::pos_one(), base, base* base, base* base* base, base* base* base* base, base* base* base* base* base,
};

template <int base, is_infint InfInt>
	requires valid_base<base>
constexpr auto digit_coef(size_t i)
{
	auto& coefs = digit_coefs<base, InfInt>;
	InfInt const infint_base{ base };
	while (coefs.size() < i)
		coefs.emplace_back(coefs.back() * infint_base);
	return digit_coefs<base, InfInt>[i];
}

template <typename T>
concept has_flip = requires(T& t) { t.flip(); };

template <std::unsigned_integral T>
consteval std::pair<T, size_t> max_powten()
{
	T old_v = 10, v;
	size_t i = 1;
	while ((v = old_v * 10) > old_v)
	{
		old_v = v;
		++i;
	}
	return { old_v, i };
}

} // namespace

template <infint_container vector_t, boolish bool_t>
constexpr infint<vector_t, bool_t>::infint(vector_t&& vec)
	: number_(std::move(vec))
	, sign_(false)
{
	number_.clear();
	number_.emplace_back(false);
}

template <infint_container vector_t, boolish bool_t>
constexpr infint<vector_t, bool_t>::infint(infint&& other)
	: number_(std::move(other.number_))
	, sign_(other.sign_)
{
	other.number_ = { false };
	other.sign_ = false;
}

template <infint_container vector_t, boolish bool_t>
constexpr auto infint<vector_t, bool_t>::operator=(infint&& other) -> infint&
{
	this->number_ = std::move(other.number_);
	this->sign_ = other.sign_;
	other.number_ = { false };
	other.sign_ = false;
	return *this;
}

template <infint_container vector_t, boolish bool_t>
template <infint_container ovector_t, boolish obool_t>
constexpr infint<vector_t, bool_t>::infint(infint<ovector_t, obool_t> const& other)
	: number_{}
	, sign_{ false }
{
	if constexpr (std::assignable_from<vector_t, ovector_t const&>)
		number_ = other.number_;
	else
	{
		number_.resize(other.size());
		std::copy(other.number().cbegin(), other.number().cend(), number_.begin());
	}
}

template <infint_container vector_t, boolish bool_t>
template <std::unsigned_integral T>
constexpr infint<vector_t, bool_t>::infint(T other, vector_t&& vec)
	: number_(std::move(vec))
{
	number_.clear();
	this->sign_ = false;
	if (other == T{ 0 })
	{
		this->number_.emplace_back(false);
		return;
	}
	while (other != T{ 0 })
	{
		this->number_.emplace_back(static_cast<bool_t>(other & 1));
		other >>= 1;
	}
}

template <infint_container vector_t, boolish bool_t>
template <std::signed_integral T>
constexpr infint<vector_t, bool_t>::infint(T other, vector_t&& vec)
	: number_(std::move(vec))
{
	number_.clear();
	if (other >= T{ 0 })
	{
		this->sign_ = false;
		if (other == T{ 0 })
		{
			this->number_.emplace_back(false);
			return;
		}
		while (other != T{ 0 })
		{
			this->number_.emplace_back(static_cast<bool>(other & 1));
			other >>= 1;
		}
	}
	else
	{
		this->sign_ = true;
		if (other == T{ -1 })
		{
			this->number_.emplace_back(false);
			return;
		}
		while (other != T{ -1 })
		{
			this->number_.emplace_back(static_cast<bool>(other & 1));
			other >>= 1;
		}
	}
}

template <infint_container vector_t, boolish bool_t>
template <std::signed_integral T>
constexpr auto infint<vector_t, bool_t>::of(T other, vector_t&& vec) -> infint
{
	return { other, std::move(vec) };
}

template <infint_container vector_t, boolish bool_t>
template <std::unsigned_integral T>
constexpr auto infint<vector_t, bool_t>::of(T other, vector_t&& vec) -> infint
{
	return { other, std::move(vec) };
}

template <infint_container vector_t, boolish bool_t>
constexpr infint<vector_t, bool_t>::infint(std::string_view other)
	: number_{}
	, sign_(false)
{
	if (other.empty())
	{
		this->number_.emplace_back(false);
		return;
	}
	if (other.front() == '-')
	{
		this->sign_ = true;
		other.remove_prefix(1);
	}
	else if (other.front() == '+')
		other.remove_prefix(1);
	this->number_.reserve(other.size());
	for (char c: reversed(other))
		this->number_.emplace_back(c != '0');
	this->clean();
}

template <infint_container vector_t, boolish bool_t>
template <int base_>
	requires valid_base<base_>
constexpr infint<vector_t, bool_t>::infint(std::string_view other, std::integral_constant<int, base_> base)
	: number_{ false }
	, sign_(false)
{
	if (other.empty()) return;
	bool sign = other.front() == '-';
	if (sign)
		other.remove_prefix(1);
	else if (other.front() == '+')
		other.remove_prefix(1);
	for (size_t i = 0; char c: reversed(other))
	{
		auto v = digit_value<base>(c);
		if (v > 0) *this += infint(v) * digit_coef<base, infint>(i++);
	}
	this->clean();
	if (sign) this->twos_complement();
}

template <infint_container vector_t, boolish bool_t>
constexpr auto infint<vector_t, bool_t>::of(std::string_view other) -> infint
{
	return infint{ other };
}

template <infint_container vector_t, boolish bool_t>
template <int base>
	requires valid_base<base>
constexpr auto infint<vector_t, bool_t>::of(std::string_view other) -> infint
{
	return infint{ other, std::integral_constant<int, base>() };
}

template <infint_container vector_t, boolish bool_t>
constexpr infint<vector_t, bool_t>::operator bool() const
{
	return this->sign() || this->size() != 1 || (*this)[0];
}

template <infint_container vector_t, boolish bool_t>
constexpr vector_t const& infint<vector_t, bool_t>::number() const
{
	return number_;
}

template <infint_container vector_t, boolish bool_t>
constexpr bool_t infint<vector_t, bool_t>::sign() const
{
	return this->sign_;
}

template <infint_container vector_t, boolish bool_t>
constexpr bool_t infint<vector_t, bool_t>::get(size_type pos) const
{
	if (pos < this->size()) return (*this)[pos];
	return this->sign_;
}

template <infint_container vector_t, boolish bool_t>
template <std::integral T>
constexpr T infint<vector_t, bool_t>::get_int(size_type pos) const
{
	bool b = this->get(pos);
	return b;
}

template <infint_container vector_t, boolish bool_t>
constexpr bool_t infint<vector_t, bool_t>::operator[](size_type pos) const
{
	return this->number_[pos];
}

template <infint_container vector_t, boolish bool_t>
constexpr auto infint<vector_t, bool_t>::size(void) const -> size_type
{
	return this->number_.size();
}

template <infint_container vector_t, boolish bool_t>
constexpr auto infint<vector_t, bool_t>::ones_complement(void) -> infint&
{
	this->sign_ = !this->sign_;
	if constexpr (!has_flip<vector_t>)
		for (bool_t& b: this->number_)
			b = !b;
	else
		this->number_.flip();
	return *this;
}

template <infint_container vector_t, boolish bool_t>
constexpr auto infint<vector_t, bool_t>::twos_complement(void) -> infint&
{
	if (!*this) return *this;
	this->ones_complement();
	infint tmp;
	tmp.sign_ = this->sign();
	tmp.number_.resize(this->size() + 1, false);
	tmp.number_[1] = this->get(0);
	tmp.number_[0] = !this->get(0);
	for (size_type i = 1; i < this->size(); ++i)
	{
		tmp.number_[i + 1] = this->get(i) && tmp.get(i);
		tmp.number_[i] = this->get(i) != tmp.get(i);
	}
	if (!tmp.number_.back()) tmp.number_.pop_back();
	tmp.clean();
	*this = tmp;
	return *this;
}

template <infint_container vector_t, boolish bool_t>
constexpr std::string infint<vector_t, bool_t>::Bstr() const
{
	std::string str;
	str.reserve(this->size());
	if (this->sign_)
		str.push_back('-');
	else
		str.push_back('+');
	for (size_t i = size() - 1; i > 0; --i)
		str.push_back('0' + this->get(i));
	if (this->size() > 0) str.push_back('0' + this->get(0));
	return str;
}

template <infint_container vector_t, boolish bool_t>
constexpr std::string infint<vector_t, bool_t>::Bstr(size_type str_size) const
{
	if (str_size == 0) str_size = this->size() + 1;
	if (str_size <= this->size())
		throw std::logic_error("std::string infint<vector_t, bool_t>::b_str(size_type str_size) "
							   "const: str_size <= size()");
	std::string str;
	str.reserve(str_size);
	for (; str_size > this->size(); --str_size)
		str.push_back('0' + this->sign_);
	for (size_t i = this->size() - 1; i > 0; --i)
		str.push_back('0' + get(i));
	if (this->size() > 0) str.push_back('0' + get(0));
	return str;
}

template <infint_container vector_t, boolish bool_t>
template <int base_>
	requires valid_base<base_>
constexpr std::string infint<vector_t, bool_t>::str(std::integral_constant<int, base_>) const
{
	std::string str;
	infint tmp(*this);
	if (!tmp) str.push_back('0');
	if (tmp.sign()) tmp.twos_complement();
	infint const infint_base{ base_ };
	while (tmp)
	{
		auto [quotient, remainder] = infint::fulldiv(tmp, infint_base);
		auto v = remainder.template to_int<char>();
		tmp = std::move(quotient);
		if (v < 10)
			str.push_back('0' + v);
		else if (v < 36)
			str.push_back('a' + (v - 10));
		else
			str.push_back('A' + (v - 36));
	}
	if (this->sign()) str.push_back('-');
	std::reverse(str.begin(), str.end());
	return str;
}

template <infint_container vector_t, boolish bool_t>
constexpr std::string infint<vector_t, bool_t>::str() const
{
	using ulong_t = unsigned long long;
	auto const [powten, size] = max_powten<ulong_t>();
	std::string str;
	infint tmp(*this);
	if (tmp.sign()) tmp.twos_complement();
	while (true)
	{ // do {...} while (temp != zero);
		auto [quotient, remainder] = infint::fulldiv(tmp, powten);
		tmp = std::move(quotient);
		if (!tmp)
		{
			str = std::to_string(remainder.template to_int<ulong_t>()) + str;
			break;
		}
		std::string tmpstr = std::to_string(remainder.template to_int<ulong_t>());
		size_type tmpsize = size - tmpstr.size();
		str = tmpstr + str;
		tmpstr.clear();
		for (size_type i = 0; i < tmpsize; ++i)
			tmpstr.push_back('0');
		str = tmpstr + str;
	}
	return this->sign() ? '-' + str : str;
}

template <infint_container vector_t, boolish bool_t>
template <std::integral T>
constexpr T infint<vector_t, bool_t>::to_int() const
{
	T tmp{ 0 };
	if constexpr (std::is_signed_v<T>)
		if (sign()) tmp = T{ -1 } ^ ((T{ 1 } << size()) + T{ -1 });
	for (size_type i = 0; i < size(); ++i)
		tmp |= this->get_int<T>(i) << i;
	return tmp;
}

template <infint_container vector_t, boolish bool_t>
template <std::integral T>
constexpr T infint<vector_t, bool_t>::to_int_safe() const
{
	if (sizeof(T) * CHAR_BIT < size() + sign() ? 1u : 0u)
		throw std::overflow_error("T infint::to_int_safe() const: Given type is too litle!");
	T tmp{ 0 };
	if constexpr (std::is_unsigned_v<T>)
	{
		if (sign()) throw std::domain_error("T infint::to_int_safe() const: Given type do not have the right signess!");
	}
	else if (sign())
		tmp = T{ -1 } ^ ((T{ 1 } << size()) + T{ -1 });
	for (size_type i = 0; i < size(); ++i)
		tmp |= get_int<T>(i) << i;
	return tmp;
}

template <infint_container vector_t, boolish bool_t>
constexpr auto infint<vector_t, bool_t>::fulldiv(infint const& _a, infint const& _b) -> fulldiv_t<infint>
{
	if (!_b)
		throw std::domain_error("fulldiv_t infint::fulldiv(infint const& _a, infint const& _b): Cannot divide by 0");

	infint q;
	infint a(_a);
	if (a.sign()) a.twos_complement();
	infint abs_b(_b);
	if (abs_b.sign()) abs_b.twos_complement();
	infint b(abs_b);

	auto cmp = b <=> a;
	if (cmp >= 0)
	{
		infint remainder, quotient;
		if (cmp == 0)
			quotient = _a.sign() == _b.sign() ? infint::pos_one() : infint::neg_one();
		else
			remainder = _a;
		return { std::move(quotient), std::move(remainder) };
	}

	size_type const size_diff = a.size() - b.size();
	infint mask = infint::pos_one() << size_diff;
	b <<= size_diff;
	while (a >= abs_b)
	{
		if (a < b)
		{
			mask >>= 1;
			b >>= 1;
		}
		a -= b;
		q |= mask;
		size_type const size_diff = b.size() - a.size();
		mask >>= size_diff;
		b >>= size_diff;
	}

	if (_a.sign() != _b.sign()) q.twos_complement();
	if (a.sign() != _a.sign()) a.twos_complement();
	return { std::move(q), std::move(a) };
}

template <infint_container vector_t, boolish bool_t>
constexpr bool infint<vector_t, bool_t>::operator==(infint const& other) const
{
	return this->sign_ == other.sign_ && this->number_ == other.number_;
}

template <infint_container vector_t, boolish bool_t>
constexpr std::strong_ordering infint<vector_t, bool_t>::operator<=>(infint const& other) const
{
	using ord = std::strong_ordering;
	if (this->sign() && !other.sign()) return ord::less;
	if (!this->sign() && other.sign()) return ord::greater;
	if (this->size() < other.size()) return !this->sign() ? ord::less : ord::greater;
	if (this->size() > other.size()) return this->sign() ? ord::less : ord::greater;
	if (this->size() > 1)
	{
		for (size_type i = this->size() - 2; i > 0; --i)
		{
			if ((*this)[i] == other[i]) continue;
			return (*this)[i] ? ord::greater : ord::less;
		}
	}
	if (this->size() != 0 && (*this)[0] != other.get(0)) return (*this)[0] ? ord::greater : ord::less;
	return ord::equal;
}

template <infint_container vector_t, boolish bool_t>
constexpr auto infint<vector_t, bool_t>::operator+() const -> infint
{
	return *this;
}

template <infint_container vector_t, boolish bool_t>
constexpr auto infint<vector_t, bool_t>::operator-() const -> infint
{
	infint tmp(*this);
	tmp.twos_complement();
	return tmp;
}

template <infint_container vector_t, boolish bool_t>
constexpr auto infint<vector_t, bool_t>::operator+(infint const& other) const -> infint
{
	return infint(*this) += other;
}

template <infint_container vector_t, boolish bool_t>
constexpr auto infint<vector_t, bool_t>::operator+=(infint const& other) -> infint&
{
	size_type max_size;
	if (this->number_.size() < other.number_.size())
		max_size = other.size();
	else
		max_size = this->size();
	this->number_.resize(max_size, this->sign());
	bool old_carry = false;
	for (size_type i = 0; i < max_size; ++i)
	{
		bool new_carry = ((this->get(i) != other.get(i)) && old_carry) || (this->get(i) && other.get(i));
		this->number_[i] = (this->get(i) != other.get(i)) != old_carry;
		old_carry = new_carry;
	}
	if (this->sign() == other.sign())
		this->number_.emplace_back(old_carry);
	else
		this->sign_ = !old_carry;
	return this->clean();
}

template <infint_container vector_t, boolish bool_t>
constexpr auto infint<vector_t, bool_t>::operator++() -> infint&
{
	*this += infint::pos_one();
	return *this;
}

template <infint_container vector_t, boolish bool_t>
constexpr auto infint<vector_t, bool_t>::operator++(int) -> infint
{
	infint tmp(*this);
	++(*this);
	return tmp;
}

template <infint_container vector_t, boolish bool_t>
constexpr auto infint<vector_t, bool_t>::operator-(infint const& other) const -> infint
{
	return infint(*this) -= other;
}

template <infint_container vector_t, boolish bool_t>
constexpr auto infint<vector_t, bool_t>::operator-=(infint const& other) -> infint&
{
	return (*this) += (-other);
}

template <infint_container vector_t, boolish bool_t>
constexpr auto infint<vector_t, bool_t>::operator--() -> infint&
{
	return *this += infint::neg_one();
}

template <infint_container vector_t, boolish bool_t>
constexpr auto infint<vector_t, bool_t>::operator--(int) -> infint
{
	infint tmp(*this);
	--(*this);
	return tmp;
}

template <infint_container vector_t, boolish bool_t>
constexpr auto infint<vector_t, bool_t>::operator*(infint const& other) const -> infint
{
	if (other.size() < this->size()) return other * (*this);
	infint temp;
	infint a(*this);
	if (a.sign()) a.twos_complement();
	infint b(other);
	if (b.sign()) b.twos_complement();
	for (size_type i = 0; i < a.size(); ++i)
		if (a.get(i)) temp += b << i;
	if (this->sign() != other.sign()) temp.twos_complement();
	return temp;
}

template <infint_container vector_t, boolish bool_t>
constexpr auto infint<vector_t, bool_t>::operator*=(infint const& other) -> infint&
{
	*this = (*this) * other;
	return *this;
}

template <infint_container vector_t, boolish bool_t>
constexpr auto infint<vector_t, bool_t>::operator/(infint const& other) const -> infint
{
	return infint::fulldiv(*this, other).q;
}

template <infint_container vector_t, boolish bool_t>
constexpr auto infint<vector_t, bool_t>::operator/=(infint const& other) -> infint&
{
	return *this = *this / other;
}

template <infint_container vector_t, boolish bool_t>
constexpr auto infint<vector_t, bool_t>::operator%(infint const& other) const -> infint
{
	if (!other) throw std::domain_error("infint infint::operator%(infint const& other) const: Cannot divide by 0");

	infint a(*this);
	if (a.sign()) a.twos_complement();
	infint abs_other(other);
	if (abs_other.sign()) abs_other.twos_complement();
	infint b = abs_other;

	if (b >= a)
	{
		if (b == a)
			return infint::zero();
		else
		{
			if (a.sign() != this->sign()) a.twos_complement();
			return a;
		}
	}

	b <<= a.size() - b.size();
	while (a >= abs_other)
	{
		if (a < b) b >>= 1;
		a -= b;
		b >>= b.size() - a.size();
	}

	if (a.sign() != this->sign()) a.twos_complement();
	return a;
}

template <infint_container vector_t, boolish bool_t>
constexpr auto infint<vector_t, bool_t>::operator%=(infint const& other) -> infint&
{
	return *this = *this % other;
}

template <infint_container vector_t, boolish bool_t>
constexpr auto infint<vector_t, bool_t>::operator&(infint const& other) const -> infint
{
	size_type max_size = 1;
	if (this->size() < other.size())
		max_size = other.size();
	else
		max_size = this->size();
	infint temp;
	temp.sign_ = this->sign() && other.sign();
	temp.number_.resize(max_size, temp.sign());
	for (size_type i = 0; i < max_size; ++i)
		temp.number_[i] = this->get(i) && other.get(i);
	return temp.clean();
}

template <infint_container vector_t, boolish bool_t>
constexpr auto infint<vector_t, bool_t>::operator&=(infint const& other) -> infint&
{
	size_type max_size = 1;
	if (this->size() < other.size())
		max_size = other.size();
	else
		max_size = this->size();
	this->sign_ = this->sign() && other.sign();
	this->number_.resize(max_size, this->sign());
	for (size_type i = 0; i < max_size; ++i)
		this->number_[i] = this->get(i) && other.get(i);
	return this->clean();
}

template <infint_container vector_t, boolish bool_t>
constexpr auto infint<vector_t, bool_t>::operator|(infint const& other) const -> infint
{
	size_type max_size;
	if (this->size() < other.size())
		max_size = other.size();
	else
		max_size = this->size();
	infint temp;
	temp.sign_ = this->sign() || other.sign();
	temp.number_.resize(max_size, temp.sign());
	for (size_type i = 0; i < max_size; ++i)
		temp.number_[i] = this->get(i) || other.get(i);
	return temp.clean();
}

template <infint_container vector_t, boolish bool_t>
constexpr auto infint<vector_t, bool_t>::operator|=(infint const& other) -> infint&
{
	size_type max_size;
	if (this->size() < other.size())
		max_size = other.size();
	else
		max_size = this->size();
	this->sign_ = this->sign() || other.sign();
	this->number_.resize(max_size, this->sign());
	for (size_type i = 0; i < max_size; ++i)
		this->number_[i] = this->get(i) || other.get(i);
	return this->clean();
}

template <infint_container vector_t, boolish bool_t>
constexpr auto infint<vector_t, bool_t>::operator^(infint const& other) const -> infint
{
	size_type max_size;
	if (this->size() < other.size())
		max_size = other.size();
	else
		max_size = this->size();
	infint temp;
	temp.sign_ = this->sign() != other.sign();
	temp.number_.resize(max_size, temp.sign());
	for (size_type i = 0; i < max_size; ++i)
		temp.number_[i] = this->get(i) != other.get(i);
	return temp.clean();
}

template <infint_container vector_t, boolish bool_t>
constexpr auto infint<vector_t, bool_t>::operator^=(infint const& other) -> infint&
{
	size_type max_size;
	if (this->size() < other.size())
		max_size = other.size();
	else
		max_size = this->size();
	this->sign_ = this->sign() != other.sign();
	this->number_.resize(max_size, this->sign());
	for (size_type i = 0; i < max_size; ++i)
		this->number_[i] = this->get(i) != other.get(i);
	return this->clean();
}

template <infint_container vector_t, boolish bool_t>
constexpr auto infint<vector_t, bool_t>::operator<<(size_type other) const -> infint
{
	infint temp{ *this };
	temp <<= other;
	return temp;
}

template <infint_container vector_t, boolish bool_t>
constexpr auto infint<vector_t, bool_t>::operator<<=(size_type other) -> infint&
{
	if (other == 0 || !*this) return *this;
	this->number_.insert(this->number_.cbegin(), other, false);
	return *this;
}

template <infint_container vector_t, boolish bool_t>
constexpr auto infint<vector_t, bool_t>::operator>>(size_type other) const -> infint
{
	if (other == 0) return *this;
	if (other > this->size()) return { this->sign(), {} };
	return {
		this->sign(), {this->number_.cbegin() + other, this->number_.cend()}
	};
}

template <infint_container vector_t, boolish bool_t>
constexpr auto infint<vector_t, bool_t>::operator>>=(size_type other) -> infint&
{
	if (other == 0) return *this;
	if (other >= this->size())
	{
		this->number_.clear();
		this->number_.emplace_back(this->sign());
	}
	else
		this->number_.erase(this->number_.cbegin(), this->number_.cbegin() + other);
	return *this;
}

template <infint_container vector_t, boolish bool_t>
constexpr auto infint<vector_t, bool_t>::zero() -> infint
{
	return 0;
}

template <infint_container vector_t, boolish bool_t>
constexpr auto infint<vector_t, bool_t>::pos_one() -> infint
{
	return 1;
}

template <infint_container vector_t, boolish bool_t>
constexpr auto infint<vector_t, bool_t>::neg_one() -> infint
{
	return -1;
}

template <infint_container vector_t, boolish bool_t>
constexpr infint<vector_t, bool_t>::infint(bool_t sign, vector_t&& number)
	: number_{ std::move(number) }
	, sign_{ sign }
{
	this->clean();
}

template <infint_container vector_t, boolish bool_t>
constexpr auto infint<vector_t, bool_t>::clean() -> infint&
{
	while (this->size() > 1 && this->number_.back() == this->sign_)
		this->number_.pop_back();
	if (this->size() == 0) this->number_.emplace_back(this->sign_);
	return *this;
}

// alows the use of the macro _inf to transform a unsigned long long to an
// infint
constexpr infint<> operator"" _infint(unsigned long long other) { return other; }

template <infint_container vector_t, boolish bool_t>
std::ostream& operator<<(std::ostream& os, infint<vector_t, bool_t> const& infint)
{
	return os << infint.str();
}

template <infint_container vector_t, boolish bool_t>
std::istream& operator>>(std::istream& is, infint<vector_t, bool_t>& infint)
{
	if (!is) return is;
	std::string str;
	is >> str;
	if (!is) return is;
	infint = infint.template of<10>(str);
	return is;
}

} // namespace infint
