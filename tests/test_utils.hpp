#pragma once

// C++ std
#include <iostream>

// infint
#include <infint/infint.hpp>

class error
{
public:
	enum class type : bool
	{
		none = false,
		error = true
	};

	constexpr error(std::ostream& os = std::cerr)
		: os_{ os }
	{}

	constexpr error(type type, std::ostream& os = std::cerr)
		: type_{ type }
		, os_{ os }
	{}

	error& operator<<(type type)
	{
		type_ = type;
		return *this;
	}

	template <typename T>
	error& operator<<(T&& t)
	{
		if (type_ == type::none) return *this;
		os_ << std::forward<T>(t);
		return *this;
	}

private:
	type type_ = type::none;
	std::ostream& os_;
};
