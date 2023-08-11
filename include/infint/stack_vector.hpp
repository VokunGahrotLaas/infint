#pragma once

// C++ std
#include <array>
#include <bitset>
#include <cassert>
#include <memory>
#include <span>

// infint
#include <infint/concepts.hpp>

namespace infint
{

template <typename T, std::size_t stack_size>
class stack_vector
{
public:
	using value_type = T;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;
	using iterator = T*;
	using const_iterator = T const*;
	using reversed_iterator = T*;
	using const_reversed_iterator = T const*;
	using reference = T&;
	using const_reference = T const&;

	constexpr stack_vector() = default;
	constexpr stack_vector(stack_vector const&) = default;
	constexpr stack_vector(stack_vector&&) = default;

	constexpr stack_vector(std::size_t size, T const& value = T()) { resize(size, value); }
	constexpr stack_vector(std::initializer_list<T> list)
	{
		reserve(list.size());
		size_ = list.size();
		std::copy(list.begin(), list.end(), begin());
	}

	constexpr ~stack_vector() = default;

	constexpr stack_vector& operator=(stack_vector const&) = default;
	constexpr stack_vector& operator=(stack_vector&&) = default;

	constexpr void resize(std::size_t new_size, T const& value = T())
	{
		reserve(new_size);
		if (new_size > size())
			for (T& v: std::span(data() + size(), new_size - size()))
				v = value;
		size_ = new_size;
	}

	constexpr void reserve(std::size_t capacity)
	{
		assert(capacity <= stack_size);
		capacity_ = std::max(capacity_, capacity);
	}

	constexpr void clear() { size_ = 0; }

	[[nodiscard]]
	constexpr std::size_t size() const
	{
		return size_;
	}

	[[nodiscard]]
	constexpr std::size_t capacity() const
	{
		return capacity_;
	}

	[[nodiscard]]
	constexpr T&
	operator[](std::size_t index)
	{
		return data()[index];
	}

	[[nodiscard]]
	constexpr T const&
	operator[](std::size_t index) const
	{
		return data()[index];
	}

	[[nodiscard]]
	constexpr T& at(std::size_t index)
	{
		assert(index < size());
		return (*this)[index];
	}

	[[nodiscard]]
	constexpr T const& at(std::size_t index) const
	{
		assert(index < size());
		return (*this)[index];
	}

	constexpr void insert(T const* it, std::size_t count, T const& value)
	{
		if (count == 0) return;
		reserve(size() + count);
		T* const stack = data();
		assert(stack <= it && it <= stack + size_);
		std::size_t const beg = it - stack;
		for (std::size_t i = size(); i > beg; --i)
			stack[count + i - 1] = std::move(stack[i - 1]);
		for (T& v: std::span(data() + beg, count))
			v = value;
		size_ += count;
	}

	template <typename... Args>
	constexpr void emplace_back(Args... args)
	{
		T value(std::forward<Args>(args)...);
		reserve(size() + 1);
		data()[size()] = std::move(value);
		++size_;
	}

	[[nodiscard]]
	constexpr T* begin()
	{
		return data();
	}
	[[nodiscard]]
	constexpr T const* begin() const
	{
		return data();
	}
	[[nodiscard]]
	constexpr T const* cbegin() const
	{
		return begin();
	}
	[[nodiscard]]
	constexpr T* end()
	{
		return data() + size();
	}
	[[nodiscard]]
	constexpr T const* end() const
	{
		return data() + size();
	}
	[[nodiscard]]
	constexpr T const* cend() const
	{
		return end();
	}

	[[nodiscard]]
	constexpr T* rbegin()
	{
		return data() + size() - 1;
	}
	[[nodiscard]]
	constexpr T const* rbegin() const
	{
		return data() + size() - 1;
	}
	[[nodiscard]]
	constexpr T const* crbegin() const
	{
		return begin();
	}
	[[nodiscard]]
	constexpr T* rend()
	{
		return data() - 1;
	}
	[[nodiscard]]
	constexpr T const* rend() const
	{
		return data() - 1;
	}
	[[nodiscard]]
	constexpr T const* crend() const
	{
		return end();
	}

	[[nodiscard]]
	constexpr T* data()
	{
		return stack_.data();
	}

	[[nodiscard]]
	constexpr T const* data() const
	{
		return stack_.data();
	}

	[[nodiscard]]
	constexpr std::span<T> span()
	{
		return std::span(data(), size());
	}

	[[nodiscard]]
	constexpr std::span<T const> span() const
	{
		return std::span(data(), size());
	}

	[[nodiscard]]
	constexpr bool
	operator==(stack_vector const& other) const
	{
		return size() == other.size() && std::equal(data(), data() + size(), other.data());
	}

	[[nodiscard]]
	constexpr bool
	operator!=(stack_vector const& other) const = default;

	[[nodiscard]]
	constexpr T& front()
	{
		return data()[0];
	}
	[[nodiscard]]
	constexpr T const& front() const
	{
		return data()[0];
	}

	[[nodiscard]]
	constexpr T& back()
	{
		return data()[size() - 1];
	}
	[[nodiscard]]
	constexpr T const& back() const
	{
		return data()[size() - 1];
	}

	constexpr void pop_back()
	{
		if (size() == 0) return;
		--size_;
	}

	constexpr void erase(T const* beg_it, T const* end_it)
	{
		std::size_t const count = end_it - beg_it;
		if (count == 0) return;
		assert(data() <= beg_it && beg_it <= end_it && end_it <= data() + size());
		std::size_t const beg = beg_it - data();
		for (size_t i = beg; i < size() - count; ++i)
			data()[i] = std::move(data()[i + count]);
		size_ -= count;
	}

private:
	std::array<T, stack_size> stack_{};
	std::size_t size_{ 0 };
	std::size_t capacity_{ stack_size };
};

/*
template <std::size_t stack_size>
class stack_vector<bool, stack_size>
{
public:
	using value_type = bool;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;
	using iterator = T*;
	using const_iterator = T const*;
	using reversed_iterator = T*;
	using const_reversed_iterator = T const*;
	using bitset = std::bitset<stack_size>;
	using reference = typename bitset::reference;

	constexpr stack_vector() = default;
	constexpr stack_vector(stack_vector const&) = default;
	constexpr stack_vector(stack_vector&&) = default;

	constexpr stack_vector(std::size_t size, bool const& value = false) { resize(size, value); }
	constexpr stack_vector(std::initializer_list<bool> list) {
		assert(list.size() < stack_size);
		size_ = capacity_ = list.size();
		bool const* const list_data = list.begin();
		for (std::size_t i = 0; i < list.size(); ++i)
			data()[i] = list_data[i];
	}

	constexpr ~stack_vector() = default;

	constexpr stack_vector& operator=(stack_vector const&) = default;
	constexpr stack_vector& operator=(stack_vector&&) = default;

	constexpr void resize(std::size_t new_size, bool const& value = false)
	{
		reserve(new_size);
		if (new_size > size())
			for (T& v: std::span(data() + size(), new_size - size()))
				v = value;
		size_ = new_size;
	}

	constexpr void reserve(std::size_t capacity)
	{
		assert(capacity <= stack_size);
		capacity_ = std::max(capacity_, capacity);
	}

	constexpr void clear() { size_ = 0; }

	[[nodiscard]]
	constexpr std::size_t size() const { return size_; }

	[[nodiscard]]
	constexpr std::size_t capacity() const { return capacity_; }

	[[nodiscard]]
	constexpr reference operator[](std::size_t index) { return data()[index]; }

	[[nodiscard]]
	constexpr bool operator[](std::size_t index) const { return data()[index]; }

	[[nodiscard]]
	constexpr reference at(std::size_t index)
	{
		assert(index < size());
		return (*this)[index];
	}

	[[nodiscard]]
	constexpr bool at(std::size_t index) const
	{
		assert(index < size());
		return (*this)[index];
	}

	constexpr void insert(const_iterator it, std::size_t count, bool value) {
		if (count == 0) return;
		reserve(size() + count);
		T* const stack = data();
		assert(stack <= it && it <= stack + size_);
		std::size_t const beg = it - stack;
		for (std::size_t i = size(); i > beg; --i)
			stack[count + i - 1] = std::move(stack[i - 1]);
		for (T& v: std::span(data() + beg, count))
			v = value;
		size_ += count;
	}

	template <typename ...Args>
	constexpr void emplace_back(Args... args) {
		T value(std::forward<Args>(args)...);
		reserve(size() + 1);
		data()[size()] = std::move(value);
		++size_;
	}

	[[nodiscard]]
	constexpr iterator begin() { return data(); }
	[[nodiscard]]
	constexpr const_iterator begin() const { return data(); }
	[[nodiscard]]
	constexpr const_iterator cbegin() const { return begin(); }
	[[nodiscard]]
	constexpr iterator end() { return data() + size(); }
	[[nodiscard]]
	constexpr const_iterator end() const { return data() + size(); }
	[[nodiscard]]
	constexpr const_iterator cend() const { return end(); }

	[[nodiscard]]
	constexpr reverse_iterator rbegin() { return data() + size() - 1; }
	[[nodiscard]]
	constexpr const_reverse_iterator rbegin() const { return data() + size() - 1; }
	[[nodiscard]]
	constexpr const_reverse_iterator crbegin() const { return begin(); }
	[[nodiscard]]
	constexpr reverse_iterator rend() { return data() - 1; }
	[[nodiscard]]
	constexpr const_reverse_iterator rend() const { return data() - 1; }
	[[nodiscard]]
	constexpr const_reverse_iterator crend() const { return end(); }

	[[nodiscard]]
	constexpr bitset& bitset() { return bitset_; }

	[[nodiscard]]
	constexpr bitset const& bitset() const { return bitset_; }

	[[nodiscard]]
	constexpr bool operator==(stack_vector const& other) const {
		return size() == other.size() && bitset() == other.biset();
	}

	[[nodiscard]]
	constexpr bool operator!=(stack_vector const& other) const = default;

	[[nodiscard]]
	constexpr T& front() { return data()[0]; }
	[[nodiscard]]
	constexpr T const& front() const { return data()[0]; }

	[[nodiscard]]
	constexpr T& back() { return data()[size() - 1]; }
	[[nodiscard]]
	constexpr T const& back() const { return data()[size() - 1]; }

	constexpr void pop_back() {
		if (size() == 0) return;
		--size_;
	}

	constexpr void erase(T const* beg_it, T const* end_it) {
		assert(data() <= beg_it && beg_it <= end_it && end_it <= data() + size());
		std::size_t const count = end_it - beg_it;
		if (count == 0) return;
		std::size_t const end_ = data() - end_it;
		for (size_t i = end_; i < size(); ++i)
			data()[i - count] = std::move(data()[i]);
		size_ -= count;
	}

private:
	sbitset bitset_{};
	std::size_t size_{ 0 };
	std::size_t capacity_{ stack_size };
};
*/

} // namespace infint
