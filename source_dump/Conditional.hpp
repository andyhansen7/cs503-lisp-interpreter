//
// Created by andyh on 2/3/22.
//

#ifndef LISP_INTERPRETER_CONDITIONAL_HPP
#define LISP_INTERPRETER_CONDITIONAL_HPP

// src
#include "IBasicType.hpp"
#include "Number.cpp"
#include "List.cpp"
#include "ErrorHandle.cpp"

// STL
#include <string>
#include <iostream>

namespace basic_types
{
    class Conditional : public IBasicType
    {
    public:
        Conditional(const std::string& source);
        Conditional(const Conditional& other);
        Conditional(const Number& number);
        Conditional(const List& list);
        Conditional();
        ~Conditional() = default;

        void operator=(const Conditional& other);
        void operator=(const std::string& source);
        operator bool() const;

        static bool isConditional(const std::string& source);

        void operator<<(std::ostream& stream) override;
        std::string type() const override { return "CONDITIONAL"; }
        std::string str() const override;
    private:
        bool _val;

        bool parseConditional(const std::string& source);
    };
}

#endif //LISP_INTERPRETER_CONDITIONAL_HPP
