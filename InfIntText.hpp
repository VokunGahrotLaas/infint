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
	size_type m_block_size;
	size_type m_count;
	std::vector<InfInt> m_memory;
};

std::ostream& operator<<(std::ostream& out, const InfIntText& text);
std::istream& operator>>(std::istream& in, InfIntText& text);



const InfIntText::size_type InfIntText::char_size = sizeof(InfIntText::char_type) * 8;

InfIntText::InfIntText(size_type block_size):
	m_block_size(block_size),
	m_count(0),
	m_memory()
{
	//
}

InfIntText::InfIntText(size_type block_size, const std::string& str):
	m_block_size(block_size),
	m_count(0),
	m_memory()
{
	this->write(str);
}

InfIntText::~InfIntText(void) {
	//
}

void InfIntText::write(const std::string& str) {
	InfInt buffer;
	if (this->m_count > 0)
		buffer = this->pop();
	for (size_type i = 0; i < str.size(); ++i) {
		buffer <<= InfIntText::char_size;
		buffer |= str[i];
		++this->m_count;
		if (this->m_count >= this->m_block_size) {
			this->push(buffer);
			buffer >>= this->m_block_size * InfIntText::char_size;
			this->m_count = 0;
		}
	}
	if (this->m_count > 0)
		this->push(buffer);
}

void InfIntText::write(std::istream& in) {
	in.ignore();
	InfInt buffer;
	if (this->m_count > 0)
		buffer = this->pop();
	while (!in.eof()) {
		buffer <<= InfIntText::char_size;
		char_type c = in.get();
		if (c == '\n')
			break;
		buffer |= c;
		++this->m_count;
		if (this->m_count >= this->m_block_size) {
			this->push(buffer);
			buffer >>= this->m_block_size * InfIntText::char_size;
			this->m_count = 0;
		}
	}
	if (this->m_count > 0)
		this->push(buffer);
}

std::string InfIntText::read(void) const {
	std::string str;
	InfInt buffer;
	for (size_type i = 0; i < this->m_memory.size(); ++i) {
		buffer |= this->m_memory[this->m_memory.size() - i - 1];
		for (size_type j = 0; j < this->m_block_size; ++j) {
			str.push_back(buffer.to_int<char_type>());
			buffer >>= InfIntText::char_size;
		}
	}
	std::reverse(str.begin(), str.end());
	return str;
}

void InfIntText::clear(void) {
	this->m_memory.clear();
}

void InfIntText::push(const InfInt& data) {
	if (data.size() > this->m_block_size * InfIntText::char_size)
		throw std::invalid_argument(std::string("void InfIntText::push(const InfInt& data): data is too big (") + std::to_string(data.size()) + " > " + std::to_string(this->m_block_size * InfIntText::char_size) + ")");
	this->m_memory.push_back(data);
	this->m_count = 0;
}

void InfIntText::push(const InfInt& data, size_type size) {
	if (0 < size && size <= this->m_block_size)
		throw std::invalid_argument(std::string("void InfIntText::push(const InfInt& data, size_type size): invalid size, must have 0 < size < block_size (0 < ") + std::to_string(size) + " < " + std::to_string(this->m_block_size) + ")");
	if (data.size() > size * InfIntText::char_size)
		throw std::invalid_argument(std::string("void InfIntText::push(const InfInt& data, size_type size): data is too big (") + std::to_string(data.size()) + " > " + std::to_string(size * InfIntText::char_size) + ")");
	this->m_memory.push_back(data);
	this->m_count = size % this->m_block_size;
}

InfInt InfIntText::pop(void) {
	InfInt data = this->m_memory.back();
	this->m_memory.pop_back();
	return data;
}

void InfIntText::set(size_type index, const InfInt& data) {
	this->m_memory[index] = data;
	if (index + 1 == this->m_memory.size())
		this->m_count = 0;
}

const InfInt& InfIntText::get(size_type index) const {
	return this->m_memory.at(index);
}

InfIntText::size_type InfIntText::size(void) {
	return this->m_memory.size();
}

void InfIntText::resize_blocks(size_type block_size) {
	//
}

InfIntText::size_type InfIntText::block_size(void) {
	return this->m_block_size;
}


std::ostream& operator<<(std::ostream& out, const InfIntText& text) {
	out << text.read();
	return out;
}

std::istream& operator>>(std::istream& in, InfIntText& text) {
	text.write(in);
	return in;
}

#endif // INFINTTEXT_HPP