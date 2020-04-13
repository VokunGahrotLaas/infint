// C++ libs
#include <iostream>

// InfInt libs
#include "InfInt.hpp"
#include "InfIntRSA.hpp"

void main(void) {
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
}