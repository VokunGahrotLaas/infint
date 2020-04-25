#include "InfIntRSA.hpp"

InfIntRSA::InfIntRSA(void) {
	//
}

InfIntRSA::InfIntRSA(const InfInt& p, const InfInt& q) {
	this->create_keys(p, q);
}

InfIntRSA::InfIntRSA(const InfInt& p, const InfInt& q, const InfInt& min_e):
	InfIntRSA()
{
	this->create_keys(p, q, min_e);
}

InfIntRSA::~InfIntRSA(void) {
	//
}

void InfIntRSA::create_keys(const InfInt& p, const InfInt& q) {
	this->m_n = p * q;

	//std::cout << "n: " << this->m_n << std::endl;

	InfInt phi((p - InfInt::pos_one) * (q - InfInt::pos_one));

	//std::cout << "phi: " << phi << std::endl;

	this->m_e = InfInt(65'537);

	//std::cout << "e: " << this->m_e << std::endl;

	this->m_d = InfIntMath::modinv(this->m_e, phi);
	if (this->m_d.sign())
		this->m_d += phi;

	//std::cout << "d: " << this->m_d << std::endl;
}

void InfIntRSA::create_keys(const InfInt& p, const InfInt& q, const InfInt& min_e) {
	this->m_n = p * q;

	//std::cout << "n: " << this->m_n << std::endl;

	InfInt phi((p - InfInt::pos_one) * (q - InfInt::pos_one));

	//std::cout << "phi: " << phi << std::endl;

	for (
		this->m_e = min_e;
		!InfIntMath::coprime(this->m_e, phi);
		++this->m_e
		);

	//std::cout << "e: " << this->m_e << std::endl;

	this->m_d = InfIntMath::egcd(this->m_e, phi).x();
	if (this->m_d.sign())
		this->m_d += phi;

	//std::cout << "d: " << this->m_d << std::endl;
}

InfInt InfIntRSA::cypher(const InfInt& unciphered) {
	return InfIntMath::modpow(unciphered, this->m_e, this->m_n);
}

InfInt InfIntRSA::uncypher(const InfInt& ciphered) {
	return InfIntMath::modpow(ciphered, this->m_d, this->m_n);
}
