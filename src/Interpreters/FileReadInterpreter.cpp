//
// Created by andyh on 2/13/22.
//

#include "FileReadInterpreter.hpp"

// STL
#include <vector>

using namespace interpreters;

FileReadInterpreter(const std::string& filePath, std::ostream& outputStream)
        : _filePath(filePath), _outstream(outputStream)
{
    _instream = std::ifstream(_filePath, std::ifstream::in);
    _parser = std::make_unique<parsers::Parser>();
}

int FileReadInterpreter::start()
{
    _outstream << "File Based LISP Interpreter by Andy Hansen\nCS503-001 Spring 2022\n"
               << "Running script from file " << _filePath << std::endl;

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
        catch(std::exception e)
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