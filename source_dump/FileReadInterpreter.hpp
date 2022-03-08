//
// Created by andyh on 2/13/22.
//

#ifndef LISP_INTERPRETER_FILEREADINTERPRETER_HPP
#define LISP_INTERPRETER_FILEREADINTERPRETER_HPP

// src
#include "Parser.cpp"

// STL
#include <string>
#include <iostream>
#include <fstream>
#include <memory>

namespace interpreters
{
    class FileReadInterpreter
    {
    public:
        FileReadInterpreter(const std::string& filePath, std::ostream& outputStream);
        ~FileReadInterpreter() = default;
        FileReadInterpreter(const FileReadInterpreter& other) = delete;
        void operator=(const FileReadInterpreter& other) = delete;

        int start();
    private:
        std::unique_ptr<parsers::Parser> _parser;
        std::string _filePath;
        std::ostream& _outstream;
    };
}


#endif //LISP_INTERPRETER_FILEREADINTERPRETER_HPP
