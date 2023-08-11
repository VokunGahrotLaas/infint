#pragma once

// C++ std
#include <memory>
#include <span>

namespace infint
{

template <typename T>
class stack_allocator
{
public:
	using type = stack_allocator<T>;
	using value_type = T;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;
	template <typename U>
	struct rebind
	{
		using other = stack_allocator<U>;
	};

	constexpr stack_allocator(std::span<T> stack) noexcept
		: stack_{ stack }
	{}
	constexpr stack_allocator(stack_allocator const&) noexcept = default;
	constexpr stack_allocator(stack_allocator&&) noexcept = default;
	template <typename U>
	constexpr stack_allocator(stack_allocator<U> const& other) noexcept
		: stack_{ other.stack_ }
	{}

	constexpr ~stack_allocator() noexcept = default;

	[[nodiscard]]
	constexpr T* allocate(std::size_t n)
	{
		if (n == 0 || pos_ + n > max_size())
		{
			std::new_handler handler = std::get_new_handler();
			if (handler == nullptr) throw std::bad_alloc();
			handler();
			return nullptr;
		}
		T* addr = data() + pos_;
		pos_ += n;
		return addr;
	}

	constexpr void deallocate(T* p, std::size_t n) noexcept
	{
		if (data() + pos_ == p + n) pos_ -= n;
	}

	[[nodiscard]]
	constexpr std::size_t max_size() const noexcept
	{
		return stack_.size();
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

protected:
	std::span<T> stack_;
	std::size_t pos_{ 0 };
};

template <typename T1, typename T2>
constexpr bool operator==(stack_allocator<T1> const& lhs, stack_allocator<T2> const& rhs) noexcept
{
	return lhs.data() == rhs.data() && lhs.max_size() && rhs.max_size();
}

template <typename T1, typename T2>
constexpr bool operator!=(stack_allocator<T1> const& lhs, stack_allocator<T2> const& rhs) noexcept
{
	return !(lhs == rhs);
}

} // namespace infint
