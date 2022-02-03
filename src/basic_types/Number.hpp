//
// Created by andyh on 2/2/22.
//

#ifndef LISP_INTERPRETER_NUMBER_HPP
#define LISP_INTERPRETER_NUMBER_HPP

// src
#include <basic_types/IBasicType.hpp>

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

        double get();
        bool castToInt();
        std::string str() override;

        static bool isNumber(const std::string& text);
        static bool isInteger(const std::string& text);
        static bool isFloat(const std::string& text);
        static bool allAreIntegers(std::vector<Number> numbers);
    private:
        double _value;
        int _castToInt;
    };
}

#endif //LISP_INTERPRETER_NUMBER_HPP
