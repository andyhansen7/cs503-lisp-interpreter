/** LISP INTERPRETER
 *  CS503-001 S22
 * Andrew Hansen
 * arhansen@crimson.ua.edu
 */

 #include <iostream>

#include "../src/parser/LispParser.hpp"

int main(void)
{
    parsers::LispParser parser;

    std::cout << parser.parse("(+ 5 6)") << std::endl;

    return 0;
}

