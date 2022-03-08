//
// Created by andyh on 2/13/22.
//
#ifndef __FRI
#define __FRI

#include "FileReadInterpreter.hpp"

// STL
#include <vector>

using namespace interpreters;

FileReadInterpreter::FileReadInterpreter(const std::string& filePath, std::ostream& outputStream)
        : _filePath(filePath), _outstream(outputStream)
{
    _parser = std::make_unique<parsers::Parser>();
}

int FileReadInterpreter::start()
{
    _outstream << "File Based LISP Interpreter by Andy Hansen\nCS503-001 Spring 2022\n"
               << "Running script from file " << _filePath << std::endl;

    std::ifstream file;
    file.open(_filePath);

    while(true)
    {
        std::string line = "";
        std::vector<std::string> result;
        bool exception = false;

        // Load line from user
        std::getline(file, line);

        if(line == "(exit)" || line.empty())
        {
            file.close();
            return 0;
        }

        try
        {
            result = _parser->parse(line);
        }
        catch(const std::exception& e)
        {
            _outstream << "\033[31m" << "Invalid command: " << line << std::endl << '\t' << e.what() << "\033[0m" << std::endl;
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