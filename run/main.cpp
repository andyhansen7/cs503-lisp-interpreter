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

    std::cout << parser.parseCommand("(+ 5 (- 7 2) (/ 10 2))") << std::endl;
    std::cout << parser.parseCommand("(< 4 (- 7 2) (/ 10 2))") << std::endl;
    std::cout << parser.parseCommand("(setq x 5)") << std::endl;
    std::cout << parser.parseCommand("(+ x 4)") << std::endl;

    return 0;
}

