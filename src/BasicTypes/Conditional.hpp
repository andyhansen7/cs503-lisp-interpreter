//
// Created by andyh on 2/3/22.
//

#ifndef LISP_INTERPRETER_CONDITIONAL_HPP
#define LISP_INTERPRETER_CONDITIONAL_HPP

// src
#include <BasicTypes/IBasicType.hpp>
#include <BasicTypes/Number.hpp>
#include <BasicTypes/List.hpp>
#include <Output/ErrorHandle.hpp>

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
        bool isNull() const override { return _isNull; }
        std::string str() override;
    private:
        bool _val;
        bool _isNull;

        bool parseConditional(const std::string& source);
    };
}

#endif //LISP_INTERPRETER_CONDITIONAL_HPP
