/** LISP INTERPRETER
 *  CS503-001 S22
 * Andrew Hansen
 * arhansen@crimson.ua.edu
 */

 #include <iostream>

#include "../src/parser/LispParser.hpp"

#include <functions/Functions.hpp>

int main(void)
{
//    parsers::LispParser parser;

//    std::cout << parser.parseCommand("(+ 5 (- 7 2) (/ 10 2))") << std::endl;
//    std::cout << parser.parseCommand("(< 4 (- 7 2) (/ 10 2))") << std::endl;
//    std::cout << parser.parseCommand("(setq x 5)") << std::endl;
//    std::cout << parser.parseCommand("(+ x 4)") << std::endl;
//    std::cout << parser.parseCommand("(if (< 7 3) (+ 3 4) (+ 1 2))") << std::endl;
//    std::cout << parser.parseCommand("(cons 0 1)") << std::endl;

    basic_types::Number a("5"), b = 6, c("7.0");

    std::vector<basic_types::Number> x = {a, b, c};
    std::vector<basic_types::List> y;

    std::cout << functions::globalFunctions.at("+")({.numberOperands = x, .listOperands = y})->str() << std::endl;
    std::cout << functions::globalFunctions.at("-")({.numberOperands = x, .listOperands = y})->str() << std::endl;

    return 0;
}

