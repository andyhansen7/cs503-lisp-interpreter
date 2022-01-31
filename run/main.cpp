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

    std::cout << parser.parseCommand("(+ 5 (- 6 2))") << std::endl;

    return 0;
}

