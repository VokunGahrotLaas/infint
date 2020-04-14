#ifndef INFINTRANDOM_HPP
#define INFINTRANDOM_HPP

// std libs
#include <random>
#include <chrono>
#include <cmath>

// InfInt libs
#include "InfInt.hpp"

class InfIntRandomEngine {
public:
	typedef std::default_random_engine RandomEngine;
	typedef RandomEngine::result_type result_type;

	static const result_type result_size;
	static const result_type result_mask;

	InfIntRandomEngine(result_type size);
	InfIntRandomEngine(result_type size, result_type val);
	template <class Sseq>
	InfIntRandomEngine(result_type size, Sseq& q);
	virtual ~InfIntRandomEngine(void);

	InfInt min(void) const;
	InfInt max(void) const;

	virtual void seed(void);
	virtual void seed(result_type val);
	template <class Sseq>
	void seed (Sseq& q);

	InfInt operator()(void);
	void discard(unsigned long long z);
protected:
	RandomEngine m_random_engine;
	result_type m_size;
	result_type m_top_size;
	result_type m_top_mask;
	result_type m_length;
};

#endif // INFINTRANDOM_HPP