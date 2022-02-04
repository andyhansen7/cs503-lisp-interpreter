//
// Created by andyh on 2/3/22.
//

#ifndef LISP_INTERPRETER_COMMANDLINEINTERPRETER_HPP
#define LISP_INTERPRETER_COMMANDLINEINTERPRETER_HPP

// src
#include <Parsers/Parser.hpp>

// STL
#include <string>
#include <iostream>
#include <memory>

namespace interpreters
{
    class CommandLineInterpreter
    {
    public:
        CommandLineInterpreter(std::istream& inputStream, std::ostream& outputStream);
        ~CommandLineInterpreter() = default;
        CommandLineInterpreter(const CommandLineInterpreter& other) = delete;
        void operator=(const CommandLineInterpreter& other) = delete;

        int start();
    private:
        std::unique_ptr<parsers::Parser> _parser;
        std::istream& _instream;
        std::ostream& _outstream;
    };
}

#endif //LISP_INTERPRETER_COMMANDLINEINTERPRETER_HPP
