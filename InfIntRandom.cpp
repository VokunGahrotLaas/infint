#include "InfIntRandom.hpp"



const InfIntRandomEngine::result_type InfIntRandomEngine::result_size = InfIntRandomEngine::RandomEngine::max() + 1 == 0 ? sizeof(InfIntRandomEngine::result_type) * 8 : floor(log2(InfIntRandomEngine::RandomEngine::max() + 1));
const InfIntRandomEngine::result_type InfIntRandomEngine::result_mask = (1 << InfIntRandomEngine::result_size) - 1;

InfIntRandomEngine::InfIntRandomEngine(result_type size):
	m_random_engine(),
	m_size(size),
	m_length(size / this->result_size),
	m_top_size(size % this->result_size),
	m_top_mask((1 << this->m_top_size) - 1)
{
	this->seed();
}

InfIntRandomEngine::InfIntRandomEngine(result_type size, result_type val):
	m_random_engine(val),
	m_size(size),
	m_length(size / this->result_size),
	m_top_size(size % this->result_size),
	m_top_mask((1 << this->m_top_size) - 1)
{
	//
}

template <class Sseq>
InfIntRandomEngine::InfIntRandomEngine(result_type size, Sseq& q) :
	m_random_engine(q),
	m_size(size),
	m_length(size / this->result_size),
	m_top_size(size % this->result_size),
	m_top_mask((1 << this->m_top_size) - 1)
{
	//
}

InfIntRandomEngine::~InfIntRandomEngine(void) {
	//
}

InfInt InfIntRandomEngine::min(void) const {
	return InfInt::zero;
}

InfInt InfIntRandomEngine::max(void) const {
	return (InfInt::pos_one << this->m_size) - InfInt::pos_one;
}

void InfIntRandomEngine::seed(void) {
	try {
		this->m_random_engine.seed(std::random_device()());
	} catch (const std::exception&) {
		this->m_random_engine.seed(std::chrono::system_clock::now().time_since_epoch().count());
	}
}

void InfIntRandomEngine::seed(result_type val) {
	this->m_random_engine.seed(val);
}

template <class Sseq>
void InfIntRandomEngine::seed(Sseq& q) {
	this->m_random_engine.seed(q);
}

InfInt InfIntRandomEngine::operator()(void) {
	InfInt tmp;
	if (this->m_top_size != 0)
		tmp |= this->m_top_mask & this->m_random_engine();
	for (result_type i = 0; i < this->m_length; ++i) {
		tmp <<= this->result_size;
		tmp |= this->m_random_engine();
	}
	return tmp;
}

void InfIntRandomEngine::discard(unsigned long long z) {
	this->m_random_engine.discard(this->m_length);
	if (this->m_top_size != 0)
		this->m_random_engine.discard(1);
}
