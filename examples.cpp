// std libs
#include <iostream>

// InfInt libs
#include "InfInt.hpp"
#include "InfIntMath.hpp"
#include "InfIntRSA.hpp"
#include "InfIntRandom.hpp"
#include "InfIntText.hpp"

// InfRatio libs
#include "InfRatio.hpp"
#include "InfRatioMath.hpp"

void operators_tests(void);
void exemple_text(void);
void exemple_prime(void);
void exemple_random(void);
void exemple_ratio(void);
void exemple_rsa(void);

int main(void) {
	std::cout << "/!\\ Start /!\\" << std::endl << std::endl;

	//operators_tests();
	//exemple_text();
	//exemple_prime();
	//exemple_random();
	//exemple_ratio();
	exemple_rsa();

	std::cout << std::endl << "/!\\ End /!\\" << std::endl;
	return EXIT_SUCCESS;
}

void exemple_rsa(void) {
	std::cout << "Start Exemple RSA" << std::endl << std::endl;

	InfIntRandomEngine rand(512);

	InfInt p;
	std::cout << "p: ";
	std::cin >> p;
	if (p == 0)
		p = 1'754'397'133;
	else if (p == 1)
		do { p = rand(); if (!p.get(0)) ++p; } while (!InfIntMath::probable_prime(p));

	InfInt q;
	std::cout << "q: ";
	std::cin >> q;
	if (q == 0)
		q = 2'038'064'033;
	else if (q == 1)
		do { q = rand(); if (!q.get(0)) ++q; } while (!InfIntMath::probable_prime(q));

	InfInt min_e;
	std::cout << "min e: ";
	std::cin >> min_e;

	InfIntRSA rsa;
	if (min_e < 2)
		rsa.create_keys(p, q);
	else
		rsa.create_keys(p, q, min_e);

	std::cout << std::endl
		<< "primes: (" << p << ", " << q << ")" << std::endl
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

	std::cout << "End Exemple RSA, press entrer to continue... "; std::cin.get();
	std::cout << std::endl << std::endl << std::endl;
}

void exemple_random(void) {
	std::cout << "Start Exemple Random" << std::endl << std::endl;

	InfIntRandomEngine infg(1024);
	for (int j = 0; j < 255; ++j) {
		std::string s = infg().Bstr();
		std::cout << s << std::endl;
		int count_zero = 0;
		int count_one = 0;
		for (std::string::size_type i = 0; i < s.size(); ++i) {
			if (s.at(i) == '0')
				++count_zero;
			else if (s.at(i) == '1')
				++count_one;
		}
		std::cout << "0: " << count_zero << " | 1: " << count_one << " | size: " << s.size() - 1 << std::endl;
	}

	std::cout << "End Exemple Random, press entrer to continue... "; std::cin.get();
	std::cout << std::endl << std::endl << std::endl;
}

void exemple_prime(void) {
	std::cout << "Start Exemple Prime" << std::endl << std::endl;

	InfIntRandomEngine infg(1024);
	InfInt n;
	do {
		std::cout << std::endl;
		n = infg();
		if (!n.get(0)) ++n;
	} while (!InfIntMath::probable_prime(n));

	std::cout << std::endl << std::endl;
	std::cout << "Result: " << n << std::endl;
	std::cout << std::endl << std::endl;

	std::cout << "End Exemple Prime, press entrer to continue... "; std::cin.get();
	std::cout << std::endl << std::endl << std::endl;
}

void exemple_text(void) {
	std::cout << "Start Exemple Text" << std::endl << std::endl;

	InfIntRandomEngine rand(1024);

	InfInt p;
	std::cout << "p: ";
	std::cin >> p;
	if (p == 0)
		p = 1'754'397'133;
	else if (p == 1)
		do { p = rand(); if (!p.get(0)) ++p; } while (!InfIntMath::probable_prime(p));

	InfInt q;
	std::cout << "q: ";
	std::cin >> q;
	if (q == 0)
		q = 2'038'064'033;
	else if (q == 1)
		do { q = rand(); if (!q.get(0)) ++q; } while (!InfIntMath::probable_prime(q));

	InfInt min_e;
	std::cout << "min e: ";
	std::cin >> min_e;

	InfIntRSA rsa;
	if (min_e < 2)
		rsa.create_keys(p, q);
	else
		rsa.create_keys(p, q, min_e);

	std::cout << std::endl
		<< "primes: (" << p << ", " << q << ")" << std::endl
		<< "public key: (" << rsa.e() << ", " << rsa.n() << ")" << std::endl
		<< "private key: (" << rsa.d() << ", " << rsa.n() << ")" << std::endl
		<< std::endl;

	InfIntText inftext(rsa.n().size() / 8 + (rsa.n().size() % 8 > 0 ? 1 : 0) + 1);
	std::cout << "Text size: " << inftext.block_size() << std::endl;
	std::cout << "Write: ";
	std::cin >> inftext;
	std::cout << "Output: '" << inftext << "'" << std::endl;
	for (InfInt::size_type i = 0; i < inftext.size(); ++i) {
		std::cout << inftext.get(i) << " | ";
		inftext.set(i, rsa.cypher(inftext.get(i)));
		std::cout << inftext.get(i) << std::endl;
	}
	std::cout << "Result: '" << inftext << "'" << std::endl;
	for (InfInt::size_type i = 0; i < inftext.size(); ++i) {
		std::cout << inftext.get(i) << " | ";
		inftext.set(i, rsa.uncypher(inftext.get(i)));
		std::cout << inftext.get(i) << std::endl;
	}
	std::cout << "Back: '" << inftext << "'" << std::endl;

	std::cout << "End Exemple Text, press entrer to continue... "; std::cin.get();
	std::cout << std::endl << std::endl << std::endl;
}

void exemple_ratio(void) {
	std::cout << "Start Exemple Ratio" << std::endl << std::endl;

	InfRatio a(InfInt("2", 10), InfInt("5", 10));
	InfRatio b(InfInt("3", 10), InfInt("2", 10));
	InfRatio r = a / b;

	std::cout << std::endl << std::endl;
	std::cout << "a: " << a << std::endl;
	std::cout << "b: " << b << std::endl;
	std::cout << "r: " << r << std::endl;
	std::cout << std::endl << std::endl;

	std::cout << "End Exemple Ratio, press entrer to continue... "; std::cin.get();
	std::cout << std::endl << std::endl << std::endl;
}

void operators_tests(void) {
	std::cout << "Start Operators' Tests" << std::endl << std::endl;

	int min = -16;
	int max = 16;

	std::cout << "Testing operator+ ..." << std::endl;
	for (int i = min; i < max; ++i)
		for (int j = min; j < max; ++j)
			if ((InfInt(i) + InfInt(j)).to_int_safe<int>() != i + j)
				std::cout << "bug: " << i << " + " << j << " = " << i + j << " or getting: " << (InfInt(i) + InfInt(j)).to_int_safe<int>() << std::endl;
	std::cout << "Finished testing operator+" << std::endl << std::endl;

	std::cout << "Testing operator- ..." << std::endl;
	for (int i = min; i < max; ++i)
		for (int j = min; j < max; ++j)
			if ((InfInt(i) - InfInt(j)).to_int_safe<int>() != i - j)
				std::cout << "bug: " << i << " - " << j << " = " << i - j << " or getting: " << (InfInt(i) - InfInt(j)).to_int_safe<int>() << std::endl;
	std::cout << "Finished testing operator-" << std::endl << std::endl;

	std::cout << "Testing operator* ..." << std::endl;
	for (int i = min; i < max; ++i)
		for (int j = min; j < max; ++j)
			if ((InfInt(i) * InfInt(j)).to_int_safe<int>() != i * j)
				std::cout << "bug: " << i << " * " << j << " = " << i * j << " or getting: " << (InfInt(i) * InfInt(j)).to_int_safe<int>() << std::endl;
	std::cout << "Finished testing operator*" << std::endl << std::endl;

	std::cout << "Testing operator/ ..." << std::endl;
	for (int i = min; i < max; ++i) {
		for (int j = min; j < max; ++j) {
			if (j == 0) continue;
			if ((InfInt(i) / InfInt(j)).to_int_safe<int>() != i / j)
				std::cout << "bug: " << i << " / " << j << " = " << i / j << " or getting: " << (InfInt(i) / InfInt(j)).to_int_safe<int>() << std::endl;
		}
	}
	std::cout << "Finished testing operator/" << std::endl << std::endl;

	std::cout << "Testing operator% ..." << std::endl;
	for (int i = min; i < max; ++i) {
		for (int j = min; j < max; ++j) {
			if (j == 0) continue;
			if ((InfInt(i) % InfInt(j)).to_int_safe<int>() != i % j)
				std::cout << "bug: " << i << " % " << j << " = " << i % j << " or getting: " << (InfInt(i) % InfInt(j)).to_int_safe<int>() << std::endl;
		}
	}
	std::cout << "Finished testing operator%" << std::endl << std::endl;

	std::cout << "Testing fulldiv ..." << std::endl;
	for (int i = min; i < max; ++i) {
		for (int j = min; j < max; ++j) {
			if (j == 0) continue;
			auto result = InfInt::fulldiv(i, j);
			if (result.remainder().to_int_safe<int>() != i % j)
				std::cout << "bug: " << i << " % " << j << " = " << i % j << " or getting: " << result.remainder().to_int_safe<int>() << std::endl;
			if (result.quotient().to_int_safe<int>() != i / j)
				std::cout << "bug: " << i << " / " << j << " = " << i / j << " or getting: " << result.quotient().to_int_safe<int>() << std::endl;
		}
	}
	std::cout << "Finished testing fulldiv" << std::endl << std::endl;

	std::cout << "End Operators' Tests, press entrer to continue... "; std::cin.get();
	std::cout << std::endl << std::endl << std::endl;
}
