//
// Created by andyh on 2/2/22.
//

#ifndef LISP_INTERPRETER_NUMBER_HPP
#define LISP_INTERPRETER_NUMBER_HPP

// src
#include <BasicTypes/IBasicType.hpp>
#include <BasicTypes/Null.hpp>

// STL
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

namespace basic_types
{
    class Number : public IBasicType
    {
    public:
        Number(const std::string& source);
        Number(const int value);
        Number(const double value);
        Number();
        ~Number() = default;

        void operator=(const Number& source);
        void operator=(const int val);
        void operator=(const double val);
        void operator<<(std::ostream& stream) override;
        std::string type() const override { return "NUMBER"; }
        std::string str() const override;
        double get() const;


        static bool isNumber(const std::string& text);
    private:
        double _value;
    };
}

#endif //LISP_INTERPRETER_NUMBER_HPP
