# InfInt

## Desc
 Library for infinit integers.\
 __Vers:__ 1.1

## Auth
 * [Maxence MICHOT](https://github.com/VokunGahrotLaas)

## Stuff it does
 * Numbers are stored as binary in std::vector<bool>, it as the adventage of using as few storage as posible\
 * Bitwise operators as &, |, ^, << and >> are implemented\
 * Comparaison operator as ==, !=, >, <=, < and >= are implemented\
 * Basic operation are obviusly permited +, -, *, / and %\
 * Those things are in too +=, -=, *=, /=, %=, &=, |=, ^=, <<= and >>=\
 * Incrementation and decrementation operators are implemented in postfix and prefix\
 * .size() returns the number of bits the number is composed of\
 * .get(pos) returns the bool in the number at pos\
 * .sign() returns, well... the sign of the number\
 * .to_Bstr() returns a std::string representing the memory\
 * .to_Bstr(str_size) same as .b_str() but add bits until the string is str_size long\
 * .to_str(int base) give out a std::string starting with '+' or '-' and ending with the number in the given base from 2 to 62, base 2 will not reflect memory sush as in .to_Bstr()\
 * 255_i is equivalent to scp::math::Int(255) just like 255l is equivalent to long(255)\
 * Overloaded operator << for ostream, example cout << 5_i << endl; outputs: "+101\n"\
 * use "using namespace scp::math;"\
 *  of "typedef scp::math::Int Int;"\
 * Don't be be silly and write scp::math::Int each time\
 * You can static_cast<Int>(x) or (Int)x or Int(x) or whatever from these types:\
  1. c++ char (char)\
  2. c++ integers (int, long long, unsigned long long, etc...)\
  3. c++ string (std::string)\
 * Cast from std::string have some rules:\
  1. If the string doesn't starts with '+' or '-' the number will be assumed to be positive\
  2. Any char other than '0' will be considered as '1' (except for the first char who can also be '+' or '-'), exemple: Int("10+3") == Int(0b1011) == Int(11)\
  3. Numbers will be assumed to be signed binary, exemple: Int("+101") == Int("101") == -Int("-011")\
 * The same rules applies to the output of .to_Bstr()\
 * added .full_div(divisor, remainder, quotient) that calculate the remander and the quotient in one execution\
 * added consts Int::neg_one, Int::zero and Int::pos_one, the most useful is Int::zero wich is used very often, this alows one allocation for multiple uses\