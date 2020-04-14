// std libs
#include <iostream>

// InfInt libs
#include "InfInt.hpp"
#include "InfIntMath.hpp"
#include "InfIntRSA.hpp"
#include "InfIntRandom.hpp"

void exemple_rsa(void) {
	std::cout << "Start Exemple RSA" << std::endl;

	InfInt p;
	std::cout << "p: ";
	std::cin >> p;
	if (p == 0)
		p = 1754397133;

	InfInt q;
	std::cout << "q: ";
	std::cin >> q;
	if (q == 0)
		q = 2038064033;

	InfInt min_e;
	std::cout << "min e: ";
	std::cin >> min_e;
	if (min_e < 2)
		q = 2;

	InfIntRSA rsa(p, q, min_e);

	std::cout << std::endl
		<< "public key: (" << rsa.e() << ", " << rsa.n() << ")" << std::endl
		<< "private key: (" << rsa.d() << ", " << rsa.n() << ")" << std::endl
		<< std::endl;

	InfInt ascii;
	std::cout << "ascii: ";
	std::cin >> ascii;
	while (ascii != 0) {
		InfInt cyphered = rsa.cypher(ascii);
		std::cout << "cyphered: " << cyphered << std::endl;
		std::cout << "uncyphered: " << rsa.uncypher(cyphered) << std::endl;
		std::cout << std::endl;
		std::cout << "ascii: ";
		std::cin >> ascii;
	}

	std::cout << "End Exemple RSA" << std::endl;
	std::cout << std::endl << std::endl << std::endl;
}

void exemple_random(void) {
	std::cout << "Start Exemple Random" << std::endl;

	InfIntRandomEngine infg(1024);
	for (int j = 0; j < 255; ++j) {
		std::string s = infg().Bstr();
		std::cout << s << std::endl;
		int count_zero = 0;
		int count_one = 0;
		for (int i = 0; i < s.size(); ++i) {
			if (s.at(i) == '0')
				++count_zero;
			else if (s.at(i) == '1')
				++count_one;
		}
		std::cout << "0: " << count_zero << " | 1: " << count_one << " | size: " << s.size() - 1 << std::endl;
	}

	std::cout << "End Exemple Random" << std::endl;
	std::cout << std::endl << std::endl << std::endl;
}

void exemple_prime(void) {
	std::cout << "Start Exemple Prime" << std::endl;

	InfIntRandomEngine infg(256);
	InfInt n = infg();
	if (!n.get(0)) ++n;
	std::cout << "Generated: " << n << std::endl;
	if (InfIntMath::probable_prime_base(n, 2))
		std::cout << "is probable prime base 2" << std::endl;
	else
		std::cout << "is composite" << std::endl;

	std::cout << "End Exemple Prime" << std::endl;
	std::cout << std::endl << std::endl << std::endl;
}

int main(void) {
	exemple_prime();
	std::cout << "Press entrer to continue... "; std::cin.get();
	exemple_random();
	std::cout << "Press entrer to continue... "; std::cin.get();
	exemple_rsa();
	std::cout << "Press entrer to continue... "; std::cin.get();
}