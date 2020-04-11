# InfInt

## Desc
 C++ library for infinit integers.\
 __Vers:__ 1.3

## Auth
 * [Maxence MICHOT](https://github.com/VokunGahrotLaas)

## Stuff it does
 * Numbers are stored as binary in std::vector<bool>, it as the adventage of using as few storage as posible
 * Bitwise operators as &, |, ^, << and >> are implemented
 * Comparaison operator as ==, !=, >, <=, < and >= are implemented
 * Basic operation are obviusly permited +, -, *, / and %
 * Those things are in too +=, -=, *=, /=, %=, &=, |=, ^=, <<= and >>=
 * Incrementation and decrementation operators are implemented in postfix and prefix
 * .size() returns the number of bits the number is composed of
 * .get(pos) returns the bool in the number at pos or .sign() if pos >= .size()
 * .sign() returns, well... the sign of the number
 * .Bstr() returns a std::string representing the memory
 * .Bstr(str_size) same as .Bstr() but add bits until the string is at least str_size long
 * .str(int base) give out a std::string starting with '+' or '-' and ending with the number in the given base from 2 to 62, base 2 will not reflect memory sush as in .to_Bstr()
 * 255_i is equivalent to InfInt(255) just like 255l is equivalent to long(255)
 * Overloaded operator << for ostream, example cout << 5_i << endl; outputs: "+101\n"
 * You can static_cast<InfInt>(x) or (InfInt)x or InfInt(x) or whatever from these types:
   * c++ char (char)
   * c++ integers (int, long long, unsigned long long, etc...)
   * c++ string (std::string)
 * Cast from std::string have some rules:
   * If the string doesn't starts with '+' or '-' the number will be assumed to be positive
   * Any char other than '0' will be considered as '1' (except for the first char who can also be '+' or '-'), exemple: InfInt("10+3") == InfInt(0b1011) == InfInt(11)
   * Numbers will be assumed to be signed binary, exemple: InfInt("+101") == InfInt("101") == -InfInt("-011")
 * The same rules applies to the output of .to_Bstr()
 * added {void InfInt::full_div(divisor, remainder, quotient) const} that calculate the remainder and the quotient in one execution
 * added consts InfInt::neg_one, InfInt::zero and InfInt::pos_one, the most useful is InfInt::zero wich is used very often, this alows one allocation for multiple uses
 * re-done operator* (faster algorithm)
 * re-done operator/, operator% and full_div (faster algorithm)
 * Cast from std::string with base:
   * Same format as {void InfInt::to_str(int base)}
   * Base between 2 and 62 included
   * The '+' sign can be implicite
   * Any thing other than the sign or a digit under base will be 0
 * Added {InfInt& InfInt::full_div(divisor, remainder)} use (*this) as quotient
 * All not const operators return a reference to self
 * pow is now using binary exponentiation, went from O(n) to O(log2(n))
 * added modpow(a, b, m), return a ** b % m