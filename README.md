# InfInt

## Desc
 Library for infinit integers.\
 __Vers:__ 1.0

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
 * .b_str() returns a std::string representing the memory\
 * .b_str(str_size) same as .b_str() but add bits until the string is str_size long\
 * .str(int base) give out a std::string starting with '+' or '-' and ending with the number in the given base from 2 to 36\
 * 255_i is equivalent to scp::math::Int(255) just like 255l is equivalent to long(255)\
 * Overloaded operator << for ostream, example cout << 5_i << endl; outputs: "+101\n"\
 * I did not just spent like two fucking days on it and it totaly is not 7:25AM.\