#ifndef INFINTTEXT_HPP
#define INFINTTEXT_HPP

// std libs
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

// InfInt libs
#include "InfInt.hpp"

class InfIntText {
public:
	typedef InfInt::size_type size_type;
	typedef std::string::value_type char_type;
	static const size_type char_size;

	InfIntText(size_type block_size);
	InfIntText(size_type block_size, const std::string& str);
	virtual ~InfIntText(void);

	void write(const std::string& str);
	void write(std::istream& out);
	std::string read(void) const;
	void clear(void);

	void push(const InfInt& data);
	void push(const InfInt& data, size_type size);
	InfInt pop(void);

	void set(size_type index, const InfInt& data);
	const InfInt& get(size_type index) const;
	size_type size(void);

	void resize_blocks(size_type block_size);
	size_type block_size(void);
protected:
	std::vector<InfInt> m_memory;
	size_type m_block_size;
	size_type m_count;
};

std::ostream& operator<<(std::ostream& out, const InfIntText& text);
std::istream& operator>>(std::istream& in, InfIntText& text);

#endif // INFINTTEXT_HPP