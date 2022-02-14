/** LISP INTERPRETER
 *  CS503-001 S22
 * Andrew Hansen
 * arhansen@crimson.ua.edu
 */

// src
#include <Interpreters/CommandLineInterpreter.hpp>
#include <Interpreters/FileReadInterpreter.hpp>
#include <Output/Debug.hpp>

// STL
#include <string>
#include <iostream>

int main(int argc, char** argv)
{
    std::istream& inStream = std::cin;
    std::ostream& outStream = std::cout;

    std::string filePathIn = "";
    bool useFileIn = false;
    output::Debug::useDebug = false;

    // Check for user args
    if(argc != 0)
    {
        // Parse args
        for(int i = 0; i < argc; i++)
        {
            if(std::string(argv[i]) == "-i" && !useFileIn && i != argc - 1)
            {
                useFileIn = true;
                filePathIn = std::string(argv[i + 1]);
            }

            else if(std::string(argv[i]) == "-d")
            {
                output::Debug::useDebug = true;
            }

            else if(std::string(argv[i]) == "--help")
            {
                std::cout << "Command Line LISP Interpreter by Andy Hansen\nCS503-001 Spring 2022\n\n"
                          << "Arguments: \n"
                          << "\t-i: Set input file\n"
                          << "\t-d: Enable debug output\n"
                          << "\t--help: You already know what that does\n";

                return 0;
            }
        }
    }

    // Handle arguments
    if(useFileIn)
    {
        interpreters::FileReadInterpreter interpreter(filePathIn, outStream);
        interpreter.start();
    }
    else
    {
        interpreters::CommandLineInterpreter interpreter(inStream, outStream);
        interpreter.start();
    }

    return 0;
}

