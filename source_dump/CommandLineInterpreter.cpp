//
// Created by andyh on 2/3/22.
//
#ifndef __CLI
#define __CLI

#include "CommandLineInterpreter.hpp"

// STL
#include <vector>

using namespace interpreters;

CommandLineInterpreter::CommandLineInterpreter(std::istream& inputStream, std::ostream& outputStream)
    : _instream(inputStream), _outstream(outputStream)
{
    _parser = std::make_unique<parsers::Parser>();
}

int CommandLineInterpreter::start()
{
    _outstream << "Command Line LISP Interpreter by Andy Hansen\nCS503-001 Spring 2022\n\n"
               << "Enter commands one at a time on each line and press \'Enter\' to execute\n"
               << "Enter (exit) to exit the interpreter" << std::endl;

    while(true)
    {
        std::string userInput = "";
        std::vector<std::string> result;
        std::string prompt = "> ";
        bool exception = false;

        // Load line from user
        _outstream << prompt;
        std::getline(_instream, userInput);

        if(userInput == "(exit)")
        {
            return 0;
        }

        try
        {
            result = _parser->parse(userInput);
        }
        catch(const std::exception& e)
        {
            _outstream << "\033[31m" << "Invalid command: " << userInput << std::endl << '\t' << e.what() << "\033[0m" << std::endl;
            exception = true;
        }
        if(!exception)
        {
            for(const auto& str : result)
            {
                _outstream << str << std::endl;
            }
        }
    }
}
#endif
