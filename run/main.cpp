/** LISP INTERPRETER
 *  CS503-001 S22
 * Andrew Hansen
 * arhansen@crimson.ua.edu
 */

// src
#include <Interpreters/CommandLineInterpreter.hpp>
#include <Output/Debug.hpp>

int main(void)
{
    output::Debug::useDebug = true;
    interpreters::CommandLineInterpreter interpreter(std::cin, std::cout);
    interpreter.start();

    return 0;
}

