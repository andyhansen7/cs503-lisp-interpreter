//
// Created by andyh on 2/16/22.
//

#ifndef LISP_INTERPRETER_NULL_HPP
#define LISP_INTERPRETER_NULL_HPP

// src
#include "IBasicType.hpp"

// STL
#include <string>

namespace basic_types
{
    class Null : public IBasicType
    {
    public:
        Null() {}
        Null(const std::string&) {}
        ~Null() = default;

        void operator<<(std::ostream& stream) override { stream << std::string("()"); }
        std::string type() const override { return "NULL"; }
        std::string str() const override { return "()"; }
        static bool isNull(const std::string& data) { return data == "()"; }
    };
}


#endif //LISP_INTERPRETER_NULL_HPP
