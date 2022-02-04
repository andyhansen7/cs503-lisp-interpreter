/** LISP INTERPRETER
 *  CS503-001 S22
 * Andrew Hansen
 * arhansen@crimson.ua.edu
 */

 #include <iostream>

#include <Parsers/Parser.hpp>
#include <BasicTypes/Number.hpp>
#include <BasicTypes/List.hpp>

int main(void)
{
    parsers::Parser p;

    std::cout << p.parse("(+ 1 2 3)") << std::endl;
    std::cout << Number("1234.5").str() << std::endl;
    std::cout << List("(1 2 3 4 5").str() << std::endl;

    return 0;
}

